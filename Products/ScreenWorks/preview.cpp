#include "lupch.h"
#pragma hdrstop

#include "about.h"
#include "config.h"
#include "main.h"
#include "preview.h"
#include "saver.h"
#include "SWutils.h"

#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XVIEW3DLib_OCX"
#pragma resource "*.dfm"
TPreviewForm *PreviewForm;
//---------------------------------------------------------------------------

__fastcall TPreviewForm::TPreviewForm(TComponent* Owner) : TScrForm(Owner)
{ 
}
//---------------------------------------------------------------------------
void __fastcall TPreviewForm::FormShow(TObject *Sender)
{
MainForm->MainFormCreate(Sender);

if (false == g_bIsSolidPartners)
    {
    TCHAR       cWinSysDir[MAX_PATH], cBMPFileName[MAX_PATH];
    if (!GetSystemDirectory(cWinSysDir, sizeof(cWinSysDir) / sizeof(TCHAR)))
        {
        return;
        }

    // load VAR logo into Preview window
    sprintf(cBMPFileName, "%s\\ScrWorks.bmp", cWinSysDir);
    if (FileExists(cBMPFileName))
        {
        imgLogoPreview->Picture->LoadFromFile(cBMPFileName);
        }
    }
}
//---------------------------------------------------------------------------

