// ==========================================================
// FreeImage Qt
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// Based on tiffIO code written by Markus L. Noga
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#pragma warning(disable : 4541)

// ----------------------------------------------------------

#include <qcolor.h>
#include <qimage.h>
#include <qfile.h>
#include <qstring.h>
#include <windows.h>

#include "FreeImageQt.h"
#include "FreeImage.h"

// ----------------------------------------------------------

static HMODULE s_library_handle;
static BOOL s_library_loaded = FALSE;

// ----------------------------------------------------------

typedef void (*FreeImage_SetOutputMessageProc) (FreeImage_OutputMessageFunction omf);
typedef BYTE *(*FreeImage_LoadBMPFromHandleProc) (FreeImageIO *io, fi_handle handle, BMPFlags flags = BMP_DEFAULT);
typedef BYTE *(*FreeImage_LoadICOFromHandleProc) (FreeImageIO *io, fi_handle handle, ICOFlags flags = ICO_DEFAULT);
typedef BYTE *(*FreeImage_LoadKOALAFromHandleProc) (FreeImageIO *io, fi_handle handle, KOALAFlags flags = KOALA_DEFAULT);
typedef BYTE *(*FreeImage_LoadJPEGFromHandleProc) (FreeImageIO *io, fi_handle handle, JPEGFlags flags = JPEG_DEFAULT);
typedef BYTE *(*FreeImage_LoadPCDFromHandleProc) (FreeImageIO *io, fi_handle handle, PCDFlags flags = PCD_DEFAULT);
typedef BYTE *(*FreeImage_LoadPCXFromHandleProc) (FreeImageIO *io, fi_handle handle, PCXFlags flags = PCX_DEFAULT);
typedef BYTE *(*FreeImage_LoadPNGFromHandleProc) (FreeImageIO *io, fi_handle handle, PNGFlags flags = PNG_DEFAULT);
typedef BYTE *(*FreeImage_LoadPNMFromHandleProc) (FreeImageIO *io, fi_handle handle, PNMFlags flags = PNM_DEFAULT);
typedef BYTE *(*FreeImage_LoadRASFromHandleProc) (FreeImageIO *io, fi_handle handle, RASFlags flags = RAS_DEFAULT);
typedef BYTE *(*FreeImage_LoadTARGAFromHandleProc) (FreeImageIO *io, fi_handle handle, TARGAFlags flags = TARGA_DEFAULT);
typedef BYTE *(*FreeImage_LoadTIFFFromHandleProc) (FreeImageIO *io, fi_handle handle, TIFFFlags flags = TIFF_DEFAULT);
typedef BYTE *(*FreeImage_SaveBMPToHandleProc) (void *dib, FreeImageIO *io, fi_handle handle, BMPFlags flags = BMP_DEFAULT);
typedef BYTE *(*FreeImage_SaveJPEGToHandleProc) (void *dib, FreeImageIO *io, fi_handle handle, JPEGFlags flags = JPEG_DEFAULT);
typedef BYTE *(*FreeImage_SavePNGToHandleProc) (void *dib, FreeImageIO *io, fi_handle handle, PNGFlags flags = PNG_DEFAULT);
typedef BYTE *(*FreeImage_SavePNMToHandleProc) (void *dib, FreeImageIO *io, fi_handle handle, PNMFlags flags = PNM_DEFAULT);
typedef BYTE *(*FreeImage_SaveTIFFToHandleProc) (void *dib, FreeImageIO *io, fi_handle handle, TIFFFlags flags = TIFF_DEFAULT);
typedef BYTE *(*FreeImage_ConvertTo8BitsProc) (void *dib, BOOL type555 = FALSE);
typedef BYTE *(*FreeImage_ConvertTo32BitsProc) (void *dib, BOOL type555 = FALSE);
typedef BITMAPINFOHEADER *(*FreeImage_GetInfoHeaderProc) (void *dib);
typedef unsigned (*FreeImage_GetHeightProc) (void *dib);
typedef unsigned (*FreeImage_GetWidthProc) (void *dib);
typedef unsigned (*FreeImage_GetBPPProc) (void *dib);
typedef unsigned (*FreeImage_GetDotsPerMeterXProc) (void *dib);
typedef unsigned (*FreeImage_GetDotsPerMeterYProc) (void *dib);
typedef BYTE *(*FreeImage_GetScanLineProc) (void *dib, int scanline);
typedef unsigned (*FreeImage_GetTransparencyCountProc) (void *dib);
typedef BYTE *(*FreeImage_GetTransparencyTableProc) (void *dib);
typedef void *(*FreeImage_AllocateProc)(int width, int height, int bpp);
typedef void (*FreeImage_UnloadProc)(void *dib);
typedef unsigned (*FreeImage_GetColorsUsedProc)(void *dib);
typedef RGBQUAD *(*FreeImage_GetPaletteProc)(void *dib);
typedef unsigned (*FreeImage_GetPitchProc)(void *dib);
typedef const char *(*FreeImage_GetVersionProc)();
typedef const char *(*FreeImage_GetCopyrightMessageProc)();
typedef const char *(*FreeImage_GetFileTypeFromFormatProc)(FREE_IMAGE_FORMAT format);

// ----------------------------------------------------------

FreeImage_SetOutputMessageProc FI_SetOutputMessageProc;
FreeImage_LoadBMPFromHandleProc FI_LoadBMPFromHandleProc;
FreeImage_LoadICOFromHandleProc FI_LoadICOFromHandleProc;
FreeImage_LoadKOALAFromHandleProc FI_LoadKOALAFromHandleProc;
FreeImage_LoadJPEGFromHandleProc FI_LoadJPEGFromHandleProc;
FreeImage_LoadPCDFromHandleProc FI_LoadPCDFromHandleProc;
FreeImage_LoadPCXFromHandleProc FI_LoadPCXFromHandleProc;
FreeImage_LoadPNGFromHandleProc FI_LoadPNGFromHandleProc;
FreeImage_LoadPNMFromHandleProc FI_LoadPNMFromHandleProc;
FreeImage_LoadRASFromHandleProc FI_LoadRASFromHandleProc;
FreeImage_LoadTARGAFromHandleProc FI_LoadTARGAFromHandleProc;
FreeImage_LoadTIFFFromHandleProc FI_LoadTIFFFromHandleProc;
FreeImage_SaveBMPToHandleProc FI_SaveBMPToHandleProc;
FreeImage_SaveJPEGToHandleProc FI_SaveJPEGToHandleProc;
FreeImage_SavePNGToHandleProc FI_SavePNGToHandleProc;
FreeImage_SavePNMToHandleProc FI_SavePNMToHandleProc;
FreeImage_SaveTIFFToHandleProc FI_SaveTIFFToHandleProc;
FreeImage_ConvertTo8BitsProc FI_ConvertTo8BitsProc;
FreeImage_ConvertTo32BitsProc FI_ConvertTo32BitsProc;
FreeImage_GetInfoHeaderProc FI_GetInfoHeaderProc;
FreeImage_GetHeightProc FI_GetHeightProc;
FreeImage_GetWidthProc FI_GetWidthProc;
FreeImage_GetBPPProc FI_GetBPPProc;
FreeImage_GetDotsPerMeterXProc FI_GetDotsPerMeterXProc;
FreeImage_GetDotsPerMeterYProc FI_GetDotsPerMeterYProc;
FreeImage_GetScanLineProc FI_GetScanLineProc;
FreeImage_GetTransparencyCountProc FI_GetTransparencyCountProc;
FreeImage_GetTransparencyTableProc FI_GetTransparencyTableProc;
FreeImage_AllocateProc FI_AllocateProc;
FreeImage_UnloadProc FI_UnloadProc;
FreeImage_GetColorsUsedProc FI_GetColorsUsedProc;
FreeImage_GetPaletteProc FI_GetPaletteProc;
FreeImage_GetPitchProc FI_GetPitchProc;
FreeImage_GetVersionProc FI_GetVersionProc;
FreeImage_GetCopyrightMessageProc FI_GetCopyrightMessageProc;
FreeImage_GetFileTypeFromFormatProc FI_GetFileTypeFromFormatProc;

// ----------------------------------------------------------

inline unsigned
_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	char *b = static_cast<char *>(buffer);

	for (unsigned c = 0; c < count; c++) {
		QIODevice *iod = static_cast<QIODevice *>(handle);

		iod->readBlock(b, size);

		b += size;
	}

	return count;
}

inline unsigned
_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	char *b = static_cast<char *>(buffer);

	for (unsigned c = 0; c < count; c++) {
		QIODevice *iod = static_cast<QIODevice *>(handle);

		iod->writeBlock(b, size);

		b += size;
	}

	return count;
}

inline int
_SeekProc(fi_handle handle, long offset, int origin) {
	QIODevice *iod = static_cast<QIODevice *>(handle);

	switch(origin) {
		case SEEK_SET :
			iod->at(offset);
			break;

		case SEEK_CUR :
			iod->at(iod->at() + offset);
			break;

		default :
			return 1;
	}
  
	return 0;
}

inline long
_TellProc(fi_handle handle) {
	QIODevice *iod = static_cast<QIODevice *>(handle);

	return iod->at();
}

// ----------------------------------------------------------

BOOL
FormatSupportedByQt(QStrList &list, const char *format) {
	for (const char *qtformat = list.first(); qtformat != 0; qtformat = list.next()) {
		if (stricmp(format, qtformat) == 0)
			return TRUE;
	}

	return FALSE;
}

unsigned
GetDotsPerMeterX(void *dib) {
	return (FI_GetDotsPerMeterXProc != NULL) ? FI_GetDotsPerMeterXProc(dib) : 0;
}

unsigned
GetDotsPerMeterY(void *dib) {
	return (FI_GetDotsPerMeterYProc != NULL) ? FI_GetDotsPerMeterYProc(dib) : 0;
}

// ----------------------------------------------------------

static void
FIQT_LoadGeneric(QImageIO *iio, FREE_IMAGE_FORMAT fif) {
    FreeImageIO io;

    io.read_proc  = _ReadProc;
	io.seek_proc  = _SeekProc;
	io.tell_proc  = _TellProc;
	io.write_proc = _WriteProc;

	// load one of the supported bitmap types
	
	void *dib;

	switch(fif) {
		case FIF_BMP :
			dib = FI_LoadBMPFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_ICO :
			dib = FI_LoadICOFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_KOALA :
			dib = FI_LoadKOALAFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_JPEG :
			dib = FI_LoadJPEGFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_PBM :
		case FIF_PGM :
		case FIF_PPM :
			dib = FI_LoadPNMFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_PCD :
			dib = FI_LoadPCDFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_PCX :
			dib = FI_LoadPCXFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_PNG :
			dib = FI_LoadPNGFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_RAS :
			dib = FI_LoadRASFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_TARGA :
			dib = FI_LoadTARGAFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;

		case FIF_TIFF :
			dib = FI_LoadTIFFFromHandleProc(&io, (fi_handle)iio->ioDevice());
			break;
	}

    if (dib != NULL) {
		// QImage doesn't accept 4 or 24 bit bitmaps, so we convert them

		if (FI_GetBPPProc(dib) == 4) {
			void *tmp = FI_ConvertTo8BitsProc(dib);

			FI_UnloadProc(dib);

			dib = tmp;

		} else if (FI_GetBPPProc(dib) == 24) {
			void *tmp = FI_ConvertTo32BitsProc(dib);

			FI_UnloadProc(dib);

			dib = tmp;
		}

		// create an QImage

        QImage image;

		if (FI_GetBPPProc(dib) == 1)
			image.create(FI_GetWidthProc(dib), FI_GetHeightProc(dib), FI_GetBPPProc(dib), FI_GetColorsUsedProc(dib), QImage::LittleEndian);
		else
			image.create(FI_GetWidthProc(dib), FI_GetHeightProc(dib), FI_GetBPPProc(dib), FI_GetColorsUsedProc(dib));
		
		// set metrics data

		image.setDotsPerMeterX(GetDotsPerMeterX(dib));
		image.setDotsPerMeterY(GetDotsPerMeterY(dib));

		// if there is a palette, copy it

		RGBQUAD *palette = FI_GetPaletteProc(dib);

		if (FI_GetTransparencyCountProc(dib) > 0) {
			BYTE *trans_table = FI_GetTransparencyTableProc(dib);

			image.setAlphaBuffer(TRUE);

			unsigned i;

			for (i = 0; i < FI_GetTransparencyCountProc(dib); ++i) {
				image.setColor(i, qRgba(palette->rgbRed, palette->rgbGreen, palette->rgbBlue, trans_table[i]));

				palette++;
			}

			for (; i < FI_GetColorsUsedProc(dib); ++i) {
				image.setColor(i, qRgba(palette->rgbRed, palette->rgbGreen, palette->rgbBlue, 0xff));

				palette++;
			}
		} else {
			for (unsigned i = 0; i < FI_GetColorsUsedProc(dib); ++i) {
				image.setColor(i, qRgb(palette->rgbRed, palette->rgbGreen, palette->rgbBlue));

				palette++;
			}
		}

		// copy the bitmap data

        for (unsigned y = 0; y < FI_GetHeightProc(dib); ++y)
			memcpy(image.scanLine(FI_GetHeightProc(dib) - 1 - y), FI_GetScanLineProc(dib, y), FI_GetPitchProc(dib));

		// dispose the old dib

		FI_UnloadProc(dib);

        iio->setImage(image);
		iio->setStatus(0);		// status 0  == SUCCESS
	} else {
		iio->setStatus(-1);     // status -1 == FAILURE
	}	
}	

static void
FIQT_SaveGeneric(QImageIO *iio, FREE_IMAGE_FORMAT fif) {
    FreeImageIO io;

    io.read_proc  = _ReadProc;
	io.seek_proc  = _SeekProc;
	io.tell_proc  = _TellProc;
	io.write_proc = _WriteProc;

	// get a reference to the QImage

	QImage image = iio->image();

	// build a freeimage DIB from the QImage and copy data

	void *dib = FI_AllocateProc(image.width(), image.height(), image.depth());

	// copy the palette

	RGBQUAD *palette = FI_GetPaletteProc(dib);
	QRgb *colorTable = image.colorTable();

	for (int i = 0; i < image.numColors(); ++i) {
		palette[i].rgbBlue = qBlue(colorTable[i]);
		palette[i].rgbGreen = qGreen(colorTable[i]);
		palette[i].rgbRed = qRed(colorTable[i]);
	}

	// copy the metrics data

	BITMAPINFOHEADER *header = FI_GetInfoHeaderProc(dib);
	header->biXPelsPerMeter = image.dotsPerMeterX();
	header->biYPelsPerMeter = image.dotsPerMeterY();

	// copy the bits

    for (unsigned y = 0; y < FI_GetHeightProc(dib); y++)
		memcpy(FI_GetScanLineProc(dib, y), image.scanLine(FI_GetHeightProc(dib) - 1 - y), FI_GetPitchProc(dib));

	// save the bitmap to a file in the requested format

	switch(fif) {
		case FIF_BMP :
			if (FI_SaveBMPToHandleProc(dib, &io, (fi_handle)iio->ioDevice())) {
				iio->setStatus(0); // status 0  == SUCCESS
			} else {
				iio->setStatus(-1); // status -1 == FAILURE
			}

			break;

		case FIF_JPEG :
			if (FI_SaveJPEGToHandleProc(dib, &io, (fi_handle)iio->ioDevice())) {
				iio->setStatus(0); // status 0  == SUCCESS
			} else {
				iio->setStatus(-1); // status -1 == FAILURE
			}

			break;

		case FIF_PNG :
			if (FI_SavePNGToHandleProc(dib, &io, (fi_handle)iio->ioDevice())) {
				iio->setStatus(0); // status 0  == SUCCESS
			} else {
				iio->setStatus(-1); // status -1 == FAILURE
			}
			break;

		case FIF_PBM :
		case FIF_PGM :
		case FIF_PPM :
			if (FI_SavePNMToHandleProc(dib, &io, (fi_handle)iio->ioDevice())) {
				iio->setStatus(0); // status 0  == SUCCESS
			} else {
				iio->setStatus(-1); // status -1 == FAILURE
			}
			break;

		case FIF_TIFF :
			if (FI_SaveTIFFToHandleProc(dib, &io, (fi_handle)iio->ioDevice())) {
				iio->setStatus(0); // status 0  == SUCCESS
			} else {
				iio->setStatus(-1); // status -1 == FAILURE
			}

			break;

		default :
			iio->setStatus(-1); // status -1 == FAILURE
			break;
	}

	FI_UnloadProc(dib);
}

// ----------------------------------------------------------

static void
FIQT_LoadBMP(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_BMP);
}

static void
FIQT_LoadICO(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_ICO);
}

static void
FIQT_LoadKOALA(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_KOALA);
}

static void
FIQT_LoadJPEG(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_JPEG);
}

static void
FIQT_LoadPBM(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PBM);
}

static void
FIQT_LoadPCD(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PCD);
}

static void
FIQT_LoadPCX(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PCX);
}

static void
FIQT_LoadPGM(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PGM);
}

static void
FIQT_LoadPNG(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PNG);
}

static void
FIQT_LoadPPM(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_PPM);
}

static void
FIQT_LoadRAS(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_RAS);
}

static void
FIQT_LoadTARGA(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_TARGA);
}

static void
FIQT_LoadTIFF(QImageIO *iio) {
	FIQT_LoadGeneric(iio, FIF_TIFF);
}

// ----------------------------------------------------------

static void
FIQT_SaveBMP(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_BMP);
}

static void
FIQT_SaveJPEG(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_JPEG);
}

static void
FIQT_SavePBM(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_PBM);
}

static void
FIQT_SavePGM(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_PGM);
}

static void
FIQT_SavePNG(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_PNG);
}

static void
FIQT_SavePPM(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_PPM);
}

static void
FIQT_SaveTIFF(QImageIO *iio) {
	FIQT_SaveGeneric(iio, FIF_TIFF);
}

// ----------------------------------------------------------

bool
FIQT_Register(BOOL new_formats_only) {
	if (!s_library_loaded) {
		if ((s_library_handle = LoadLibrary("freeimage.dll")) != NULL) {
			// extract the functions from the FreeImage library
			
			FI_SetOutputMessageProc = reinterpret_cast<FreeImage_SetOutputMessageProc>(GetProcAddress(s_library_handle, "FreeImage_SetOutputMessage"));
			FI_LoadBMPFromHandleProc = reinterpret_cast<FreeImage_LoadBMPFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadBMPFromHandle"));
			FI_LoadICOFromHandleProc = reinterpret_cast<FreeImage_LoadICOFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadICOFromHandle"));
			FI_LoadKOALAFromHandleProc = reinterpret_cast<FreeImage_LoadKOALAFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadKOALAFromHandle"));
			FI_LoadJPEGFromHandleProc = reinterpret_cast<FreeImage_LoadJPEGFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadJPEGFromHandle"));
			FI_LoadPCDFromHandleProc = reinterpret_cast<FreeImage_LoadPCDFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadPCDFromHandle"));
			FI_LoadPCXFromHandleProc = reinterpret_cast<FreeImage_LoadPCXFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadPCXFromHandle"));
			FI_LoadPNGFromHandleProc = reinterpret_cast<FreeImage_LoadPNGFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadPNGFromHandle"));
			FI_LoadPNMFromHandleProc = reinterpret_cast<FreeImage_LoadPNMFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadPNMFromHandle"));
			FI_LoadRASFromHandleProc = reinterpret_cast<FreeImage_LoadRASFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadRASFromHandle"));
			FI_LoadTARGAFromHandleProc = reinterpret_cast<FreeImage_LoadTARGAFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadTARGAFromHandle"));
			FI_LoadTIFFFromHandleProc = reinterpret_cast<FreeImage_LoadTIFFFromHandleProc>(GetProcAddress(s_library_handle, "FreeImage_LoadTIFFFromHandle"));
			FI_SaveBMPToHandleProc = reinterpret_cast<FreeImage_SaveBMPToHandleProc>(GetProcAddress(s_library_handle, "FreeImage_SaveBMPToHandle"));
			FI_SaveJPEGToHandleProc = reinterpret_cast<FreeImage_SaveJPEGToHandleProc>(GetProcAddress(s_library_handle, "FreeImage_SaveJPEGToHandle"));
			FI_SavePNGToHandleProc = reinterpret_cast<FreeImage_SavePNGToHandleProc>(GetProcAddress(s_library_handle, "FreeImage_SavePNGToHandle"));
			FI_SavePNMToHandleProc = reinterpret_cast<FreeImage_SavePNMToHandleProc>(GetProcAddress(s_library_handle, "FreeImage_SavePNMToHandle"));
			FI_SaveTIFFToHandleProc = reinterpret_cast<FreeImage_SaveTIFFToHandleProc>(GetProcAddress(s_library_handle, "FreeImage_SaveTIFFToHandle"));
			FI_ConvertTo8BitsProc = reinterpret_cast<FreeImage_ConvertTo8BitsProc>(GetProcAddress(s_library_handle, "FreeImage_ConvertTo8Bits"));
			FI_ConvertTo32BitsProc = reinterpret_cast<FreeImage_ConvertTo32BitsProc>(GetProcAddress(s_library_handle, "FreeImage_ConvertTo32Bits"));
			FI_GetInfoHeaderProc = reinterpret_cast<FreeImage_GetInfoHeaderProc>(GetProcAddress(s_library_handle, "FreeImage_GetInfoHeader"));
			FI_GetHeightProc = reinterpret_cast<FreeImage_GetHeightProc>(GetProcAddress(s_library_handle, "FreeImage_GetHeight"));
			FI_GetWidthProc = reinterpret_cast<FreeImage_GetWidthProc>(GetProcAddress(s_library_handle, "FreeImage_GetWidth"));
			FI_GetBPPProc = reinterpret_cast<FreeImage_GetBPPProc>(GetProcAddress(s_library_handle, "FreeImage_GetBPP"));
			FI_GetDotsPerMeterXProc = reinterpret_cast<FreeImage_GetDotsPerMeterXProc>(GetProcAddress(s_library_handle, "FreeImage_GetDotsPerMeterX"));
			FI_GetDotsPerMeterYProc = reinterpret_cast<FreeImage_GetDotsPerMeterYProc>(GetProcAddress(s_library_handle, "FreeImage_GetDotsPerMeterY"));			
			FI_GetScanLineProc = reinterpret_cast<FreeImage_GetScanLineProc>(GetProcAddress(s_library_handle, "FreeImage_GetScanLine"));
			FI_GetTransparencyCountProc = reinterpret_cast<FreeImage_GetTransparencyCountProc>(GetProcAddress(s_library_handle, "FreeImage_GetTransparencyCount"));
			FI_GetTransparencyTableProc = reinterpret_cast<FreeImage_GetTransparencyTableProc>(GetProcAddress(s_library_handle, "FreeImage_GetTransparencyTable"));
			FI_AllocateProc = reinterpret_cast<FreeImage_AllocateProc>(GetProcAddress(s_library_handle, "FreeImage_Allocate"));
			FI_UnloadProc = reinterpret_cast<FreeImage_UnloadProc>(GetProcAddress(s_library_handle, "FreeImage_Unload"));
			FI_GetColorsUsedProc = reinterpret_cast<FreeImage_GetColorsUsedProc>(GetProcAddress(s_library_handle, "FreeImage_GetColorsUsed"));
			FI_GetPaletteProc = reinterpret_cast<FreeImage_GetPaletteProc>(GetProcAddress(s_library_handle, "FreeImage_GetPalette"));
			FI_GetPitchProc = reinterpret_cast<FreeImage_GetPitchProc>(GetProcAddress(s_library_handle, "FreeImage_GetPitch"));
			FI_GetVersionProc = reinterpret_cast<FreeImage_GetVersionProc>(GetProcAddress(s_library_handle, "FreeImage_GetVersion"));
			FI_GetCopyrightMessageProc = reinterpret_cast<FreeImage_GetCopyrightMessageProc>(GetProcAddress(s_library_handle, "FreeImage_GetCopyrightMessage"));
			FI_GetFileTypeFromFormatProc = reinterpret_cast<FreeImage_GetFileTypeFromFormatProc>(GetProcAddress(s_library_handle, "FreeImage_GetFileTypeFromFormat"));
			
			if ((FI_LoadBMPFromHandleProc != 0) &&
				(FI_LoadICOFromHandleProc != 0) &&
				(FI_LoadKOALAFromHandleProc != 0) &&
				(FI_LoadPCDFromHandleProc != 0) &&
				(FI_LoadPCXFromHandleProc != 0) &&
				(FI_LoadPNGFromHandleProc != 0) &&
				(FI_LoadPNMFromHandleProc != 0) &&
				(FI_LoadRASFromHandleProc != 0) &&
				(FI_LoadTARGAFromHandleProc != 0) &&
				(FI_LoadTIFFFromHandleProc != 0) &&
				(FI_SaveBMPToHandleProc != 0) &&
				(FI_SaveJPEGToHandleProc != 0) &&
				(FI_SavePNGToHandleProc != 0) &&
				(FI_SavePNMToHandleProc != 0) &&
				(FI_SaveTIFFToHandleProc != 0) &&
				(FI_ConvertTo8BitsProc != 0) &&
				(FI_ConvertTo32BitsProc != 0) &&
				(FI_GetInfoHeaderProc != 0) &&
				(FI_GetHeightProc != 0) &&
				(FI_GetWidthProc != 0) &&
				(FI_GetBPPProc != 0) &&
				(FI_GetScanLineProc != 0) &&
				(FI_GetTransparencyCountProc != 0) &&
				(FI_GetTransparencyTableProc != 0) &&
				(FI_AllocateProc != 0) &&
				(FI_UnloadProc != 0) &&
				(FI_GetColorsUsedProc != 0) &&
				(FI_GetPaletteProc != 0) &&
				(FI_GetPitchProc != 0)) {

				// register the bitmap formats in Qt

				QStrList format_list;
				format_list = QImageIO::inputFormats();

				if (!FormatSupportedByQt(format_list, "BMP") || !new_formats_only)
					QImageIO::defineIOHandler("BMP",    "^BM", 0, FIQT_LoadBMP,   FIQT_SaveBMP);
				
				if (!FormatSupportedByQt(format_list, "PBM") || !new_formats_only)
					QImageIO::defineIOHandler("PBM",    "^P1", 0, FIQT_LoadPBM,   FIQT_SavePBM);				

				if (!FormatSupportedByQt(format_list, "PBMRAW") || !new_formats_only)
					QImageIO::defineIOHandler("PBMRAW", "^P4", 0, FIQT_LoadPBM,   FIQT_SavePBM);				

				if (!FormatSupportedByQt(format_list, "PGM") || !new_formats_only)
					QImageIO::defineIOHandler("PGM",    "^P2", 0, FIQT_LoadPGM,   FIQT_SavePGM);				

				if (!FormatSupportedByQt(format_list, "PGMRAW") || !new_formats_only)
					QImageIO::defineIOHandler("PGMRAW", "^P5", 0, FIQT_LoadPGM,   FIQT_SavePGM);				

				if (!FormatSupportedByQt(format_list, "PNG") || !new_formats_only)
					QImageIO::defineIOHandler("PNG",    "^.PNG\r", 0, FIQT_LoadPNG,   FIQT_SavePNG);				

				if (!FormatSupportedByQt(format_list, "PPM") || !new_formats_only)
					QImageIO::defineIOHandler("PPM",    "^P3", 0, FIQT_LoadPPM,   FIQT_SavePPM);				

				if (!FormatSupportedByQt(format_list, "PPMRAW") || !new_formats_only)
					QImageIO::defineIOHandler("PPMRAW", "^P6", 0, FIQT_LoadPPM,   FIQT_SavePPM);					
				
				if (!FormatSupportedByQt(format_list, "ICO") || !new_formats_only)
					QImageIO::defineIOHandler("ICO",    "", 0, FIQT_LoadICO,   NULL);			

				if (!FormatSupportedByQt(format_list, "JPEG") || !new_formats_only)
					QImageIO::defineIOHandler("JPEG",   "^\377\330\377", 0, FIQT_LoadJPEG,  FIQT_SaveJPEG);				

				if (!FormatSupportedByQt(format_list, "KOALA") || !new_formats_only)
					QImageIO::defineIOHandler("KOALA",  "", 0, FIQT_LoadKOALA, NULL);				

				if (!FormatSupportedByQt(format_list, "PCD") || !new_formats_only)
					QImageIO::defineIOHandler("PCD",    "", 0, FIQT_LoadPCD,   NULL);				

				if (!FormatSupportedByQt(format_list, "PCX") || !new_formats_only)
					QImageIO::defineIOHandler("PCX",    "", 0, FIQT_LoadPCX,   NULL);				

				if (!FormatSupportedByQt(format_list, "RAS") || !new_formats_only)
					QImageIO::defineIOHandler("RAS",    "", 0, FIQT_LoadRAS,   NULL);				

				if (!FormatSupportedByQt(format_list, "TARGA") || !new_formats_only)
					QImageIO::defineIOHandler("TARGA",  "", 0, FIQT_LoadTARGA, NULL);				

				if (!FormatSupportedByQt(format_list, "TIFF") || !new_formats_only)
					QImageIO::defineIOHandler("TIFF",   "^[MI][MI][\\x01*][\\x01*]", 0, FIQT_LoadTIFF,  FIQT_SaveTIFF);				

				s_library_loaded = TRUE;

				atexit(FIQT_Unregister); // when the application stops, automatically unregister

				return s_library_loaded;
			}
		}

		s_library_loaded = FALSE;

		return s_library_loaded;
	}

	return s_library_loaded;
}

const char *
FIQT_GetFileTypeFromExtension(const QString &extension) {
	QString ext = extension.upper();

	if (ext == "BMP")
		return "BMP";

	if (ext == "ICO")
		return "ICO";

	if ((ext == "JPEG") || (ext == "JIF") || (ext == "JPG"))
		return "JPEG";

	if ((ext == "KOA") || (ext == "KOALA"))
		return "KOALA";

	if (ext == "PBM")
		return "PBM";

	if ((ext == "PCD") || (ext == "PHOTOCD"))
		return "PCD";

	if (ext == "PCX")
		return "PCX";

	if (ext == "PGM")
		return "PGM";

	if (ext == "PNG")
		return "PNG";

	if (ext == "PPM")
		return "PPM";

	if (ext == "RAS")
		return "RAS";

	if ((ext == "TARGA") || (ext == "TGA"))
		return "TARGA";

	if ((ext == "TIFF") || (ext == "TIF"))
		return "TIFF";

	return NULL;
}

const char *
FIQT_GetFileTypeFromFormat(FREE_IMAGE_FORMAT format) {
	return (FI_GetFileTypeFromFormatProc != NULL) ? FI_GetFileTypeFromFormatProc(format) : NULL;
}

void
FIQT_Unregister() {
	if (s_library_loaded) {
		FreeLibrary(s_library_handle);

		s_library_loaded = FALSE;
	}		
}

bool
FIQT_IsLoaded() {
	return s_library_loaded;
}

void
FIQT_SetOutputMessage(FreeImage_OutputMessageFunction omf) {
	if (FI_SetOutputMessageProc != NULL) {
		FI_SetOutputMessageProc(omf);
	}
}

const char *
FIQT_GetVersion() {
	return (FI_GetVersionProc != NULL) ? FI_GetVersionProc() : NULL;
}

const char *
FIQT_GetCopyrightMessage() {
	return (FI_GetCopyrightMessageProc != NULL) ? FI_GetCopyrightMessageProc() : NULL;
}

