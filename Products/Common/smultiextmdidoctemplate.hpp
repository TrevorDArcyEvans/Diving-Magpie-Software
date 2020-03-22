#ifndef __SMultiExtMDIDocTemplate_hpp
#define __SMultiExtMDIDocTemplate_hpp

#include <afxwin.h>

class SMultiExtMDIDocTemplate:public CMultiDocTemplate
{
private:

	mutable int m_NewCount;

public:

	SMultiExtMDIDocTemplate (UINT nIDResource, 
							 CRuntimeClass* pDocClass,
							 CRuntimeClass* pFrameClass, 
							 CRuntimeClass* pViewClass)
		:CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass),
	     m_NewCount (-1) {}

	BOOL GetDocString(CString& rString,enum DocStringIndex i) const;

	CDocTemplate::Confidence MatchDocType (const char* pszPathName, 
										   CDocument*& rpDocMatch);

	void SkipNextNew () {m_NewCount = 1;}
	void NotInNewList () {m_NewCount = -1;}
};//SMultiExtMDIDocTemplate

#endif

