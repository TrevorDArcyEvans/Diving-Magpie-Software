// BMPWorks.h : main header file for the BMPWORKS DLL
//

#if !defined(AFX_BMPWORKS_H__C3392CA5_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_)
#define AFX_BMPWORKS_H__C3392CA5_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBMPWorksApp
// See BMPWorks.cpp for the implementation of this class
//

class CBMPWorksApp : public CWinApp
{
public:
	CBMPWorksApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMPWorksApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBMPWorksApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPWORKS_H__C3392CA5_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_)
