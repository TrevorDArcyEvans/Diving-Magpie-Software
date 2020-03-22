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
//  Description: Implements the CWinWksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>
#include <comdef.h>

#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"
#include "WinWks.h"


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
CWinWksApp::CWinWksApp(LPSLDWORKS pSldWorks)
{
	// application
	m_pSldWorks = pSldWorks;
	m_pActiveDoc = NULL;

	// menus
	m_bPartMenu = FALSE;
	m_bAssemblyMenu = FALSE;
	m_bDrawingMenu = FALSE;
}

CWinWksApp::~CWinWksApp()
{
	// default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CWinWksApp::StartApplication(void)
{
	// add menus to the active document
	AddMenus();

	// create a control item to handle application-level events
	swAppEvents* eventApp = new swAppEvents;
	eventApp->OnCreate(m_pSldWorks);

	return TRUE;
}

void CWinWksApp::TerminateApplication(void)
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
void CWinWksApp::AddMenus(void)
{
	HRESULT         res, hres;
	VARIANT_BOOL    bres;


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

// adds a menu and save-as item to the currently active document type
//
void CWinWksApp::docCreateMenu(long DocumentType)
{
    #define WW_POSITION              5
    #define SAVE_ALL_POSITION        7
    #define swLastPosition          -1

	HRESULT         hres;
	VARIANT_BOOL    bres;

    char            pcCallback[_MAX_PATH];

	LPFRAME pFrame;
	hres = m_pSldWorks->IFrameObject(&pFrame);

    // remove existing menu
	hres = m_pSldWorks->RemoveMenu(DocumentType,
                auT(WW_MENU_ITEM_CLOSE_ALL), NULL, &bres);

	// add new Close All menu item
    sprintf(pcCallback, WW_EXPORT_CLOSE_ALL_STR, WW_DLL_NAME,
        WW_EXPORT_CLOSE_ALL);
	hres = pFrame->AddMenuItem(
			    auT("&Window"), auT("Close Al&l"), WW_POSITION,
                _bstr_t(pcCallback),
				&bres);

	// add new Save All menu item
    sprintf(pcCallback, WW_EXPORT_SAVE_ALL_STR, WW_DLL_NAME,
        WW_EXPORT_SAVE_ALL);
	hres = pFrame->AddMenuItem(
			    auT("&File"), auT("Sav&e All"), SAVE_ALL_POSITION,
                _bstr_t(pcCallback),
				&bres);

    // try and add WindowWorks menu to top level SolidPartners menu
    hres = pFrame->AddMenu(auT(WW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
    	// add top level SolidPartners menu item
	    hres = pFrame->AddMenu(_bstr_t(SP_MENU), -1, &bres);


        // add WindowWorks menu
        hres = pFrame->AddMenu(auT(WW_MENU), swLastPosition, &bres);
        }


    // add WindowWorks Register menu item
    sprintf(pcCallback, WW_EXPORT_REGISTER_STR, WW_DLL_NAME,
        WW_EXPORT_REGISTER, WW_EXPORT_REGISTER_UPDATE);
    hres = pFrame->AddMenuItem(
                auT(WW_MENU), auT(WW_MENU_ITEM_REGISTER), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add WindowWorks Help menu item
    sprintf(pcCallback, WW_EXPORT_HELP_STR, WW_DLL_NAME,
        WW_EXPORT_HELP);
    hres = pFrame->AddMenuItem(
                auT(WW_MENU), auT(WW_MENU_ITEM_HELP), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add WindowWorks About menu item
    sprintf(pcCallback, WW_EXPORT_ABOUT_STR, WW_DLL_NAME,
        WW_EXPORT_ABOUT);
    hres = pFrame->AddMenuItem(
                auT(WW_MENU), auT(WW_MENU_ITEM_ABOUT), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

	// clean up
	pFrame->Release();
}

void CWinWksApp::RemoveMenus(void)
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
void CWinWksApp::docRemoveMenu(long DocumentType)
{
	HRESULT      hres;
	VARIANT_BOOL bres;

	// remove Window->Close All menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(WW_MENU_ITEM_CLOSE_ALL), NULL, &bres);

	// remove File->Savee All menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(WW_MENU_ITEM_SAVE_ALL), NULL, &bres);

	//remove WindowWorks menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(WW_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CWinWksApp::AddEvent(CObject* swEventHandler)
{
	// add to the object list
	m_EventList.AddTail(swEventHandler);
}

bool CWinWksApp::RemoveEvent(CObject* swEventHandler)
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

void CWinWksApp::ChangeActiveDoc(void)
{
	// release the refence count on the previously active document
	if (m_pActiveDoc != NULL)
		m_pActiveDoc->Release();

	// Set the new active document
	HRESULT res;
	res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}

void CWinWksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
	// Determine if the part being destroyed was the active document.
	// If so, release a reference to it, and set m_pActiveDoc to NULL
	if (DocBeingDestroyed == m_pActiveDoc)
	{
		m_pActiveDoc->Release();
		m_pActiveDoc = NULL;
	}
}

void CWinWksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
	m_pSldWorks = pSldWorks;
}

LPSLDWORKS CWinWksApp::GetSWApp(void)
{
	return m_pSldWorks;
}
// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
