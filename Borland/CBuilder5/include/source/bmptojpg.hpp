// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'BmpToJpg.pas' rev: 4.00

#ifndef BmpToJpgHPP
#define BmpToJpgHPP

#pragma delphiheader begin
#pragma option push -w-
#include <ExtCtrls.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
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

namespace Bmptojpg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBmpToJpeg;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TBmpToJpeg : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Classes::TStream* FStream;
	Extctrls::TImage* FImage;
	Jpeg::TJPEGImage* FJpeg;
	Graphics::TPicture* FBmp;
	AnsiString FBmpFile;
	AnsiString FJpegFile;
	
protected:
	void __fastcall FCopyBmpToJpeg(void);
	void __fastcall FCopyImageToJpeg(void);
	
public:
	__fastcall virtual TBmpToJpeg(Classes::TComponent* AOwner);
	__fastcall virtual ~TBmpToJpeg(void);
	void __fastcall CopyBmpToJpeg(void);
	void __fastcall CopyImageToJpeg(void);
	
__published:
	__property Extctrls::TImage* Image = {read=FImage, write=FImage};
	__property AnsiString BmpFile = {read=FBmpFile, write=FBmpFile};
	__property AnsiString JpegFile = {read=FJpegFile, write=FJpegFile};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Bmptojpg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Bmptojpg;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// BmpToJpg
