// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CPointerWorksApp class which is the
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

#define	PW_MENU						"&PointerWorks"
#define	PW_MENU_ITEM_CONFIG			"&Configure..."
#define	PW_MENU_ITEM_CONFIG_LOAD	"&Load..."
#define	PW_MENU_ITEM_CONFIG_SAVE	"&Save"
#define	PW_MENU_ITEM_CONFIG_SAVE_AS	"Sa&ve As..."
#define	PW_MENU_ITEM_ABOUT			"&About..."

#ifdef _UNICODE
#define	PW_EXPORT_CONFIG			"PtrWorksNT@PW_Config, Configure PointerWorks"
#define	PW_EXPORT_CONFIG_LOAD		"PtrWorksNT@PW_ConfigLoad, Load a configuration"
#define	PW_EXPORT_CONFIG_SAVE		"PtrWorksNT@PW_ConfigSave, Save current configuration"
#define	PW_EXPORT_CONFIG_SAVE_AS	"PtrWorksNT@PW_ConfigSaveAs, Save current configuration under another name"
#define	PW_EXPORT_ABOUT				"PtrWorksNT@PW_About, Display program information"
#else
#define	PW_EXPORT_CONFIG			"PtrWorks95@PW_Config, Configure PointerWorks"
#define	PW_EXPORT_CONFIG_LOAD		"PtrWorks95@PW_ConfigLoad, Load a configuration"
#define	PW_EXPORT_CONFIG_SAVE		"PtrWorks95@PW_ConfigSave, Save current configuration"
#define	PW_EXPORT_CONFIG_SAVE_AS	"PtrWorks95@PW_ConfigSaveAs, Save current configuration under another name"
#define	PW_EXPORT_ABOUT				"PtrWorks95@PW_About, Display program information"
#endif

// --------------------------------
//  Class: CPointerWorksApp
// --------------------------------

class CPointerWorksApp : public CObject
{
private:
	bool m_bPartMenu;
	bool m_bAssemblyMenu;
	bool m_bDrawingMenu;

	CObList m_EventList;

public:
	// data members
	LPSLDWORKS m_pSldWorks;
	LPMODELDOC m_pActiveDoc;

	//  constructor/destructor
	CPointerWorksApp(LPSLDWORKS pSldWorks);
	~CPointerWorksApp();

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

	// events
	void AddEvent(CObject* swEventHandler);
	bool RemoveEvent(CObject* swEventHandler);

	CObList& GetEventList() {return m_EventList;}

private:
	void docCreateMenu(long DocumentType);
	void docRemoveMenu(long DocumentType);
};

// the application object
extern CPointerWorksApp* TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------


