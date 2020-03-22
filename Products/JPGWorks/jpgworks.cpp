//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: JPGWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "JPGWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "resource.h"
#include <tchar.h>

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "DMS_JPGWks.h"
#include "DMS_JPGWks_i.c"

#include "SLogError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------
// the application object
CJPGWorksApp*                       TheApplication = NULL;
static AFX_EXTENSION_MODULE         JPGWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("JPGWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(JPGWorksDLL, hInstance);

        CoInitialize(NULL);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(JPGWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("JPGWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        CoUninitialize();

        // Terminate the library before destructors are called
        AfxTermExtensionModule(JPGWorksDLL);
    }
    return 1;   // ok
}
//------------------------------------------------------------------------

// --------------------------------
//  connections to SolidWorks
// --------------------------------

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
    TheApplication = new CJPGWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------

// document callbacks

//------------------------------------------------------------------------
void DllExport JPG_SaveAs(LPTSTR FileName, LPSLDWORKS pSolidWorks)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   JPG_ResourceHandle = GetModuleHandle(JPG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(JPG_ResourceHandle);


    try
        {
        USES_CONVERSION;

        CComPtr <IModelDoc>         pModelDoc;
        CComPtr <IModelView>        pModelView;
        CComPtr<IDMS_JPGWorks>      pDMS_JPGWorks;
        int                         pos;
        long                        SW_Handle;

        CString                     sFileName(FileName);

        // strip off trailing file access letter
        sFileName.Delete(sFileName.GetLength() - 2, 2);

        pos = sFileName.Find(_T('.'));
        if (-1 != pos)
            {
            sFileName.Delete(pos, sFileName.GetLength() - pos);
            }

        // add JPG extension
        sFileName += _T(".jpg");

        STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
        if (pModelDoc == NULL)
            {
            // no file loaded, so go home
            return;
            }

        STEST_HR(pModelDoc->get_IActiveView(&pModelView));
        STEST_HR(pModelDoc->GraphicsRedraw2());
        STEST_HR(pModelView->GetViewHWnd(&SW_Handle));

        STEST_HR(pDMS_JPGWorks.CoCreateInstance(__uuidof(DMS_JPGWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(pDMS_JPGWorks->SaveAsJPEG(CComBSTR(sFileName), SW_Handle));
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
void DllExport JPG_Configure(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   JPG_ResourceHandle = GetModuleHandle(JPG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(JPG_ResourceHandle);


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
void DllExport JPG_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\JPGWorks\\JPGWks.hlp"
        , SW_NORMAL);

    return;
}
//------------------------------------------------------------------------
void DllExport JPG_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   JPG_ResourceHandle = GetModuleHandle(JPG_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(JPG_ResourceHandle);


    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(false));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(JPG_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(JPG_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_JPG_WORKS))));

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
//  End of JPGWorks.cpp
// --------------------------------
