//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowResults.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma resource "*.dfm"
TfrmShowResults *frmShowResults;
//---------------------------------------------------------------------------
__fastcall TfrmShowResults::TfrmShowResults(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResults::btnOKClick(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResults::FormHide(TObject *Sender)
{
    FormStorageResults->SaveFormPlacement();
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResults::FormShow(TObject *Sender)
{
    FormStorageResults->RestoreFormPlacement();
}
//---------------------------------------------------------------------------

