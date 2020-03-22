#include <vcl.h>
#pragma hdrstop

#include "Main5.h"

#pragma package( smart_init )

#pragma link "ZIPBuilder"
#pragma link "SortGrid"
#pragma resource "*.dfm"

TMainForm *MainForm;
bool		  Cancelled;

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseButClick( TObject *Sender ) {
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewZipButClick( TObject *Sender ) {
	OpenDialog1->Title = "Create New ZIP File";
	OpenDialog1->Options << ofHideReadOnly << ofShareAware;
	OpenDialog1->Options >> ofPathMustExist >> ofFileMustExist >> ofExtensionDifferent;
	OpenDialog1->FileName   = "";
	OpenDialog1->DefaultExt = "exe";
	OpenDialog1->Filter     = "EXE Files (*.EXE)|*.exe";
	if ( !OpenDialog1->Execute() ) return;
	String FileName = OpenDialog1->FileName;

	if ( OpenDialog1->Options.Contains( ofExtensionDifferent) ) {
		ShowMessage( "Error: your new archive must end in .EXE" );
		return;
	}
	if ( FileExists( FileName ) ) {
		if ( MessageDlg( "Overwrite Existing File: " + FileName + "?",
				mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes )
			DeleteFile( FileName );
		else return;	// Don't use the new name.
	}
	SetZipFName( FileName );

	// if ( MessageDlg( "Protect the archive with a password?",
	// 		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes ) {
		ZipBuilder1->GetAddPassword();
		if ( ZipBuilder1->Password == "" ) {
			// The 2 password's entered by user didn't match.
			// We'll give him/her one more try.
			if ( MessageDlg( "Do you want another chance to enter the password?",
					mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes ) {
				ZipBuilder1->GetAddPassword();
				if ( ZipBuilder1->Password == "" ) return;
			} else return;
		}
	// }
	ZipBuilder1->ZipFilename = FileName;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteZipButClick( TObject *Sender ) {
	if ( FileExists( ZipBuilder1->ZipFilename ) ) {
		if ( MessageDlg( "Are you sure you want to delete: " + ZipBuilder1->ZipFilename + "?",
				mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) == mrYes ) {
			if ( DeleteFile( ZipBuilder1->ZipFilename ) ) {
				SetZipFName( "<none>" );
				ZipBuilder1->ZipFilename = "";
			}
		}
	} else ShowMessage( "Zip file not found: " + ZipBuilder1->ZipFilename );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ZipBuilder1DirUpdate( TObject *Sender ) {
	FillGrid();
	FilesLabel->Caption = IntToStr( ZipBuilder1->Count );
	SetZipFName( ZipBuilder1->ZipFilename );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate( TObject *Sender ) {
	chdir( "C:\\" );

	/* Make sure "goColMoving" is false in object inspector. This lets the
      TSortGrid use Mouse Clicks on the col headers. */
	StringGrid1->RowCount     =   2;  // First row is fixed, and used for column headers.
	StringGrid1->Cells[0][0]  = "File Name";
	StringGrid1->Cells[1][0]  = "Compr. Size";
	StringGrid1->Cells[2][0]  = "Uncompr. Size";
	StringGrid1->Cells[3][0]  = "Date/Time";
   StringGrid1->ColWidths[0] = 316;
	StringGrid1->ColWidths[1] =  84;
	StringGrid1->ColWidths[2] =  94;
	StringGrid1->ColWidths[3] = 120;
	ZipBuilder1->Load_Zip_Dll();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FillGrid( void ) {
	// Remove everything from grid except col titles.
	StringGrid1->ClearFrom( 1 );
	StringGrid1->RowCount = 2;
	if ( !ZipBuilder1->Count ) return;

	StringGrid1->RowCount = ZipBuilder1->Count + 1;
	for ( int i = 1; i <= ZipBuilder1->Count; i++ ) {
		ZipDirEntry *zde = (ZipDirEntry *)ZipBuilder1->ZipContents->Items[i - 1];
		StringGrid1->Cells[0][i] = zde->FileName;
		StringGrid1->Cells[1][i] = IntToStr( (int)zde->CompressedSize );
		StringGrid1->Cells[2][i] = IntToStr( (int)zde->UncompressedSize );
		StringGrid1->Cells[3][i] = FormatDateTime( "ddddd  t", FileDateToDateTime( zde->DateTime ) );
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddButClick( TObject *Sender ) {
	String IsOne;

	// In this program, the first Add will cause the SFX code to be added,
	// and will make the SFX control block.  So, we need to set the SFX
	// properties now!
	ZipBuilder1->SFXDefaultDir = "C:\\";	// default extract directory.

	if ( ZipBuilder1->ZipFilename == "" ) {
		ShowMessage( "Error - create a new archive first" );
		return;
	}
	AddForm->Left   = Left;
	AddForm->Top    = Top;
	AddForm->Width  = Width;
	AddForm->Height = Height;
	Cancelled = false;
	AddForm->ShowModal();	// Let user pick filenames to add.
	if ( Cancelled ) return;
	if ( AddForm->SelectedList->Items->Count == 0 ) {
		ShowMessage( "No files selected" );
		return;
	}

	ZipBuilder1->Verbose = false;
	ZipBuilder1->Trace   = false;
	ZipBuilder1->AddOptions.Clear();
	if ( ZipBuilder1->Password > "" )
		ZipBuilder1->AddOptions = ZipBuilder1->AddOptions << AddEncrypt;	// We want a password.
	ZipBuilder1->FSpecArgs->Clear();
	ZipBuilder1->FSpecArgs->Assign( AddForm->SelectedList->Items );		// Specify filenames.
	AddForm->SelectedList->Clear();
	Screen->Cursor = crHourGlass;
	try {
		ZipBuilder1->Add();
	} catch ( ... ) {
		ShowMessage( "Error in Add; Fatal DLL Exception in mainunit" );
		Screen->Cursor = crDefault;
		return;
	}
	Screen->Cursor = crDefault;
	if ( ZipBuilder1->SuccessCnt == 1 )
		IsOne = " was";
	else
		IsOne = "s were";
	ShowMessage( IntToStr( ZipBuilder1->SuccessCnt ) + " file" + IsOne + " added" );
}

//---------------------------------------------------------------------------
// This is the "OnMessage" event handler
void __fastcall TMainForm::ZipBuilder1Message( TObject *Sender, int ErrCode, String Message ) {
	if ( ErrCode > 0 )
		ShowMessage( "Error Msg from DLL: " + Message );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteButClick( TObject *Sender ) {
	if ( ZipBuilder1->Count < 1 ) {
		ShowMessage( "Error - no files to delete" );
		return;
	}
	if ( MessageDlg( "Delete selected files from: " + ZipBuilder1->ZipFilename + "?",
			mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ) return;

	ZipBuilder1->FSpecArgs->Clear();
	for ( int i = StringGrid1->Selection.Top; i <= StringGrid1->Selection.Bottom; i++ ) {
		ZipBuilder1->FSpecArgs->Add( StringGrid1->Cells[0][i] );
	}
	if ( ZipBuilder1->FSpecArgs->Count < 1 ) {
		ShowMessage( "Error - no files selected" );
		return;
	}
	ZipBuilder1->Verbose = false;
	ZipBuilder1->Trace   = false;

	Screen->Cursor = crHourGlass;
	try {
		ZipBuilder1->Delete();
	} catch ( ... ) {
		ShowMessage( "Fatal error trying to delete" );
		Screen->Cursor = crDefault;
		return;
	}
	Screen->Cursor = crDefault;

	String IsOne = (ZipBuilder1->SuccessCnt == 1) ? " was" : "s were";
	ShowMessage( IntToStr( ZipBuilder1->SuccessCnt ) + " file" + IsOne + " deleted" );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SetZipFName( String aCaption ) {
	ZipFName->Caption = MinimizeName( aCaption, ZipFName->Canvas, ZipFName->Width );
	if ( ZipFName->Canvas->TextWidth( aCaption ) > ZipFName->Width ) {
		ZipFName->Hint         = aCaption;
		ZipFName->ShowHint     = true;
	} else ZipFName->ShowHint = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy( TObject *Sender ) {
	ZipBuilder1->Unload_Zip_Dll();
}

