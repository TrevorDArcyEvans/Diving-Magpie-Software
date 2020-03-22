//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "main.h"
#include "print_sel.h"
#include "utils.h"

#include <printers.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrinters *frmPrinters;
//---------------------------------------------------------------------------
__fastcall TfrmPrinters::TfrmPrinters(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrinters::FormCreate(TObject *Sender)
{
frmPrinters->Caption = Application->Title;
ddlPrinters->Items->Clear();
ddlPrinters->Items->AddStrings(frmPltWorks->m_Printer->Printers);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrinters::btnOKClick(TObject *Sender)
{
frmPltWorks->m_Printer->PrinterIndex = ddlPrinters->ItemIndex;
frmPltWorks->m_nCurrentPrinter       = ddlPrinters->ItemIndex;
}
//---------------------------------------------------------------------------


