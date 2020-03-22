#include <vcl\vcl.h>
#pragma hdrstop

#include "Message.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMsgForm *MsgForm;

//---------------------------------------------------------------------------
void __fastcall TMsgForm::DismissButClick( TObject *Sender ) {
	Hide();
}

//---------------------------------------------------------------------------
void __fastcall TMsgForm::CancelButClick( TObject *Sender ) {
	if ( MainForm->ZipBuilder1->ZipBusy || MainForm->ZipBuilder1->UnzBusy )
		MainForm->ZipBuilder1->Cancel = true;
	else
		Hide(); // Nothing to cancel - assume user wants to close msg window.
}

//---------------------------------------------------------------------------
void __fastcall TMsgForm::FormCreate( TObject *Sender ) {
	ProgressBar2 = new TProgressBar( StatusBar1 );	// Parent will delete it.

	ProgressBar2->Parent   = StatusBar1;
	ProgressBar2->Top      = 2;
	ProgressBar2->Left     = StatusBar1->Left + StatusBar1->Panels->Items[0]->Width +
									 StatusBar1->Panels->Items[1]->Width + 2;
	ProgressBar2->Height   = StatusBar1->Height - 2;
	ProgressBar2->Min      = 1;
	ProgressBar2->Max      = 10001;
	ProgressBar2->Position = 1;

	FormInitialWidth		  = MsgForm->Width;
}

//---------------------------------------------------------------------------
void __fastcall TMsgForm::FormResize( TObject *Sender ) {
	ProgressBar2->Width = StatusBar1->Width - StatusBar1->Panels->Items[0]->Width -
								  StatusBar1->Panels->Items[1]->Width - 18;
	ProgressBar1->Width = 177 + (MsgForm->Width - FormInitialWidth);
}

