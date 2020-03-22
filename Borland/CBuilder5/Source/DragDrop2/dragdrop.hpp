// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DragDrop.pas' rev: 4.00

#ifndef DragDropHPP
#define DragDropHPP

#pragma delphiheader begin
#pragma option push -w-
#include <ShellAPI.hpp>	// Pascal unit
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

namespace Dragdrop
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TFilesDropped)(int NumItems);

class DELPHICLASS TDragDrop;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TDragDrop : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TFilesDropped FFilesDropped;
	void *OldWndProc;
	void *NewWndProc;
	Classes::TStringList* FList;
	bool FBTF;
	bool FActive;
	void __fastcall HookParent(void);
	void __fastcall UnhookParent(void);
	void __fastcall HookWndProc(Messages::TMessage &Message);
	void __fastcall SetActive(bool YesNo);
	
public:
	__fastcall virtual TDragDrop(Classes::TComponent* AOwner);
	__fastcall virtual ~TDragDrop(void);
	__property Classes::TStringList* DroppedFiles = {read=FList};
	
__published:
	void __fastcall ClearList(void);
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property bool BringToFront = {read=FBTF, write=FBTF, nodefault};
	__property TFilesDropped OnFilesDropped = {read=FFilesDropped, write=FFilesDropped};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dragdrop */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dragdrop;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DragDrop
