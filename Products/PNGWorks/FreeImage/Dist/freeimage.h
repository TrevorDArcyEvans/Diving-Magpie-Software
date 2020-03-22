// ==========================================================
// FreeImage
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Alex Kwak
// - Alexander Dymerets (sashad@te.net.ua)
// - Hervé Drolon (drolon@iut.univ-lehavre.fr)
// - Jan L. Nauta (jln@magentammt.com)
// - Jani Kajala (janik@remedy.fi)
// - Adam Gates (adam.gates@str.com.au)
// - Markus Loibl (markus.loibl@epost.de)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#ifndef FREEIMAGE_H
#define FREEIMAGE_H

#ifdef FREEIMAGE_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

// enabled modules in the DLL -----------------------------------------------

#define BMP_ENABLED
#define ICO_ENABLED
#define KOALA_ENABLED
#define JPEG_ENABLED
#define PCD_ENABLED
#define PCX_ENABLED
#define PNG_ENABLED
#define PNM_ENABLED			// PBM, PGM & PPM
#define RAS_ENABLED
#define TARGA_ENABLED
#define TIFF_ENABLED
#define EFFECTS_ENABLED
#define CONVERSION_ENABLED

// For C compatility --------------------------------------------------------

#ifdef __cplusplus
#define FI_DEFAULT(x)	= x
#define FI_ENUM(x)		enum x
#define FI_STRUCT(x)	struct x
#else
#define FI_DEFAULT(x)
#define FI_ENUM(x)		typedef int x; enum x
#define FI_STRUCT(x)	typedef struct x x; struct x
#endif

// Types used in the library (directly copied from Windows) -----------------

#ifndef _WINDOWS_
#define _WINDOWS_

#define FALSE 0
#define TRUE  1
#define NULL  0

typedef long BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#ifndef SEEK_SET
#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2
#endif

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

typedef struct tagRGBQUAD {
  BYTE    rgbBlue; 
  BYTE    rgbGreen; 
  BYTE    rgbRed; 
  BYTE    rgbReserved; 
} RGBQUAD; 

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;
  LONG   biWidth; 
  LONG   biHeight; 
  WORD   biPlanes; 
  WORD   biBitCount;
  DWORD  biCompression; 
  DWORD  biSizeImage; 
  LONG   biXPelsPerMeter; 
  LONG   biYPelsPerMeter; 
  DWORD  biClrUsed; 
  DWORD  biClrImportant; 
} BITMAPINFOHEADER, *PBITMAPINFOHEADER; 

typedef struct tagBITMAPINFO { 
  BITMAPINFOHEADER bmiHeader; 
  RGBQUAD          bmiColors[1];
} BITMAPINFO, *PBITMAPINFO; 

#endif

// File IO routines ---------------------------------------------------------

#ifndef FREEIMAGE_IO
#define FREEIMAGE_IO

#define fi_handle void*

typedef unsigned (*FI_ReadProc) (void *buffer, unsigned size, unsigned count, fi_handle handle);
typedef unsigned (*FI_WriteProc) (void *buffer, unsigned size, unsigned count, fi_handle handle);
typedef int (*FI_SeekProc) (fi_handle handle, long offset, int origin);
typedef long (*FI_TellProc) (fi_handle handle);

#pragma pack (push, 1)

FI_STRUCT( FreeImageIO ) {
	FI_ReadProc  read_proc;     //! pointer to the function used to read data
	FI_WriteProc write_proc;    //! pointer to the function used to write data
	FI_SeekProc  seek_proc;		//! pointer to the function used to seek
	FI_TellProc  tell_proc;		//! pointer to the function used to aquire the current position
};

#pragma pack(pop)

// FreeImage type FI_ENUM( ------------------------------------------------------

#ifndef FREEIMAGE_FORMAT_DEF
#define FREEIMAGE_FORMAT_DEF

FI_ENUM(FREE_IMAGE_FORMAT) {
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

// Other FI_ENUM( used in FreeImage ---------------------------------------------

FI_ENUM(FREE_IMAGE_COLOR_TYPE) {
	FIC_MINISWHITE = 0,		//! min value is white
	FIC_MINISBLACK = 1,		//! min value is black
	FIC_RGB	       = 2,		//! RGB color model
	FIC_PALETTE    = 3,		//! color map indexed
};

FI_ENUM(FREE_IMAGE_QUANTIZE) {
	FIQ_WUQUANT = 0,
};

FI_ENUM(BMPFlags) {
	BMP_DEFAULT   = 0,
};

FI_ENUM(ICOFlags) {
	ICO_DEFAULT   = 0,
	ICO_FIRST     = 0,
	ICO_SECOND    = 1,
	ICO_THIRD     = 2,
};

FI_ENUM(KOALAFlags) {
	KOALA_DEFAULT = 0,
};

FI_ENUM(JPEGFlags) {
	JPEG_DEFAULT  = 0,
	JPEG_FAST     = 1,            // load flags
	JPEG_ACCURATE = 2,

	JPEG_QUALITYSUPERB  = 0x80,   // save flags
	JPEG_QUALITYGOOD    = 0x100,  // you can use either this
	JPEG_QUALITYNORMAL  = 0x200,  // or a quality id from 0 to 100
	JPEG_QUALITYAVERAGE = 0x400,
	JPEG_QUALITYBAD     = 0x800,
};

FI_ENUM(PCDFlags) {
	PCD_DEFAULT   = 0,
	PCD_BASE      = 1,
	PCD_BASEDIV4  = 2,
	PCD_BASEDIV16 = 3,
};

FI_ENUM(PCXFlags) {
	PCX_DEFAULT   = 0,
};

FI_ENUM(PNGFlags) {
	PNG_DEFAULT   = 0,
};

FI_ENUM(PNMFlags) {				//! PBM, PGM, PPM
	PNM_DEFAULT		= 0,
	PNM_SAVE_RAW	= 0,	//! If set the writer saves in RAW format (i.e. P4, P5 or P6)
	PNM_SAVE_ASCII	= 1		//! If set the writer saves in ASCII format (i.e. P1, P2 or P3)

};

FI_ENUM(RASFlags) {
	RAS_DEFAULT   = 0,
};

FI_ENUM(TARGAFlags) {
	TARGA_DEFAULT	  = 0,
	TARGA_LOAD_RGB888 = 1,  //! If set the loader converts ARGB8888 -> RGB888.
	TARGA_LOAD_RGB555 = 2,  //! If set the loader doesn't convert 16bit RGB555 -> 24bit RGB888.
};

FI_ENUM(TIFFFlags) {
	TIFF_DEFAULT    = 0,
	TIFF_DIRECTORY0 = 0,
	TIFF_DIRECTORY1 = 1,
	TIFF_DIRECTORY2 = 2,
	TIFF_DIRECTORY3 = 3,
	TIFF_DIRECTORY4 = 4,
	TIFF_DIRECTORY5 = 5,
	TIFF_DIRECTORY6 = 6,
	TIFF_DIRECTORY7 = 7,
	TIFF_DIRECTORY8 = 8,
	TIFF_DIRECTORY9 = 9,
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

// Version routines ---------------------------------------------------------

DLL_API const char *FreeImage_GetVersion();
DLL_API const char *FreeImage_GetCopyrightMessage();

// Message output functions -------------------------------------------------

typedef void(*FreeImage_OutputMessageFunction)(FREE_IMAGE_FORMAT fif, const char *msg);
DLL_API void FreeImage_SetOutputMessage(FreeImage_OutputMessageFunction omf);

// MMX routines ------------------------------------------------------------

DLL_API void FreeImage_EnableMMX();
DLL_API void FreeImage_DisableMMX();

// Allocate/Unload routines ------------------------------------------------

DLL_API void *FreeImage_Allocate(int width, int height, int bpp);
DLL_API void FreeImage_Free(void *dib);
DLL_API void FreeImage_Unload(void *dib);

// Image Load routines -----------------------------------------------------

DLL_API void *FreeImage_LoadBMP(const char *filename, BMPFlags flags FI_DEFAULT(BMP_DEFAULT));
DLL_API void *FreeImage_LoadBMPFromHandle(FreeImageIO *io, fi_handle handle, BMPFlags flags FI_DEFAULT(BMP_DEFAULT));
DLL_API void *FreeImage_LoadICO(const char *filename, ICOFlags flags FI_DEFAULT( ICO_DEFAULT ) );
DLL_API void *FreeImage_LoadICOFromHandle(FreeImageIO *io, fi_handle handle, ICOFlags flags FI_DEFAULT(ICO_DEFAULT));
DLL_API void *FreeImage_LoadJPEG(const char *filename, JPEGFlags flags FI_DEFAULT( JPEG_DEFAULT ) );
DLL_API void *FreeImage_LoadJPEGFromHandle(FreeImageIO *io, fi_handle handle, JPEGFlags flags FI_DEFAULT(JPEG_DEFAULT));
DLL_API void *FreeImage_LoadKOALA(const char *filename, KOALAFlags flags FI_DEFAULT(KOALA_DEFAULT));
DLL_API void *FreeImage_LoadKOALAFromHandle(FreeImageIO *io, fi_handle handle, KOALAFlags flags FI_DEFAULT(KOALA_DEFAULT));
DLL_API void *FreeImage_LoadPCD(const char *filename, PCDFlags flags FI_DEFAULT(PCD_DEFAULT));
DLL_API void *FreeImage_LoadPCDFromHandle(FreeImageIO *io, fi_handle handle, PCDFlags flags FI_DEFAULT(PCD_DEFAULT));
DLL_API void *FreeImage_LoadPCX(const char *filename, PCXFlags flags FI_DEFAULT(PCX_DEFAULT));
DLL_API void *FreeImage_LoadPCXFromHandle(FreeImageIO *io, fi_handle handle, PCXFlags flags FI_DEFAULT(PCX_DEFAULT));
DLL_API void *FreeImage_LoadPNM(const char *filename, PNMFlags flags FI_DEFAULT(PNM_DEFAULT));
DLL_API void *FreeImage_LoadPNMFromHandle(FreeImageIO *io, fi_handle handle, PNMFlags flags FI_DEFAULT(PNM_DEFAULT));
DLL_API void *FreeImage_LoadPNG(const char *filename, PNGFlags flags FI_DEFAULT(PNG_DEFAULT));
DLL_API void *FreeImage_LoadPNGFromHandle(FreeImageIO *io, fi_handle handle, PNGFlags flags FI_DEFAULT(PNG_DEFAULT));
DLL_API void *FreeImage_LoadRAS(const char *filename, RASFlags flags FI_DEFAULT(RAS_DEFAULT));
DLL_API void *FreeImage_LoadRASFromHandle(FreeImageIO *io, fi_handle handle, RASFlags flags FI_DEFAULT(RAS_DEFAULT));
DLL_API void *FreeImage_LoadTARGA(const char *filename, TARGAFlags flags FI_DEFAULT(TARGA_DEFAULT));
DLL_API void *FreeImage_LoadTARGAFromHandle(FreeImageIO *io, fi_handle handle, TARGAFlags flags FI_DEFAULT(TARGA_DEFAULT));
DLL_API void *FreeImage_LoadTIFF(const char *filename, TIFFFlags flags FI_DEFAULT(TIFF_DEFAULT));
DLL_API void *FreeImage_LoadTIFFFromHandle(FreeImageIO *io, fi_handle handle, TIFFFlags flags FI_DEFAULT(TIFF_DEFAULT));

// Image Save routines -----------------------------------------------------

DLL_API BOOL FreeImage_SaveBMP(void *dib, const char *filename, BMPFlags flags FI_DEFAULT( BMP_DEFAULT ) );
DLL_API BOOL FreeImage_SaveBMPToHandle(void *dib, FreeImageIO *io, fi_handle handle, BMPFlags flags FI_DEFAULT( BMP_DEFAULT ) );
DLL_API BOOL FreeImage_SaveJPEG(void *dib, const char *filename, JPEGFlags flags FI_DEFAULT(JPEG_DEFAULT));
DLL_API BOOL FreeImage_SaveJPEGToHandle(void *dib, FreeImageIO *io, fi_handle handle, JPEGFlags flags FI_DEFAULT(JPEG_DEFAULT));
DLL_API BOOL FreeImage_SavePNG(void *dib, const char *filename, PNGFlags flags FI_DEFAULT( PNG_DEFAULT ) );
DLL_API BOOL FreeImage_SavePNGToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNGFlags flags FI_DEFAULT( PNG_DEFAULT ) );
DLL_API BOOL FreeImage_SavePNM(void *dib, const char *filename, PNMFlags flags FI_DEFAULT( PNM_DEFAULT ) );
DLL_API BOOL FreeImage_SavePNMToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNMFlags flags FI_DEFAULT( PNM_DEFAULT ) );
DLL_API BOOL FreeImage_SaveTIFF(void *dib, const char *filename, TIFFFlags flags FI_DEFAULT( TIFF_DEFAULT ) );
DLL_API BOOL FreeImage_SaveTIFFToHandle(void *dib, FreeImageIO *io, fi_handle handle, TIFFFlags flags FI_DEFAULT( TIFF_DEFAULT ) );

// Filetype request routines -----------------------------------------------

DLL_API FREE_IMAGE_FORMAT FreeImage_GetFileType(const char *filename, int size);
DLL_API FREE_IMAGE_FORMAT FreeImage_GetFileTypeFromHandle(FreeImageIO *io, fi_handle handle, int size);
DLL_API FREE_IMAGE_FORMAT FreeImage_GetFileTypeFromExt(const char *ext);
DLL_API const char *FreeImage_GetFileTypeFromFormat(FREE_IMAGE_FORMAT format);

// FreeImage info routines -------------------------------------------------

DLL_API unsigned FreeImage_GetTransparencyCount(void *dib);
DLL_API BYTE *FreeImage_GetTransparencyTable(void *dib);
DLL_API void FreeImage_SetTransparencyTable(void *dib, BYTE *table, BYTE count);

// DIB info routines -------------------------------------------------------

DLL_API unsigned FreeImage_GetColorsUsed(void *dib);
DLL_API BYTE * FreeImage_GetBits(void *dib);
DLL_API BYTE * FreeImage_GetBitsRowCol(void *dib, int col, int row);
DLL_API BYTE * FreeImage_GetScanLine(void *dib, int scanline);
DLL_API unsigned FreeImage_GetBPP(void *dib);
DLL_API unsigned FreeImage_GetWidth(void *dib);
DLL_API unsigned FreeImage_GetHeight(void *dib);
DLL_API unsigned FreeImage_GetLine(void *dib);
DLL_API unsigned FreeImage_GetPitch(void *dib);
DLL_API unsigned FreeImage_GetDIBSize(void *dib);
DLL_API RGBQUAD *FreeImage_GetPalette(void *dib);
DLL_API unsigned FreeImage_GetDotsPerMeterX(void *dib);
DLL_API unsigned FreeImage_GetDotsPerMeterY(void *dib);
DLL_API BITMAPINFOHEADER *FreeImage_GetInfoHeader(void *dib);
DLL_API BITMAPINFO *FreeImage_GetInfo(void *dib);
DLL_API FREE_IMAGE_COLOR_TYPE FreeImage_GetColorType(void *dib);

// Conversion routines -----------------------------------------------------

DLL_API void FreeImage_ConvertToGreyscale(void *dib);
DLL_API void *FreeImage_ConvertTo8Bits(void *dib, BOOL type555 FI_DEFAULT(FALSE));
DLL_API void *FreeImage_ConvertTo16Bits(void *dib, BOOL type555 FI_DEFAULT(FALSE));
DLL_API void *FreeImage_ConvertTo24Bits(void *dib, BOOL type555 FI_DEFAULT(FALSE));
DLL_API void *FreeImage_ConvertTo32Bits(void *dib, BOOL type555 FI_DEFAULT(FALSE));
DLL_API void * FreeImage_ColorQuantize(void *dib, FREE_IMAGE_QUANTIZE quantize);

// Effects -----------------------------------------------------------------

DLL_API void *FreeImage_Clone(void *dib);
DLL_API void FreeImage_Blur(void *dib);
DLL_API void FreeImage_Brighten(void *dib, double factor);
DLL_API void FreeImage_Combine(void *dib1, void *dib2, int x, int y, unsigned int alpha FI_DEFAULT(256));
DLL_API void FreeImage_Darken(void *dib, double factor);
DLL_API void FreeImage_MaskCombine24(void *dib1, void *dib2, void *mask, int x, int y);
DLL_API void FreeImage_MaskCombine24Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *psrc, void *pmask, int srcx, int srcy);
DLL_API void FreeImage_MaskCombine32(void *dib1, void *dib2, int x, int y);
DLL_API void FreeImage_MaskCombine32Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *pSrc, int srcx, int srcy);
DLL_API void FreeImage_AddAlphaMask(void *dib, void *mask);
DLL_API void *FreeImage_Crop(void *dib, int left, int top, int right, int bottom);
DLL_API void FreeImage_Flip(void *dib);
DLL_API void FreeImage_Mirror(void *dib);
DLL_API void FreeImage_Invert(void *dib);
DLL_API void *FreeImage_Rotate(void *dib, double angle);

#ifdef __cplusplus
}
#endif

#endif // !FREEIMAGE_H