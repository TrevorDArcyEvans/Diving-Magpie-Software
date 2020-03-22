//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: WinWks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1


#include "WinWks.h"
#include "about.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "register.h"
#include "resource.h"
#include "WinUtil.h"
#include "utils.h"
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CWinWksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE WinWksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("WinWks.DLL Initializing!\n");

        // Extension DLL one-time initialization
        AfxInitExtensionModule(WinWksDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(WinWksDLL);

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("WinWks.DLL Terminating!\n");

        // shut down the sample application
        TheApplication->TerminateApplication();
        delete TheApplication;

        // Terminate the library before destructors are called
        AfxTermExtensionModule(WinWksDLL);
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
    TheApplication = new CWinWksApp(pSldWorks);
    if (!TheApplication->StartApplication())
        return 0;

    g_bRegistered = false;
    g_nTimesUsed = 0;

    _TCHAR      CodeUStr[_MAX_PATH];
    char        CodeStr [_MAX_PATH];

    GetPrivateProfileString(
            WINDOW_WORKS_INI_FILE_SECTION,
            WINDOW_WORKS_INI_FILE_KEY,
            _T("SolidPartners"), // points to default string
            CodeUStr, // points to destination buffer
            _MAX_PATH,        // size of destination buffer
            WINDOW_WORKS_INI_FILE_NAME);

    wu_strcpy(CodeStr, ::CString(CodeUStr));

    char    MachineID[_MAX_PATH];
    strcpy(MachineID, GetMachineID());

    if (CheckCode(MachineID, (char *) WINDOW_WORKS_TITLE_CODE, CodeStr) == true)
        {
        // disable menu item
        g_bRegistered = true;
        }

    // connected successfully
    return 1;
}

// document callbacks
// --------------------------------
void DllExport WW_CloseAll(void)
{
#define     WW_BCB_DLL_NAME         _T("WinWks.dll")

typedef bool (WINAPI * _WW_CLOSE_ALL)();

_WW_CLOSE_ALL       lpfnWW_CloseAll = NULL;
HINSTANCE           hWWLib = NULL;

hWWLib = LoadLibrary(WW_BCB_DLL_NAME);
if (NULL == hWWLib)
    {
    TCHAR       cTempStr[MAX_PATH];

    _stprintf(cTempStr, _T("Could not load %s"), WW_BCB_DLL_NAME);
    MessageBox(NULL, cTempStr, WINDOW_WORKS_TITLE,
        MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
    return;
    }

lpfnWW_CloseAll = (_WW_CLOSE_ALL ) GetProcAddress(hWWLib, "WW_CloseAll");
if (NULL != lpfnWW_CloseAll)
    {
    if (g_nTimesUsed++ <= WW_MAX_UNREG  ||
        TRUE == g_bRegistered           )
        {
        bool bRet = lpfnWW_CloseAll();
        }

    if ((WW_MAX_UNREG + 1) == g_nTimesUsed  &&
        FALSE == g_bRegistered              )
        {
        TCHAR        cstrCmdLine[_MAX_PATH];

        _stprintf(cstrCmdLine, _T("WindowWorks -\nSorry, already used %d times."),
            WW_MAX_UNREG);
        AfxMessageBox(cstrCmdLine);
        }
    }

FreeLibrary(hWWLib);
return;
}
// --------------------------------
void DllExport WW_SaveAll(void)
{
if (g_nTimesUsed++ <= WW_MAX_UNREG  ||
    TRUE == g_bRegistered           )
    {
    LPENUMDOCUMENTS         pDocEnum = NULL;
    LPMODELDOC              pModelDoc = NULL;
    HRESULT                 hres;

    hres = TheApplication->GetSWApp()->EnumDocuments(&pDocEnum);
    if (NULL == pDocEnum || S_OK != hres)
        {
        return;
        }

    while (S_OK == pDocEnum->Next(1, &pModelDoc, NULL))
        {
        long            retval;
        VARIANT_BOOL    bRet;

        // only save if needed, should really check read only flag too
        hres = pModelDoc->GetSaveFlag(&bRet);
        if (TRUE == bRet && S_OK == hres)
            {
            pModelDoc->Save2(TRUE, &retval);
            }

        pModelDoc->Release();
        pModelDoc = NULL;
        }

    if (NULL != pDocEnum)
        {
        pDocEnum->Release();
        }
    }

if ((WW_MAX_UNREG + 1) == g_nTimesUsed  &&
    FALSE == g_bRegistered              )
    {
    TCHAR        cstrCmdLine[_MAX_PATH];

    _stprintf(cstrCmdLine, _T("WindowWorks -\nSorry, already used %d times."),
        WW_MAX_UNREG);
    AfxMessageBox(cstrCmdLine);
    }

return;
}
// --------------------------------
void DllExport WW_Register(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(_T(WW_DLL_NAME));

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CRegister   dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}
// --------------------------------
int WW_RegisterUpdate(void)
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
void DllExport WW_Help(void)
{
WinExec("winhlp32 C:\\Program Files\\SolidPartners\\WindowWorks\\WinWks.hlp"
        , SW_NORMAL);

return;
}
// --------------------------------
void DllExport WW_About(void)
{
    // Save the current resource handle
    HINSTANCE hSaveResource = AfxGetResourceHandle();

    HINSTANCE SW_ResourceHandle = GetModuleHandle(_T(WW_DLL_NAME));

    // Switch to the Application resources
    AfxSetResourceHandle(SW_ResourceHandle);

    CAbout    dlg;

    dlg.DoModal();

    // Reset to previous resource handle
    AfxSetResourceHandle(hSaveResource);

    return;
}


// --------------------------------
//  End of WinWks.cpp
// --------------------------------
