// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:    JPGWorks.h
// Application: C++ Application Wizard
// Contents:    Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif


#define         JPG_WORKS_TITLE_CODE           "JPGWorks v1.x"
#define         JPG_WORKS_TITLE                _T("JPGWorks v1.0")
#define         JPG_WORKS_INI_FILE_NAME        "JPGWks.ini"


#define         SP_MENU                         "&SolidPartners"
#define         JPG_MENU                        "&JPGWorks...@&SolidPartners"
#define         JPG_MENU_ITEM_CONFIGURE         "&Configure..."
#define         JPG_MENU_ITEM_HELP              "&Help..."
#define         JPG_MENU_ITEM_ABOUT             "&About..."

#define         JPG_SAVE_AS_DESCRIP             "jpg\nJPEG files (*.jpg)"

#ifdef _UNICODE
#define         JPG_DLL_NAME                    _T("JPGWksNT.dll")

#define         JPG_EXPORT_SAVE_AS              "JPGWksNT@JPG_SaveAs"
#define         JPG_EXPORT_CONFIGURE            "JPGWksNT@JPG_Configure"
#define         JPG_EXPORT_HELP                 "JPGWksNT@JPG_Help, Browse help file..."
#define         JPG_EXPORT_ABOUT                "JPGWksNT@JPG_About, Display program information"

#else
#define         JPG_DLL_NAME                    _T("JPGWks95.dll")

#define         JPG_EXPORT_SAVE_AS              "JPGWks95@JPG_SaveAs"
#define         JPG_EXPORT_CONFIGURE            "JPGWks95@JPG_Configure"
#define         JPG_EXPORT_HELP                 "JPGWks95@JPG_Help, Browse help file..."
#define         JPG_EXPORT_ABOUT                "JPGWks95@JPG_About, Display program information"
#endif

//------------------------------------------------------------------------
