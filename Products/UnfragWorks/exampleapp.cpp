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
//  Description: Implements the CUnfragWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>
#include <comdef.h>

#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"

#include "UnfragWorks.h"

#include "debug.h"

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
CUnfragWorksApp::CUnfragWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks     = pSldWorks;
    m_pActiveDoc    = NULL;

    // menus
    m_bPartMenu     = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu  = FALSE;
}
// -----------------------------------------------------------------
CUnfragWorksApp::~CUnfragWorksApp()
{
    // default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CUnfragWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
// -----------------------------------------------------------------
void CUnfragWorksApp::TerminateApplication(void)
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
void CUnfragWorksApp::AddMenus(void)
{
    HRESULT res;

    LPMODELDOC pModelDoc = NULL;
    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);

    if (pModelDoc != NULL)
    {
        // get the document type
        long doctype;
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
// -----------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CUnfragWorksApp::docCreateMenu(long DocumentType)
{
    HRESULT         hres;
    VARIANT_BOOL    bres;

    char            pcCallback[_MAX_PATH];

    LPFRAME pFrame;
    hres = m_pSldWorks->IFrameObject(&pFrame);


    // add UnfragWorks menu
    hres = pFrame->AddMenu(auT(UW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level menu item
        hres = pFrame->AddMenu(_bstr_t(SP_MENU), -1, &bres);


        // add PointerWorks menu
        hres = pFrame->AddMenu(auT(UW_MENU), swLastPosition, &bres);
        }


    // add UnfragWorks Register menu item
    sprintf(pcCallback, UW_EXPORT_REGISTER_STR, UW_DLL_NAME,
        UW_EXPORT_REGISTER, UW_EXPORT_REGISTER_UPDATE);
    hres = pFrame->AddMenuItem(
                auT(UW_MENU), auT(UW_MENU_ITEM_REGISTER), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    #if 0
    // add UnfragWorks Configure menu item
    hres = pFrame->AddMenuItem(
                auT(SW_TOOLS), auT(UW_MENU_ITEM_REG_CONFIG), swLastPosition,
                auT(UW_EXPORT_CONFIG),
                &bres);
    #endif

    // add UnfragWorks Help menu item
    sprintf(pcCallback, UW_EXPORT_HELP_STR, UW_DLL_NAME,
        UW_EXPORT_HELP);
    hres = pFrame->AddMenuItem(
                auT(UW_MENU), auT(UW_MENU_ITEM_HELP), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add UnfragWorks About menu item
    sprintf(pcCallback, UW_EXPORT_ABOUT_STR, UW_DLL_NAME,
        UW_EXPORT_ABOUT);
    hres = pFrame->AddMenuItem(
                auT(UW_MENU), auT(UW_MENU_ITEM_ABOUT), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // clean up
    pFrame->Release();
}
// -----------------------------------------------------------------
void CUnfragWorksApp::RemoveMenus(void)
{
    // remove menus and save-as items from each document type
    if (m_bPartMenu)
        docRemoveMenu(swDocPART);

    if (m_bAssemblyMenu)
        docRemoveMenu(swDocASSEMBLY);

    if (m_bDrawingMenu)
        docRemoveMenu(swDocDRAWING);
}
// -----------------------------------------------------------------
// removes menu from the currently active document type
//
void CUnfragWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT      hres;
    VARIANT_BOOL bres;

    LPFRAME pFrame;
    hres = m_pSldWorks->IFrameObject(&pFrame);

    char        pcMenuItem[_MAX_PATH],
                pcCallback[_MAX_PATH];

    #if 0
    // remove Tools->Register UnfragWorks
    sprintf(pcMenuItem, "%s@%s", UW_MENU_ITEM_REGISTER, SW_TOOLS);
    sprintf(pcCallback, UW_EXPORT_REGISTER_STR, UW_DLL_NAME,
        UW_EXPORT_REGISTER, UW_EXPORT_REGISTER_UPDATE);
    hres = m_pSldWorks->RemoveMenu(DocumentType,
            _bstr_t(pcMenuItem), _bstr_t(pcCallback), &bres);

    // remove Tools->Configure UnfragWorks
    sprintf(pcMenuItem, "%s@%s", UW_MENU_ITEM_CONFIG, SW_TOOLS);
    sprintf(pcCallback, UW_EXPORT_CONFIG_STR, UW_DLL_NAME,
        UW_EXPORT_CONFIG);
    hres = m_pSldWorks->RemoveMenu(DocumentType,
            _bstr_t(pcMenuItem), _bstr_t(pcCallback), &bres);

    // remove Tools->UnfragWorks Help
    sprintf(pcMenuItem, "%s@%s", UW_MENU_ITEM_HELP, SW_TOOLS);
    sprintf(pcCallback, UW_EXPORT_HELP_STR, UW_DLL_NAME,
        UW_EXPORT_HELP);
    hres = m_pSldWorks->RemoveMenu(DocumentType,
            _bstr_t(pcMenuItem), _bstr_t(pcCallback), &bres);

    // remove Tools->About UnfragWorks
    sprintf(pcMenuItem, "%s@%s", UW_MENU_ITEM_ABOUT, SW_TOOLS);
    sprintf(pcCallback, UW_EXPORT_ABOUT_STR, UW_DLL_NAME,
        UW_EXPORT_ABOUT);
    hres = m_pSldWorks->RemoveMenu(DocumentType,
            _bstr_t(pcMenuItem), _bstr_t(pcCallback), &bres);
    #endif

    //remove menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(UW_MENU), NULL, &bres);

    // clean up
    pFrame->Release();
}

// --------------------------------
//  Events
// --------------------------------

void CUnfragWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
// -----------------------------------------------------------------
bool CUnfragWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CUnfragWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
// -----------------------------------------------------------------
void CUnfragWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
        {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
        }
}
// -----------------------------------------------------------------
void CUnfragWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}
// -----------------------------------------------------------------
LPSLDWORKS CUnfragWorksApp::GetSWApp(void)
{
    return m_pSldWorks;
}
// -----------------------------------------------------------------

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
