#if !defined(AFX_DLG_FILES_H__C3392CAD_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_)
#define AFX_DLG_FILES_H__C3392CAD_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Files.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_Files dialog

class CDlg_Files : public CDialog
{
// Construction
public:
	CString     m_cstrFileName;
	CDlg_Files(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_Files)
	enum { IDD = IDD_DIALOG_FILES };
	int		m_nFileIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Files)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Files)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_FILES_H__C3392CAD_BD92_11D3_8BE4_08002BBCB3E1__INCLUDED_)
