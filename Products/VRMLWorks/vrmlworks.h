// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	VRMLWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

#define         VRML_WORKS_TITLE_CODE           "VRMLWorks v1.x"
#define         VRML_WORKS_TITLE                _T("VRMLWorks v1.0")
#define         VRML_WORKS_INI_FILE_NAME        "VRMLWks.ini"


#define         SP_MENU                         "&SolidPartners"
#define         VRML_MENU                       "&VRMLWorks...@&SolidPartners"
#define         VRML_MENU_ITEM_REGISTER         "&Register..."
#define         VRML_MENU_ITEM_HELP             "&Help..."
#define         VRML_MENU_ITEM_ABOUT            "&About..."

#define         VRML_OPEN_DESCRIP               "wrl\nVRML files (*.wrl)"

#ifdef _UNICODE
#define         VRML_DLL_NAME                   _T("VRMLWksNT.dll")

#define         VRML_EXPORT_OPEN                "VRMLWksNT@VRML_OpenFile"
#define         VRML_EXPORT_REGISTER            "VRMLWksNT@VRML_Register@VRML_RegisterUpdate, Enter software registration code"
#define         VRML_EXPORT_HELP                "VRMLWksNT@VRML_Help, Browse help file..."
#define         VRML_EXPORT_ABOUT               "VRMLWksNT@VRML_About, Display program information"

#else
#define         VRML_DLL_NAME                   _T("VRMLWks95.dll")

#define         VRML_EXPORT_OPEN                "VRMLWks95@VRML_OpenFile"
#define         VRML_EXPORT_REGISTER            "VRMLWks95@VRML_Register@VRML_RegisterUpdate, Enter software registration code"
#define         VRML_EXPORT_HELP                "VRMLWks95@VRML_Help, Browse help file..."
#define         VRML_EXPORT_ABOUT               "VRMLWks95@VRML_About, Display program information"
#endif

//------------------------------------------------------------------------
