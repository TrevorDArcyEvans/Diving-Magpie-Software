#include <vcl\vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "uViewZip.h"

//---------------------------------------------------------------------------
#pragma link "ZIPBuilder"
#pragma package(smart_init)
#pragma resource "*.dfm"

TfViewZip *fViewZip;

char   *TEMPDir;
char    TempDizPathSz[255];
String  TempDizPath;

//---------------------------------------------------------------------------
void __fastcall TfViewZip::FormCreate( TObject *Sender ) {
    // Find a temp directory by checking environment vars
	 TEMPDir = getenv( "TEMP" );
    if ( strlen( TEMPDir ) == 0 )
    	TEMPDir = getenv( "TMP" );
    if ( strlen( TEMPDir ) == 0 )
       TEMPDir = "C:";  // use root dir of drive C for temp dir
    if ( TEMPDir[strlen( TEMPDir )- 1] == '\\' )
    	TEMPDir[strlen( TEMPDir )- 1] = '\0';

    TempDizPath = AnsiString( TEMPDir ) + "\\FILE_ID.DIZ";
    strcpy( TempDizPathSz, TEMPDir );
    strcat( TempDizPathSz, "\\" );
    strcat( TempDizPathSz, "FILE_ID.DIZ" );

    Label1->Caption     = "";
	 btnTilfoj->Enabled  = false;
    btnOpdater->Enabled = false;
    btnSlet->Enabled    = false;
    ZipBuilder1->Load_Zip_Dll();
	 ZipBuilder1->Load_Unz_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::FileListBox1DblClick( TObject *Sender ) {
    // Read in a Diz file from the archive
    FILE *fil;

    char ch;
    int  cnt = 0;
    char line[255];

    // Keep the zip filename in Label1
    Label1->Caption = MinimizeName( FileListBox1->FileName, Label1->Canvas, Label1->Width );
    Memo->Lines->Clear();
    ZipBuilder1->ZipFilename = FileListBox1->FileName;
    ZipBuilder1->ExtrBaseDir = AnsiString( TEMPDir );
    ZipBuilder1->FSpecArgs->Clear();
    ZipBuilder1->FSpecArgs->Add( "FILE_ID.DIZ" );
    ZipBuilder1->Extract();
    DirectoryListBox1->Update();
    FileListBox1->Update();

    // Read the Diz file into the memo
    fil = fopen( TempDizPathSz, "rt" );
    if ( fil == NULL ) {
	  	 // No diz file, allow creation of new one
	  		btnTilfoj->Enabled  = true;
      	btnOpdater->Enabled = false;
      	btnSlet->Enabled	  = false;
      	return;
    } else {
       // diz file found; allow updates, and deletion of diz file
      	btnTilfoj->Enabled  = false;
      	btnOpdater->Enabled = true;
      	btnSlet->Enabled    = true;
    }

    ch = (char)fgetc( fil );
    while ( !feof( fil ) ) {
      if ( ch != 10 && ch != 13 )
      	 line[cnt++] = ch;
      else {
      	 line[cnt] = '\0';
      	 Memo->Lines->Add( AnsiString( line ) );
          cnt = 0;
      }
      ch = (char)fgetc( fil );
    }
    if ( cnt > 0 ) {
      line[cnt] = '\0';
      Memo->Lines->Add( AnsiString( line ) );
    }
    fclose( fil );

    // Remove the Diz file from the temp dir
    remove( TempDizPathSz );
    Memo->SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::btnAfslutClick( TObject *Sender ) {
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::btnOpdaterClick( TObject *Sender ) {
    // Update a Diz file, or create a new one
	 FILE *fil;
    int   ix;

    // Build a Diz file in temp directory from memo text
    fil = fopen( TempDizPathSz, "wt" );
    if ( (fil == NULL) || ferror(fil) ) {
       ShowMessage( "Error opening new diz for write" );
       return;
    }
    for ( ix = 0; ix < Memo->Lines->Count; ix++ ) {
    	fprintf( fil, "%s\n",Memo->Lines->Strings[ix].c_str() );
    }
    fclose( fil );

    // Add the new Diz file; let it overwrite any pre-existing one
    ZipBuilder1->FSpecArgs->Clear();
    ZipBuilder1->FSpecArgs->Add( TempDizPath );
	 ZipBuilder1->ZipFilename = FileListBox1->FileName;
    ZipBuilder1->Add();
    ZipBuilder1->ZipFilename = "";

    // Remove the Diz file from the temp dir
    remove( TempDizPathSz );
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::btnTilfojClick( TObject *Sender ) {
   // create a new Diz file
   if ( Memo->Lines->Count == 0 ) {
      ShowMessage( "Please enter text first" );
      return;
   }
   // Let's use the update code to create a new one
   fViewZip->btnOpdaterClick( fViewZip );

   // diz file now exists; allow updates, and deletion of diz file
   btnTilfoj->Enabled	= false;
   btnOpdater->Enabled	= true;
   btnSlet->Enabled		= true;
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::FormDestroy( TObject *Sender ) {
 	ZipBuilder1->Unload_Zip_Dll();
	ZipBuilder1->Unload_Unz_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::btnSletClick( TObject *Sender ) {
    // Delete the Diz file
    ZipBuilder1->FSpecArgs->Clear();
    ZipBuilder1->FSpecArgs->Add( "FILE_ID.DIZ" );
	 ZipBuilder1->ZipFilename = FileListBox1->FileName;
    ZipBuilder1->Delete();
    ZipBuilder1->ZipFilename = "";
    Memo->Lines->Clear();
    btnSlet->Enabled		= false;
    btnOpdater->Enabled	= false;
    btnTilfoj->Enabled	= true;
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::FileListBox1Change( TObject *Sender ) {
    Memo->Lines->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TfViewZip::ZipBuilder1Message( TObject *Sender, int ErrCode, String Message ) {
   // Ignore error code of 100 - that means FILE_ID.DIZ not found
   if ( (ErrCode > 0) && (ErrCode != 100) )
      ShowMessage( "Err Code: " + IntToStr( ErrCode ) + " " + Message );  // report any zip/unzip errors
}

