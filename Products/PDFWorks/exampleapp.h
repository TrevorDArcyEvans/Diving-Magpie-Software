// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CPDFWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#if !defined(EXAMPLEAPP_H)
#define EXAMPLEAPP_H

#if _MSC_VER >= 1000
#pragma once
#endif

// SolidWorks includes
#include "SldWorks.h"

// --------------------------------
//  Class: CPDFWorksApp
// --------------------------------

class CPDFWorksApp : public CObject
{
private:
    // data members
    LPSLDWORKS      m_pSldWorks;
    LPMODELDOC      m_pActiveDoc;

    bool            m_bPartMenu;
    bool            m_bAssemblyMenu;
    bool            m_bDrawingMenu;

    CObList         m_EventList;

public:
    //  constructor/destructor
    CPDFWorksApp(LPSLDWORKS pSldWorks);
    ~CPDFWorksApp();

    // load/unload application
    bool StartApplication(void);
    void TerminateApplication(void);

    // menus
    void AddMenus(void);
    void RemoveMenus(void);

    // helper
    void ChangeActiveDoc(void);
    void DestroyDoc(LPMODELDOC DocBeingDestroyed);
    void SetSWApp(LPSLDWORKS pSldWorks);
    LPSLDWORKS GetSWApp();

    // events
    void AddEvent(CObject* swEventHandler);
    bool RemoveEvent(CObject* swEventHandler);

    CObList& GetEventList() {return m_EventList;}

private:
    void docCreateMenu(long DocumentType);
    void docRemoveMenu(long DocumentType);
};

// the application object
extern CPDFWorksApp* TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------

