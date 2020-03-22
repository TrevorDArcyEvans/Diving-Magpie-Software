// ==========================================================
// PCX Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Jani Kajala (janik@remedy.fi)
// - Markus Loibl (markus.loibl@epost.de)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <assert.h>

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

static BYTE s_nibble;
static BOOL s_high_nibble = FALSE;

// ----------------------------------------------------------

#ifdef PCX_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

#pragma pack(push, 1)

struct tagPCXHEADER {
	BYTE  manufacturer;
	BYTE  version;
	BYTE  encoding;
	BYTE  bpp;
	WORD  window[4];
	WORD  hdpi;
	WORD  vdpi;
	BYTE  color_map[48];
	BYTE  reserved;
	BYTE  planes;
	WORD  bytes_per_line;
	WORD  palette_info;
	WORD  h_screen_size;
	WORD  v_screen_size;
	BYTE  filler[54];
};
		
#pragma pack(pop)

// ----------------------------------------------------------

BYTE
GetNibble(FreeImageIO *io, fi_handle handle) {
	BYTE n;

	if (s_high_nibble) {
		n = HINIBBLE(s_nibble) >> 4;

		io->read_proc(&s_nibble, 1, 1, handle);
	} else {
		n = LOWNIBBLE(s_nibble);
	}

	s_high_nibble = !s_high_nibble;

	return n;
}

// ----------------------------------------------------------
//   PCX Loading
// ----------------------------------------------------------

void *
FreeImage_LoadPCX(const char *filename, PCXFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadPCXFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadPCXFromHandle(FreeImageIO *io, fi_handle handle, PCXFlags flags) {
	if (handle) {

		// process the header

		tagPCXHEADER pcx_header;

		io->read_proc(&pcx_header, sizeof(tagPCXHEADER), 1, handle);

		if (pcx_header.manufacturer == 10) {
			int width = pcx_header.window[2] - pcx_header.window[0] + 1;
			int height = pcx_header.window[3] - pcx_header.window[1] + 1;
			int bitcount = pcx_header.bpp * pcx_header.planes;
		
			int line = pcx_header.bytes_per_line * pcx_header.planes;
			int pitch = CalculatePitch(line);
			
			if (bitcount == 8) {
				
				// calculate how much memory we need to store the bitmap and then allocate it

				BYTE *dib = (BYTE *)FreeImage_Allocate(width, height, bitcount);				

				// metrics handling code

				BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);
				pInfoHeader->biXPelsPerMeter = (int) (((float)pcx_header.hdpi) / 0.0254000 + 0.5);
				pInfoHeader->biYPelsPerMeter = (int) (((float)pcx_header.vdpi) / 0.0254000 + 0.5);
				
				// load the bitmap data

				for (int i = 0; i < height; i++) {

					// -----------------------------------------------------------//
					//       THIS IS HOW RUNTIME LENGTH ENCODING WORKS IN PCX:    //
					//                                                            //
					//  1) If the upper 2 bits of a byte are set,                 //
					//     the lower 6 bits specify the count for the next byte   //
					//                                                            //
					//  2) If the upper 2 bits of the byte are clear,             //
					//     the byte is actual data with a count of 1              //
					//                                                            //
					//  Note that a scanline always has an even number of bytes   //
					// -------------------------------------------------------------
						
					BYTE rle;

					int written = 0;
					
					while (written < width) {						
						io->read_proc(&rle, sizeof(BYTE), 1, handle);

						if ((rle & 0xC0) == 0xC0) {
							int count = rle & 0x3F;

							io->read_proc(&rle, sizeof(BYTE), 1, handle);

							for (int c = 0; c < count; c++) {
								*(FreeImage_GetScanLine(dib, height - i - 1) + written++) = rle;
							}							
						} else {
							*(FreeImage_GetScanLine(dib, height - i - 1) + written++) = rle;
						}						
					}

					// skip trailing garbage at the end of the scanline
					
					for (int count = written; count < pcx_header.bytes_per_line; count++) {
						io->read_proc(&rle, sizeof(BYTE), 1, handle);
					}
				}
  			
				// load the palette

				BYTE palette_id;

				io->read_proc(&palette_id, sizeof(BYTE), 1, handle);

				if (palette_id == 12) {
					RGBQUAD *quad = FreeImage_GetPalette(dib);
					
					for (int i = 0; i < 256; i++) {
						io->read_proc(&quad[i].rgbRed, 1, 1, handle);						
						io->read_proc(&quad[i].rgbGreen, 1, 1, handle);
						io->read_proc(&quad[i].rgbBlue, 1, 1, handle);						
					}
				}				
			
				return (void *)dib;
			}
		
			if (bitcount == 24) {
				// calculate how much memory we need to store the bitmap and then allocate it

				int scanline = height;

				// allocate temporary buffer for a single line

				BYTE *dib = (BYTE *)FreeImage_Allocate(width, height, bitcount);

				// metrics handling code

				BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);
				pInfoHeader->biXPelsPerMeter = (int) (((float)pcx_header.hdpi) / 0.0254000 + 0.5);
				pInfoHeader->biYPelsPerMeter = (int) (((float)pcx_header.vdpi) / 0.0254000 + 0.5);

				// decompress the rle'ed scanlines

				BYTE *line_buff = new BYTE[pitch * 2];

				for (int i = 0; i < height; i++) {
					scanline--;
					
					BYTE rle;
					int written = 0;

					// read single scanline 

					while (written < line) {
						io->read_proc(&rle, sizeof(BYTE), 1, handle);

						if ((rle & 0xC0) == 0xC0) {
							BYTE pixel;

							io->read_proc(&pixel, sizeof(BYTE), 1, handle);

							for (int c = 0; c < (rle & 0x3F); c++) {
//								assert(written < pitch);

								line_buff[written++] = pixel;
							}							
						} else {
							assert(written < pitch);

							line_buff[written++] = rle;
						}
					}	

					// convert the plane stream to RGB (RRRRGGGGBBBB -> RGBRGBRGBRGB)

					int src = 0;
					int plane;

					for (plane = pcx_header.planes - 1; plane >= 0; --plane) {
						int written = plane;
						int plane_end = src + width;

						for (; src < plane_end ; ++src) {
							assert(written < pitch);

							*(FreeImage_GetScanLine(dib, scanline) + written) = line_buff[src];

							written += pcx_header.planes;
						}
					}
				}

				delete[] line_buff;

				return (void *)dib;
			}
		}
	}

	return NULL;
}

#endif
