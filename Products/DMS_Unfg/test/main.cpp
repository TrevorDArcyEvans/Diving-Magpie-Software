//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
::CoInitialize(0);
DMS_Unfrag = CoDMS_Unfrag::Create();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowseClick(TObject *Sender)
{
OpenDialog->FileName = edtFileName->Text;
if (OpenDialog->Execute())
    {
    edtFileName->Text = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCodeClick(TObject *Sender)
{
DMS_Unfrag.set_AuthCode(WideString(edtCode->Text).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnUnfragClick(TObject *Sender)
{
long        nBytesSaved = -1;
DMS_Unfrag.UnfragFile(WideString(edtFileName->Text).Detach(), &nBytesSaved);

if (nBytesSaved > 0)
    {
    String      sTemp;
    sTemp = "Saved " + sTemp.FormatFloat("0", nBytesSaved) + String(" bytes");
    ShowMessage(sTemp);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnPreviewClick(TObject *Sender)
{
DMS_Unfrag.RemovePreview(WideString(edtFileName->Text).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGeometryClick(TObject *Sender)
{
DMS_Unfrag.RemoveGeometry(WideString(edtFileName->Text).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
delete DMS_Unfrag;
::CoUninitialize();
}
//---------------------------------------------------------------------------
