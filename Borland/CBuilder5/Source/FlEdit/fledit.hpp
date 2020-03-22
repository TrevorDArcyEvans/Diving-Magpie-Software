// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FlEdit.pas' rev: 5.00

#ifndef FlEditHPP
#define FlEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Fledit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFloatEdit;
class PASCALIMPLEMENTATION TFloatEdit : public Stdctrls::TEdit 
{
	typedef Stdctrls::TEdit inherited;
	
private:
	Byte FDigits;
	Extended FMin;
	Extended FMax;
	char fdec;
	AnsiString Fertext;
	Extended foldval;
	
protected:
	void __fastcall setvalue(Extended Newvalue);
	void __fastcall setmin(Extended Newvalue);
	void __fastcall setmax(Extended Newvalue);
	void __fastcall setdigits(Byte Newvalue);
	Extended __fastcall getvalue(void);
	DYNAMIC void __fastcall KeyPress(char &Key);
	DYNAMIC void __fastcall doexit(void);
	DYNAMIC void __fastcall doEnter(void);
	
__published:
	__property Byte Digits = {read=FDigits, write=setdigits, nodefault};
	__property Extended Value = {read=getvalue, write=setvalue};
	__property Extended Min = {read=FMin, write=setmin};
	__property Extended Max = {read=FMax, write=setmax};
	__property AnsiString ErrorMessage = {read=Fertext, write=Fertext};
	__fastcall virtual TFloatEdit(Classes::TComponent* aowner);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFloatEdit(HWND ParentWindow) : Stdctrls::TEdit(
		ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TFloatEdit(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define notext "[No Text]"
extern PACKAGE void __fastcall Register(void);

}	/* namespace Fledit */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Fledit;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FlEdit
