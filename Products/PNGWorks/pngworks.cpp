//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: PNGWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "PNGWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "resource.h"
#include <tchar.h>
#include <shlwapi.h>

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "DMS_JPGWks.h"
#include "DMS_JPGWks_i.c"

#include "SLogError.h"

#include "FreeImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------
// the application object
CPNGWorksApp*                           TheApplication = NULL;
static AFX_EXTENSION_MODULE             PNGWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("PNGWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(PNGWorksDLL, hInstance);

        CoInitialize(NULL);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(PNGWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("PNGWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        CoUninitialize();

        // Terminate the library before destructors are called
        AfxTermExtensionModule(PNGWorksDLL);
    }
    return 1;   // ok
}
//------------------------------------------------------------------------

// --------------------------------
//  connections to SolidWorks
// --------------------------------

//------------------------------------------------------------------------
#define DllExport __declspec( dllexport )
//------------------------------------------------------------------------

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
    TheApplication = new CPNGWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------

// document callbacks

//------------------------------------------------------------------------
// PNG_SaveAs
// uses DMS_JPGWorks to first save to a temporary JPG and then convert this
// to a PNG file
void DllExport PNG_SaveAs(LPTSTR FileName, LPSLDWORKS pSolidWorks)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PNG_ResourceHandle = GetModuleHandle(PNG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PNG_ResourceHandle);


    try
        {
        USES_CONVERSION;

        CComPtr <IModelDoc>         pModelDoc;
        CComPtr <IModelView>        pModelView;
        CComPtr<IDMS_JPGWorks>      pDMS_JPGWorks;
        long                        SW_Handle;

        CString                     sJPGFileName(FileName);
        CString                     sPNGFileName(FileName);
        TCHAR                       sTempStr     [MAX_PATH];
        TCHAR                       sTempPath    [MAX_PATH];
        TCHAR                       sTempFileName[MAX_PATH];

        void*                       dib = NULL;

        int                         pos;
        long                        nRetVal = 0;

        // strip off trailing file access letter
        sPNGFileName.Delete(sPNGFileName.GetLength() - 2, 2);

        pos = sPNGFileName.Find(_T('.'));
        if (-1 != pos)
            {
            sPNGFileName.Delete(pos, sPNGFileName.GetLength() - pos);
            }

        _tcscpy(sTempStr, LPCTSTR(sPNGFileName));

        // add PNG extension
        PathRenameExtension(sTempStr, _T(".png"));
        sPNGFileName = sTempStr;


        // work out where the temporary files are
        GetTempPath(sizeof(sTempPath) / sizeof(TCHAR), sTempPath);

        // form the output file name
        GetTempFileName(sTempPath, _T("PNGWorks"), 0, sTempFileName);

        // remove temp file created by GetTempFileName()
        DeleteFile(sTempFileName);

        // add JPG extension
        PathRenameExtension(sTempFileName, _T(".jpg"));
        sJPGFileName = sTempFileName;


        STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
        if (pModelDoc == NULL)
            {
            // no file loaded, so go home
            return;
            }

        // save to our temporary JPG file
        STEST_HR(pModelDoc->get_IActiveView(&pModelView));
        STEST_HR(pModelDoc->GraphicsRedraw2());
        STEST_HR(pModelView->GetViewHWnd(&SW_Handle));

        STEST_HR(pDMS_JPGWorks.CoCreateInstance(__uuidof(DMS_JPGWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(pDMS_JPGWorks->SaveAsJPEG(CComBSTR(sJPGFileName), SW_Handle));

        // load JPG into FreeImage
        dib = FreeImage_LoadJPEG(T2A(const_cast <TCHAR * > (LPCTSTR(sJPGFileName))), JPEG_ACCURATE);
        if (NULL != dib)
            {
            // dump out to our PNG file
            FreeImage_SavePNG(dib, T2A(const_cast <TCHAR * > (LPCTSTR(sPNGFileName))), PNG_DEFAULT);

            FreeImage_Free(dib);
            }

        // remove our temporary JPG file
        DeleteFile(sJPGFileName);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------
void DllExport PNG_Configure(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PNG_ResourceHandle = GetModuleHandle(PNG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PNG_ResourceHandle);


    try
        {
        CComPtr<IDMS_JPGWorks>      pDMS_JPGWorks;

        STEST_HR(pDMS_JPGWorks.CoCreateInstance(__uuidof(DMS_JPGWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(pDMS_JPGWorks->Configure());
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------
void DllExport PNG_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\PNGWorks\\PNGWks.hlp"
        , SW_NORMAL);

    return;
}
//------------------------------------------------------------------------
void DllExport PNG_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   PNG_ResourceHandle = GetModuleHandle(PNG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(PNG_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(false));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(PNG_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(PNG_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_PNG_WORKS))));

        STEST_HR(DMS_Comm->About());

        DMS_Comm = NULL;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//------------------------------------------------------------------------

// --------------------------------
//  End of PNGWorks.cpp
// --------------------------------
