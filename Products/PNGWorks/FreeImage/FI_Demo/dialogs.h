#if !defined(AFX_DIALOGS_H__7A7F2881_ABAE_11D4_9568_F621226ACF67__INCLUDED_)
#define AFX_DIALOGS_H__7A7F2881_ABAE_11D4_9568_F621226ACF67__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dialogs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRotation dialog

class DlgRotation : public CDialog
{
// Construction
public:
	DlgRotation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRotation)
	enum { IDD = IDD_DLG_INT };
	int		m_Angle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRotation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgRotation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// DlgImageInfos dialog

class DlgImageInfos : public CDialog
{
// Construction
public:
	DlgImageInfos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgImageInfos)
	enum { IDD = IDD_IMAGE_INFOS };
	CString	m_Class;
	UINT	m_Depth;
	UINT	m_Height;
	UINT	m_ResX;
	UINT	m_ResY;
	UINT	m_Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgImageInfos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgImageInfos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// DlgFloat dialog

class DlgFloat : public CDialog
{
// Construction
public:
	DlgFloat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgFloat)
	enum { IDD = IDD_DLG_FLOAT };
	CString	m_FloatName;
	float	m_FloatValue;
	//}}AFX_DATA
	CString m_sCaption;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgFloat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgFloat)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGS_H__7A7F2881_ABAE_11D4_9568_F621226ACF67__INCLUDED_)
