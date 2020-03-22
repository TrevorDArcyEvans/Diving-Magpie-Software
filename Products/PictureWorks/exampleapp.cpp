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
//  Description: Implements the CPictureWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

#include "PictureWorks.h"
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
CPictureWorksApp::CPictureWorksApp(LPSLDWORKS pSldWorks)
{
	// application
	m_pSldWorks = pSldWorks;
	m_pActiveDoc = NULL;

	// menus
	m_bPartMenu = FALSE;
	m_bAssemblyMenu = FALSE;
	m_bDrawingMenu = FALSE;
}

CPictureWorksApp::~CPictureWorksApp()
{
	// default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CPictureWorksApp::StartApplication(void)
{
	// add menus to the active document
	AddMenus();

	// create a control item to handle application-level events
	swAppEvents* eventApp = new swAppEvents;
	eventApp->OnCreate(m_pSldWorks);

	return TRUE;
}

void CPictureWorksApp::TerminateApplication(void)
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
void CPictureWorksApp::AddMenus(void)
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
void CPictureWorksApp::docCreateMenu(long DocumentType)
{
    #define swLastPosition      -1
    #define PW_MenuPosition     2
    #define PW_ItemPosition     4

	HRESULT hres;
	VARIANT_BOOL bres;

	LPFRAME pFrame;
	hres = m_pSldWorks->IFrameObject(&pFrame);

    // add PictureWorks menu
    hres = pFrame->AddMenu(auT(PW_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add PictureWorks menu
        hres = pFrame->AddMenu(auT(PW_MENU), swLastPosition, &bres);
        }

    // add Help menu item
	hres = pFrame->AddMenuItem(
				auT(PW_MENU), auT(PW_MENU_ITEM_HELP), swLastPosition,
				auT(PW_EXPORT_HELP),
				&bres);

    // add About menu item
	hres = pFrame->AddMenuItem(
				auT(PW_MENU), auT(PW_MENU_ITEM_ABOUT), swLastPosition,
				auT(PW_EXPORT_ABOUT),
				&bres);




	// add menu item
	hres = pFrame->AddMenuItem(
				    auT("&Edit"),
                    auT("Copy &image"),
                    PW_ItemPosition,
					auT(PW_EXPORT_COPY),
					&bres);

	// clean up
	pFrame->Release();
}

void CPictureWorksApp::RemoveMenus(void)
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
void CPictureWorksApp::docRemoveMenu(long DocumentType)
{
	HRESULT      hres;
	VARIANT_BOOL bres;

	// remove menu
	hres = m_pSldWorks->RemoveMenu(DocumentType,
        auT("Copy &image@&Edit"), NULL, &bres);

	//remove PictureWorks menu
	hres = m_pSldWorks->RemoveMenu(DocumentType, auT(PW_MENU), NULL, &bres);

}

// --------------------------------
//  Events
// --------------------------------

void CPictureWorksApp::AddEvent(CObject* swEventHandler)
{
	// add to the object list
	m_EventList.AddTail(swEventHandler);
}

bool CPictureWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CPictureWorksApp::ChangeActiveDoc(void)
{
	// release the refence count on the previously active document
	if (m_pActiveDoc != NULL)
		m_pActiveDoc->Release();

	// Set the new active document
	HRESULT res;
	res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}

void CPictureWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
	// Determine if the part being destroyed was the active document.
	// If so, release a reference to it, and set m_pActiveDoc to NULL
	if (DocBeingDestroyed == m_pActiveDoc)
	{
		m_pActiveDoc->Release();
		m_pActiveDoc = NULL;
	}
}

void CPictureWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
	m_pSldWorks = pSldWorks;
}

LPSLDWORKS CPictureWorksApp::GetSWApp(void)
{
	return m_pSldWorks;
}


// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
