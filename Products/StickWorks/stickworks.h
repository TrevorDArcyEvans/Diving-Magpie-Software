// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	StickWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
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

#define     STICK_WORKS_TITLE_CODE              "StickWorks v3.x"
#define     STICK_WORKS_TITLE                   _T("StickWorks v3.0")


#define     STICK_WORKS_INI_FILE_NAME           _T("StkWorks.ini")

#define     STICK_WORKS_INI_FILE_SECTION        _T("Security")
#define     STICK_WORKS_INI_FILE_KEY            _T("code")

#define     STICK_WORKS_INI_SECTION_CONFIG      _T("Config")
#define     STICK_WORKS_INI_KEY_THRESHOLD       _T("Threshold")
#define     STICK_WORKS_INI_KEY_SENSITIVITY     _T("Sensitivity")

//---------------------------------------------------------------------------

#define SP_MENU                     "&SolidPartners"
#define SW_MENU                     "&StickWorks...@&SolidPartners"
#define SW_MENU_ITEM_CONFIG         "&Configure..."
#define SW_MENU_ITEM_CALIBRATE      "Ca&librate..."
#define SW_MENU_ITEM_REGISTER       "&Register..."
#define SW_MENU_ITEM_HELP           "&Help..."
#define SW_MENU_ITEM_ABOUT          "&About..."

#ifdef _UNICODE
#define SW_DLL_NAME                 _T("StkWksNT.dll")

#define SW_EXPORT_CONFIG            "StkWksNT@SW_Config, Configure StickWorks"
#define SW_EXPORT_CALIBRATE         "StkWksNT@SW_Calibrate, Calibrate joystick"
#define SW_EXPORT_HELP              "StkWksNT@SW_Help, Browse help file..."
#define SW_EXPORT_REGISTER          "StkWksNT@SW_Register@SW_RegisterUpdate, Enter software registration code"
#define SW_EXPORT_ABOUT             "StkWksNT@SW_About, Display program information"
#else
#define SW_DLL_NAME                 _T("StkWks95.dll")

#define SW_EXPORT_CONFIG            "StkWks95@SW_Config, Configure StickWorks"
#define SW_EXPORT_CALIBRATE         "StkWks95@SW_Calibrate, Calibrate joystick"
#define SW_EXPORT_REGISTER          "StkWks95@SW_Register@SW_RegisterUpdate, Enter software registration code"
#define SW_EXPORT_HELP              "StkWks95@SW_Help, Browse help file..."
#define SW_EXPORT_ABOUT             "StkWks95@SW_About, Display program information"
#endif

//---------------------------------------------------------------------------

GLOBAL      JOYCAPS         g_jcJoyCaps;
GLOBAL      UINT            g_uJoyTimerID, g_uRegTimerID, g_uJoyPanelTimerID;
GLOBAL      bool            g_bCtrlDown, g_bEscDown,
                            g_bRegistered, g_bJoystickPanelShowing;
GLOBAL      int             g_nThreshold, g_nSensitivity;


//---------------------------------------------------------------------------


#endif
