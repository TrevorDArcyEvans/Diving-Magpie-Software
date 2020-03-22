// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CDiffWorksApp class which is the
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

#include "DMS_DiffWks.h"
#include "DMS_ProgPipe.h"

// --------------------------------
//  Class: CDiffWorksApp
// --------------------------------

class CDiffWorksApp : public CObject
{
private:
    // data members
    LPSLDWORKS                          m_pSldWorks;
    LPMODELDOC                          m_pActiveDoc;

    bool                                m_bMainMenu;
    bool                                m_bPartMenu;
    bool                                m_bAssemblyMenu;
    bool                                m_bDrawingMenu;

    CObList                             m_EventList;

    HINSTANCE                           m_hSaveInst;

public:
    //  constructor/destructor
    CDiffWorksApp(LPSLDWORKS pSldWorks);
    ~CDiffWorksApp();

    // functionality

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
    LPSLDWORKS GetSWApp(void) { return m_pSldWorks;}
    void SetResource();
    void ResetResource();

    // events
    void AddEvent(CObject* swEventHandler);
    bool RemoveEvent(CObject* swEventHandler);

    CObList& GetEventList() {return m_EventList;}

    CComPtr<IDMS_DiffWorks>             m_DMS_DiffWks;
    CComPtr<IDMS_ProgPipe>              m_DMS_ProgPipe;

private:
    void docCreateMenu(long DocumentType);
    void docRemoveMenu(long DocumentType);
};

// the application object
extern CDiffWorksApp*           TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------


