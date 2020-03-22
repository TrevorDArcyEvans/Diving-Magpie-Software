// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	PNGWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif



#define         PNG_WORKS_TITLE_CODE           "PNGWorks v1.x"
#define         PNG_WORKS_TITLE                _T("PNGWorks v1.0")
#define         PNG_WORKS_INI_FILE_NAME        "PNGWks.ini"


#define         SP_MENU                         "&SolidPartners"
#define         PNG_MENU                        "&PNGWorks...@&SolidPartners"
#define         PNG_MENU_ITEM_CONFIGURE         "&Configure..."
#define         PNG_MENU_ITEM_HELP              "&Help..."
#define         PNG_MENU_ITEM_ABOUT             "&About..."

#define         PNG_SAVE_AS_DESCRIP             "PNG\nPNG files (*.PNG)"

#ifdef _UNICODE
#define         PNG_DLL_NAME                    _T("PNGWksNT.dll")

#define         PNG_EXPORT_SAVE_AS              "PNGWksNT@PNG_SaveAs"
#define         PNG_EXPORT_CONFIGURE            "PNGWksNT@PNG_Configure"
#define         PNG_EXPORT_HELP                 "PNGWksNT@PNG_Help, Browse help file..."
#define         PNG_EXPORT_ABOUT                "PNGWksNT@PNG_About, Display program information"

#else
#define         PNG_DLL_NAME                    _T("PNGWks95.dll")

#define         PNG_EXPORT_SAVE_AS              "PNGWks95@PNG_SaveAs"
#define         PNG_EXPORT_CONFIGURE            "PNGWks95@PNG_Configure"
#define         PNG_EXPORT_HELP                 "PNGWks95@PNG_Help, Browse help file..."
#define         PNG_EXPORT_ABOUT                "PNGWks95@PNG_About, Display program information"
#endif

//------------------------------------------------------------------------
