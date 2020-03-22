//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCodeGen *frmCodeGen;
//---------------------------------------------------------------------------
__fastcall TfrmCodeGen::TfrmCodeGen(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeGen::btnRegisterClick(TObject *Sender)
{
char            MachineID[MAX_PATH];

strcpy(MachineID, GetMachineID());

if (CheckCode(MachineID, VIEW_WORKS_TITLE_CODE, edtCode->Text.c_str()) == true)
    {
    MessageBox(NULL, "Successfully registered!", VIEW_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION);

    // write code into PltWorks.ini
    frmViewWorks->regSettings->WriteString("Security", "code", edtCode->Text);

    // security passed, enable options
    frmViewWorks->mnuRegister->Enabled = false;

    frmViewWorks->bRegistered = true;

    // and close form so as not to bother user again
    frmCodeGen->Close();
    }
else
    {
    // alert user to the error of his ways but let user close form
    // since may have incorrectly entered code
    MessageBox(NULL, "Incorrect code!", VIEW_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeGen::FormCreate(TObject *Sender)
{
edtMachineID->Text = AnsiString::AnsiString(GetMachineID());
}
//---------------------------------------------------------------------------

