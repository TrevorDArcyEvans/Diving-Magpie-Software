// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: HandleEvents.h
//  Description: Definition of event handler classes for SolidWorks
//               notifications.
//
// -------------------------------------------------------------------

#if !defined(HANDLEEVENTS_H)
#define HANDLEEVENTS_H

#include "ccitem.h"

class swAppEvents;
class swDocumentEvents;
class swPartEvents;
class swDrawingEvents;
class swAssemblyEvents;
class swViewEvents;

class swAppEvents : public CControlItem
{
public:
	swAppEvents(){}
	DECLARE_EVENTSINK_MAP()

	// ole event handlers
	HRESULT OnModelDocChange(void);
	HRESULT swAppEvents::OnDocumentOpen(BSTR docName);
	HRESULT OnDocumentNew(LPDISPATCH NewDoc, long DocType);
	HRESULT OnDestroy(void);
};

class swDocumentEvents : public  CControlItem
{
private:
	BOOL	m_bLoaded;

public:
	BOOL FoundInterface(LPMODELDOC pDoc);

	virtual void Serialize(CArchive& ar);
	virtual void GetStreamName(CString& strStream);

public:
	swDocumentEvents(){m_bLoaded = FALSE;}
	~swDocumentEvents();
	DECLARE_EVENTSINK_MAP()
	DECLARE_SERIAL(swDocumentEvents)

	// ole event handlers
	HRESULT OnLoadFromStorage();
	HRESULT OnSaveToStorage();
	HRESULT OnNewView();
	HRESULT OnDestroy(void);
};

class swPartEvents : public swDocumentEvents
{
public:
	virtual void Serialize(CArchive& ar);
	virtual void GetStreamName(CString& strStream);

public:
	swPartEvents(){}
	DECLARE_EVENTSINK_MAP()
	DECLARE_SERIAL(swPartEvents)
};

class swAssemblyEvents : public swDocumentEvents
{
public:
	virtual void Serialize(CArchive& ar);
	virtual void GetStreamName(CString& strStream);

public:
	swAssemblyEvents(){}
	DECLARE_EVENTSINK_MAP()
	DECLARE_SERIAL(swAssemblyEvents)
};

class swDrawingEvents : public swDocumentEvents
{
public:
	virtual void Serialize(CArchive& ar);
	virtual void GetStreamName(CString& strStream);

public:
	swDrawingEvents(){}
	DECLARE_EVENTSINK_MAP()
	DECLARE_SERIAL(swDrawingEvents)
};

class swViewEvents : public CControlItem
{
public:
	BOOL FoundInterface(LPMODELVIEW pView);

public:
	swViewEvents(){ m_pfnOriginalWndProc = NULL; }
	DECLARE_EVENTSINK_MAP()
	DECLARE_SERIAL(swViewEvents)

	virtual ~swViewEvents();

protected:
	friend LRESULT CALLBACK PointerWorksWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	HWND    m_hWnd;
	WNDPROC m_pfnOriginalWndProc;

public:
	void OverloadWndProc();
	LRESULT CALLBACK OriginalWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		if(m_pfnOriginalWndProc)
		{
			return ::CallWindowProc(m_pfnOriginalWndProc, hWnd, nMsg, wParam, lParam);
		}
		else
		{
			return 0L;
		}
	}

	// Message Handling Functions
	BOOL OnLButtonDown(UINT nFlags, CPoint point);

	// ole event handlers
	HRESULT OnDestroy(void);
};

#endif

// --------------------------------
//  End of HandleEvents.h
// --------------------------------
