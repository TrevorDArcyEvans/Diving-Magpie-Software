// ==========================================================
// FreeImage Test Script
//
// Design and implementation by Floris van den Berg
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <assert.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "FreeImage.h"

void
Output(FREE_IMAGE_FORMAT fif, const char *message) {
	OutputDebugString(message);
	OutputDebugString("\n");
}

// ----------------------------------------------------------
int __cdecl
main(int argc, char *argv[]) {
	void *dib = NULL;
	int id = 1;

	FreeImage_SetOutputMessage(Output);

	printf(FreeImage_GetVersion());
	printf(FreeImage_GetCopyrightMessage());

	// open the log file

	FILE *log_file = fopen("log_file.txt", "w");

	// batch convert all supported bitmaps

	_finddata_t finddata;

	long handle;

	if ((handle = _findfirst("e:\\projects\\images\\*.*", &finddata)) != -1) {
		do {
			dib = NULL;

			// grab the extension

			char *ext = new char[4];
			ext[3] = 0;
			strncpy(ext, finddata.name + strlen(finddata.name) - 3, 3);

			// make a path to a directory

			char *directory = new char[128];
			strcpy(directory, "e:\\projects\\images\\");
			strcat(directory, finddata.name);

			// make a unique filename

			char *unique = new char[128];
			itoa(id, unique, 10);
			strcat(unique, ".jpg");

			// open the file

			switch(FreeImage_GetFileTypeFromExt(ext)) {
				case FIF_BMP :
					dib = FreeImage_LoadBMP(directory, BMP_DEFAULT);
					break;

				case FIF_ICO :
					dib = FreeImage_LoadICO(directory, ICO_DEFAULT);
					break;

				case FIF_JPEG :
					dib = FreeImage_LoadJPEG(directory, JPEG_DEFAULT);
					break;

				case FIF_KOALA :
					dib = FreeImage_LoadKOALA(directory, KOALA_DEFAULT);
					break;

				case FIF_PCD :
					dib = FreeImage_LoadPCD(directory, PCD_DEFAULT);
					break;

				case FIF_PCX :
					dib = FreeImage_LoadPCX(directory, PCX_DEFAULT);
					break;

				case FIF_PNG :
					dib = FreeImage_LoadPNG(directory, PNG_DEFAULT);
					break;

				case FIF_PBM :
				case FIF_PGM :
				case FIF_PPM :
					dib = FreeImage_LoadPNM(directory, PNM_DEFAULT);
					break;

				case FIF_RAS :
					dib = FreeImage_LoadRAS(directory, RAS_DEFAULT);
					break;

				case FIF_TARGA :
					dib = FreeImage_LoadTARGA(directory, TARGA_DEFAULT);
					break;

				case FIF_TIFF :
					dib = FreeImage_LoadTIFF(directory, TIFF_DEFAULT);
					break;
			};

			if (dib != NULL) {
				FreeImage_SaveJPEG(dib, unique, JPEG_QUALITYSUPERB);

				FreeImage_Free(dib);

				fwrite(unique, strlen(unique), 1, log_file);
				fwrite(" >> ", 4, 1, log_file);
				fwrite(directory, strlen(directory), 1, log_file);
				fwrite("\n", 1, 1, log_file);

				id++;
			}

			delete [] unique;
			delete [] directory;
			delete [] ext;

		} while (_findnext(handle, &finddata) == 0);

		_findclose(handle);
	}

	fclose(log_file);

	return 0;
}