//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#define        MAIN    1

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "enum.h"
#include "errors.h"
#include "main.h"
#include "print_file.h"
#include "print_sel.h"
#include "PrintMap.h"
#include "SWutils.h"
#include "utils.h"

#include <printers.hpp>
//---------------------------------------------------------------------------
#pragma link "Regi1632"
#pragma link "Dropper"
#pragma link "MRUList"
#pragma link "MRUList"
#pragma link "MRUList"
#pragma link "MRUList"
#pragma resource "*.dfm"
TfrmPltWorks *frmPltWorks;
//---------------------------------------------------------------------------
__fastcall TfrmPltWorks::TfrmPltWorks(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::btnAddClick(TObject *Sender)
{
if (dlgOpen->Execute() == true)
    {
    // set dirty flag
    m_bDirty = true;
    
    for (int i = 0; i < dlgOpen->Files->Count; i++)
        {
        lbxList->Items->Add(dlgOpen->Files->Strings[i]);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::btnRemoveClick(TObject *Sender)
{
if (lbxList->SelCount >= 1)
    {
    // set dirty flag
    m_bDirty = true;

    int             Curr = 0;
    TStringList    *Items = NULL;

    Items = new TStringList();
    Items->AddStrings(lbxList->Items);

    for (int i = 0; i < lbxList->Items->Count; i++)
        {
        if (lbxList->Selected[i] == true)
            {
            Items->Delete(i - Curr);
            Curr++;
            }
        }
    lbxList->Items->Clear();
    lbxList->Items->AddStrings(Items);
    delete Items;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::btnPrintClick(TObject *Sender)
{
PrintFiles();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuSelPrintClick(TObject *Sender)
{
// FIX ME!
// need to determine the default Windows printer
// might be something in the registry under:
//      [HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\Devices]
// MFC uses CPrintDialog::GetPrinterDC()
m_Printer->PrinterIndex = m_nCurrentPrinter;
frmPrinters->ddlPrinters->ItemIndex = m_nCurrentPrinter;
if (mrOk == frmPrinters->ShowModal())
    {
    dlgPrintDialog->Execute();

    m_nCurrentPrinter = frmPrinters->ddlPrinters->ItemIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuPrintSetupClick(TObject *Sender)
{
dlgPrinterSetupDialog->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::FormClose(TObject *Sender,
      TCloseAction &Action)
{
// if no filename & we've got something in the list,
// or if we've made changes to an existing file,
// then give the user a chance to save
if (true == m_FileName.IsEmpty()    &&
    lbxList->Items->Count >  0      ||
    true == m_bDirty                )
    {
    int     nRet = Application->MessageBox("Do you want to save your changes?",
                        PLT_WORKS_TITLE, MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1);

    if (IDYES == nRet)
        {
        mnuSaveClick(Sender);
        }

    // if we are aborting exiting, we can go back now
    if (IDCANCEL == nRet)
        {
        Action = caNone;
        return;
        }
    }

// if SW was not already running ie we started it, then close it down
if (false == g_bSW_Running  &&
    true  == m_bPrinted     )
    {
    try
        {
        // attempt to reconnect to SW and then shut it down
        Variant         swApp = CreateOleObject("SldWorks.Application");
        swApp.OleFunction("ExitApp");
        }
    PW_CATCH_OLE_ERROR;
    }

delete m_Printer;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::FormCreate(TObject *Sender)
{
char            MachineID[MAX_PATH];
AnsiString      CodeStr;

Application->Title   = PLT_WORKS_TITLE;
frmPltWorks->Caption = Application->Title;

g_bSW_Running   = false;

m_bRegistered   = false;
m_bPrinted      = false;
m_bDirty        = false;

// see if SW is already running
EnumWindows((WNDENUMPROC ) PlotWorksEnumFunc, (LPARAM ) 1);

// initialise FileName to hold list of files
m_FileName = '\0';

m_Printer = new TPrinter();

// use default printer
m_nCurrentPrinter = m_Printer->PrinterIndex;

strcpy(MachineID, GetMachineID());
CodeStr = regSettings->ReadString("Security", "code");

if (CheckCode(MachineID, PLT_WORKS_TITLE_CODE, CodeStr.c_str()) == true)
    {
    // security passed, enable options
    mnuRegister->Enabled = false;
    m_bRegistered = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuSaveClick(TObject *Sender)
{
// if no filename, then get one
if (m_FileName.IsEmpty() == true)
    {
    mnuSaveAsClick(Sender);
    }
else
    {
    // clear dirty flag
    m_bDirty = false;

    // note that we save the file, even if there are no files in the list
    lbxList->Items->SaveToFile(m_FileName);

    UpdateFileName(m_FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuSaveAsClick(TObject *Sender)
{
// get a valid file name and save the file
if (dlgSaveFileName->Execute() == true)
    {
    m_FileName = dlgSaveFileName->FileName;
    mnuSaveClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuOpenClick(TObject *Sender)
{
// if no filename & we've got something in the list,
// then give the user a chance to save
if (m_FileName.IsEmpty()  == true &&
    lbxList->Items->Count >  0    )
    {
    if (IDYES == Application->MessageBox("Do you want to save your changes?",
                    PLT_WORKS_TITLE, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1))
        {
        mnuSaveAsClick(Sender);
        }
    }

if (dlgOpenFileName->Execute() == true)
    {
    m_FileName = dlgOpenFileName->FileName;

    // TO DO
    // manually catch exceptions on trying to load strings from file
    // this is done by the default RTL handler at the moment
    lbxList->Items->LoadFromFile(m_FileName);

    UpdateFileName(m_FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuAboutClick(TObject *Sender)
{
frmAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuContentsClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuRegisterClick(TObject *Sender)
{
frmCodeGen->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuViewLogClick(TObject *Sender)
{
frmError->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::FileDropperDrop(TObject *Sender,
      AnsiString Filename)
{
if (true == IsSolidWorksFile(Filename))
    {
    // set dirty flag
    m_bDirty = true;

    lbxList->Items->Add(Filename);
    }
else
    {
    // TO DO
    // manually catch exceptions on trying to load strings from file
    // this is done by the default RTL handler at the moment

    // note that if there is more than one file dropped,
    // they will each be loaded in turn, over the previous one,
    // so only the last file will remain
    lbxList->Items->LoadFromFile(Filename);

    UpdateFileName(m_FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::btnUpClick(TObject *Sender)
{
// moving only makes sense if one item is selected
if (1 != lbxList->SelCount)
    {
    return;
    }

// get index of current selection
int nCurrPos = lbxList->ItemIndex;

// only move up if not the first item
// note that if nothing is selected, then nCurrPos = -1
if (nCurrPos >= 1)
    {
    // set dirty flag
    m_bDirty = true;

    lbxList->Items->Move(nCurrPos, nCurrPos - 1);
    lbxList->ItemIndex = nCurrPos - 1;

    // now rehighlight currently selected item
    lbxList->Selected[nCurrPos - 1] = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::btnDownClick(TObject *Sender)
{
// moving only makes sense if one item is selected
if (1 != lbxList->SelCount)
    {
    return;
    }

// get index of current selection
int nCurrPos = lbxList->ItemIndex;

// only move down if it is not the last one and there is something selected
if (nCurrPos < lbxList->Items->Count - 1 &&
    nCurrPos != -1)
    {
    // set dirty flag
    m_bDirty = true;

    lbxList->Items->Move(nCurrPos, nCurrPos + 1);
    lbxList->ItemIndex = nCurrPos + 1;

    // now rehighlight currently selected item
    lbxList->Selected[nCurrPos + 1] = true;
    }
}
//---------------------------------------------------------------------------
void TfrmPltWorks::UpdateFileName(String   AFileName)
{
// update app & form titles with filename *after* we have loaded the file
// since we may have thrown an exception
m_FileName = AFileName;
Application->Title = ::String(PLT_WORKS_TITLE) + ::String(" - ") +
                            ::String(m_FileName);
frmPltWorks->Caption = Application->Title;
frmError   ->Caption = Application->Title;

// add filename to MRU list
MRUFileList->Add(m_FileName, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::mnuMapPrintersClick(TObject *Sender)
{
frmPrintMap->ShowModal();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmPltWorks::MRUFileListClick(TObject *Sender,
      const AnsiString RecentName, const AnsiString Caption, int UserData)
{
// TO DO
// manually catch exceptions on trying to load strings from file
// this is done by the default RTL handler at the moment
lbxList->Items->LoadFromFile(RecentName);

UpdateFileName(RecentName);
}
//---------------------------------------------------------------------------

