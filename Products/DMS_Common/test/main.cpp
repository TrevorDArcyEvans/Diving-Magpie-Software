//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "DMS_Comm_TLB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TCOMIDMS_Common      DMS_Comm;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
delete DMS_Comm;
::CoUninitialize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnAboutClick(TObject *Sender)
{
DMS_Comm->set_Commercial(cboCommercial->Checked);

if (cboIcon->Checked)
    {
    DMS_Comm->set_Icon((long ) Application->Icon->Handle);
    }

DMS_Comm->set_ProductName(WideString(edtProductName->Text));
DMS_Comm->set_ProductCode(WideString(edtProductCode->Text));
DMS_Comm->About();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnRegisterClick(TObject *Sender)
{
DMS_Comm->set_ProductName(WideString(edtProductName->Text));
DMS_Comm->set_ProductCode(WideString(edtProductCode->Text));
DMS_Comm->set_IniFileName(WideString(edtIniFileName->Text));
DMS_Comm->Register();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
::CoInitialize(0);
DMS_Comm = CoDMS_Common::Create();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnMachineIDClick(TObject *Sender)
{
BSTR        sMachineID;
DMS_Comm->GetMachineID(&sMachineID);
edtMachineID->Text = sMachineID;
}
//---------------------------------------------------------------------------

