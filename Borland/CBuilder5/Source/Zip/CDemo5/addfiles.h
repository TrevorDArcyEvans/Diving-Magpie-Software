#ifndef AddFilesH
#define AddFilesH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <FileCtrl.hpp>

#include "ZipBuilder.h"

#include "Main5.h"

//---------------------------------------------------------------------------
class TAddForm : public TForm {
	__published:		// IDE-managed Components
		TButton				*AddFileBut;
		TButton				*RemoveBut;
		TButton				*OKBut;
		TButton				*CancelBut;
		TButton				*SortBut;
		TButton				*SelectAllBut;
		TButton				*AddDirBut;
		TLabel				*Label1;
		TPanel				*Panel1;
		TPanel				*Panel2;
		TPanel				*Panel3;
		TPanel				*Panel4;
		TPanel				*Panel5;
		TPanel				*Panel6;
		TPanel				*Panel7;
		TPanel				*Panel8;
		TListBox				*SelectedList;
		TDriveComboBox		*DriveComboBox1;
		TFileListBox		*FileListBox1;
		TDirectoryListBox	*DirectoryListBox1;

		void __fastcall FormCreate( TObject *Sender );
		void __fastcall OKButClick( TObject *Sender );
		void __fastcall SortButClick( TObject *Sender );
		void __fastcall AddDirButClick( TObject *Sender );
		void __fastcall RemoveButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall AddFileButClick( TObject *Sender );
		void __fastcall SelectAllButClick( TObject *Sender );

	public:			// User declarations
		__fastcall TAddForm( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TAddForm *AddForm;

extern bool InMouseClick;
extern bool Cancelled;

#endif

