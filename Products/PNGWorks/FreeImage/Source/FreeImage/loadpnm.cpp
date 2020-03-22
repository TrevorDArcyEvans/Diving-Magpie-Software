// ==========================================================
// PNM (PPM, PGM, PBM) Loader and Writer
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@infonie.fr)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <stdio.h>		// for sprintf()
#include <string.h>

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef PNM_ENABLED

// ----------------------------------------------------------

static int GetInt(FreeImageIO *io, fi_handle handle) {
	// get an integer value from the actual position pointed by handle

    char c = 0;
	BOOL firstchar;

    // skip forward to start of next number

    io->read_proc(&c, 1, 1, handle);

    while (1) {
        // eat comments

        if (c == '#') {
			// if we're at a comment, read to end of line

            firstchar = TRUE;

            while (1) {
				io->read_proc(&c, 1, 1, handle);

				if (firstchar && c == ' ') {
					// loop off 1 sp after #

					firstchar = FALSE;
				} else if(c == '\n') {
					break;
				}
			}
		}

        if (c >= '0' && c <='9') {
			// we've found what we were looking for

            break;
		}

        io->read_proc(&c, 1, 1, handle);
    }

    // we're at the start of a number, continue until we hit a non-number

    int i = 0;

    while (1) {
        i = (i*10) + (c - '0');

        io->read_proc(&c, 1, 1, handle);

        if (c < '0' || c > '9')
            break;
    }

    return i;
}

// ----------------------------------------------------------
//   PNM Loading
// ----------------------------------------------------------

void *
FreeImage_LoadPNM(const char *filename, PNMFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadPNMFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadPNMFromHandle(FreeImageIO *io, fi_handle handle, PNMFlags flags) {
	char id_one, id_two;
	WORD x, y;
	BYTE *dib;
    BYTE *bits;		// pointer to dib data
	RGBQUAD *pal;	// pointer to dib palette
	int i, max, level;

	if(!handle)
		return NULL;

	try {
		// Read the first two bytes of the file to determine the file format
		// "P1" = ascii bitmap, "P2" = ascii greymap, "P3" = ascii pixmap,
		// "P4" = raw bitmap, "P5" = raw greymap, "P6" = raw pixmap

		io->read_proc(&id_one, 1, 1, handle);
		io->read_proc(&id_two, 1, 1, handle);

		if (id_one != 'P' || id_two < '1' || id_two > '6') {
			throw "Invalid magic number";
		}

		// Read the header information

		int width  = GetInt(io, handle);
		int height = GetInt(io, handle);

		// Create a new DIB

		switch(id_two)  {
			case '1':
			case '4':
				dib = (BYTE *)FreeImage_Allocate(width, height, 1);
				break;

			case '2':
			case '5':
				dib = (BYTE *)FreeImage_Allocate(width, height, 8);
				break;

			case '3':
			case '6':
				dib = (BYTE *)FreeImage_Allocate(width, height, 24);
				break;
		}

		if(!dib)
			throw "DIB allocation failed";

		// Read the image...

		int pitch = FreeImage_GetPitch(dib);

		switch(id_two)  {
			case '1':
			case '4':
				// write the palette data

				pal = FreeImage_GetPalette(dib);
				pal[0].rgbRed = pal[0].rgbGreen = pal[0].rgbBlue = 0;
				pal[1].rgbRed = pal[1].rgbGreen = pal[1].rgbBlue = 255;

				// write the bitmap data

				if (id_two == '1') {	// ASCII bitmap
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < width; x++) {
							if (GetInt(io, handle) == 0)
								bits[x >> 3] |= (0x80 >> (x & 0x7));
							else
								bits[x >> 3] &= (0xFF7F >> (x & 0x7));
						}
					}
				}  else {		// Raw bitmap
					int line   = CalculateLine(width, 1);
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < line; x++) {
							io->read_proc(&bits[x], 1, 1, handle);
							bits[x] = ~bits[x];
						}
					}
				}
				return (void*)dib;
				break;

			case '2':
			case '5':
				// Build a greyscale palette
				
				pal = FreeImage_GetPalette(dib);
				for(i = 0; i < 256; i++) {
					pal[i].rgbRed	= i;
					pal[i].rgbGreen = i;
					pal[i].rgbBlue	= i;
				}

				max = GetInt(io, handle);	// read the 'max' value

				// write the bitmap data

				if(id_two == '2') {		// ASCII greymap
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < width; x++) {
							level = GetInt(io, handle);
							bits[x] = (BYTE)((255 * level) / max);
						}
					}
				} else {		// Raw greymap
					level = 0;
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < width; x++) {
							io->read_proc(&level, 1, 1, handle);
							bits[x] = (BYTE)((255 * level) / max);
						}
					}
				}
				return (void*)dib;
				break;

			case '3':
			case '6':
				max = GetInt(io, handle);	// read the 'max' value

				// write the bitmap data

				if (id_two == '3') {		// ASCII pixmap
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < width; x++) {
							bits[2] = (BYTE)((255 * GetInt(io, handle)) / max);	// R
							bits[1] = (BYTE)((255 * GetInt(io, handle)) / max);	// G
							bits[0] = (BYTE)((255 * GetInt(io, handle)) / max);	// B
							bits += 3;
						}
					}
				}  else {			// Raw pixmap
					level = 0;
					for (y = 0; y < height; y++) {				
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for (x = 0; x < width; x++) {
							io->read_proc(&level, 1, 1, handle); 
							bits[2] = (BYTE)((255 * level) / max);	// R
							io->read_proc(&level, 1, 1, handle);
							bits[1] = (BYTE)((255 * level) / max);	// G
							io->read_proc(&level, 1, 1, handle);
							bits[0] = (BYTE)((255 * level) / max);	// B
							bits += 3;
						}
					}
				}
				return (void*)dib;
				break;
		}

	} catch(char *text)  {
			if (FreeImage_OutputMessage) {
				switch(id_two)  {
					case '1':
					case '4':
						FreeImage_OutputMessage(FIF_PBM, text);
						break;
					case '2':
					case '5':
						FreeImage_OutputMessage(FIF_PGM, text);
						break;
					case '3':
					case '6':
						FreeImage_OutputMessage(FIF_PPM, text);
						break;
				}
			}
			return NULL;
	}
		
	return NULL;
}

// ----------------------------------------------------------
//   PNM Saving
// ----------------------------------------------------------
//
// Output format :
//
// Bit depth		flags			file format
// -------------    --------------  -----------
// 1-bit / pixel	PNM_SAVE_ASCII	PBM (P1)
// 1-bit / pixel	PNM_SAVE_RAW	PBM (P4)
// 8-bit / pixel	PNM_SAVE_ASCII	PGM (P2)
// 8-bit / pixel	PNM_SAVE_RAW	PGM (P5)
// 24-bit / pixel	PNM_SAVE_ASCII	PPM (P3)
// 24-bit / pixel	PNM_SAVE_RAW	PPM (P6)
// ----------------------------------------------------------

BOOL
FreeImage_SavePNM(void *dib, const char *filename, PNMFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "wb");
	
	if (handle) {
		BOOL success = FreeImage_SavePNMToHandle(dib, &io, (fi_handle)handle, flags);

		fclose(handle);

		return success;
	}

	return FALSE;
}

// ----------------------------------------------------------

BOOL
FreeImage_SavePNMToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNMFlags flags) {
    int magic, bpp;
	WORD x, y, width, height;
    BYTE *bits;		// pointer to dib data
	char buffer[20];

	
	if((dib) && (handle)) {
		bpp = FreeImage_GetBPP(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		// Find the appropriate magic number for this file type
		magic = 0;
		switch(bpp)
		{
			case 1:
				magic = 1;	// PBM file (B & W)
				break;
			case 8:			
				magic = 2;	// PGM file	(Greyscale)
				break;
			case 24:
				magic = 3;	// PPM file (RGB)
				break;
			default:
				return FALSE;	// Invalid bit depth
		}
		if(flags == PNM_SAVE_RAW)
			magic += 3;

		// Write the header info

		sprintf(buffer, "P%d\n%d %d\n", magic, width, height);
		io->write_proc(&buffer, strlen(buffer), 1, handle);
		if( bpp != 1) {
			sprintf(buffer, "255\n");
			io->write_proc(&buffer, strlen(buffer), 1, handle);
		}

		// Write the image data
		///////////////////////

		int pitch = FreeImage_GetPitch(dib);

		switch(bpp)  {
			case 24:            // 24-bit RGB, 3 bytes per pixel
			{
				if(flags == PNM_SAVE_RAW)  {						
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < width; x++) {
							io->write_proc(&bits[2], 1, 1, handle);	// R
							io->write_proc(&bits[1], 1, 1, handle);	// G
							io->write_proc(&bits[0], 1, 1, handle);	// B
							bits += 3;
						}
					}
				}
				else {
					int length = 0;
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < width; x++) {
							sprintf(buffer, "%3d %3d %3d ", bits[2], bits[1], bits[0]);
							io->write_proc(&buffer, strlen(buffer), 1, handle);
							length += 12;
							if(length > 58)
							{
								sprintf(buffer, "\n");
								io->write_proc(&buffer, strlen(buffer), 1, handle);
								length = 0;
							}
							bits += 3;
						}
					}
				}
			}
			break;

			case 8:				// 8-bit greyscale
			{
				if(flags == PNM_SAVE_RAW)  {
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < width; x++) {
							io->write_proc(&bits[x], 1, 1, handle);
						}
					}
				}
				else {
					int length = 0;
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < width; x++) {
							sprintf(buffer, "%3d ", bits[x]);
							io->write_proc(&buffer, strlen(buffer), 1, handle);
							length += 4;
							if(length > 66)	{
								sprintf(buffer, "\n");
								io->write_proc(&buffer, strlen(buffer), 1, handle);
								length = 0;
							}
						}
					}
				}
			}
			break;

			case 1:				// 1-bit B & W
			{
				RGBQUAD *pal = FreeImage_GetPalette(dib);
				int color;

				if(flags == PNM_SAVE_RAW)  {
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < FreeImage_GetLine(dib); x++)
							io->write_proc(&bits[x], 1, 1, handle);
					}
				}
				else  {
					int length = 0;
					for(y = 0; y < height; y++) {
						bits = FreeImage_GetBits(dib) + (height - 1 - y) * pitch;
						for(x = 0; x < FreeImage_GetLine(dib) * 8; x++)	{
							color = (bits[x>>3] & (0x80 >> (x & 0x07))) != 0;
							sprintf(buffer, "%c ", color ? '1':'0');
							io->write_proc(&buffer, strlen(buffer), 1, handle);
							length += 2;

							if(length > 68) {
								sprintf(buffer, "\n");
								io->write_proc(&buffer, strlen(buffer), 1, handle);
								length = 0;
							}
						}
					}
				}
			}
			break;
		}

		return TRUE;
	}

	return FALSE;
}

#endif
