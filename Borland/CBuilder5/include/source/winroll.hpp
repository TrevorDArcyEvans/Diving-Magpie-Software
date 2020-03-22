// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinRoll.pas' rev: 4.00

#ifndef WinRollHPP
#define WinRollHPP

#pragma delphiheader begin
#pragma option push -w-
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

namespace Winroll
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EOwnerError;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION EOwnerError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EOwnerError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EOwnerError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EOwnerError(int Ident, Extended Dummy) : Sysutils::Exception(
		Ident, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EOwnerError(int Ident, const System::TVarRec * Args, 
		const int Args_Size) : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EOwnerError(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EOwnerError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EOwnerError(int Ident, int AHelpContext) : Sysutils::Exception(
		Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EOwnerError(int Ident, const System::TVarRec * Args
		, const int Args_Size, int AHelpContext) : Sysutils::Exception(Ident, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EOwnerError(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

#pragma option push -b-
enum TRollerMode { mdRollDown, mdRollUp };
#pragma option pop

typedef void __fastcall (__closure *TRollerNotifyEvent)(System::TObject* Sender, TRollerMode mode);

class DELPHICLASS TWinRoller;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TWinRoller : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	void *DefWinProc;
	void *DefWinProcInstance;
	bool FEnabled;
	TRollerNotifyEvent FOnRoller;
	Classes::TNotifyEvent FOnFormDestroy;
	bool FRoller;
	bool FVisible;
	Windows::TRect ButtonArea;
	bool DrawPushed;
	bool Pushed;
	bool RestoreWndProc;
	HRGN rgn;
	bool Stop;
	void __fastcall CalcArea(void);
	void __fastcall OnRollerDestroy(System::TObject* Sender);
	void __fastcall PaintRollerButton(void);
	void __fastcall Rollup(void);
	void __fastcall SetEnabled(bool Val);
	void __fastcall SetRoller(bool Val);
	void __fastcall SetVisible(bool Val);
	void __fastcall WinProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TWinRoller(Classes::TComponent* Owner);
	__fastcall virtual ~TWinRoller(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
	__property bool Roller = {read=FRoller, write=SetRoller, default=0};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
	__property TRollerNotifyEvent OnRoller = {read=FOnRoller, write=FOnRoller};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE unsigned si;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Winroll */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Winroll;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WinRoll
