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
//  Description: Implements the CViewWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"
#include <comdef.h>

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
CViewWorksApp::CViewWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks = pSldWorks;
    m_pActiveDoc = NULL;

    // menus
    m_bPartMenu = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu = FALSE;
    m_bSWMenu = FALSE;
}

CViewWorksApp::~CViewWorksApp()
{
    // default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CViewWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}

void CViewWorksApp::TerminateApplication(void)
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
         delete headEvent;            // destructor will remove it from list with RemoveAt(pos)
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

#define swMenuPosition  5    // add your menu after Tools and before Window
#define swLastPosition -1

//  Add a menu to the active document frame.  This is to be done
//  only ONCE for each document type.
//
void CViewWorksApp::AddMenus(void)
{
    HRESULT         res, hres;
    VARIANT_BOOL    bres;

    if (NULL == m_bSWMenu)
        {
        // add file save-as item
        hres = m_pSldWorks->AddFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_PRT), swDocPART, &bres);

        hres = m_pSldWorks->AddFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_ASM), swDocASSEMBLY, &bres);

        hres = m_pSldWorks->AddFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_DRW), swDocDRAWING, &bres);

        // add file open item
        hres = m_pSldWorks->AddFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_PRT), &bres);

        hres = m_pSldWorks->AddFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_ASM), &bres);

        hres = m_pSldWorks->AddFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_DRW), &bres);

        m_bSWMenu = TRUE;
        }

    LPMODELDOC pModelDoc = NULL;
    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);

    if (pModelDoc != NULL)
        {
        // get the document type
        long    doctype;
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
        else
            return;

        // clean up
        pModelDoc->Release();
        }
}

// adds a menu and save-as item to the currently active document type
//
void CViewWorksApp::docCreateMenu(long DocumentType)
{
    #define swLastPosition -1

    HRESULT         hres;
    VARIANT_BOOL    bres;

    LPFRAME pFrame;
    hres = m_pSldWorks->IFrameObject(&pFrame);

    // add ViewWorks menu
    hres = pFrame->AddMenu(auT(VW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add ViewWorks menu
        hres = pFrame->AddMenu(auT(VW_MENU), swLastPosition, &bres);
        }

    // add Register menu item
    hres = pFrame->AddMenuItem(
                auT(VW_MENU), auT(VW_MENU_ITEM_REGISTER), swLastPosition,
                auT(VW_EXPORT_REGISTER),
                &bres);

    // add Help menu item
    hres = pFrame->AddMenuItem(
                auT(VW_MENU), auT(VW_MENU_ITEM_HELP), swLastPosition,
                auT(VW_EXPORT_HELP),
                &bres);

    // add About menu item
    hres = pFrame->AddMenuItem(
                auT(VW_MENU), auT(VW_MENU_ITEM_ABOUT), swLastPosition,
                auT(VW_EXPORT_ABOUT),
                &bres);

    // clean up
    pFrame->Release();
}

void CViewWorksApp::RemoveMenus(void)
{
    HRESULT         hres;
    VARIANT_BOOL    bres;

    if (TRUE == m_bSWMenu)
        {
        // remove save-as item
        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_PRT), swDocPART, &bres);

        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_ASM), swDocASSEMBLY, &bres);

        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(VW_EXPORT_SAVE_AS),
                    _bstr_t(VW_DESCRIP_DRW), swDocDRAWING, &bres);

        // remove file open item
        hres = m_pSldWorks->RemoveFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_PRT), &bres);

        hres = m_pSldWorks->RemoveFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_ASM), &bres);

        hres = m_pSldWorks->RemoveFileOpenItem(auT(VW_EXPORT_OPEN_AS),
                    _bstr_t(VW_DESCRIP_DRW), &bres);
        }

    // remove menus and save-as items from each document type
    if (m_bPartMenu)
        docRemoveMenu(swDocPART);

    if (m_bAssemblyMenu)
        docRemoveMenu(swDocASSEMBLY);

    if (m_bDrawingMenu)
        docRemoveMenu(swDocDRAWING);
}

// removes a menu and save-as item to the currently active document type
//
void CViewWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT      hres;
    VARIANT_BOOL bres;

    //remove menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(VW_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CViewWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}

bool CViewWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CViewWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}

void CViewWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
        {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
        }
}

void CViewWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}

LPSLDWORKS CViewWorksApp::GetSWApp()
{
    return m_pSldWorks;
}


// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
