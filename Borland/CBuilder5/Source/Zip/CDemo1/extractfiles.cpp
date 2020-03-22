#include <vcl\vcl.h>
#pragma hdrstop

#include "ExtractFiles.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExtract *Extract;

//---------------------------------------------------------------------------
void __fastcall TExtract::OKButClick( TObject *Sender ) {
	Canceled   = false;
	ExtractDir = DirectoryListBox1->Directory;
	ExpandDirs = ( !RadioGroup1->ItemIndex ) ? false : true;
	OverWr	  = ( !RadioGroup2->ItemIndex ) ? false : true;
	AllFiles	  = ( !RadioGroup3->ItemIndex ) ? true  : false;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TExtract::CancelButClick( TObject *Sender ) {
	ExtractDir = "";
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TExtract::FormActivate(TObject *Sender) {
	Canceled = true;					 // Default.
}

//---------------------------------------------------------------------------
void __fastcall TExtract::FormCreate( TObject *Sender ) {
	String SpecFolder = "";

	MainForm->GetSpecialFolder( CSIDL_DESKTOPDIRECTORY, SpecFolder );
	DriveComboBox1->Drive = ExtractFileDrive( SpecFolder )[1];
	DirectoryListBox1->Directory = ExtractFilePath( SpecFolder );
}

