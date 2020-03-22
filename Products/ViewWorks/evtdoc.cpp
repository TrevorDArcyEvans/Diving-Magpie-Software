// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: EvtDoc.cpp
//  Description: Implementation of the event handlers for SolidWorks
//               notifications.
//
// -------------------------------------------------------------------

// To Handle events sent by a SolidWorks Object: 
//  	Derive an object like swx*****Events from CControlItem
//  	Define Functions on this object to handle the events you are interested in
//  	Put appropriate ON_EVENT lines for those events in the object's EVENTSINK map
//
// Syntax for ON_EVENT 
//
//  ON_EVENT (object, -1, swxEventID, handlerFunc, handlerFuncArgs)
//   handlerFuncArgs are specified in the API documentation for that event.
//   It is a space seperated list of arguments with appropriate types
//   defined in mfc\include\afxdisp.h file Some common ones are
//  
//   double			VTS_R8
//   long			VTS_I4
//	 boolean		VTS_BOOL
//   IDispatch*     VTS_DISPATCH
//   LPCOLESTR		VTS_WBSTR
//	 No args		VTS_NONE

#include "stdafx.h"

#include "SldWorks.h"
#include "debug.h"
#include "EvtDoc.h"

#include "ExampleApp.h"

// --------------------------------
//  Document Events
// --------------------------------
IMPLEMENT_SERIAL(swDocumentEvents, CCmdTarget, 1)
BEGIN_EVENTSINK_MAP(swDocumentEvents, CControlItem)
END_EVENTSINK_MAP()
// --------------------------------
swDocumentEvents::~swDocumentEvents()
{
	HRESULT hres;

	// inform CSillyWksApp that this document has been destroyed

	LPMODELDOC pModelDoc = NULL;
	hres = m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);

	TheApplication->DestroyDoc(pModelDoc);
	pModelDoc->Release();
}
// --------------------------------
BOOL swDocumentEvents::FoundInterface(LPMODELDOC pDoc)
{
	LPMODELDOC pModelDoc = NULL;
	m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);
	if(pModelDoc && (pDoc == pModelDoc))
	{
		pModelDoc->Release();
		return TRUE;
	}
	return FALSE;
}
// --------------------------------
void swDocumentEvents::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
// --------------------------------
void swDocumentEvents::GetStreamName(CString& strStream)
{
	strStream = _T("ViewWorksDoc");
}
// --------------------------------
HRESULT swDocumentEvents::OnLoadFromStorage()
{
	return S_OK;
}
// --------------------------------
HRESULT swDocumentEvents::OnSaveToStorage()
{
	return S_OK;
}
// --------------------------------
HRESULT swDocumentEvents::OnNewView()
{
	return S_OK;
}
// --------------------------------
HRESULT swDocumentEvents::OnDestroy(void)
{
	// tde
	VW_OutputDebugString(_T("swDocumentEvents::OnDestroy"));

	delete this;
	return S_OK;
}
// --------------------------------
//  End of EvtDoc.cpp
// --------------------------------
