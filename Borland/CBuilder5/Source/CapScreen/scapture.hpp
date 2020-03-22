// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SCapture.pas' rev: 5.00

#ifndef SCaptureHPP
#define SCaptureHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Clipbrd.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Scapture
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TScreenCapture;
class PASCALIMPLEMENTATION TScreenCapture : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	Graphics::TBitmap* fBitmap;
	bool fActive;
	bool fAutocopy;
	bool fDesktop;
	Classes::TNotifyEvent fOnCapture;
	void __fastcall SetActive(bool Value);
	
protected:
	virtual void __fastcall loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TScreenCapture(Classes::TComponent* AOwner);
	__fastcall virtual ~TScreenCapture(void);
	Graphics::TBitmap* __fastcall Bitmap(void);
	void __fastcall Capture(void);
	void __fastcall Copytoclipboard(void);
	
__published:
	__property bool Autocopy = {read=fAutocopy, write=fAutocopy, nodefault};
	__property bool Active = {read=fActive, write=SetActive, nodefault};
	__property bool Desktop = {read=fDesktop, write=fDesktop, nodefault};
	__property Classes::TNotifyEvent OnCapture = {read=fOnCapture, write=fOnCapture};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TScreenCapture(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Scapture */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Scapture;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SCapture
