// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	ZipWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

#define     ZIP_WORKS_TITLE_CODE          "ZipWorks v2.x"
#define     ZIP_WORKS_TITLE               "ZipWorks v2.0"

#ifdef _UNICODE
#define     ZIP_WORKS_INI_FILE_NAME       _T("C:\\Program Files\\SolidPartners\\ZipWorks\\ZipWorks.ini")
#else
#define     ZIP_WORKS_INI_FILE_NAME       _T("C:\\Program Files\\SolidPartners\\ZipWorks\\ZipWorks.ini")
#endif

#define     ZIP_WORKS_INI_FILE_SECTION    _T("Security")
#define     ZIP_WORKS_INI_FILE_KEY        _T("code")

#ifdef MAIN
#define     GLOBAL
#else
#define     GLOBAL              extern
#endif

GLOBAL      bool    g_bRegistered   ;
GLOBAL      bool    g_bRunning      ;
GLOBAL      long    g_lDateCode     ;


extern CString		cstrFileName;
