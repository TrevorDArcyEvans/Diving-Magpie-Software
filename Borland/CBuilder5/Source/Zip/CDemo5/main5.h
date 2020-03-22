#ifndef Main5H
#define Main5H

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include <dir.h>

#include "AddFiles.h"
#include "ZIPBuilder.h"
#include "SortGrid.hpp"

//---------------------------------------------------------------------------
class TMainForm : public TForm {
	__published:	// IDE-managed Components
		TPanel			*Panel1;
		TPanel			*Panel2;
		TPanel			*Panel3;
		TPanel			*Panel4;
		TLabel			*Label1;
		TLabel			*Label2;
		TLabel			*ZipFName;
		TLabel			*FilesLabel;
		TBevel			*Bevel2;
		TBevel			*Bevel1;
		TButton			*AddBut;
		TButton			*CloseBut;
		TButton			*NewZipBut;
		TButton			*DeleteBut;
		TButton			*DeleteZipBut;
		TOpenDialog		*OpenDialog1;
		TZipBuilder		*ZipBuilder1;
		TSortGrid		*StringGrid1;

		void __fastcall AddButClick( TObject *Sender );
		void __fastcall CloseButClick( TObject *Sender );
		void __fastcall DeleteButClick( TObject *Sender );
		void __fastcall NewZipButClick( TObject *Sender );
		void __fastcall DeleteZipButClick( TObject *Sender );
		void __fastcall ZipBuilder1DirUpdate( TObject *Sender );
		void __fastcall ZipBuilder1Message( TObject *Sender, int ErrCode, String Message );
		void __fastcall FormDestroy( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );

	public:			// User declarations
		__fastcall TMainForm( TComponent *Owner ) : TForm( Owner ) { }

		void __fastcall FillGrid( void );
		void __fastcall SetZipFName( String aCaption );
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;

extern bool Cancelled;
#endif

