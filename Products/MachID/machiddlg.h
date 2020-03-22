// MachIDDlg.h : header file
//

#if !defined(AFX_MACHIDDLG_H__A3EDBBC0_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_)
#define AFX_MACHIDDLG_H__A3EDBBC0_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMachIDDlg dialog

class CMachIDDlg : public CDialog
{
// Construction
public:
    CMachIDDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CMachIDDlg)
    enum { IDD = IDD_MACHID_DIALOG };
    CString m_cstrMachID;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMachIDDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CMachIDDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACHIDDLG_H__A3EDBBC0_E4BA_11D2_8A80_08002BBCB3E1__INCLUDED_)
