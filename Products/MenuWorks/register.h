#if !defined(AFX_REGISTER_H__8D4EE8F1_7236_11D2_89AE_000000000000__INCLUDED_)
#define AFX_REGISTER_H__8D4EE8F1_7236_11D2_89AE_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Register.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegister dialog

class CRegister : public CDialog
{
// Construction
public:
	CRegister(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegister)
	enum { IDD = IDD_REGISTER };
	CString	m_cstrCode;
	CString	m_cstrMachineID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegister)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegister)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTER_H__8D4EE8F1_7236_11D2_89AE_000000000000__INCLUDED_)
