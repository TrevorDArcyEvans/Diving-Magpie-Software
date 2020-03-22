// DMS_WinError_TestDlg.h : header file
//

#if !defined(AFX_DMS_WINERROR_TESTDLG_H__5B309D77_6E02_11D4_83D3_00104BB2580C__INCLUDED_)
#define AFX_DMS_WINERROR_TESTDLG_H__5B309D77_6E02_11D4_83D3_00104BB2580C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDMS_WinError_TestDlg dialog

class CDMS_WinError_TestDlg : public CDialog
{
// Construction
public:
	CDMS_WinError_TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDMS_WinError_TestDlg)
	enum { IDD = IDD_DMS_WINERROR_TEST_DIALOG };
	int		m_nErrorCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMS_WinError_TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDMS_WinError_TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMS_WINERROR_TESTDLG_H__5B309D77_6E02_11D4_83D3_00104BB2580C__INCLUDED_)
