// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	STLWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

#define          STL_WORKS_TITLE_CODE           "STLWorks v1.x"
#define          STL_WORKS_TITLE                _T("STLWorks v1.0")
#define          STL_WORKS_INI_FILE_NAME        "STLWks.ini"


#define         SP_MENU                         "&SolidPartners"
#define         STL_MENU                        "&STLWorks...@&SolidPartners"
#define         STL_MENU_ITEM_REGISTER          "&Register..."
#define         STL_MENU_ITEM_HELP              "&Help..."
#define         STL_MENU_ITEM_ABOUT             "&About..."

#define         STL_OPEN_DESCRIP                "stl\nSTL files (*.stl)"

#ifdef _UNICODE
#define         STL_DLL_NAME                    _T("STLWksNT.dll")

#define         STL_EXPORT_OPEN                 "STLWksNT@STL_OpenFile"
#define         STL_EXPORT_REGISTER             "STLWksNT@STL_Register@STL_RegisterUpdate, Enter software registration code"
#define         STL_EXPORT_HELP                 "STLWksNT@STL_Help, Browse help file..."
#define         STL_EXPORT_ABOUT                "STLWksNT@STL_About, Display program information"

#else
#define         STL_DLL_NAME                    _T("STLWks95.dll")

#define         STL_EXPORT_OPEN                 "STLWks95@STL_OpenFile"
#define         STL_EXPORT_REGISTER             "STLWks95@STL_Register@STL_RegisterUpdate, Enter software registration code"
#define         STL_EXPORT_HELP                 "STLWks95@STL_Help, Browse help file..."
#define         STL_EXPORT_ABOUT                "STLWks95@STL_About, Display program information"
#endif

//------------------------------------------------------------------------
