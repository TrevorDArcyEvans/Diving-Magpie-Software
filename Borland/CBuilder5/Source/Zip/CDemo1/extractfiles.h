#ifndef ExtractFilesH
#define ExtractFilesH

//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\FileCtrl.hpp>

#include "Main.h"

//---------------------------------------------------------------------------
class TExtract : public TForm {
	__published:	// IDE-managed Components
		TPanel				*Panel1;
		TPanel				*Panel2;
		TPanel				*Panel3;
		TButton				*OKBut;
		TButton				*CancelBut;
		TRadioGroup			*RadioGroup1;
		TRadioGroup			*RadioGroup2;
		TRadioGroup			*RadioGroup3;
		TDriveComboBox		*DriveComboBox1;
		TDirectoryListBox	*DirectoryListBox1;

		void __fastcall OKButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall FormActivate( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );

	public:		// User declarations
		__fastcall TExtract( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TExtract *Extract;

#endif

