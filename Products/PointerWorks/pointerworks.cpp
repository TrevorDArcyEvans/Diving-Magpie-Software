// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: PointerWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#include "PointerWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "About.h"
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CPointerWorksApp* TheApplication = NULL;

static AFX_EXTENSION_MODULE PointerWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("PointerWorks.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(PointerWorksDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(PointerWorksDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("PointerWorks.DLL Terminating!\n");

		// shut down the sample application
		TheApplication->TerminateApplication();
		delete TheApplication;

		// Terminate the library before destructors are called
		AfxTermExtensionModule(PointerWorksDLL);
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
	TheApplication = new CPointerWorksApp(pSldWorks);
	if (!TheApplication->StartApplication())
		return 0;

	// connected successfully
	return 1;
}

// document callbacks

void DllExport PW_About(void)
{
    CAbout      dlg;

    dlg.DoModal();

	return;
}

// --------------------------------
//  End of PointerWorks.cpp
// --------------------------------
