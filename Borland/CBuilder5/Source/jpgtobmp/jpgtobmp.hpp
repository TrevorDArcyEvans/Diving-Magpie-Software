// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'JpgToBmp.pas' rev: 5.00

#ifndef JpgToBmpHPP
#define JpgToBmpHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Jpgtobmp
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TJpegToBmp;
class PASCALIMPLEMENTATION TJpegToBmp : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Extctrls::TImage* FImage;
	Classes::TStream* FStreamBmp;
	Classes::TStream* FStreamJpg;
	Jpeg::TJPEGImage* FJpeg;
	Graphics::TBitmap* FBmp;
	AnsiString FBmpFile;
	AnsiString FJpegFile;
	
protected:
	void __fastcall FCopyJpegToBmp(void);
	void __fastcall FCopyImageToBmp(void);
	
public:
	__fastcall virtual TJpegToBmp(Classes::TComponent* AOwner);
	__fastcall virtual ~TJpegToBmp(void);
	void __fastcall CopyJpegToBmp(void);
	void __fastcall CopyImageToBmp(void);
	
__published:
	__property Extctrls::TImage* Image = {read=FImage, write=FImage};
	__property AnsiString BmpFile = {read=FBmpFile, write=FBmpFile};
	__property AnsiString JpegFile = {read=FJpegFile, write=FJpegFile};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Jpgtobmp */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Jpgtobmp;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// JpgToBmp
