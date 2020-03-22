// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	ViewWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )


#include "SldWorks.h"
//---------------------------------------------------------------------------

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL      extern
#endif

//---------------------------------------------------------------------------

#define     VIEW_WORKS_TITLE_CODE              "ViewWorks v1.x"
#define     VIEW_WORKS_TITLE                   _T("ViewWorks v1.0")


#define     VIEW_WORKS_INI_FILE_NAME           _T("ViewWorks.ini")

#define     VIEW_WORKS_INI_FILE_SECTION        _T("CU_Security")
#define     VIEW_WORKS_INI_FILE_KEY            _T("code")

#define     MAX_UNREG_VIEW_SAVES                5

//---------------------------------------------------------------------------

GLOBAL      bool            g_bRegistered;
GLOBAL      int             g_nViewSaveCount;

//---------------------------------------------------------------------------
void DllExport VW_SaveAsView(LPTSTR FileName, LPSLDWORKS pSolidWorks);
void DllExport VW_OpenView  (LPTSTR FileName, LPSLDWORKS pSolidWorks);
void DllExport VW_Help(void);
void DllExport VW_Register(void);
int  DllExport VW_RegisterUpdate(void);
void DllExport VW_About(void);

#endif
