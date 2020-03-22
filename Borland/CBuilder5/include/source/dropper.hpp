// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Dropper.pas' rev: 4.00

#ifndef DropperHPP
#define DropperHPP

#pragma delphiheader begin
#pragma option push -w-
#include <ShellAPI.hpp>	// Pascal unit
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

namespace Dropper
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnDrop)(System::TObject* Sender, AnsiString Filename);

class DELPHICLASS TFileDropper;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TFileDropper : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	void *FWndProcInstance;
	int FDefProc;
	Controls::TWinControl* FDropSite;
	TOnDrop FOnDrop;
	bool FAllowDir;
	bool FSubFolder;
	void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall DropFile(int Drop);
	void __fastcall Add(AnsiString Path);
	void __fastcall AddFolder(AnsiString Path);
	bool __fastcall IsDirectory(AnsiString Path);
	
protected:
	__fastcall virtual TFileDropper(Classes::TComponent* AOwner);
	__fastcall virtual ~TFileDropper(void);
	virtual void __fastcall Loaded(void);
	
__published:
	__property Controls::TWinControl* DropSite = {read=FDropSite, write=FDropSite};
	__property TOnDrop OnDrop = {read=FOnDrop, write=FOnDrop};
	__property bool AllowDir = {read=FAllowDir, write=FAllowDir, nodefault};
	__property bool SubFolders = {read=FSubFolder, write=FSubFolder, nodefault};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dropper */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dropper;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Dropper
