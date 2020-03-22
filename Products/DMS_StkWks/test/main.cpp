//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "DMS_StkWks_TLB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    TCOMIDMS_StickWorks      DMS_StkWks;

    ::CoInitialize(0);
    DMS_StkWks = CoDMS_StickWorks::Create();
    DMS_StkWks->set_Name(WideString(Edit1->Text));
    DMS_StkWks->Configure();
    ::CoUninitialize();
}
//---------------------------------------------------------------------------
