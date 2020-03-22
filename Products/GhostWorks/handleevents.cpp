//$c01 JPS 08/20/98  Added fix for WndProc option
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
//      Derive an object like swx*****Events from CControlItem
//      Define Functions on this object to handle the events you are interested in
//      Put appropriate ON_EVENT lines for those events in the object's EVENTSINK map
//
// Syntax for ON_EVENT 
//
//  ON_EVENT (object, -1, swxEventID, handlerFunc, handlerFuncArgs)
//   handlerFuncArgs are specified in the API documentation for that event.
//   It is a space seperated list of arguments with appropriate types
//   defined in mfc\include\afxdisp.h file Some common ones are
//  
//   double         VTS_R8
//   long           VTS_I4
//   boolean        VTS_BOOL
//   IDispatch*     VTS_DISPATCH
//   LPCOLESTR      VTS_WBSTR
//   No args        VTS_NONE

#include "stdafx.h"

#include "SldWorks.h"
#include "HandleEvents.h"
#include "ExampleApp.h"
#include "GhostWorks.h"
#include "FMView.h"
#include "debug.h"


// --------------------------------
//  Application Events
// --------------------------------

BEGIN_EVENTSINK_MAP(swAppEvents, CControlItem)
    ON_EVENT (swAppEvents, (unsigned int)-1, swAppActiveModelDocChangeNotify, OnModelDocChange, VTS_NONE)
    ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileOpenNotify, OnDocumentOpen, VTS_BSTR)
    ON_EVENT (swAppEvents, (unsigned int)-1, swAppFileNewNotify, OnDocumentNew, VTS_DISPATCH VTS_I4)
    ON_EVENT (swAppEvents, (unsigned int)-1, swAppDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()


//------------------------------------------------------------------------
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
//------------------------------------------------------------------------
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
        OnDocumentNew(pActiveDoc, DocType);     // Set up events for opened doc.
    }

    pActiveDoc->Release();

    return S_OK;
}
//------------------------------------------------------------------------
// A new document has been created.
//
HRESULT swAppEvents::OnDocumentNew(LPDISPATCH NewDoc, long DocType)
{
    HRESULT                     hres;
    CFMView*                    pFMView;
    LPMODELDOC                  pModelDoc = NULL;

    hres = NewDoc->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);
    ASSERT(hres == S_OK && pModelDoc != NULL);

    // Create a control item for the new document
    if (DocType == swDocASSEMBLY)
        {
        // we only do assemblies
        swAssemblyEvents*       assemblyEvent;
        assemblyEvent = new swAssemblyEvents;
        assemblyEvent->OnCreate(pModelDoc);

        // Create the Feature Manager View
        pFMView = CreateFeatureManagerView(true);
        assemblyEvent->SetFMView(pFMView);
        }

    // clean up
    pModelDoc->Release();

    return S_OK;
}
//------------------------------------------------------------------------
// SolidWorks is shutting down and will destroy this applications
// menus, notification and save-as items
//
HRESULT swAppEvents::OnDestroy(void)
{
    delete  this;
    TheApplication->SetSWApp(NULL);

    return S_OK;
}
//------------------------------------------------------------------------


// --------------------------------
//  Document Events
// --------------------------------
IMPLEMENT_SERIAL(swDocumentEvents, CCmdTarget, 1)
BEGIN_EVENTSINK_MAP(swDocumentEvents, CControlItem)
END_EVENTSINK_MAP()


//------------------------------------------------------------------------
swDocumentEvents::~swDocumentEvents()
{
    HRESULT hres;

    // inform CGhostWorksApp that this document has been destroyed

    LPMODELDOC pModelDoc = NULL;
    hres = m_lpObject->QueryInterface(IID_IModelDoc, (void**)&pModelDoc);

    TheApplication->DestroyDoc(pModelDoc);
    pModelDoc->Release();
}
//------------------------------------------------------------------------
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
//------------------------------------------------------------------------
HRESULT swDocumentEvents::OnDestroy(void)
{
    delete this;
    return S_OK;
}
//------------------------------------------------------------------------
void swDocumentEvents::SetFMView(CFMView* pFMView)
{
    m_pFMView = pFMView;
}
//------------------------------------------------------------------------


// --------------------------------
//  Part Events
// --------------------------------

IMPLEMENT_SERIAL(swPartEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swPartEvents, swDocumentEvents)
    ON_EVENT (swPartEvents, (unsigned int)-1, swPartDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()


// --------------------------------
//  Assembly Events
// --------------------------------

IMPLEMENT_SERIAL(swAssemblyEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swAssemblyEvents, swDocumentEvents)
    ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyNewSelectionNotify, OnNewSelection, VTS_NONE)
    ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyDestroyNotify, OnDestroy, VTS_NONE)
    ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyAddItemNotify, OnAddItemNotify, VTS_I4 VTS_BSTR)
    ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyDeleteItemNotify, OnDeleteItemNotify, VTS_I4 VTS_BSTR)
    ON_EVENT (swAssemblyEvents, (unsigned int)-1, swAssemblyRenameItemNotify, OnRenameItemNotify, VTS_I4 VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


//------------------------------------------------------------------------
HRESULT swAssemblyEvents::OnNewSelection()
{
    SW_OutputDebugString(_T("swAssemblyEvents::OnNewSelection\n"));

    return S_OK;
}
//------------------------------------------------------------------------
HRESULT swAssemblyEvents::OnAddItemNotify(long EntityType, BSTR FileName)
{
    SW_OutputDebugString(_T("swAssemblyEvents::OnAddItemNotify\n"));

    if (swNotifyComponent == EntityType)
        {
        SW_OutputDebugString(_T("swAssemblyEvents::OnAddItemNotify : swNotifyComponent\n"));

        if (m_pFMView)
            {
            m_pFMView->Initialise();
            }
        }
    return S_OK;
}
//------------------------------------------------------------------------
HRESULT swAssemblyEvents::OnDeleteItemNotify(long EntityType, BSTR ItemName)
{
    SW_OutputDebugString(_T("swAssemblyEvents::OnDeleteItemNotify\n"));

    if (swNotifyComponent == EntityType)
        {
        SW_OutputDebugString(_T("swAssemblyEvents::OnDeleteItemNotify : swNotifyComponent\n"));

        if (m_pFMView)
            {
            m_pFMView->Initialise();
            }
        }
    return S_OK;
}
//------------------------------------------------------------------------
HRESULT swAssemblyEvents::OnRenameItemNotify(long EntityType, BSTR OldName, BSTR NewName)
{
    SW_OutputDebugString(_T("swAssemblyEvents::RenameItemNotify\n"));

    if (swNotifyComponent == EntityType)
        {
        SW_OutputDebugString(_T("swAssemblyEvents::RenameItemNotify : swNotifyComponent\n"));

        if (m_pFMView)
            {
            m_pFMView->Initialise();
            }
        }
    return S_OK;
}
//------------------------------------------------------------------------


// --------------------------------
//  Drawing Events
// --------------------------------

IMPLEMENT_SERIAL(swDrawingEvents, swDocumentEvents, 1)
BEGIN_EVENTSINK_MAP(swDrawingEvents, swDocumentEvents)
    ON_EVENT (swDrawingEvents, (unsigned int)-1, swDrawingDestroyNotify, OnDestroy, VTS_NONE)
END_EVENTSINK_MAP()

// --------------------------------
//  End of HandleEvents.cpp
// --------------------------------
