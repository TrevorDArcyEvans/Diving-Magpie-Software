//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

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
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FlEdit"
#pragma resource "*.dfm"
TfrmPrintMap *frmPrintMap;
//---------------------------------------------------------------------------
__fastcall TfrmPrintMap::TfrmPrintMap(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::FormCreate(TObject *Sender)
{
Caption = PLT_WORKS_TITLE;

for (int i = 0; i < NUM_PAPER_SIZES; i++)
    {
    dynamic_cast<TComboBox *>(FindComponent(ddlPrinterName[i]))->Items->AddStrings(frmPltWorks->m_Printer->Printers);
    }

LoadRegistrySettings();
}
//---------------------------------------------------------------------------
void TfrmPrintMap::IncrementScale(int  nIndex)
{
dynamic_cast<TFloatEdit *>(FindComponent(fleScaleName[nIndex]))->Value += SCALE_INCR_DECR;
}
//---------------------------------------------------------------------------
void TfrmPrintMap::DecrementScale(int  nIndex)
{
dynamic_cast<TFloatEdit *>(FindComponent(fleScaleName[nIndex]))->Value -= SCALE_INCR_DECR;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA_LandscapeDownClick(TObject *Sender)
{
DecrementScale(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA_LandscapeUpClick(TObject *Sender)
{
IncrementScale(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA_PortraitDownClick(TObject *Sender)
{
DecrementScale(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA_PortraitUpClick(TObject *Sender)
{
IncrementScale(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbB_LandscapeDownClick(TObject *Sender)
{
DecrementScale(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbB_LandscapeUpClick(TObject *Sender)
{
IncrementScale(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbC_LandscapeDownClick(TObject *Sender)
{
DecrementScale(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbC_LandscapeUpClick(TObject *Sender)
{
IncrementScale(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbD_LandscapeDownClick(TObject *Sender)
{
DecrementScale(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbD_LandscapeUpClick(TObject *Sender)
{
IncrementScale(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbE_LandscapeDownClick(TObject *Sender)
{
DecrementScale(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbE_LandscapeUpClick(TObject *Sender)
{
IncrementScale(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA4_LandscapeDownClick(TObject *Sender)
{
DecrementScale(6);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA4_LandscapeUpClick(TObject *Sender)
{
IncrementScale(6);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA4_PortraitDownClick(TObject *Sender)
{
DecrementScale(7);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA4_PortraitUpClick(TObject *Sender)
{
IncrementScale(7);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA3_LandscapeDownClick(TObject *Sender)
{
DecrementScale(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA3_LandscapeUpClick(TObject *Sender)
{
IncrementScale(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA2_LandscapeDownClick(TObject *Sender)
{
DecrementScale(9);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA2_LandscapeUpClick(TObject *Sender)
{
IncrementScale(9);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA1_LandscapeDownClick(TObject *Sender)
{
DecrementScale(10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA1_LandscapeUpClick(TObject *Sender)
{
IncrementScale(10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA0_LandscapeDownClick(TObject *Sender)
{
DecrementScale(11);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbA0_LandscapeUpClick(TObject *Sender)
{
IncrementScale(11);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbOtherDownClick(TObject *Sender)
{
DecrementScale(12);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::udbOtherUpClick(TObject *Sender)
{
IncrementScale(12);
}
//---------------------------------------------------------------------------
void TfrmPrintMap::SetScaleUpDownState (int  nIndex)
{
bool    bState = !dynamic_cast<TCheckBox *>(FindComponent(cboScaleName[nIndex]))->Checked;

dynamic_cast<TFloatEdit   *>(FindComponent(fleScaleName[nIndex]))->Enabled = bState;
dynamic_cast<TCSpinButton *>(FindComponent(udbScaleName[nIndex]))->Enabled = bState;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA_PortraitClick(TObject *Sender)
{
SetScaleUpDownState(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboB_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboC_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(3);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboD_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(4);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboE_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(5);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA4_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(6);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA4_PortraitClick(TObject *Sender)
{
SetScaleUpDownState(7);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA3_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(8);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA2_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(9);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA1_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboA0_LandscapeClick(TObject *Sender)
{
SetScaleUpDownState(11);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::cboOtherClick(TObject *Sender)
{
SetScaleUpDownState(12);
}
//---------------------------------------------------------------------------
void TfrmPrintMap::LoadRegistrySettings(void)
{
int     i;

// first initialise all controls with 'reasonable' values before we try
// to read actual values from .ini file
for (i = 0; i < NUM_PAPER_SIZES; i++)
    {
    dynamic_cast<TComboBox *>(FindComponent(ddlPrinterName[i]))->ItemIndex = 0;

    dynamic_cast<TCheckBox  *>(FindComponent(cboScaleName[i]))->Checked = true;
    dynamic_cast<TFloatEdit *>(FindComponent(fleScaleName[i]))->Value   = 1.0;
    }

// now try to read in values from .ini file
for (i = 0; i < NUM_PAPER_SIZES; i++)
    {
    dynamic_cast<TComboBox *>(FindComponent(ddlPrinterName[i]))->ItemIndex =
        frmPltWorks->regSettings->ReadString(PaperSizeName[i], "Printer").ToInt();

    dynamic_cast<TCheckBox  *>(FindComponent(cboScaleName[i]))->Checked =
        frmPltWorks->regSettings->ReadString(PaperSizeName[i], "Scale_to_fit").ToInt();

    dynamic_cast<TFloatEdit *>(FindComponent(fleScaleName[i]))->Value =
        frmPltWorks->regSettings->ReadString(PaperSizeName[i], "Scale").ToDouble();
    }
}
//---------------------------------------------------------------------------
void TfrmPrintMap::SaveRegistrySettings(void)
{
int     i;

for (i = 0; i < NUM_PAPER_SIZES; i++)
    {
    frmPltWorks->regSettings->WriteString(PaperSizeName[i], "Printer",
        dynamic_cast<TComboBox *>(FindComponent(ddlPrinterName[i]))->ItemIndex);

    frmPltWorks->regSettings->WriteString(PaperSizeName[i], "Scale_to_fit",
        (int ) dynamic_cast<TCheckBox *>(FindComponent(cboScaleName[i]))->Checked);

    String      sTemp;
    frmPltWorks->regSettings->WriteString(PaperSizeName[i], "Scale",
        sTemp.FormatFloat(::String("0.0"),
            dynamic_cast<TFloatEdit *>(FindComponent(fleScaleName[i]))->Value));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintMap::btnOKClick(TObject *Sender)
{
SaveRegistrySettings();
}
//---------------------------------------------------------------------------

