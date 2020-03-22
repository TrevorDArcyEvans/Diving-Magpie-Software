// DMS_PDFWORKSIMPL : Implementation of TDMS_PDFWorksImpl (CoClass: DMS_PDFWorks, Interface: IDMS_PDFWorks)

#include <vcl.h>
#pragma hdrstop

#include "DMS_PDFWORKSIMPL.H"
#include "configure.h"
#include "pdflib.h"
#include "jpg2pdf.h"
#include "bmptojpg.hpp"

/////////////////////////////////////////////////////////////////////////////
// TDMS_PDFWorksImpl
//---------------------------------------------------------------------------
TDMS_PDFWorksImpl::TDMS_PDFWorksImpl()
{
m_hIcon             = NULL;

// flag if using Amyuni PDF printer driver
//      default = true
m_bAmyuni = true;

// top margin size in points
//      default = 0
//      min =
//      max =
m_PDF_Setup.PageSetup.MarginTop = 0;

// bottom margin size in points
//      default = 0
//      min =
//      max =
m_PDF_Setup.PageSetup.MarginBottom = 0;

// left  margin size in points
//      default = 0
//      min =
//      max =
m_PDF_Setup.PageSetup.MarginLeft = 0;

// right margin size in points
//      default = 0
//      min =
//      max =
m_PDF_Setup.PageSetup.MarginRight = 0;

// index of paper size
//      default = 8 = PAPER_SIZE_LETTER
//      min =  0 = PAPER_SIZE_A0
//      max = 12 = PAPER_SIZE_USER
m_PDF_Setup.PageSetup.PaperSize = PAPER_SIZE_LETTER;

// paper height in points
//      default = 792 = LETTER_HEIGHT
//      min =    72 =    1 in =   2.54  cm for Acrobat 3
//          =     3 = 1/24 in =   0.106 cm for Acrobat 4
//      max =  3240 =   45 in = 114.3   cm for Acrobat 3
//          = 14400 =  200 in = 508     cm for Acrobat 4
m_PDF_Setup.PageSetup.PaperHeight = letter_height;

// paper width in points
//      default = 612 = LETTER_WIDTH
//      min =    72 =    1 in =   2.54  cm for Acrobat 3
//          =     3 = 1/24 in =   0.106 cm for Acrobat 4
//      max =  3240 =   45 in = 114.3   cm for Acrobat 3
//          = 14400 =  200 in = 508     cm for Acrobat 4
m_PDF_Setup.PageSetup.PaperWidth = letter_width;

// bool flag whether to print in landscape mode
//      default = 0 = false
//      true  = 1 = print in landscape mode
//      false = 0 = print in portrait  mode
m_PDF_Setup.PageSetup.Landscape = 0;

// bool flag whether to scale image to fit on (physical) page
// note:  this is not the same as the ImageSetup.Stretch property
//      default = 0 = false
//      true  = 1 =        scale to fit on page
//      false = 0 = do not scale to fit on page
m_PDF_Setup.PageSetup.ScaleToFit = false;

// amount to scale image
//      default = 1.0 = full size
//      min = 0.0 = no size ie no image
//      max = 3.0 = 300% of nominal size
m_PDF_Setup.PageSetup.Scale = 1.0;

// bool flag whether to keep image aspect ratio when stretching to fit on
// (physical) page
//      default = 1 = true
//      true  = 1 =        maintain original image aspect ratio
//      false = 0 = do not maintain original image aspect ratio
//                  ie stretch ratio is different for height and width
m_PDF_Setup.PageSetup.KeepAspectRatio = true;

// bool flag whether to centre image on page
//      default = 0 = false
//      true  = 1 =        centre image on page
//      false = 0 = do not centre image on page
m_PDF_Setup.PageSetup.CentreOnPage = false;


// subject information to go in document General Info
//      default = "" = nothing
m_PDF_Setup.Info.InfoSubject = WideString("");

// title information to go in document General Info
//      default = "" = nothing
m_PDF_Setup.Info.InfoTitle = WideString("");

// creator information to go in document General Info
//      default = "" = nothing
m_PDF_Setup.Info.InfoCreator = WideString("");

// author information to go in document General Info
//      default = "" = nothing
m_PDF_Setup.Info.InfoAuthor = WideString("");

// keyword information to go in document General Info
//      default = "" = nothing
m_PDF_Setup.Info.InfoKeyWords = WideString("");

// jpeg image compression
//      default = 100 = no compression
//      min =   0 = total crap
//      max = 100 = no compression
m_PDF_Setup.ImageSetup.JPGQuality = 100;

// output raster image height in pixels
//      default = 0 = use screen height in pixels
//      min = 0
//      max =
m_PDF_Setup.ImageSetup.ImageHeight = 0;

// output raster image width in pixels
//      default = 0 = use screen width in pixels
//      min = 0
//      max =
m_PDF_Setup.ImageSetup.ImageWidth  = 0;

// bool flag whether to stretch image to fit the specified image width and height
// note:  this is *not the same as the PageSetup.ScaleToFit property
//      default = 0 = false
//      true  = 1 =        stretch image to fit specified size
//      false = 0 = do not centre  image to fit specified size
m_PDF_Setup.ImageSetup.Stretch = 0;

// type of units to be displayed to the user
//      default = 0 = MILLIMETERS
//      min = 0 = MILLIMETERS
//      max = 2 = POINTS
m_PDF_Setup.Units = UNITS_MILLIMETERS;
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::Configure(BSTR sTitle, long* bOK,
  PDF_Setup* pPDF_Setup)
// runs a configuration dialog so the user can specify all parameters for
// generating PDF files
//
// parameters:
//      sTitle
//          string specifying text to be displayed in the title bar of the dialog
//      bOK
//          holds return code from configuration dialog box
//          true    if user pressed OK      button
//          false   if user pressed Cancel  button
//      pPDF_Setup
//          on entry, holds configuration information to display in all the fields in the dialog box
//          on exit, if bOK is true, holds new configuration information
// note:
//      the caller must store configuration information.  This function does not
//      persist the configuration information to permanent storage ie to disk
//
//     if bOK is true, the internal configuration information is updated
{
try
    {
    frmConfig = new TfrmConfig(NULL);

    if (m_hIcon)
        {
        frmConfig->Icon->Handle = m_hIcon;
        }

    frmConfig->Caption = sTitle;

    // setup dialog box according to passed in configuration info
    frmConfig->SetPDFInfo(*pPDF_Setup);

    frmConfig->SetAmyuni(m_bAmyuni);

    frmConfig->ShowModal();

    // if user pressed OK
    if (mrOk == frmConfig->ModalResult)
        {
        // retrieve new settings
        frmConfig->GetPDFInfo(pPDF_Setup);

        // update internal configuration
        m_PDF_Setup = *pPDF_Setup;

        // and tell caller about it so he can store them somewhere
        *bOK = true;
        }
    else
        {
        *bOK = false;
        }

    delete frmConfig;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Icon(long Param1)
{
try
    {
    m_hIcon = (HICON ) Param1;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
// FIX ME!      we should really have a Stretch, Width and Height property for
// the resultant image file.  We can do this by constructing a TImage and set the
// Stretch property.  We then construct a TPicture and use it to get the image
// from the clipboard and assign TPicture to the Picture property of the TImage.
// We would then resize the TImage to the Width and Height.
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::ClipBoardToJPGFile(BSTR sFileName)
// parameters:
//     sFileName
//         name of file to save image file to
//         caller must ensure that it has the correct extension
{
try
    {
    HRESULT         hres = S_FALSE;

    String          sJPGFileName = sFileName;

    TClipboard      *pCB = Clipboard();
    if (pCB->HasFormat(CF_BITMAP))
        {
        TImage      *pImage     = new TImage(NULL);
        TPicture    *pPicture   = new TPicture();
        TBmpToJpeg  *pBmpToJpeg = new TBmpToJpeg(NULL);

        pPicture->LoadFromClipboardFormat(CF_BITMAP, pCB->GetAsHandle(CF_BITMAP), 0);

        pImage->Picture = pPicture;
        pBmpToJpeg->Image = pImage;
        pBmpToJpeg->JpegFile = sJPGFileName;
        pBmpToJpeg->CopyImageToJpeg();

        delete pBmpToJpeg;
        delete pPicture;
        delete pImage;

        hres = S_OK;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::ClipBoardToBMPFile(BSTR sFileName)
// parameters:
//     sFileName
//         name of file to save image file to
//         caller must ensure that it has the correct extension
{
try
    {
    HRESULT         hres = S_FALSE;

    String          sBMPFileName = sFileName;

    TClipboard      *pCB = Clipboard();
    if (pCB->HasFormat(CF_BITMAP))
        {
        Graphics::TBitmap *pBitmap = new Graphics::TBitmap();

        pBitmap->LoadFromClipboardFormat(CF_BITMAP, pCB->GetAsHandle(CF_BITMAP), 0);
        pBitmap->SaveToFile(sBMPFileName);

        delete pBitmap;

        hres = S_OK;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::ClipBoardToGIFFile(BSTR sFileName)
// parameters:
//      sFileName
//          name of file to save image file to
//          caller must ensure that it has the correct extension
//
// note:
//      should really return E_NOTIMPL until we pay the Unisys licencing fee :-(
{
try
    {
    HRESULT         hres = S_FALSE;

    String          sGIFFileName = sFileName;

    TClipboard      *pCB = Clipboard();
    if (pCB->HasFormat(CF_BITMAP))
        {
        TGIFImage       *pGIFImage = new TGIFImage();
        TFileStream     *pStream   = new TFileStream(sGIFFileName, fmCreate);

        pGIFImage->LoadFromClipboardFormat(CF_BITMAP, pCB->GetAsHandle(CF_BITMAP), 0);
        pGIFImage->SaveToStream(pStream);

        delete pStream;
        delete pGIFImage;

        hres = S_OK;
        }
    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::ClipBoardToPDFFile(BSTR sFileName)
// parameters:
//     sFileName
//         name of file to save PDF file to
//         caller must ensure that it has the correct extension
{
try
    {
    HRESULT         hres = S_FALSE;

    String          sPDFFileName = sFileName;

    // get temporary directory & file
    char            sTempFileDir  [MAX_PATH],
                    sTempFileName [MAX_PATH];

    GetTempPath(sizeof(sTempFileDir), sTempFileDir);
    //GetTempFileName(sTempFileDir, sPDFFileName.c_str(), 0, sTempFileName);
    GetTempFileName(sTempFileDir, "PDFWorks", 0, sTempFileName);
    DeleteFile(sTempFileName);

    // form an intermediate JPG file
    // should really use ClipBoardToGIFFile() since this will give the least
    // image loss but we have to pay the Unisys licencing fee :-(
    // could also use ClipBoardToBMPFile() and then BMP2JPG() but that means
    // two intermediary files
    hres |= ClipBoardToJPGFile(WideString(sTempFileName));

    // now do our magic!!
    hres |= jpeg_image(sTempFileName, sPDFFileName.c_str(), m_PDF_Setup);

    // remove temporary jpg file before we return
    DeleteFile(sTempFileName);

    hres = S_OK;

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_JPGQuality(long* Value)
{
try
    {
    *Value = m_PDF_Setup.ImageSetup.JPGQuality;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_JPGQuality(long Value)
{
try
    {
    // clamp image quality between 0 to 100
    m_PDF_Setup.ImageSetup.JPGQuality = (Value > 100) ? 100 : Value;
    m_PDF_Setup.ImageSetup.JPGQuality = (Value <   0) ?   0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_MarginBottom(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.MarginBottom;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_MarginTop(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.MarginTop;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_PaperHeight(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.PaperHeight;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_PaperSize(long* Value)
{
try
    {
    HRESULT         hres = S_FALSE;

    // do with a switch so that we can be sure that the paper size is valid
    switch (m_PDF_Setup.PageSetup.PaperSize)
        {
        case    PAPER_SIZE_A0       :
        case    PAPER_SIZE_A1       :
        case    PAPER_SIZE_A2       :
        case    PAPER_SIZE_A3       :
        case    PAPER_SIZE_A4       :
        case    PAPER_SIZE_A5       :
        case    PAPER_SIZE_A6       :
        case    PAPER_SIZE_B5       :
        case    PAPER_SIZE_LETTER   :
        case    PAPER_SIZE_LEGAL    :
        case    PAPER_SIZE_LEDGER   :
        case    PAPER_SIZE_P11x17   :
        case    PAPER_SIZE_USER     :
            *Value = m_PDF_Setup.PageSetup.PaperSize;
            hres = S_OK;
            break;

        default :
            hres = S_FALSE;
            break;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_PaperSize(long Value)
// sets paper size index to specified value and, if NOT a user specified size,
// updates paper height and width
{
try
    {
    HRESULT         hres = S_FALSE;

    // do with a switch so that we can be sure that the passed in
    // paper size is valid
    switch (Value)
        {
        case    PAPER_SIZE_A0       :
        case    PAPER_SIZE_A1       :
        case    PAPER_SIZE_A2       :
        case    PAPER_SIZE_A3       :
        case    PAPER_SIZE_A4       :
        case    PAPER_SIZE_A5       :
        case    PAPER_SIZE_A6       :
        case    PAPER_SIZE_B5       :
        case    PAPER_SIZE_LETTER   :
        case    PAPER_SIZE_LEGAL    :
        case    PAPER_SIZE_LEDGER   :
        case    PAPER_SIZE_P11x17   :
            // got a valid paper size, but NOT a user specified size,
            // so update internal paper height and width
            m_PDF_Setup.PageSetup.PaperHeight = PDF_PAPER_HEIGHT[Value];
            m_PDF_Setup.PageSetup.PaperWidth  = PDF_PAPER_WIDTH [Value];
            // FALLTHROUGH

        case    PAPER_SIZE_USER     :
            // got a valid paper size, including a user specified size,
            // so update paper size index
            // note that internal paper size should already have been updated
            m_PDF_Setup.PageSetup.PaperSize   = (PDF_PAPER_SIZE ) Value;
            hres = S_OK;
            break;

        default :
            hres = S_FALSE;
            break;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_PaperWidth(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.PaperWidth;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_MarginBottom(long Value)
{
try
    {
    // bottom margin can't be negative
    m_PDF_Setup.PageSetup.MarginBottom = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_MarginTop(long Value)
{
try
    {
    // top margin can't be negative
    m_PDF_Setup.PageSetup.MarginTop = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_PaperHeight(long Value)
// updates internal paper height but ONLY if PaperSize has been previously set to
// PAPER_SIZE_USER
{
try
    {
    HRESULT         hres = S_FALSE;

    if (PAPER_SIZE_USER == m_PDF_Setup.PageSetup.PaperSize)
        {
        m_PDF_Setup.PageSetup.PaperHeight = Value;
        hres = S_OK;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_PaperWidth(long Value)
// updates internal paper width but ONLY if PaperSize has been previously set to
// PAPER_SIZE_USER
{
try
    {
    HRESULT         hres = S_FALSE;

    if (PAPER_SIZE_USER == m_PDF_Setup.PageSetup.PaperSize)
        {
        // paper width can't be negative
        m_PDF_Setup.PageSetup.PaperWidth = (Value < 0) ? 0 : Value;
        hres = S_OK;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_CentreOnPage(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.CentreOnPage;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_InfoSubject(BSTR* Value)
{
try
    {
    *Value = WideString(m_PDF_Setup.Info.InfoSubject);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_Landscape(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.Landscape;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_ScaleToFit(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.ScaleToFit;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_CentreOnPage(long Value)
{
try
    {
    m_PDF_Setup.PageSetup.CentreOnPage = (true == Value) ? true : false;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_InfoSubject(BSTR Value)
{
try
    {
    m_PDF_Setup.Info.InfoSubject = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Landscape(long Value)
{
try
    {
    m_PDF_Setup.PageSetup.Landscape = (true == Value) ? true : false;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_ScaleToFit(long Value)
{
try
    {
    m_PDF_Setup.PageSetup.ScaleToFit = (true == Value) ? true : false;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_InfoCreator(BSTR* Value)
{
try
    {
    *Value = WideString(m_PDF_Setup.Info.InfoCreator);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_InfoTitle(BSTR* Value)
{
try
    {
    *Value = WideString(m_PDF_Setup.Info.InfoTitle);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_InfoCreator(BSTR Value)
{
try
    {
    m_PDF_Setup.Info.InfoCreator = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_InfoTitle(BSTR Value)
{
try
    {
    m_PDF_Setup.Info.InfoTitle = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_InfoAuthor(BSTR* Value)
{
try
    {
    *Value = WideString(m_PDF_Setup.Info.InfoAuthor);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_InfoAuthor(BSTR Value)
{
try
    {
    m_PDF_Setup.Info.InfoAuthor = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_Units(long* Value)
{
try
    {
    HRESULT     hres = S_FALSE;

    // do with a switch so that we can be sure that the passed in
    // paper size is valid
    switch (m_PDF_Setup.Units)
        {
        case    UNITS_MILLIMETERS :
        case    UNITS_INCHES      :
        case    UNITS_POINTS      :
            *Value = m_PDF_Setup.Units;
            hres = S_OK;
            break;

        default :
            hres = S_FALSE;
            break;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Units(long Value)
{
try
    {
    HRESULT     hres = S_FALSE;

    // do with a switch so that we can be sure that the passed in
    // paper size is valid
    switch (Value)
        {
        case    UNITS_MILLIMETERS :
        case    UNITS_INCHES      :
        case    UNITS_POINTS      :
            m_PDF_Setup.Units = (PDF_UNITS ) Value;
            hres = S_OK;
            break;

        default :
            hres = S_FALSE;
            break;
        }

    return hres;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_Scale(double* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.Scale;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Scale(double Value)
{
try
    {
    // clamp scale to between 0.0 and 3.0
    m_PDF_Setup.PageSetup.Scale = (Value > 3.0) ? 3.0 : Value;
    m_PDF_Setup.PageSetup.Scale = (Value < 0.0) ? 0.0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_MarginLeft(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.MarginLeft;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_MarginLeft(long Value)
{
try
    {
    // left margin can't be negative
    m_PDF_Setup.PageSetup.MarginLeft = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_MarginRight(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.MarginRight;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_MarginRight(long Value)
{
try
    {
    // right margin can't be negative
    m_PDF_Setup.PageSetup.MarginRight = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_ImageHeight(long* Value)
{
try
    {
    *Value = m_PDF_Setup.ImageSetup.ImageHeight;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_ImageHeight(long Value)
{
try
    {
    // image height can't be negative
    m_PDF_Setup.ImageSetup.ImageHeight = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_ImageWidth(long* Value)
{
try
    {
    *Value = m_PDF_Setup.ImageSetup.ImageWidth;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_ImageWidth(long Value)
{
try
    {
    // image width can't be negative
    m_PDF_Setup.ImageSetup.ImageWidth = (Value < 0) ? 0 : Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_Stretch(long* Value)
{
try
    {
    *Value = m_PDF_Setup.ImageSetup.Stretch;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Stretch(long Value)
{
try
    {
    m_PDF_Setup.ImageSetup.Stretch = (true == Value) ? true : false;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_InfoKeyWords(BSTR* Value)
{
try
    {
    *Value = WideString(m_PDF_Setup.Info.InfoKeyWords);

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_InfoKeyWords(BSTR Value)
{
try
    {
    m_PDF_Setup.Info.InfoKeyWords = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
void TDMS_PDFWorksImpl::BMP2JPG(
            String    sBMPFileName,
            String    sJPGFileName)
{
try
    {
    TBmpToJpeg      *BmpToJpeg = new TBmpToJpeg(NULL);

    BmpToJpeg->BmpFile  = sBMPFileName;
    BmpToJpeg->JpegFile = sJPGFileName;

    BmpToJpeg->CopyBmpToJpeg();

    delete BmpToJpeg;
    }
catch(Exception &e)
    {
    return (void ) Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::Initialise(PDF_Setup PDF_Init)
{
try
    {
    m_PDF_Setup = PDF_Init;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_KeepAspectRatio(long* Value)
{
try
    {
    *Value = m_PDF_Setup.PageSetup.KeepAspectRatio;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_KeepAspectRatio(long Value)
{
try
    {
    m_PDF_Setup.PageSetup.KeepAspectRatio = Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::get_Amyuni(long* Value)
{
try
    {
    *Value = m_bAmyuni;
    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------
STDMETHODIMP TDMS_PDFWorksImpl::set_Amyuni(long Value)
{
try
    {
    m_bAmyuni = Value;
    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_PDFWorks);
    }
}
//---------------------------------------------------------------------------

