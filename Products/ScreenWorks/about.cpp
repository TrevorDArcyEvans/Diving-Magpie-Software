#include "lupch.h"
#pragma hdrstop

#include <stdio.h>

#include "about.h"
#include "config.h"
#include "main.h"
#include "preview.h"
#include "saver.h"
#include "SWutils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------

__fastcall TAboutForm::TAboutForm(TComponent* Owner) : TScrDialog(Owner)
{ 
}
//---------------------------------------------------------------------------

void __fastcall TAboutForm::lblWebSolidPartnersClick(TObject *Sender)
{
TLabel *label=dynamic_cast<TLabel*>(Sender); if (label==NULL) return;
ShellExecute(Handle,"open",label->Caption.c_str(),NULL,NULL,SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormShow(TObject *Sender)
{
MainForm->MainFormCreate(Sender);

TCHAR       cWinSysDir[MAX_PATH], cBMPFileName[MAX_PATH];
if (!GetSystemDirectory(cWinSysDir, sizeof(cWinSysDir) / sizeof(TCHAR)))
    {
    return;
    }

sprintf(cBMPFileName, "%s\\ScrWorks.bmp", cWinSysDir);


if (true == g_bIsSolidPartners)
    {
    // SolidPartners
    lblBannerVar->Caption = g_strVarName;
    lblWebVar->Caption = g_strVarWebSite;

    imgLogoVar->Enabled = true;
    lblBannerVar->Enabled = true;
    lblWebVar->Enabled = true;
    imgLogoVar->Enabled = true;

    imgLogoVar->Visible = true;
    lblBannerVar->Visible = true;
    lblWebVar->Visible = true;
    imgLogoVar->Visible = true;

    // change VAR logo
    if (FileExists(cBMPFileName))
        {
        imgLogoVar->Picture->LoadFromFile(cBMPFileName);
        }
    }
else
    {
    // Actify

    // replace SP info with VAR info
    lblBannerSolidPartners->Caption = g_strVarBanner;
    lblWebSolidPartners->Caption = g_strVarWebSite;

    imgLogoVar->Enabled = false;
    lblBannerVar->Enabled = false;
    lblWebVar->Enabled = false;

    // hide VAR info since this will replace the SP info
    imgLogoVar->Visible = false;
    lblBannerVar->Visible = false;
    lblWebVar->Visible = false;

    // change SP logo at top to the VAR logo
    if (FileExists(cBMPFileName))
        {
        imgLogoSolidPartners->Picture->LoadFromFile(cBMPFileName);
        }
    }
}
//---------------------------------------------------------------------------
