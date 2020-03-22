#include <vcl.h>
#pragma hdrstop

#include "AddFiles.h"

//---------------------------------------------------------------------------
#pragma package( smart_init )
#pragma resource "*.dfm"

TAddForm *AddForm;
bool      InMouseClick;

//---------------------------------------------------------------------------
void __fastcall TAddForm::OKButClick( TObject *Sender ) {
	Cancelled = false;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::CancelButClick( TObject *Sender ) {
	Cancelled = true;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::SortButClick( TObject *Sender ) {
	SelectedList->Sorted = true;
	SortBut->Enabled     = false;  // List will remain sorted.
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::RemoveButClick( TObject *Sender ) {
	for ( int i = SelectedList->Items->Count - 1; i >= 0 ; i-- ) {
		if ( SelectedList->Selected[i] )
			SelectedList->Items->Delete( i );
	}
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::SelectAllButClick( TObject *Sender ) {
	for ( int i = 0; i < FileListBox1->Items->Count; i++ )
		FileListBox1->Selected[i] = true;
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::FormCreate( TObject *Sender ) {
	InMouseClick = false;
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::AddDirButClick( TObject *Sender ) {
	String FullName;

	Cancelled = true;  // Default.
	for ( int i = 0; i < DirectoryListBox1->Items->Count; i++ ) {
		if ( DirectoryListBox1->Selected[i] ) {
			// Add this file if it isn't already in listbox.
			FullName = MainForm->ZipBuilder1->AppendSlash( DirectoryListBox1->Directory ) + "*.*";

			if ( SelectedList->Items->IndexOf( FullName ) < 0 )
				SelectedList->Items->Add( FullName );
			// Never de-select dirnames from the DirectoryList!
			// DirectoryListBox1->Selected[i] = false;
		}
	}
	// Position the "SelectedList" listbox at the bottom.
	SelectedList->Selected[SelectedList->Items->Count - 1] = true;
	SelectedList->Selected[SelectedList->Items->Count - 1] = false;
}

//---------------------------------------------------------------------------
void __fastcall TAddForm::AddFileButClick( TObject *Sender ) {
	String FullName;

	Cancelled = true;  // default
	for ( int i = 0; i < FileListBox1->Items->Count; i++ ) {
		if ( FileListBox1->Selected[i] ) {
			// Add this file if it isn't already in listbox.
			FullName =  MainForm->ZipBuilder1->AppendSlash( DirectoryListBox1->Directory ) + FileListBox1->Items->Strings[i];
			if ( SelectedList->Items->IndexOf( FullName ) < 0 )
				SelectedList->Items->Add( FullName );
			FileListBox1->Selected[i] = false;
		}
	}
	// Position the "SelectedList" listbox at the bottom.
	SelectedList->Selected[SelectedList->Items->Count - 1] = true;
	SelectedList->Selected[SelectedList->Items->Count - 1] = false;
}

