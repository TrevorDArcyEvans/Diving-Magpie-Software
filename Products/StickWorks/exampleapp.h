// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.h
//  Description: Implements the CStickWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#if !defined(EXAMPLEAPP_H)
#define EXAMPLEAPP_H

#if _MSC_VER >= 1000
#pragma once
#endif

#include <atlbase.h>

// SolidWorks includes
#include "SldWorks.h"

#include "StickWorks.h"
#include "DMS_Comm.h"
#include "DMS_StkWks.h"

// --------------------------------
//  Class: CStickWorksApp
// --------------------------------

class CStickWorksApp : public CObject
{
private:
    bool                        m_bPartMenu;
    bool                        m_bAssemblyMenu;
    bool                        m_bDrawingMenu;

    CObList                     m_EventList;

    CComPtr<IDMS_Common>        m_DMS_Comm;
    CComPtr<IDMS_StickWorks>    m_DMS_StkWks;

public:
    // data members
    LPSLDWORKS                  m_pSldWorks;
    LPMODELDOC                  m_pActiveDoc;

    //  constructor/destructor
    CStickWorksApp(LPSLDWORKS pSldWorks);
    ~CStickWorksApp();

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

    // events
    void AddEvent(CObject* swEventHandler);
    bool RemoveEvent(CObject* swEventHandler);

    CObList& GetEventList() {return m_EventList;}

    CComPtr<IDMS_Common>        get_DMS_Comm    () { return m_DMS_Comm; };
    CComPtr<IDMS_StickWorks>    get_DMS_StkWks  () { return m_DMS_StkWks; }

private:
    void docCreateMenu(long DocumentType);
    void docRemoveMenu(long DocumentType);
};

// the application object
extern CStickWorksApp*          TheApplication;

#endif

// --------------------------------
//  End of ExampleApp.h
// --------------------------------


