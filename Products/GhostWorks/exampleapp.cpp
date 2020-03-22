//$c01 JPS 06/17/98  Initialize m_pActiveDoc pointer
//
// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.cpp
//  Description: Implements the CGhostWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"
#include "GhostWorks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// --------------------------------
//  Constructor/Destructor
// --------------------------------

// the constructor and destructor are only called once per session
//
CGhostWorksApp::CGhostWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks     = pSldWorks;
    m_pActiveDoc    = NULL;

    // menus
    m_bPartMenu     = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu  = FALSE;
}
//------------------------------------------------------------------------
CGhostWorksApp::~CGhostWorksApp()
{
    // default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CGhostWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
//------------------------------------------------------------------------
void CGhostWorksApp::TerminateApplication(void)
{
    // need this test because SW can terminate the app by
    // shutting down or by unloading it from the Add-In
    if (m_pSldWorks == NULL)
        return;

    // remove all menus
    RemoveMenus();

    // remove events - the event destructor removes
    // the object from the list
    int count = m_EventList.GetCount();
    for (int i=0; i<count; i++)
    {
         CObject* headEvent = m_EventList.GetHead();
         delete headEvent;          // destructor will remove it from list with RemoveAt(pos)
    }

    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // disconnect from SolidWorks
    m_pSldWorks->Release();
    m_pSldWorks = NULL;
}

// --------------------------------
//  menus
// --------------------------------

//  Add a menu to the active document frame.  This is to be done
//  only ONCE for each document type.
//  
void CGhostWorksApp::AddMenus(void)
{
    HRESULT                     res;
    CComPtr <IModelDoc>         pModelDoc;
    long                        doctype;

    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);
    if (pModelDoc == NULL)
        {
        return;
        }

    // get the document type
    res = pModelDoc->GetType(&doctype);

    if (doctype == swDocPART && m_bPartMenu == NULL)
        {
        #if 0
        // don't do parts - keep for reference
        docCreateMenu(doctype);
        m_bPartMenu = TRUE;
        #endif
        }
    else if (doctype == swDocASSEMBLY && m_bAssemblyMenu == NULL)
        {
        docCreateMenu(doctype);
        m_bAssemblyMenu = TRUE;
        }
    else if (doctype == swDocDRAWING && m_bDrawingMenu == NULL)
        {
        #if 0
        // don't do drawings - keep for reference
        docCreateMenu(doctype);
        m_bDrawingMenu = TRUE;
        #endif
        }
    else
        {
        return;
        }
}
//------------------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CGhostWorksApp::docCreateMenu(long DocumentType)
{
    const long                  swLastPosition = -1;

    HRESULT                     hres;
    VARIANT_BOOL                bres;

    CComPtr <IFrame>            pFrame;

    hres = m_pSldWorks->IFrameObject(&pFrame);

    // add GhostWorks menu
    hres = pFrame->AddMenu(auT(GHOST_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level SolidPartners menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add MassWorks menu
        hres = pFrame->AddMenu(auT(GHOST_MENU), swLastPosition, &bres);
        }

    // add Help menu item
    hres = pFrame->AddMenuItem(
                auT(GHOST_MENU), auT(GHOST_MENU_ITEM_HELP), swLastPosition,
                auT(GHOST_EXPORT_HELP),
                &bres);

    // add About menu item
    hres = pFrame->AddMenuItem(
                auT(GHOST_MENU), auT(GHOST_MENU_ITEM_ABOUT), swLastPosition,
                auT(GHOST_EXPORT_ABOUT),
                &bres);
}
//------------------------------------------------------------------------
void CGhostWorksApp::RemoveMenus(void)
{
    // remove menus and save-as items from each document type
    #if 0
    // don't do parts - keep for reference
    if (m_bPartMenu)
        {
        docRemoveMenu(swDocPART);
        }
    #endif

    if (m_bAssemblyMenu)
        {
        docRemoveMenu(swDocASSEMBLY);
        }

    #if 0
    // don't do drawings - keep for reference
    if (m_bDrawingMenu)
        docRemoveMenu(swDocDRAWING);
    #endif
}
//------------------------------------------------------------------------
// removes a menu and save-as item to the currently active document type
//
void CGhostWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT                     hres;
    VARIANT_BOOL                bres;

    // remove menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(GHOST_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CGhostWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
//------------------------------------------------------------------------
bool CGhostWorksApp::RemoveEvent(CObject* swEventHandler)
{
    POSITION pos;

    // remove from the object list
    pos = m_EventList.Find(swEventHandler);
    if (pos == 0)
        return FALSE;

    m_EventList.RemoveAt(pos);
    return TRUE;
}

// --------------------------------
//  helper functions
// --------------------------------

void CGhostWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
//------------------------------------------------------------------------
void CGhostWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
    {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
    }
}
//------------------------------------------------------------------------
void CGhostWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}
//------------------------------------------------------------------------
LPSLDWORKS CGhostWorksApp::GetSWApp(void)
{
    return m_pSldWorks;
}
//------------------------------------------------------------------------
void CGhostWorksApp::SetResources()
{
    TheApplication->m_hSaveDll = AfxGetResourceHandle();
    AfxSetResourceHandle(TheApplication->m_hDll);
}
//------------------------------------------------------------------------
void CGhostWorksApp::ResetResources()
{
    AfxSetResourceHandle(TheApplication->m_hSaveDll);
}
//------------------------------------------------------------------------
void CGhostWorksApp::SetResourceDll(HMODULE hDll)
{
    m_hDll = hDll;
}
//------------------------------------------------------------------------

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------

