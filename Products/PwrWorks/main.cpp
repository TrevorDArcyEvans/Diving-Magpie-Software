//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
#include "main.h"

#include <Registry.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuExitClick(TObject *Sender)
{
frmMain->Close();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAboutClick(TObject *Sender)
{
frmAbout->Caption 					= Application->Title;
frmAbout->lblProductName->Caption 	= "Product Name:   " + Application->Title;
frmAbout->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
Application->HelpFile 	= "PwrWorks.HLP";

// read all registry settings and update state of controls
btnReadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuContentsClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnReadClick(TObject *Sender)
{
// read all registry settings and update state of controls
DWORD       dwType = 0;

// read email setting from:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\SolidWorks 98\SW Event Log]
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\SolidWorks 98Plus\SW Event Log]
//      "Email Enabled"=dword:00000000
HKEY        hEmail_SW98, hEmail_SW98P;
BYTE        dwEmail_SW98[MAX_PATH], dwEmail_SW98P[MAX_PATH];
DWORD       dwEmailSize_SW98  = sizeof(dwEmail_SW98 ),
            dwEmailSize_SW98P = sizeof(dwEmail_SW98P);

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    "SOFTWARE\\SolidWorks\\SolidWorks 98\\SW Event Log",
    0, KEY_ALL_ACCESS, &hEmail_SW98))
    {
    RegQueryValueEx(hEmail_SW98,
        "Email Enabled", NULL, &dwType, dwEmail_SW98, &dwEmailSize_SW98);
    RegCloseKey(hEmail_SW98);
    }

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    "SOFTWARE\\SolidWorks\\SolidWorks 98Plus\\SW Event Log",
    0, KEY_ALL_ACCESS, &hEmail_SW98P))
    {
    RegQueryValueEx(hEmail_SW98P,
        "Email Enabled", NULL, &dwType, dwEmail_SW98P, &dwEmailSize_SW98P);
    RegCloseKey(hEmail_SW98P);
    }

// if email setting inconsistent between two, then gray control
if (dwEmail_SW98[0] != dwEmail_SW98P[0])
    {
    chkEnableEmail->AllowGrayed = true;
    chkEnableEmail->State = cbGrayed;
    }
else
    {
    chkEnableEmail->AllowGrayed = false;
    chkEnableEmail->Checked = dwEmail_SW98P[0];
    }

// read MCD setting from:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\Performance]
//      [HKEY_CURRENT_USER\SOFTWARE\SolidWorks\Performance]
//      "Enable MCD"=dword:00000001
HKEY        hMCD_LM, hMCD_CU;
BYTE        dwMCD_LM[MAX_PATH], dwMCD_CU[MAX_PATH];
DWORD       dwMCD_LMSize = sizeof(dwMCD_LM),
            dwMCD_CUSize = sizeof(dwMCD_CU);

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    "SOFTWARE\\SolidWorks\\Performance",
    0, KEY_ALL_ACCESS, &hMCD_LM))
    {
    RegQueryValueEx(hMCD_LM,
        "Enable MCD", NULL, &dwType, dwMCD_LM, &dwMCD_LMSize);
    RegCloseKey(hMCD_LM);
    }

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
    "SOFTWARE\\SolidWorks\\Performance",
    0, KEY_ALL_ACCESS, &hMCD_CU))
    {
    RegQueryValueEx(hMCD_CU,
        "Enable MCD", NULL, &dwType, dwMCD_CU, &dwMCD_CUSize);
    RegCloseKey(hMCD_CU);
    }

// if MCD setting inconsistent between two, then gray control
if (dwMCD_LM[0] != dwMCD_CU[0])
    {
    chkEnableMCD->AllowGrayed = true;
    chkEnableMCD->State = cbGrayed;
    }
else
    {
    chkEnableMCD->Checked = dwMCD_LM[0];
    }


// read drawings setting from:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\General]
//      [HKEY_CURRENT_USER\SOFTWARE\SolidWorks\General]
//      "Disable model changes from drawings"=dword:00000000
HKEY        hDwg_LM, hDwg_CU;
BYTE        dwDwg_LM[MAX_PATH], dwDwg_CU[MAX_PATH];
DWORD       dwDwg_LMSize = sizeof(dwDwg_LM),
            dwDwg_CUSize = sizeof(dwDwg_CU);

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    "SOFTWARE\\SolidWorks\\General",
    0, KEY_ALL_ACCESS, &hDwg_LM))
    {
    RegQueryValueEx(hDwg_LM,
        "Disable model changes from drawings", NULL, &dwType, dwDwg_LM, &dwDwg_LMSize);
    RegCloseKey(hDwg_LM);
    }

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
    "SOFTWARE\\SolidWorks\\General",
    0, KEY_ALL_ACCESS, &hDwg_CU))
    {
    RegQueryValueEx(hDwg_CU,
        "Disable model changes from drawings", NULL, &dwType, dwDwg_CU, &dwDwg_CUSize);
    RegCloseKey(hDwg_CU);
    }

// if Dwg setting inconsistent between two, then gray control
if (dwDwg_LM[0] != dwDwg_CU[0])
    {
    chkEnableDwgChanges->AllowGrayed = true;
    chkEnableDwgChanges->State = cbGrayed;
    }
else
    {
    chkEnableDwgChanges->Checked = dwDwg_LM[0];
    }


// read tip of the day setting from:
//      [HKEY_CURRENT_USER\Software\SolidWorks\TipOfDay]
//      "ShowTipsAtStart"=dword:00000000
HKEY        hTip;
BYTE        dwTip[MAX_PATH];
DWORD       dwTipSize = sizeof(dwTip);

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
    "SOFTWARE\\SolidWorks\\TipOfDay",
    0, KEY_ALL_ACCESS, &hTip))
    {
    RegQueryValueEx(hTip,
        "ShowTipsAtStart", NULL, &dwType, dwTip, &dwTipSize);
    RegCloseKey(hTip);
    }

if (0 == dwTip[0])
    {
    chkTips->Checked = false;
    }

//  enumerate apps under:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\Applications]
//      [HKEY_CURRENT_USER\Software\SolidWorks\Applications]
TRegIniFile     *AppIniFile = new TRegIniFile("");
TStringList     *TempStr = new TStringList;

ddlApps->Items->Clear();

AppIniFile->RootKey = HKEY_LOCAL_MACHINE;
AppIniFile->OpenKey("Software\\SolidWorks\\Applications", false);
AppIniFile->GetKeyNames(TempStr);

ddlApps->Items->AddStrings(TempStr);

AppIniFile->RootKey = HKEY_CURRENT_USER;
AppIniFile->OpenKey("Software\\SolidWorks\\Applications", false);
AppIniFile->GetKeyNames(TempStr);

ddlApps->Items->AddStrings(TempStr);

ddlApps->ItemIndex = 0;

delete TempStr;
delete AppIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnWriteClick(TObject *Sender)
{
// write all registry settings
DWORD       dwType = REG_DWORD;

// write email setting into:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\SolidWorks 98\SW Event Log]
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\SolidWorks 98Plus\SW Event Log]
//      "Email Enabled"=dword:00000000
if (cbGrayed != chkEnableEmail->State)
    {
    HKEY        hEmail_SW98, hEmail_SW98P;
    BYTE        dwEmail[4];
    DWORD       dwEmailSize = sizeof(dwEmail);

    dwType = REG_DWORD;
    memset(dwEmail, 0, sizeof(dwEmail));
    dwEmail[0] = chkEnableEmail->Checked;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\SolidWorks\\SolidWorks 98\\SW Event Log",
        0, KEY_ALL_ACCESS, &hEmail_SW98))
        {
        RegSetValueEx(hEmail_SW98,
            "Email Enabled", NULL, dwType, dwEmail, dwEmailSize);
        RegCloseKey(hEmail_SW98);
        }

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\SolidWorks\\SolidWorks 98Plus\\SW Event Log",
        0, KEY_ALL_ACCESS, &hEmail_SW98P))
        {
        RegSetValueEx(hEmail_SW98P,
            "Email Enabled", NULL, dwType, dwEmail, dwEmailSize);
        RegCloseKey(hEmail_SW98P);
        }
    }


// write MCD setting into:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\Performance]
//      [HKEY_CURRENT_USER\SOFTWARE\SolidWorks\Performance]
//      "Enable MCD"=dword:00000001
if (cbGrayed != chkEnableMCD->State)
    {
    HKEY        hMCD_LM, hMCD_CU;
    BYTE        dwMCD_LM[4], dwMCD_CU[4];
    DWORD       dwMCD_LMSize = sizeof(dwMCD_LM),
                dwMCD_CUSize = sizeof(dwMCD_CU);

    dwType = REG_DWORD;
    memset(dwMCD_LM, 0, sizeof(dwMCD_LM));
    memset(dwMCD_CU, 0, sizeof(dwMCD_CU));
    dwMCD_LM[0] = chkEnableMCD->Checked;
    dwMCD_CU[0] = chkEnableMCD->Checked;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\SolidWorks\\Performance",
        0, KEY_ALL_ACCESS, &hMCD_LM))
        {
        RegSetValueEx(hMCD_LM,
            "Enable MCD", NULL, dwType, dwMCD_LM, dwMCD_LMSize);
        RegCloseKey(hMCD_LM);
        }

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
        "SOFTWARE\\SolidWorks\\Performance",
        0, KEY_ALL_ACCESS, &hMCD_CU))
        {
        RegSetValueEx(hMCD_CU,
            "Enable MCD", NULL, dwType, dwMCD_CU, dwMCD_CUSize);
        RegCloseKey(hMCD_CU);
        }
    }


// read drawings setting from:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\General]
//      [HKEY_CURRENT_USER\SOFTWARE\SolidWorks\General]
//      "Disable model changes from drawings"=dword:00000000
if (cbGrayed != chkEnableDwgChanges->State)
    {
    HKEY        hDwg_LM, hDwg_CU;
    BYTE        dwDwg_LM[4], dwDwg_CU[4];
    DWORD       dwDwg_LMSize = sizeof(dwDwg_LM),
                dwDwg_CUSize = sizeof(dwDwg_CU);

    dwType = REG_DWORD;
    memset(dwDwg_LM, 0, sizeof(dwDwg_LM));
    memset(dwDwg_CU, 0, sizeof(dwDwg_CU));
    dwDwg_LM[0] = chkEnableDwgChanges->Checked;
    dwDwg_CU[0] = chkEnableDwgChanges->Checked;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\SolidWorks\\General",
        0, KEY_ALL_ACCESS, &hDwg_LM))
        {
        RegSetValueEx(hDwg_LM,
            "Disable model changes from drawings", NULL,
            dwType, dwDwg_LM, dwDwg_LMSize);
        RegCloseKey(hDwg_LM);
        }

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
        "SOFTWARE\\SolidWorks\\General",
        0, KEY_ALL_ACCESS, &hDwg_CU))
        {
        RegSetValueEx(hDwg_CU,
            "Disable model changes from drawings", NULL,
            dwType, dwDwg_CU, dwDwg_CUSize);
        RegCloseKey(hDwg_CU);
        }
    }


// write tip of the day setting into:
//      [HKEY_CURRENT_USER\Software\SolidWorks\TipOfDay]
//      "ShowTipsAtStart"=dword:00000000
HKEY        hTip;
BYTE        dwTip[4];
DWORD       dwTipSize = sizeof(dwTip);

dwType = REG_DWORD;
memset(dwTip, 0, sizeof(dwTip));
dwTip[0] = chkTips->Checked;

if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,
    "SOFTWARE\\SolidWorks\\TipOfDay",
    0, KEY_ALL_ACCESS, &hTip))
    {
    RegSetValueEx(hTip,
        "ShowTipsAtStart", NULL, dwType, dwTip, dwTipSize);
    RegCloseKey(hTip);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRemoveClick(TObject *Sender)
{
// delete currently selected application from:
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidWorks\Applications]
//      [HKEY_CURRENT_USER\Software\SolidWorks\Applications]
//          CLSID
#if 0
TRegIniFile     *AppIniFile = new TRegIniFile("");
String          KeyName = "Software\\SolidWorks\\Applications\\" +
                            ddlApps->Items->Strings[ddlApps->ItemIndex];

String          RegFileName = ddlApps->Items->Strings[ddlApps->ItemIndex]+ ".reg";

AppIniFile->RootKey = HKEY_LOCAL_MACHINE;
if (true == AppIniFile->OpenKey(KeyName, false))
    {
    if (true == AppIniFile->SaveKey(KeyName, RegFileName))
        {
        //Application->MessageBox(ddlApps->Items->Strings[ddlApps->ItemIndex].c_str(),
        //    "List success", IDOK);

        // Call DeleteKey to remove a specified key and its associated data, if any,
        // from the registry. Under Windows 95, if the key has subkeys, the subkeys
        // and any associated data are also removed. Under Windows NT, subkeys must
        // be explicitly deleted by separate calls to DeleteKey.
        //AppIniFile->DeleteKey(KeyName);
        if (OS == NT)
            {
            while (ERROR_SUCCESS == RegEnumKey)
                {
                }
            }
        }
    }

AppIniFile->RootKey = HKEY_CURRENT_USER;

btnReadClick(Sender);

delete AppIniFile;
#endif
}
//---------------------------------------------------------------------------

