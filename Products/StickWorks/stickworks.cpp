//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: StickWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1

#include <mmsystem.h>
#include "Configure.h"
#include "StickWorks.h"
#include "SldWorks.h"
#include "timer.h"
#include "JoyPanel.h"
#include "ExampleApp.h"
#include <tchar.h>

#include <atlbase.h>

#include "DMS_Comm.h"
#include "DMS_Comm_i.c"

#include "DMS_StkWks.h"
#include "DMS_StkWks_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// the application object
CStickWorksApp*                 TheApplication  = NULL;
CDynLinkLibrary*                pDynLinkLibrary = NULL;

//---------------------------------------------------------------------------
static AFX_EXTENSION_MODULE     StickWorksDLL = { NULL, NULL };
//---------------------------------------------------------------------------
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("StickWorks.DLL Initializing!\n");

        // Extension DLL one-time initialization
        AfxInitExtensionModule(StickWorksDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(StickWorksDLL);
        pDynLinkLibrary = new CDynLinkLibrary(StickWorksDLL);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        KillTimer(NULL, g_uJoyTimerID       );
        KillTimer(NULL, g_uRegTimerID       );
        KillTimer(NULL, g_uJoyPanelTimerID  );

        TRACE0("StickWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        // Terminate the library before destructors are called
        delete pDynLinkLibrary;
        AfxTermExtensionModule(StickWorksDLL);
    }
    return 1;   // ok
}

// --------------------------------
//  connections to SolidWorks
// --------------------------------

#define DllExport __declspec( dllexport )
//---------------------------------------------------------------------------
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
    TheApplication = new CStickWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;


    TCHAR   TempUStr[_MAX_PATH];

    // read sensitivity & threshold from ini file
    GetPrivateProfileString(
        STICK_WORKS_INI_SECTION_CONFIG,
        STICK_WORKS_INI_KEY_THRESHOLD,
        _T("10"), // points to default string
        TempUStr, // points to destination buffer
        _MAX_PATH,        // size of destination buffer
        STICK_WORKS_INI_FILE_NAME);
    g_nThreshold = _ttoi(TempUStr);

    GetPrivateProfileString(
        STICK_WORKS_INI_SECTION_CONFIG,
        STICK_WORKS_INI_KEY_SENSITIVITY,
        _T("50"), // points to default string
        TempUStr, // points to destination buffer
        _MAX_PATH,        // size of destination buffer
        STICK_WORKS_INI_FILE_NAME);
    g_nSensitivity = _ttoi(TempUStr);

    SetPriorityClass (GetCurrentProcess(), IDLE_PRIORITY_CLASS);
    SetThreadPriority(GetCurrentThread (), THREAD_PRIORITY_IDLE);

    joyGetDevCaps(JOYSTICKID1, &g_jcJoyCaps, sizeof(JOYCAPS));

    g_uJoyTimerID = SetTimer(NULL, 0, 100, SW_JoyTimer);
    g_uRegTimerID = SetTimer(NULL, 0,
        //15*1000, // time-out value = 15 seconds
        15*60*1000, // time-out value = 15 minutes
        SW_RegTimer);
    g_uJoyPanelTimerID = SetTimer(NULL, 0, 1500, SW_JoyControlPanelTimer);

    // connected successfully
    return 1;
}
//---------------------------------------------------------------------------
void DllExport SW_Config(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(SW_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CConfigure      dlg;

    //dlg.DoModal();


    try
        {
        HRESULT                     hr;
        hr = TheApplication->get_DMS_StkWks()->Configure();
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//---------------------------------------------------------------------------
void DllExport SW_Calibrate(void)
{
    WinExec("control joy.cpl", SW_NORMAL);
}
//---------------------------------------------------------------------------
void DllExport SW_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\StickWorks\\StkWorks.hlp"
        , SW_NORMAL);
}
//---------------------------------------------------------------------------
void DllExport SW_Register(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(SW_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);


    int                         nTempIsReg = false;

    try
        {
        HRESULT                     hr;
        hr = TheApplication->get_DMS_Comm()->Register();
        hr = TheApplication->get_DMS_Comm()->get_IsRegistered(&nTempIsReg);
        }
    catch (...)
        {
        }
    g_bRegistered = nTempIsReg;


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
//---------------------------------------------------------------------------
int DllExport SW_RegisterUpdate(void)
{
#if 0
return 0;   // If you want the menu item to be unchecked and disabled (grayed out)
return 1;   // If you want the menu item to be unchecked and enabled
return 2;   // If you want the menu item to be checked and disabled (grayed out)
return 3;   // If you want the menu item to be checked and enabled
#endif

    return g_bRegistered == true ? 0 : 1;
}
//---------------------------------------------------------------------------
void DllExport SW_About(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(SW_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);


    try
        {
        HRESULT                     hr;
        hr = TheApplication->get_DMS_Comm()->About();
        }
    catch (...)
        {
        }


    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}

// --------------------------------
//  End of StickWorks.cpp
// --------------------------------
