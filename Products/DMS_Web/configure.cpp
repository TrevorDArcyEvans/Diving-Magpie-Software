//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "ToolEdit"
#pragma link "CSPIN"
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
    FormStorage->Active = true;

    chkFileInfoClick (Sender);
    chkMassPropsClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkFileInfoClick(TObject *Sender)
{
    bool    bEnabled = chkFileInfo->Checked;

    chkBitmap       ->Enabled = bEnabled;
    chkFileName     ->Enabled = bEnabled;
    rdoFileNameOnly ->Enabled = bEnabled;
    rdoIncDirectory ->Enabled = bEnabled;
    chkFileSize     ->Enabled = bEnabled;
    chkDateTime     ->Enabled = bEnabled;

    chkFileNameClick(Sender);
    chkBitmapClick  (Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkMassPropsClick(TObject *Sender)
{
    bool    bEnabled = chkMassProps->Checked;

    chkCentreOfMass ->Enabled = bEnabled;
    chkVolume       ->Enabled = bEnabled;
    chkArea         ->Enabled = bEnabled;
    chkMass         ->Enabled = bEnabled;
    chkMassMoment   ->Enabled = bEnabled;
    chkBoundBox     ->Enabled = bEnabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkFileNameClick(TObject *Sender)
{
    bool    bEnabled = chkFileInfo->Checked && chkFileName->Checked;

    rdoFileNameOnly ->Enabled = bEnabled;
    rdoIncDirectory ->Enabled = bEnabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::btnCancelClick(TObject *Sender)
{
    FormStorage->Active = false;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::btnOKClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkBitmapClick(TObject *Sender)
{
    bool    bEnabled = chkFileInfo->Checked && chkBitmap->Checked;

    chkBitmapSize->Enabled = bEnabled;

    chkBitmapSizeClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfigure::chkBitmapSizeClick(TObject *Sender)
{
    bool    bEnabled = chkFileInfo->Checked && chkBitmap->Checked && chkBitmapSize->Checked;

    sedHeight->Enabled = bEnabled;
    sedWidth ->Enabled = bEnabled;
}
//---------------------------------------------------------------------------

