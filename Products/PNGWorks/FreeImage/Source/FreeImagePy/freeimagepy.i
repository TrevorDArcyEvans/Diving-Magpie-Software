// ==========================================================
// FreeImage Python
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Adam Gates (adam.gates@str.com.au)
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

%module FreeImagePy
%{
/* Put header files here (optional) */
#include <Windows.H>
#include "..\FreeImage.H"
#pragma warning(disable : 4273)		// inconsistent dll linkage.  dllexport assumed.
%}

// seems to require this or swig crashes
%name (fiGetVersion) extern const char *FreeImage_GetVersion();

enum BOOL{
	FALSE = 0,
	TRUE	= 1
};

// enum used in FreeImage ---------------------------------------------------

extern enum FREE_IMAGE_COLOR_TYPE {
	FIC_MINISWHITE = 0,  //! min value is white
	FIC_MINISBLACK,      //! min value is black
	FIC_RGB,             //! RGB color model
	FIC_PALETTE,         //! color map indexed
};

extern enum FREE_IMAGE_FORMAT {
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

extern enum FREE_IMAGE_QUANTIZE {
	FIQ_WUQUANT = 0,
};

extern enum BMPFlags {
	BMP_DEFAULT   = 0,
};

extern enum ICOFlags {
	ICO_DEFAULT   = 0,
	ICO_FIRST     = 0,
	ICO_SECOND    = 1,
	ICO_THIRD     = 2,
};

extern enum KOALAFlags {
	KOALA_DEFAULT = 0,
};

extern enum JPEGFlags {
	JPEG_DEFAULT        = 0,      // load flags
	JPEG_FAST           = 1,
	JPEG_ACCURATE       = 2,
      JPEG_QUALITYSUPERB  = 0x80,   // save flags
      JPEG_QUALITYGOOD    = 0x100,
      JPEG_QUALITYNORMAL  = 0x200,
      JPEG_QUALITYAVERAGE = 0x400,
      JPEG_QUALITYBAD     = 0x800,
};

extern enum PCDFlags {
	PCD_DEFAULT   = 0,
	PCD_BASE      = 1,
	PCD_BASEDIV4  = 2,
	PCD_BASEDIV16 = 3,      
};

extern enum PCXFlags {
	PCX_DEFAULT   = 0,
};

extern enum PNGFlags {
	PNG_DEFAULT   = 0,
};

extern enum PNMFlags {		//! PBM, PGM, PPM
	PNM_DEFAULT		= 0,
	PNM_SAVE_RAW	= 0,	//! If set the writer save in RAW format (i.e. P4, P5 or P6)
	PNM_SAVE_ASCII	= 1	//! If set the writer save in ASCII format (i.e. P1, P2 or P3)
};

extern enum RASFlags {
	RAS_DEFAULT   = 0,
};

extern enum TARGAFlags {
	TARGA_DEFAULT     = 0,
	TARGA_LOAD_RGB888 = 1,  //! If set the loader convert ARGB8888 -> RGB888.
	TARGA_LOAD_RGB555 = 2,  //! If set the loader doesn't convert 16bit RGB555 -> 24bit RGB888.
};

extern enum TIFFFlags {
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

// Version routines ---------------------------------------------------------

%name (GetVersion) extern const char *FreeImage_GetVersion();
%name (GetCopyrightMessage) extern const char *FreeImage_GetCopyrightMessage();

// Message output functions -------------------------------------------------

//%name (OutputMessageFunction) extern typedef void(*FreeImage_OutputMessageFunction)(FREE_IMAGE_FORMAT fif, const char *msg);
//%name (OutputMessage)	extern static FreeImage_OutputMessageFunction FreeImage_OutputMessage;

//%name (SetOutputMessage) extern void FreeImage_SetOutputMessage(FreeImage_OutputMessageFunction omf);

// MMX routines ------------------------------------------------------------

%name (EnableMMX)	extern void FreeImage_EnableMMX();
%name (DisableMMX) extern void FreeImage_DisableMMX();

// Allocate/Unload routines ------------------------------------------------

%name (Allocate) extern void *FreeImage_Allocate(int width, int height, int bpp);
%name (Free) extern void FreeImage_Free(void *dib);
%name (Unload) extern void FreeImage_Unload(void *dib);

// Image Load routines -----------------------------------------------------

%name (LoadBMP) extern void *FreeImage_LoadBMP(const char *filename, BMPFlags flags = BMP_DEFAULT);
%name (LoadBMPFromHandle) extern void *FreeImage_LoadBMPFromHandle(FreeImageIO *io, fi_handle handle, BMPFlags flags = BMP_DEFAULT);
%name (LoadICO) extern void *FreeImage_LoadICO(const char *filename, ICOFlags flags = ICO_DEFAULT);
%name (LoadICOFromHandle) extern void *FreeImage_LoadICOFromHandle(FreeImageIO *io, fi_handle handle, ICOFlags flags = ICO_DEFAULT);
%name (LoadJPEG) extern void *FreeImage_LoadJPEG(const char *filename, JPEGFlags flags = JPEG_DEFAULT);
%name (LoadJPEGFromHandle) extern void *FreeImage_LoadJPEGFromHandle(FreeImageIO *io, fi_handle handle, JPEGFlags flags = JPEG_DEFAULT);
%name (LoadKOALA)	extern void *FreeImage_LoadKOALA(const char *filename, KOALAFlags flags = KOALA_DEFAULT);
%name (LoadKOALAFromHandle) extern void *FreeImage_LoadKOALAFromHandle(FreeImageIO *io, fi_handle handle, KOALAFlags flags = KOALA_DEFAULT);
%name (LoadPCD) extern void *FreeImage_LoadPCD(const char *filename, PCDFlags flags = PCD_DEFAULT);
%name (LoadPCDFromHandle) extern void *FreeImage_LoadPCDFromHandle(FreeImageIO *io, fi_handle handle, PCDFlags flags = PCD_DEFAULT);
%name (LoadPCX) extern void *FreeImage_LoadPCX(const char *filename, PCXFlags flags = PCX_DEFAULT);
%name (LoadPCXFromHandle) extern void *FreeImage_LoadPCXFromHandle(FreeImageIO *io, fi_handle handle, PCXFlags flags = PCX_DEFAULT);
%name (LoadPNM) extern void *FreeImage_LoadPNM(const char *filename, PNMFlags flags = PNM_DEFAULT);
%name (LoadPNMFromHandle) extern void *FreeImage_LoadPNMFromHandle(FreeImageIO *io, fi_handle handle, PNMFlags flags = PNM_DEFAULT);
%name (LoadPNG) extern void *FreeImage_LoadPNG(const char *filename, PNGFlags flags = PNG_DEFAULT);
%name (LoadPNGFromHandle) extern void *FreeImage_LoadPNGFromHandle(FreeImageIO *io, fi_handle handle, PNGFlags flags = PNG_DEFAULT);
%name (LoadRAS) extern void *FreeImage_LoadRAS(const char *filename, RASFlags flags = RAS_DEFAULT);
%name (LoadRASFromHandle) extern void *FreeImage_LoadRASFromHandle(FreeImageIO *io, fi_handle handle, RASFlags flags = RAS_DEFAULT);
%name (LoadTARGA) extern void *FreeImage_LoadTARGA(const char *filename, TARGAFlags flags = TARGA_DEFAULT);
%name (LoadTARGAFromHandle) extern void *FreeImage_LoadTARGAFromHandle(FreeImageIO *io, fi_handle handle, TARGAFlags flags = TARGA_DEFAULT);
%name (LoadTIFF) extern void *FreeImage_LoadTIFF(const char *filename, TIFFFlags flags = TIFF_DEFAULT);
%name (LoadTIFFFromHandle) extern void *FreeImage_LoadTIFFFromHandle(FreeImageIO *io, fi_handle handle, TIFFFlags flags = TIFF_DEFAULT);

// Image Save routines -----------------------------------------------------

%name (SaveBMP) extern BOOL FreeImage_SaveBMP(void *dib, const char *filename, BMPFlags flags = BMP_DEFAULT);
%name (SaveBMPToHandle) extern BOOL FreeImage_SaveBMPToHandle(void *dib, FreeImageIO *io, fi_handle handle, BMPFlags flags = BMP_DEFAULT);
%name (SaveJPEG) extern BOOL FreeImage_SaveJPEG(void *dib, const char *filename, JPEGFlags flags = JPEG_DEFAULT);
%name (SaveJPEGToHandle) extern BOOL FreeImage_SaveJPEGToHandle(void *dib, FreeImageIO *io, fi_handle handle, JPEGFlags flags = JPEG_DEFAULT);
%name (SavePNG) extern BOOL FreeImage_SavePNG(void *dib, const char *filename, PNGFlags flags = PNG_DEFAULT);
%name (SavePNGToHandle) extern BOOL FreeImage_SavePNGToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNGFlags flags = PNG_DEFAULT);
%name (SavePNM) extern BOOL FreeImage_SavePNM(void *dib, const char *filename, PNMFlags flags = PNM_DEFAULT);
%name (SavePNMToHandle) extern BOOL FreeImage_SavePNMToHandle(void *dib, FreeImageIO *io, fi_handle handle, PNMFlags flags = PNM_DEFAULT);
%name (SaveTIFF) extern BOOL FreeImage_SaveTIFF(void *dib, const char *filename, TIFFFlags flags = TIFF_DEFAULT);
%name (SaveTIFFToHandle) extern BOOL FreeImage_SaveTIFFToHandle(void *dib, FreeImageIO *io, fi_handle handle, TIFFFlags flags = TIFF_DEFAULT);

// Filetype request routines -----------------------------------------------

%name (GetFileType) extern FREE_IMAGE_FORMAT FreeImage_GetFileType(const char *filename, int size);
%name (GetFileTypeFromHandle)	extern FREE_IMAGE_FORMAT FreeImage_GetFileTypeFromHandle(FreeImageIO *io, fi_handle handle, int size);
%name (GetFileTypeFromExt) extern FREE_IMAGE_FORMAT FreeImage_GetFileTypeFromExt(const char *ext);
%name (GetFileTypeFromFormat) extern const char *FreeImage_GetFileTypeFromFormat(FREE_IMAGE_FORMAT format);

// FreeImage info routines -------------------------------------------------

%name (GetTransparencyCount) extern unsigned FreeImage_GetTransparencyCount(void *dib);
%name (GetTransparencyTable) extern BYTE *FreeImage_GetTransparencyTable(void *dib);
%name (SetTransparencyTable) extern void FreeImage_SetTransparencyTable(void *dib, BYTE *table, BYTE count);

// DIB info routines -------------------------------------------------------

%name (GetColorsUsed) extern unsigned FreeImage_GetColorsUsed(void *dib);
%name (GetBits) extern BYTE * FreeImage_GetBits(void *dib);
%name (GetBitsRowCol) extern BYTE * FreeImage_GetBitsRowCol(void *dib, int col, int row);
%name (GetScanLine) extern BYTE * FreeImage_GetScanLine(void *dib, int scanline);
%name (GetBPP) extern unsigned FreeImage_GetBPP(void *dib);
%name (GetWidth) extern unsigned FreeImage_GetWidth(void *dib);
%name (GetHeight)	extern unsigned FreeImage_GetHeight(void *dib);
%name (GetLine) extern unsigned FreeImage_GetLine(void *dib);
%name (GetPitch) extern unsigned FreeImage_GetPitch(void *dib);
%name (GetDIBSize) extern unsigned FreeImage_GetDIBSize(void *dib);
%name (GetPalette) extern RGBQUAD *FreeImage_GetPalette(void *dib);
%name (GetDotsPerMeterX) extern unsigned FreeImage_GetDotsPerMeterX(void *dib);
%name (GetDotsPerMeterY) extern unsigned FreeImage_GetDotsPerMeterY(void *dib);
%name (GetInfoHeader) extern BITMAPINFOHEADER *FreeImage_GetInfoHeader(void *dib);
%name (GetInfo) extern BITMAPINFO *FreeImage_GetInfo(void *dib);
%name (GetColorType) extern FREE_IMAGE_COLOR_TYPE FreeImage_GetColorType(void *dib);

// Conversion routines -----------------------------------------------------

%name (ConvertToGreyscale) extern void FreeImage_ConvertToGreyscale(void *dib);
%name (ConvertTo8Bits) extern void *FreeImage_ConvertTo8Bits(void *dib, BOOL type555 = FALSE);
%name (ConvertTo16Bits) extern void *FreeImage_ConvertTo16Bits(void *dib, BOOL type555 = FALSE);
%name (ConvertTo24Bits) extern void *FreeImage_ConvertTo24Bits(void *dib, BOOL type555 = FALSE);
%name (ConvertTo32Bits) extern void *FreeImage_ConvertTo32Bits(void *dib, BOOL type555 = FALSE);
%name (ColorQuantize) extern void * FreeImage_ColorQuantize(void *dib, FREE_IMAGE_QUANTIZE quantize);

// Effects -----------------------------------------------------------------

%name (Clone) extern void *FreeImage_Clone(void *dib);
%name (Blur) extern void FreeImage_Blur(void *dib);
%name (Brighten) extern void FreeImage_Brighten(void *dib, double factor);
%name (Combine) extern void FreeImage_Combine(void *dib1, void *dib2, int x, int y, unsigned int alpha = 256);
%name (Darken) extern void FreeImage_Darken(void *dib, double factor);
%name (MaskCombine24) extern void FreeImage_MaskCombine24(void *dib1, void *dib2, void *mask, int x, int y);
%name (MaskCombine24Ex) extern void FreeImage_MaskCombine24Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *psrc, void *pmask, int srcx, int srcy);
%name (MaskCombine32) extern void FreeImage_MaskCombine32(void *dib1, void *dib2, int x, int y);
%name (MaskCombine32Ex) extern void FreeImage_MaskCombine32Ex(void *pdst, int dstx, int dsty, unsigned int width, unsigned int height, void *pSrc, int srcx, int srcy);
%name (AddAlphaMask) extern void FreeImage_AddAlphaMask(void *dib, void *mask);
%name (Crop) extern void *FreeImage_Crop(void *dib, int left, int top, int right, int bottom);
%name (Flip) extern void FreeImage_Flip(void *dib);
%name (Mirror) extern void FreeImage_Mirror(void *dib);
%name (Invert) extern void FreeImage_Invert(void *dib);
%name (Rotate) extern void *FreeImage_Rotate(void *dib, double angle);
