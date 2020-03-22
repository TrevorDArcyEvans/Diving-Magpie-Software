//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "about.h"
#include "config.h"
#include "SWutils.h"
#include "unfrag.h"
#include "UnfragFile.h"
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
frmAbout->Caption = UNFRAG_WORKS_TITLE;
lblProductName->Caption = lblProductName->Caption + UNFRAG_WORKS_TITLE;
}
//--------------------------------------------------------------------------- 
