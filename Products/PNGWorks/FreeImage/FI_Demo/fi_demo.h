// FI_Demo.h : main header file for the FI_DEMO application
//

#if !defined(AFX_FI_DEMO_H__782F8FC4_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
#define AFX_FI_DEMO_H__782F8FC4_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "FreeImage.h"

/////////////////////////////////////////////////////////////////////////////
// CFI_App:
// See FI_Demo.cpp for the implementation of this class
//

class CFI_App : public CWinApp
{
public:
	CFI_App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFI_App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFI_App)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FI_DEMO_H__782F8FC4_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
