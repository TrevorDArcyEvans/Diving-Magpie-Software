// ==========================================================
// TARGA Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Jani Kajala (janik@remedy.fi)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef TARGA_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

#pragma pack(push, 1)

typedef struct tagRGBTRIPLE { 
  BYTE rgbtBlue; 
  BYTE rgbtGreen; 
  BYTE rgbtRed; 
} RGBTRIPLE; 

struct tagTGAHEADER {
	BYTE id_length;
	BYTE color_map_type;
	BYTE image_type;

	WORD cm_first_entry;
	WORD cm_length;
	BYTE cm_size;

	WORD is_xorigin;
	WORD is_yorigin;
	WORD is_width;
	WORD is_height;
	BYTE is_pixel_depth;
	BYTE is_image_descriptor;
};

#pragma pack(pop)

// ----------------------------------------------------------
//   TARGA Loading
// ----------------------------------------------------------

void *
FreeImage_LoadTARGA(const char *filename, TARGAFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadTARGAFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadTARGAFromHandle(FreeImageIO *io, fi_handle handle, TARGAFlags flags) {
	if (handle) {
		try {
			BYTE *dib = NULL;
			tagTGAHEADER header;

			io->read_proc(&header, sizeof(tagTGAHEADER), 1, handle);

			int line = CalculateLine(header.is_width, header.is_pixel_depth);
			int pitch = CalculatePitch(line);

			switch (header.is_pixel_depth) {
				case 8 :
				{
					dib = (BYTE *)FreeImage_Allocate(header.is_width, header.is_height, 8);

					if (dib == NULL) {
						throw "DIB allocation failed";
					}

					// read the palette

					RGBQUAD *palette = FreeImage_GetPalette(dib);

					for (unsigned count = header.cm_first_entry; count < 256; count++) {
						RGBTRIPLE triple;

						io->read_proc(&triple, sizeof(RGBTRIPLE), 1, handle);
						
						palette[count].rgbRed = triple.rgbtRed;
						palette[count].rgbGreen = triple.rgbtGreen;
						palette[count].rgbBlue = triple.rgbtBlue;
					}
					
					// read in the bitmap bits

					switch (header.image_type) {
						case 1 :
						{
							for (count = 0; count < header.is_height; count++)
								io->read_proc(FreeImage_GetScanLine(dib, count), line, 1, handle);
							
							break;
						}

						case 9 :
						{
							int x = 0;
							int y = 0;
							BYTE rle;
							BYTE pixel;
							
							while(1) {
								io->read_proc(&rle,1, 1, handle);
								
								if (rle > 127) {
									rle -= 127;

									io->read_proc(&pixel, 1, 1, handle);

									for (int ix = 0; ix < rle; ix++) {
										BYTE *bits = FreeImage_GetScanLine(dib, y);

										bits[x++] = pixel;

										if (x >= header.is_width) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done1;																
										}
									}
								} else {
									rle++;

									for (int ix = 0; ix < rle; ix++) {
										BYTE *bits = FreeImage_GetScanLine(dib, y);

										io->read_proc(&pixel, 1, 1, handle);

										bits[x++] = pixel;

										if (x >= header.is_width) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done1;																
										}
									}
								}
							}
						done1:
							break;
						}		
						
						default :
							FreeImage_Free(dib);
							return NULL;
					}

					break;
				}

				case 16 :
				{
					// load native 16bit format if requested

					int pixel_bits;

					if (TARGA_LOAD_RGB555 & flags)
						pixel_bits = 16;
					else
						pixel_bits = 24;					

					// allocate the dib

					int line = CalculateLine(header.is_width, pixel_bits);
					int pitch = CalculatePitch(line);
					const unsigned pixel_size = unsigned(pixel_bits) / 8;

					dib = (BYTE *)FreeImage_Allocate(header.is_width, header.is_height, pixel_bits);

					if (dib == 0)
						throw "DIB allocation failed";					

					// read in the bitmap bits

					WORD pixel;
							
					switch (header.image_type) {
						case 2 :
						{
							for (int y = 0; y < header.is_height; y++) {
								BYTE *bits = FreeImage_GetScanLine(dib, y);

								for (int x = 0; x < line; ) {
									io->read_proc(&pixel, sizeof(WORD), 1, handle);
								
									if (TARGA_LOAD_RGB555 & flags) {
										*reinterpret_cast<WORD*>(bits + x) = 0x7FFF & pixel;
									} else {
										bits[x + 0] = (pixel & 0x001f) << 3;
										bits[x + 1] = (pixel & 0x03e0) >> 2;
										bits[x + 2] = (pixel & 0x7c00) >> 7;
									}

									x += pixel_size;
								}
							}

							break;
						}

						case 10 :
						{
							int x = 0;
							int y = 0;
							BYTE rle;
							WORD pixel;

							while(1) {
								BYTE *bits = FreeImage_GetScanLine(dib, y);
		
								io->read_proc(&rle,1, 1, handle);
								
								// compressed block
								
								if (rle > 127) {
									rle -= 127;

									io->read_proc(&pixel, sizeof(WORD), 1, handle);
								
									for (int ix = 0; ix < rle; ix++) {
										if (TARGA_LOAD_RGB555 & flags) {
											*reinterpret_cast<WORD*>(bits + x) = 0x7FFF & pixel;
										} else {
											bits[x + 0] = (pixel & 0x001f) << 3;
											bits[x + 1] = (pixel & 0x03e0) >> 2;
											bits[x + 2] = (pixel & 0x7c00) >> 7;
										}

										x += pixel_size;
										
										if (x >= line) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done2;																
										}
									}
								} else {
									rle++;

									for (int ix = 0; ix < rle; ix++) {
										io->read_proc(&pixel, sizeof(WORD), 1, handle);

										if (TARGA_LOAD_RGB555 & flags) {
											*reinterpret_cast<WORD*>(bits + x) = 0x7FFF & pixel;
										} else {
											bits[x + 0] = (pixel & 0x001f) << 3;
											bits[x + 1] = (pixel & 0x03e0) >> 2;
											bits[x + 2] = (pixel & 0x7c00) >> 7;
										}

										x += pixel_size;

										if (x >= line) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done2;																
										}
									}
								}
							}

					done2 :
							break;
						}

						default :
							FreeImage_Free(dib);
							return NULL;
					}

					break;
				}

				case 24 :
				{
					dib = (BYTE *)FreeImage_Allocate(header.is_width, header.is_height, 24);

					if (dib == 0)
						throw "DIB allocation failed";					

					// read in the bitmap bits

					switch (header.image_type) {
						case 2 :
						{
							for (unsigned count = 0; count < header.is_height; count++) {
								BYTE *bits = FreeImage_GetScanLine(dib, count);

								io->read_proc(bits, line, 1, handle);

								bits += pitch;
							}

							break;
						}

						case 10 :
						{
							int x = 0;
							int y = 0;

							BYTE *bits = FreeImage_GetScanLine(dib, y);
							BYTE rle;
							
							while(1) {
								io->read_proc(&rle,1, 1, handle);
								
								if (rle>127) {
									rle -= 127;

									RGBTRIPLE triple;

									io->read_proc(&triple, 3, 1, handle);

									for (int ix = 0; ix < rle; ix++) {
										bits[x++] = triple.rgbtBlue;
										bits[x++] = triple.rgbtGreen;
										bits[x++] = triple.rgbtRed;

										if (x >= line) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done243;											
											
											bits = FreeImage_GetScanLine(dib, y);
										}
									}
								} else {
									rle++;

									for (int ix = 0; ix < rle; ix++) {
										RGBTRIPLE triple;		

										io->read_proc(&triple, 3, 1, handle);

										bits[x++] = triple.rgbtBlue;
										bits[x++] = triple.rgbtGreen;
										bits[x++] = triple.rgbtRed;
										
										if (x >= line) {
											x = 0;
											y++;

											if (y >= header.is_height)
												goto done243;											

											bits = FreeImage_GetScanLine(dib, y);
										}
									}
								}
							}
					done243 :
							break;
						}

						default :
							FreeImage_Free(dib);
							return NULL;
					}

					break;
				}
				
				case 32 :
				{
					int pixel_bits;

					if (TARGA_LOAD_RGB888 & flags) {
						pixel_bits = 24;

						line = CalculateLine(header.is_width, pixel_bits);
						pitch = CalculatePitch(line);
					} else {
						pixel_bits = 32;
					}

					const unsigned pixel_size = unsigned (pixel_bits) / 8;

					// Allocate the DIB

					dib = (BYTE *)FreeImage_Allocate(header.is_width, header.is_height, pixel_bits);
					
					if (dib == 0)
						throw "DIB allocation failed";					

					// read in the bitmap bits

					switch (header.image_type) {
						case 2 :
						{
							// uncompressed

							switch(header.is_image_descriptor) {
								case 0 :
								{
									for (unsigned count = header.is_height - 1; count > 0; count--) {
										BYTE *bits = FreeImage_GetScanLine(dib, count);

										for (unsigned cols = 0; cols < header.is_width; cols++) {
											RGBQUAD rgb;

											io->read_proc(&rgb, sizeof(RGBQUAD), 1, handle);

											bits[0] = rgb.rgbBlue;
											bits[1] = rgb.rgbGreen;
											bits[2] = rgb.rgbRed;

											if ((TARGA_LOAD_RGB888 & flags) != TARGA_LOAD_RGB888)
												bits[3] = rgb.rgbReserved;											

											bits += pixel_size;
										}
									}

									break;
								}

								case 8 :
								{
									for (unsigned count = 0; count < header.is_height; count++) {
										BYTE *bits = FreeImage_GetScanLine(dib, count);

										for (unsigned cols = 0; cols < header.is_width; cols++) {
											RGBQUAD rgb;

											io->read_proc(&rgb, sizeof(RGBQUAD), 1, handle);

											bits[0] = rgb.rgbBlue;
											bits[1] = rgb.rgbGreen;
											bits[2] = rgb.rgbRed;

											if ((TARGA_LOAD_RGB888 & flags) != TARGA_LOAD_RGB888)
												bits[3] = rgb.rgbReserved;											

											bits += pixel_size;
										}
									}

									break;
								}

								default :
									FreeImage_Free(dib);
									return NULL;
							}

							break;
						}
					}

					break;
				}
			}

			return (void *)dib;

		} catch(char *message) {
			if (FreeImage_OutputMessage)
				FreeImage_OutputMessage(FIF_TARGA, message);

			return NULL;
		}
	}

	return NULL;
}

#endif