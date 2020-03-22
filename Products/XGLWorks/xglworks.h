// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	XGLWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

#define          XGL_WORKS_TITLE_CODE           "XGLWorks v1.x"
#define          XGL_WORKS_TITLE                _T("XGLWorks v1.0")
#define          XGL_WORKS_INI_FILE_NAME        "XGLWks.ini"


#define         SP_MENU                         "&SolidPartners"
#define         XGL_MENU                        "&XGLWorks...@&SolidPartners"
#define         XGL_MENU_ITEM_RWWEB             "&RealityWave site"
#define         XGL_MENU_ITEM_REGISTER          "&Register..."
#define         XGL_MENU_ITEM_HELP              "&Help..."
#define         XGL_MENU_ITEM_ABOUT             "&About..."

#define         XGL_OPEN_DESCRIP                "xgl\nXGL files (*.xgl)"
#define         ZGL_OPEN_DESCRIP                "zgl\nZGL files (*.zgl)"

#ifdef _UNICODE
#define         XGL_DLL_NAME                    _T("XGLWksNT.dll")

#define         XGL_EXPORT_OPEN                 "XGLWksNT@XGL_OpenFile"
#define         XGL_EXPORT_RWWEB                "XGLWksNT@XGL_RealityWave, Visit RealityWave web site"
#define         XGL_EXPORT_REGISTER             "XGLWksNT@XGL_Register@XGL_RegisterUpdate, Enter software registration code"
#define         XGL_EXPORT_HELP                 "XGLWksNT@XGL_Help, Browse help file..."
#define         XGL_EXPORT_ABOUT                "XGLWksNT@XGL_About, Display program information"

#else
#define         XGL_DLL_NAME                    _T("XGLWks95.dll")

#define         XGL_EXPORT_OPEN                 "XGLWks95@XGL_OpenFile"
#define         XGL_EXPORT_RWWEB                "XGLWks95GL_RealityWave, Visit RealityWave web site"
#define         XGL_EXPORT_REGISTER             "XGLWks95@XGL_Register@XGL_RegisterUpdate, Enter software registration code"
#define         XGL_EXPORT_HELP                 "XGLWks95@XGL_Help, Browse help file..."
#define         XGL_EXPORT_ABOUT                "XGLWks95@XGL_About, Display program information"
#endif

//------------------------------------------------------------------------
