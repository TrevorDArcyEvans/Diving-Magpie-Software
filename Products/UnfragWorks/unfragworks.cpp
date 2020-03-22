//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: UnfragWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1

#include "About.h"
#include "ExampleApp.h"
#include "UnfragWorks.h"
#include "register.h"
#include "SldWorks.h"
#include "WinUtil.h"
#include "utils.h"

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CUnfragWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE UnfragWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("UnfragWorks.DLL Initializing!\n");

        // Extension DLL one-time initialization
        AfxInitExtensionModule(UnfragWorksDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(UnfragWorksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("UnfragWorks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        // Terminate the library before destructors are called
        AfxTermExtensionModule(UnfragWorksDLL);
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
    TheApplication = new CUnfragWorksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    g_bRegistered = false;
    g_nTimesUsed = 0;

    // set time out value to 10 secs
    g_nTimeOut = 10;

    _TCHAR      CodeUStr[_MAX_PATH];
    char        CodeStr [_MAX_PATH];

    GetPrivateProfileString(
            UNFRAG_WORKS_INI_FILE_SECTION,
            UNFRAG_WORKS_INI_FILE_KEY,
            _T("SolidPartners"), // points to default string
            CodeUStr, // points to destination buffer
            _MAX_PATH,        // size of destination buffer
            UNFRAG_WORKS_INI_FILE_NAME);

    wu_strcpy(CodeStr, ::CString(CodeUStr));

    char        MachineID[_MAX_PATH];
    GetMachineID(MachineID);

    if (CheckCode(MachineID, (char *) UNFRAG_WORKS_TITLE_CODE, CodeStr) == true)
        {
        // disable menu item
        g_bRegistered = true;
        }

    // connected successfully
    return 1;
}

// document callbacks

void DoProgramExecute(_TCHAR *CmdLine)
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
    StartupInfo.dwFlags         = 0;
    StartupInfo.wShowWindow     = SW_HIDE;
    StartupInfo.cbReserved2     = 0;
    StartupInfo.lpReserved2     = NULL;
    StartupInfo.hStdInput       = NULL;
    StartupInfo.hStdOutput      = NULL;
    StartupInfo.hStdError       = NULL;

    if (TRUE == CreateProcess(
                    NULL,  // pointer to name of executable module
                    CmdLine,  // pointer to command line string
                    NULL,  // process security attributes
                    NULL,   // thread security attributes
                    FALSE, // handle inheritance flag
                    DETACHED_PROCESS | CREATE_DEFAULT_ERROR_MODE, // creation flags
                    NULL,  // pointer to new environment block
                    NULL,   // pointer to current directory name
                    &StartupInfo,  // pointer to STARTUPINFO
                    &ProcessInformation  // pointer to PROCESS_INFORMATION
                    ))
        {
        // run process as detached
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        }

    return;
}

void DllExport UW_About(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(_T(UW_DLL_NAME));

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CAbout  dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}

void DllExport UW_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\UnfragWorks\\UnfrgWks.hlp"
        , SW_NORMAL);

    return;
}

void DllExport UW_Register(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(_T(UW_DLL_NAME));

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CRegister   dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}

int DllExport UW_RegisterUpdate(void)
{
#if 0
return 0;   // If you want the menu item to be unchecked and disabled (grayed out)
return 1;   // If you want the menu item to be unchecked and enabled
return 2;   // If you want the menu item to be checked and disabled (grayed out)
return 3;   // If you want the menu item to be checked and enabled
#endif

    return g_bRegistered == true ? 0 : 1;
}

void DllExport UW_Config(void)
{
    AfxMessageBox(_T("UW_Config"));
}

// --------------------------------
//  End of UnfragWorks.cpp
// --------------------------------
