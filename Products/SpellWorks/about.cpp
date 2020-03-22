//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "crc_32.h"
#include "CodeGen.h"
#include "enum.h"
#include "main.h"
#include "utils.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//--------------------------------------------------------------------- 
__fastcall TfrmAbout::TfrmAbout(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmAbout::OKButtonClick(TObject *Sender)
{
frmAbout->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
frmAbout->Caption = SPELL_WORKS_TITLE;
lblProductName->Caption = lblProductName->Caption + SPELL_WORKS_TITLE;
}
//---------------------------------------------------------------------------

