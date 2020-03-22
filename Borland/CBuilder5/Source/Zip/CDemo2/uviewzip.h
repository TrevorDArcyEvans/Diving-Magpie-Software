#ifndef uViewZipH
#define uViewZipH

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\FileCtrl.hpp>
#include <vcl\ExtCtrls.hpp>

#include "ZIPBuilder.h"
#include <Graphics.hpp>

//---------------------------------------------------------------------------
class TfViewZip : public TForm {
	__published:	// IDE-managed Components
		TFileListBox		*FileListBox1;
		TDirectoryListBox	*DirectoryListBox1;
		TDriveComboBox		*DriveComboBox1;
		TEdit					*Edit1;
		TGroupBox			*GroupBox1;
		TMemo					*Memo;
		TButton				*btnTilfoj;
		TButton				*btnOpdater;
		TButton				*btnSlet;
		TButton				*btnAfslut;
		TImage				*Image1;
		TLabel				*Label1;
		TZipBuilder			*ZipBuilder1;

		void __fastcall FormCreate( TObject *Sender );
		void __fastcall FileListBox1DblClick( TObject *Sender );
		void __fastcall btnAfslutClick( TObject *Sender );
		void __fastcall btnTilfojClick( TObject *Sender );
		void __fastcall FormDestroy( TObject *Sender );
		void __fastcall btnOpdaterClick( TObject *Sender );
		void __fastcall btnSletClick( TObject *Sender );
		void __fastcall FileListBox1Change( TObject *Sender );
		void __fastcall ZipBuilder1Message( TObject *Sender, int ErrCode, String Message );

	public:		// User declarations
		__fastcall TfViewZip( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TfViewZip *fViewZip;
#endif

