#ifndef AddFilesH
#define AddFilesH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <FileCtrl.hpp>

#include "Main.h"

//---------------------------------------------------------------------------
class TAddFile : public TForm {
	__published:	// IDE-managed Components
		TBevel				*Bevel1;
		TButton				*AddFileBut;
		TButton				*RemoveBut;
		TButton				*OKBut;
		TButton				*CancelBut;
		TButton				*SortBut;
		TButton				*SelectAllBut;
		TButton				*AddDirBut;
		TButton				*AddWildBttn;
		TButton				*AddWildPathBttn;
		TCheckBox			*DirNameCB;
		TCheckBox			*RecurseCB;
		TCheckBox			*EncryptCB;
		TLabel				*Label1;
		TLabel				*Label3;
		TPanel				*Panel1;
		TPanel				*Panel2;
		TPanel				*Panel3;
		TPanel				*Panel4;
		TPanel				*Panel5;
		TPanel				*Panel6;
		TPanel				*Panel7;
		TPanel				*Panel8;
		TPanel				*Panel9;
		TEdit					*WildEdit;
		TListBox				*SelectedList;
		TLabel				*Label2;
		TDriveComboBox		*DriveComboBox1;
		TFileListBox		*FileListBox1;
		TDirectoryListBox	*DirectoryListBox1;

		void __fastcall OKButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall SortButClick( TObject *Sender );
		void __fastcall RemoveButClick( TObject *Sender );
		void __fastcall SelectAllButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall AddDirButClick( TObject *Sender );
		void __fastcall AddFileButClick( TObject *Sender );
		void __fastcall AddWildBttnClick( TObject *Sender );
		void __fastcall AddWildPathBttnClick( TObject *Sender );

	public:		// User declarations
		__fastcall TAddFile( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TAddFile *AddFile;

extern bool InMouseClick;

#endif

