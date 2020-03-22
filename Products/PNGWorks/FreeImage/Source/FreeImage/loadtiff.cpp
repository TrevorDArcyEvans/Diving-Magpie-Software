// ==========================================================
// TIFF Loader and Writer
//
// Design and implementation by 
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@iut.univ-lehavre.fr)
// - Markus Loibl (markus.loibl@epost.de)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include "..\LibTIFF\tiffiop.h"

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef TIFF_ENABLED

static FreeImageIO *g_io;

// ----------------------------------------------------------
//   libtiff interface 
// ----------------------------------------------------------

static tsize_t 
_tiffReadProc(thandle_t file, tdata_t buf, tsize_t size) {
	return g_io->read_proc(buf, size, 1, (fi_handle)file) * size;
}

static tsize_t
_tiffWriteProc(thandle_t file, tdata_t buf, tsize_t size) {
	return g_io->write_proc(buf, size, 1, (fi_handle)file) * size;
}

static toff_t
_tiffSeekProc(thandle_t file, toff_t off, int whence) {
	g_io->seek_proc((fi_handle)file, off, whence);
	return g_io->tell_proc((fi_handle)file);
}

static int
_tiffCloseProc(thandle_t fd) {
	return 0;
}

#include <sys/stat.h>

static toff_t
_tiffSizeProc(thandle_t file) {
	struct stat sb;
	return (fstat((int) file, &sb) < 0 ? 0 : sb.st_size);
}

static int
_tiffMapProc(thandle_t fd, tdata_t* pbase, toff_t* psize) {
	return 0;
}

static void
_tiffUnmapProc(thandle_t fd, tdata_t base, toff_t size) {
}

// ----------------------------------------------------------
//   Open a TIFF file descriptor for read/writing.
// ----------------------------------------------------------

TIFF*
TIFFFdOpen(thandle_t handle, const char *name, const char *mode) {
	TIFF *tif;

	tif = TIFFClientOpen(name, mode, (thandle_t) handle,
	    _tiffReadProc, _tiffWriteProc, _tiffSeekProc, _tiffCloseProc,
	    _tiffSizeProc, _tiffMapProc, _tiffUnmapProc);

	if (tif) {
		tif->tif_fd = (int)handle;
	}

	return tif;
}

// ----------------------------------------------------------
//   Open a TIFF file for read/writing.
// ----------------------------------------------------------

TIFF*
TIFFOpen(const char* name, const char* mode) {
	return 0;
}

tdata_t
_TIFFmalloc(tsize_t s) {
	return malloc(s);
}

void
_TIFFfree(tdata_t p) {
	free(p);
}

tdata_t
_TIFFrealloc(tdata_t p, tsize_t s) {
	return realloc(p, s);
}

void
_TIFFmemset(tdata_t p, int v, tsize_t c) {
	memset(p, v, (size_t) c);
}

void
_TIFFmemcpy(tdata_t d, const tdata_t s, tsize_t c) {
	memcpy(d, s, (size_t) c);
}

int
_TIFFmemcmp(const tdata_t p1, const tdata_t p2, tsize_t c) {
	return (memcmp(p1, p2, (size_t) c));
}

// ----------------------------------------------------------
//   in FreeImage warnings and errors are disabled
// ----------------------------------------------------------

static void
msdosWarningHandler(const char* module, const char* fmt, va_list ap) {
}

TIFFErrorHandler _TIFFwarningHandler = msdosWarningHandler;

static void
msdosErrorHandler(const char* module, const char* fmt, va_list ap) {
}

TIFFErrorHandler _TIFFerrorHandler = msdosErrorHandler;

// ----------------------------------------------------------

#define CVT(x)      (((x) * 255L) / ((1L<<16)-1))
#define	SCALE(x)	(((x)*((1L<<16)-1))/255)

// ----------------------------------------------------------

static uint16
CheckColormap(int n, uint16* r, uint16* g, uint16* b) {
    while (n-- > 0) {
        if (*r++ >= 256 || *g++ >= 256 || *b++ >= 256) {
			return 16;
		}
	}

    return 8;
}

static uint16
CheckPhotometric(void *dib, uint16 bitspersample) {
	RGBQUAD *rgb;
	uint16 i;

	switch(bitspersample) {
		case 1:
		{
			rgb = FreeImage_GetPalette(dib);

			if ((rgb->rgbRed == 0) && (rgb->rgbGreen == 0) && (rgb->rgbBlue == 0)) {
				return PHOTOMETRIC_MINISBLACK;
			} else {
				return PHOTOMETRIC_MINISWHITE;
			}			
		}

		case 4:	// Check if the DIB has a color or a greyscale palette
		case 8:
			rgb = FreeImage_GetPalette(dib);

			for (i = 0; i < FreeImage_GetColorsUsed(dib); i++) {
				if ((rgb->rgbRed != rgb->rgbGreen) || (rgb->rgbRed != rgb->rgbBlue)) {
					return PHOTOMETRIC_PALETTE;
				}
				// The DIB has a color palette if the greyscale isn't a linear ramp
				if (rgb->rgbRed != i) {
					return PHOTOMETRIC_PALETTE;
				}

				rgb++;
			}

			return PHOTOMETRIC_MINISBLACK;
			
		case 24:
			return PHOTOMETRIC_RGB;			
	}

	return PHOTOMETRIC_MINISBLACK;
}

// ----------------------------------------------------------
//   TIFF Loading
// ----------------------------------------------------------

void *
FreeImage_LoadTIFF(const char *filename, TIFFFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadTIFFFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadTIFFFromHandle(FreeImageIO *io, fi_handle handle, TIFFFlags flags) {
	g_io = io;

    TIFF   *tif;
    uint32 height; 
    uint32 width; 
    uint16 bitspersample;
    uint16 samplesperpixel;
    uint32 rowsperstrip;  
    uint16 photometric;
	uint16 compression;
	uint32 x, y;
	bool isRGB;

    int32 nrow;
    BYTE *buf;          
    BYTE *dib;
    BYTE *bits;		// pointer to dib data
	RGBQUAD *pal;	// pointer to dib palette
    
	if (handle) {
		try {
			tif = TIFFFdOpen((thandle_t)handle, "", "r");
    
			if (!tif || !TIFFSetDirectory(tif, static_cast<int>(flags)))
				throw "Error encountered while opening TIFF file";			

			TIFFGetField(tif, TIFFTAG_COMPRESSION, &compression);

			if (compression == COMPRESSION_LZW)
				throw "LZW compression is no longer supported due to Unisys patent enforcement";			

			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
			TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
			TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitspersample);
			TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);   
			TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photometric);

			// Convert to 24 bits RGB if the image is full color

			isRGB = (bitspersample >= 8) &&
				(photometric == PHOTOMETRIC_RGB) ||
				(photometric == PHOTOMETRIC_YCBCR) ||
				(photometric == PHOTOMETRIC_SEPARATED) ||
				(photometric == PHOTOMETRIC_LOGLUV);

			if (isRGB) {
				// Read the whole image into one big RGBA buffer and then 
				// convert it to a DIB. This is using the traditional
				// TIFFReadRGBAImage() API that we trust.

				uint32* raster;		// retrieve RGBA image
				uint32 *row;

				raster = (uint32*)_TIFFmalloc(width * height * sizeof (uint32));

				if (raster == NULL) {
					throw "No space for raster buffer";
				}
				
				// Read the image in one chunk into an RGBA array

				if(!TIFFReadRGBAImage(tif, width, height, raster, 0)) {
					_TIFFfree(raster);
					return NULL;
				}

				// create a new DIB

				dib = (BYTE *)FreeImage_Allocate(width, height, 24);

				if (dib == NULL) {
					_TIFFfree(raster);

					throw "DIB allocation failed";
				}
				
				float	fResX, fResY;
				uint16	resUnit;
				TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &resUnit);
				TIFFGetField(tif, TIFFTAG_XRESOLUTION, &fResX);
				TIFFGetField(tif, TIFFTAG_YRESOLUTION, &fResY);

				BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);

				if (resUnit == RESUNIT_INCH) {
					/* english */

					pInfoHeader->biXPelsPerMeter = (int) (fResX/0.0254000 + 0.5);
					pInfoHeader->biYPelsPerMeter = (int) (fResY/0.0254000 + 0.5);
				} else if(resUnit== RESUNIT_CENTIMETER) {
					/* metric */

					pInfoHeader->biXPelsPerMeter = (int) (fResX*100.0 + 0.5);
					pInfoHeader->biYPelsPerMeter = (int) (fResY*100.0 + 0.5);
				}

				// read the raster lines and save them in the DIB
				// with RGB mode, we have to change the order of the 3 samples RGB
				// We use macros for extracting components from the packed ABGR 
				// form returned by TIFFReadRGBAImage.

				row = &raster[0];

				for(y = 0; y < height; y++) {
					bits = FreeImage_GetScanLine(dib, y);

					for (x = 0; x < width; x++) {
						bits[0] = (BYTE)TIFFGetB(row[x]);
						bits[1] = (BYTE)TIFFGetG(row[x]);
						bits[2] = (BYTE)TIFFGetR(row[x]);

						bits += 3;
					}

					row += width;
				}

				_TIFFfree(raster);

				return (void *)dib;
			} else {
				// calculate the line + pitch

				int line = CalculateLine(width, bitspersample * samplesperpixel);
				int pitch = CalculatePitch(line);

				// create a new DIB

				dib = (BYTE *)FreeImage_Allocate(width, height, bitspersample * samplesperpixel);

				if (dib == NULL) {
					throw "No space for DIB image";
				}

				float	fResX, fResY;
				uint16	resUnit;
				TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &resUnit);
				TIFFGetField(tif, TIFFTAG_XRESOLUTION, &fResX);
				TIFFGetField(tif, TIFFTAG_YRESOLUTION, &fResY);

				BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);

				if (resUnit == RESUNIT_INCH) {
					/* english */

					pInfoHeader->biXPelsPerMeter = (int) (fResX/0.0254000 + 0.5);
					pInfoHeader->biYPelsPerMeter = (int) (fResY/0.0254000 + 0.5);
				} else if(resUnit== RESUNIT_CENTIMETER) {
					/* metric */

					pInfoHeader->biXPelsPerMeter = (int) (fResX*100.0 + 0.5);
					pInfoHeader->biYPelsPerMeter = (int) (fResY*100.0 + 0.5);
				}

				// In the tiff file the lines are save from up to down 
				// In a DIB the lines must be save from down to up

				bits = FreeImage_GetBits(dib) + height * pitch;

				// now lpBits pointe on the bottom line

				// set up the colormap based on photometric	

				pal = FreeImage_GetPalette(dib);

				switch(photometric) {
					case PHOTOMETRIC_MINISBLACK:	// bitmap and greyscale image types
					case PHOTOMETRIC_MINISWHITE:

						// Monochrome image

						if(bitspersample == 1) {
							if(photometric == PHOTOMETRIC_MINISBLACK) {
								pal[0].rgbRed = 0;
								pal[0].rgbGreen = 0;
								pal[0].rgbBlue = 0;
								pal[1].rgbRed = 255;
								pal[1].rgbGreen = 255;
								pal[1].rgbBlue = 255;
							} else {
								pal[0].rgbRed = 255;
								pal[0].rgbGreen = 255;
								pal[0].rgbBlue = 255;
								pal[1].rgbRed = 0;
								pal[1].rgbGreen = 0;
								pal[1].rgbBlue = 0;
							}
						} else {
							// need to build the scale for greyscale images

							for(int i = 0; i < 256; i++) {
								pal[i].rgbRed	= i;
								pal[i].rgbGreen = i;
								pal[i].rgbBlue	= i;
							}
						}

						break;

					case PHOTOMETRIC_PALETTE:	// color map indexed
						uint16 *red;
						uint16 *green;
						uint16 *blue;
						bool Palette16Bits;
						
						TIFFGetField(tif, TIFFTAG_COLORMAP, &red, &green, &blue); 

						// Is the palette 16 or 8 bits ?

						if (CheckColormap(1<<bitspersample, red, green, blue) == 16)  {
							Palette16Bits = TRUE;
						} else {
							Palette16Bits = FALSE;
						}

						// load the palette in the DIB

						for (int i = (1 << bitspersample) - 1; i >= 0; i--) {
							if (Palette16Bits) {
								pal[i].rgbRed =(BYTE) CVT(red[i]);
								pal[i].rgbGreen = (BYTE) CVT(green[i]);
								pal[i].rgbBlue = (BYTE) CVT(blue[i]);           
							} else {
								pal[i].rgbRed = (BYTE) red[i];
								pal[i].rgbGreen = (BYTE) green[i];
								pal[i].rgbBlue = (BYTE) blue[i];        
							}
						}

						break;
					
				}

				// read the tiff lines and save them in the DIB

				buf = new BYTE[TIFFStripSize(tif)];

				for (y = 0; y < height; y += rowsperstrip) {
					nrow = (y + rowsperstrip > height ? height - y : rowsperstrip);

					if (TIFFReadEncodedStrip(tif, TIFFComputeStrip(tif, y, 0), buf, nrow * line) == -1) {
						delete [] buf;

						return NULL;
					} else {
						for (int l = 0; l < nrow; l++) {
							bits -= pitch;

							memcpy(bits, buf + l * line, line);
						}
					}
				}
				
				delete [] buf;

				return (void *)dib;

			}

		} catch (char *text) {
			if (FreeImage_OutputMessage)
				FreeImage_OutputMessage(FIF_TIFF, text);

			return NULL;
		}
	}

	return NULL;	   
}

// ----------------------------------------------------------
//   TIFF Saving
// ----------------------------------------------------------

BOOL
FreeImage_SaveTIFF(void *dib, const char *filename, TIFFFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "wb");
	
	if (handle) {
		BOOL success = FreeImage_SaveTIFFToHandle(dib, &io, (fi_handle)handle, flags);

		fclose(handle);

		return success;
	}

	return FALSE;
}

// ----------------------------------------------------------

BOOL
FreeImage_SaveTIFFToHandle(void *dib, FreeImageIO *io, fi_handle handle, TIFFFlags flags) {
	g_io = io;

    TIFF   *out;
    uint32 height; 
    uint32 width; 
	uint32 rowsperstrip = (uint32) -1;
    uint16 bitspersample;
    uint16 samplesperpixel;
    uint16 photometric;
	uint16 compression;

	uint32 x, y;
	tsize_t linebytes;
	uint8 *buf;

	BYTE *bits, *lpBits;	// pointers to dib data
	uint16 pitch;
  
	if((dib) && (handle)) {
		try {
			out = TIFFFdOpen((thandle_t)handle, "", "w");
    
			if (out == NULL) {
				return FALSE;			
			}

			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			bitspersample = FreeImage_GetBPP(dib);
			samplesperpixel = (bitspersample == 24) ? 3 : 1;
			photometric = CheckPhotometric(dib, bitspersample);

			// handle standard width/height/bpp stuff

			TIFFSetField(out, TIFFTAG_IMAGEWIDTH, width);
			TIFFSetField(out, TIFFTAG_IMAGELENGTH, height);
			TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesperpixel);
			TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, bitspersample / samplesperpixel);
			TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photometric);
			TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);	// single image plane 
			TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
			TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, rowsperstrip));

			// handle metrics

			BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);
			TIFFSetField(out, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
			TIFFSetField(out, TIFFTAG_XRESOLUTION, 0.0254*((float)pInfoHeader->biXPelsPerMeter));
			TIFFSetField(out, TIFFTAG_YRESOLUTION, 0.0254*((float)pInfoHeader->biYPelsPerMeter));

			if (photometric == PHOTOMETRIC_PALETTE) {
				// Palette image colormaps are automatically scaled to 16-bits. 

				uint16 *r, *g, *b;
				RGBQUAD *pal = FreeImage_GetPalette(dib);
				uint16 nColors = FreeImage_GetColorsUsed(dib);

				r = (uint16 *) _TIFFmalloc(sizeof(uint16) * 3 * nColors);
				g = r + nColors;
				b = g + nColors;

				for (int i = nColors-1; i >= 0; i--) {
					r[i] = SCALE( (uint16)pal[i].rgbRed );
					g[i] = SCALE( (uint16)pal[i].rgbGreen );
					b[i] = SCALE( (uint16)pal[i].rgbBlue );
				}

				TIFFSetField(out, TIFFTAG_COLORMAP, r, g, b);

				_TIFFfree(r);
			}

			switch(bitspersample) {
				case 1 :
					compression = COMPRESSION_CCITTFAX4;
					break;

				case 8 :
				case 24 :
					compression = COMPRESSION_PACKBITS;
					break;

				default :
					compression = COMPRESSION_NONE;
					break;
			}

			TIFFSetField(out, TIFFTAG_COMPRESSION, compression);

			linebytes = width * samplesperpixel;

			if (TIFFScanlineSize(out) > linebytes) {
				linebytes = TIFFScanlineSize(out);
			}

			buf = (uint8 *)_TIFFmalloc(linebytes);	

			// read the DIB lines from bottom to top
			// and save them in the TIF
			// -------------------------------------
			
			lpBits = FreeImage_GetBits(dib);
			pitch = FreeImage_GetPitch(dib);
			
			switch(bitspersample) {				
				case 1 :
				case 4 :
				case 8 :
				{
					for (y = 0; y < height; y++) {
						bits = lpBits + (pitch * (height-1-y));
						_TIFFmemcpy(buf, bits, linebytes);
						TIFFWriteScanline(out, buf, y, 0);
					}

					break;
				}				

				case 24 :
				{
					uint8 *pBuf;

					for (y = 0; y < height; y++) {
						bits = lpBits + (pitch * (height-1-y));
						pBuf = buf;

						for (x = 0; x < width; x++) {
							pBuf[0] = bits[2];
							pBuf[1] = bits[1];
							pBuf[2] = bits[0];
							pBuf += 3; bits += 3;
						}

						TIFFWriteScanline(out, buf, y, 0);
					}

					break;
				}				
			}

			_TIFFfree(buf);

		} catch (char *text) {
			if (FreeImage_OutputMessage) {
				FreeImage_OutputMessage(FIF_TIFF, text);
			}

			return FALSE;
		}
	}

	TIFFClose(out);

	return TRUE; 
}

#endif
