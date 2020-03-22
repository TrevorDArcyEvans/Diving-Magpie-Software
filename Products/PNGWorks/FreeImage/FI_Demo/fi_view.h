// FI_View.h : interface of the CFI_View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FI_VIEW_H__782F8FCE_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
#define AFX_FI_VIEW_H__782F8FCE_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vfw.h>

// tell linker to look in Video for Windows
#pragma comment(lib,"vfw32.lib")


class CFI_View : public CScrollView
{
protected: // create from serialization only
	CFI_View();
	DECLARE_DYNCREATE(CFI_View)

// Attributes
protected:
	CPalette *m_pPalette;	// Color palette
	HDRAWDIB m_hDrawDib;	// for DrawDib
	
	BOOL CreatePalette(void *dib);

// Attributes
public:
	CFI_Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFI_View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFI_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFI_View)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FI_View.cpp
inline CFI_Doc* CFI_View::GetDocument()
   { return (CFI_Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FI_VIEW_H__782F8FCE_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
