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
//  Description: Implements the CZipWorksApp class which is the
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
CZipWorksApp::CZipWorksApp(LPSLDWORKS pSldWorks)
{
	// application
	m_pSldWorks = pSldWorks;
	m_pActiveDoc = NULL;

	// menus
	m_bPartMenu = FALSE;
	m_bAssemblyMenu = FALSE;
	m_bDrawingMenu = FALSE;
}

CZipWorksApp::~CZipWorksApp()
{
	// default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CZipWorksApp::StartApplication(void)
{
	// add menus to the active document
	AddMenus();

	// create a control item to handle application-level events
	swAppEvents* eventApp = new swAppEvents;
	eventApp->OnCreate(m_pSldWorks);

	return TRUE;
}

void CZipWorksApp::TerminateApplication(void)
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

#define swMenuPosition  5	// add your menu after Tools and before Window
#define swLastPosition -1

//  Add a menu to the active document frame.  This is to be done
//  only ONCE for each document type.
//  
void CZipWorksApp::AddMenus(void)
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

// adds a menu and save-as item to the currently active document type
//
void CZipWorksApp::docCreateMenu(long DocumentType)
{
	HRESULT hres;
	VARIANT_BOOL bres;

	LPFRAME pFrame;
	hres = m_pSldWorks->IFrameObject(&pFrame);

	// add menu
	hres = pFrame->AddMenu(auT(ZW_MENU), swMenuPosition, &bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_FILE_NAME), swLastPosition,
					auT(ZW_EXPORT_FILE_NAME),
					&bres);

	// add separator
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_SEPARATOR), swLastPosition,
					auT(ZW_EXPORT_NULL),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_ADD), swLastPosition,
					auT(ZW_EXPORT_ADD),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_ADD_RECUR), swLastPosition,
					auT(ZW_EXPORT_ADD_RECUR),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_ADD_ALL), swLastPosition,
					auT(ZW_EXPORT_ADD_ALL),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_ADD_ALL_RECUR), swLastPosition,
					auT(ZW_EXPORT_ADD_ALL_RECUR),
					&bres);

	// add separator
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_SEPARATOR), swLastPosition,
					auT(ZW_EXPORT_NULL),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_OPTIONS), swLastPosition,
					auT(ZW_EXPORT_OPTIONS),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_PASSWORD), swLastPosition,
					auT(ZW_EXPORT_PASSWORD),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_COMPRESSION), swLastPosition,
					auT(ZW_EXPORT_COMPRESSION),
					&bres);

	// add separator
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_SEPARATOR), swLastPosition,
					auT(ZW_EXPORT_NULL),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_REGISTER), swLastPosition,
					auT(ZW_EXPORT_REGISTER),
					&bres);

	// add separator
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_SEPARATOR), swLastPosition,
					auT(ZW_EXPORT_NULL),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_ABOUT), swLastPosition,
					auT(ZW_EXPORT_ABOUT),
					&bres);

	// add menu item
	hres = pFrame->AddMenuItem(
					auT(ZW_MENU), auT(ZW_MENU_ITEM_HELP), swLastPosition,
					auT(ZW_EXPORT_HELP),
					&bres);

	// clean up
	pFrame->Release();
}

void CZipWorksApp::RemoveMenus(void)
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
void CZipWorksApp::docRemoveMenu(long DocumentType)
{
	HRESULT      hres;
	VARIANT_BOOL bres;

	// remove menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(ZW_MENU), NULL, &bres);

}

// --------------------------------
//  Events
// --------------------------------

void CZipWorksApp::AddEvent(CObject* swEventHandler)
{
	// add to the object list
	m_EventList.AddTail(swEventHandler);
}

bool CZipWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CZipWorksApp::ChangeActiveDoc(void)
{
	// release the refence count on the previously active document
	if (m_pActiveDoc != NULL)
		m_pActiveDoc->Release();

	// Set the new active document
	HRESULT res;
	res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}

void CZipWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
	// Determine if the part being destroyed was the active document.
	// If so, release a reference to it, and set m_pActiveDoc to NULL
	if (DocBeingDestroyed == m_pActiveDoc)
	{
		m_pActiveDoc->Release();
		m_pActiveDoc = NULL;
	}
}

void CZipWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
	m_pSldWorks = pSldWorks;
}

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
