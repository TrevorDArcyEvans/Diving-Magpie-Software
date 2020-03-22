#include <vcl.h>
#include <sharemem.hpp>
#pragma hdrstop

#include "Unit3.h"

#pragma package(smart_init)
#pragma link "ZipBuilder"
#pragma resource "*.dfm"

#pragma link "ZIPBuilder"

TForm3 *Form3;

//---------------------------------------------------------------------------
void __fastcall TForm3::AddButClick( TObject *Sender ) {
	Memo1->Clear();
	Memo1->Lines->Add( "Adding test*.txt to test1.zip" );
	ZipBuilder1->ZipFilename = "test1.zip";
	ZipBuilder1->Verbose = true;

	// Add as many filespecs as we want to:
	// (MS-DOS Wildcards are OK)
	ZipBuilder1->FSpecArgs->Add( "test*.txt" );
	// Set the AddOptions; these also appear in Property Inspector:
	// NOTE: This is the new "set" syntax
	ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddHiddenFiles;
	ZipBuilder1->AddOptions = ZipBuilder1->AddOptions >> AddEncrypt; // no password
	ZipBuilder1->Add();  // do it!
}

//---------------------------------------------------------------------------
void __fastcall TForm3::ZipBuilder1Message( TObject *Sender, int ErrCode, String Message ) {
	// Add a message from the DLLs to the memo box
	Memo1->Lines->Add( Message );
}

//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click( TObject *Sender ) {
	Close();  // exit program
}

//---------------------------------------------------------------------------
void __fastcall TForm3::ExtrButClick( TObject *Sender ) {
	Memo1->Clear();
	if ( !FileExists( "test1.zip" ) ) {
		ShowMessage( "Error - test1.zip not found; do a Add first" );
		return;
	}
	Memo1->Lines->Add( "Extracting from test1.zip" );
	ZipBuilder1->ZipFilename = "test1.zip";
	ZipBuilder1->Verbose = true;

	// We can specify as many filespecs as we want to extract:
	// (MS-DOS Wildcards are OK)
	ZipBuilder1->FSpecArgs->Add( "test*.txt" );

	// Set the ExtrOptions; these also appear in Property Inspector:
	ZipBuilder1->ExtrOptions = ZipBuilder1->ExtrOptions << ExtrOverWrite;
	ZipBuilder1->Extract();  // do it!
}

//---------------------------------------------------------------------------
void __fastcall TForm3::VersButClick( TObject *Sender ) {
	char outbuf[80];

	// When using a C string for output, I can use sprintf to format, and
	// MessageBox to display.
	// I could have used an AnsiString, and it's Format method, and
	// ShowMessage to display.
	sprintf( outbuf, "ZIPDLL.DLL = %d,  UNZDLL.DLL = %d", ZipBuilder1->ZipVers, ZipBuilder1->UnzVers );
	MessageBox( Handle, outbuf, "DLL Versions", MB_OK + MB_ICONINFORMATION );
}

//---------------------------------------------------------------------------
void __fastcall TForm3::ListButClick( TObject *Sender ) {
	int i;
	ZipDirEntry *dirp;
	char fname[80], datetime[20], outbuf[120];

	Memo1->Clear();
	if ( !FileExists( "test1.zip" ) ) {
		ShowMessage( "Error - test1.zip not found; do a Add first" );
		return;
	}
	Memo1->Lines->Add( "Listing test1.zip" );
	// The ZipContents TList is automatically filled with the contents of the
	// zipfile when the filename is assigned.
	ZipBuilder1->ZipFilename = "test1.zip";

	if ( !ZipBuilder1->Count ) return;     // no files in archive, or bad archive

	// I normally prefer to use TSortGrid for showing the user this info.
	// In this demo, I'm just using a plain memo so I can demonstrate how
	// to manipulate the strings and integers for display.  I want to
	// emphasize how to use C with the VCL components.

	// Print some column headers
	Memo1->Lines->Add( "Filename         Cmp byt  Unc byt      Date/Time" );
	for ( i = 0; i < ZipBuilder1->Count; i++ ) {
		// ZipContents is a TList, which contains an array of pointers
      // to ZipDirEntry structs.
      dirp = (ZipDirEntry *)(ZipBuilder1->ZipContents->Items[i]);

      // In this demo, I'm going to convert the AnsiStrings to C strings
      // in order to use sprintf for the output formatting.  It would have
      // also been possible to use the Format method of AnsiString to do
      // output formatting.
      strcpy( fname, dirp->FileName.c_str() );
      strcpy( datetime, FormatDateTime( "ddddd  t", FileDateToDateTime( dirp->DateTime )).c_str() );
      sprintf( outbuf, "%-16s %6d   %6d    %-16s", fname, dirp->CompressedSize, dirp->UncompressedSize, datetime );
      Memo1->Lines->Add( outbuf );
   } // end for
}

//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate( TObject *Sender ) {
   // The easiest way to handle DLL loading and unloading is to load them in
   // the form's OnCreate event handler, and unload them in the form's
   // OnDestroy event handler.
   ZipBuilder1->Load_Zip_Dll();
   ZipBuilder1->Load_Unz_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TForm3::FormDestroy( TObject *Sender ) {
   ZipBuilder1->Unload_Zip_Dll();
   ZipBuilder1->Unload_Unz_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TForm3::TestButClick( TObject *Sender ) {
   Memo1->Clear();
   if ( !FileExists( "test1.zip" ) ) {
      ShowMessage( "Error - test1.zip not found; do a Zip first" );
      return;
   }
   Memo1->Lines->Add( "Testing test1.zip" );
   ZipBuilder1->ZipFilename = "test1.zip";
   ZipBuilder1->Verbose = true;

   // TEST ONLY, do NOT extract!
   ZipBuilder1->ExtrOptions = ZipBuilder1->ExtrOptions << ExtrTest;

   ZipBuilder1->Extract();  // do it! (just test, don't save extracted files)
}

//---------------------------------------------------------------------------
void __fastcall TForm3::DeleteButClick( TObject *Sender ) {
   Memo1->Clear();
   if ( !FileExists( "test1.zip" ) ) {
      ShowMessage( "Error - test1.zip not found; do a Zip first" );
      return;
   }
   Memo1->Lines->Add( "Deleting from test1.zip" );
   ZipBuilder1->ZipFilename = "test1.zip";
   ZipBuilder1->Verbose = true;

   // We can specify as many filespecs as we want to delete:
   // (MS-DOS Wildcards are OK)
   ZipBuilder1->FSpecArgs->Add( "testa.txt" );
   ZipBuilder1->FSpecArgs->Add( "testb.txt" );

   ZipBuilder1->Delete();  // do it!
}

//---------------------------------------------------------------------------
void __fastcall TForm3::AddPwdButClick( TObject *Sender ) {
   Memo1->Clear();
   Memo1->Lines->Add( "Adding test*.txt to test1.zip" );
   ZipBuilder1->ZipFilename = "test1.zip";
   ZipBuilder1->Verbose     = true;

   // Add as many filespecs as we want to:
   // (MS-DOS Wildcards are OK)
   ZipBuilder1->FSpecArgs->Add( "test*.txt" );
   // Set the AddOptions; these also appear in Property Inspector:
   // NOTE: This is the new "set" syntax
   ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddEncrypt;
   ZipBuilder1->Add();  // do it!
}

