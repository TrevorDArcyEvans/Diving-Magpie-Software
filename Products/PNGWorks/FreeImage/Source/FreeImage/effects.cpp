// ==========================================================
// Bitmap effects
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Alexander Dymerets (sashad@te.net.ua)
// - Hervé Drolon (drolon@iut.univ-lehavre.fr)
//
// This file is part of FreeImage 
//
// Use at your own risk!
// ==========================================================

#pragma warning (disable : 4244)

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef EFFECTS_ENABLED

#include <stdlib.h>
#include <memory.h> 

// ----------------------------------------------------------

#pragma pack(push, 1)

typedef struct tagRGBTRIPLE {
  BYTE rgbtBlue; 
  BYTE rgbtGreen; 
  BYTE rgbtRed;
} RGBTRIPLE; 

#pragma pack(pop)

// ----------------------------------------------------------

#ifndef min
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef GREY
#define GREY(r,g,b) (BYTE)(((WORD)r * 77 + (WORD)g * 150 + (WORD)b * 29) >> 8)
// #define GREY(r,g,b) (BYTE)(((WORD)r * 169 + (WORD)g * 256 + (WORD)b * 87) >> 9)
#endif

// ----------------------------------------------------------
//  cloning
// ----------------------------------------------------------

void *
FreeImage_Clone(void *dib) {
	BYTE *new_dib = (BYTE *)FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), FreeImage_GetBPP(dib));

	if (new_dib) {
		memcpy(new_dib, dib, sizeof(FREEIMAGEHEADER) + FreeImage_GetDIBSize(dib));

		return new_dib;
	}

	return NULL;
}

// ----------------------------------------------------------
//   mirror and flip
// ----------------------------------------------------------

void
FreeImage_Flip(void *dib) {
	if (dib) {
		void *clone = FreeImage_Clone(dib);

		// swap the buffer

		int pitch = FreeImage_GetLine(dib);
		int lines = FreeImage_GetHeight(dib);

		int line_t = 0;
		int line_s = lines - 1;

		for (int count = 0 ; count < lines ; ++count) {
			BYTE *bits_s = FreeImage_GetScanLine(clone, line_s--);
			BYTE *bits_t = FreeImage_GetScanLine(dib, line_t++);

			memcpy(bits_t, bits_s, pitch);
		}

		FreeImage_Free(clone);
	}
}

void
FreeImage_Mirror(void *dib) {
	if (dib) {
		int line   = FreeImage_GetLine(dib);
		int pitch  = FreeImage_GetPitch(dib);
		int height = FreeImage_GetHeight(dib);

		BYTE table[8]  = { 1, 2, 4, 8, 16, 32, 64, 128 };
		BYTE *new_bits = (BYTE *)malloc(line);

		// mirror the buffer

		for (int count = 0; count < height; count++) {
			BYTE *bits = FreeImage_GetScanLine(dib, count);
			memcpy(new_bits, bits, line);

			switch (FreeImage_GetBPP(dib)) {
				case 1 :
				{
					for (int c = 0; c < line; c++) {
						BYTE inverted = 0;

						for (int d = 0; d < 8; d++) {
							if ((new_bits[line - c - 1] & table[d]) == table[d]) {
								inverted |= table[7 - d];
							}
						}

						bits[c] = inverted;
					}

					break;
				}

				case 4 :
				{
					for (int c = 0; c < line; c++) {
						bits[c] = new_bits[line - c - 1];

						BYTE nibble = HINIBBLE(bits[c]) >> 4;

						bits[c] = bits[c] << 4;
						bits[c] |= nibble;
					}

					break;
				}

				case 8 :
				{
					for (int c = 0; c < line; c++) {
						bits[c] = new_bits[line - c - 1];
					}

					break;
				}

				case 16 :
				{
					for (int c = 0; c < line; c += sizeof(WORD)) {
						memcpy(bits + c, new_bits + line - c, sizeof(WORD));
						
					}

					break;
				}

				case 24 :
				{
					for (int c = 0; c < line; c += sizeof(RGBTRIPLE)) {
						memcpy(bits + c, new_bits + line - c, sizeof(RGBTRIPLE));
						
					}

					break;
				}

				case 32 :
				{
					for (int c = 0; c < line; c += sizeof(RGBQUAD)) {
						memcpy(bits + c, new_bits + line - c, sizeof(RGBQUAD));						
					}

					break;
				}
			};
		}

		free(new_bits);
	}
}

// ----------------------------------------------------------
//   grayscale conversion
// ----------------------------------------------------------

void
FreeImage_ConvertToGreyscale(void *dib) {
	if (dib) {
		switch (FreeImage_GetBPP(dib)) {
			case 1 :
			case 4 :
			case 8 :
			{
				RGBQUAD *rgb = FreeImage_GetPalette(dib);

				for (unsigned pal = 0; pal < FreeImage_GetColorsUsed(dib); pal++) {
					BYTE gray = GREY(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue);
					
					rgb->rgbRed   =
					rgb->rgbGreen =
					rgb->rgbBlue  = gray;

					rgb++;
				}

				break;
			}

			case 24 :
			case 32 :
			{
				int bytespp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);

				for (unsigned r = 0; r < FreeImage_GetHeight(dib); r++) {
					BYTE *bits = FreeImage_GetScanLine(dib, r);

					for (unsigned c = 0; c < FreeImage_GetWidth(dib); c++) {
						BYTE gray = GREY(bits[2], bits[1], bits[0]);

						bits[0] =
						bits[1] =
						bits[2] = gray;

						bits += bytespp;
					}
				}

				break;
			}
		}
	}
}

// ----------------------------------------------------------
//   alpha blending
// ----------------------------------------------------------

void
FreeImage_Combine(void *dib1, void *dib2, int x, int y, unsigned int alpha) {
	if (alpha) {
		if ((FreeImage_GetBPP(dib1) == 24) && (FreeImage_GetBPP(dib2) == 24)) {
			if ((x + FreeImage_GetWidth(dib2) <= FreeImage_GetWidth(dib1)) &&
				(y + FreeImage_GetHeight(dib2) <= FreeImage_GetHeight(dib1))) {

				BYTE *bits1 = FreeImage_GetBits(dib1) + ((FreeImage_GetHeight(dib1) - FreeImage_GetHeight(dib2) - y) * FreeImage_GetPitch(dib1)) + (x * 3);
				BYTE *bits2 = FreeImage_GetBits(dib2);	

				if (CheckMMXTechnology()) {
					int width  = FreeImage_GetWidth(dib2);
					int height = FreeImage_GetHeight(dib2);
					int pitch1 = FreeImage_GetPitch(dib1);
					int pitch2 = FreeImage_GetPitch(dib2);

					int ddst, dsrc;

					static __int64 mask = 0x0000ffffffffffff, dbg;

					_asm {
						mov		edi, bits1
						mov		esi, bits2
						pxor	mm5, mm5
						mov		eax, width
						mov		edx, eax
						shl		eax, 1
						add		eax, edx
						mov		ecx, pitch1
						sub		ecx, eax
						mov		ddst, ecx
						mov		ecx, pitch2
						sub		ecx, eax
						mov		dsrc, ecx
						movd	mm2, alpha
						movq	dbg, mm2
						punpcklwd mm2, mm2
						punpckldq mm2, mm2
						pand	mm2, mask
						mov		ebx, height
						cmp		ebx, 0
						jle		eol
				ol:
						mov		eax, edx
						cmp		eax, 0
						jle		eil
				il:
						movd	mm0, dword ptr[esi]
						punpcklbw mm0, mm5
						movd	mm1, dword ptr[edi]
						punpcklbw mm1, mm5
						add		esi, 3
						psubw	mm0, mm1
						psllw	mm1, 8
						pmullw	mm0, mm2
						paddw	mm0, mm1
						psrlw	mm0, 8
						packuswb mm0, mm5
						movd	dword ptr[edi], mm0
						add		edi, 3
						dec		eax
						jnz		il
				eil:
						add		edi, ddst
						add		esi, dsrc
						dec		ebx
						jnz		ol
				eol:
						emms
					}
				} else {
					if (alpha > 255) {
						for (unsigned rows = 0; rows < FreeImage_GetHeight(dib2); rows++) {
							memcpy(bits1, bits2, FreeImage_GetLine(dib2));

							bits1 += FreeImage_GetPitch(dib1);
							bits2 += FreeImage_GetPitch(dib2);
						}
					} else {
						for (unsigned rows = 0; rows < FreeImage_GetHeight(dib2); rows++) {
							for (unsigned cols = 0; cols < FreeImage_GetLine(dib2); cols++) {							
								bits1[cols] = (BYTE)(((bits2[cols] - bits1[cols]) * alpha + (bits1[cols] << 8)) >> 8);
							}

							bits1 += FreeImage_GetPitch(dib1);
							bits2 += FreeImage_GetPitch(dib2);
						}
					}
				}				
			}

			return;
		}
	}
}

void
FreeImage_MaskCombine24Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *psrc, void *pmask, int srcx, int srcy) {
	if ((FreeImage_GetBPP(pdst) == 24) && (FreeImage_GetBPP(psrc) == 24) && (FreeImage_GetBPP(pmask) == 8)) {
		if (dstx < 0) {
			srcx -= dstx;

			width += dstx;

			dstx = 0;
		}

		if (dsty < 0)  {
			srcy -= dsty;

			height += dsty;

			dsty = 0;
		}

		if (srcx < 0) {
			srcx = 0;
		}

		if (srcy < 0) {
			srcy = 0;
		}

		RGBQUAD* mpal = FreeImage_GetPalette(pmask);
		BYTE	*src = (BYTE*) FreeImage_GetBits(psrc) + srcy * FreeImage_GetPitch(psrc) + srcx * 3;
		BYTE	*dst = (BYTE*) FreeImage_GetBits(pdst) + dsty * FreeImage_GetPitch(pdst) + dstx * 3;
		BYTE	*msk = (BYTE*) FreeImage_GetBits(pmask) + srcy * FreeImage_GetPitch(psrc) + srcx * 3;
		int mwidth = FreeImage_GetWidth(pmask);
		width  = min(min(FreeImage_GetWidth(pdst) - dstx, FreeImage_GetWidth(pmask) - srcx), 
			min(width, FreeImage_GetWidth(psrc) - srcx));
		height = min(min(FreeImage_GetHeight(pdst) - dsty, FreeImage_GetHeight(pmask) - srcy), 
			min(width, FreeImage_GetHeight(psrc) - srcy));

		int dsrc = FreeImage_GetPitch(psrc) - width*3;
		int ddst = FreeImage_GetPitch(pdst) - width*3;
		int dmsk = FreeImage_GetPitch(pmask) - width;
		if (CheckMMXTechnology()) {
			_asm {
				mov		edi, dst
				mov		esi, src
				mov		ebx, msk
				mov		edx, mpal
				pxor	mm5, mm5
				cmp		height, 0
				jle		eol
		ol:
				mov		ecx, width
				cmp		ecx, 0
				jle		eil
		il:
				movd	mm0, dword ptr[esi] ;read source RGB value
				punpcklbw mm0, mm5			;unpack bytes to words
				movd	mm1, dword ptr[edi] ;read destination RGB
				xor		eax, eax			;zero the register to prevent CPU stall
				mov		al, byte ptr [ebx]	;read color index from mask
				movd	mm2, dword ptr[eax*4+edx]	;read RGB value from the mask palette
				punpcklbw mm1, mm5
				punpcklbw mm2, mm5
				add		esi, 3				;advance src
				psubw	mm0, mm1			;mm0 = src-dst
				psllw	mm1, 8				;mm1 = dst<<8
				pmullw	mm0, mm2			;mm0 = (src-dst)*alpha
				inc		ebx					;advance msk
				paddw	mm0, mm1			;mm0 = (src - dst) * alpha + (dst << 8)
				psrlw	mm0, 8				;mm0 = ((src - dst) * alpha + (dst << 8))>>8
				packuswb mm0, mm5			;pack words to bytes
				movd	dword ptr[edi], mm0	;store results
				add		edi, 3				;advance dst
				loop	il
		eil:
				add		edi, ddst
				add		esi, dsrc
				add		ebx, dmsk
				dec		height
				jnz		ol
		eol:
				emms						;leave mmx mode
			}
		} else {
			for (unsigned nIndex2 = 0; nIndex2 < height; nIndex2++) {
				for (unsigned nIndex1 = 0; nIndex1 < width; nIndex1++) {
					int alpha = mpal[*msk++].rgbBlue;
					dst[0] = (BYTE)(((src[0] - dst[0]) * alpha + (dst[0] << 8)) >> 8);
					dst[1] = (BYTE)(((src[1] - dst[1]) * alpha + (dst[1] << 8)) >> 8);
					dst[2] = (BYTE)(((src[2] - dst[2]) * alpha + (dst[2] << 8)) >> 8);

					dst += 3;
					src += 3;
				}

				src	+= dsrc;
				dst += ddst;
				msk += dmsk;
			}
		}
	}
}

void
FreeImage_MaskCombine24(void *dib1, void *dib2, void *mask, int x, int y) {
	FreeImage_MaskCombine24Ex(dib1, x, y, FreeImage_GetWidth(dib1), FreeImage_GetHeight(dib1), dib2, mask, 0, 0);
}

void
FreeImage_MaskCombine32Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *psrc, int srcx, int srcy) {
	if ((FreeImage_GetBPP(pdst) == 32) && (FreeImage_GetBPP(psrc) == 32)) {
		if (dstx < 0) {
			srcx -= dstx;

			width += dstx;

			dstx = 0;
		}

		if (dsty < 0)  {
			srcy -= dsty;

			height += dsty;

			dsty = 0;
		}

		if (srcx < 0) {
			srcx = 0;
		}

		if (srcy < 0) {
			srcy = 0;
		}

		BYTE	*src = (BYTE*) FreeImage_GetBits(psrc) + (srcy * FreeImage_GetWidth(psrc) + srcx) * 4;
		BYTE	*dst = (BYTE*) FreeImage_GetBits(pdst) + (dsty * FreeImage_GetWidth(pdst) + dstx) * 4;

		width  = min(FreeImage_GetWidth(pdst) - dstx, min(width, FreeImage_GetWidth(psrc) - srcx));
		height = min(FreeImage_GetHeight(pdst) - dsty, min(width, FreeImage_GetHeight(psrc) - srcy));

		int dsrc = (FreeImage_GetWidth(psrc) - width) << 2;
		int ddst = (FreeImage_GetWidth(pdst) - width) << 2;

		if (CheckMMXTechnology()) {
			_asm {
				mov		edi, dst
				mov		esi, src
				pxor	mm5, mm5
				mov		edx, width
				mov		ebx, height
				cmp		ebx, 0
				jle		eol
		ol:
				mov		eax, edx
				cmp		eax, 0
				jle		eil
		il:
				movd	mm0, dword ptr[esi]
				punpcklbw mm0, mm5
				movd	mm1, dword ptr[edi]
				movq	mm2, mm0
				punpcklbw mm1, mm5
				punpckhwd mm2, mm2
				add		esi, 4
				punpckhdq mm2, mm2
				psubw	mm0, mm1
				psllw	mm1, 8
				pmullw	mm0, mm2
				paddw	mm0, mm1
				psrlw	mm0, 8
				packuswb mm0, mm5
				movd	dword ptr[edi], mm0
				add		edi, 4
				dec		eax
				jnz		il
		eil:
				add		edi, ddst
				add		esi, dsrc
				dec		ebx
				jnz		ol
		eol:
				emms
			}
		} else {
			for (unsigned nIndex2 = 0; nIndex2 < height; nIndex2++) {
				for (unsigned nIndex1 = 0; nIndex1 < width; nIndex1++) {
					dst[0] = (BYTE)(((src[0] - dst[0]) * src[3] + (dst[0] << 8)) >> 8);
					dst[1] = (BYTE)(((src[1] - dst[1]) * src[3] + (dst[1] << 8)) >> 8);
					dst[2] = (BYTE)(((src[2] - dst[2]) * src[3] + (dst[2] << 8)) >> 8);

					dst += 4;
					src += 4;
				}

				src	+= dsrc;
				dst += ddst;
			}
		}
	}
}

void
FreeImage_MaskCombine32(void *dib1, void *dib2, int x, int y) {
	FreeImage_MaskCombine32Ex(dib1, x, y, FreeImage_GetWidth(dib1), FreeImage_GetHeight(dib1), dib2, 0, 0);
}


void
FreeImage_AddAlphaMask(void *dib, void *mask) {	
	if ((FreeImage_GetBPP(dib) == 32) && (FreeImage_GetBPP(mask) == 8)) {
		unsigned width  = min(FreeImage_GetWidth(dib), FreeImage_GetWidth(mask));
		unsigned height = min(FreeImage_GetHeight(dib), FreeImage_GetHeight(mask));

		for (unsigned rows = 0; rows < height; rows++) {
			BYTE *bits_mask = FreeImage_GetScanLine(mask, rows);
			RGBQUAD *bits   = (RGBQUAD *)FreeImage_GetScanLine(dib, rows);

			for (unsigned cols = 0; cols < width; cols++) {
				bits[cols].rgbReserved = bits_mask[cols];
			}
		}
	}
}

// ----------------------------------------------------------
//   blurring
// ----------------------------------------------------------

void
FreeImage_Blur(void *dib) {
	if (dib) {
		int pitch = FreeImage_GetPitch(dib);

		switch (FreeImage_GetBPP(dib)) {
			case 24 :
			{
				// calculate a nice convolution mask

				int mask[] = { (0 - pitch) + (0 - sizeof(RGBTRIPLE)), (0 - pitch), (0 - pitch) + sizeof(RGBTRIPLE), (0 - sizeof(RGBTRIPLE)), 0, sizeof(RGBTRIPLE), pitch + (0 - sizeof(RGBTRIPLE)), pitch, pitch + sizeof(RGBTRIPLE) };
				int conv_mask[] = { 3, 3, 3, 3, 10, 3, 3, 3, 3 };
						
				// clone the bitmap

				void *clone = FreeImage_Clone(dib);

				// do the blur thingie

				for (unsigned y = 1; y < FreeImage_GetHeight(dib) - 1; y++) {
					BYTE *clone_bits = FreeImage_GetScanLine(clone, y);
					BYTE *bits = FreeImage_GetScanLine(dib, y);

					for (unsigned x = 1; x < FreeImage_GetWidth(dib) - 1; x++) {
						// add all pixels and divide them by the total weight of the convolution mask

						int convolution_red = 0;
						int convolution_green = 0;
						int convolution_blue = 0;

						for (int conv = 0; conv < 9; conv++) {
							convolution_red += ((RGBTRIPLE *)(clone_bits + mask[conv]))->rgbtRed * conv_mask[conv];
							convolution_green += ((RGBTRIPLE *)(clone_bits + mask[conv]))->rgbtGreen * conv_mask[conv];
							convolution_blue += ((RGBTRIPLE *)(clone_bits + mask[conv]))->rgbtBlue * conv_mask[conv];
						}

						((RGBTRIPLE *)bits)->rgbtRed = convolution_red / 34;
						((RGBTRIPLE *)bits)->rgbtGreen = convolution_green / 34;
						((RGBTRIPLE *)bits)->rgbtBlue = convolution_blue / 34;

						bits += sizeof(RGBTRIPLE);
						clone_bits += sizeof(RGBTRIPLE);
					}
				}

				FreeImage_Free(clone);
			}
		}
	}
}

// ----------------------------------------------------------
//   cropping
// ----------------------------------------------------------

void *
FreeImage_Crop(void *dib, int left, int top, int right, int bottom) {
	if (dib) {
		if (FreeImage_GetBPP(dib) >= 8) {
			if ((right > left) && (bottom > top)) {
				BYTE *clip = (BYTE *)FreeImage_Allocate(right - left, bottom - top, FreeImage_GetBPP(dib));
				BYTE *bits = FreeImage_GetBits(dib) + ((FreeImage_GetHeight(dib) - top - (bottom - top)) * FreeImage_GetPitch(dib));		
				BYTE *clip_bits = FreeImage_GetBits(clip);

				int line = CalculateLine(right - left, FreeImage_GetBPP(dib));
				int pitch = CalculatePitch(line);
				int line_large = CalculateLine(FreeImage_GetWidth(dib), FreeImage_GetBPP(dib));
				int pitch_large = CalculatePitch(line_large);

				switch (FreeImage_GetBPP(dib)) {
					case 8 :
					{
						// copy the palette

						memcpy(FreeImage_GetPalette(clip), FreeImage_GetPalette(dib), FreeImage_GetColorsUsed(dib) * sizeof(RGBQUAD));

						// copy the bits

						for (int y = 0; y < bottom - top; y++)
							memcpy(clip_bits + y * pitch, bits + (y * pitch_large) + left, line);

						break;
					}

					case 16 :
					{
						for (int y = 0; y < bottom - top; y++)
							memcpy(clip_bits + y * pitch, bits + (y * pitch_large) + (left * sizeof(WORD)), line);

						break;
					}

					case 24 :
					{
						for (int y = 0; y < bottom - top; y++)
							memcpy(clip_bits + y * pitch, bits + (y * pitch_large) + (left * sizeof(RGBTRIPLE)), line);

						break;
					}

					case 32 :
					{
						for (int y = 0; y < bottom - top; y++)
							memcpy(clip_bits + y * pitch, bits + (y * pitch_large) + (left * sizeof(RGBQUAD)), line);

						break;
					}
				}

				return clip;
			}
		}
	}

	return NULL;
}

// ----------------------------------------------------------
//   darkening/brightening
// ----------------------------------------------------------

void
FreeImage_Brighten(void *dib, double factor) {
	if (dib) {
		switch(FreeImage_GetBPP(dib)) {
			case 24 :
			{
				for (unsigned y = 0; y < FreeImage_GetHeight(dib); y++) {
					RGBTRIPLE *bits = (RGBTRIPLE *)(FreeImage_GetBits(dib) + (y * FreeImage_GetPitch(dib)));

					for (unsigned x = 0; x < FreeImage_GetWidth(dib); x++) {
						if ((bits->rgbtRed * factor > 255) || (bits->rgbtRed * factor < bits->rgbtRed)) {
							bits->rgbtRed = 255;
						} else {
							bits->rgbtRed *= factor;
						}

						if ((bits->rgbtGreen * factor > 255) || (bits->rgbtGreen * factor < bits->rgbtGreen)) {
							bits->rgbtGreen = 255;
						} else {
							bits->rgbtGreen *= factor;
						}

						if ((bits->rgbtBlue * factor > 255) || (bits->rgbtBlue * factor < bits->rgbtBlue)) {
							bits->rgbtBlue = 255;
						} else {
							bits->rgbtBlue *= factor;
						}

						bits++;
					}
				}
			}
		}
	}
}

void
FreeImage_Darken(void *dib, double factor) {
	if (dib) {
		switch(FreeImage_GetBPP(dib)) {
			case 24 :
			{
				for (unsigned y = 0; y < FreeImage_GetHeight(dib); y++) {
					RGBTRIPLE *bits = (RGBTRIPLE *)(FreeImage_GetBits(dib) + (y * FreeImage_GetPitch(dib)));

					for (unsigned x = 0; x < FreeImage_GetWidth(dib); x++) {
						bits->rgbtRed /= factor;
						bits->rgbtGreen /= factor;
						bits->rgbtBlue /= factor;

						bits++;
					}
				}
			}
		}
	}
}

// ----------------------------------------------------------
//   color inverting
// ----------------------------------------------------------

void
FreeImage_Invert(void *dib) {
	WORD x, y;
	BYTE *bits;

	if (!dib) {
		return;
	}
	
	switch(FreeImage_GetBPP(dib))
	{
        case 1 :
		case 4 :
		case 8 :
		{
			// If the dib has a colormap, just invert it

			if (FreeImage_GetColorType(dib) == FIC_PALETTE) {
				RGBQUAD *pal = FreeImage_GetPalette(dib);

				for (WORD i = 0; i < FreeImage_GetColorsUsed(dib); i++) {
					pal[i].rgbRed	= 255 - pal[i].rgbRed;
					pal[i].rgbGreen = 255 - pal[i].rgbGreen;
					pal[i].rgbBlue	= 255 - pal[i].rgbBlue;
				}
			} else {
				WORD pitch = FreeImage_GetPitch(dib);

				for(y = 0; y < FreeImage_GetHeight(dib); y++) {
					bits = FreeImage_GetBits(dib) + y * pitch;

					for (x = 0; x < FreeImage_GetLine(dib); x++) {
						bits[x] = ~bits[x];
					}
				}
			}

			break;
		}		

		case 24 :
		{
			bits = FreeImage_GetBits(dib);

			for(y = 0; y < FreeImage_GetHeight(dib); y++) {
				for(x = 0; x < FreeImage_GetWidth(dib); x++) {
					bits[0] = ~bits[0];
					bits[1] = ~bits[1];
					bits[2] = ~bits[2];

					bits += 3;
				}
			}

			break;
		}
		
		case 32 :
		{
			bits = FreeImage_GetBits(dib);

			for (y = 0; y < FreeImage_GetHeight(dib); y++) {
				for (x = 0; x < FreeImage_GetWidth(dib); x++) {
					bits[0] = ~bits[0];
					bits[1] = ~bits[1];
					bits[2] = ~bits[2];

					bits += 4;
				}
			}

			break;
		}
	}
}

// ----------------------------------------------------------
//   rotation
// ----------------------------------------------------------

template<class T>
void
FreeImage_RotateLine(void *dib, T *DstLine, double angle, int y) {
	int TransX = FreeImage_GetWidth(dib)  / 2;
	int TransY = FreeImage_GetHeight(dib) / 2;

	double SinAngle = sin(angle * pi() / 180.0);
	double CosAngle = cos(angle * pi() / 180.0);

	for (unsigned x = 0; x < FreeImage_GetWidth(dib); x++) {
		int xc = x - TransX;
		int yc = y - TransY;

		int SrcX = xc * CosAngle - yc * SinAngle + TransX;
		int SrcY = xc * SinAngle + yc * CosAngle + TransY;

		if (SrcX < 0 || SrcX >= static_cast<int>(FreeImage_GetWidth(dib)) || 
			SrcY < 0 || SrcY >= static_cast<int>(FreeImage_GetHeight(dib)))
			memset(DstLine++, 0, sizeof(T));
		else
			*DstLine++ = *(reinterpret_cast<T *>(FreeImage_GetScanLine(dib, SrcY) + SrcX * sizeof(T)));
	}
}

void *
FreeImage_Rotate(void *dib, double angle) {
	if (dib) {
		// normalize the angle

		if (angle >= 0) {
			while (angle >= 360) {
				angle -= 360;
			}
		} else {
			while (angle < -360) {
				angle += 360;
			}

			angle = 360 + angle;
		}

		// rotate lines

		switch(FreeImage_GetBPP(dib)) {
			case 8 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), FreeImage_GetBPP(dib));

				memcpy(FreeImage_GetPalette(new_dib), FreeImage_GetPalette(dib), FreeImage_GetColorsUsed(dib) * sizeof(RGBQUAD));

				for (unsigned y = 0; y < FreeImage_GetHeight(new_dib); y++)
					FreeImage_RotateLine(dib, reinterpret_cast<BYTE *>(FreeImage_GetScanLine(new_dib, y)), angle, y);				

				return new_dib;
			}

			case 16 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), FreeImage_GetBPP(dib));

				for (unsigned y = 0; y < FreeImage_GetHeight(new_dib); y++)
					FreeImage_RotateLine(dib, reinterpret_cast<WORD *>(FreeImage_GetScanLine(new_dib, y)), angle, y);

				return new_dib;
			}

			case 24 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), FreeImage_GetBPP(dib));

				for (unsigned y = 0; y < FreeImage_GetHeight(new_dib); y++)
					FreeImage_RotateLine(dib, reinterpret_cast<RGBTRIPLE *>(FreeImage_GetScanLine(new_dib, y)), angle, y);

				return new_dib;
			}

			case 32 :
			{
				void *new_dib = FreeImage_Allocate(FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), FreeImage_GetBPP(dib));

				for (unsigned y = 0; y < FreeImage_GetHeight(new_dib); y++)
					FreeImage_RotateLine(dib, reinterpret_cast<RGBQUAD *>(FreeImage_GetScanLine(new_dib, y)), angle, y);

				return new_dib;
			}

		}
	}

	return NULL;
}

#endif

