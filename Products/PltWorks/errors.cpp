//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "errors.h"
#include "main.h"
#include "print_sel.h"
#include "utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmError *frmError;
//---------------------------------------------------------------------------
__fastcall TfrmError::TfrmError(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmError::FormCreate(TObject *Sender)
{
frmError->Caption = Application->Title;
}
//---------------------------------------------------------------------------
