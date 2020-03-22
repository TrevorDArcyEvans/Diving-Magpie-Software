// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: HandleEvents.cpp
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
#include "HandleEvents.h"
#include "ExampleApp.h"

// --------------------------------
//  Application Events
// --------------------------------

BEGIN_EVENTSINK_MAP(swAppEvents, CControlItem)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppActiveModelDocChangeNotify, OnModelDocChange, VTS_NONE)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileOpenNotify, OnDocumentOpen, VTS_BSTR)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileNewNotify, OnDocumentNew, VTS_DISPATCH VTS_I4)
	ON_EVENT (swAppEvents, (unsigned int)-1, swAppDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()

// A new document has been actived by the user.
//
HRESULT swAppEvents::OnModelDocChange(void)
{
	// If this is the first time a document of this type has been
	// activated, add the appropriate menus.  This can occur if the
	// application is loaded after SolidWorks is running.
	TheApplication->AddMenus();

	return S_OK;
}

// An existing document has been opened.
//
HRESULT swAppEvents::OnDocumentOpen(BSTR docName)
{
	// make sure a document of this type has menus
	TheApplication->AddMenus();

	HRESULT hres;
	LPSLDWORKS pSldWorks = NULL;
	
	hres = m_lpObject->QueryInterface(IID_ISldWorks, (void**)&pSldWorks);
	if(!pSldWorks)
		return S_OK;

	LPMODELDOC pActiveDoc = NULL;
	hres = pSldWorks->get_IActiveDoc(&pActiveDoc);

	pSldWorks->Release();

	if(!pActiveDoc)
		return S_OK;

	CObList& listEvents = TheApplication->GetEventList();

	BOOL fFound = FALSE;
	CControlItem* pItem = NULL;
	POSITION pos = listEvents.GetHeadPosition();
	while (pos)
	{
		pItem = (CControlItem*)listEvents.GetNext(pos);
		if(pItem && pItem->IsKindOf(RUNTIME_CLASS(swDocumentEvents)))
		{
			if(((swDocumentEvents*)pItem)->FoundInterface(pActiveDoc))
			{
				fFound = TRUE;
				break;
			}
		}
	}

	if(!fFound)
	{
		long DocType;
		pActiveDoc->GetType(&DocType);
		OnDocumentNew(pActiveDoc, DocType);
	}

	pActiveDoc->Release();

	return S_OK;
}

// A new document has been created.
//
HRESULT swAppEvents::OnDocumentNew(LPDISPATCH NewDoc, long DocType)
{
	HRESULT hres;

	LPMODELDOC pModelDoc = NULL;
	hres = NewDoc->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);
	ASSERT(hres == S_OK && pModelDoc != NULL);

	// Create a control item for the new document
	if(DocType == swDocPART)
	{
		swPartEvents* partEvent;
		partEvent = new swPartEvents;
		partEvent->OnCreate(pModelDoc);
		partEvent->OnNewView();
	}
	else if(DocType == swDocASSEMBLY)
	{
		swAssemblyEvents* assemblyEvent;
		assemblyEvent = new swAssemblyEvents;
		assemblyEvent->OnCreate(pModelDoc);
		assemblyEvent->OnNewView();
	}
	else if(DocType == swDocDRAWING)
	{
		swDrawingEvents* drawingEvent;
		drawingEvent = new swDrawingEvents;
		drawingEvent->OnCreate(pModelDoc);
		drawingEvent->OnNewView();
	}

	// clean up
	pModelDoc->Release();

	return S_OK;
}

// SolidWorks is shutting down and will destroy this applications
// menus, notification and save-as items
//
HRESULT swAppEvents::OnDestroy(void)
{
	delete  this;
	TheApplication->SetSWApp(NULL);

	return S_OK;
}

// --------------------------------
//  Document Events
// --------------------------------
IMPLEMENT_SERIAL(swDocumentEvents, CCmdTarget, 1)
BEGIN_EVENTSINK_MAP(swDocumentEvents, CControlItem)
END_EVENTSINK_MAP()

swDocumentEvents::~swDocumentEvents()
{
	HRESULT hres;

	// inform CPointerWorksApp that this document has been destroyed

	LPMODELDOC pModelDoc = NULL;
	hres = m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);

	TheApplication->DestroyDoc(pModelDoc);
	pModelDoc->Release();
}

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

void swDocumentEvents::GetStreamName(CString& strStream)
{
	strStream = _T("PointerWorksDoc");
}

HRESULT swDocumentEvents::OnLoadFromStorage()
{
	if(m_bLoaded != FALSE)
	{
		// This check is required because,
		// solid sends this notification even if
		// have already loaded our document.
		// This inturn will cause components data loss.
		return S_OK;
	}
	m_bLoaded = TRUE;

	HRESULT res;
	LPUNKNOWN pUnk = NULL;
	CString strStorage;
	GetStreamName(strStorage);
	BSTR stringIn = strStorage.AllocSysString();

	LPMODELDOC pModelDoc = NULL;
	res = m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);
	if(!pModelDoc)
	{
		return E_FAIL;
	}

	res = pModelDoc->IGet3rdPartyStorage(stringIn, FALSE, &pUnk);

	if(!pUnk)
	{
		return E_FAIL;
	}

	LPSTREAM pStream = NULL;
	res = pUnk->QueryInterface(IID_IStream, (LPVOID *)&pStream);
	ASSERT(res == S_OK);

	if(!pStream)
	{
		return E_FAIL;
	}

	COleStreamFile file(pStream);
	CArchive ar(&file, CArchive::load);

	Serialize(ar);

	pStream->Release();

	pModelDoc->Release();

	return S_OK;
}

HRESULT swDocumentEvents::OnSaveToStorage()
{
	HRESULT res;
	LPUNKNOWN pUnk = NULL;
	CString strStorage;
	GetStreamName(strStorage);
	BSTR stringIn = strStorage.AllocSysString();

	LPMODELDOC pModelDoc = NULL;
	res = m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);
	if(!pModelDoc)
	{
		return E_FAIL;
	}

	res = pModelDoc->IGet3rdPartyStorage(stringIn, TRUE, &pUnk);

	if(!pUnk)
	{
		return E_FAIL;
	}

	LPSTREAM pStream = NULL;
	res = pUnk->QueryInterface(IID_IStream, (LPVOID *)&pStream);
	ASSERT(res == S_OK);

	if(!pStream)
	{
		return E_FAIL;
	}

	COleStreamFile file(pStream);

	CArchive ar(&file, CArchive::store);

	Serialize(ar);

	pStream->Release();

	return S_OK;
}

HRESULT swDocumentEvents::OnNewView()
{
	LPMODELDOC pModelDoc = NULL;
	m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);

	if(!pModelDoc)
		return S_OK;

	LPMODELVIEW pModelView = NULL;
	HRESULT res = pModelDoc->get_IActiveView(&pModelView);
	pModelDoc->Release();

	if(!pModelView)
		return S_OK;

	CObList& listEvents = TheApplication->GetEventList();

	BOOL fFound = FALSE;
	CControlItem* pItem = NULL;
	POSITION pos = listEvents.GetHeadPosition();
	while (pos)
	{
		pItem = (CControlItem*)listEvents.GetNext(pos);
		if(pItem && pItem->IsKindOf(RUNTIME_CLASS(swViewEvents)))
		{
			if(((swViewEvents*)pItem)->FoundInterface(pModelView))
			{
				fFound = TRUE;
				break;
			}
		}
	}

	if(!fFound)
	{
		swViewEvents* pViewEvent = new swViewEvents();
		pViewEvent->OnCreate(pModelView);
		pViewEvent->OverloadWndProc();
	}

	pModelView->Release();

	return S_OK;
}

HRESULT swDocumentEvents::OnDestroy(void)
{
	delete this;
	return S_OK;
}

// --------------------------------
//  Part Events
// --------------------------------

IMPLEMENT_SERIAL(swPartEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swPartEvents, swDocumentEvents)
	ON_EVENT (swPartEvents, (unsigned int)-1, swPartDestroyNotify, OnDestroy, VTS_NONE)
	ON_EVENT (swPartEvents, (unsigned int)-1, swPartLoadFromStorageNotify, OnLoadFromStorage, VTS_NONE)
	ON_EVENT (swPartEvents, (unsigned int)-1, swPartSaveToStorageNotify, OnSaveToStorage, VTS_NONE)
	ON_EVENT (swPartEvents, (unsigned int)-1, swPartViewNewNotify, OnNewView, VTS_NONE)
END_EVENTSINK_MAP()

void swPartEvents::Serialize(CArchive& ar)
{
	swDocumentEvents::Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

void swPartEvents::GetStreamName(CString& strStream)
{
	strStream = _T("PointerWorksPart");
}

// --------------------------------
//  Assembly Events
// --------------------------------

IMPLEMENT_SERIAL(swAssemblyEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swAssemblyEvents, swDocumentEvents)
	ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyDestroyNotify, OnDestroy, VTS_NONE)
	ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyLoadFromStorageNotify, OnLoadFromStorage, VTS_NONE)
	ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblySaveToStorageNotify, OnSaveToStorage, VTS_NONE)
	ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyViewNewNotify, OnNewView, VTS_NONE)
END_EVENTSINK_MAP()

void swAssemblyEvents::Serialize(CArchive& ar)
{
	swDocumentEvents::Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

void swAssemblyEvents::GetStreamName(CString& strStream)
{
	strStream = _T("PointerWorksAssembly");
}

// --------------------------------
//  Drawing Events
// --------------------------------

IMPLEMENT_SERIAL(swDrawingEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swDrawingEvents, swDocumentEvents)
	ON_EVENT (swDrawingEvents, (unsigned int)-1, swDrawingDestroyNotify, OnDestroy, VTS_NONE)
	ON_EVENT (swDrawingEvents, (unsigned int)-1, swDrawingLoadFromStorageNotify, OnLoadFromStorage, VTS_NONE)
	ON_EVENT (swDrawingEvents, (unsigned int)-1, swDrawingSaveToStorageNotify, OnSaveToStorage, VTS_NONE)
	ON_EVENT (swDrawingEvents, (unsigned int)-1, swDrawingViewNewNotify, OnNewView, VTS_NONE)
END_EVENTSINK_MAP()

void swDrawingEvents::Serialize(CArchive& ar)
{
	swDocumentEvents::Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

void swDrawingEvents::GetStreamName(CString& strStream)
{
	strStream = _T("PointerWorksDrawing");
}

// --------------------------------
//  View Events
// --------------------------------

IMPLEMENT_SERIAL(swViewEvents, CCmdTarget, 1)
BEGIN_EVENTSINK_MAP(swViewEvents, CControlItem)
	ON_EVENT (swViewEvents, (unsigned int)-1, swViewDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()

CMapPtrToPtr g_mapHwndToPointerWorksViewEvent;

LRESULT CALLBACK PointerWorksWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	swViewEvents* pViewEvent = NULL;
	BOOL bRes = g_mapHwndToPointerWorksViewEvent.Lookup(hWnd, (void*&)pViewEvent);

	if(bRes && pViewEvent)
    	{
		BOOL bRetVal = TRUE;

		if(nMsg == WM_LBUTTONDOWN)
    		{
			CPoint point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			bRetVal = pViewEvent->OnLButtonDown(wParam, point);
    		}

    	// get the active document
		if(nMsg == WM_MBUTTONDOWN || nMsg == WM_MOUSEWHEEL)
            {
            // variables for middle button and wheel
            LPMODELDOC      ActiveDoc;

            if (S_OK == TheApplication->m_pSldWorks->get_IActiveDoc(&ActiveDoc))
                {
        		if(nMsg == WM_MBUTTONDOWN)
            		{
                    ActiveDoc->ViewZoomtofit();   	
	    	        }


        		if(nMsg == WM_MOUSEWHEEL)
        		    {
                    // Handle WM_MOUSEWHEEL message.
                    // We handle this message a little differently since the
                    //  roller movement info is in the HIWORD of wParam.
                    //
                    // The MouseWheel has 18 'detents'. As the wheel is rolled
                    //  and a detent is encountered, the OS will send a WM_MOUSEWHEEL
                    //  message with the HIWORD of wParam set to a value of +/- 120.
                    //  '+' if the wheel is being rolled forward (away from the user),
                    //  '-' if the wheel is being rolled backwards (towards the user). 

            		// Mouse Wheel is being rolled forward
        	    	if((short ) HIWORD(wParam) > 0)
		                {
                        ActiveDoc->ViewZoomin();
	            	    }

            		// Mouse Wheel is being rolled backward
	            	if((short ) HIWORD(wParam) < 0)
        		        {
                        ActiveDoc->ViewZoomout();
	            	    }
        		    }
                }

        	bRetVal = FALSE;
            }

		// bRetVal = FALSE means Component doesn't want
		// Solid Works to handle this message.
		// That means Component has used this message
		// for its own purpose.
		if(bRetVal == FALSE)
		    {
			return 0L;
		    }
		else
		    {
			return pViewEvent->OriginalWndProc(hWnd, nMsg, wParam, lParam);
		    }
	}
	return AfxWndProc(hWnd, nMsg, wParam, lParam);
}

swViewEvents::~swViewEvents()
{
	if ( m_pfnOriginalWndProc != NULL )
	{
		::SetWindowLong(m_hWnd, GWL_WNDPROC,
			(LONG)(WNDPROC)m_pfnOriginalWndProc);
	}
	g_mapHwndToPointerWorksViewEvent.RemoveKey(m_hWnd);
}

HRESULT swViewEvents::OnDestroy(void)
{
	delete this;
	return S_OK;
}

BOOL swViewEvents::FoundInterface(LPMODELVIEW pView)
{
	LPMODELVIEW pModelView = NULL;
	m_lpObject->QueryInterface(IID_IModelView, (void**)&pModelView);
	if(pModelView && (pView == pModelView))
	{
		pModelView->Release();
		return TRUE;
	}
	return FALSE;
}

void swViewEvents::OverloadWndProc()
{
	LPMODELVIEW pModelView = NULL;
	m_lpObject->QueryInterface(IID_IModelView, (void**)&pModelView);

	long h;
	pModelView->GetViewHWnd(&h);
	m_hWnd = (HWND)h;
	m_pfnOriginalWndProc = (WNDPROC)::GetWindowLong(m_hWnd, GWL_WNDPROC);
	::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)(WNDPROC)PointerWorksWndProc);
	g_mapHwndToPointerWorksViewEvent[m_hWnd] = this;

	pModelView->Release();
}

BOOL swViewEvents::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bRetVal = TRUE;

	// tde
	//AfxMessageBox(_T("swViewEvents::OnLButtonDown"));

	// bRetVal = FALSE means Component doesn't want
	// Solid Works to handle this message.
	// That means Component has used this message
	// for its own purpose.

	return bRetVal;
}

// --------------------------------
//  End of HandleEvents.cpp
// --------------------------------
