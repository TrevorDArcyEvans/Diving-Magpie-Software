//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#define		MAIN	1
#include "about.h"
#include "crc_32.h"
#include "CodeGen.h"
#include "enum.h"
#include "main.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WinRoll"
#pragma link "Regi1632"
#pragma link "VspelocxLib_OCX"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
// maximum number of checks for the unregistered version
#define		MAX_SPELL		    10
//---------------------------------------------------------------------------
#define		swDocINVALID       -1
#define		swDocNONE 		    0
#define		swDocPART    	    1
#define		swDocASSEMBLY       2
#define		swDocDrawing        3

#define		swSelDIMENSIONS    14
#define		swSelNOTES		   15
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
if (0 != strcmp(ParamStr(1).c_str(), "debug"))
    {
    memText->Lines->Clear();
    }

g_nNumSpell = 1;

Application->Title = SPELL_WORKS_TITLE;
Caption = SPELL_WORKS_TITLE;
stbSpell->SimpleText = ::String("Welcome to ") + ::String(SPELL_WORKS_TITLE);

Application->HelpFile 	= "SpellWks.HLP";

char                MachineID[MAX_PATH];
String              CodeStr;

g_bRegistered = false;

strcpy(MachineID, GetMachineID());
CodeStr = regSpell->ReadString("Security", "code");
if (CheckCode(MachineID, SPELL_WORKS_TITLE_CODE, CodeStr.c_str()) == true)
    {
    // security passed, disable register menu item
    mnuRegister->Enabled = false;
    mnu_Register->Enabled = false;
    btnUpdate->Enabled = true;
    mnu_Update->Enabled = true;

    g_bRegistered = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuOnTopClick(TObject *Sender)
{
mnuOnTop->Checked  = !mnuOnTop->Checked;
mnu_OnTop->Checked = !mnu_OnTop->Checked;

SetWindowPos(
    frmMain->Handle,
    (true == mnuOnTop->Checked) ? HWND_TOPMOST : HWND_NOTOPMOST,
    0, 0, 0, 0,
    SWP_NOMOVE | SWP_NOSIZE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCheckClick(TObject *Sender)
{
// NOTE:  can still check spelling, even if SW is not running

// if unregistered
if (++g_nNumSpell > MAX_SPELL &&
    false == g_bRegistered  )
    {
    btnUpdate->Enabled = false;
    mnu_Update->Enabled = false;
    }

// return if no text to check
// otherwise TVSpell will throw an exception
if (memText->Lines->Count <= 0)
    {
    return;
    }

// do spell check
splSpell->CheckText = ::WideString(memText->Lines->Text.c_str()).c_bstr();

if (VSR_CHECK_CANCELED != splSpell->ResultCode)
    {
    // update memo field with spellchecked text
    memText->Lines->Text = splSpell->Text;

    // update SW text, if we can
    btnUpdateClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuRegisterClick(TObject *Sender)
{
frmCodeGen->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuAboutClick(TObject *Sender)
{
frmAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuHelpClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormActivate(TObject *Sender)
{
g_bSW_Running = false;

// now try and find SW
EnumWindows((WNDENUMPROC ) SpellWorksEnumFunc, (LPARAM ) 1);

if (false == g_bSW_Running)
    {
    return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::WinRollRoller(TObject *Sender, TRollerMode mode)
{
FormActivate(Sender);

if (false == g_bSW_Running)
    {
    return;
    }

GetSWText();
}
//---------------------------------------------------------------------------
void    TfrmMain::GetSWText()
{
FormActivate(NULL);

if (false == g_bSW_Running)
    {
    return;
    }

try
    {
    // first refresh our connection to SolidWorks
	swApp = CreateOleObject("SldWorks.Application");

    // refresh the active document
    swModelDoc = swApp.OleFunction("ActiveDoc");

    // return if no document
    if (swModelDoc.IsNull ()   ||
        swModelDoc.IsEmpty()   )
        {
        return;
        }

    // get selection manager
    swSelMgr = swModelDoc.OleFunction("SelectionManager");

    // see if anything is selected
    int NumSel = swSelMgr.OleFunction("GetSelectedObjectCount");
    if (NumSel == 0)
        {
        return;
        }

    // get first selected object type
    // return if not a note
    int swType = swSelMgr.OleFunction("GetSelectedObjectType2", 1);
    if (swSelNOTES != swType)
        {
        return;
        }

    // get first selected SW note text
    swNote = swSelMgr.OleFunction("GetSelectedObject3", 1);
    if (!swNote.IsNull ()   &&
        !swNote.IsEmpty()   )
        {
        // clear memo field
        memText->Lines->Clear();

        bool    bRet = swNote.OleFunction("IsCompoundNote");
        String  swNoteText;

        if (true == bRet)
            {
            int     nTextCount = swNote.OleFunction("GetTextCount");

            for (int i = 1; i < nTextCount; i++)
                {
                swNoteText = swNote.OleFunction("GetTextAtIndex", i);

                // update memo field text with SW note text
                memText->Lines->Add(swNoteText);
                }
            }
        else
            {
            swNoteText = swNote.OleFunction("GetText");

            // update memo field text with SW note text
            memText->Lines->Add(swNoteText);
            }
        }
    }
CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnUpdateClick(TObject *Sender)
{
FormActivate(Sender);
if (false == g_bSW_Running)
    {
    return;
    }

// if unregistered
if (++g_nNumSpell > MAX_SPELL &&
    false == g_bRegistered  )
    {
    btnUpdate->Enabled = false;
    return;
    }

try
    {
    // first refresh our connection to SolidWorks
	swApp = CreateOleObject("SldWorks.Application");

    // refresh the active document
    swModelDoc = swApp.OleFunction("ActiveDoc");

    // return if no document
    if (swModelDoc.IsNull ()   ||
        swModelDoc.IsEmpty()   )
        {
        return;
        }

    // get selection manager
    swSelMgr = swModelDoc.OleFunction("SelectionManager");

    // see if anything is selected
    int NumSel = swSelMgr.OleFunction("GetSelectedObjectCount");
    if (NumSel == 0)
        {
        return;
        }

    // get first selected object type
    // return if not a note
    int swType = swSelMgr.OleFunction("GetSelectedObjectType2", 1);
    if (swSelNOTES != swType)
        {
        return;
        }

    // get first selected SW note text
    swNote = swSelMgr.OleFunction("GetSelectedObject3", 1);
    if (!swNote.IsNull ()   &&
        !swNote.IsEmpty()   )
        {
        // update SW note text with memo field text
        swNote.OleFunction("SetText", memText->Lines->Text);
        }
    }
CATCH_OLE_ERROR;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnImportClick(TObject *Sender)
{
GetSWText();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAboutClick(TObject *Sender)
{
splSpell->AboutBox();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnu_ExitClick(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

