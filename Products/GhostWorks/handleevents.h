//$c01 JPS 08/20/98  Added fix for WndProc option
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

class CFMView;
//------------------------------------------------------------------------
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
//------------------------------------------------------------------------
class swDocumentEvents : public  CControlItem
{
private:
    BOOL                            m_bLoaded;
    CFMView*                        m_pFMView;

public:
    BOOL FoundInterface(LPMODELDOC pDoc);

public:
    swDocumentEvents() {}
    ~swDocumentEvents();
    DECLARE_EVENTSINK_MAP()
    DECLARE_SERIAL(swDocumentEvents)

    // ole event handlers
    HRESULT OnDestroy(void);

    void SetFMView(CFMView*  pFMView);

    friend class swPartEvents;
    friend class swAssemblyEvents;
    friend class swDrawingEvents;
};
//------------------------------------------------------------------------
class swPartEvents : public swDocumentEvents
{
public:
    swPartEvents(){}
    DECLARE_EVENTSINK_MAP()
    DECLARE_SERIAL(swPartEvents)
};
//------------------------------------------------------------------------
class swAssemblyEvents : public swDocumentEvents
{
public:
    swAssemblyEvents(){}
    DECLARE_EVENTSINK_MAP()
    DECLARE_SERIAL(swAssemblyEvents)

    HRESULT OnNewSelection();
    HRESULT OnAddItemNotify(long EntityType, BSTR FileName);
    HRESULT OnDeleteItemNotify(long entityType, BSTR ItemName);
    HRESULT OnRenameItemNotify(long EntityType, BSTR OldName, BSTR NewName);
};
//------------------------------------------------------------------------
class swDrawingEvents : public swDocumentEvents
{
public:
    swDrawingEvents(){}
    DECLARE_EVENTSINK_MAP()
    DECLARE_SERIAL(swDrawingEvents)
};
//------------------------------------------------------------------------

#endif

// --------------------------------
//  End of HandleEvents.h
// --------------------------------
