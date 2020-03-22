// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'PNGImage.pas' rev: 5.00

#ifndef PNGImageHPP
#define PNGImageHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Pngimage
{
//-- type declarations -------------------------------------------------------
typedef Byte *TFilterRow[5];

#pragma option push -b-
enum TEncodeFilter { efNone, efSub, efUp, efAverage, efPaeth };
#pragma option pop

typedef Set<TEncodeFilter, efNone, efPaeth>  TEncodeFilterSet;

typedef char TChunkType[4];

class DELPHICLASS TChunk;
class DELPHICLASS TChunkList;
class DELPHICLASS TChunkIHDR;
class DELPHICLASS TChunkGAMA;
class DELPHICLASS TPNGImage;
class PASCALIMPLEMENTATION TChunk : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TChunk(TChunkList* AOwner);
	__fastcall virtual ~TChunk(void);
	
private:
	TChunkList* fList;
	Classes::TMemoryStream* fStream;
	int __fastcall GetSize(void);
	TChunkIHDR* __fastcall GetIHDR(void);
	TChunkGAMA* __fastcall GetGAMA(void);
	TPNGImage* __fastcall GetBitmap(void);
	
protected:
	char fType[4];
	int __fastcall GetIndex(void);
	virtual void __fastcall DoAction(void);
	__property TChunkIHDR* IHDR = {read=GetIHDR};
	__property TChunkGAMA* GAMA = {read=GetGAMA};
	__property TPNGImage* Bitmap = {read=GetBitmap};
	__property Classes::TMemoryStream* Stream = {read=fStream};
	
public:
	virtual void __fastcall Assign(TChunk* Source);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	__property int Index = {read=GetIndex, nodefault};
	__property TChunkList* Owner = {read=fList};
	__property int Size = {read=GetSize, nodefault};
	;
};


class DELPHICLASS TChunkIEND;
class PASCALIMPLEMENTATION TChunkIEND : public TChunk 
{
	typedef TChunk inherited;
	
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkIEND(TChunkList* AOwner) : TChunk(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkIEND(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkTEXT;
class PASCALIMPLEMENTATION TChunkTEXT : public TChunk 
{
	typedef TChunk inherited;
	
public:
	__fastcall virtual TChunkTEXT(TChunkList* AOwner);
	
private:
	AnsiString __fastcall GetValue(int Index);
	void __fastcall SetValue(int Index, AnsiString Value);
	
public:
	__property AnsiString Keyword = {read=GetValue, write=SetValue, index=0};
	__property AnsiString Text = {read=GetValue, write=SetValue, index=1};
public:
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkTEXT(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkZTXT;
class PASCALIMPLEMENTATION TChunkZTXT : public TChunk 
{
	typedef TChunk inherited;
	
private:
	AnsiString __fastcall GetValue(int Index);
	void __fastcall SetValue(int Index, AnsiString Value);
	
public:
	__property AnsiString Keyword = {read=GetValue, write=SetValue, index=0};
	__property AnsiString Text = {read=GetValue, write=SetValue, index=1};
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkZTXT(TChunkList* AOwner) : TChunk(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkZTXT(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TChunkGAMA : public TChunk 
{
	typedef TChunk inherited;
	
public:
	__fastcall virtual TChunkGAMA(TChunkList* AOwner);
	virtual void __fastcall Assign(TChunk* Source);
	
protected:
	Byte GammaTable[256];
	Byte InverseTable[256];
	virtual void __fastcall DoAction(void);
	
private:
	unsigned __fastcall GetValue(void);
	void __fastcall SetValue(unsigned Value);
	
public:
	__property unsigned Value = {read=GetValue, write=SetValue, nodefault};
public:
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkGAMA(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkPLTE;
class PASCALIMPLEMENTATION TChunkPLTE : public TChunk 
{
	typedef TChunk inherited;
	
public:
	__fastcall virtual ~TChunkPLTE(void);
	
private:
	HPALETTE fPalette;
	HPALETTE __fastcall GetPalette(void);
	
public:
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	__property HPALETTE Palette = {read=GetPalette, nodefault};
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkPLTE(TChunkList* AOwner) : TChunk(AOwner) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TChunkIHDR : public TChunk 
{
	typedef TChunk inherited;
	
public:
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	__fastcall virtual TChunkIHDR(TChunkList* AOwner);
	
private:
	unsigned __fastcall GetWidth(void);
	unsigned __fastcall GetHeight(void);
	void __fastcall SetWidth(unsigned Value);
	void __fastcall SetHeight(unsigned Value);
	Byte __fastcall GetValue(int Index);
	void __fastcall SetValue(int Index, Byte Value);
	
public:
	__property unsigned Width = {read=GetWidth, write=SetWidth, nodefault};
	__property unsigned Height = {read=GetHeight, write=SetHeight, nodefault};
	__property Byte BitDepth = {read=GetValue, write=SetValue, index=0, nodefault};
	__property Byte ColorType = {read=GetValue, write=SetValue, index=1, nodefault};
	__property Byte Compression = {read=GetValue, write=SetValue, index=2, nodefault};
	__property Byte Filter = {read=GetValue, write=SetValue, index=3, nodefault};
	__property Byte Interlaced = {read=GetValue, write=SetValue, index=4, nodefault};
public:
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkIHDR(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkIDAT;
class PASCALIMPLEMENTATION TChunkIDAT : public TChunk 
{
	typedef TChunk inherited;
	
public:
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	
protected:
	int __fastcall GetBufferWidth(void);
	void __fastcall FilterRow(Byte Filter, Sysutils::PByteArray CurrentRow, Sysutils::PByteArray LastRow
		, int offset, int row_buffer_width);
	int __fastcall EncodeFilterRow(Sysutils::PByteArray row_buffer, const Sysutils::PByteArray * Filter_buffers
		, unsigned row_width, unsigned filter_width);
	virtual void __fastcall DoAction(void);
	int __fastcall GetOffset(void);
	void __fastcall EncodeImage(void);
	void __fastcall SetupPixelFormat(void);
	void __fastcall DecodeNonInterlacedRow(void * ImageData, Sysutils::PByteArray Data, int RowBytes, TChunkGAMA* 
		GamaChunk);
	void __fastcall DecodeInterlacedRow(void * ImageData, Sysutils::PByteArray Data, int ColStart, int 
		ColIncrement, int RowBytes, int Pass, TChunkGAMA* GamaChunk);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkIDAT(TChunkList* AOwner) : TChunk(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkIDAT(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkTIME;
class PASCALIMPLEMENTATION TChunkTIME : public TChunk 
{
	typedef TChunk inherited;
	
public:
	__fastcall virtual TChunkTIME(TChunkList* AOwner);
	System::TDateTime __fastcall GetDateTime(void);
	
private:
	void __fastcall SetDateTime(const System::TDateTime Value);
	
public:
	__property System::TDateTime DateTime = {read=GetDateTime, write=SetDateTime};
public:
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkTIME(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkTRNS;
class PASCALIMPLEMENTATION TChunkTRNS : public TChunk 
{
	typedef TChunk inherited;
	
private:
	Graphics::TColor __fastcall GetRGBColor(void);
	
public:
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	__property Graphics::TColor RGBColor = {read=GetRGBColor, nodefault};
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkTRNS(TChunkList* AOwner) : TChunk(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkTRNS(void) { }
	#pragma option pop
	
};


typedef TMetaClass*TChunkClass;

struct TChunkClassInfo
{
	char ChunkType[4];
	TMetaClass*ChunkClass;
} ;

typedef TChunkClassInfo *pChunkClassInfo;

class DELPHICLASS TChunkClasses;
class PASCALIMPLEMENTATION TChunkClasses : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TChunkClasses(void);
	
private:
	Classes::TList* fList;
	int __fastcall GetCount(void);
	TChunkClassInfo __fastcall GetItem(int Index);
	
public:
	__property int Count = {read=GetCount, nodefault};
	int __fastcall IndexOf(const char * Item)/* overload */;
	int __fastcall IndexOf(TMetaClass* Item)/* overload */;
	void __fastcall Add(const char * ChunkType, TMetaClass* ChunkClass);
	__property TChunkClassInfo Item[int Index] = {read=GetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TChunkClasses(void) : System::TObject() { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TChunkList : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	__fastcall TChunkList(TPNGImage* AOwner);
	__fastcall virtual ~TChunkList(void);
	
private:
	TPNGImage* fImage;
	Classes::TList* fList;
	int __fastcall GetCount(void);
	TChunk* __fastcall GetItem(int Index);
	
public:
	__property TPNGImage* Owner = {read=fImage};
	__property int Count = {read=GetCount, nodefault};
	__property TChunk* Item[int Index] = {read=GetItem/*, default*/};
	void __fastcall Move(int Index1, int Index2);
	TChunk* __fastcall Add(TChunk* Item)/* overload */;
	TChunk* __fastcall Add(TMetaClass* ChunkClass)/* overload */;
	TChunk* __fastcall Add(Classes::TStream* Stream)/* overload */;
	void __fastcall Remove(TChunk* Item);
	int __fastcall IndexOf(TChunk* Chunk)/* overload */;
	int __fastcall IndexOf(TMetaClass* ChunkClass)/* overload */;
	void __fastcall Clear(void);
};


class PASCALIMPLEMENTATION TPNGImage : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
__published:
	__fastcall virtual TPNGImage(void);
	__fastcall virtual ~TPNGImage(void);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	
private:
	Graphics::TBitmap* fMask;
	TEncodeFilterSet fEncodeFilter;
	bool fInterlacing;
	TChunkList* fChunkList;
	void __fastcall SetFilter(TEncodeFilterSet Value);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property TEncodeFilterSet Filter = {read=fEncodeFilter, write=SetFilter, nodefault};
	__property bool Interlacing = {read=fInterlacing, write=fInterlacing, nodefault};
	void __fastcall Clear(void);
	__property TChunkList* Chunks = {read=fChunkList};
	/*         class method */ static void __fastcall RegisterChunkClass(TMetaClass* vmt, const char * 
		ChunkType, TMetaClass* ChunkClass);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_HEADER;
#define Pngimage_PNG_ERROR_INVALID_HEADER System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_HEADER)
	
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_CHUNK_INDEX;
#define Pngimage_PNG_ERROR_INVALID_CHUNK_INDEX System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_CHUNK_INDEX)
	
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_CHUNK_CLASS_INDEX;
#define Pngimage_PNG_ERROR_INVALID_CHUNK_CLASS_INDEX System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_CHUNK_CLASS_INDEX)
	
extern PACKAGE System::ResourceString _PNG_ERROR_CHUNK_INVALID_CRC;
#define Pngimage_PNG_ERROR_CHUNK_INVALID_CRC System::LoadResourceString(&Pngimage::_PNG_ERROR_CHUNK_INVALID_CRC)
	
extern PACKAGE System::ResourceString _PNG_ERROR_IHDR_NOT_FIRST;
#define Pngimage_PNG_ERROR_IHDR_NOT_FIRST System::LoadResourceString(&Pngimage::_PNG_ERROR_IHDR_NOT_FIRST)
	
extern PACKAGE System::ResourceString _PNG_ERROR_NO_IDAT;
#define Pngimage_PNG_ERROR_NO_IDAT System::LoadResourceString(&Pngimage::_PNG_ERROR_NO_IDAT)
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_PLTE;
#define Pngimage_PNG_ERROR_INVALID_PLTE System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_PLTE)
	
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_COLOR_TYPE;
#define Pngimage_PNG_ERROR_INVALID_COLOR_TYPE System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_COLOR_TYPE)
	
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_FILTER_TYPE;
#define Pngimage_PNG_ERROR_INVALID_FILTER_TYPE System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_FILTER_TYPE)
	
extern PACKAGE System::ResourceString _PNG_ERROR_INVALID_INTERLACE;
#define Pngimage_PNG_ERROR_INVALID_INTERLACE System::LoadResourceString(&Pngimage::_PNG_ERROR_INVALID_INTERLACE)
	
extern PACKAGE System::ResourceString _PNG_ERROR_UNKOWN_CRITICAL_CHUNK;
#define Pngimage_PNG_ERROR_UNKOWN_CRITICAL_CHUNK System::LoadResourceString(&Pngimage::_PNG_ERROR_UNKOWN_CRITICAL_CHUNK)
	
extern PACKAGE System::ResourceString _PNG_ERROR_NO_PALETTE;
#define Pngimage_PNG_ERROR_NO_PALETTE System::LoadResourceString(&Pngimage::_PNG_ERROR_NO_PALETTE)
extern PACKAGE System::ResourceString _PNG_INVALID_COLOR_TYPE;
#define Pngimage_PNG_INVALID_COLOR_TYPE System::LoadResourceString(&Pngimage::_PNG_INVALID_COLOR_TYPE)
	
extern PACKAGE System::ResourceString _CHUNK_NOT_CHILD;
#define Pngimage_CHUNK_NOT_CHILD System::LoadResourceString(&Pngimage::_CHUNK_NOT_CHILD)
extern PACKAGE System::ResourceString _TIME_CORRUPTED;
#define Pngimage_TIME_CORRUPTED System::LoadResourceString(&Pngimage::_TIME_CORRUPTED)
extern PACKAGE System::ResourceString _PNG_SHARE;
#define Pngimage_PNG_SHARE System::LoadResourceString(&Pngimage::_PNG_SHARE)
extern PACKAGE System::ResourceString _PNG_SHARE_TITLE;
#define Pngimage_PNG_SHARE_TITLE System::LoadResourceString(&Pngimage::_PNG_SHARE_TITLE)

}	/* namespace Pngimage */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Pngimage;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// PNGImage
