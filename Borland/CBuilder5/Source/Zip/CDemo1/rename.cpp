#include <vcl.h>
#pragma hdrstop

#include "Rename.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SortGrid"

#pragma resource "*.dfm"

TRenForm *RenForm;

//---------------------------------------------------------------------------
__fastcall TRenForm::TRenForm( TComponent *Owner ) : TForm( Owner ) {
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::FormShow( TObject *Sender ) {
	GDateTime = 0;
	SelectedGrid->RowCount = 2;
	SelectedGrid->Rows[1]->Clear();
	RenForm->Caption = "Rename items in zip archive: " + ExtractFileName( MainForm->ZipBuilder1->ZipFileName );
	OldCombo->Clear();
	ClearZipRenList();
	for (int i = 1; i <= MainForm->ZipBuilder1->Count; i++ ) {
		ZipDirEntry *zde = (ZipDirEntry *)MainForm->ZipBuilder1->ZipContents->Items[i - 1];

		OldCombo->Items->Add( zde->FileName );
	}
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::FormCreate( TObject *Sender ) {
	ZipRenameList = new TList();
	SelectedGrid->Cells[0][0] = "Old name";
	SelectedGrid->Cells[1][0] = "New name";
	SelectedGrid->Cells[2][0] = "Date/Time";
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::FormDestroy( TObject *Sender ) {
	ClearZipRenList();
	delete ZipRenameList;
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::ClearZipRenList( void ) {
	ZipRenameRec *RenRec;

	for (int i = 0; i < ZipRenameList->Count; i++) {
		RenRec = (ZipRenameRec *)ZipRenameList->Items[i];
		delete RenRec;
	}
	ZipRenameList->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::AddBtnClick( TObject *Sender ) {
	ZipRenameRec *RenRec;
	String        AddItem;

	AddItem = OldCombo->Text;
	if ( AddItem != NewEdit->Text || DTEdit->Text != "" ) {
		if ( AddItem.Length() > 0 && NewEdit->Text.Length() > 0 ) {
			if ( SelectedGrid->RowCount > 2 || (SelectedGrid->RowCount == 2 && SelectedGrid->Cells[0][1] != "") )
				SelectedGrid->RowCount++;
			RenRec = new ZipRenameRec;
			RenRec->Source   = AddItem;
			RenRec->Dest     = NewEdit->Text;
         try {
				if ( DTEdit->Text != "" )
					RenRec->DateTime = DateTimeToFileDate( StrToDateTime( DTEdit->Text ) );
			} catch( ... ) {
				delete RenRec;
				throw;
			}
			ZipRenameList->Add( RenRec );
			SelectedGrid->Cells[0][SelectedGrid->RowCount - 1] = AddItem;
			SelectedGrid->Cells[1][SelectedGrid->RowCount - 1] = NewEdit->Text;
			SelectedGrid->Cells[2][SelectedGrid->RowCount - 1] = DTEdit->Text;
		}
		OldCombo->Text = "";
		NewEdit->Text  = "";
		DTEdit->Text   = "";
	}
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::RemoveBtnClick( TObject *Sender ) {
	ZipRenameRec *RenRec;
	int j = SelectedGrid->Selection.Bottom;

	for (int i = SelectedGrid->Selection.Top; i >= j; i--) {
		if ( SelectedGrid->Cells[0][i] != "" ) {
			RenRec = (ZipRenameRec *)ZipRenameList->Items[i - 1];
			ZipRenameList->Delete( i - 1 );
			delete RenRec;
			SelectedGrid->Rows[i]->Clear();
			if ( i != 1 )
				SelectedGrid->DeleteRow( i );
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::CancelBitBtnClick( TObject *Sender ) {
	Hide();
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::OkBitBtnClick( TObject *Sender ) {
	int RenameErr;

	AddBtnClick( Sender );

	MsgForm->RichEdit1->Clear();
	MsgForm->Show();
	// Put this message into the message form's memo.
	MainForm->ZipBuilder1Message( this, 0, "Begin renaming entries in: " + MainForm->ZipBuilder1->ZipFileName );

	RenameErr = MainForm->ZipBuilder1->Rename( *ZipRenameList, GDateTime );
	if ( RenameErr )
		ShowMessage( "Error " + IntToStr( RenameErr ) + " in rename zip specification(s)" );
	MsgForm->Hide();
	Hide();
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::OldComboClick( TObject *Sender ) {
	NewEdit->Text = OldCombo->Items->Strings[OldCombo->ItemIndex];
	NewEdit->SetFocus();
	NewEdit->SelStart = NewEdit->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TRenForm::SelectedGridGetCellFormat( TObject *Sender, int Col, int Row, TGridDrawState State, TFormatOptions &FormatOptions ) {
	if ( !Row  ) {
		FormatOptions.AlignmentHorz = taCenter;
		FormatOptions.Font->Style   = FormatOptions.Font->Style << fsBold;
		FormatOptions.Font->Color   = clBlue;
	}
}

//---------------------------------------------------------------------------
void __fastcall TRenForm::DTAllBtnClick( TObject *Sender ) {
	if ( DTEdit->Text != "" )
		GDateTime = DateTimeToFileDate( StrToDateTime( DTEdit->Text ) );
	else
		GDateTime = 0;
}

