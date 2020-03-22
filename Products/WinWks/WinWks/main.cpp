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
CoInitialize(NULL);
Application->Title = WINDOW_WORKS_TITLE;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCancelClick(TObject *Sender)
{
ModalResult = mrCancel;
//Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnHelpClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        WW_HELP_FILE).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOKClick(TObject *Sender)
{
Variant         swApp, swModelDoc;
long            Errors;

try
    {
    swApp = CreateOleObject("SldWorks.Application");

    for (int i = 0; i < clbFileList->Items->Count; i++)
        {
        if (false == clbFileList->Checked[i])
            {
            swApp.OleFunction("QuitDoc", clbFileList->Items->Strings[i]);
            }
        else
            {
            // note that we only save the file if it is checked
            // and needs to be saved
            swModelDoc  = swApp.OleFunction("ActivateDoc2",
                clbFileList->Items->Strings[i], true, &Errors);
            if (true == (bool ) swModelDoc.OleFunction("GetSaveFlag"))
                {
                swModelDoc.OleFunction("Save2", true);
                }
            else
                {
                swApp.OleFunction("QuitDoc", clbFileList->Items->Strings[i]);
                }
            }
        }
    }
WW_CATCH_OLE_ERROR;

ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormShow(TObject *Sender)
{
Variant         swApp, swModelDoc;
AnsiString      strFileName;

clbFileList->Clear();

try
    {
    swApp = CreateOleObject("SldWorks.Application");
    swModelDoc  = swApp.OleFunction("GetFirstDocument");

    do
        {
        char        drive   [MAXDRIVE   ],
                    dir     [MAXDIR     ],
                    file    [MAXFILE    ],
                    ext     [MAXEXT     ];

        // only add document to lift if it is in an open window
        // SW will implicitly open all children, for example in
        // an assembly or drawing
        if (true == (bool ) swModelDoc.OleFunction("Visible"))
            {
            strFileName = swModelDoc.OleFunction("GetPathName");

            fnsplit(strFileName.c_str(), drive, dir, file, ext);

            strFileName = ::String(file) + ::String(ext);

            clbFileList->Items->Add(strFileName);
            clbFileList->Checked[clbFileList->Items->Count - 1] = swModelDoc.OleFunction("GetSaveFlag");
            }

        swModelDoc = swModelDoc.OleFunction("GetNext");
        } while (!swModelDoc.IsNull() && !swModelDoc.IsEmpty());
    }
WW_CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
#define     MIN_WIDTH       220
#define     MIN_HEIGHT      185

if (MIN_WIDTH  > NewWidth ||
    MIN_HEIGHT > NewHeight)
    {
    Resize = false;
    }
}
//---------------------------------------------------------------------------

