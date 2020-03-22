// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Just1_32.pas' rev: 5.00

#ifndef Just1_32HPP
#define Just1_32HPP

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

namespace Just1_32
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TJustOne32;
class PASCALIMPLEMENTATION TJustOne32 : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FAbout;
	
public:
	__fastcall virtual TJustOne32(Classes::TComponent* AOwner);
	__fastcall virtual ~TJustOne32(void);
	void __fastcall ShowAbout(void);
	
__published:
	__property AnsiString About = {read=FAbout, write=FAbout, stored=false};
};


class DELPHICLASS TPreviousInstance;
class PASCALIMPLEMENTATION TPreviousInstance : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	AnsiString FAppName;
	unsigned FMutexHandle;
	bool FhPrevInst;
	AnsiString __fastcall GetAppName();
	void __fastcall SetAppName(AnsiString filename);
	
public:
	__property AnsiString AppName = {read=GetAppName, write=SetAppName};
	__property unsigned MutexHandle = {read=FMutexHandle, write=FMutexHandle, nodefault};
	__property bool hPrevInst = {read=FhPrevInst, write=FhPrevInst, nodefault};
	void __fastcall SethPrevInst(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPreviousInstance(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPreviousInstance(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Just1_32 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Just1_32;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Just1_32
