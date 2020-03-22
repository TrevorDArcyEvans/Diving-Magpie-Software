// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CZipWorksApp class which is the
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

#define		ZW_MENU						"&ZipWorks"
#define		ZW_MENU_ITEM_FILE_NAME		"&File name..."
#define		ZW_MENU_ITEM_OPTIONS		"&Options..."
#define		ZW_MENU_ITEM_ADD			"A&dd"
#define		ZW_MENU_ITEM_ADD_RECUR		"Add re&cursively"
#define		ZW_MENU_ITEM_ADD_ALL		"Add a&ll"
#define		ZW_MENU_ITEM_ADD_ALL_RECUR	"Add all &recursively"
#define		ZW_MENU_ITEM_PASSWORD		"&Password..."
#define		ZW_MENU_ITEM_COMPRESSION	"Co&mpression..."
#define		ZW_MENU_ITEM_SEPARATOR		"\0"
#define		ZW_MENU_ITEM_REGISTER		"Re&gister..."
#define		ZW_MENU_ITEM_ABOUT			"&About..."
#define		ZW_MENU_ITEM_HELP			"&Help..."

#ifdef _UNICODE
#define		ZW_EXPORT_FILE_NAME			"ZipWorksNT@ZW_FileName, Specify zip file name"
#define		ZW_EXPORT_OPTIONS			"ZipWorksNT@ZW_Options, Set options for zip file"
#define		ZW_EXPORT_ADD				"ZipWorksNT@ZW_FileAdd, Add current file to zip file"
#define		ZW_EXPORT_ADD_RECUR			"ZipWorksNT@ZW_FileAddRecur, Add current file recursively to zip file"
#define		ZW_EXPORT_ADD_ALL			"ZipWorksNT@ZW_FileAddAll, Add all open files to zip file"
#define		ZW_EXPORT_ADD_ALL_RECUR		"ZipWorksNT@ZW_FileAddAllRecur, Add all open files recursively to zip file"
#define		ZW_EXPORT_PASSWORD			"ZipWorksNT@ZW_Password, Enter password for zip file"
#define		ZW_EXPORT_COMPRESSION		"ZipWorksNT@ZW_Compression, Specify level of data compression"
#define		ZW_EXPORT_NULL				""
#define		ZW_EXPORT_REGISTER			"ZipWorksNT@ZW_Register@ZW_RegisterUpdate, Enter software registration code"
#define		ZW_EXPORT_ABOUT				"ZipWorksNT@ZW_About, Program information"
#define		ZW_EXPORT_HELP				"ZipWorksNT@ZW_Help, Browse online help file"
#else
#define		ZW_EXPORT_FILE_NAME			"ZipWorks95@ZW_FileName, Specify zip file name"
#define		ZW_EXPORT_OPTIONS			"ZipWorks95@ZW_Options, Set options for zip file"
#define		ZW_EXPORT_ADD				"ZipWorks95@ZW_FileAdd, Add current file to zip file"
#define		ZW_EXPORT_ADD_RECUR			"ZipWorks95@ZW_FileAddRecur, Add current file recursively to zip file"
#define		ZW_EXPORT_ADD_ALL			"ZipWorks95@ZW_FileAddAll, Add all open files to zip file"
#define		ZW_EXPORT_ADD_ALL_RECUR		"ZipWorks95@ZW_FileAddAllRecur, Add all open files recursively to zip file"
#define		ZW_EXPORT_PASSWORD			"ZipWorks95@ZW_Password, Enter password for zip file"
#define		ZW_EXPORT_COMPRESSION		"ZipWorks95@ZW_Compression, Specify level of data compression"
#define		ZW_EXPORT_NULL				""
#define		ZW_EXPORT_REGISTER			"ZipWorks95@ZW_Register@ZW_RegisterUpdate, Enter software registration code"
#define		ZW_EXPORT_ABOUT				"ZipWorks95@ZW_About, Program information"
#define		ZW_EXPORT_HELP				"ZipWorks95@ZW_Help, Browse online help file"
#endif
// --------------------------------
//  Class: CZipWorksApp
// --------------------------------

class CZipWorksApp : public CObject
{
private:
	bool m_bPartMenu;
	bool m_bAssemblyMenu;
	bool m_bDrawingMenu;

	CObList m_EventList;

public:
	//  constructor/destructor
	CZipWorksApp(LPSLDWORKS pSldWorks);
	~CZipWorksApp();

	// data members
	LPSLDWORKS m_pSldWorks;
	LPMODELDOC m_pActiveDoc;

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
extern CZipWorksApp* TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------


