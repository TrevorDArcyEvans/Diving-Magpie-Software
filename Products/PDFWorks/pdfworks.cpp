//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: PDFWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1

#include "PDFWorks.h"
#include "amapp.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "Resource.h"
#include <tchar.h>

#include <atlbase.h>
#include <objbase.h>

#include "DMS_PDFWks.h"
#include "DMS_PDFWks_i.c"

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include <shlwapi.h>

#include "cdintf.h"
#include "configure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ---------------------------------------------------------------

// the application object
CPDFWorksApp*                   TheApplication = NULL;

static AFX_EXTENSION_MODULE     PDFWorksDLL = { NULL, NULL };

ICDIntf                         PDFPrinter;

// local function prototypes -------------------------------------

BOOL FileExists(LPCTSTR lpFileName);

void WindowToClipBoard(LPSLDWORKS pSolidWorks);

void PDF_ConfigLoad(void);
void PDF_ConfigSave(void);
void PDF_CheckRegistered
(
    bool            bShowDialog
);

// ---------------------------------------------------------------

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    long                        nRetVal;

    if (dwReason == DLL_PROCESS_ATTACH)
        {
        TRACE0("PDFWorks.DLL Initializing!\n");

        // Extension DLL one-time initialization
        AfxInitExtensionModule(PDFWorksDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(PDFWorksDLL);


        // PDFWorks initialisation
        CoInitialize(NULL);
        nRetVal = PDFPrinter.CreateDispatch(_T("CDIntf.CDIntf"));
        nRetVal = PDFPrinter.PDFDriverInit(_T("PDF Compatible Printer Driver"));
        }
    else if (dwReason == DLL_PROCESS_DETACH)
        {
        TRACE0("PDFWorks.DLL Terminating!\n");

        // PDFWorks shutdown
        try
            {
            //PDFPrinter.DriverEnd();
            PDFPrinter.DetachDispatch();
            }
        catch (...)
            {
            TRACE0("PDFWorks.DLL Exception thrown in DLL_PROCESS_DETACH\n");
            }


        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;


        // Terminate the library before destructors are called
        AfxTermExtensionModule(PDFWorksDLL);
        }
    return 1;   // ok
}

// --------------------------------
//  connections to SolidWorks
// --------------------------------

#define DllExport __declspec( dllexport )

// this is the function SolidWorks calls to connect
// to the add-in application
long DllExport InitUserDLL3(LPSLDWORKS pSldWorks)
{
    // this function should be called once per session
    if ( TheApplication != NULL )
        {
        ASSERT ( FALSE );
        return 0;
        }

    // start the application
    TheApplication = new CPDFWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;


    // load configuration from storage into m_PDF_Setup
    PDF_ConfigLoad();


    // check registration status
    g_bRegistered = false;

    PDF_CheckRegistered(false);

    // connected successfully
    return 1;
}
// ---------------------------------------------------------------
void WindowToClipBoard(LPSLDWORKS pSolidWorks)
{
    #define     CLEANUP     AfxSetResourceHandle(hSaveResource)

    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);


    CComPtr<IModelView>         pModelView;
    CComQIPtr<IModelDoc>        pActiveDoc;

    DIBSECTION*                 pDIBSection = NULL;
    BITMAPINFO                  BitMapInfo;
    HBITMAP                     hBitmap;

    long                        nDummyDIBSection = 0;

    if (S_OK != pSolidWorks->get_IActiveDoc(&pActiveDoc))
        {
        CLEANUP;
        return;
        }

    if (S_OK != pActiveDoc->get_IActiveView(&pModelView))
        {
        CLEANUP;
        return;
        }

    if (S_OK != pModelView->GetViewDIB(&nDummyDIBSection))
        {
        CLEANUP;
        return;
        }

    pDIBSection = (DIBSECTION *) nDummyDIBSection;

    BitMapInfo.bmiHeader                = pDIBSection->dsBmih;
    BitMapInfo.bmiColors[0].rgbBlue     = 0;
    BitMapInfo.bmiColors[0].rgbGreen    = 0;
    BitMapInfo.bmiColors[0].rgbRed      = 0;
    BitMapInfo.bmiColors[0].rgbReserved = 0;

    hBitmap = CreateDIBitmap(
                GetDC(NULL),
                &pDIBSection->dsBmih,
                CBM_INIT,
                pDIBSection->dsBm.bmBits,      // pointer to initialization data
                &BitMapInfo,  // pointer to bitmap color-format data
                DIB_RGB_COLORS);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    // see SWAPI help file for ModelView::GetViewDIB()
    CoTaskMemFree(pDIBSection);

    // Reset to previous resource handle
    CLEANUP;

    return;
}//WindowToClipBoard
// ---------------------------------------------------------------
// PDF_SaveAsPDF
// SldWorks::AddFileSaveAsItem
// The format of the FileName argument is:
//
//     <FullPath > <FileName> <AccessType>
//
// where:
//
// FullPath is the file name with full path information,
// FileName is the file name and extension (without separator),
// AccessType is w or r
//
// TDE
// NB: the FileName argument appears to be all in upper case
void DllExport PDF_SaveAsPDF
(
    LPTSTR                      FileName,
    LPSLDWORKS                  pSolidWorks
)
{
    #define     CLEANUP     AfxSetResourceHandle(hSaveResource)

    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);

    // only proceed if registered or not exceeded trial limits
    if (g_nPDFSaveCount > MAX_UNREG_PDF_SAVES &&
        FALSE == g_bRegistered)
        {
        MessageBox(NULL, _T("Unregistered save limit reached."), PDF_WORKS_TITLE,
            MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

        CLEANUP;
        return;
        }


    CComQIPtr<IModelDoc>        pActiveDoc;
    if (S_OK != pSolidWorks->get_IActiveDoc(&pActiveDoc))
        {
        CLEANUP;
        return;
        }

    // now generate the PDF file name based on the full path which was passed in
    CString                     cstrPDFFileName(FileName),
                                cstrSWFileExt, cstrSWFullFileName;
    long                        doctype;
    CComBSTR                    sTempString;


    // get the full path name of the currently active document, which will be
    // the same one for which we are generating the pdf file
    pActiveDoc->GetPathName(&sTempString);
    cstrSWFullFileName = sTempString;

    cstrSWFullFileName.MakeLower();
    cstrPDFFileName   .MakeLower();

    // get the document type
    pActiveDoc->GetType(&doctype);

    // if we can't find the .pdf extension
    if (-1 == cstrPDFFileName.Find(_T(".pdf")))
        {
        switch (doctype)
            {
            case    swDocPART       :
                cstrSWFileExt = _T(".sldprt");
                break;

            case    swDocASSEMBLY   :
                cstrSWFileExt = _T(".sldasm");
                break;

            case    swDocDRAWING    :
                cstrSWFileExt = _T(".slddrw");
                break;

            default                 :
                break;
            }
        }
    else
        {
        // must have .pdf extension - we hope
        cstrSWFileExt = _T(".pdf");
        }

    // truncate string at full path including extn
    int         nExtLoc = cstrPDFFileName.Find(cstrSWFileExt);
    if (-1 != nExtLoc)
        {
        cstrPDFFileName.Delete(nExtLoc + _tcslen(cstrSWFileExt),
                cstrPDFFileName.GetLength() - nExtLoc - _tcslen(cstrSWFileExt));
        }

    // add .pdf extension
    cstrPDFFileName.Replace(LPCTSTR(cstrSWFileExt), _T(".pdf"));


    // get our magic PDF generator
    CComPtr<IDMS_PDFWorks>      DMS_PDFWks;
    HRESULT                     hres;

    hres = DMS_PDFWks.CoCreateInstance(__uuidof(DMS_PDFWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hres));

    if (SUCCEEDED(hres))
        {
        DMS_PDFWks->Initialise(m_PDF_Setup);
        }
    else
        {
        MessageBox(NULL,
            _T("Sorry, could not create PDF generator."),
            PDF_WORKS_TITLE, MB_OK | MB_ICONERROR);

        CLEANUP;
        return;
        }


    if (swDocDRAWING == doctype)
        {
        CComBSTR                    sSheetName;
        CComBSTR                    sDrwPDFFileName;
        LPDISPATCH                  pSheet = NULL;
        CComQIPtr<ISheet>           pQISheet;

        long                        nSheetCount = 0;
        long                        i = 0;

        CComQIPtr<IDrawingDoc>      pQIDrawDoc = pActiveDoc;
        if (pQIDrawDoc == NULL)
            {
            CLEANUP;
            return;
            }

        if (S_OK != pQIDrawDoc->GetSheetCount(&nSheetCount))
            {
            CLEANUP;
            return;
            }

        // go to the first sheet
        for (i = 0; i < nSheetCount; i++)
            {
            // don't check return values here because we could call this from
            // the first drw sheet
            pQIDrawDoc->SheetPrevious();
            }

        // remove .pdf extension & replace with underscore
        cstrPDFFileName.Replace(_T(".pdf"), _T("_"));

        for (i = 0; i < nSheetCount; i++)
            {
            // refresh the current doc
            if (S_OK != pSolidWorks->get_IActiveDoc(&pActiveDoc))
                {
                CLEANUP;
                return;
                }

            if (S_OK != pActiveDoc->ViewZoomtofit2())
                {
                CLEANUP;
                return;
                }

            // copy the current print preview image to the clipboard
            WindowToClipBoard(pSolidWorks);

            // get the current sheet name
            if (S_OK != pQIDrawDoc->GetCurrentSheet(&pSheet))
                {
                CLEANUP;
                return;
                }
            pQISheet = pSheet;
            pSheet->Release();
            if (pQISheet == NULL)
                {
                CLEANUP;
                return;
                }

            if (S_OK != pQISheet->GetName(&sSheetName))
                {
                CLEANUP;
                return;
                }

            // form PDF file name for this sheet
            sDrwPDFFileName  = LPCTSTR(cstrPDFFileName);
            sDrwPDFFileName += sSheetName;
            sDrwPDFFileName += _T(".pdf");

            // check for file existence here because we use the filename supplied
            // by SW as the root and add the sheet names.  Thus, SW will not ask
            // the user if he wants to overwrite an existing file!
            if (FileExists(LPCTSTR(sDrwPDFFileName.m_str)))
                {
                CString             sErrMsg = ::CString(sDrwPDFFileName.m_str) +
                                                    _T(" already exists.\n") +
                                                    _T("Do you want to overwrite this file?");

                if (IDYES == MessageBox(NULL, LPCTSTR(sErrMsg),
                                PDF_WORKS_TITLE, MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2))
                    {
                    DMS_PDFWks->ClipBoardToPDFFile(sDrwPDFFileName);
                    }
                }

            if (S_OK != pQIDrawDoc->SheetNext())
                {
                CLEANUP;
                return;
                }
            }//for
        }
    else
        {
        // no need to check for file existence here because SW will have already
        // asked the user if he wants to overwrite an existing file

        // copy the current print preview image to the clipboard
        WindowToClipBoard(pSolidWorks);

        // do our magic for parts & asemblies
        DMS_PDFWks->ClipBoardToPDFFile(CComBSTR(cstrPDFFileName));
        }

    // get rid of PDF generator now
    DMS_PDFWks = NULL;


    // increment save counter
    g_nPDFSaveCount++;

    // Reset to previous resource handle
    CLEANUP;

    return;
}
// ---------------------------------------------------------------
void DllExport PDF_Configure(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);


    CComPtr<IDMS_PDFWorks>      DMS_PDFWks;
    CComBSTR                    sName(PDF_WORKS_TITLE);
    long                        bOK;
    HRESULT                     hres;

    hres = DMS_PDFWks.CoCreateInstance(__uuidof(DMS_PDFWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hres));

    if (SUCCEEDED(hres))
        {
        // load configuration from storage into m_PDF_Setup
        PDF_ConfigLoad();

        DMS_PDFWks->put_Icon((long ) LoadIcon(PDF_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DMS)));

        DMS_PDFWks->Configure(sName, &bOK, &m_PDF_Setup);

        DMS_PDFWks = NULL;

        // save m_PDF_Setup to storage
        PDF_ConfigSave();
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
// ---------------------------------------------------------------
// PDF_Help
// spawns WinHelp with hardcoded location to help file
void DllExport PDF_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\PDFWorks\\PDFWorks.hlp"
        , SW_NORMAL);
}
// ---------------------------------------------------------------
// 
// parameters
//      bShowDialog
//          true if dialog is to be shown
//          false if just want to check .ini file
// notes
//      updates g_bRegistered
void PDF_CheckRegistered
(
    bool            bShowDialog
)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);


    CComPtr<IDMS_Common>        DMS_Comm;
    CComBSTR                    sName(PDF_WORKS_TITLE),
                                sCode(PDF_WORKS_TITLE_CODE);
    HRESULT                     hres;

    hres = DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hres));

    if (SUCCEEDED(hres))
        {
        DMS_Comm->put_ProductName(sName);
        DMS_Comm->put_ProductCode(sCode);
        DMS_Comm->put_IniFileName(PDF_WORKS_INI_FILE_NAME);

        if (true == bShowDialog)
            {
            DMS_Comm->put_Icon((long ) LoadIcon(PDF_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DMS)));

            // only run dialog if asked
            // will store result to .ini file if successfully registered
            DMS_Comm->Register();
            }

        DMS_Comm->get_IsRegistered(&g_bRegistered);

        DMS_Comm = NULL;
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
// ---------------------------------------------------------------
// PDF_Register
// runs registration dialog in response to SW menu pick
void DllExport PDF_Register(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);


    PDF_CheckRegistered(true);


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
// ---------------------------------------------------------------
int DllExport PDF_RegisterUpdate(void)
{
    #if 0
    return 0;   // If you want the menu item to be unchecked and disabled (grayed out)
    return 1;   // If you want the menu item to be unchecked and enabled
    return 2;   // If you want the menu item to be checked and disabled (grayed out)
    return 3;   // If you want the menu item to be checked and enabled
    #endif

    return (TRUE == g_bRegistered) ? 0 : 1;
}
// ---------------------------------------------------------------
void DllExport PDF_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);

    CComPtr<IDMS_Common>        DMS_Comm;
    CComBSTR                    sName(PDF_WORKS_TITLE);
    HRESULT                     hres;

    hres = DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hres));

    if (SUCCEEDED(hres))
        {
        DMS_Comm->put_Commercial(false);
        DMS_Comm->put_ProductName(sName);
        DMS_Comm->put_Icon((long ) LoadIcon(PDF_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DMS)));

        DMS_Comm->About();

        DMS_Comm = NULL;
        }

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
// ---------------------------------------------------------------
void PDF_ConfigLoad(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource     = AfxGetResourceHandle();
    HINSTANCE                   SW_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);


    USES_CONVERSION;

    TCHAR                       TempUStr[25][_MAX_PATH];


    GetPrivateProfileString(_T("PageSetup"  ), _T("MarginTop"       ), _T("60"), TempUStr[ 0], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("MarginBottom"    ), _T("60"), TempUStr[ 1], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("MarginLeft"      ), _T("60"), TempUStr[ 2], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("MarginRight"     ), _T("60"), TempUStr[ 3], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("PaperSize"       ), _T("60"), TempUStr[ 4], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("PaperHeight"     ), _T("60"), TempUStr[ 5], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("PaperWidth"      ), _T("60"), TempUStr[ 6], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("Landscape"       ), _T("60"), TempUStr[ 7], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("ScaleToFit"      ), _T("60"), TempUStr[ 8], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("Scale"/*float*/  ), _T("60"), TempUStr[ 9], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("PageSetup"  ), _T("CentreOnPage"    ), _T("60"), TempUStr[10], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);

    m_PDF_Setup.PageSetup.MarginTop     = _ttoi(TempUStr[ 0]);
    m_PDF_Setup.PageSetup.MarginBottom  = _ttoi(TempUStr[ 1]);
    m_PDF_Setup.PageSetup.MarginLeft    = _ttoi(TempUStr[ 2]);
    m_PDF_Setup.PageSetup.MarginRight   = _ttoi(TempUStr[ 3]);
    m_PDF_Setup.PageSetup.PaperSize     = (PDF_PAPER_SIZE ) _ttoi(TempUStr[ 4]);
    m_PDF_Setup.PageSetup.PaperHeight   = _ttoi(TempUStr[ 5]);
    m_PDF_Setup.PageSetup.PaperWidth    = _ttoi(TempUStr[ 6]);
    m_PDF_Setup.PageSetup.Landscape     = _ttoi(TempUStr[ 7]);
    m_PDF_Setup.PageSetup.ScaleToFit    = _ttoi(TempUStr[ 8]);
    m_PDF_Setup.PageSetup.Scale         = _tcstod(TempUStr[ 9], _T('\0'));
    m_PDF_Setup.PageSetup.CentreOnPage  = _ttoi  (TempUStr[10]);


    GetPrivateProfileString(_T("Info"       ), _T("InfoSubject"     ), _T("60"), TempUStr[11], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("Info"       ), _T("InfoTitle"       ), _T("60"), TempUStr[12], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("Info"       ), _T("InfoCreator"     ), _T("60"), TempUStr[13], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("Info"       ), _T("InfoAuthor"      ), _T("60"), TempUStr[14], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("Info"       ), _T("InfoKeyWords"    ), _T("60"), TempUStr[15], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);

    CComBSTR                    sTemp11(TempUStr[11]),
                                sTemp12(TempUStr[12]),
                                sTemp13(TempUStr[13]),
                                sTemp14(TempUStr[14]),
                                sTemp15(TempUStr[15]);

    sTemp11.CopyTo(&m_PDF_Setup.Info.InfoSubject    );
    sTemp12.CopyTo(&m_PDF_Setup.Info.InfoTitle      );
    sTemp13.CopyTo(&m_PDF_Setup.Info.InfoCreator    );
    sTemp14.CopyTo(&m_PDF_Setup.Info.InfoAuthor     );
    sTemp15.CopyTo(&m_PDF_Setup.Info.InfoKeyWords   );


    GetPrivateProfileString(_T("ImageSetup" ), _T("JPGQuality"      ), _T("60"), TempUStr[16], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("ImageSetup" ), _T("ImageHeight"     ), _T("60"), TempUStr[17], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("ImageSetup" ), _T("ImageWidth"      ), _T("60"), TempUStr[18], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);
    GetPrivateProfileString(_T("ImageSetup" ), _T("Stretch"         ), _T("60"), TempUStr[19], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);

    m_PDF_Setup.ImageSetup.JPGQuality   = _ttoi(TempUStr[16]);
    m_PDF_Setup.ImageSetup.ImageHeight  = _ttoi(TempUStr[17]);
    m_PDF_Setup.ImageSetup.ImageWidth   = _ttoi(TempUStr[18]);
    m_PDF_Setup.ImageSetup.Stretch      = _ttoi(TempUStr[19]);


    GetPrivateProfileString(_T("Units"      ), _T("Units"           ), _T("60"), TempUStr[20], _MAX_PATH, PDF_WORKS_INI_FILE_NAME);

    m_PDF_Setup.Units = (PDF_UNITS ) _ttoi(TempUStr[20]);


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);
    return;
}
// ---------------------------------------------------------------
void PDF_ConfigSave(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource     = AfxGetResourceHandle();
    HINSTANCE                   SW_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);


    USES_CONVERSION;

    TCHAR                       TempUStr[25][_MAX_PATH];

    _stprintf(TempUStr[ 0], _T("%d"), m_PDF_Setup.PageSetup.MarginTop       );
    _stprintf(TempUStr[ 1], _T("%d"), m_PDF_Setup.PageSetup.MarginBottom    );
    _stprintf(TempUStr[ 2], _T("%d"), m_PDF_Setup.PageSetup.MarginLeft      );
    _stprintf(TempUStr[ 3], _T("%d"), m_PDF_Setup.PageSetup.MarginRight     );
    _stprintf(TempUStr[ 4], _T("%d"), m_PDF_Setup.PageSetup.PaperSize       );
    _stprintf(TempUStr[ 5], _T("%d"), m_PDF_Setup.PageSetup.PaperHeight     );
    _stprintf(TempUStr[ 6], _T("%d"), m_PDF_Setup.PageSetup.PaperWidth      );
    _stprintf(TempUStr[ 7], _T("%d"), m_PDF_Setup.PageSetup.Landscape       );
    _stprintf(TempUStr[ 8], _T("%d"), m_PDF_Setup.PageSetup.ScaleToFit      );
    _stprintf(TempUStr[ 9], _T("%f"), m_PDF_Setup.PageSetup.Scale           );
    _stprintf(TempUStr[10], _T("%d"), m_PDF_Setup.PageSetup.CentreOnPage    );

    WritePrivateProfileString(_T("PageSetup"    ), _T("MarginTop"   ), TempUStr[ 0], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("MarginBottom"), TempUStr[ 1], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("MarginLeft"  ), TempUStr[ 2], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("MarginRight" ), TempUStr[ 3], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("PaperSize"   ), TempUStr[ 4], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("PaperHeight" ), TempUStr[ 5], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("PaperWidth"  ), TempUStr[ 6], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("Landscape"   ), TempUStr[ 7], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("ScaleToFit"  ), TempUStr[ 8], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("Scale"       ), TempUStr[ 9], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("PageSetup"    ), _T("CentreOnPage"), TempUStr[10], PDF_WORKS_INI_FILE_NAME);


    _stprintf(TempUStr[11], _T("%s"), m_PDF_Setup.Info.InfoSubject  );
    _stprintf(TempUStr[12], _T("%s"), m_PDF_Setup.Info.InfoTitle    );
    _stprintf(TempUStr[13], _T("%s"), m_PDF_Setup.Info.InfoCreator  );
    _stprintf(TempUStr[14], _T("%s"), m_PDF_Setup.Info.InfoAuthor   );
    _stprintf(TempUStr[15], _T("%s"), m_PDF_Setup.Info.InfoKeyWords );

    WritePrivateProfileString(_T("Info"         ), _T("InfoSubject" ), TempUStr[11], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("Info"         ), _T("InfoTitle"   ), TempUStr[12], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("Info"         ), _T("InfoCreator" ), TempUStr[13], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("Info"         ), _T("InfoAuthor"  ), TempUStr[14], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("Info"         ), _T("InfoKeyWords"), TempUStr[15], PDF_WORKS_INI_FILE_NAME);


    _stprintf(TempUStr[16], _T("%d"), m_PDF_Setup.ImageSetup.JPGQuality );
    _stprintf(TempUStr[17], _T("%d"), m_PDF_Setup.ImageSetup.ImageHeight);
    _stprintf(TempUStr[18], _T("%d"), m_PDF_Setup.ImageSetup.ImageWidth );
    _stprintf(TempUStr[19], _T("%d"), m_PDF_Setup.ImageSetup.Stretch    );

    WritePrivateProfileString(_T("ImageSetup"   ), _T("JPGQuality"  ), TempUStr[16], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("ImageSetup"   ), _T("ImageHeight" ), TempUStr[17], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("ImageSetup"   ), _T("ImageWidth"  ), TempUStr[18], PDF_WORKS_INI_FILE_NAME);
    WritePrivateProfileString(_T("ImageSetup"   ), _T("Stretch"     ), TempUStr[19], PDF_WORKS_INI_FILE_NAME);


    _stprintf(TempUStr[20], _T("%d"), m_PDF_Setup.Units);

    WritePrivateProfileString(_T("Units"        ), _T("Units"       ), TempUStr[20], PDF_WORKS_INI_FILE_NAME);


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);
    return;
}
// ---------------------------------------------------------------
BOOL FileExists(LPCTSTR lpFileName)
{
    HANDLE                  hFile;
    WIN32_FIND_DATA         wfdFindFileData;

    hFile = FindFirstFile(lpFileName, &wfdFindFileData);

    if (INVALID_HANDLE_VALUE == hFile)
        {
        return FALSE;
        }
    else
        {
        FindClose(hFile);
        return TRUE;
        }
}
// ---------------------------------------------------------------
// Amyuni_SaveAsPDF
//
// SldWorks::AddFileSaveAsItem
// The format of the FileName argument is:

//     <FullPath > <FileName> <AccessType>

// where:
//
// FullPath is the file name with full path information,
// FileName is the file name and extension (without separator),
// AccessType is w or r
//
// TDE
// NB: the FileName argument appears to be all in upper case
void DllExport Amyuni_SaveAsPDF
(
    LPTSTR                      FileName,
    LPSLDWORKS                  pSolidWorks
)
{
    #define     CLEANUP     AfxSetResourceHandle(hSaveResource)

    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PDF_ResourceHandle = GetModuleHandle(PDF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PDF_ResourceHandle);

    // only proceed if registered or not exceeded trial limits
    if (g_nPDFSaveCount > MAX_UNREG_PDF_SAVES &&
        FALSE == g_bRegistered)
        {
        MessageBox(NULL, _T("Unregistered save limit reached."), PDF_WORKS_TITLE,
            MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

        CLEANUP;
        return;
        }


    // now generate the PDF file name based on the full path which was passed in
    CString                     cstrPDFFileName(FileName);

    // look for dot which delimits extension of full path
    int                         nDotPos = cstrPDFFileName.Find('.');
    if (-1 != nDotPos)
        {
        // get portion of string up to full path excluding extn
        cstrPDFFileName = cstrPDFFileName.Left(nDotPos);

        // add .pdf extension
        cstrPDFFileName += _T(".pdf");
        }
    else
        {
        // TODO     alert user & return
        return;
        }


    // file output options
    const int                   AMYUNI_NO_PROMPT            =   1;
    const int                   AMYUNI_USE_FILENAME         =   2;
    const int                   AMYUNI_CONCATENATE          =   4;
    const int                   AMYUNI_DISABLE_COMPRESSION  =   8;
    const int                   AMYUNI_EMBED_FONTS          =  16;
    const int                   AMYUNI_BROADCAST_MESSAGES   =  32;

    // paper orientations
    const int                   AMYUNI_PORTRAIT             =   1;
    const int                   AMYUNI_LANDSCAPE            =   2;

    // 72 pt = 2.54 cm
    const double                MM_PER_POINT                = 25.4 / 72.0;

    long                        nRetVal;
    int                         nPDFPaperIndex = m_PDF_Setup.PageSetup.PaperSize;


    if (true == Papers[nPDFPaperIndex].bSystem)
        {
        // one of the paper sizes supported by Windows
        PDFPrinter.SetPaperSize(Papers[nPDFPaperIndex].nWinPaper);
        }
    else if (Papers[nPDFPaperIndex].nHeight > 0 && Papers[nPDFPaperIndex].nWidth > 0)
        {
        // not a user defined type but one of the standard sizes

        // have to convert from points to tenths of mm
        double          nHeightTenthsMM = Papers[nPDFPaperIndex].nHeight * MM_PER_POINT * 10.0;
        double          nWidthTenthsMM  = Papers[nPDFPaperIndex].nWidth  * MM_PER_POINT * 10.0;

        PDFPrinter.SetPaperLength((long ) nHeightTenthsMM);
        PDFPrinter.SetPaperWidth ((long ) nWidthTenthsMM );
        }
    else
        {
        // fully user defined type

        // have to convert from points to tenths of mm
        double          nHeightTenthsMM = m_PDF_Setup.PageSetup.PaperHeight * MM_PER_POINT * 10.0;
        double          nWidthTenthsMM  = m_PDF_Setup.PageSetup.PaperWidth  * MM_PER_POINT * 10.0;

        PDFPrinter.SetPaperLength((long ) nHeightTenthsMM);
        PDFPrinter.SetPaperWidth ((long ) nWidthTenthsMM );
        }


    // have to convert from points to tenths of mm
    // note:
    //      that, in PDFWorks.ini, the margins are stored for PDF_Lib.
    //      Thus, for the Amyuni driver, the following mappings apply:
    //
    //      PDF_Lib       ----> Amyuni
    //      -------------------------------------
    //      top    margin       horizontal margin
    //      bottom margin       vertical   margin
    double          nHorizMarginTenthsMM = m_PDF_Setup.PageSetup.MarginTop    * MM_PER_POINT * 10.0;
    double          nVertMarginTenthsMM  = m_PDF_Setup.PageSetup.MarginBottom * MM_PER_POINT * 10.0;

    PDFPrinter.SetHorizontalMargin((short ) nHorizMarginTenthsMM);
    PDFPrinter.SetVerticalMargin  ((short ) nVertMarginTenthsMM );


    if (m_PDF_Setup.PageSetup.Landscape)
        {
        PDFPrinter.SetOrientation(AMYUNI_LANDSCAPE);
        }


    nRetVal = PDFPrinter.SetDefaultConfig ();
    nRetVal = PDFPrinter.SetDefaultPrinter();

    PDFPrinter.SetDefaultFileName (cstrPDFFileName);

    PDFPrinter.SetFileNameOptions(AMYUNI_NO_PROMPT | AMYUNI_USE_FILENAME);


    // print out here
    CComQIPtr<IModelDoc>        pActiveDoc;
    if (S_OK == pSolidWorks->get_IActiveDoc(&pActiveDoc))
        {
        pActiveDoc->PrintDirect();
        }

    PDFPrinter.SetFileNameOptions(0);

    nRetVal = PDFPrinter.RestoreDefaultPrinter();


    // increment save counter
    g_nPDFSaveCount++;

    // Reset to previous resource handle
    CLEANUP;

    return;
}

// --------------------------------
//  End of PDFWorks.cpp
// --------------------------------

