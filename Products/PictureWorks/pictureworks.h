// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	PictureWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#define	SP_MENU						"&SolidPartners"

#define	PW_MENU						"P&ictureWorks...@&SolidPartners"
#define	PW_MENU_ITEM_HELP           "&Help..."
#define	PW_MENU_ITEM_ABOUT			"&About..."

#ifdef _UNICODE
#define	PW_DLL_NAME			        _T("PictureWorksNT.dll")

#define	PW_EXPORT_COPY              "PictureWorksNT@PW_Copy, Copy bitmap image to clipboard"
#define	PW_EXPORT_HELP              "PictureWorksNT@PW_Help, Browse help file..."
#define	PW_EXPORT_ABOUT				"PictureWorksNT@PW_About, Display program information"
#else
#define	PW_DLL_NAME			        _T("PictureWorks95.dll")

#define	PW_EXPORT_COPY              "PictureWorks95@PW_Copy, Copy bitmap image to clipboard"
#define	PW_EXPORT_HELP              "PictureWorks95@PW_Help, Browse help file..."
#define	PW_EXPORT_ABOUT				"PictureWorks95@PW_About, Display program information"
#endif


#endif
