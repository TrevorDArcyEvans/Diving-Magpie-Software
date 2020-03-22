// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CViewWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#if !defined(EXAMPLEAPP_H)
#define EXAMPLEAPP_H

#if _MSC_VER >= 1000
#pragma once
#endif

// SolidWorks includes
#include "SldWorks.h"


#define	SP_MENU						"&SolidPartners"
#define	VW_MENU						"&ViewWorks...@&SolidPartners"
#define	VW_MENU_ITEM_REGISTER       "&Register..."
#define	VW_MENU_ITEM_HELP           "&Help..."
#define	VW_MENU_ITEM_ABOUT			"&About..."

#define	VW_DESCRIP_PRT              "VEWPRT\nSolidWorks Viewer (*.vewprt)"
#define	VW_DESCRIP_ASM              "VEWASM\nSolidWorks Viewer (*.vewasm)"
#define	VW_DESCRIP_DRW              "VEWDRW\nSolidWorks Viewer (*.vewdrw)"

#ifdef _UNICODE
#define	VW_DLL_NAME			        _T("ViewWorksNT.dll")
#define	VW_EXPORT_SAVE_AS   		"ViewWorksNT@VW_SaveAsView"
#define	VW_EXPORT_OPEN_AS   		"ViewWorksNT@VW_OpenView"
#define	VW_EXPORT_HELP              "ViewWorksNT@VW_Help, Browse help file..."
#define	VW_EXPORT_REGISTER          "ViewWorksNT@VW_Register@VW_RegisterUpdate, Enter software registration code"
#define	VW_EXPORT_ABOUT				"ViewWorksNT@VW_About, Display program information"
#else
#define	VW_DLL_NAME			        _T("ViewWorks95.dll")
#define	VW_EXPORT_SAVE_AS   		"ViewWorks95@VW_SaveAsView"
#define	VW_EXPORT_OPEN_AS   		"ViewWorks95@VW_OpenView"
#define	VW_EXPORT_HELP              "ViewWorks95@VW_Help, Browse help file..."
#define	VW_EXPORT_REGISTER          "ViewWorks95@VW_Register@VW_RegisterUpdate, Enter software registration code"
#define	VW_EXPORT_ABOUT				"ViewWorks95@VW_About, Display program information"
#endif

// --------------------------------
//  Class: CViewWorksApp
// --------------------------------

class CViewWorksApp : public CObject
{
private:
	// data members
	LPSLDWORKS m_pSldWorks;
	LPMODELDOC m_pActiveDoc;

	bool m_bPartMenu;
	bool m_bAssemblyMenu;
	bool m_bDrawingMenu;
	bool m_bSWMenu;

	CObList m_EventList;

public:
	//  constructor/destructor
	CViewWorksApp(LPSLDWORKS pSldWorks);
	~CViewWorksApp();

    //DECLARE_EVENTSINK_MAP()

	// load/unload application
	bool StartApplication(void);
	void TerminateApplication(void);

	// menus
	void AddMenus(void);
	void RemoveMenus(void);

	// helper
	void ChangeActiveDoc(void);
	void DestroyDoc(LPMODELDOC DocBeingDestroyed);
	void SetSWApp(LPSLDWORKS pSldWorks);
    LPSLDWORKS GetSWApp();

	// events
	void AddEvent(CObject* swEventHandler);
	bool RemoveEvent(CObject* swEventHandler);

	CObList& GetEventList() {return m_EventList;}

private:
	void docCreateMenu(long DocumentType);
	void docRemoveMenu(long DocumentType);
};

// the application object
extern CViewWorksApp* TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------


