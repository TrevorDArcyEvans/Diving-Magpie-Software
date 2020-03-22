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
//  Description: Implements the CStickWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

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
CStickWorksApp::CStickWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks     = pSldWorks;
    m_pActiveDoc    = NULL;

    // menus
    m_bPartMenu     = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu  = FALSE;


    CComBSTR                    sName(STICK_WORKS_TITLE);
    CComBSTR                    sCode(STICK_WORKS_TITLE_CODE);
    CComBSTR                    sIniFileName(STICK_WORKS_INI_FILE_NAME);
    int                         nTempIsReg = false;
    HRESULT                     hr;

    // initially set addin to unregistered &
    // joystick control panel not open
    g_bRegistered           = false;
    g_bJoystickPanelShowing = false;

    CoInitialize(NULL);

    hr = m_DMS_Comm.CoCreateInstance(__uuidof(DMS_Common), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hres));
    if (SUCCEEDED(hr))
        {
        try
            {
            hr = m_DMS_Comm->put_SolidWorks(pSldWorks);

            hr = m_DMS_Comm->put_Commercial(true);
            hr = m_DMS_Comm->put_ProductName(sName);
            hr = m_DMS_Comm->put_ProductCode(sCode);
            hr = m_DMS_Comm->put_Icon((long ) LoadIcon(GetModuleHandle(SW_DLL_NAME), MAKEINTRESOURCE(IDI_ICON_STKWKS)));
            hr = m_DMS_Comm->put_IniFileName(sIniFileName);
            hr = m_DMS_Comm->get_IsRegistered(&nTempIsReg);
            }
        catch (...)
            {
            }

        g_bRegistered = nTempIsReg;
        }


    hr = m_DMS_StkWks.CoCreateInstance(__uuidof(DMS_StickWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
    ASSERT(SUCCEEDED(hr));
    if (SUCCEEDED(hr))
        {
        try
            {
            hr = m_DMS_StkWks->put_Name(sName);
            hr = m_DMS_StkWks->put_Icon((long ) LoadIcon(GetModuleHandle(SW_DLL_NAME), MAKEINTRESOURCE(IDI_ICON_STKWKS)));
            }
        catch (...)
            {
            }
        }
}
//---------------------------------------------------------------------------
CStickWorksApp::~CStickWorksApp()
{
    // default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CStickWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
//---------------------------------------------------------------------------
void CStickWorksApp::TerminateApplication(void)
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
void CStickWorksApp::AddMenus(void)
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
//---------------------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CStickWorksApp::docCreateMenu(long DocumentType)
{
    #define swLastPosition -1

    HRESULT hres;
    VARIANT_BOOL bres;

    LPFRAME pFrame;
    hres = m_pSldWorks->IFrameObject(&pFrame);

    // add StickWorks menu
    hres = pFrame->AddMenu(auT(SW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level (SolidPartners) menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add StickWorks submenu
        hres = pFrame->AddMenu(auT(SW_MENU), swLastPosition, &bres);
        }

    // add configure menu item
    hres = pFrame->AddMenuItem(
                auT(SW_MENU), auT(SW_MENU_ITEM_CONFIG), swLastPosition,
                auT(SW_EXPORT_CONFIG),
                &bres);

    // add calibrate menu item
    hres = pFrame->AddMenuItem(
                auT(SW_MENU), auT(SW_MENU_ITEM_CALIBRATE), swLastPosition,
                auT(SW_EXPORT_CALIBRATE),
                &bres);

    // add separator
    hres = pFrame->AddMenuItem(
                    auT(SW_MENU), NULL, swLastPosition,
                    NULL,
                    &bres);

    // add Register menu item
    hres = pFrame->AddMenuItem(
                auT(SW_MENU), auT(SW_MENU_ITEM_REGISTER), swLastPosition,
                auT(SW_EXPORT_REGISTER),
                &bres);

    // add Help menu item
    hres = pFrame->AddMenuItem(
                auT(SW_MENU), auT(SW_MENU_ITEM_HELP), swLastPosition,
                auT(SW_EXPORT_HELP),
                &bres);

    // add About menu item
    hres = pFrame->AddMenuItem(
                auT(SW_MENU), auT(SW_MENU_ITEM_ABOUT), swLastPosition,
                auT(SW_EXPORT_ABOUT),
                &bres);

    // clean up
    pFrame->Release();
}
//---------------------------------------------------------------------------
void CStickWorksApp::RemoveMenus(void)
{
    // remove menus and save-as items from each document type
    if (m_bPartMenu)
        docRemoveMenu(swDocPART);

    if (m_bAssemblyMenu)
        docRemoveMenu(swDocASSEMBLY);

    if (m_bDrawingMenu)
        docRemoveMenu(swDocDRAWING);
}
//---------------------------------------------------------------------------
// removes a menu and save-as item to the currently active document type
//
void CStickWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT      hres;
    VARIANT_BOOL bres;

    //remove menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(SW_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CStickWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
//---------------------------------------------------------------------------
bool CStickWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CStickWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
//---------------------------------------------------------------------------
void CStickWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
    {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
    }
}
//---------------------------------------------------------------------------
void CStickWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
