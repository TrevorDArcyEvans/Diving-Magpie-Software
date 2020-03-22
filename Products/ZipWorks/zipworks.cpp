// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ZipWorks.cpp
//  Description: This defines the interface to SolidWorks and the
//               initialization routines for the DLL.
//
// -------------------------------------------------------------------

// pre-compiled headers
#include "stdafx.h"

// MFC includes
#include <afxdllx.h>

#define     MAIN        1

#include "ZipWorks.h"
#include "SldWorks.h"
#include "ExampleApp.h"
#include "About.h"
#include "FileName.h"
#include "Register.h"
#include "WinUtil.h"
#include "utils.h"
#include <tchar.h>

#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// the application object
CZipWorksApp* TheApplication = NULL;

// zip file name
CString		cstrFileName;

// true if application registered
bool		bZW_Registered;

static AFX_EXTENSION_MODULE ZipWorksDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("ZipWorks.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(ZipWorksDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(ZipWorksDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("ZipWorks.DLL Terminating!\n");

		// shut down the sample application
		TheApplication->TerminateApplication();
		delete TheApplication;

		// Terminate the library before destructors are called
		AfxTermExtensionModule(ZipWorksDLL);
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
	TheApplication = new CZipWorksApp(pSldWorks);
	if (!TheApplication->StartApplication())
		return 0;

    // initially set addin to unregistered
    g_bRegistered = false;

    TCHAR   CodeUStr[_MAX_PATH];
    char    CodeStr [_MAX_PATH];

    GetPrivateProfileString( 
            ZIP_WORKS_INI_FILE_SECTION,
            ZIP_WORKS_INI_FILE_KEY,
            _T("SolidPartners"), // points to default string 
            CodeUStr, // points to destination buffer 
            100,        // size of destination buffer 
            ZIP_WORKS_INI_FILE_NAME); 

    wu_strcpy(CodeStr, ::CString(CodeUStr));

    char    MachineID[_MAX_PATH];
    strcpy(MachineID, GetMachineID());

    if (CheckCode(MachineID, (char *) LPCTSTR(ZIP_WORKS_TITLE_CODE), CodeStr) == true)
        {
        // disable menu item & set running flag
        g_bRegistered = true;
        g_bRunning = true;
        }

    // get SW date code for 
    TheApplication->m_pSldWorks->DateCode(&g_lDateCode);

	// connected successfully
	return 1;
}

// document callbacks

void DllExport ZW_About(void)
{
	CAbout	dlg;

	dlg.DoModal();

    return;
}

void DllExport ZW_Help(void)
{
    #ifdef _UNICODE
    #define     ZW_HELP_CMD     "winhlp32 C:\\Program Files\\SolidPartners\\ZipWorks\\ZipWorks.hlp"
    #else
    #define     ZW_HELP_CMD     "winhlp32 C:\\Program Files\\SolidPartners\\ZipWorks\\ZipWorks.hlp"
    #endif
    
    WinExec(ZW_HELP_CMD, SW_NORMAL);

	return;
}

void DllExport ZW_FileName(void)
{
	CFileName dlg;

	dlg.m_FileName = cstrFileName;

	if (IDOK == dlg.DoModal())
		{
		cstrFileName = dlg.m_FileName;
		}

    return;
}

void DllExport ZW_Options(void)
{
    return;
}

void DllExport ZW_FileAdd(void)
{
START:
	
	// if there is a file name
	if (!cstrFileName.IsEmpty())
		{
		// refresh active document
		if (S_OK == TheApplication->m_pSldWorks->get_IActiveDoc(&TheApplication->m_pActiveDoc))
			{
			BSTR	FileName;
			if (S_OK == TheApplication->m_pActiveDoc->GetPathName(&FileName))
				{
				// save current view mode
				VARIANT_BOOL			retval;
				LPMODELVIEW				ActiveView;
				swViewDisplayType_e		OldView = swIsViewShaded;
				
				/*
				swIsViewSectioned
				swIsViewPerspective
				swIsViewShaded
				swIsViewWireFrame
				swIsViewHiddenLinesRemoved
				swIsViewHiddenInGrey
				swIsViewCurvature
				*/

				TheApplication->m_pActiveDoc->get_IActiveView(&ActiveView);

				ActiveView->GetDisplayState(swIsViewSectioned, &retval);
				OldView = (true == retval) ? swIsViewSectioned : OldView;

				ActiveView->GetDisplayState(swIsViewPerspective, &retval);
				OldView = (true == retval) ? swIsViewPerspective : OldView;

				ActiveView->GetDisplayState(swIsViewShaded, &retval);
				OldView = (true == retval) ? swIsViewShaded : OldView;

				ActiveView->GetDisplayState(swIsViewWireFrame, &retval);
				OldView = (true == retval) ? swIsViewWireFrame : OldView;

				ActiveView->GetDisplayState(swIsViewHiddenLinesRemoved, &retval);
				OldView = (true == retval) ? swIsViewHiddenLinesRemoved : OldView;

				ActiveView->GetDisplayState(swIsViewHiddenInGrey, &retval);
				OldView = (true == retval) ? swIsViewHiddenInGrey : OldView;

				ActiveView->GetDisplayState(swIsViewCurvature, &retval);
				OldView = (true == retval) ? swIsViewCurvature : OldView;

				// switch to hidden line removed
				TheApplication->m_pActiveDoc->ViewDisplayHiddenremoved();

				// save file
				TheApplication->m_pActiveDoc->Save();

				// add to zip
				CString		SysCommand = "start zip.exe \"" + cstrFileName + "\" \"" + FileName + "\"";

				char *TempStr = new char[SysCommand.GetLength() + 10];

				for (int i = 0; i < SysCommand.GetLength(); i++)
				{
				TempStr[i] = SysCommand[i];	
				}
				TempStr[SysCommand.GetLength()] = '\0';

				system(TempStr);

				delete TempStr;
				
				// restore old view
				switch (OldView)
					{
					case	swIsViewShaded					:	TheApplication->m_pActiveDoc->ViewDisplayShaded			();	break;
					case	swIsViewWireFrame				:	TheApplication->m_pActiveDoc->ViewDisplayWireframe		();	break;
					case	swIsViewHiddenLinesRemoved		:	TheApplication->m_pActiveDoc->ViewDisplayHiddenremoved	();	break;
					case	swIsViewHiddenInGrey			:	TheApplication->m_pActiveDoc->ViewDisplayHiddengreyed	();	break;

					case	swIsViewSectioned				:
					case	swIsViewPerspective				:
					case	swIsViewCurvature				:
					default									:	TheApplication->m_pActiveDoc->ViewDisplayShaded			();	break;
					}
				}

			}
		}
	else
		{
		ZW_FileName();
		goto START;
		}
	return;
}

void DllExport ZW_FileAddRecur(void)
{
	return;
}

void DllExport ZW_FileAddAll(void)
{
	return;
}

void DllExport ZW_FileAddAllRecur(void)
{
	return;
}

void DllExport ZW_Password(void)
{
	return;
}

void DllExport ZW_Compression(void)
{
	return;
}

void DllExport ZW_Register(void)
{
	CRegister	dlg;

    dlg.DoModal();

	return;
}

int DllExport ZW_RegisterUpdate(void)
{
#if 0
return 0;  	// If you want the menu item to be unchecked and disabled (grayed out)
return 1;  	// If you want the menu item to be unchecked and enabled
return 2;  	// If you want the menu item to be checked and disabled (grayed out)
return 3; 	// If you want the menu item to be checked and enabled
#endif

	return g_bRegistered == true ? 0 : 1;
}

// --------------------------------
//  End of ZipWorks.cpp
// --------------------------------
