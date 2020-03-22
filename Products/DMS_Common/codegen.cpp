//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CodeGen.h"
#include "crc_32.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Regi1632"
#pragma resource "*.dfm"
TfrmCodeGen *frmCodeGen;
//---------------------------------------------------------------------------
__fastcall TfrmCodeGen::TfrmCodeGen(TComponent* Owner)
    : TForm(Owner)
{
m_sProductName = "Diving Magpie Software v1.0";
m_sProductCode = "Diving Magpie Software v1.x";
m_bIsRegistered = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeGen::btnRegisterClick(TObject *Sender)
{
char            MachineID[MAX_PATH];

strcpy(MachineID, GetMachineID());

if (CheckCode(MachineID, m_sProductCode.c_str(), edtCode->Text.c_str()) == true)
    {
    m_bIsRegistered = true;
    m_sAuthCode = edtCode->Text;

    MessageBox(NULL, "Successfully registered!", m_sProductName.c_str(),
        MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION);

    // caller is responsible for writing to file
    
    // and close form so as not to bother user again
    ModalResult = mrOk;
    }
else
    {
    // alert user to the error of his ways but let user close form
    // since may have incorrectly entered code
    MessageBox(NULL, "Incorrect code!", m_sProductName.c_str(),
        MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCodeGen::FormShow(TObject *Sender)
{
edtMachineID->Text = AnsiString::AnsiString(GetMachineID());
Caption = m_sProductName + " " + Caption;
}
//---------------------------------------------------------------------------

