// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	WinWks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif


#define WINDOW_WORKS_TITLE                  _T("WindowWorks v1.0")
#define WINDOW_WORKS_TITLE_CODE             "WindowWorks v1.x"

#define WINDOW_WORKS_INI_FILE_NAME          _T("WinWks.ini")

#define WINDOW_WORKS_INI_FILE_SECTION       _T("Security")
#define WINDOW_WORKS_INI_FILE_KEY           _T("code")


#define WW_MENU                     "&WindowWorks...@&SolidPartners"
#define SP_MENU                     "&SolidPartners"

#define SAVE_ALL_MENU               "Sav&e All@&File"

#ifdef _UNICODE
#define	WW_DLL_NAME			        "WinWksNT.dll"
#else
#define	WW_DLL_NAME			        "WinWks95.dll"
#endif

#define	WW_MENU_ITEM_CLOSE_ALL      "Close Al&l@&Window"
#define	WW_EXPORT_CLOSE_ALL_STR     "%s@%s, Close all open windows"
#define	WW_EXPORT_CLOSE_ALL         "WW_CloseAll"

#define	WW_MENU_ITEM_SAVE_ALL       "Sav&e All@&File"
#define	WW_EXPORT_SAVE_ALL_STR      "%s@%s, Save all files"
#define	WW_EXPORT_SAVE_ALL          "WW_SaveAll"

#define	WW_MENU_ITEM_REGISTER       "&Register..."
#define	WW_EXPORT_REGISTER_STR      "%s@%s@%s, Enter software registration code"
#define	WW_EXPORT_REGISTER          "WW_Register"
#define	WW_EXPORT_REGISTER_UPDATE   "WW_RegisterUpdate"

#define	WW_MENU_ITEM_HELP           "&Help..."
#define	WW_EXPORT_HELP_STR          "%s@%s, Browse help file..."
#define	WW_EXPORT_HELP              "WW_Help"

#define	WW_MENU_ITEM_ABOUT          "&About..."
#define	WW_EXPORT_ABOUT_STR	        "%s@%s, Display program information"
#define	WW_EXPORT_ABOUT				"WW_About"

#define	WW_MAX_UNREG                5

GLOBAL  bool		g_bRegistered;
GLOBAL  INT		    g_nTimesUsed;

