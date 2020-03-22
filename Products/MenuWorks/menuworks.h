// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:    MenuWorks.h
// Application:    C++ Application Wizard
// Contents:    Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif

#define MENU_WORKS_TITLE_CODE               "MenuWorks v2.x"
#define MENU_WORKS_TITLE                    _T("MenuWorks v2.1")

#define MENU_WORKS_INI_FILE_NAME            _T("MenuWorks.ini")
#define MENU_WORKS_MAIN                     _T("CU_Main")
#define MENU_WORKS_MAIN_TITLE               _T("Title")

#define MENU_WORKS_INI_FILE_SECTION         _T("CU_Security")
#define MENU_WORKS_INI_FILE_KEY             _T("code")

#define	SP_MENU						        "&SolidPartners"
#define	MW_MENU						        "&MenuWorks...@&SolidPartners"

#define    MW_MENU_ITEM_REGISTER           "&Register..."
#define    MW_MENU_ITEM_CONFIG             "&Configure..."
#define    MW_MENU_ITEM_ABOUT              "&About..."
#define    MW_MENU_ITEM_HELP               "&Help..."

#ifdef _UNICODE
#define    MW_DLL_NAME                      _T("MenuWorksNT.dll")
#define    MW_MAIN_DLL_NAME                 _T("MenuWorksNT")

#define    MW_EXPORT_REGISTER              "MenuWorksNT@MW_Register@MW_RegisterUpdate, Enter software registration code"
#define    MW_EXPORT_CONFIG                "MenuWorksNT@MW_Config, Configure menu items and hints"
#define    MW_EXPORT_ABOUT                 "MenuWorksNT@MW_About, Program information"
#define    MW_EXPORT_HELP                  "MenuWorksNT@MW_Help, Browse online help file"
#else
#define    MW_DLL_NAME                      _T("MenuWorks95.dll")
#define    MW_MAIN_DLL_NAME                 _T("MenuWorks95")

#define    MW_EXPORT_REGISTER              "MenuWorks95@MW_Register@MW_RegisterUpdate, Enter software registration code"
#define    MW_EXPORT_CONFIG                "MenuWorks95@MW_Config, Configure menu items and hints"
#define    MW_EXPORT_ABOUT                 "MenuWorks95@MW_About, Program information"
#define    MW_EXPORT_HELP                  "MenuWorks95@MW_Help, Browse online help file"
#endif

#define MENU_WORKS_MAX_MENUS                10
#define MENU_WORKS_MIN_MENUS                2

GLOBAL  struct  MenuStruct
    {
    _TCHAR    ProgName[512];
    _TCHAR    MenuText[512];
    _TCHAR    HintText[512];
    } MenuItem[MENU_WORKS_MAX_MENUS];

GLOBAL  _TCHAR      g_MainMenuName[512];
GLOBAL  bool        g_bRegistered;
GLOBAL  int         g_nMaxMenus;

void DoProgramExecute(_TCHAR *ProgName);

void DllExport ProgExec0(void);
void DllExport ProgExec1(void);
void DllExport ProgExec2(void);
void DllExport ProgExec3(void);
void DllExport ProgExec4(void);
void DllExport ProgExec5(void);
void DllExport ProgExec6(void);
void DllExport ProgExec7(void);
void DllExport ProgExec8(void);
void DllExport ProgExec9(void);

void DllExport MW_About(void);
void DllExport MW_Help(void);
void DllExport MW_Register(void);
int  DllExport MW_RegisterUpdate(void);

#endif

