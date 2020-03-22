// ==========================================================
// FreeImage implementation
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Hervé Drolon (drolon@iut.univ-lehavre.fr)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#pragma warning (disable : 4786)

#include <stdlib.h>
#include <windows.h>

#include "FreeImage.h"
#include "Common.h"

//----------------------------------------------------------------------

static const char *g_version = "1.4.4";
static const char *g_copyright = "This program uses FreeImage, an open source image library supporting all common bitmap formats. Get your free copy now from http://home.wxs.nl/~flvdberg.";

//----------------------------------------------------------------------

BOOL APIENTRY
DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH :
		case DLL_THREAD_ATTACH  :
		case DLL_THREAD_DETACH  :
		case DLL_PROCESS_DETACH :
			break;
    }

    return TRUE;
}

//----------------------------------------------------------------------

const char *
FreeImage_GetVersion() {
	return g_version;
}

const char *
FreeImage_GetCopyrightMessage() {
	return g_copyright;
}

//----------------------------------------------------------------------

FreeImage_OutputMessageFunction FreeImage_OutputMessage = NULL;

void
FreeImage_SetOutputMessage(FreeImage_OutputMessageFunction omf) {
	FreeImage_OutputMessage = omf;
}

//----------------------------------------------------------------------

FREE_IMAGE_COLOR_TYPE
FreeImage_GetColorType(void *dib) {
	RGBQUAD *rgb;

	switch (FreeImage_GetBPP(dib)) {
		case 1:
		{
			rgb = FreeImage_GetPalette(dib);

			if ((rgb->rgbRed == 0) && (rgb->rgbGreen == 0) && (rgb->rgbBlue == 0)) {
				return FIC_MINISBLACK;
			} else {
				return FIC_MINISWHITE;
			}
		}

		case 8:	// Check if the DIB has a color or a greyscale palette
		{
			rgb = FreeImage_GetPalette(dib);

			for (unsigned i = 0; i < FreeImage_GetColorsUsed(dib); i++) {
				if ((rgb->rgbRed != rgb->rgbGreen) || (rgb->rgbRed != rgb->rgbBlue)) {
					return FIC_PALETTE;
				}
				// The DIB has a color palette if the greyscale isn't a linear ramp
				if (rgb->rgbRed != i) {
					return FIC_PALETTE;
				}

				rgb++;
			}

			return FIC_MINISBLACK;
		}
		
		case 24:
			return FIC_RGB;
			
		default :
			return FIC_MINISBLACK;
	}
}

//----------------------------------------------------------------------

unsigned
FreeImage_GetWidth(void *dib) {
	return dib ? FreeImage_GetInfoHeader(dib)->biWidth : 0;
}

unsigned
FreeImage_GetHeight(void *dib) {
	if (dib) {
		int height = FreeImage_GetInfoHeader(dib)->biHeight;

		return (height < 0) ? - height : height;
	} else {
		return 0;
	}
}

unsigned
FreeImage_GetBPP(void *dib) {
	return dib ? FreeImage_GetInfoHeader(dib)->biBitCount : 0;
}

unsigned
FreeImage_GetLine(void *dib) {
	return dib ? ((FreeImage_GetWidth(dib) * FreeImage_GetBPP(dib)) + 7) / 8 : 0;
}

unsigned
FreeImage_GetPitch(void *dib) {
	return dib ? FreeImage_GetLine(dib) + 3 & ~3 : 0;
}

unsigned
FreeImage_GetColorsUsed(void *dib) {
	return dib ? FreeImage_GetInfoHeader(dib)->biClrUsed : 0;
}

BYTE *
FreeImage_GetBits(void *dib) {
	return dib ? (((BYTE *)FreeImage_GetInfoHeader(dib)) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * FreeImage_GetInfoHeader(dib)->biClrUsed) : NULL;
}

BYTE *
FreeImage_GetBitsRowCol(void *dib, int col, int row) {
	int width = FreeImage_GetWidth(dib);

	if (FreeImage_GetBPP(dib) == 4)
		width /= 2;
	else if (FreeImage_GetBPP(dib) == 1)
		width /= 8;

	return FreeImage_GetBits(dib) + ((FreeImage_GetHeight(dib) - row - 1) * FreeImage_GetPitch(dib)) + (col * FreeImage_GetBPP(dib) / 8);
}

BYTE *
FreeImage_GetScanLine(void *dib, int scanline) {
	return (FreeImage_GetBits(dib) + FreeImage_GetPitch(dib) * scanline);
}

unsigned
FreeImage_GetDIBSize(void *dib) {
	int dib_size = sizeof(BITMAPINFOHEADER);
	dib_size += FreeImage_GetColorsUsed(dib) * sizeof(RGBQUAD);
	dib_size += FreeImage_GetPitch(dib) * FreeImage_GetHeight(dib);

	return dib_size;
}

void *
FreeImage_Allocate(int width, int height, int bpp) {
	// allocate a DIB

	int dib_size = sizeof(FREEIMAGEHEADER) + sizeof(BITMAPINFOHEADER);
	dib_size += sizeof(RGBQUAD) * CalculateUsedColors(bpp);
	dib_size += CalculatePitch(CalculateLine(width, bpp)) * height;

	BYTE *dib = (BYTE *)malloc(dib_size);

	if (dib) {
		memset(dib, 0, dib_size);

		// write out the BITMAPINFOHEADER

		BITMAPINFOHEADER *bih = FreeImage_GetInfoHeader(dib);

		bih->biSize           = sizeof(BITMAPINFOHEADER);
		bih->biWidth          = width;
		bih->biHeight         = abs(height);
		bih->biPlanes         = 1;
		bih->biCompression    = 0;
		bih->biBitCount       = bpp;
		bih->biClrUsed        = CalculateUsedColors(bpp);
		bih->biClrImportant   = CalculateUsedColors(bpp);

		return (void *)dib;
	}

	return NULL;
}

void
FreeImage_Free(void *dib) {
	free(dib);

	dib = NULL;
}

void
FreeImage_Unload(void *dib) {
	FreeImage_Free(dib);
}

RGBQUAD *
FreeImage_GetPalette(void *dib) {
	return (dib && FreeImage_GetBPP(dib) < 16) ? (RGBQUAD *)((BYTE *)dib + sizeof(FREEIMAGEHEADER) + sizeof(BITMAPINFOHEADER)) : NULL;
}

unsigned
FreeImage_GetDotsPerMeterX(void *dib) {
	return FreeImage_GetInfoHeader(dib)->biXPelsPerMeter;
}

unsigned
FreeImage_GetDotsPerMeterY(void *dib) {
	return FreeImage_GetInfoHeader(dib)->biYPelsPerMeter;
}

BITMAPINFOHEADER *
FreeImage_GetInfoHeader(void *dib) {
	return dib ? (BITMAPINFOHEADER *)((BYTE *)dib + sizeof(FREEIMAGEHEADER)) : NULL;
}

BITMAPINFO *
FreeImage_GetInfo(void *dib) {
	return dib ? (BITMAPINFO *)((BYTE *)dib + sizeof(FREEIMAGEHEADER)) : NULL;
}

//----------------------------------------------------------------------

BYTE *
FreeImage_GetTransparencyTable(void *dib) {
	return dib ? ((FREEIMAGEHEADER *)dib)->transparent_table : NULL;
}

void
FreeImage_SetTransparencyTable(void *dib, BYTE *table, BYTE count) {
	if (dib) {
		((FREEIMAGEHEADER *)dib)->transparency_count = count;

		if (table != NULL) {
			memcpy(((FREEIMAGEHEADER *)dib)->transparent_table, table, count);
		} else {
			memset(((FREEIMAGEHEADER *)dib)->transparent_table, 0xff, count);
		}
	}
}

unsigned
FreeImage_GetTransparencyCount(void *dib) {
	return dib ? ((FREEIMAGEHEADER *)dib)->transparency_count: 0;
}

