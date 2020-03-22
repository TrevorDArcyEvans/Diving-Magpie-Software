// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TNTEditor.pas' rev: 5.00

#ifndef TNTEditorHPP
#define TNTEditorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <TreeNT.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tnteditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TTreeNTEditor;
class PASCALIMPLEMENTATION TTreeNTEditor : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Buttons::TSpeedButton* CancelButton;
	Buttons::TSpeedButton* OKButton;
	Menus::TPopupMenu* PopupMenu;
	Menus::TMenuItem* InsertNode;
	Menus::TMenuItem* N1;
	Menus::TMenuItem* DeleteNode;
	Extctrls::TPanel* Panel1;
	Extctrls::TPanel* Panel2;
	Forms::TScrollBox* ImageBox;
	Menus::TMenuItem* DuplicateNode;
	Forms::TScrollBox* StateImageBox;
	Stdctrls::TLabel* Label1;
	Stdctrls::TLabel* Label2;
	Stdctrls::TLabel* Label3;
	Buttons::TSpeedButton* FontButton;
	Dialogs::TFontDialog* FontDialog;
	Dialogs::TColorDialog* ColorDialog;
	Stdctrls::TLabel* Label4;
	Buttons::TSpeedButton* ColorButton;
	Stdctrls::TLabel* Label5;
	Stdctrls::TCheckBox* ParentFontBox;
	Stdctrls::TCheckBox* ParentColorBox;
	Forms::TScrollBox* SImageBox;
	Stdctrls::TLabel* Label6;
	Menus::TMenuItem* AddChildItem;
	Stdctrls::TLabel* IntegralLabel;
	Stdctrls::TEdit* IntegralEdit;
	Comctrls::TStatusBar* StatusBar;
	Stdctrls::TLabel* CheckTypeLabel;
	Stdctrls::TLabel* Label8;
	Stdctrls::TCheckBox* EnabledBox;
	Stdctrls::TComboBox* CheckStyleCombo;
	Extctrls::TPanel* Panel3;
	Treent::TTreeNT* Tree;
	Menus::TMenuItem* N2;
	Menus::TMenuItem* Expand;
	Menus::TMenuItem* Collapse;
	Menus::TMenuItem* SelectAll;
	void __fastcall CancelButtonClick(System::TObject* Sender);
	void __fastcall CopyChildren(Treent::TTreeNTNode* Source, Treent::TTreeNTNode* Destination);
	void __fastcall OKButtonClick(System::TObject* Sender);
	void __fastcall FormKeyPress(System::TObject* Sender, char &Key);
	void __fastcall InsertNodeClick(System::TObject* Sender);
	void __fastcall SelectedImageClick(System::TObject* Sender);
	void __fastcall StateImageClick(System::TObject* Sender);
	void __fastcall UnselectedImageClick(System::TObject* Sender);
	void __fastcall DuplicateNodeClick(System::TObject* Sender);
	void __fastcall PopupMenuPopup(System::TObject* Sender);
	void __fastcall TreeChange(System::TObject* Sender, Treent::TTreeNTNode* Node);
	void __fastcall TreeDragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, Controls::TDragState 
		State, bool &Accept);
	void __fastcall TreeDragDrop(System::TObject* Sender, System::TObject* Source, int X, int Y);
	void __fastcall TreeStartDrag(System::TObject* Sender, Controls::TDragObject* &DragObject);
	void __fastcall FontButtonClick(System::TObject* Sender);
	void __fastcall ColorButtonClick(System::TObject* Sender);
	void __fastcall ParentFontBoxClick(System::TObject* Sender);
	void __fastcall ParentColorBoxClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall DeleteNodeClick(System::TObject* Sender);
	void __fastcall AddChildItemClick(System::TObject* Sender);
	void __fastcall IntegralEditChange(System::TObject* Sender);
	void __fastcall TreeKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	void __fastcall IntegralEditEnter(System::TObject* Sender);
	void __fastcall CheckStyleComboChange(System::TObject* Sender);
	void __fastcall EnabledBoxClick(System::TObject* Sender);
	void __fastcall TreeMouseUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall ExpandClick(System::TObject* Sender);
	void __fastcall SelectAllClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	Buttons::TSpeedButton* FirstSImageButton;
	Buttons::TSpeedButton* FirstImageButton;
	Buttons::TSpeedButton* FirstStateButton;
	bool FChanging;
	
public:
	void __fastcall DisplayHint(System::TObject* Sender);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TTreeNTEditor(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTreeNTEditor(Classes::TComponent* AOwner, int 
		Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTreeNTEditor(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TTreeNTEditor(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall EditTreeViewItems(Treent::TTreeNTNodes* EditItems);

}	/* namespace Tnteditor */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Tnteditor;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TNTEditor
