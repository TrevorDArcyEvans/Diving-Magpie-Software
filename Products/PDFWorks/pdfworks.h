// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:    PDFWorks.h
// Application:    C++ Application Wizard
// Contents:    Main entry point declaration
// ========================================================================


//---------------------------------------------------------------------------

#include "SldWorks.h"
#include <atlbase.h>
#include "DMS_PDFWks.h"

typedef tagPDF_Setup            PDF_Setup;
typedef tagPDF_PAPER_SIZE       PDF_PAPER_SIZE;
typedef tagPDF_UNITS            PDF_UNITS;

//---------------------------------------------------------------------------

#ifndef DllExport

#define DllExport __declspec( dllexport )
//---------------------------------------------------------------------------

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL      extern
#endif

//---------------------------------------------------------------------------

#define         PDF_WORKS_TITLE_CODE        "PDFWorks v1.x"
#define         PDF_WORKS_TITLE             _T("PDFWorks v1.0")


#define         PDF_WORKS_INI_FILE_NAME     _T("PDFWorks.ini")

#define         PDF_WORKS_INI_FILE_SECTION  _T("CU_Security")
#define         PDF_WORKS_INI_FILE_KEY      _T("code")

#define         MAX_UNREG_PDF_SAVES          5

#define         SP_MENU                     "&SolidPartners"
#define         PDF_MENU                    "&PDFWorks...@&SolidPartners"
#define         PDF_MENU_ITEM_CONFIGURE     "&Configure..."
#define         PDF_MENU_ITEM_REGISTER      "&Register..."
#define         PDF_MENU_ITEM_HELP          "&Help..."
#define         PDF_MENU_ITEM_ABOUT         "&About..."

#ifdef _UNICODE
#define         PDF_DLL_NAME                _T("PDFWorksNT.dll")

#ifdef PDF_LIB
#define         PDF_EXPORT_SAVE_AS          "PDFWorksNT@PDF_SaveAsPDF"
#else
#define         PDF_EXPORT_SAVE_AS          "PDFWorksNT@Amyuni_SaveAsPDF"
#endif

#define         PDF_EXPORT_CONFIGURE        "PDFWorksNT@PDF_Configure, Change PDF output settings"
#define         PDF_EXPORT_REGISTER         "PDFWorksNT@PDF_Register@PDF_RegisterUpdate, Enter software registration code"
#define         PDF_EXPORT_HELP             "PDFWorksNT@PDF_Help, Browse help file..."
#define         PDF_EXPORT_ABOUT            "PDFWorksNT@PDF_About, Display program information"
#else
#define         PDF_DLL_NAME                _T("PDFWorks95.dll")

#ifdef PDF_LIB
#define         PDF_EXPORT_SAVE_AS          "PDFWorks95@PDF_SaveAsPDF"
#else
#define         PDF_EXPORT_SAVE_AS          "PDFWorks95@Amyuni_SaveAsPDF"
#endif

#define         PDF_EXPORT_CONFIGURE        "PDFWorks95@PDF_Configure, Change PDF output settings"
#define         PDF_EXPORT_REGISTER         "PDFWorks95@PDF_Register@PDF_RegisterUpdate, Enter software registration code"
#define         PDF_EXPORT_HELP             "PDFWorks95@PDF_Help, Browse help file..."
#define         PDF_EXPORT_ABOUT            "PDFWorks95@PDF_About, Display program information"
#endif


//---------------------------------------------------------------------------

GLOBAL      int             g_bRegistered;
GLOBAL      int             g_nPDFSaveCount;
GLOBAL      PDF_Setup       m_PDF_Setup;

//---------------------------------------------------------------------------

void DllExport PDF_SaveAsPDF(LPTSTR FileName, LPSLDWORKS pSolidWorks);
void DllExport PDF_Configure        (void);
void DllExport PDF_Help             (void);
void DllExport PDF_Register         (void);
int  DllExport PDF_RegisterUpdate   (void);
void DllExport PDF_About            (void);

//---------------------------------------------------------------------------

#endif

