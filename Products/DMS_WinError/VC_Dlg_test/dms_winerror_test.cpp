// DMS_WinError_Test.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DMS_WinError_Test.h"
#include "DMS_WinError_TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMS_WinError_TestApp

BEGIN_MESSAGE_MAP(CDMS_WinError_TestApp, CWinApp)
	//{{AFX_MSG_MAP(CDMS_WinError_TestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMS_WinError_TestApp construction

CDMS_WinError_TestApp::CDMS_WinError_TestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDMS_WinError_TestApp object

CDMS_WinError_TestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDMS_WinError_TestApp initialization

BOOL CDMS_WinError_TestApp::InitInstance()
{
	AfxEnableControlContainer();

    CoInitialize(NULL);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDMS_WinError_TestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CDMS_WinError_TestApp::ExitInstance() 
{
    CoUninitialize();
    return CWinApp::ExitInstance();
}
