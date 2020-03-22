// DMS_WinError_Test.h : main header file for the DMS_WINERROR_TEST application
//

#if !defined(AFX_DMS_WINERROR_TEST_H__5B309D75_6E02_11D4_83D3_00104BB2580C__INCLUDED_)
#define AFX_DMS_WINERROR_TEST_H__5B309D75_6E02_11D4_83D3_00104BB2580C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDMS_WinError_TestApp:
// See DMS_WinError_Test.cpp for the implementation of this class
//

class CDMS_WinError_TestApp : public CWinApp
{
public:
	CDMS_WinError_TestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMS_WinError_TestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDMS_WinError_TestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMS_WINERROR_TEST_H__5B309D75_6E02_11D4_83D3_00104BB2580C__INCLUDED_)
