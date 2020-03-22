// ========================================================================
//
// Filename:	DiffWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

#define         DIFF_WORKS_TITLE_CODE           "DiffWorks v1.x"
#define         DIFF_WORKS_TITLE                _T("DiffWorks v1.0")
#define         DIFF_WORKS_INI_FILE_NAME        "DiffWks.ini"


#define         SP_MENU                          "&SolidPartners"
#define         DIFF_MENU                       "&DiffWorks...@&SolidPartners"
#define         DIFF_MENU_ITEM_COMPARE          "F&ind differences..."
#define         DIFF_MENU_ITEM_SHOW             "Show &last results"
#define         DIFF_MENU_ITEM_REGISTER         "&Register..."
#define         DIFF_MENU_ITEM_HELP             "&Help..."
#define         DIFF_MENU_ITEM_ABOUT            "&About..."

#ifdef _UNICODE
#define         DIFF_DLL_NAME                   _T("DiffWksNT.dll")

#define         DIFF_EXPORT_COMPARE             "DiffWksNT@DW_CompareFiles, Select files and show differences"
#define         DIFF_EXPORT_SHOW                "DiffWksNT@DW_ShowLast, Show results of last files compared"
#define         DIFF_EXPORT_REGISTER            "DiffWksNT@DW_Register@DW_RegisterUpdate, Enter software registration code"
#define         DIFF_EXPORT_HELP                "DiffWksNT@DW_Help, Browse help file..."
#define         DIFF_EXPORT_ABOUT               "DiffWksNT@DW_About, Display program information"

#else
#define         DIFF_DLL_NAME                   _T("DiffWks95.dll")

#define         DIFF_EXPORT_COMPARE             "DiffWks95@DW_CompareFiles, Select files and show differences"
#define         DIFF_EXPORT_SHOW                "DiffWks95@DW_ShowLast, Show results of last files compared"
#define         DIFF_EXPORT_REGISTER            "DiffWks95@DW_Register@DW_RegisterUpdate, Enter software registration code"
#define         DIFF_EXPORT_HELP                "DiffWks95@DW_Help, Browse help file..."
#define         DIFF_EXPORT_ABOUT               "DiffWks95@DW_About, Display program information"
#endif

//------------------------------------------------------------------------
