// ==========================================================
// Bitmap conversion routines
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@iut.univ-lehavre.fr)
// - Jani Kajala (janik@remedy.fi)
//
// This file is part of FreeImage 
//
// Use at your own risk!
// ==========================================================

#include "FreeImage.h"
#include "Quantizers.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef CONVERSION_ENABLED

// ----------------------------------------------------------

void *
FreeImage_ConvertTo8Bits(void *dib, BOOL type555) {
	unsigned int rows, cols;

	if(!dib)
		return NULL;

	void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 8);

	if (!new_dib)
		return NULL;

	// Build a greyscale palette

	RGBQUAD *new_pal = FreeImage_GetPalette(new_dib);

	for(int i = 0; i < 256; i++) {
		new_pal[i].rgbRed	= i;
		new_pal[i].rgbGreen = i;
		new_pal[i].rgbBlue	= i;
	}

	switch(FreeImage_GetBPP(dib)) {
	    case 1:
		{
			BYTE color;

			// Expand and copy the bitmap data

			RGBQUAD *old_pal = FreeImage_GetPalette(dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
				BYTE *bits = FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				for (cols = 0; cols < FreeImage_GetLine(dib) * 8; cols++) {
					color = (bits[cols >> 3] & (0x80 >> (cols & 0x07))) != 0;
					new_bits[cols] = color ? old_pal[1].rgbRed : old_pal[0].rgbRed;
				}
			}

			return new_dib;
		}

		case 4 :
		{
			// Copy the palette

			RGBQUAD *old_pal = FreeImage_GetPalette(dib);
			for (int i = 0; i < 16; i++) {
				new_pal[i].rgbRed	= old_pal[i].rgbRed;
				new_pal[i].rgbGreen = old_pal[i].rgbGreen;
				new_pal[i].rgbBlue	= old_pal[i].rgbBlue;
			}

			// Expand and copy the bitmap data

			for (unsigned y = 0; y < FreeImage_GetHeight(dib); y++) {
				unsigned count_new = 0;
				unsigned count_org = 0;

				BYTE *org_bits = FreeImage_GetScanLine(dib, y);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, y);

				BOOL hinibble  = FALSE;

				while (count_new < FreeImage_GetWidth(dib)) {
					if (hinibble) {
						new_bits[count_new] = HINIBBLE(org_bits[count_org]) >> 4;
					} else {
						new_bits[count_new] |= LOWNIBBLE(org_bits[count_org]);

						count_org++;
					}

					hinibble = !hinibble;

					count_new++;
				}
			}

			return new_dib;
		}

		case 16 :
		{
			// convert the 16 bits bitmap to 8 bits

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);			
				WORD *bits = (WORD *)FreeImage_GetScanLine(dib, rows);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					if (type555) 
						new_bits[cols] = GREY((((bits[cols] & 0x7C00) >> 10) << 3), (((bits[cols] & 0x3E0) >> 4) << 2), ((bits[cols] & 0x1F) << 3));
					else
						new_bits[cols] = GREY((((bits[cols] & 0xF800) >> 11) << 3), (((bits[cols] & 0x7E0) >> 5) << 2), ((bits[cols] & 0x1F) << 3));

				}
			}

			return new_dib;
		}

		case 24 :
		{
			// convert the 24 bits bitmap to 8 bits

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);			
				BYTE *bits = FreeImage_GetScanLine(dib, rows);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					new_bits[cols] = GREY(bits[2], bits[1], bits[0]);
					bits += 3;
				}
			}

			return new_dib;
		}

		case 32 :
		{
			// convert the 32 bits bitmap to 8 bits

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);			
				BYTE *bits = FreeImage_GetScanLine(dib, rows);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					new_bits[cols] = GREY(bits[2], bits[1], bits[0]);

					bits += 4;
				}
			}

			return new_dib;
		}
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_ConvertTo16Bits(void *dib, BOOL type555) {
	if (dib != NULL) {
		switch (FreeImage_GetBPP(dib)) {
			case 1:
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 16);

				if (new_dib) {
					RGBQUAD *palette = FreeImage_GetPalette(dib);
					BYTE index;

					for (unsigned int rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
						BYTE *bits = FreeImage_GetScanLine(dib, rows);
						WORD *new_bits = (WORD *)FreeImage_GetScanLine(new_dib, rows);

						for (unsigned int cols = 0; cols < FreeImage_GetLine(dib) * 8; cols++) {
							index = (bits[cols >> 3] & (0x80 >> (cols & 0x07))) != 0 ? 1 : 0;

							if (type555) {
								new_bits[cols] = RGB555(palette[index].rgbBlue, palette[index].rgbGreen, palette[index].rgbRed);
							} else {
								new_bits[cols] = RGB565(palette[index].rgbBlue, palette[index].rgbGreen, palette[index].rgbRed);
							}
						}
					}
					
					return new_dib;
				}

				break;
			}

			case 4 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 16);

				if (new_dib) {
					for (unsigned int rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
						BYTE *bits = FreeImage_GetScanLine(dib, rows);
						WORD *new_bits = (WORD *)FreeImage_GetScanLine(new_dib, rows);

						BOOL lonibble = FALSE;
						int x = 0;

						for (unsigned int cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
							RGBQUAD *palette;

							if (lonibble) {
								palette = FreeImage_GetPalette(dib) + LOWNIBBLE(bits[x++]);
							} else {
								palette = FreeImage_GetPalette(dib) + (HINIBBLE(bits[x]) >> 4);								
							}

							if (type555) {
								new_bits[cols] = RGB555(palette->rgbBlue, palette->rgbGreen, palette->rgbRed);
							} else {
								new_bits[cols] = RGB565(palette->rgbBlue, palette->rgbGreen, palette->rgbRed);
							}

							lonibble = !lonibble;
						}
					}

					return new_dib;
				}

				break;
			}

			case 8 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 16);

				if (new_dib) {
					for (unsigned int rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
						BYTE *bits = FreeImage_GetScanLine(dib, rows);
						WORD *new_bits = (WORD *)FreeImage_GetScanLine(new_dib, rows);

						for (unsigned int cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
							RGBQUAD *palette = FreeImage_GetPalette(dib) + bits[cols];

							if (type555) {
								new_bits[cols] = RGB555(palette->rgbBlue, palette->rgbGreen, palette->rgbRed);
							} else {
								new_bits[cols] = RGB565(palette->rgbBlue, palette->rgbGreen, palette->rgbRed);
							}							
						}
					}

					return new_dib;
				}

				break;
			}

			case 24 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 16);

				if (new_dib) {
					for (unsigned int rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
						BYTE *bits = FreeImage_GetScanLine(dib, rows);
						WORD *new_bits = (WORD *)FreeImage_GetScanLine(new_dib, rows);

						for (unsigned int cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
							if (type555) {
								new_bits[cols] = RGB555(bits[0], bits[1], bits[2]);
							} else {
								new_bits[cols] = RGB565(bits[0], bits[1], bits[2]);
							}

							bits += 3;
						}
					}

					return new_dib;
				}

				break;
			}

			case 32 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 16);

				if (new_dib) {
					for (unsigned int rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
						BYTE *bits = FreeImage_GetScanLine(dib, rows);
						WORD *new_bits = (WORD *)FreeImage_GetScanLine(new_dib, rows);

						for (unsigned int cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
							if (type555) {
								new_bits[cols] = RGB555(bits[0], bits[1], bits[2]);
							} else {
								new_bits[cols] = RGB565(bits[0], bits[1], bits[2]);
							}

							bits += 4;
						}
					}

					return new_dib;
				}

				break;
			}
		}
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_ConvertTo24Bits(void *dib, BOOL type555) {
	unsigned int bpp;
	unsigned int rows;
	unsigned int cols;

	if (!dib) {
		return NULL;
	}

	bpp = FreeImage_GetBPP(dib);

	if(!((bpp & 1) || (bpp & 4) || (bpp & 8) || (bpp & 16) || (bpp & 32))) {
		return NULL;
	}

	void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 24);

	if (!new_dib) {
		return NULL;
	}

	switch(bpp) {
	    case 1:
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);
			BYTE index;

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
				BYTE *bits = FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				for (cols = 0; cols < FreeImage_GetLine(dib) * 8; cols++) {
					index = (bits[cols >> 3] & (0x80 >> (cols & 0x07))) != 0 ? 1 : 0;

					new_bits[0] = palette[index].rgbBlue;
					new_bits[1] = palette[index].rgbGreen;
					new_bits[2] = palette[index].rgbRed;

					new_bits += 3;
				}
			}
			
			return new_dib;
		}

		case 4 :
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *bits = FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				BOOL low_nibble = FALSE;
				int x = 0;

				for (unsigned cols = 0 ; cols < FreeImage_GetWidth(dib); ++cols ) {
					if (low_nibble) {
						new_bits[0] = palette[LOWNIBBLE(bits[x])].rgbBlue;
						new_bits[1] = palette[LOWNIBBLE(bits[x])].rgbGreen;
						new_bits[2] = palette[LOWNIBBLE(bits[x])].rgbRed;

						x++;
					} else {
						new_bits[0] = palette[HINIBBLE(bits[x]) >> 4].rgbBlue;
						new_bits[1] = palette[HINIBBLE(bits[x]) >> 4].rgbGreen;
						new_bits[2] = palette[HINIBBLE(bits[x]) >> 4].rgbRed;
					}

					low_nibble = !low_nibble;

					new_bits += 3;
				}
			}
			
			return new_dib;
		}
			
		case 8 :
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
				BYTE *bits = FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				for (cols = 0; cols < FreeImage_GetLine(dib); cols++) {
					new_bits[0] = palette[bits[cols]].rgbBlue;
					new_bits[1] = palette[bits[cols]].rgbGreen;
					new_bits[2] = palette[bits[cols]].rgbRed;

					new_bits += 3;
				}
			}
			
			return new_dib;
		}

		case 16 :
		{
			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				WORD *bits = (WORD *)FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					if (type555) {
						new_bits[2] = ((bits[cols] & 0x7C00) >> 10) << 3;
						new_bits[1] = ((bits[cols] & 0x3E0) >> 4) << 2;
						new_bits[0] = (bits[cols] & 0x1F) << 3;
					} else {
						new_bits[2] = ((bits[cols] & 0xF800) >> 11) << 3;
						new_bits[1] = ((bits[cols] & 0x7E0) >> 5) << 2;
						new_bits[0] = (bits[cols] & 0x1F) << 3;
					}

					new_bits += 3;
				}
			}
			
			return new_dib;
		}

		case 32 :
		{
			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *bits = FreeImage_GetScanLine(dib, rows);
				BYTE *new_bits = FreeImage_GetScanLine(new_dib, rows);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					new_bits[0] = bits[0];
					new_bits[1] = bits[1];
					new_bits[2] = bits[2];

					bits += 4;
					new_bits += 3;
				}
			}
			
			return new_dib;
		}

	}

	return NULL;
}


// ----------------------------------------------------------

void *
FreeImage_ConvertTo32Bits(void *dib, BOOL type555) {

	unsigned int bpp, opitch, npitch;
	unsigned int rows, cols;

	if (!dib) {
		return NULL;
	}

	bpp = FreeImage_GetBPP(dib);

	if (!((bpp & 1) || (bpp & 4) || (bpp & 8) || (bpp & 16) || (bpp & 24))) {
		return NULL;
	}

	void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 32);

	if (!new_dib) {
		return NULL;
	}

	opitch = FreeImage_GetPitch(dib);
	npitch = FreeImage_GetPitch(new_dib);

	switch(bpp) {
	    case 1:
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);
			BYTE *bits = FreeImage_GetBits(dib);
			BYTE index;

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
				BYTE *new_bits = FreeImage_GetBits(new_dib) + (rows * npitch);

				for (cols = 0; cols < FreeImage_GetLine(dib) * 8; cols++) {
					index = (bits[cols>>3] & (0x80 >> (cols & 0x07))) != 0 ? 1 : 0;
					new_bits[0] = palette[index].rgbBlue;
					new_bits[1] = palette[index].rgbGreen;
					new_bits[2] = palette[index].rgbRed;
					new_bits += 4;
				}

				bits += opitch;
			}
			
			return new_dib;
		}

		case 4 :
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);
			BYTE *bits = FreeImage_GetBits(dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *new_bits = FreeImage_GetBits(new_dib) + (rows * npitch);

				BOOL low_nibble = FALSE;
				int x = 0;

				int owidth = FreeImage_GetWidth(dib);

				for (int cols = 0 ; cols < owidth ; ++cols) {
					if (low_nibble) {
						new_bits[0] = palette[LOWNIBBLE(bits[x])].rgbBlue;
						new_bits[1] = palette[LOWNIBBLE(bits[x])].rgbGreen;
						new_bits[2] = palette[LOWNIBBLE(bits[x])].rgbRed;

						x++;
					} else {
						new_bits[0] = palette[HINIBBLE(bits[x]) >> 4].rgbBlue;
						new_bits[1] = palette[HINIBBLE(bits[x]) >> 4].rgbGreen;
						new_bits[2] = palette[HINIBBLE(bits[x]) >> 4].rgbRed;
					}

					low_nibble = !low_nibble;

					new_bits += 4;
				}

				bits += opitch;
			}
			
			return new_dib;
		}
			
		case 8 :
		{
			RGBQUAD *palette = FreeImage_GetPalette(dib);
			BYTE *bits = FreeImage_GetBits(dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {				
				BYTE *new_bits = FreeImage_GetBits(new_dib) + (rows * npitch);

				for (cols = 0; cols < FreeImage_GetLine(dib); cols++) {
					new_bits[0] = palette[bits[cols]].rgbBlue;
					new_bits[1] = palette[bits[cols]].rgbGreen;
					new_bits[2] = palette[bits[cols]].rgbRed;

					new_bits += 4;
				}

				bits += opitch;
			}
			
			return new_dib;
		}

		case 16 :
		{
			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				WORD *bits = (WORD *)(FreeImage_GetBits(dib) + (rows * opitch));
				BYTE *new_bits = FreeImage_GetBits(new_dib) + (rows * npitch);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					if (type555) {
						new_bits[2] = ((bits[cols] & 0x7C00) >> 10) << 3;
						new_bits[1] = ((bits[cols] & 0x3E0) >> 4) << 2;
						new_bits[0] = (bits[cols] & 0x1F) << 3;
					} else {
						new_bits[2] = ((bits[cols] & 0xF800) >> 11) << 3;
						new_bits[1] = ((bits[cols] & 0x7E0) >> 5) << 2;
						new_bits[0] = (bits[cols] & 0x1F) << 3;
					}

					new_bits += 4;
				}

				bits += opitch;
			}
			
			return new_dib;
		}

		case 24 :
		{
			DWORD *new_bits = (DWORD *) FreeImage_GetBits(new_dib);

			for (rows = 0; rows < FreeImage_GetHeight(dib); rows++) {
				BYTE *bits = FreeImage_GetBits(dib) + (rows * opitch);

				for (cols = 0; cols < FreeImage_GetWidth(dib); cols++) {
					*new_bits = *(DWORD*)bits & 0x00FFFFFF;

					new_bits++;
					bits += 3;
				}
			}

			return new_dib;
		}

	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_ColorQuantize(void *dib, FREE_IMAGE_QUANTIZE quantize) {
	if (dib) {
		if (FreeImage_GetBPP(dib) == 24) {
			switch(quantize) {
				case FIQ_WUQUANT :
					try {
						WuQuantizer Q (dib);
						return (void *) Q.Quantize();
					} catch (char *) {
						return NULL;
					}			
			}
		}
	}

	return NULL;
}

#endif