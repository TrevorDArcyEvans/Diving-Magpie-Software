// ==========================================================
// GetType
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include <string.h>

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

FREE_IMAGE_FORMAT
FreeImage_GetFileType(const char *filename, int size) {
	FreeImageIO io;
	SetDefaultIO(&io);
	
	FILE *handle = fopen(filename, "rb");

	if (handle) {
		FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)handle, size);

		fclose(handle);

		return format;
	} else {
		return FIF_UNKNOWN;
	}
}

// ----------------------------------------------------------

FREE_IMAGE_FORMAT
FreeImage_GetFileTypeFromHandle(FreeImageIO *io, fi_handle handle, int size) {
	if (handle) {
		BYTE id[16];

		if (size > 16) {
			size = 16;
		}

		io->read_proc(id, 1, size, handle);
		io->seek_proc(handle, -size, SEEK_CUR);

		// description of all the formats
		// note : there is no reliable way to identify TARGA, PhotoCD, ICO and KOALA
				
		BYTE bmp_id[]   = { 0x42, 0x4D };
		BYTE jpeg_id[]  = { 0xFF, 0xD8 };
		BYTE koala_id[] = { 0x00, 0x60 };
		BYTE pbm_id1[]  = { 0x50, 0x31 };
		BYTE pbm_id2[]  = { 0x50, 0x34 };
		BYTE pcx_id[]   = { 0x0A };
		BYTE pgm_id1[]  = { 0x50, 0x32 };
		BYTE pgm_id2[]  = { 0x50, 0x35 };
		BYTE png_id[]   = { 137, 80, 78, 71, 13, 10, 26, 10 };
		BYTE ppm_id1[]  = { 0x50, 0x33 };
		BYTE ppm_id2[]  = { 0x50, 0x36 };
		BYTE ras_id[]	= { 0x59, 0xA6, 0x6A, 0x95 };
		BYTE tiff_id1[] = { 0x49, 0x49 };
		BYTE tiff_id2[] = { 0x4D, 0x4D };

		if ((size >= sizeof(bmp_id)) && (memcmp(id, bmp_id, sizeof(bmp_id)) == 0)) {
			return FIF_BMP;
		}

		if ((size >= sizeof(jpeg_id)) && (memcmp(id, jpeg_id, sizeof(jpeg_id)) == 0)) {
			return FIF_JPEG;
		}

		if ((size >= sizeof(koala_id)) && (memcmp(id, koala_id, sizeof(koala_id)) == 0)) {
			return FIF_KOALA;
		}

		if ((size >= sizeof(pbm_id1)) && ((memcmp(id, pbm_id1, sizeof(pbm_id1)) == 0) || (memcmp(id, pbm_id2, sizeof(pbm_id2)) == 0))) {
			return FIF_PBM;
		}		

		if ((size >= sizeof(pcx_id)) && (memcmp(id, pcx_id, sizeof(pcx_id)) == 0)) {
			return FIF_PCX;
		}

		if ((size >= sizeof(pgm_id1)) && ((memcmp(id, pgm_id1, sizeof(pgm_id1)) == 0) || (memcmp(id, pgm_id2, sizeof(pgm_id2)) == 0))) {
			return FIF_PGM;
		}		
		
		if ((size >= sizeof(png_id)) && (memcmp(id, png_id, sizeof(png_id)) == 0)) {
			return FIF_PNG;
		}

		if ((size >= sizeof(ppm_id1)) && ((memcmp(id, ppm_id1, sizeof(ppm_id1)) == 0) || (memcmp(id, ppm_id2, sizeof(ppm_id2)) == 0))) {
			return FIF_PPM;
		}		

		if ((size >= sizeof(ras_id)) && (memcmp(id, ras_id, sizeof(ras_id)) == 0)) {
			return FIF_RAS;
		}

		if ((size >= sizeof(tiff_id1)) && ((memcmp(id, tiff_id1, sizeof(tiff_id1)) == 0) || (memcmp(id, tiff_id2, sizeof(tiff_id2)) == 0))) {
			return FIF_TIFF;
		}
	}

	return FIF_UNKNOWN;
}

// ----------------------------------------------------------

FREE_IMAGE_FORMAT
FreeImage_GetFileTypeFromExt(const char *ext) {
	if (stricmp(ext, "BMP") == 0)
		return FIF_BMP;

	if (stricmp(ext, "ICO") == 0)
		return FIF_ICO;

	if ((stricmp(ext, "JPEG") == 0) || (stricmp(ext, "JPG") == 0) || (stricmp(ext, "JIF") == 0) || (stricmp(ext, "JFIF") == 0))
		return FIF_JPEG;

	if ((stricmp(ext, "KOALA") == 0) || (stricmp(ext, "KOA") == 0))
		return FIF_KOALA;

	if (stricmp(ext, "PCD") == 0)
		return FIF_PCD;

	if (stricmp(ext, "PCX") == 0)
		return FIF_PCX;

	if (stricmp(ext, "PNG") == 0)
		return FIF_PNG;

	if (stricmp(ext, "PBM") == 0)
		return FIF_PBM;

	if (stricmp(ext, "PGM") == 0)
		return FIF_PGM;

	if (stricmp(ext, "PPM") == 0)
		return FIF_PPM;

	if (stricmp(ext, "RAS") == 0)
		return FIF_RAS;

	if ((stricmp(ext, "TARGA") == 0) || (stricmp(ext, "TGA") == 0))
		return FIF_TARGA;

	if ((stricmp(ext, "TIFF") == 0) || (stricmp(ext, "TIF") == 0))
		return FIF_TIFF;

	return FIF_UNKNOWN;
}

// ----------------------------------------------------------

const char *
FreeImage_GetFileTypeFromFormat(FREE_IMAGE_FORMAT format) {
	switch(format) {
		case FIF_BMP :
			return "BMP";

		case FIF_ICO :
			return "ICO";

		case FIF_JPEG :
			return "JPEG";

		case FIF_KOALA :
			return "KOALA";

		case FIF_PBM :
			return "PBM";

		case FIF_PCD :
			return "PCD";

		case FIF_PCX :
			return "PCX";

		case FIF_PGM :
			return "PGM";

		case FIF_PNG :
			return "PNG";

		case FIF_PPM :
			return "PPM";

		case FIF_RAS :
			return "RAS";

		case FIF_TARGA :
			return "TARGA";

		case FIF_TIFF :
			return "TIFF";			
	}

	return NULL;
}
