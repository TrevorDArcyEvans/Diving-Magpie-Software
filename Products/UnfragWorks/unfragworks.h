// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	UnfragWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif

#define UNFRAG_WORKS_TITLE_CODE             "UnfragWorks v2.x"
#define UNFRAG_WORKS_TITLE                  _T("UnfragWorks v2.1")

#define UNFRAG_WORKS_INI_FILE_NAME          _T("UnfragWorks.ini")

#define UNFRAG_WORKS_INI_FILE_SECTION       _T("Security")
#define UNFRAG_WORKS_INI_FILE_KEY           _T("code")

#define	UW_EXE_NAME                         _T("UnfragWorks.exe")
#define	UW_PASSWD						    _T("trevorde")

#define	UW_MAX_UNREG                5

#define SW_TOOLS                    "&Tools"

#define UW_MENU                     "&UnfragWorks...@&SolidPartners"
#define SP_MENU                     "&SolidPartners"

#ifdef _UNICODE
#define	UW_DLL_NAME			        "UnfragWorksNT.dll"
#else
#define	UW_DLL_NAME			        "UnfragWorks95.dll"
#endif

#define	UW_MENU_ITEM_REGISTER       "&Register..."
#define	UW_EXPORT_REGISTER_STR      "%s@%s@%s, Enter software registration code"
#define	UW_EXPORT_REGISTER          "UW_Register"
#define	UW_EXPORT_REGISTER_UPDATE   "UW_RegisterUpdate"

#define	UW_MENU_ITEM_CONFIG         "&Configure..."
#define	UW_EXPORT_CONFIG_STR        "%s@%s, Set UnfragWorks options"
#define	UW_EXPORT_CONFIG            "UW_Config"

#define	UW_MENU_ITEM_HELP           "&Help..."
#define	UW_EXPORT_HELP_STR          "%s@%s, Browse help file..."
#define	UW_EXPORT_HELP              "UW_Help"

#define	UW_MENU_ITEM_ABOUT          "&About..."
#define	UW_EXPORT_ABOUT_STR	        "%s@%s, Display program information"
#define	UW_EXPORT_ABOUT				"UW_About"



GLOBAL  bool		g_bRegistered;
GLOBAL  INT		    g_nTimesUsed;
GLOBAL  INT		    g_nTimeOut;

void DoProgramExecute(_TCHAR *CmdLine);

void DllExport UW_About(void);
void DllExport UW_Help(void);
void DllExport UW_Register(void);
int  DllExport UW_RegisterUpdate(void);
void DllExport UW_Config(void);

#endif
