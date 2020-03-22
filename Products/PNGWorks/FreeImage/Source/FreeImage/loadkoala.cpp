// ==========================================================
// KOALA Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef KOALA_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

const int CBM_WIDTH = 320;
const int CBM_HEIGHT = 200;

BYTE pixel_mask[4]         = { 0xc0, 0x30, 0x0c, 0x03 };
BYTE pixel_displacement[4] = { 6, 4, 2, 0 };

unsigned char g_load_address[2];	// highbit, lowbit

// ----------------------------------------------------------

#pragma pack(push, 1)

typedef struct tagKOALA {
	BYTE image[8000];		// pixmap image
	BYTE colour1[1000];		// first colourmap (colour 1 and 2)
	BYTE colour2[1000];		// second colourmap (colour 3)
	BYTE background;		// background colour
} koala_t;

struct colour_t { 
	int	r;
	int g;
	int b;	
};

#pragma pack(pop)

// ----------------------------------------------------------

const colour_t c64colours[16] = {
	{   0,   0,   0 },	// Black
	{ 255, 255, 255 },	// White
	{ 170,  17,  17 },	// Red
	{  12, 204, 204 },	// Cyan
	{ 221,  51, 221 },	// Purple
	{  0,  187,  0 },	// Green
	{   0,   0, 204 },	// Blue
	{ 255, 255, 140 },	// Yellow
	{ 204, 119,  34 },	// Orange
	{ 136,  68,   0 },	// Brown
	{ 255, 153, 136 },	// Light red
	{  92,  92,  92 },	// Gray 1
	{ 170, 170, 170 },	// Gray 2
	{ 140, 255, 178 },	// Light green
	{  39, 148, 255 },	// Light blue
	{ 196, 196, 196 }	// Gray 3
};

// ----------------------------------------------------------
//   KOALA Loading
// ----------------------------------------------------------

void *
FreeImage_LoadKOALA(const char *filename, KOALAFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadKOALAFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadKOALAFromHandle(FreeImageIO *io, fi_handle handle, KOALAFlags flags) {
	if (handle) {
		koala_t image;

		int	pixel, index, colourindex;

		// read the load address

		io->read_proc(&g_load_address, 1, 2, handle);

		// if the load address is correct, skip it. otherwise ignore the load address

		if ((g_load_address[0] != 0x00) || (g_load_address[1] != 0x60)) {
			((BYTE *)&image)[0] = g_load_address[0];
			((BYTE *)&image)[1] = g_load_address[1];

			io->read_proc((BYTE *)&image + 2, 1, 10001 - 2, handle);
		} else {
			io->read_proc(&image, 1, 10001, handle);
		}		

		// build DIB in memory

		BYTE *dib = (BYTE *)FreeImage_Allocate(CBM_WIDTH, CBM_HEIGHT, 4);

		if (dib) {
			// write out the Commodore 64 color palette

			RGBQUAD *palette = FreeImage_GetPalette(dib);

			for (int i = 0; i < 16; i++) {
				palette[i].rgbBlue = c64colours[i].b;
				palette[i].rgbGreen = c64colours[i].g;
				palette[i].rgbRed = c64colours[i].r;
			}

			// write out bitmap data

			unsigned char found_color = 0;

			for (int y = 0; y < 200; y++) {
				for (int x = 0; x < 160; x++) {

					// Get value of pixel at (x,y)

					index = (x / 4) * 8 + (y % 8) + (y / 8) * CBM_WIDTH;
					colourindex = (x / 4) + (y / 8) * 40;
					pixel = (image.image[index] & pixel_mask[x % 4]) >> pixel_displacement[x % 4];

					// Retrieve RGB values

					switch (pixel) {
						case 0: // Background
							found_color = image.background;
							break;
							
						case 1: // Colour 1
							found_color = image.colour1[colourindex] >> 4;
							break;
							
						case 2: // Colour 2
							found_color = image.colour1[colourindex] & 0xf;
							break;
							
						case 3: // Colour 3
							found_color = image.colour2[colourindex] & 0xf;
							break;
					};

					*(FreeImage_GetScanLine(dib, CBM_HEIGHT - y - 1) + x) = (found_color << 4) | found_color;
				}
			}

			return dib;
		}
	}

	return NULL;
}

#endif
