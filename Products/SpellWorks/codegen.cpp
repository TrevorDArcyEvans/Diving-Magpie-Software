//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "crc_32.h"
#include "CodeGen.h"
#include "enum.h"
#include "main.h"
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

void __fastcall TfrmCodeGen::FormCreate(TObject *Sender)
{
edtMachineID->Text = AnsiString::AnsiString(GetMachineID());
frmCodeGen->Caption = frmMain->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCodeGen::btnRegisterClick(TObject *Sender)
{
char            MachineID[MAX_PATH];

strcpy(MachineID, GetMachineID());

if (CheckCode(MachineID, SPELL_WORKS_TITLE_CODE, edtCode->Text.c_str()) == true)
    {
    MessageBox(NULL, "Successfully registered!", SPELL_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION);

    // write code into SpellWks.ini
    frmMain->regSpell->WriteString("Security", "code", edtCode->Text);

    // security passed, disable menu item
    frmMain->mnuRegister->Enabled = false;
    frmMain->mnu_Register->Enabled = false;
    frmMain->btnUpdate->Enabled = true;
    frmMain->mnu_Update->Enabled = true;

    g_bRegistered = true;

    // and close form so as not to bother user again
    frmCodeGen->Close();
    }
else
    {
    // alert user to the error of his ways but let user close form
    // since may have incorrectly entered code
    MessageBox(NULL, "Incorrect code!", SPELL_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------

