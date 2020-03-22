// ==========================================================
// BMP Loader and Writer
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
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

#ifdef BMP_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

const BYTE RLE_COMMAND     = 0;
const BYTE RLE_ENDOFLINE   = 0;
const BYTE RLE_ENDOFBITMAP = 1;
const BYTE RLE_DELTA       = 2;

// ----------------------------------------------------------

#pragma pack(push, 1)

typedef struct tagBITMAPCOREHEADER {
  DWORD   bcSize; 
  WORD    bcWidth; 
  WORD    bcHeight; 
  WORD    bcPlanes; 
  WORD    bcBitCount; 
} BITMAPCOREHEADER, *PBITMAPCOREHEADER; 

typedef struct tagBITMAPFILEHEADER { 
  WORD    bfType; 
  DWORD   bfSize; 
  WORD    bfReserved1; 
  WORD    bfReserved2;
  DWORD   bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

#pragma pack(pop)

// ----------------------------------------------------------
//   BMP Loading
// ----------------------------------------------------------

void *
FreeImage_LoadBMP(const char *filename, BMPFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadBMPFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadBMPFromHandle(FreeImageIO *io, fi_handle handle, BMPFlags flags) {
	BYTE *dib = NULL;
	DWORD type = 0;

	if (handle) {
		// we use this offset value to make seemingly absolute seeks relative in the file
		
		long offset_in_file = io->tell_proc(handle);

		// read the file header

		BITMAPFILEHEADER bitmapfileheader;

		io->read_proc(&bitmapfileheader, sizeof(BITMAPFILEHEADER), 1, handle);		
		io->read_proc(&type, sizeof(DWORD), 1, handle);
		io->seek_proc(handle, 0 - sizeof(DWORD), SEEK_CUR);
		
		// ----------------------------------------------------------------------
		//   WINDOWS BITMAPS
		// ----------------------------------------------------------------------

		if (type == sizeof(BITMAPINFOHEADER)) {
			BITMAPINFOHEADER bih;

			io->read_proc(&bih, sizeof(BITMAPINFOHEADER), 1, handle);

			// keep some general information about the bitmap

			int used_colors = bih.biClrUsed;
			int width       = bih.biWidth;
			int height      = bih.biHeight;
			int bit_count   = bih.biBitCount;
			int compression = bih.biCompression;
			int pitch       = CalculatePitch(CalculateLine(width, bit_count));
			
			switch (bit_count) {
				case 1 :
				case 4 :
				case 8 :
				{
					if ((used_colors <= 0) || (used_colors > CalculateUsedColors(bit_count)))
						used_colors = CalculateUsedColors(bit_count);					
					
					// allocate enough memory to hold the bitmap (header, palette, pixels) and read the palette

					dib = (BYTE *)FreeImage_Allocate(width, height, bit_count);

					BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);
					pInfoHeader->biXPelsPerMeter = bih.biXPelsPerMeter;
					pInfoHeader->biYPelsPerMeter = bih.biYPelsPerMeter;
					
					// load the palette

					io->read_proc(FreeImage_GetPalette(dib), used_colors * sizeof(RGBQUAD), 1, handle);

					// seek to the actual pixel data.
					// this is needed because sometimes the palette is larger than the entries it contains predicts

					if (bitmapfileheader.bfOffBits > (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (used_colors * sizeof(RGBQUAD)))) {
						io->seek_proc(handle, offset_in_file, SEEK_SET);
						io->seek_proc(handle, bitmapfileheader.bfOffBits, SEEK_CUR);
					}
					
					// read the pixel data

					switch (compression) {
						case BI_RGB :
							if (height > 0) {
								io->read_proc(FreeImage_GetBits(dib), height * pitch, 1, handle);
							} else {
								for (int c = 0; c < abs(height); ++c) {
									io->read_proc(FreeImage_GetScanLine(dib, height - c - 1), pitch, 1, handle);								
								}
							}
							
							return (void *)dib;

						case BI_RLE4 :
						{
							BYTE status_byte = 0;
							BYTE second_byte = 0;
							int scanline = 0;
							int bits = 0;
							BOOL low_nibble = FALSE;

							for (;;) {
								io->read_proc(&status_byte, sizeof(BYTE), 1, handle);

								switch (status_byte) {
									case RLE_COMMAND :
										io->read_proc(&status_byte, sizeof(BYTE), 1, handle);

										switch (status_byte) {
											case RLE_ENDOFLINE :
												bits = 0;
												scanline++;
												low_nibble = FALSE;
												break;

											case RLE_ENDOFBITMAP :
												return (void *)dib;

											case RLE_DELTA :
											{
												// read the delta values

												BYTE delta_x;
												BYTE delta_y;

												io->read_proc(&delta_x, sizeof(BYTE), 1, handle);
												io->read_proc(&delta_y, sizeof(BYTE), 1, handle);

												// apply them

												bits       += delta_x / 2;
												scanline   += delta_y;
												break;
											}

											default :
												io->read_proc(&second_byte, sizeof(BYTE), 1, handle);

												BYTE *sline = FreeImage_GetScanLine(dib, scanline);

												for (int i = 0; i < status_byte; i++) {
													if (low_nibble) {
														*(sline + bits) |= LOWNIBBLE(second_byte);

														if (i != status_byte - 1)
															io->read_proc(&second_byte, sizeof(BYTE), 1, handle);

														bits++;
													} else {
														*(sline + bits) |= HINIBBLE(second_byte);
													}
													
													low_nibble = !low_nibble;
												}

												if ((status_byte / 2) & 1 == 1)
													io->read_proc(&second_byte, sizeof(BYTE), 1, handle);												

												break;
										};

										break;

									default :
									{
										BYTE *sline = FreeImage_GetScanLine(dib, scanline);

										io->read_proc(&second_byte, sizeof(BYTE), 1, handle);

										for (unsigned i = 0; i < status_byte; i++) {
											if (low_nibble) {
												*(sline + bits) |= LOWNIBBLE(second_byte);

												bits++;
											} else {
												*(sline + bits) |= HINIBBLE(second_byte);
											}				
											
											low_nibble = !low_nibble;
										}
									}

									break;
								};
							}

							break;
						}

						case BI_RLE8 :
						{
							BYTE status_byte = 0;
							BYTE second_byte = 0;
							int scanline = 0;
							int bits = 0;

							for (;;) {
								io->read_proc(&status_byte, sizeof(BYTE), 1, handle);

								switch (status_byte) {
									case RLE_COMMAND :
										io->read_proc(&status_byte, sizeof(BYTE), 1, handle);

										switch (status_byte) {
											case RLE_ENDOFLINE :
												bits = 0;
												scanline++;
												break;

											case RLE_ENDOFBITMAP :
												return (void *)dib;

											case RLE_DELTA :
											{
												// read the delta values

												BYTE delta_x;
												BYTE delta_y;

												io->read_proc(&delta_x, sizeof(BYTE), 1, handle);
												io->read_proc(&delta_y, sizeof(BYTE), 1, handle);

												// apply them

												bits     += delta_x;
												scanline += delta_y;
												break;
											}

											default :
												io->read_proc((void *)(FreeImage_GetScanLine(dib, scanline) + bits), sizeof(BYTE) * status_byte, 1, handle);
												
												// align run length to even number of bytes 

												if (status_byte & 1 == 1)
													io->read_proc(&second_byte, sizeof(BYTE), 1, handle);												

												bits += status_byte;													

												break;								
										};

										break;

									default :
										BYTE *sline = FreeImage_GetScanLine(dib, scanline);

										io->read_proc(&second_byte, sizeof(BYTE), 1, handle);

										for (unsigned i = 0; i < status_byte; i++) {
											*(sline + bits) = second_byte;

											bits++;					
										}

										break;
								};
							}

							break;
						}

						default :								
							if (FreeImage_OutputMessage) {
								FreeImage_OutputMessage(FIF_BMP, "compression type not supported");
							}

							return NULL;
					}						
				}

				break;

				case 16 :
				case 24 :
				case 32 :
				{
					dib = (BYTE *)FreeImage_Allocate(width, height, bit_count);

					BITMAPINFOHEADER *pInfoHeader = FreeImage_GetInfoHeader(dib);
					pInfoHeader->biXPelsPerMeter = bih.biXPelsPerMeter;
					pInfoHeader->biYPelsPerMeter = bih.biYPelsPerMeter;

					io->read_proc(FreeImage_GetBits(dib), height * pitch, 1, handle);					

					return (void *)dib;
				}
			}
		}		
		
		// ----------------------------------------------------------------------
		//   OS/2 BITMAPS
		// ----------------------------------------------------------------------
		
		if (type == sizeof(BITMAPCOREHEADER)) {
			BITMAPCOREHEADER bch;

			io->read_proc(&bch, sizeof(BITMAPCOREHEADER), 1, handle);

			int width     = bch.bcWidth;
			int height    = bch.bcHeight;
			int bit_count = bch.bcBitCount;
			int line      = CalculateLine(width, bit_count);
			int pitch     = CalculatePitch(line);
			
			switch (bit_count) {
				case 1 :
				case 4 :
				case 8 :
				{
					int used_colors = CalculateUsedColors(bit_count);

					// allocate the bitmap

					dib = (BYTE *)FreeImage_Allocate(width, height, bit_count);

					RGBQUAD *quad = FreeImage_GetPalette(dib);

					for (int i = 0; i < used_colors; i++) {
						io->read_proc(&quad->rgbBlue, 1, 1, handle);
						io->read_proc(&quad->rgbGreen, 1, 1, handle);
						io->read_proc(&quad->rgbRed, 1, 1, handle);

						quad++;
					}

					// read the bitmap data

					io->read_proc(FreeImage_GetBits(dib), height * pitch, 1, handle);					

					return (void *)dib;
				}

				case 16 :
				case 24 :
				case 32 :
				{
					// allocate the bitmap

					dib = (BYTE *)FreeImage_Allocate(width, height, bit_count);
					
					io->read_proc(FreeImage_GetBits(dib), height * pitch, 1, handle);

					return (void *)dib;
				}
			}

			return NULL;
		}
	} else {
		return NULL;
	}

	return NULL;
}

// ----------------------------------------------------------
//   BMP Saving
// ----------------------------------------------------------

BOOL
FreeImage_SaveBMP(void *dib, const char *filename, BMPFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "wb");
	
	if (handle) {
		BOOL success = FreeImage_SaveBMPToHandle(dib, &io, (fi_handle)handle, flags);

		fclose(handle);

		return success;
	}

	return FALSE;
}

// ----------------------------------------------------------

BOOL
FreeImage_SaveBMPToHandle(void *dib, FreeImageIO *io, fi_handle handle, BMPFlags flags) {
	if ((dib) && (handle)) {		
		BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(dib);
		RGBQUAD *palette = FreeImage_GetPalette(dib);

		BITMAPFILEHEADER bitmapfileheader;
		bitmapfileheader.bfType = 0x4D42;
		bitmapfileheader.bfSize = sizeof(BITMAPFILEHEADER) + FreeImage_GetDIBSize(dib);
		bitmapfileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (bih->biClrUsed * sizeof(RGBQUAD));
		bitmapfileheader.bfReserved1 = 0;
		bitmapfileheader.bfReserved2 = 0;

		// write the chunks to the file

		if (io->write_proc(&bitmapfileheader, sizeof(BITMAPFILEHEADER), 1, handle) != 1)
			return FALSE;		

		if (io->write_proc(bih, sizeof(BITMAPINFOHEADER), 1, handle) != 1)
			return FALSE;		

		if (palette && (io->write_proc(palette, sizeof(RGBQUAD) * FreeImage_GetColorsUsed(dib), 1, handle) != 1))
			return FALSE;		

		if (io->write_proc(FreeImage_GetBits(dib), FreeImage_GetHeight(dib) * FreeImage_GetPitch(dib), 1, handle) != 1)
			return FALSE;

		return TRUE;
	} else {
		return FALSE;
	}
}

#endif
