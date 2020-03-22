// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AviWriter.pas' rev: 5.00

#ifndef AviWriterHPP
#define AviWriterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ActiveX.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Aviwriter
{
//-- type declarations -------------------------------------------------------
typedef int LONG;

typedef void *PVOID;

struct TAVIFileInfoW
{
	unsigned dwMaxBytesPerSec;
	unsigned dwFlags;
	unsigned dwCaps;
	unsigned dwStreams;
	unsigned dwSuggestedBufferSize;
	unsigned dwWidth;
	unsigned dwHeight;
	unsigned dwScale;
	unsigned dwRate;
	unsigned dwLength;
	unsigned dwEditCount;
	wchar_t szFileType[64];
} ;

typedef TAVIFileInfoW *PAVIFileInfoW;

struct TAVIStreamInfoA
{
	unsigned fccType;
	unsigned fccHandler;
	unsigned dwFlags;
	unsigned dwCaps;
	Word wPriority;
	Word wLanguage;
	unsigned dwScale;
	unsigned dwRate;
	unsigned dwStart;
	unsigned dwLength;
	unsigned dwInitialFrames;
	unsigned dwSuggestedBufferSize;
	unsigned dwQuality;
	unsigned dwSampleSize;
	Windows::TRect rcFrame;
	unsigned dwEditCount;
	unsigned dwFormatChangeCount;
	char szName[64];
} ;

typedef TAVIStreamInfoA  TAVIStreamInfo;

typedef TAVIStreamInfoA *PAVIStreamInfo;

struct TAVIStreamInfoW
{
	unsigned fccType;
	unsigned fccHandler;
	unsigned dwFlags;
	unsigned dwCaps;
	Word wPriority;
	Word wLanguage;
	unsigned dwScale;
	unsigned dwRate;
	unsigned dwStart;
	unsigned dwLength;
	unsigned dwInitialFrames;
	unsigned dwSuggestedBufferSize;
	unsigned dwQuality;
	unsigned dwSampleSize;
	Windows::TRect rcFrame;
	unsigned dwEditCount;
	unsigned dwFormatChangeCount;
	wchar_t szName[64];
} ;

typedef void *PAVIStream;

typedef void *PAVIFile;

typedef void *TAVIStreamList[1];

typedef void * *PAVIStreamList;

typedef int __stdcall (*TAVISaveCallback)(int nPercent);

#pragma pack(push, 1)
struct TAVICompressOptions
{
	unsigned fccType;
	unsigned fccHandler;
	unsigned dwKeyFrameEvery;
	unsigned dwQuality;
	unsigned dwBytesPerSecond;
	unsigned dwFlags;
	void *lpFormat;
	unsigned cbFormat;
	void *lpParms;
	unsigned cbParms;
	unsigned dwInterleaveEvery;
} ;
#pragma pack(pop)

typedef TAVICompressOptions *PAVICompressOptions;

#pragma pack(push, 1)
struct TAVIPalChange
{
	Byte bFirstEntry;
	Byte bNumEntries;
	Word wFlags;
	tagPALETTEENTRY peNew[256];
} ;
#pragma pack(pop)

typedef TAVIPalChange *PAVIPalChange;

typedef void *APAVISTREAM[2];

typedef TAVICompressOptions *APAVICompressOptions[2];

#pragma option push -b-
enum TPixelFormat { pfDevice, pf1bit, pf4bit, pf8bit, pf15bit, pf16bit, pf24bit, pf32bit, pfCustom }
	;
#pragma option pop

class DELPHICLASS TAviWriter;
class PASCALIMPLEMENTATION TAviWriter : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString TempFileName;
	void *pFile;
	int fHeight;
	int fWidth;
	bool fStretch;
	int fFrameTime;
	AnsiString fFileName;
	AnsiString fWavFileName;
	int FrameCount;
	void *VideoStream;
	void *AudioStream;
	void __fastcall AddVideo(void);
	void __fastcall AddAudio(void);
	void __fastcall InternalGetDIBSizes(HBITMAP Bitmap, int &InfoHeaderSize, int &ImageSize, TPixelFormat 
		PixelFormat);
	bool __fastcall InternalGetDIB(HBITMAP Bitmap, HPALETTE Palette, void *BitmapInfo, void *Bits, TPixelFormat 
		PixelFormat);
	void __fastcall InitializeBitmapInfoHeader(HBITMAP Bitmap, tagBITMAPINFOHEADER &Info, TPixelFormat 
		PixelFormat);
	void __fastcall SetWavFileName(AnsiString value);
	
public:
	Classes::TList* Bitmaps;
	__fastcall virtual TAviWriter(Classes::TComponent* AOwner);
	__fastcall virtual ~TAviWriter(void);
	void __fastcall Write(void);
	
__published:
	__property int Height = {read=fHeight, write=fHeight, nodefault};
	__property int Width = {read=fWidth, write=fWidth, nodefault};
	__property int FrameTime = {read=fFrameTime, write=fFrameTime, nodefault};
	__property bool Stretch = {read=fStretch, write=fStretch, nodefault};
	__property AnsiString FileName = {read=fFileName, write=fFileName};
	__property AnsiString WavFileName = {read=fWavFileName, write=SetWavFileName};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint AVIF_HASINDEX = 0x10;
static const Shortint AVIF_MUSTUSEINDEX = 0x20;
static const Word AVIF_ISINTERLEAVED = 0x100;
static const int AVIF_WASCAPTUREFILE = 0x10000;
static const int AVIF_COPYRIGHTED = 0x20000;
static const int AVIF_KNOWN_FLAGS = 0x30130;
static const unsigned AVIERR_UNSUPPORTED = 0x80044065;
static const unsigned AVIERR_BADFORMAT = 0x80044066;
static const unsigned AVIERR_MEMORY = 0x80044067;
static const unsigned AVIERR_INTERNAL = 0x80044068;
static const unsigned AVIERR_BADFLAGS = 0x80044069;
static const unsigned AVIERR_BADPARAM = 0x8004406a;
static const unsigned AVIERR_BADSIZE = 0x8004406b;
static const unsigned AVIERR_BADHANDLE = 0x8004406c;
static const unsigned AVIERR_FILEREAD = 0x8004406d;
static const unsigned AVIERR_FILEWRITE = 0x8004406e;
static const unsigned AVIERR_FILEOPEN = 0x8004406f;
static const unsigned AVIERR_COMPRESSOR = 0x80044070;
static const unsigned AVIERR_NOCOMPRESSOR = 0x80044071;
static const unsigned AVIERR_READONLY = 0x80044072;
static const unsigned AVIERR_NODATA = 0x80044073;
static const unsigned AVIERR_BUFFERTOOSMALL = 0x80044074;
static const unsigned AVIERR_CANTCOMPRESS = 0x80044075;
static const unsigned AVIERR_USERABORT = 0x800440c6;
static const unsigned AVIERR_ERROR = 0x800440c7;
static const Shortint AVISF_DISABLED = 0x1;
static const int AVISF_VIDEO_PALCHANGES = 0x10000;
static const int AVISF_KNOWN_FLAGS = 0x10001;
extern PACKAGE unsigned RIFF_PaletteChange;
static const Shortint AVIERR_OK = 0x0;
static const Shortint AVIIF_LIST = 0x1;
static const Shortint AVIIF_TWOCC = 0x2;
static const Shortint AVIIF_KEYFRAME = 0x10;
static const int streamtypeVIDEO = 0x73646976;
static const int streamtypeAUDIO = 0x73647561;
extern PACKAGE void __fastcall Register(void);
extern "C" void __stdcall AVIFileInit(void);
extern "C" void __stdcall AVIFileExit(void);
extern "C" HRESULT __stdcall AVIFileOpen(void * &ppfile, char * szFile, unsigned uMode, void * lpHandler
	);
extern "C" HRESULT __stdcall AVIFileCreateStream(void * pfile, void * &ppavi, TAVIStreamInfoA &psi);
	
extern "C" HRESULT __stdcall AVIStreamSetFormat(void * pavi, int lPos, void * lpFormat, int cbFormat
	);
extern "C" HRESULT __stdcall AVIStreamReadFormat(void * pavi, int lPos, void * lpFormat, int &cbFormat
	);
extern "C" HRESULT __stdcall AVIStreamWrite(void * pavi, int lStart, int lSamples, void * lpBuffer, 
	int cbBuffer, unsigned dwFlags, int &plSampWritten, int &plBytesWritten);
extern "C" unsigned __stdcall AVIStreamRelease(void * pavi);
extern "C" unsigned __stdcall AVIFileRelease(void * pfile);
extern "C" HRESULT __stdcall AVIFileGetStream(void * pfile, void * &ppavi, unsigned fccType, int lParam
	);
extern "C" HRESULT __stdcall CreateEditableStream(void * &ppsEditable, void * psSource);
extern "C" HRESULT __stdcall AVISaveV(char * szFile, System::PGUID pclsidHandler, TAVISaveCallback lpfnCallback
	, int nStreams, const void * * pavi, const PAVICompressOptions * lpOptions);
#pragma option push -w-inl
inline HRESULT __stdcall AVIFileOpen(void * &ppfile, char * szFile, unsigned uMode, void * lpHandler
	)
{
	return AVIFileOpenA(ppfile, szFile, uMode, lpHandler);
}
#pragma option pop


#pragma option push -w-inl
inline HRESULT __stdcall AVIFileCreateStream(void * pfile, void * &ppavi, TAVIStreamInfoA &psi)
{
	return AVIFileCreateStreamA(pfile, ppavi, psi);
}
#pragma option pop



}	/* namespace Aviwriter */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Aviwriter;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AviWriter
