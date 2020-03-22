// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:    BundleWorks.h
// Application:    C++ Application Wizard
// Contents:    Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

//---------------------------------------------------------------------------

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL      extern
#endif

//---------------------------------------------------------------------------

#define     BUN_WORKS_TITLE_CODE                "BundleWorks v1.x"
#define     BUN_WORKS_TITLE                     _T("BundleWorks v1.0")


#define     BUN_WORKS_INI_FILE_NAME             _T("BunWorks.ini")

#define     BUN_WORKS_INI_FILE_SECTION          _T("Security")
#define     BUN_WORKS_INI_FILE_KEY              _T("code")

#define     BUN_WORKS_INI_FILE_PREFS_SECT       _T("Prefs")
#define     BUN_WORKS_INI_FILE_RECURSE          _T("recurse")
#define     BUN_WORKS_INI_FILE_DIRSTRUCT        _T("DirStruct")


#define     MAX_UNREG_BUNDLE_SAVES              5

#define     BUN_WORKS_MENU                      "&BundleWorks...@&SolidPartners"
#define     SP_MENU                             "&SolidPartners"


#ifdef _UNICODE
#define     BUN_WORKS_DLL_NAME                  "BunWksNT.dll"
#define	    BUN_WORKS_EXPORT_SAVE_AS   		    "BunWksNT.dll@BunWks_SaveAsZip"
#define	    BUN_WORKS_EXPORT_OPEN_AS   		    "BunWksNT.dll@BunWks_OpenZip"
#else
#define     BUN_WORKS_DLL_NAME                  "BunWks95.dll"
#define	    BUN_WORKS_EXPORT_SAVE_AS   		    "BunWks95.dll@BunWks_SaveAsZip"
#define	    BUN_WORKS_EXPORT_OPEN_AS   		    "BunWks95.dll@BunWks_OpenZip"
#endif

//---------------------------------------------------------------------------

#define	    BUN_WORKS_DESCRIP_PRT              "zip\nzip files (*.zip)"
#define	    BUN_WORKS_DESCRIP_ASM              "zip\nzip files (*.zip)"
#define	    BUN_WORKS_DESCRIP_DRW              "zip\nzip files (*.zip)"


#define     BUN_WORKS_MENU_ITEM_RECURSE         "R&ecurse assembly/drawing"
#define     BUN_WORKS_EXPORT_RECURSE_STR        "%s@%s@%s, Add all sub-assemblies and parts"
#define     BUN_WORKS_EXPORT_RECURSE            "BunWks_Recurse"
#define     BUN_WORKS_EXPORT_RECURSE_UPDATE     "BunWks_RecurseUpdate"

#define     BUN_WORKS_MENU_ITEM_DIRSTRUCT       "&Preserve directories"
#define     BUN_WORKS_EXPORT_DIRSTRUCT_STR      "%s@%s@%s, Keep directory structure"
#define     BUN_WORKS_EXPORT_DIRSTRUCT          "BunWks_DirStruct"
#define     BUN_WORKS_EXPORT_DIRSTRUCT_UPDATE   "BunWks_DirStructUpdate"

#define     BUN_WORKS_MENU_ITEM_REGISTER        "&Register..."
#define     BUN_WORKS_EXPORT_REGISTER_STR       "%s@%s@%s, Enter software registration code"
#define     BUN_WORKS_EXPORT_REGISTER           "BunWks_Register"
#define     BUN_WORKS_EXPORT_REGISTER_UPDATE    "BunWks_RegisterUpdate"

#define     BUN_WORKS_MENU_ITEM_HELP            "&Help..."
#define     BUN_WORKS_EXPORT_HELP_STR           "%s@%s, Browse help file..."
#define     BUN_WORKS_EXPORT_HELP               "BunWks_Help"

#define     BUN_WORKS_MENU_ITEM_ABOUT           "&About..."
#define     BUN_WORKS_EXPORT_ABOUT_STR          "%s@%s, Display program information"
#define     BUN_WORKS_EXPORT_ABOUT              "BunWks_About"

#define     BUN_WORKS_MAX_UNREG                 5

//---------------------------------------------------------------------------

GLOBAL      bool            g_bRegistered;
GLOBAL      int             g_nBundleSaveCount;

//---------------------------------------------------------------------------

#endif
