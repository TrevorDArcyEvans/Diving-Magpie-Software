//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "Placemnt"
#pragma link "mwajpeg"
#pragma resource "*.dfm"
TfrmConfigure *frmConfigure;
//---------------------------------------------------------------------------
__fastcall TfrmConfigure::TfrmConfigure(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::btnOKClick(TObject *Sender)
{
    FormPlacement->SaveFormPlacement();
    FormStorage  ->SaveFormPlacement();

    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::btnCancelClick(TObject *Sender)
{
    FormPlacement->Active = false;
    FormStorage  ->Active = false;

    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::FormShow(TObject *Sender)
{
    FormPlacement->Active = true;
    FormStorage  ->Active = true;

    FormPlacement->RestoreFormPlacement();
    FormStorage  ->RestoreFormPlacement();

    chkSpecifySizeClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkSpecifySizeClick(TObject *Sender)
{
    bool    bEnabled = chkSpecifySize->Checked;

    sedWidth ->Enabled = bEnabled;
    sedHeight->Enabled = bEnabled;
}
//---------------------------------------------------------------------------
