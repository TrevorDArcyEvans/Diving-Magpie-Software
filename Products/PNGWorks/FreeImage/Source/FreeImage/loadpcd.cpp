// ==========================================================
// Kodak PhotoCD Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// 
// Based on pascal code developed by Alex Kwak
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#pragma warning (disable : 4244)

#include <stdlib.h>
#include <memory.h> 

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef PCD_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

void
YUV2RGB(int y, int cb, int cr, int &r, int &g, int &b) {
	const float c = 256;

	float c11 = 0.0054980  * c;
	float c12 = 0.0000001  * c;
	float c13 = 0.0051681  * c;
	float c21 = 0.0054980  * c;
	float c22 = -0.0015446 * c;
	float c23 = -0.0026325 * c;
	float c31 = 0.0054980  * c;
	float c32 = 0.0079533  * c;
	float c33 = 0.0000001  * c;

	r = round(c11 * y + c12 * (cb - 156) + c13 * (cr - 137));
	g = round(c21 * y + c22 * (cb - 156) + c23 * (cr - 137));
	b = round(c31 * y + c32 * (cb - 156) + c33 * (cr - 137));

	if (r < 0) {
		r = 0;
	}

	if (g < 0) {
		g = 0;
	}

	if (b < 0) {
		b = 0;
	}

	if (r > 255) {
		r = 255;
	}

	if (g > 255) {
		g = 255;
	}

	if (b > 255) {
		b = 255;
	}
}

BOOL
VerticalOrientation(FreeImageIO *io, fi_handle handle) {
	char buffer[128];

	io->read_proc(buffer, 128, 1, handle);

	return (buffer[72] & 63) == 8;
}

// ----------------------------------------------------------
//   PCD Loading
// ----------------------------------------------------------

void *
FreeImage_LoadPCD(const char *filename, PCDFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadPCDFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadPCDFromHandle(FreeImageIO *io, fi_handle handle, PCDFlags flags) {
	int width;
	int height;
	int line;
	int pitch;
	int bpp = 24;
	int scan_line_add   = 1;
	int start_scan_line = 0;

	// we use this offset value to make seemingly absolute seeks relative in the file
	
	long offset_in_file = io->tell_proc(handle);
	long seek;

	switch (flags) {
		case PCD_BASEDIV4 :
			seek = 0x2000;
			width = 192;
			height = 128;
			line = CalculateLine(width, bpp);
			pitch = CalculatePitch(line);
			break;

		case PCD_BASEDIV16 :
			seek = 0xB800;
			width = 384;
			height = 256;
			line = CalculateLine(width, bpp);
			pitch = CalculatePitch(line);
			break;

		default :
			seek = 0x30000;
			width = 768;
			height = 512;
			line = CalculateLine(width, bpp);
			pitch = CalculatePitch(line);
			break;
	}

	// allocate the dib and write out the header

	BYTE *dib = (BYTE *)FreeImage_Allocate(width, height, bpp);
	
	// check if the PCD is bottom-up

	if (VerticalOrientation(io, handle)) {
		scan_line_add = -1;
		start_scan_line = height - 1;		
	}

	// temporary stuff to load PCD

	BYTE *y1   = (BYTE *)malloc(width);
	BYTE *y2   = (BYTE *)malloc(width);
	BYTE *cbcr = (BYTE *)malloc(width);
	
	io->seek_proc(handle, offset_in_file, SEEK_SET);
	io->seek_proc(handle, seek, SEEK_CUR);

	for (int y = 0; y < (height / 2); y++) {
		io->read_proc(y1, width, 1, handle);
		io->read_proc(y2, width, 1, handle);
		io->read_proc(cbcr, width, 1, handle);

		int r, g, b;		

		for (int x = 0; x < width; x++) {
			YUV2RGB(y1[x], cbcr[x / 2], cbcr[(width / 2) + (x / 2)], r, g, b);

			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 0) = b;
			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 1) = g;
			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 2) = r;
		}

		start_scan_line += scan_line_add;
		
		for (x = 0; x < width; x++) {
			YUV2RGB(y2[x], cbcr[x / 2], cbcr[(width / 2) + (x / 2)], r, g, b);

			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 0) = b;
			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 1) = g;
			*(FreeImage_GetScanLine(dib, start_scan_line) + (x * 3) + 2) = r;
		}

		start_scan_line += scan_line_add;
	}

	free(cbcr);
	free(y2);
	free(y1);

	return dib;
}

#endif
