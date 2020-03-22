// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Regi1632.pas' rev: 4.00

#ifndef Regi1632HPP
#define Regi1632HPP

#pragma delphiheader begin
#pragma option push -w-
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Regi1632
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TRegistry1632;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TRegistry1632 : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool fRunningWin31;
	AnsiString fIniFileName;
	bool fWasError;
	AnsiString fErrorMessage;
	AnsiString __fastcall ReadKey(int Where, AnsiString Key, AnsiString Path);
	void __fastcall WriteKey(int Where, AnsiString Key, AnsiString Path, AnsiString Value);
	
public:
	__fastcall virtual TRegistry1632(Classes::TComponent* AOwner);
	__fastcall virtual ~TRegistry1632(void);
	AnsiString __fastcall ReadString(AnsiString Path, AnsiString Key);
	AnsiString __fastcall ReadUserString(AnsiString Path, AnsiString Key);
	void __fastcall WriteString(AnsiString Path, AnsiString Key, AnsiString Value);
	void __fastcall WriteUserString(AnsiString Path, AnsiString Key, AnsiString Value);
	__property bool WasError = {read=fWasError, nodefault};
	__property AnsiString ErrorMessage = {read=fErrorMessage};
	
__published:
	__property bool RunningWin31 = {read=fRunningWin31, write=fRunningWin31, nodefault};
	__property AnsiString IniFileName = {read=fIniFileName, write=fIniFileName};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define keynotfoundvalue "xyxyxyxyxyxyxyxyxyxyxyxyxyx"
extern PACKAGE void __fastcall Register(void);

}	/* namespace Regi1632 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Regi1632;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Regi1632
