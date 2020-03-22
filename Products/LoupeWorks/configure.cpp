//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "RXSpin"
#pragma link "Placemnt"
#pragma resource "*.dfm"
TfrmConfigure *frmConfigure;
//---------------------------------------------------------------------------
__fastcall TfrmConfigure::TfrmConfigure(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::FormCreate(TObject *Sender)
{
    FormStorage->RestoreFormPlacement();
    frmMain->BI_Loupe->ZoomLevel = sedZoom->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::FormShow(TObject *Sender)
{
    FormStorage  ->Active = true;
    FormStorage  ->RestoreFormPlacement();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::bnOKClick(TObject *Sender)
{
    FormStorage->SaveFormPlacement();
    frmMain->BI_Loupe->ZoomLevel = sedZoom->Value;

    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::btnCancelClick(TObject *Sender)
{
    FormStorage->Active = false;

    Hide();
}
//---------------------------------------------------------------------------
