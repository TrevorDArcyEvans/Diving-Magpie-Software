// ==========================================================
// ICO Loader
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <stdlib.h>

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#ifdef ICO_ENABLED

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

#pragma pack(push, 1)

typedef struct tagIconDirectoryEntry {
    BYTE  bWidth;
    BYTE  bHeight;
    BYTE  bColorCount;
    BYTE  bReserved;
    WORD  wPlanes;
    WORD  wBitCount;
    DWORD dwBytesInRes;
    DWORD dwImageOffset;
} ICONDIRENTRY;

typedef struct tagIconDir {
    WORD          idReserved;
    WORD          idType;
    WORD          idCount;
} ICONHEADER;

#pragma pack(pop)

// ----------------------------------------------------------
//   ICON Loading
// ----------------------------------------------------------

void *
FreeImage_LoadICO(const char *filename, ICOFlags flags) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		void *dib = FreeImage_LoadICOFromHandle(&io, (fi_handle)handle, flags);

		fclose(handle);

		return dib;
	}

	return NULL;
}

// ----------------------------------------------------------

void *
FreeImage_LoadICOFromHandle(FreeImageIO *io, fi_handle handle, ICOFlags flags) {
	if (handle) {
		BYTE *dib;

		// we use this offset value to make seemingly absolute seeks relative in the file
		
		long start_of_file = io->tell_proc(handle);

		// read the icon header

		ICONHEADER icon_header;

		io->read_proc(&icon_header, sizeof(ICONHEADER), 1, handle);

		if ((icon_header.idReserved == 0) && (icon_header.idType == 1)) {

			ICONDIRENTRY *icon_list = (ICONDIRENTRY *)malloc(icon_header.idCount * sizeof(ICONDIRENTRY));

			// load the icon descriptions

			for (int c = 0; c < icon_header.idCount; c++)
				io->read_proc(icon_list + c, sizeof(ICONDIRENTRY), 1, handle);
			
			if (static_cast<int>(flags) < icon_header.idCount) {
				// calculate the bit count for the colors in the bitmap
				
				int bit_count = 1;
				int colors_used = icon_list[static_cast<int>(flags)].bColorCount;

				while (CalculateUsedColors(bit_count) != colors_used)
					bit_count++;
							
				int width  = icon_list[static_cast<int>(flags)].bWidth;
				int height = icon_list[static_cast<int>(flags)].bHeight;
				int line   = CalculateLine(width, bit_count);
				int pitch  = CalculatePitch(line);

				// allocate memory for one icon

				dib = (BYTE *)FreeImage_Allocate(width, height, bit_count);

				if (dib == NULL)
					return NULL;

				// find the icon and skip the infoheader

				io->seek_proc(handle, start_of_file, SEEK_SET);
				io->seek_proc(handle, icon_list[static_cast<int>(flags)].dwImageOffset, SEEK_CUR);
				io->seek_proc(handle, sizeof(BITMAPINFOHEADER), SEEK_CUR);

				// read the palette data

				RGBQUAD *quad = FreeImage_GetPalette(dib);

				for (int c = 0; c < colors_used; c++) {			
					io->read_proc(quad++, sizeof(RGBQUAD), 1, handle);
				}

				// apply the AND and XOR masks

				BYTE *xor_mask     = (BYTE *)malloc(pitch * height);
				BYTE *and_mask     = (BYTE *)malloc(pitch * height);
				BYTE *old_xor_mask = xor_mask;
				BYTE *old_and_mask = and_mask;

				io->read_proc(xor_mask, pitch * height, 1, handle);
				io->read_proc(and_mask, pitch * height, 1, handle);

				for (int row = 0; row < height; row++) {
					for (int column = 0; column < line; column++) {
						*(FreeImage_GetScanLine(dib, row) + column) &= and_mask[column];
						*(FreeImage_GetScanLine(dib, row) + column) ^= xor_mask[column];
					}

					xor_mask += pitch;
					and_mask += pitch;
				}

				free(old_and_mask);
				free(old_xor_mask);

				// bitmap has been loaded successfully!

				return (void *)dib;
			}
		}
	} else {
		if (FreeImage_OutputMessage)
			FreeImage_OutputMessage(FIF_ICO, "file is not an ICO file");
	}

	return NULL;
}

#endif
