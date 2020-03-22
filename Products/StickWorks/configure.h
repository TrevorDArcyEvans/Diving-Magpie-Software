#if !defined(AFX_CONFIGURE_H__0DE9B871_73F1_11D3_8B76_08002BBCB3E1__INCLUDED_)
#define AFX_CONFIGURE_H__0DE9B871_73F1_11D3_8B76_08002BBCB3E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Configure.h : header file
//
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigure dialog

class CConfigure : public CDialog
{
// Construction
public:
    CConfigure(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CConfigure)
    enum { IDD = IDD_DLG_CONFIG };
    int     m_nSensitivity;
    int     m_nThreshold;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConfigure)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigure)
    virtual void OnOK();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURE_H__0DE9B871_73F1_11D3_8B76_08002BBCB3E1__INCLUDED_)
