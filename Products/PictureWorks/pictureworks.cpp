//$c01 DMH 08/20/98  Added fix for Serialization option (sub by JPS per DMH)
// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: PictureWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "About.h"
#include "PictureWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CPictureWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE PictureWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("PictureWorks.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(PictureWorksDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(PictureWorksDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("PictureWorks.DLL Terminating!\n");

		// shut down the sample application
		TheApplication->TerminateApplication();
		delete TheApplication;

		// Terminate the library before destructors are called
		AfxTermExtensionModule(PictureWorksDLL);
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
	TheApplication = new CPictureWorksApp(pSldWorks);
	if (!TheApplication->StartApplication())
		return 0;

	// connected successfully
	return 1;
}

// document callbacks

void DllExport PW_Copy(void)
{
    LPSLDWORKS pSldWorks = TheApplication->GetSWApp(); 

    HDC         hdc, hdcMem;
    HBITMAP     hBitmap;
    HWND        hwnd;

    // update active doc
    LPMODELDOC      pActiveDoc = NULL;
    if (S_OK != pSldWorks->get_IActiveDoc(&pActiveDoc) ||
        NULL == pActiveDoc )
        {
		return;
        }

    // update active view
	LPMODELVIEW pModelView = NULL;
    if (S_OK != pActiveDoc->get_IActiveView(&pModelView) ||
        NULL == pModelView)
        {
	    pActiveDoc->Release();
		return;
        }

    // get handle to window
    pModelView->GetViewHWnd((long *) &hwnd);
    if (NULL == hwnd)
        {
        goto _CLEAN_UP;
        }

	pModelView->Release();
    pActiveDoc->Release();

    hdc = GetWindowDC(hwnd);
    if (NULL == hdc)
        {
        goto _CLEAN_UP;
        }

    hdcMem = CreateCompatibleDC(hdc);
    if (NULL == hdcMem)
        {
        goto _CLEAN_UP;
        }

    RECT        Rect;
    GetClientRect(hwnd, &Rect);

    hBitmap = CreateCompatibleBitmap(hdc,
        abs(Rect.right ),
        abs(Rect.bottom));
    if (NULL == hBitmap)
        {
        goto _CLEAN_UP;
        }

    SelectObject(hdcMem, hBitmap);
    StretchBlt(hdcMem,
        0, 0,
        abs(Rect.right ),
        abs(Rect.bottom),
        hdc,
        0, 0,
        abs(Rect.right ),
        abs(Rect.bottom),
        SRCCOPY);

    OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    _CLEAN_UP   :
        ;

    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdc);

    return;
}
// --------------------------------
void DllExport PW_Help(void)
{
    WinExec("winhlp32 C:\\Program Files\\SolidPartners\\PictureWorks\\PictWks.hlp"
        , SW_NORMAL);
}
// --------------------------------
void DllExport PW_About(void)
{
    // Save the current resource handle                                 
    HINSTANCE hSaveResource = AfxGetResourceHandle();                   
                                                                                    
    HINSTANCE SW_ResourceHandle = GetModuleHandle(PW_DLL_NAME);         
                                                                                    
    // Switch to the Application resources                              
    AfxSetResourceHandle(SW_ResourceHandle);

    CAbout      dlg;

    dlg.DoModal();

    // Reset to previous resource handle        
    AfxSetResourceHandle(hSaveResource);        
                                                            
	return;
}
// --------------------------------
//  End of PictureWorks.cpp
// --------------------------------
