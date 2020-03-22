// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: EvtDoc.h
//  Description: Definition of event handler classes for SolidWorks
//               notifications.
//
// -------------------------------------------------------------------

#if !defined(EVTSDOC_H)
#define EVTSDOC_H

#include "ccitem.h"
#include "SldWorks.h"

class swDocumentEvents;

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
	virtual HRESULT OnNewView();
	virtual HRESULT OnDestroy(void);
};

#endif

// --------------------------------
//  End of EvtDoc.h
// --------------------------------
