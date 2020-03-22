// FI_Doc.h : interface of the CFI_Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FI_DOC_H__782F8FCC_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
#define AFX_FI_DOC_H__782F8FCC_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFI_Doc : public CDocument
{
protected: // create from serialization only
	CFI_Doc();
	DECLARE_DYNCREATE(CFI_Doc)

// Attributes
public:
	void *m_dib;

// Operations
public:
	bool Load(LPCTSTR lpszPathName);
	bool Save(LPCTSTR lpszPathName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFI_Doc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFI_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFI_Doc)
	afx_msg void OnFileSaveAs();
	afx_msg void OnConvertTo8Bits();
	afx_msg void OnUpdateConvertTo8Bits(CCmdUI* pCmdUI);
	afx_msg void OnConvertTo16Bits();
	afx_msg void OnUpdateConvertTo16Bits(CCmdUI* pCmdUI);
	afx_msg void OnConvertTo24Bits();
	afx_msg void OnUpdateConvertTo24Bits(CCmdUI* pCmdUI);
	afx_msg void OnConvertTo32Bits();
	afx_msg void OnUpdateConvertTo32Bits(CCmdUI* pCmdUI);
	afx_msg void OnColorQuantize();
	afx_msg void OnUpdateColorQuantize(CCmdUI* pCmdUI);
	afx_msg void OnFlip();
	afx_msg void OnMirror();
	afx_msg void OnInvert();
	afx_msg void OnRotate();
	afx_msg void OnConvertToGreyscale();
	afx_msg void OnUpdateConvertToGreyscale(CCmdUI* pCmdUI);
	afx_msg void OnImageInfos();
	afx_msg void OnBlur();
	afx_msg void OnUpdateBlur(CCmdUI* pCmdUI);
	afx_msg void OnBrighten();
	afx_msg void OnUpdateBrighten(CCmdUI* pCmdUI);
	afx_msg void OnDarken();
	afx_msg void OnUpdateDarken(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FI_DOC_H__782F8FCC_A9D8_11D4_9568_CE2CCEDA354F__INCLUDED_)
