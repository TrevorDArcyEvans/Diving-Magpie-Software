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
//  Description: Implements the CXGLWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

#include "XGLWorks.h"
#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"

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
CXGLWorksApp::CXGLWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks     = pSldWorks;
    m_pActiveDoc    = NULL;

    // menus
    m_bMainMenu     = FALSE;
    m_bPartMenu     = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu  = FALSE;
}
//------------------------------------------------------------------------
CXGLWorksApp::~CXGLWorksApp()
{
    // default destructor
}
//------------------------------------------------------------------------

// --------------------------------
//  Load/Unload
// --------------------------------

bool CXGLWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents*                eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
//------------------------------------------------------------------------
void CXGLWorksApp::TerminateApplication(void)
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
void CXGLWorksApp::AddMenus(void)
{
    HRESULT                     res;
    CComPtr <IModelDoc>         pModelDoc;
    long                        doctype;

    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);
    if (pModelDoc == NULL)
        {
        if (!m_bMainMenu)
            {
            docCreateMenu(swNONE);

            m_bMainMenu = TRUE;
            }

        return;
        }

    // get the document type
    res = pModelDoc->GetType(&doctype);

    if (doctype == swDocPART && m_bPartMenu == NULL)
        {
        docCreateMenu(doctype);
        m_bPartMenu = TRUE;
        }
    else if (doctype == swDocASSEMBLY && m_bAssemblyMenu == NULL)
        {
        docCreateMenu(doctype);
        m_bAssemblyMenu = TRUE;
        }
    else if (doctype == swDocDRAWING && m_bDrawingMenu == NULL)
        {
        docCreateMenu(doctype);
        m_bDrawingMenu = TRUE;
        }
}
//------------------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CXGLWorksApp::docCreateMenu(long DocumentType)
{
    #define swLastPosition      -1

    HRESULT                 hres;
    VARIANT_BOOL            bres;
    LPFRAME                 pFrame;

    hres = m_pSldWorks->IFrameObject(&pFrame);

    // add XGLWorks menu
    hres = pFrame->AddMenu(auT(XGL_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level (SolidPartners) menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add XGLWorks submenu
        hres = pFrame->AddMenu(auT(XGL_MENU), swLastPosition, &bres);
        }

    // add RealityWave web site menu item
    hres = pFrame->AddMenuItem(
                    auT(XGL_MENU), auT(XGL_MENU_ITEM_RWWEB), swLastPosition,
                    auT(XGL_EXPORT_RWWEB),
                    &bres);

    // add separator
    hres = pFrame->AddMenuItem(
                    auT(XGL_MENU), NULL, swLastPosition,
                    NULL,
                    &bres);

    // add Register menu item
    hres = pFrame->AddMenuItem(
                auT(XGL_MENU), auT(XGL_MENU_ITEM_REGISTER), swLastPosition,
                auT(XGL_EXPORT_REGISTER),
                &bres);

    // add Help menu item
    hres = pFrame->AddMenuItem(
                auT(XGL_MENU), auT(XGL_MENU_ITEM_HELP), swLastPosition,
                auT(XGL_EXPORT_HELP),
                &bres);

    // add About menu item
    hres = pFrame->AddMenuItem(
                    auT(XGL_MENU), auT(XGL_MENU_ITEM_ABOUT), swLastPosition,
                    auT(XGL_EXPORT_ABOUT),
                    &bres);


    // clean up
    pFrame->Release();


    if (swDocNONE == DocumentType)
        {
        // add XGL file open item
        hres = m_pSldWorks->AddFileOpenItem(auT(XGL_EXPORT_OPEN),
                        auT(XGL_OPEN_DESCRIP), &bres);

        // add ZGL file open item
        hres = m_pSldWorks->AddFileOpenItem(auT(XGL_EXPORT_OPEN),
                        auT(ZGL_OPEN_DESCRIP), &bres);
        }
}
//------------------------------------------------------------------------
void CXGLWorksApp::RemoveMenus(void)
{
    // remove menus and save-as items from each document type
    if (m_bMainMenu)
        {
        docRemoveMenu(swDocNONE);
        }

    if (m_bPartMenu)
        {
        docRemoveMenu(swDocPART);
        }

    if (m_bAssemblyMenu)
        {
        docRemoveMenu(swDocASSEMBLY);
        }

    if (m_bDrawingMenu)
        {
        docRemoveMenu(swDocDRAWING);
        }
}
//------------------------------------------------------------------------
// removes a menu and save-as item to the currently active document type
//
void CXGLWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT                 hres;
    VARIANT_BOOL            bres;
    LPFRAME                 pFrame;

    if (swDocNONE == DocumentType)
        {
        hres = m_pSldWorks->IFrameObject(&pFrame);

        // remove from SolidWorks top level menu
        hres = pFrame->RemoveMenu(auT(XGL_MENU));

        // clean up
        pFrame->Release();


        // remove XGL open item
        hres = m_pSldWorks->RemoveFileOpenItem(auT(XGL_EXPORT_OPEN),
                        auT(XGL_OPEN_DESCRIP), &bres);

        // remove ZGL open item
        hres = m_pSldWorks->RemoveFileOpenItem(auT(XGL_EXPORT_OPEN),
                        auT(ZGL_OPEN_DESCRIP), &bres);
        }


    // remove from SolidPartners menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(XGL_MENU), NULL, &bres);
}
//------------------------------------------------------------------------


// --------------------------------
//  Events
// --------------------------------

void CXGLWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
//------------------------------------------------------------------------
bool CXGLWorksApp::RemoveEvent(CObject* swEventHandler)
{
    POSITION pos;

    // remove from the object list
    pos = m_EventList.Find(swEventHandler);
    if (pos == 0)
        return FALSE;

    m_EventList.RemoveAt(pos);
    return TRUE;
}
//------------------------------------------------------------------------


// --------------------------------
//  helper functions
// --------------------------------

void CXGLWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
//------------------------------------------------------------------------
void CXGLWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
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
void CXGLWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}
//------------------------------------------------------------------------
LPSLDWORKS CXGLWorksApp::GetSWApp(void)
{
    return m_pSldWorks;
}
//------------------------------------------------------------------------

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
