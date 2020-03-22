//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::OKButtonClick(TObject *Sender)
{
frmAbout->Close();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
Caption = PLT_WORKS_TITLE;
lblProductName->Caption = "Product Name:   " + ::String(PLT_WORKS_TITLE);
}
//---------------------------------------------------------------------------

