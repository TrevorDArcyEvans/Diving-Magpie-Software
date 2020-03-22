// ==========================================================
// PNG Loader and Writer
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Herve Drolon (drolon@infonie.fr)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <stdlib.h>
#include <memory.h> 

#include "..\LibPNG\png.h"

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef PNG_ENABLED

// ----------------------------------------------------------

#define PNG_BYTES_TO_CHECK 8

// ----------------------------------------------------------

static FreeImageIO *s_io;
static fi_handle s_handle;

/////////////////////////////////////////////////////////////////////////////
// libpng interface 
// 

static void
_ReadProc(struct png_struct_def *, unsigned char *data, unsigned int size) {
	s_io->read_proc(data, size, 1, s_handle);
}

static void
_WriteProc(struct png_struct_def *, unsigned char *data, unsigned int size) {
	s_io->write_proc(data, size, 1, s_handle);
}

static void
_FlushProc(png_structp png_ptr) {
	// empty flush implementation, since the default one seems to crash
}

// in FreeImage warnings and errors are disabled

static void
error_handler(struct png_struct_def *,const char *error) {
	throw error;
}

static void
warning_handler(struct png_struct_def *, const char *warning) {
}

// ----------------------------------------------------------
//   PNG Loading
// ----------------------------------------------------------

void *
FreeImage_LoadPNG(const char *filename, PNGFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadPNGFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadPNGFromHandle(FreeImageIO *io, fi_handle handle, PNGFlags flags) {
	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	png_colorp png_palette;
	int bpp, color_type, palette_entries;

	BYTE *dib = NULL;
	RGBQUAD *palette;	// pointer to dib palette
	png_bytepp  row_pointers = NULL;
	int i;

	s_io = io;
	s_handle = handle;

	if (handle) {
		try {		
			unsigned char png_check[PNG_BYTES_TO_CHECK];

			// check to see if the file is in fact a PNG file

			io->read_proc(png_check, 1, PNG_BYTES_TO_CHECK, handle);

			if (png_sig_cmp(png_check, (png_size_t)0, PNG_BYTES_TO_CHECK) != 0) {
				return NULL;	// Bad signature
			}
			
			// create the chunk manage structure

			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)error_handler, error_handler, warning_handler);

			if (!png_ptr) {
				return NULL;
			}

			// create the info structure

		    info_ptr = png_create_info_struct(png_ptr);

			if (!info_ptr) {
				png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
				return NULL;
			}

			// init the IO
			png_set_read_fn(png_ptr, info_ptr, _ReadProc);

			if (setjmp(png_jmpbuf(png_ptr))) {
				png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
				return NULL;
			}

			// Because we have already read the signature...

			png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);

			// read the IHDR chunk

			png_read_info(png_ptr, info_ptr);
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bpp, &color_type, NULL, NULL, NULL);

			// DIB's don't support >8 bits per sample
			// => tell libpng to strip 16 bit/color files down to 8 bits/color

			if(bpp == 16) {
				png_set_strip_16(png_ptr);
				bpp = 8;
			}

			if (color_type & PNG_COLOR_MASK_ALPHA) {
				png_set_strip_alpha(png_ptr); // DIB's don't support alpha channel
			}

			// Set some additional flags

			switch(color_type) {
				case PNG_COLOR_TYPE_RGB:
				case PNG_COLOR_TYPE_RGB_ALPHA:
					// Flip the RGB pixels to BGR (or RGBA to BGRA)

					png_set_bgr(png_ptr);
					break;

				case PNG_COLOR_TYPE_PALETTE:
					// Expand palette images to the full 8 bits from 2 or 4 bits/pixel

					if ((bpp == 2) || (bpp == 4)) {
						png_set_packing(png_ptr);
						bpp = 8;
					}					

					break;

				case PNG_COLOR_TYPE_GRAY:
				case PNG_COLOR_TYPE_GRAY_ALPHA:
					// Expand grayscale images to the full 8 bits from 2 or 4 bits/pixel

					if ((bpp == 2) || (bpp == 4)) {
						png_set_expand(png_ptr);
						bpp = 8;
					}

					break;

				default:
					throw "PNG format not supported";
			}

			// Set the background color to draw transparent and alpha images over.
			// It is possible to set the red, green, and blue components directly
			// for paletted images instead of supplying a palette index.  Note that
			// even if the PNG file supplies a background, you are not required to
			// use it - you should use the (solid) application background if it has one.

			png_color_16 my_background= { 0, 255, 255, 255, 0 };
			png_color_16 *image_background;

			if (png_get_bKGD(png_ptr, info_ptr, &image_background)) {
				png_set_background(png_ptr, image_background, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
			} else {
				png_set_background(png_ptr, &my_background, PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
			}

			// if this image has transparency, store the trns values

			png_bytep trans            = NULL;
			int num_trans              = 0;
			png_color_16p trans_values = NULL;

			png_uint_32 transparent_value = png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &trans_values);

			// unlike the example in the libpng documentation, we have *no* idea where
			// this file may have come from--so if it doesn't have a file gamma, don't
			// do any correction ("do no harm")

			double gamma = 0;
			double screen_gamma = 2.2;

			if (png_get_gAMA(png_ptr, info_ptr, &gamma)) {
				png_set_gamma(png_ptr, screen_gamma, gamma);
			}

			// All transformations have been registered; now update info_ptr data

			png_read_update_info(png_ptr, info_ptr);

			// Create a DIB and write the bitmap header
			// set up the DIB palette, if needed

			switch(color_type) {
				case PNG_COLOR_TYPE_RGB:
				case PNG_COLOR_TYPE_RGB_ALPHA:
					dib = (BYTE *)FreeImage_Allocate(width, height, 24);
					break;

				case PNG_COLOR_TYPE_PALETTE:
					dib = (BYTE *)FreeImage_Allocate(width, height, bpp);

					png_get_PLTE(png_ptr,info_ptr, &png_palette,&palette_entries);

					palette = FreeImage_GetPalette(dib);

					// store the palette

					for (i = 0; i < palette_entries; i++) {
						palette[i].rgbRed   = png_palette[i].red;
						palette[i].rgbGreen = png_palette[i].green;
						palette[i].rgbBlue  = png_palette[i].blue;
					}

					// store the transparency table

					if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
						FreeImage_SetTransparencyTable(dib, (BYTE *)trans, num_trans);
					}

					break;

				case PNG_COLOR_TYPE_GRAY:
				case PNG_COLOR_TYPE_GRAY_ALPHA:
					dib = (BYTE *)FreeImage_Allocate(width, height, bpp);

					palette = FreeImage_GetPalette(dib);
					palette_entries = 1 << bpp;

					for (i = 0; i < palette_entries; i++) {
						palette[i].rgbRed   =
						palette[i].rgbGreen =
						palette[i].rgbBlue  = (i * 255)/ (palette_entries - 1);
					}

					// store the transparency table

					if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
						FreeImage_SetTransparencyTable(dib, (BYTE *)trans, num_trans);
					}

					break;
			}

			// DIBs *do* support physical resolution

			if (png_get_valid(png_ptr,info_ptr,PNG_INFO_pHYs)) {
				png_uint_32 res_x, res_y;
				
				// We'll overload this var and use 0 to mean no phys data,
				// since if it's not in meters we can't use it anyway

				int res_unit_type = 0;

				png_get_pHYs(png_ptr,info_ptr,&res_x,&res_y,&res_unit_type);

				if (res_unit_type == 1) {
					BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(dib);

					bih->biXPelsPerMeter = res_x;
					bih->biYPelsPerMeter = res_y;
				}
			}

			// Read the image...

			// Set the individual row_pointers to point at the correct offsets

			row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep));

			if (!row_pointers) {
				png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
				FreeImage_Free(dib);
				return NULL;
			}

			for (png_uint_32 k = 0; k < height; k++) {
				row_pointers[height - 1 - k] = FreeImage_GetScanLine(dib, k);
			}

			png_read_image(png_ptr, row_pointers);
			
			free(row_pointers);
			png_read_end(png_ptr, info_ptr);
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

			return (void*)dib;

		} catch (char *text) {
			if (png_ptr) {
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			}

			if (row_pointers) {
				free(row_pointers);
			}

			if (dib) {
				FreeImage_Free(dib);
			}

			if (FreeImage_OutputMessage) {
				FreeImage_OutputMessage(FIF_PNG, text);
			}
			
			return NULL;
		}
	}			

	return NULL;
}

// ----------------------------------------------------------
//   PNG Saving
// ----------------------------------------------------------

BOOL
FreeImage_SavePNG(void *dib, const char *filename, PNGFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "wb");
	
	if (handle) {
		BOOL success = FreeImage_SavePNGToHandle(dib, &io, (fi_handle)handle, flags);

		fclose(handle);

		return success;
	}

	return FALSE;
}

// ----------------------------------------------------------

BOOL
FreeImage_SavePNGToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNGFlags flags) {
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette = NULL;
	png_bytepp row_pointers = NULL;
	png_uint_32 width, height;

	RGBQUAD *pal;	// pointer to dib palette
	int bit_depth;
	int palette_entries;
	int	interlace_type;

	s_io = io;
	s_handle = handle;

	if((dib) && (handle)) {
		try {

			// create the chunk manage structure

			png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)error_handler, error_handler, warning_handler);

			if (!png_ptr)  {
				return FALSE;
			}

			// Allocate/initialize the image information data.

			info_ptr = png_create_info_struct(png_ptr);

			if (!info_ptr)  {
				png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
				return FALSE;
			}

			// Set error handling.  REQUIRED if you aren't supplying your own
			// error handling functions in the png_create_write_struct() call.

			if (setjmp(png_jmpbuf(png_ptr)))  {
				// If we get here, we had a problem reading the file

				png_destroy_write_struct(&png_ptr, &info_ptr);

				return FALSE;
			}

			// init the IO; _FlushProc has been set to NULL to let it use the default lib function

			png_set_write_fn(png_ptr, info_ptr, _WriteProc, _FlushProc);

			// DIBs *do* support physical resolution

			BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(dib);
			png_uint_32 res_x = bih->biXPelsPerMeter;
			png_uint_32 res_y = bih->biYPelsPerMeter;

			if ((res_x > 0) && (res_y > 0))  {
				png_set_pHYs(png_ptr, info_ptr, res_x, res_y, 1);
			}
	
			// Set the image information here.  Width and height are up to 2^31,
			// bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
			// the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
			// PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
			// or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
			// PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
			// currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED

			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			bit_depth = FreeImage_GetBPP(dib);

			if ((bit_depth == 16) || (bit_depth == 32))  {
				png_destroy_write_struct(&png_ptr, &info_ptr);

				throw "Format not supported";	// Note: this could be enhanced here...
			}

			bit_depth = (bit_depth > 8) ? 8 : bit_depth;

			interlace_type = PNG_INTERLACE_NONE;	// Default value

			switch (FreeImage_GetColorType(dib))	{
				case FIC_MINISWHITE:
					// Invert monochrome files to have 0 as black and 1 as white
					// (no break here)
					png_set_invert_mono(png_ptr);

				case FIC_MINISBLACK:
					png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
						PNG_COLOR_TYPE_GRAY, interlace_type, 
						PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
					break;

				case FIC_PALETTE:
				{
					png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
						PNG_COLOR_TYPE_PALETTE, interlace_type, 
						PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

					// set the palette

					palette_entries = 1 << bit_depth;
					palette = (png_colorp)png_malloc(png_ptr, palette_entries * sizeof (png_color));
					pal = FreeImage_GetPalette(dib);

					for (int i = 0; i < palette_entries; i++) {
						palette[i].red   = pal[i].rgbRed;
						palette[i].green = pal[i].rgbGreen;
						palette[i].blue  = pal[i].rgbBlue;
					}
					
					png_set_PLTE(png_ptr, info_ptr, palette, palette_entries);

					// You must not free palette here, because png_set_PLTE only makes a link to
					// the palette that you malloced.  Wait until you are about to destroy
					// the png structure.

					break;
				}

				case FIC_RGB:
					png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
						PNG_COLOR_TYPE_RGB, interlace_type, 
						PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

					// flip BGR pixels to RGB

					png_set_bgr(png_ptr);
					break;
			}

			// Optional gamma chunk is strongly suggested if you have any guess
			// as to the correct gamma of the image.
			// png_set_gAMA(png_ptr, info_ptr, gamma);

			// Write the file header information.
			png_write_info(png_ptr, info_ptr);

			// Write image data ...

			// Set the individual row_pointers to point at the correct offsets
			row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep));

			if (!row_pointers) {
				png_destroy_write_struct(&png_ptr, &info_ptr);
				return FALSE;
			}

			for (png_uint_32 k = 0; k < height; k++) {
				row_pointers[height - 1 - k] = FreeImage_GetScanLine(dib, k);
			}

			// write out the entire image data in one call
			png_write_image(png_ptr, row_pointers);

			// It is REQUIRED to call this to finish writing the rest of the file
			// Bug with png_flush
			png_write_end(png_ptr, info_ptr);

			// clean up after the write, and free any memory allocated
			png_destroy_write_struct(&png_ptr, &info_ptr);

			free(row_pointers);

			if(palette)  {
				png_free(png_ptr, palette);
			}

			return TRUE;

		} catch (char *text) {
			if (FreeImage_OutputMessage) {
				FreeImage_OutputMessage(FIF_PNG, text);
			}

			return FALSE;
		}
	}

	return FALSE;
}

#endif
