// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SendKeys.pas' rev: 5.00

#ifndef SendKeysHPP
#define SendKeysHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Dialogs.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sendkeys
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TSendKeys;
class PASCALIMPLEMENTATION TSendKeys : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	HWND __fastcall HandleFromTitle(const AnsiString titletext);
	void __fastcall SendKeys(const AnsiString text);
	void __fastcall MakeWindowActive(HWND whandle);
	void __fastcall SendKeysTo(AnsiString Titletext, const AnsiString text);
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TSendKeys(Classes::TComponent* AOwner) : Classes::TComponent(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TSendKeys(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const char SK_BKSP = '\x8';
static const char SK_TAB = '\x9';
static const char SK_ENTER = '\xd';
static const char SK_ESC = '\x1b';
static const char SK_F1 = '\xe4';
static const char SK_F2 = '\xe5';
static const char SK_F3 = '\xe6';
static const char SK_F4 = '\xe7';
static const char SK_F5 = '\xe8';
static const char SK_F6 = '\xe9';
static const char SK_F7 = '\xea';
static const char SK_F8 = '\xeb';
static const char SK_F9 = '\xec';
static const char SK_F10 = '\xed';
static const char SK_F11 = '\xee';
static const char SK_F12 = '\xef';
static const char SK_HOME = '\xf0';
static const char SK_END = '\xf1';
static const char SK_UP = '\xf2';
static const char SK_DOWN = '\xf3';
static const char SK_LEFT = '\xf4';
static const char SK_RIGHT = '\xf5';
static const char SK_PGUP = '\xf6';
static const char SK_PGDN = '\xf7';
static const char SK_INS = '\xf8';
static const char SK_DEL = '\xf9';
static const char SK_SHIFT_DN = '\xfa';
static const char SK_SHIFT_UP = '\xfb';
static const char SK_CTRL_DN = '\xfc';
static const char SK_CTRL_UP = '\xfd';
static const char SK_ALT_DN = '\xfe';
static const char SK_ALT_UP = '\xff';
extern PACKAGE void __fastcall Register(void);

}	/* namespace Sendkeys */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Sendkeys;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SendKeys
