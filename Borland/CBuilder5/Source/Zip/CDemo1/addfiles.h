#ifndef AddFilesH
#define AddFilesH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <FileCtrl.hpp>

#include "Main.h"
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TAddFile : public TForm {
	__published:	// IDE-managed Components
		TBevel				*Bevel1;
		TCheckBox			*DirNameCB;
		TCheckBox			*RecurseCB;
		TCheckBox			*EncryptCB;
		TCheckBox			*DiskSpanCB;
		TLabel				*Label1;
		TLabel				*Label2;
		TLabel				*Label3;
		TPanel				*Panel1;
		TPanel				*Panel2;
		TButton				*AddFileBut;
		TButton				*RemoveBut;
		TButton				*OKBut;
		TButton				*CancelBut;
		TButton				*SortBut;
		TButton				*SelectAllBut;
		TButton				*AddDirBut;
		TButton				*VolSizeBut;
		TButton				*FreeDisk1But;
		TButton				*AddWildBttn;
		TButton				*AddWildPathBttn;
		TButton				*AddBtn;
		TPanel				*Panel3;
		TPanel				*Panel4;
		TPanel				*Panel5;
		TPanel				*Panel6;
		TPanel				*Panel7;
		TPanel				*Panel8;
		TPanel				*Panel9;
		TListBox				*SelectedList;
		TDriveComboBox		*DriveComboBox1;
		TFileListBox		*FileListBox1;
		TDirectoryListBox	*DirectoryListBox1;
		TEdit					*WildEdit;
		TPopupMenu			*PopupMenu1;
		TMenuItem			*Add1;
		TMenuItem			*Update1;
		TMenuItem			*Freshen1;
		TMenuItem			*Move1;

		void __fastcall OKButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall SortButClick( TObject *Sender );
		void __fastcall RemoveButClick( TObject *Sender );
		void __fastcall SelectAllButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall AddDirButClick( TObject *Sender );
		void __fastcall AddFileButClick( TObject *Sender );
		void __fastcall DiskSpanCBClick( TObject *Sender );
		void __fastcall VolSizeButClick( TObject *Sender );
		void __fastcall FreeDisk1ButClick( TObject *Sender );
		void __fastcall AddWildBttnClick( TObject *Sender );
		void __fastcall AddWildPathBttnClick( TObject *Sender );
		void __fastcall AddBtnClick( TObject *Sender );
		void __fastcall Add1Click( TObject *Sender );

	public:		// User declarations
		__fastcall TAddFile( TComponent *Owner ) : TForm( Owner ) { }

		int ZipAction;
};

//---------------------------------------------------------------------------
extern PACKAGE TAddFile *AddFile;
extern bool InMouseClick;

#endif

