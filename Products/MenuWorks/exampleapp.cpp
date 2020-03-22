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
//  Description: Implements the CMenuWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>
#include <comdef.h>

#include "Resource.h"
#include "MenuWorks.h"
#include "About.h"
#include "ExampleApp.h"
#include "init.h"
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
CMenuWorksApp::CMenuWorksApp(LPSLDWORKS pSldWorks)
{
	// application
	m_pSldWorks = pSldWorks;
	m_pActiveDoc = NULL;

	// menus
	m_bPartMenu = FALSE;
	m_bAssemblyMenu = FALSE;
	m_bDrawingMenu = FALSE;
}

CMenuWorksApp::~CMenuWorksApp()
{
	// default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CMenuWorksApp::StartApplication(void)
{
	// add menus to the active document
	AddMenus();

	// create a control item to handle application-level events
	swAppEvents* eventApp = new swAppEvents;
	eventApp->OnCreate(m_pSldWorks);

	return TRUE;
}

void CMenuWorksApp::TerminateApplication(void)
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
		 delete headEvent;			// destructor will remove it from list with RemoveAt(pos)
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
void CMenuWorksApp::AddMenus(void)
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

// adds a menu item to the currently active document type
//
void CMenuWorksApp::docCreateMenu(long DocumentType)
{
    #define swMenuPosition  5	// add your menu after Tools and before Window
    #define swLastPosition -1

    HRESULT         hres;
	VARIANT_BOOL    bres;
	LPFRAME         pFrame;
    _TCHAR          TempStr[512];

	hres = TheApplication->m_pSldWorks->IFrameObject(&pFrame);

    // ugly hack to get around problem of adding menus to
    // the active document when MW is loaded through 
    // the addin manager
	if(0 == strlen((const char *) g_MainMenuName))
        {
        // basically reinitialise if there is no top
        // level menu name
        MW_Init();
        }


    // add SolidPartners->MenuWorks menu
    hres = pFrame->AddMenu(auT(MW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add SolidPartners top level menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add MenuWorks menu
        hres = pFrame->AddMenu(auT(MW_MENU), swLastPosition, &bres);
        }


    // add Register menu item
	hres = pFrame->AddMenuItem(
				auT(MW_MENU), auT(MW_MENU_ITEM_REGISTER), swLastPosition,
				auT(MW_EXPORT_REGISTER),
				&bres);

	// add Configure menu item
	hres = pFrame->AddMenuItem(
	            auT(MW_MENU), auT(MW_MENU_ITEM_CONFIG), swLastPosition,
				auT(MW_EXPORT_CONFIG),
				&bres);


    // add Help menu item
	hres = pFrame->AddMenuItem(
				auT(MW_MENU), auT(MW_MENU_ITEM_HELP), swLastPosition,
				auT(MW_EXPORT_HELP),
				&bres);

    // add About menu item
	hres = pFrame->AddMenuItem(
				auT(MW_MENU), auT(MW_MENU_ITEM_ABOUT), swLastPosition,
				auT(MW_EXPORT_ABOUT),
				&bres);



	// add MenuWorks top level menu item
	hres = pFrame->AddMenu(_bstr_t(g_MainMenuName), swMenuPosition, &bres);

    if (false == g_bRegistered)
        {
        // add Register menu item
    	hres = pFrame->AddMenuItem(
                    _bstr_t(g_MainMenuName),
                    auT(MW_MENU_ITEM_REGISTER),
                    swLastPosition,
					auT(MW_EXPORT_REGISTER),
					&bres);

    	// add separator
	    hres = pFrame->AddMenuItem(
                    _bstr_t(g_MainMenuName),
                    NULL, swLastPosition,
				    NULL, &bres);
        }

    for (int i = 0; i < g_nMaxMenus; i++)
        {
        if (MenuItem[i].ProgName    &&
            MenuItem[i].MenuText    &&
            MenuItem[i].HintText    )
            {
            _stprintf(TempStr, _T("%s@ProgExec%d, %s"),
                MW_MAIN_DLL_NAME, i, MenuItem[i].HintText);

	        // add menu item
	        hres = pFrame->AddMenuItem(
	                    _bstr_t(g_MainMenuName),
                        _bstr_t(MenuItem[i].MenuText),
                        swLastPosition,
				        _bstr_t(TempStr),
                        &bres);
            }
        }

    if (false == g_bRegistered)
        {
    	// add separator
	    hres = pFrame->AddMenuItem(
                    _bstr_t(g_MainMenuName),
                    NULL, swLastPosition,
				    NULL, &bres);

    	// add About menu item
	    hres = pFrame->AddMenuItem(
                    _bstr_t(g_MainMenuName),
                    auT(MW_MENU_ITEM_ABOUT), swLastPosition,
					auT(MW_EXPORT_ABOUT),
                    &bres);

    	// add Help menu item
    	hres = pFrame->AddMenuItem(
                    _bstr_t(g_MainMenuName),
                    auT(MW_MENU_ITEM_HELP), swLastPosition,
			    	auT(MW_EXPORT_HELP), &bres);
        }

	// clean up
	pFrame->Release();
}

void CMenuWorksApp::RemoveMenus(void)
{
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
void CMenuWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT hres;
    VARIANT_BOOL bres;

    // remove menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(MW_MENU), NULL, &bres);
	hres = m_pSldWorks->RemoveMenu(DocumentType, _bstr_t(g_MainMenuName), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CMenuWorksApp::AddEvent(CObject* swEventHandler)
{
	// add to the object list
	m_EventList.AddTail(swEventHandler);
}

bool CMenuWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CMenuWorksApp::ChangeActiveDoc(void)
{
	// release the refence count on the previously active document
	if (m_pActiveDoc != NULL)
		m_pActiveDoc->Release();

	// Set the new active document
	HRESULT res;
	res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}

void CMenuWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
	// Determine if the part being destroyed was the active document.
	// If so, release a reference to it, and set m_pActiveDoc to NULL
	if (DocBeingDestroyed == m_pActiveDoc)
	{
		m_pActiveDoc->Release();
		m_pActiveDoc = NULL;
	}
}

void CMenuWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
	m_pSldWorks = pSldWorks;
}

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
