// DMS_WEBWORKSIMPL : Implementation of TDMS_WebWorksImpl (CoClass: DMS_WebWorks, Interface: IDMS_WebWorks)

#include <vcl.h>
#pragma hdrstop

#include "DMS_WEBWORKSIMPL.H"
#include "configure.h"
#include <assert.h>
#include <math.h>
#include "BmpToJpg.hpp"

/////////////////////////////////////////////////////////////////////////////
// TDMS_WebWorksImpl
TDMS_WebWorksImpl::TDMS_WebWorksImpl()
{
}
//---------------------------------------------------------------------
TDMS_WebWorksImpl::~TDMS_WebWorksImpl()
{
}
//---------------------------------------------------------------------
HRESULT TDMS_WebWorksImpl::FinalConstruct()
{
    ObjectLock(this);

    m_hIcon             = NULL;
    m_SolidWorks        = NULL;

    m_XSL_FileName      = "C:\\Program Files\\SolidPartners\\WebWorks\\WebWorks.xsl";

    m_SummInfo          = true;
    m_CustomProps       = true;

    m_FileInfo          = true;
    m_Bitmap            = true;
    m_BitmapSize        = true;
    m_FileName          = true;
    m_FileNameOnly      = true;
    m_IncDirectory      = true;
    m_FileSize          = true;
    m_DateTime          = true;

    m_MassProps         = true;
    m_CentreOfMass      = true;
    m_Mass              = true;
    m_Area              = true;
    m_Volume            = true;
    m_MassMoment        = true;
    m_BoundBox          = true;

    m_BitmapWidth       = 640;
    m_BitmapHeight      = 480;

    DoLoadSettings();

    try
        {
        HRESULT                         hr;
        hr = m_DMS_Comm.CoCreateInstance(CLSID_DMS_Common);
        (void ) hr;
        }
    catch (...)
        {
        }

    return S_OK;
}
//---------------------------------------------------------------------
HRESULT TDMS_WebWorksImpl::FinalRelease  ()
{
    ObjectLock(this);

    return S_OK;
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_WebWorksImpl::Configure()
{
try
    {
    ObjectLock(this);

    frmConfigure = new TfrmConfigure(NULL);

    if (m_hIcon)
        {
        frmConfigure->Icon->Handle = m_hIcon;
        }

    frmConfigure->ShowModal();

    // reload settings regardless
    DoLoadSettings();

    delete frmConfigure;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_WebWorksImpl::set_SolidWorks(LPDISPATCH Param1)
{
try
    {
    ObjectLock(this);

    m_SolidWorks = Variant(Param1);

    #if 0
    // for testing SW marshalled correctly
    long            DateCode = 0;
    DateCode = m_SolidWorks.OleFunction("DateCode");
    #endif

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
// TDMS_WebWorksImpl::SaveAsHTML
// generates an HTML file from the currently loaded SolidWorks model, using
// the parameters loaded from WebWks.ini   An intermediate XML file is first
// generated and an XSL file is then applied to it.  The resultant HTML file
// is then saved to disk.
//
// If desired, the intermediate XML may be kept, in which case, the XSL file
// will be copied to the same directory.
//
// parameters
//      sFileName
//          fully qualified path to output HTML file, including extension
//
//      bKeepXML
//          flag whether to keep intermediate XML file
//
//          TRUE
//              use sFileName as the basis for the XML file name but replace
//              extension with ".xml"  The XSl file will be copied to the same
//              directory where the XML file is.
//
//          FALSE
//              just use a temporary file for the XML file and delete this
//              after we have generated our XML file
//
// returns
//      S_OK
//          normally
//
//      S_FALSE
//          typically if m_SolidWorks is not valid or
//          SolidWorks is not running or
//          flag to keep XML file has been set but XML file name has not or
//          XSL file name has not been set
//
// notes
STDMETHODIMP TDMS_WebWorksImpl::SaveAsHTML(BSTR sFileName, long bKeepXML)
{
try
    {
    ObjectLock(this);

    HRESULT                         hr;
    CComPtr <IDMS_XML2XSL>          XML2XSL;
    String                          sXMLFileName = ChangeFileExt(sFileName, ".xml");

    // first form our XML file
    hr = SaveAsXML(WideString(sXMLFileName));
    if (S_OK != hr) { goto CLEAN_UP; }

    hr = XML2XSL.CoCreateInstance(CLSID_DMS_XML2XSL);
    if (S_OK != hr) { goto CLEAN_UP; }

    hr |= XML2XSL->set_XML_FileName     (WideString(sXMLFileName    ));
    hr |= XML2XSL->set_XSL_FileName     (WideString(m_XSL_FileName  ));
    hr |= XML2XSL->set_Output_FileName  (WideString(sFileName       ));
    hr |= XML2XSL->Apply_XSL_XML();
    if (S_OK != hr) { goto CLEAN_UP; }


    CLEAN_UP :
        ;
    if (FALSE == bKeepXML)
        {
        DeleteFile(sXMLFileName);
        }
    else
        {
        // copy style sheet to the same location as the data file
        // note XSL file will have same name as XML file
        CopyFile(m_XSL_FileName.c_str(), ChangeFileExt(sXMLFileName, ".xsl").c_str(), FALSE);
        }

    return hr;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
// TDMS_WebWorksImpl::SaveAsXML
// generates an XML file from the currently loaded SolidWorks model, using
// the parameters loaded from WebWks.ini
//
// parameters
//      sFileName
//          fully qualified path to XML file, including extension
//
// returns
//      S_OK
//          normally
//
//      S_FALSE
//          typically if m_SolidWorks is not valid or
//          SolidWorks is not running or
//          XSL file name has not been set
//
// notes
//      copies the XSL file to the same location as the XML file
//
//      TODO    puts in tags to use XSL style sheet
STDMETHODIMP TDMS_WebWorksImpl::SaveAsXML(BSTR sFileName)
{
try
    {
    ObjectLock(this);

    HRESULT                     hr;

    bool                        bFileInfo;
    String                      sJPGFileName;
    String                      sPathName;
    DWORD                       nFileSize;
    TDateTime                   sDate = TDateTime::CurrentDateTime();

    bool                        bMassProps;
    long                        nLengthUnits;
    String                      sLengthUnitsString;
    String                      sMassUnitsString;
    double                      nCentreX;
    double                      nCentreY;
    double                      nCentreZ;
    double                      nVolume;
    double                      nArea;
    double                      nMass;
    double                      nMomentXX;
    double                      nMomentYY;
    double                      nMomentZZ;
    double                      nMomentXY;
    double                      nMomentZX;
    double                      nMomentYZ;
    double                      nBoxX;
    double                      nBoxY;
    double                      nBoxZ;

    String                      sFloatString;

    // make sure SW hasn't died in the meantime
    try
        {
        int                     bIsSWRunning;

        hr = m_DMS_Comm->IsSolidWorksRunning(&bIsSWRunning);
        (void ) hr;

        if (false == bIsSWRunning) { return S_FALSE; }
        }
    catch (...)
        {
        }

    // make sure we have an XSL style sheet
    if (true == m_XSL_FileName.IsEmpty() ||
        0    == m_XSL_FileName.Length () )
        {
        return S_FALSE;
        }

    // must have located an already running instance of SW if we get here
    TCursor                                     Save_Cursor = Screen->Cursor;

    // show hourglass cursor, may take a while
    Screen->Cursor = crHourGlass;

    try
        {
        Variant                         SWApp;
        Variant                         PartDoc;
        Variant                         View;
        HWND                            SWHandle;

        HANDLE                          hFile;
        VARIANT                         vMassPropsArray;
        VARIANT                         vBoxArray;
        double*                         MassData;
        double*                         BoxData;
        SAFEARRAY*                      psa;

        // connect to SW and get all the info
        SWApp = CreateOleObject("SldWorks.Application");
        PartDoc = SWApp.OleFunction("ActiveDoc");
        if (PartDoc.IsNull() || PartDoc.IsEmpty()){ return S_FALSE; }


        // TODO     summary info
        // TODO     custom properties


        sPathName = PartDoc.OleFunction("GetPathName");

        // work out what the size is
        hFile = CreateFile(sPathName.c_str(),
                    GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        nFileSize = GetFileSize(hFile, NULL);
        CloseHandle(hFile);


        // get the bitmap preview but convert it to JPEG for size
        sJPGFileName = ChangeFileExt(sFileName, ".jpg");

        View = PartDoc.OleFunction("ActiveView");
        SWHandle = (HWND ) int(View.OleFunction("GetViewHWnd"));
        if (SWHandle)
            {
            HDC                     SWdc = GetWindowDC(SWHandle);
            Graphics::TBitmap*      SWBitmap = new Graphics::TBitmap;
            TBmpToJpeg*             SW_JPEG  = new TBmpToJpeg(NULL);
            String                  sBMPFileName = ChangeFileExt(sFileName, ".bmp");
            TRect                   Rect;

            GetWindowRect(SWHandle, &Rect);

            if (m_BitmapSize)
                {
                // use user values
                SWBitmap->Width  = m_BitmapWidth ;
                SWBitmap->Height = m_BitmapHeight;
                }
            else
                {
                // use the current SW size
                SWBitmap->Width  = Rect.Right  - Rect.Left;
                SWBitmap->Height = Rect.Bottom - Rect.Top;
                }

            // bring SW to the top, even though it should already be there
            SetWindowPos(SWHandle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

            // force a redraw since the Window DC may still have the Save-As
            // dialog in it
            PartDoc.OleFunction("GraphicsRedraw2");

            SetStretchBltMode(SWBitmap->Canvas->Handle, COLORONCOLOR);
            StretchBlt(
                SWBitmap->Canvas->Handle, 0, 0, SWBitmap->Width         , SWBitmap->Height      ,
                SWdc                    , 0, 0, Rect.Right - Rect.Left  , Rect.Bottom - Rect.Top,
                SRCCOPY);

            // dump to an intermediate BMP file
            SWBitmap->SaveToFile(sBMPFileName);

            SW_JPEG->BmpFile  = sBMPFileName;
            SW_JPEG->JpegFile = sJPGFileName;
            SW_JPEG->CopyBmpToJpeg();

            // remove the BMP file and use the JPEG since it is a *lot* smaller
            DeleteFile(sBMPFileName);

            delete SWBitmap;
            delete SW_JPEG;
            ReleaseDC(SWHandle, SWdc);
            }


        // what units are we using for length and mass
        nLengthUnits = PartDoc.OleFunction("LengthUnit");
        switch (nLengthUnits)
            {
            default :
            case swMM           : sLengthUnitsString = "mm"  ; sMassUnitsString = "g" ; break;
            case swCM           : sLengthUnitsString = "cm"  ; sMassUnitsString = "g" ; break;
            case swMETER        : sLengthUnitsString = "m"   ; sMassUnitsString = "kg"; break;
            case swINCHES       : sLengthUnitsString = "in"  ; sMassUnitsString = "lb"; break;
            case swFEET         : sLengthUnitsString = "ft"  ; sMassUnitsString = "lb"; break;
            case swFEETINCHES   : sLengthUnitsString = "inft"; sMassUnitsString = "lb"; break;
            }

        // get all the mass properties
        vMassPropsArray = PartDoc.OleFunction("GetMassProperties");
        psa =  V_ARRAY(&vMassPropsArray);

        // access the SafeArray data
        hr = SafeArrayAccessData(psa, (void **)&MassData);
        if (S_OK != hr) { goto CLEAN_UP; }

        nCentreX    = MassData[ 0];
        nCentreY    = MassData[ 1];
        nCentreZ    = MassData[ 2];
        nVolume     = MassData[ 3];
        nArea       = MassData[ 4];
        nMass       = MassData[ 5];
        nMomentXX   = MassData[ 6];
        nMomentYY   = MassData[ 7];
        nMomentZZ   = MassData[ 8];
        nMomentXY   = MassData[ 9];
        nMomentZX   = MassData[10];
        nMomentYZ   = MassData[11];

        hr = SafeArrayUnaccessData(psa);    // Unaccess the SafeArray
        hr = SafeArrayDestroy(psa);         // Destroy the SafeArray


        // bounding box dimensions
        vBoxArray = PartDoc.OleFunction("GetPartBox", TRUE);

        psa =  V_ARRAY(&vBoxArray);

        // access the SafeArray data
        hr = SafeArrayAccessData(psa, (void **)&BoxData);
        if (S_OK != hr) { goto CLEAN_UP; }

        nBoxX = fabs(BoxData[0] - BoxData[1]);
        nBoxY = fabs(BoxData[2] - BoxData[3]);
        nBoxZ = fabs(BoxData[4] - BoxData[5]);

        hr = SafeArrayUnaccessData(psa);    // Unaccess the SafeArray
        hr = SafeArrayDestroy(psa);         // Destroy the SafeArray
        }
    __finally
        {
        Screen->Cursor = Save_Cursor; // always restore the cursor
        }

    try
        {
        #define     NODE_NULL       (Msxml_tlb::IXMLDOMNodePtr *) NULL
        #define     NODE_PTR        (Msxml_tlb::IXMLDOMNodePtr  )
        #define     ELEM_PTR        (Msxml_tlb::IXMLDOMElementPtr *)

        const String                                FloatFmt = "0.00000000";

        CComQIPtr <Msxml_tlb::IXMLDOMDocument>      pDOM_Doc;

        CComQIPtr <Msxml_tlb::IXMLDOMElement>       pDOM_Root;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>         pDOM_SummInfo;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>         pDOM_CustomProps;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>         pDOM_FileInfo;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_Bitmap;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_FileName;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_FileSize;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_FileDate;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>         pDOM_MassProps;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_LengthUnits;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_MassUnits;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_Mass;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_MassCentre;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassCentreX;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassCentreY;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassCentreZ;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_Area;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_Volume;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_MassMoment;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentXX;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentYY;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentZZ;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentXY;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentZX;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>             pDOM_MassMomentYZ;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>         pDOM_Box;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_BoxX;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_BoxY;
        CComQIPtr <Msxml_tlb::IXMLDOMElement>           pDOM_BoxZ;


        hr = pDOM_Doc.CoCreateInstance(Msxml_tlb::CLSID_DOMDocument);
        if (S_OK != hr) { goto CLEAN_UP; }

        // get all the elements for our structure
        hr |= pDOM_Doc->createElement(WideString("MODEL"           ), ELEM_PTR &pDOM_Root          );
        hr |= pDOM_Doc->createElement(WideString(  "SUMMARY_INFO"  ), ELEM_PTR &pDOM_SummInfo      );
        hr |= pDOM_Doc->createElement(WideString(  "CUSTOM_PROPS"  ), ELEM_PTR &pDOM_CustomProps   );
        hr |= pDOM_Doc->createElement(WideString(  "FILE_INFO"     ), ELEM_PTR &pDOM_FileInfo      );
        hr |= pDOM_Doc->createElement(WideString(    "BITMAP"      ), ELEM_PTR &pDOM_Bitmap        );
        hr |= pDOM_Doc->createElement(WideString(    "NAME"        ), ELEM_PTR &pDOM_FileName      );
        hr |= pDOM_Doc->createElement(WideString(    "SIZE"        ), ELEM_PTR &pDOM_FileSize      );
        hr |= pDOM_Doc->createElement(WideString(    "DATE"        ), ELEM_PTR &pDOM_FileDate      );
        hr |= pDOM_Doc->createElement(WideString(  "MASS_PROPS"    ), ELEM_PTR &pDOM_MassProps     );
        hr |= pDOM_Doc->createElement(WideString(    "LENGTH_UNITS"), ELEM_PTR &pDOM_LengthUnits   );
        hr |= pDOM_Doc->createElement(WideString(    "MASS_UNITS"  ), ELEM_PTR &pDOM_MassUnits     );
        hr |= pDOM_Doc->createElement(WideString(    "MASS"        ), ELEM_PTR &pDOM_Mass          );
        hr |= pDOM_Doc->createElement(WideString(    "AREA"        ), ELEM_PTR &pDOM_Area          );
        hr |= pDOM_Doc->createElement(WideString(    "VOLUME"      ), ELEM_PTR &pDOM_Volume        );
        hr |= pDOM_Doc->createElement(WideString(    "CENTRE"      ), ELEM_PTR &pDOM_MassCentre    );
        hr |= pDOM_Doc->createElement(WideString(      "X"         ), ELEM_PTR &pDOM_MassCentreX   );
        hr |= pDOM_Doc->createElement(WideString(      "Y"         ), ELEM_PTR &pDOM_MassCentreY   );
        hr |= pDOM_Doc->createElement(WideString(      "Z"         ), ELEM_PTR &pDOM_MassCentreZ   );
        hr |= pDOM_Doc->createElement(WideString(    "MOMENT"      ), ELEM_PTR &pDOM_MassMoment    );
        hr |= pDOM_Doc->createElement(WideString(      "XX"        ), ELEM_PTR &pDOM_MassMomentXX  );
        hr |= pDOM_Doc->createElement(WideString(      "YY"        ), ELEM_PTR &pDOM_MassMomentYY  );
        hr |= pDOM_Doc->createElement(WideString(      "ZZ"        ), ELEM_PTR &pDOM_MassMomentZZ  );
        hr |= pDOM_Doc->createElement(WideString(      "XY"        ), ELEM_PTR &pDOM_MassMomentXY  );
        hr |= pDOM_Doc->createElement(WideString(      "ZX"        ), ELEM_PTR &pDOM_MassMomentZX  );
        hr |= pDOM_Doc->createElement(WideString(      "YZ"        ), ELEM_PTR &pDOM_MassMomentYZ  );
        hr |= pDOM_Doc->createElement(WideString(    "BOX"         ), ELEM_PTR &pDOM_Box           );
        hr |= pDOM_Doc->createElement(WideString(      "X"         ), ELEM_PTR &pDOM_BoxX          );
        hr |= pDOM_Doc->createElement(WideString(      "Y"         ), ELEM_PTR &pDOM_BoxY          );
        hr |= pDOM_Doc->createElement(WideString(      "Z"         ), ELEM_PTR &pDOM_BoxZ          );
        if (S_OK != hr) { goto CLEAN_UP; }

        // put info in all the nodes

        // TODO     summary info
        // TODO     custom properties

        hr |= pDOM_Bitmap  ->set_text(WideString(sJPGFileName));
        hr |= pDOM_FileName->set_text(WideString(sPathName));
        hr |= pDOM_FileSize->set_text(WideString(::String(nFileSize)));
        hr |= pDOM_FileDate->set_text(WideString(sDate.DateTimeString()));

        hr |= pDOM_LengthUnits->set_text(WideString(sLengthUnitsString));
        hr |= pDOM_MassUnits  ->set_text(WideString(sMassUnitsString  ));

        hr |= pDOM_Mass  ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMass  )));
        hr |= pDOM_Area  ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nArea  )));
        hr |= pDOM_Volume->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nVolume)));

        hr |= pDOM_MassCentreX->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nCentreX)));
        hr |= pDOM_MassCentreY->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nCentreY)));
        hr |= pDOM_MassCentreZ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nCentreZ)));

        hr |= pDOM_MassMomentXX->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentXX)));
        hr |= pDOM_MassMomentYY->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentYY)));
        hr |= pDOM_MassMomentZZ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentZZ)));
        hr |= pDOM_MassMomentXY->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentXY)));
        hr |= pDOM_MassMomentZX->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentZX)));
        hr |= pDOM_MassMomentYZ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nMomentYZ)));

        hr |= pDOM_BoxX->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nBoxX)));
        hr |= pDOM_BoxY->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nBoxY)));
        hr |= pDOM_BoxZ->set_text(WideString(sFloatString.FormatFloat(FloatFmt, nBoxZ)));
        if (S_OK != hr) { goto CLEAN_UP; }

        // setup the DOM tree according to what the user wanted
        hr |= pDOM_Doc->appendChild(NODE_PTR pDOM_Root, NODE_NULL);

        // TODO     XSL file reference but how??

        // TODO     summary info
        if (m_SummInfo)
            {
            hr |= pDOM_Root->appendChild(NODE_PTR pDOM_SummInfo, NODE_NULL);
            }

        // TODO     custom properties
        if (m_CustomProps)
            {
            hr |= pDOM_Root->appendChild(NODE_PTR pDOM_CustomProps, NODE_NULL);
            }

        if (m_FileInfo)
            {
            hr |= pDOM_Root->appendChild(NODE_PTR pDOM_FileInfo, NODE_NULL);

            if (m_Bitmap)
                {
                hr |= pDOM_FileInfo->appendChild(NODE_PTR pDOM_Bitmap, NODE_NULL);
                }

            if (m_FileName)
                {
                hr |= pDOM_FileInfo->appendChild(NODE_PTR pDOM_FileName, NODE_NULL);
                }

            if (m_FileSize)
                {
                hr |= pDOM_FileInfo->appendChild(NODE_PTR pDOM_FileSize, NODE_NULL);
                }

            if (m_DateTime)
                {
                hr |= pDOM_FileInfo->appendChild(NODE_PTR pDOM_FileDate, NODE_NULL);
                }
            }

        // must have mass properties box checked and at least one specific
        // mass property
        if (m_MassProps &&
                (
                m_Mass          ||
                m_Area          ||
                m_Volume        ||
                m_CentreOfMass  ||
                m_MassMoment    ||
                m_BoundBox
                ))
            {
            hr |= pDOM_Root->appendChild(NODE_PTR pDOM_MassProps, NODE_NULL);

            // something checked, so we'll need the units
            hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_LengthUnits, NODE_NULL);
            hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_MassUnits  , NODE_NULL);

            if (m_Mass)
                {
                hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_Mass, NODE_NULL);
                }

            if (m_Area)
                {
                hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_Area, NODE_NULL);
                }

            if (m_Volume)
                {
                hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_Volume, NODE_NULL);
                }

            if (m_CentreOfMass)
                {
                hr |= pDOM_MassProps ->appendChild(NODE_PTR pDOM_MassCentre , NODE_NULL);
                hr |= pDOM_MassCentre->appendChild(NODE_PTR pDOM_MassCentreX, NODE_NULL);
                hr |= pDOM_MassCentre->appendChild(NODE_PTR pDOM_MassCentreY, NODE_NULL);
                hr |= pDOM_MassCentre->appendChild(NODE_PTR pDOM_MassCentreZ, NODE_NULL);
                }

            if (m_MassMoment)
                {
                hr |= pDOM_MassProps ->appendChild(NODE_PTR pDOM_MassMoment  , NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentXX, NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentYY, NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentZZ, NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentXY, NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentZX, NODE_NULL);
                hr |= pDOM_MassMoment->appendChild(NODE_PTR pDOM_MassMomentYZ, NODE_NULL);
                }

            if (m_BoundBox)
                {
                hr |= pDOM_MassProps->appendChild(NODE_PTR pDOM_Box , NODE_NULL);
                hr |= pDOM_Box      ->appendChild(NODE_PTR pDOM_BoxX, NODE_NULL);
                hr |= pDOM_Box      ->appendChild(NODE_PTR pDOM_BoxY, NODE_NULL);
                hr |= pDOM_Box      ->appendChild(NODE_PTR pDOM_BoxZ, NODE_NULL);
                }
            }
        if (S_OK != hr) { goto CLEAN_UP; }

        // finally write out to disk
        hr |= pDOM_Doc->save(sFileName);
        if (S_OK != hr) { goto CLEAN_UP; }
        }
    catch (...)
        {
        }


    CLEAN_UP :
        ;

    return hr;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_WebWorksImpl::get_XSL_FileName(BSTR* sFileName)
{
try
    {
    ObjectLock(this);

    *sFileName = WideString(m_XSL_FileName).Detach();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
// TDMS_WebWorksImpl::set_XSL_FileName
// parameters
//      sFileName
//          fully qualified path to XSL file, including extension
STDMETHODIMP TDMS_WebWorksImpl::set_XSL_FileName(BSTR sFileName)
{
try
    {
    ObjectLock(this);

    m_XSL_FileName = sFileName;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_WebWorksImpl::set_Icon(long Value)
{
try
    {
    ObjectLock(this);

    m_hIcon = (HICON ) Value;

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_WebWorksImpl::LoadSettings()
{
try
    {
    ObjectLock(this);

    DoLoadSettings();

    return S_OK;
    }
catch(Exception &e)
    {
    return Error(e.Message.c_str(), IID_IDMS_WebWorks);
    }
}
//---------------------------------------------------------------------
// ExtractSW_BitmapToJPG_File
// not used but working - SW locks the file so we cannot open the file
// However, this code could be used elsewhere
void __fastcall TDMS_WebWorksImpl::ExtractSW_BitmapToJPG_File
(
    String      strSWFileName   ,
    String      strJPGFileName  ,
    int         nWidth          ,
    int         nHeight         ,
    bool        bStretch
)
{
try
    {
    HRESULT                 hr;
    IStorage*               pRoot;
    IStream*                pPreview;
    TImage*                 SWBitmap = new TImage(NULL);
    TBmpToJpeg*             SW_JPEG  = new TBmpToJpeg(NULL);
    String                  strBMPFileName = ChangeFileExt(strJPGFileName, ".bmp");

    if (S_OK == (hr = StgOpenStorage(WideString(strSWFileName), NULL,
                    STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
                    NULL, 0, &pRoot)))
        {
        if (S_OK == pRoot->OpenStream(WideString("Preview"),
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
                        0, &pPreview))
            {
            DWORD DataSize = 0;
            DWORD numRead = 0;
            pPreview->Read(&DataSize, sizeof(DWORD), &numRead);
            if (DataSize > 0)
                {
                char* dibData = new char[DataSize];
                pPreview->Read(dibData, DataSize, &numRead);
                assert(numRead == DataSize);

                LPBITMAPINFOHEADER DIBData = (LPBITMAPINFOHEADER ) dibData;

                int offset = 3;    // to have the frame look good
                DWORD dwLen = DIBData->biSize + (1 << DIBData->biBitCount) * sizeof(RGBQUAD);

                if (true == bStretch)
                    {
                    SWBitmap->Picture->Bitmap->Width  = nWidth ;
                    SWBitmap->Picture->Bitmap->Height = nHeight;
                    }
                else
                    {
                    SWBitmap->Picture->Bitmap->Width  = DIBData->biWidth ;
                    SWBitmap->Picture->Bitmap->Height = DIBData->biHeight;
                    }

                int numLines = StretchDIBits(
                        SWBitmap->Canvas->Handle,
                        offset, offset, SWBitmap->Picture->Bitmap->Width - offset * 2, SWBitmap->Picture->Bitmap->Height - offset * 2,
                        0     , 0     , DIBData->biWidth                             , DIBData->biHeight                             ,
                        (LPSTR ) DIBData + dwLen,   // address of bitmap bits
                        (LPBITMAPINFO ) DIBData,    // address of bitmap data
                        DIB_RGB_COLORS, SRCCOPY);
                (void ) numLines;

                delete dibData;
                }//if DataSize

            pPreview->Release();
            }//if OpenStream
        pRoot->Release();

        // dump to an intermediate BMP file
        SWBitmap->Picture->SaveToFile(strBMPFileName);

        SW_JPEG->BmpFile  = strBMPFileName;
        SW_JPEG->JpegFile = strJPGFileName;
        SW_JPEG->CopyBmpToJpeg();

        // remove the BMP file and use the JPEG since it is a *lot* smaller
        DeleteFile(strBMPFileName);

        delete SWBitmap;
        delete SW_JPEG;
        }//if StgOpenStorage
    (void ) hr;
    }
catch (...)
    {
    }
}
//---------------------------------------------------------------------
void TDMS_WebWorksImpl::DoLoadSettings()
{
    const String    WEB_WORKS_INI_FILE_NAME = "WebWorks.ini";
    const String    Configuration           = "Configuration";

    TIniFile*       ini = new TIniFile(WEB_WORKS_INI_FILE_NAME);

    try
        {
        m_XSL_FileName      = ini->ReadString(Configuration, "fedXSL_FileName_Text"       , "C:\\Program Files\\SolidPartners\\WebWorks\\WebWorks.xsl" );

        m_SummInfo          = ini->ReadString(Configuration, "chkSummInfo_Checked"        , "false") == "true";
        m_CustomProps       = ini->ReadString(Configuration, "chkCustomProps_Checked"     , "false") == "true";

        m_FileInfo          = ini->ReadString(Configuration, "chkFileInfo_Checked"        , "false") == "true";
        m_Bitmap            = ini->ReadString(Configuration, "chkBitmap_Checked"          , "false") == "true";
        m_BitmapSize        = ini->ReadString(Configuration, "chkBitmapSize_Checked"      , "false") == "true";
        m_FileName          = ini->ReadString(Configuration, "chkFileName_Checked"        , "false") == "true";
        m_FileNameOnly      = ini->ReadString(Configuration, "rdoFileNameOnly_Checked"    , "false") == "true";
        m_IncDirectory      = ini->ReadString(Configuration, "rdoIncDirectory_Checked"    , "false") == "true";
        m_FileSize          = ini->ReadString(Configuration, "chkFileSize_Checked"        , "false") == "true";
        m_DateTime          = ini->ReadString(Configuration, "chkDateTime_Checked"        , "false") == "true";

        m_MassProps         = ini->ReadString(Configuration, "chkMassProps_Checked"       , "false") == "true";
        m_CentreOfMass      = ini->ReadString(Configuration, "chkCentreOfMass_Checked"    , "false") == "true";
        m_Mass              = ini->ReadString(Configuration, "chkMass_Checked"            , "false") == "true";
        m_Area              = ini->ReadString(Configuration, "chkArea_Checked"            , "false") == "true";
        m_Volume            = ini->ReadString(Configuration, "chkVolume_Checked"          , "false") == "true";
        m_MassMoment        = ini->ReadString(Configuration, "chkMassMoment_Checked"      , "false") == "true";
        m_BoundBox          = ini->ReadString(Configuration, "chkBoundBox_Checked"        , "false") == "true";

        m_BitmapWidth       = ini->ReadInteger(Configuration, "sedWidth_Value"        , 640);
        m_BitmapHeight      = ini->ReadInteger(Configuration, "sedHeight_Value"       , 480);
        }
    catch (...)
        {
        }
   delete ini;
}
//---------------------------------------------------------------------

