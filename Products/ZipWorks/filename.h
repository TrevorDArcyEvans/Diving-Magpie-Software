#if !defined(AFX_ZW_FILENAME_H__F3CC0FAC_5545_11D2_896F_08002B935393__INCLUDED_)
#define AFX_ZW_FILENAME_H__F3CC0FAC_5545_11D2_896F_08002B935393__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ZW_FileName.h : header file
//

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CZW_FileName dialog

class CFileName : public CDialog
{
// Construction
public:
	CFileName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZW_FileName)
	enum { IDD = IDD_DIALOG_FILE_NAME };
	CString	m_FileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZW_FileName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZW_FileName)
	afx_msg void OnButtonBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZW_FILENAME_H__F3CC0FAC_5545_11D2_896F_08002B935393__INCLUDED_)
