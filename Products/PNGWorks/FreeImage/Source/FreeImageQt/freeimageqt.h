// ==========================================================
// FreeImage Qt
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// Based on code written by Markus L. Noga
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#ifndef FREEIMAGEQT_H
#define FREEIMAGEQT_H

// ----------------------------------------------------------

class QString;

// ----------------------------------------------------------

#ifndef FREEIMAGE_FORMAT_DEF
#define FREEIMAGE_FORMAT_DEF

enum FREE_IMAGE_FORMAT {
	FIF_UNKNOWN = 0,
	FIF_BMP,
	FIF_ICO,
	FIF_JPEG,
	FIF_KOALA,
	FIF_PBM,
	FIF_PCD,
	FIF_PCX,
	FIF_PGM,
	FIF_PNG,
	FIF_PPM,
	FIF_RAS,
	FIF_TARGA,
	FIF_TIFF,
};

#endif

// ----------------------------------------------------------

bool FIQT_Register(bool new_formats_only = false);
bool FIQT_IsLoaded();
void FIQT_Unregister();

typedef void(*FreeImage_OutputMessageFunction)(FREE_IMAGE_FORMAT fif, const char *msg);
void FIQT_SetOutputMessage(FreeImage_OutputMessageFunction omf);

const char *FIQT_GetFileTypeFromExtension(const QString &extension);
const char *FIQT_GetFileTypeFromFormat(FREE_IMAGE_FORMAT format);
const char *FIQT_GetVersion();
const char *FIQT_GetCopyrightMessage();

// ----------------------------------------------------------

#endif //!FREEIMAGEQT_H
