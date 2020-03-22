//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: GhostWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "GhostWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "Resource.h"
#include <tchar.h>

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "SLogError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
//------------------------------------------------------------------------
CGhostWorksApp*                         TheApplication = NULL;
static AFX_EXTENSION_MODULE             GhostWorksDLL = { NULL, NULL };
//------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("GhostWorks.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(GhostWorksDLL, hInstance);

        CoInitialize(NULL);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(GhostWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("GhostWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        CoUninitialize();

        // Terminate the library before destructors are called
        AfxTermExtensionModule(GhostWorksDLL);
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
    TheApplication = new CGhostWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // connected successfully
    return 1;
}
//------------------------------------------------------------------------

// document callbacks
void DllExport MenuItemCB(void)
{
    return;
}
//------------------------------------------------------------------------
void DllExport Ghost_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\GhostWorks\\GhostWks.hlp"
        , SW_NORMAL);
}
//------------------------------------------------------------------------
void DllExport Ghost_About(void)
{
    // Save the current resource handle
    HINSTANCE                   hSaveResource = AfxGetResourceHandle();

    HINSTANCE                   Ghost_ResourceHandle = GetModuleHandle(GHOST_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(Ghost_ResourceHandle);

    try
        {
        CComPtr<IDMS_Common>        DMS_Comm;

        STEST_HR(DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER));

        STEST_HR(DMS_Comm->put_Commercial(false));
        STEST_HR(DMS_Comm->put_ProductName(CComBSTR(GHOST_WORKS_TITLE)));
        STEST_HR(DMS_Comm->put_Icon((long ) LoadIcon(Ghost_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_GHOST_WKS))));

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
//  End of GhostWorks.cpp
// --------------------------------
