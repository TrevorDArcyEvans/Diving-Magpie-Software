//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSpin"
#pragma resource "*.dfm"
TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmConfig::SetPDFInfo(PDF_Setup     PDFSetup)
{
// make our own copy to track state of ddlUnits
m_PDFSetup = PDFSetup;


long double     ConversionFactor;   // display units per point

switch (PDFSetup.Units)
    {
    case    UNITS_MILLIMETERS   :
        ConversionFactor = 25.4 / 72.0;
        break;

    case    UNITS_INCHES        :
        ConversionFactor = 1.0 / 72.0;
        break;

    default                     :
    case    UNITS_POINTS        :
        ConversionFactor = 1.0;
        break;
    }

// display units
ddlUnits->ItemIndex = PDFSetup.Units;

// page margins
fedMarginTop    ->Value = ConversionFactor * PDFSetup.PageSetup.MarginTop   ;
fedMarginBottom ->Value = ConversionFactor * PDFSetup.PageSetup.MarginBottom;
fedMarginLeft   ->Value = ConversionFactor * PDFSetup.PageSetup.MarginLeft  ;
fedMarginRight  ->Value = ConversionFactor * PDFSetup.PageSetup.MarginRight ;

// paper size
ddlPaperSize->ItemIndex = PDFSetup.PageSetup.PaperSize;
fedPageHeight->Value = ConversionFactor * PDFSetup.PageSetup.PaperHeight;
fedPageWidth ->Value = ConversionFactor * PDFSetup.PageSetup.PaperWidth ;

// update paper height and width (correctly) based on size
ddlPaperSizeChange(this);

// other page settings
chkLandscape    ->Checked = PDFSetup.PageSetup.Landscape;
rdoScaleToFit   ->Checked = PDFSetup.PageSetup.ScaleToFit;
chkKeepAspect   ->Checked = PDFSetup.PageSetup.KeepAspectRatio;
chkCentreOnPage ->Checked = PDFSetup.PageSetup.CentreOnPage;
fedScale        ->Value   = PDFSetup.PageSetup.Scale;

// update scale (correctly) based on whether check to fit page
chkScaleToFitClick(this);

// image setup
fedImageHeight  ->Value   =PDFSetup.ImageSetup.ImageHeight ;
fedImageWidth   ->Value   = PDFSetup.ImageSetup.ImageWidth;
fedJPGQuality   ->Value   = PDFSetup.ImageSetup.JPGQuality;
cbStretch       ->Checked = PDFSetup.ImageSetup.Stretch;

// infomation
edtAuthor   ->Text = ::String(PDFSetup.Info.InfoAuthor  );
edtCreator  ->Text = ::String(PDFSetup.Info.InfoCreator );
edtTitle    ->Text = ::String(PDFSetup.Info.InfoTitle   );
edtSubject  ->Text = ::String(PDFSetup.Info.InfoSubject );
edtKeyWords ->Text = ::String(PDFSetup.Info.InfoKeyWords);
}
//---------------------------------------------------------------------------
void TfrmConfig::GetPDFInfo(PDF_Setup    *PDFSetup)
{
long double     ConversionFactor;   // display units per point

switch (ddlUnits->ItemIndex)
    {
    case    UNITS_MILLIMETERS   :
        PDFSetup->Units = UNITS_MILLIMETERS;
        ConversionFactor = 25.4 / 72.0;
        break;

    case    UNITS_INCHES        :
        PDFSetup->Units = UNITS_MILLIMETERS;
        ConversionFactor = 1.0 / 72.0;
        break;

    default                     :
    case    UNITS_POINTS        :
        PDFSetup->Units = UNITS_MILLIMETERS;
        ConversionFactor = 1.0;
        break;
    }

// display units
PDFSetup->Units = (PDF_UNITS ) ddlUnits->ItemIndex;

// page margins
PDFSetup->PageSetup.MarginTop    = fedMarginTop    ->Value / ConversionFactor;
PDFSetup->PageSetup.MarginBottom = fedMarginBottom ->Value / ConversionFactor;
PDFSetup->PageSetup.MarginLeft   = fedMarginLeft   ->Value / ConversionFactor;
PDFSetup->PageSetup.MarginRight  = fedMarginRight  ->Value / ConversionFactor;

// paper size
PDFSetup->PageSetup.PaperSize   = (PDF_PAPER_SIZE ) ddlPaperSize->ItemIndex;
PDFSetup->PageSetup.PaperHeight = fedPageHeight->Value / ConversionFactor;
PDFSetup->PageSetup.PaperWidth  = fedPageWidth ->Value / ConversionFactor;

// other page settings
PDFSetup->PageSetup.Landscape       = chkLandscape    ->Checked;
PDFSetup->PageSetup.ScaleToFit      = rdoScaleToFit   ->Checked;
PDFSetup->PageSetup.KeepAspectRatio = chkKeepAspect   ->Checked;
PDFSetup->PageSetup.CentreOnPage    = chkCentreOnPage ->Checked;
PDFSetup->PageSetup.Scale           = fedScale        ->Value  ;

// image setup
PDFSetup->ImageSetup.ImageHeight = fedImageHeight  ->Value  ;
PDFSetup->ImageSetup.ImageWidth  = fedImageWidth   ->Value  ;
PDFSetup->ImageSetup.JPGQuality  = fedJPGQuality   ->Value  ;
PDFSetup->ImageSetup.Stretch     = cbStretch       ->Checked;

// infomation
PDFSetup->Info.InfoAuthor   = ::WideString(edtAuthor   ->Text).Detach();
PDFSetup->Info.InfoCreator  = ::WideString(edtCreator  ->Text).Detach();
PDFSetup->Info.InfoTitle    = ::WideString(edtTitle    ->Text).Detach();
PDFSetup->Info.InfoSubject  = ::WideString(edtSubject  ->Text).Detach();
PDFSetup->Info.InfoKeyWords = ::WideString(edtKeyWords ->Text).Detach();
}
//---------------------------------------------------------------------------
void TfrmConfig::SetAmyuni (bool          bAmyuni)
{
m_bAmyuni = bAmyuni;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormShow(TObject *Sender)
{
bool            bVisible = !m_bAmyuni;

// left margin items
lblMarginLeft   ->Visible = bVisible;
fedMarginLeft   ->Visible = bVisible;
lblUnits03      ->Visible = bVisible;

// right margin items
lblMarginRight  ->Visible = bVisible;
fedMarginRight  ->Visible = bVisible;
lblUnits04      ->Visible = bVisible;

// scale group
rdogrpScaleGroup->Visible = bVisible;
rdoScaleToFit   ->Visible = bVisible;
chkKeepAspect   ->Visible = bVisible;
rdoSpecifyScale ->Visible = bVisible;
fedScale        ->Visible = bVisible;
chkCentreOnPage ->Visible = bVisible;

// other two tab sheets
tsImageSetup ->TabVisible = bVisible;
tsInformation->TabVisible = bVisible;

// disable image setup until we've figure out how to implement it!
tsImageSetup->TabVisible = false;

if (m_bAmyuni)
    {
    lblMarginTop    ->Caption = "Horizontal:";
    lblMarginBottom ->Caption = "Vertical:";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::chkScaleToFitClick(TObject *Sender)
{
fedScale->Enabled = !rdoScaleToFit->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::ddlPaperSizeChange(TObject *Sender)
{
fedPageHeight->Enabled = (PAPER_SIZE_USER == ddlPaperSize->ItemIndex);
fedPageWidth ->Enabled = (PAPER_SIZE_USER == ddlPaperSize->ItemIndex);

// don't update paper sizes for user specified
if (PAPER_SIZE_USER == ddlPaperSize->ItemIndex)
    {
    return;
    }

long double     ConversionFactor;   // display units per point
switch (ddlUnits->ItemIndex)
    {
    case    UNITS_MILLIMETERS   :
        ConversionFactor = 25.4 / 72.0;
        break;

    case    UNITS_INCHES        :
        ConversionFactor = 1.0 / 72.0;
        break;

    default                     :
    case    UNITS_POINTS        :
        ConversionFactor = 1.0;
        break;
    }

// paper size
fedPageHeight->Value = ConversionFactor * PDF_PAPER_HEIGHT[ddlPaperSize->ItemIndex];
fedPageWidth ->Value = ConversionFactor * PDF_PAPER_WIDTH [ddlPaperSize->ItemIndex];
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::ddlUnitsChange(TObject *Sender)
{
// if the units haven't changed, no need to change any of the displayed values
if (m_PDFSetup.Units == ddlUnits->ItemIndex)
    {
    return;
    }

String          sUnits = ddlUnits->Items->Strings[ddlUnits->ItemIndex];

// change text on all the unit labels
lblUnits01->Caption = sUnits;
lblUnits02->Caption = sUnits;
lblUnits03->Caption = sUnits;
lblUnits04->Caption = sUnits;
lblUnits05->Caption = sUnits;
lblUnits06->Caption = sUnits;


PDF_Setup       PDFSetup;
long double     ConversionFactor;   // display units per point


// get point sizes based on *old* units, since ddlUnits->ItemIndex holds *new* units
switch (m_PDFSetup.Units)
    {
    case    UNITS_MILLIMETERS   :
        ConversionFactor = 25.4 / 72.0;
        break;

    case    UNITS_INCHES        :
        ConversionFactor = 1.0 / 72.0;
        break;

    default                     :
    case    UNITS_POINTS        :
        ConversionFactor = 1.0;
        break;
    }

// page margins
PDFSetup.PageSetup.MarginTop    = fedMarginTop    ->Value / ConversionFactor;
PDFSetup.PageSetup.MarginBottom = fedMarginBottom ->Value / ConversionFactor;
PDFSetup.PageSetup.MarginLeft   = fedMarginLeft   ->Value / ConversionFactor;
PDFSetup.PageSetup.MarginRight  = fedMarginRight  ->Value / ConversionFactor;

// paper size
PDFSetup.PageSetup.PaperSize   = (PDF_PAPER_SIZE ) ddlPaperSize->ItemIndex;
PDFSetup.PageSetup.PaperHeight = fedPageHeight->Value / ConversionFactor;
PDFSetup.PageSetup.PaperWidth  = fedPageWidth ->Value / ConversionFactor;


// now get the conversion factor and calculate the display values based on the
// *new* units, since ddlUnits->ItemIndex holds *new* units
switch (ddlUnits->ItemIndex)
    {
    case    UNITS_MILLIMETERS   :
        ConversionFactor = 25.4 / 72.0;
        break;

    case    UNITS_INCHES        :
        ConversionFactor = 1.0 / 72.0;
        break;

    default                     :
    case    UNITS_POINTS        :
        ConversionFactor = 1.0;
        break;
    }

// page margins
fedMarginTop    ->Value = ConversionFactor * PDFSetup.PageSetup.MarginTop   ;
fedMarginBottom ->Value = ConversionFactor * PDFSetup.PageSetup.MarginBottom;
fedMarginLeft   ->Value = ConversionFactor * PDFSetup.PageSetup.MarginLeft  ;
fedMarginRight  ->Value = ConversionFactor * PDFSetup.PageSetup.MarginRight ;

// paper size
ddlPaperSize->ItemIndex = PDFSetup.PageSetup.PaperSize;
fedPageHeight->Value = ConversionFactor * PDFSetup.PageSetup.PaperHeight;
fedPageWidth ->Value = ConversionFactor * PDFSetup.PageSetup.PaperWidth ;


// finally updated saved value for units
m_PDFSetup.Units = (PDF_UNITS ) ddlUnits->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::rdoScaleToFitClick(TObject *Sender)
{
fedScale     ->Enabled = rdoSpecifyScale->Checked;
chkKeepAspect->Enabled = rdoScaleToFit  ->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::rdoSpecifyScaleClick(TObject *Sender)
{
fedScale     ->Enabled = rdoSpecifyScale->Checked;
chkKeepAspect->Enabled = rdoScaleToFit  ->Checked;
}
//---------------------------------------------------------------------------

