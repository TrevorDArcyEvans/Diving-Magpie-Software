//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "crc_32.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
#define NUM_PROD        68
char    *Products[NUM_PROD] =
            {
            "BundleWorks v1.x",
            "BundleWorks v2.x",
            "BundleWorks v3.x",

            "DiffWorks v1.x",
            "DiffWorks v2.x",
            "DiffWorks v3.x",
            "DiffWorks v4.x",

            "MenuWorks v2.x",
            "MenuWorks v3.x",
            "MenuWorks v4.x",

            "OrbWorks v2.x",
            "OrbWorks v3.x",
            "OrbWorks v4.x",

            "PDFWorks v1.x",
            "PDFWorks v2.x",
            "PDFWorks v3.x",
            "PDFWorks v4.x",

            "PlotWorks v2.x",
            "PlotWorks v3.x",
            "PlotWorks v4.x",

            "PointerWorks v2.x",
            "PointerWorks v3.x",
            "PointerWorks v4.x",

            "RosettaWorks v1.x",
            "RosettaWorks v2.x",
            "RosettaWorks v3.x",

            "SpellWorks v1.x",
            "SpellWorks v2.x",
            "SpellWorks v3.x",
            "SpellWorks v4.x",

            "StickWorks v2.x",
            "StickWorks v3.x",
            "StickWorks v4.x",

            "STLWorks v1.x",
            "STLWorks v2.x",
            "STLWorks v3.x",

            "UnfragWorks v2.x",
            "UnfragWorks v3.x",
            "UnfragWorks v4.x",

            "UnfragWorks Server v1.x",
            "UnfragWorks Server v2.x",
            "UnfragWorks Server v3.x",
            "UnfragWorks Server v4.x",

            "UnfragWorks Server Gold v1.x",
            "UnfragWorks Server Gold v2.x",
            "UnfragWorks Server Gold v3.x",
            "UnfragWorks Server Gold v4.x",

            "ViewWorks v1.x",
            "ViewWorks v2.x",
            "ViewWorks v3.x",

            "VRMLWorks v1.x",
            "VRMLWorks v2.x",
            "VRMLWorks v3.x",

            "WindowWorks v1.x",
            "WindowWorks v2.x",
            "WindowWorks v3.x",

            "XGLWorks v1.x",
            "XGLWorks v2.x",
            "XGLWorks v3.x",

            "ZipWorks v2.x",
            "ZipWorks v3.x",
            "ZipWorks v4.x",

            "SolidPartners SolidWorks Companion CD v1.x",
            "SolidPartners SolidWorks Companion CD v2.x",
            "SolidPartners SolidWorks Companion CD v3.x",

            "Activault Administrator v1.x",
            "Activault Administrator v2.x",
            "Activault Administrator v3.x"
            };

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGenerateClick(TObject *Sender)
{
unsigned long                   CRC32;
long                            CharCnt;
char                            TempStr[2 * MAX_PATH];

// start off with machine ID
strcpy(TempStr, edtMachineID->Text.Trim().c_str());

// add the product
strcat(TempStr, ddlProduct->Items->Strings[ddlProduct->ItemIndex].c_str());

// calculate 32 bit CRC value
crc32string(&CRC32,&CharCnt, TempStr);

sprintf(TempStr, "%x", CRC32);
edtCode->Text = TempStr;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
ddlProduct->Clear();

int i = 0;

for(i = 0; i < NUM_PROD; i++)
    {
    ddlProduct->Items->Add(AnsiString::AnsiString(Products[i]));
    }

// initialise dropdown list to first item
ddlProduct->ItemIndex = 0;
}
//---------------------------------------------------------------------------

