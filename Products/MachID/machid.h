// MachID.h : main header file for the MACHID application
//

#if !defined(AFX_MACHID_H__A3EDBBBE_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_)
#define AFX_MACHID_H__A3EDBBBE_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMachIDApp:
// See MachID.cpp for the implementation of this class
//

class CMachIDApp : public CWinApp
{
public:
	CMachIDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMachIDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMachIDApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACHID_H__A3EDBBBE_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_)
