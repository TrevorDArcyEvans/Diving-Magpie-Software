//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: MenuWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define MAIN    1

#include "MenuWorks.h"
#include "SldWorks.h"
#include "About.h"
#include "ExampleApp.h"
#include "init.h"
#include "register.h"
#include "WinUtil.h"
#include "utils.h"

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CMenuWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE MenuWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Extension DLL one-time initialization
        AfxInitExtensionModule(MenuWorksDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(MenuWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        // Terminate the library before destructors are called
        AfxTermExtensionModule(MenuWorksDLL);
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
    int i = 0;

    // this function should be called once per session
    if ( TheApplication != NULL )
    {
        ASSERT ( FALSE );
        return 0;
    }

    // start the application
    TheApplication = new CMenuWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    // initialise MenuWorks
    MW_Init();

    // connected successfully
    return 1;
}

// document callbacks

void DoProgramExecute(_TCHAR *ProgName)
{
    STARTUPINFO             StartupInfo;
    PROCESS_INFORMATION     ProcessInformation;

    StartupInfo.cb              = sizeof(STARTUPINFO);
    StartupInfo.lpReserved      = NULL;
    StartupInfo.lpDesktop       = NULL;
    StartupInfo.lpTitle         = NULL;
    StartupInfo.dwX             = 0;
    StartupInfo.dwY             = 0;
    StartupInfo.dwXSize         = 0;
    StartupInfo.dwYSize         = 0;
    StartupInfo.dwXCountChars   = 0;
    StartupInfo.dwYCountChars   = 0;
    StartupInfo.dwFillAttribute = 0;
    StartupInfo.dwFlags         = STARTF_USESTDHANDLES;
    StartupInfo.wShowWindow     = 0; //SW_SHOWNORMAL
    StartupInfo.cbReserved2     = 0;
    StartupInfo.lpReserved2     = NULL;
    StartupInfo.hStdInput       = NULL;
    StartupInfo.hStdOutput      = NULL;
    StartupInfo.hStdError       = NULL;

    CreateProcess(
        NULL,  // pointer to name of executable module
        ProgName,  // pointer to command line string
        NULL,  // process security attributes
        NULL,   // thread security attributes
        TRUE,  // handle inheritance flag
        CREATE_DEFAULT_ERROR_MODE, // creation flags
        NULL,  // pointer to new environment block
        NULL,   // pointer to current directory name
        &StartupInfo,  // pointer to STARTUPINFO
        &ProcessInformation  // pointer to PROCESS_INFORMATION
        );

    return;
}

void DllExport ProgExec0(void)
{
    DoProgramExecute(MenuItem[0].ProgName);
    return;
}

void DllExport ProgExec1(void)
{
    DoProgramExecute(MenuItem[1].ProgName);
    return;
}

void DllExport ProgExec2(void)
{
    DoProgramExecute(MenuItem[2].ProgName);
    return;
}

void DllExport ProgExec3(void)
{
    DoProgramExecute(MenuItem[3].ProgName);
    return;
}

void DllExport ProgExec4(void)
{
    DoProgramExecute(MenuItem[4].ProgName);
    return;
}

void DllExport ProgExec5(void)
{
    DoProgramExecute(MenuItem[5].ProgName);
    return;
}

void DllExport ProgExec6(void)
{
    DoProgramExecute(MenuItem[6].ProgName);
    return;
}

void DllExport ProgExec7(void)
{
    DoProgramExecute(MenuItem[7].ProgName);
    return;
}

void DllExport ProgExec8(void)
{
    DoProgramExecute(MenuItem[8].ProgName);
    return;
}

void DllExport ProgExec9(void)
{
    DoProgramExecute(MenuItem[9].ProgName);
    return;
}

void DllExport MW_Config(void)
{
WinExec("C:\\Program Files\\SolidPartners\\MenuWorks\\MenuWorksEditor.exe"
        , SW_NORMAL);

}

void DllExport MW_About(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(MW_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CAbout    dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}

void DllExport MW_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\MenuWorks\\MenuWks.hlp"
        , SW_NORMAL);

    return;
}

void DllExport MW_Register(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(MW_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CRegister   dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}

int DllExport MW_RegisterUpdate(void)
{
#if 0
return 0;      // If you want the menu item to be unchecked and disabled (grayed out)
return 1;      // If you want the menu item to be unchecked and enabled
return 2;      // If you want the menu item to be checked and disabled (grayed out)
return 3;     // If you want the menu item to be checked and enabled
#endif

    return g_bRegistered == true ? 0 : 1;
}

// --------------------------------
//  End of MenuWorks.cpp
// --------------------------------
