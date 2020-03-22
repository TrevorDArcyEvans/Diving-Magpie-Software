//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "DMS_PDFWks_TLB.h"

// only for paper size constants
#include "pdflib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TCOMIDMS_PDFWorks      DMS_PDFWorks_test;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
PDFSetup.PageSetup.MarginTop    = 20;
PDFSetup.PageSetup.MarginBottom = 25;
PDFSetup.PageSetup.MarginLeft   = 30;
PDFSetup.PageSetup.MarginRight  = 40;

// note setting height and width but paper size is NOT user
// However, we are not using the set_PaperHeight/Width methods,
// so these values will be applied and should be displayed
// as set here!
PDFSetup.PageSetup.PaperSize    = PAPER_SIZE_A1;
PDFSetup.PageSetup.PaperHeight  = a4_height;
PDFSetup.PageSetup.PaperWidth   = a4_width;

PDFSetup.PageSetup.Landscape        = true;
PDFSetup.PageSetup.ScaleToFit       = true;
PDFSetup.PageSetup.KeepAspectRatio  = true;
PDFSetup.PageSetup.Scale            = 2.0;
PDFSetup.PageSetup.CentreOnPage     = true;

PDFSetup.Info.InfoSubject   = WideString("InfoSubject").Detach();
PDFSetup.Info.InfoTitle     = WideString("InfoTitle").Detach();
PDFSetup.Info.InfoCreator   = WideString("InfoCreator").Detach();
PDFSetup.Info.InfoAuthor    = WideString("InfoAuthor").Detach();
PDFSetup.Info.InfoKeyWords  = WideString("InfoKeyWords").Detach();

PDFSetup.ImageSetup.JPGQuality  =  80;
PDFSetup.ImageSetup.ImageHeight = 200;
PDFSetup.ImageSetup.ImageWidth  = 400;
PDFSetup.ImageSetup.Stretch     = true;

PDFSetup.Units = UNITS_MILLIMETERS;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
long                bOK;

DMS_PDFWorks_test->set_Icon((long ) Application->Icon->Handle);

DMS_PDFWorks_test->Configure(
    ::WideString("Test").Detach(),
    &bOK,
    &PDFSetup);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
::CoInitialize(0);
DMS_PDFWorks_test = CoDMS_PDFWorks::Create();
DMS_PDFWorks_test->Initialise(PDFSetup);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
::CoUninitialize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
String      SFileName = ChangeFileExt(Edit1->Text, ::String(".jpg"));

DMS_PDFWorks_test->ClipBoardToJPGFile(::WideString(SFileName).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
String      SFileName = ChangeFileExt(Edit1->Text, ::String(".bmp"));

DMS_PDFWorks_test->ClipBoardToBMPFile(::WideString(SFileName).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
String      SFileName = ChangeFileExt(Edit1->Text, ::String(".gif"));

DMS_PDFWorks_test->ClipBoardToGIFFile(::WideString(SFileName).Detach());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
String      SFileName = ChangeFileExt(Edit1->Text, ::String(".pdf"));

DMS_PDFWorks_test->ClipBoardToPDFFile(::WideString(SFileName).Detach());
}
//---------------------------------------------------------------------------

