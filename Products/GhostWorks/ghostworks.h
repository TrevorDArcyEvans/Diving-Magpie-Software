// ========================================================================
//
//                  Copyright 1997 (Unpublished material)
//                          SolidWorks Corporation
//
// ========================================================================
//
// Filename:	GhostWorks.h
// Application:	C++ Application Wizard
// Contents:	Main entry point declaration
// ========================================================================

#ifndef DllExport

#define DllExport __declspec( dllexport )

#endif

//------------------------------------------------------------------------
// Forward definitions
class CFMView;                  // The class that controls our Feature Manager Tab
class CFMTreeCtrl;              // SubClass of CTreeCtrl for the Tree Control
class FMFeatureManagerEvents;   // Handles Feature Manager Notifications


// Call this function whenever a new window is created to add
// our custom TAB to the Feature Manager View
extern CFMView* CreateFeatureManagerView(bool bCreateView);
//------------------------------------------------------------------------


#define         GHOST_WORKS_TITLE_CODE           "GhostWorks v1.x"
#define         GHOST_WORKS_TITLE                _T("GhostWorks v1.0")
#define         GHOST_WORKS_INI_FILE_NAME        "GhostWks.ini"


#define         SP_MENU                          "&SolidPartners"
#define         GHOST_MENU                       "&GhostWorks...@&SolidPartners"
#define         GHOST_MENU_ITEM_HELP             "&Help..."
#define         GHOST_MENU_ITEM_ABOUT            "&About..."

#ifdef _UNICODE
#define         GHOST_DLL_NAME                   _T("GhostWksNT.dll")

#define         GHOST_EXPORT_HELP                "GhostWksNT@Ghost_Help, Browse help file..."
#define         GHOST_EXPORT_ABOUT               "GhostWksNT@Ghost_About, Display program information"

#else
#define         GHOST_DLL_NAME                   _T("GhostWks95.dll")

#define         GHOST_EXPORT_HELP                "GhostWks95@Ghost_Help, Browse help file..."
#define         GHOST_EXPORT_ABOUT               "GhostWks95@Ghost_About, Display program information"
#endif

//------------------------------------------------------------------------
