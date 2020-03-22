#include "lupch.h"
#pragma hdrstop

#include "about.h"
#include "config.h"
#include "main.h"
#include "preview.h"
#include "saver.h"
#include "SWutils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "scrb4_controls"
#pragma link "scrb4_values"
#pragma link "browsefoldersdialog"
#pragma resource "*.dfm"
TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner) : TScrDialog(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::btnBrowseClick(TObject *Sender)
{
BrowseFoldersDialog->Folder = MainForm->SW_DirName->Value;

if(BrowseFoldersDialog->Execute())
    {
    MainForm->SW_DirName->Value = BrowseFoldersDialog->Folder;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::FormShow(TObject *Sender)
{
MainForm->MainFormCreate(Sender);
}
//---------------------------------------------------------------------------


