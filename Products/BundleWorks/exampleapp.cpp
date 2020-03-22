//$c01 JPS 06/17/98  Initialize m_pActiveDoc pointer
//
// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1997 (Unpublished material)
//
// -------------------------------------------------------------------
//
//     Filename: ExampleApp.cpp
//  Description: Implements the CBundleWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>
#include <comdef.h>

#include "BundleWorks.h"
#include "Resource.h"
#include "ExampleApp.h"
#include "HandleEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// --------------------------------
//  Constructor/Destructor
// --------------------------------

// the constructor and destructor are only called once per session
//
CBundleWorksApp::CBundleWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks = pSldWorks;
    m_pActiveDoc = NULL;

    // menus
    m_bPartMenu = FALSE;
    m_bAssemblyMenu = FALSE;
    m_bDrawingMenu = FALSE;

    m_bRecurse = TRUE;
    m_bDirStructure = TRUE;

    TCHAR   TempUStr[_MAX_PATH];

    GetPrivateProfileString(
            BUN_WORKS_INI_FILE_PREFS_SECT,
            BUN_WORKS_INI_FILE_RECURSE,
            _T("1"), // points to default string
            TempUStr, // points to destination buffer
            _MAX_PATH,        // size of destination buffer
            BUN_WORKS_INI_FILE_NAME);
    m_bRecurse = _ttoi(TempUStr);

    GetPrivateProfileString(
            BUN_WORKS_INI_FILE_PREFS_SECT,
            BUN_WORKS_INI_FILE_DIRSTRUCT,
            _T("1"), // points to default string
            TempUStr, // points to destination buffer
            _MAX_PATH,        // size of destination buffer
            BUN_WORKS_INI_FILE_NAME);
    m_bDirStructure = _ttoi(TempUStr);
}
// ----------------------------------------------------------------
CBundleWorksApp::~CBundleWorksApp()
{
    // default destructor
}

// --------------------------------
//  Load/Unload
// --------------------------------

bool CBundleWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
// ----------------------------------------------------------------
void CBundleWorksApp::TerminateApplication(void)
{
    // need this test because SW can terminate the app by
    // shutting down or by unloading it from the Add-In
    if (m_pSldWorks == NULL)
        return;

    // remove all menus
    RemoveMenus();

    // remove events - the event destructor removes
    // the object from the list
    int count = m_EventList.GetCount();
    for (int i=0; i<count; i++)
        {
         CObject* headEvent = m_EventList.GetHead();
         delete headEvent;            // destructor will remove it from list with RemoveAt(pos)
        }

    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // disconnect from SolidWorks
    m_pSldWorks->Release();
    m_pSldWorks = NULL;
}

// --------------------------------
//  menus
// --------------------------------

#define swMenuPosition  5    // add your menu after Tools and before Window
#define swLastPosition -1

//  Add a menu to the active document frame.  This is to be done
//  only ONCE for each document type.
//
void CBundleWorksApp::AddMenus(void)
{
    HRESULT         res, hres;
    VARIANT_BOOL    bres;

    if (NULL == m_bSWMenu)
        {
        // add file save-as item
        hres = m_pSldWorks->AddFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_PRT), swDocPART, &bres);

        hres = m_pSldWorks->AddFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_ASM), swDocASSEMBLY, &bres);

        hres = m_pSldWorks->AddFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_DRW), swDocDRAWING, &bres);

        // add file open item
        hres = m_pSldWorks->AddFileOpenItem(auT(BUN_WORKS_EXPORT_OPEN_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_PRT), &bres);

        m_bSWMenu = TRUE;
        }


    LPMODELDOC pModelDoc = NULL;
    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);

    if (pModelDoc != NULL)
        {
        // get the document type
        long doctype;
        res = pModelDoc->GetType(&doctype);

        if (doctype == swDocPART && m_bPartMenu == NULL)
            {
            docCreateMenu(doctype);
            m_bPartMenu = TRUE;
            }
        else if (doctype == swDocASSEMBLY && m_bAssemblyMenu == NULL)
            {
            docCreateMenu(doctype);
            m_bAssemblyMenu = TRUE;
            }
        else if (doctype == swDocDRAWING && m_bDrawingMenu == NULL)
            {
            docCreateMenu(doctype);
            m_bDrawingMenu = TRUE;
            }
        else
            return;

        // clean up
        pModelDoc->Release();
        }
}
// ----------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CBundleWorksApp::docCreateMenu(long DocumentType)
{
    HRESULT         hres;
    VARIANT_BOOL    bres;

    char            pcCallback[_MAX_PATH];

    LPFRAME         pFrame;

    hres = m_pSldWorks->IFrameObject(&pFrame);

    // try and add BundleWorks menu to top level SolidPartners menu
    hres = pFrame->AddMenu(auT(BUN_WORKS_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level SolidPartners menu item
        hres = pFrame->AddMenu(_bstr_t(SP_MENU), -1, &bres);


        // add BundleWorks menu
        hres = pFrame->AddMenu(auT(BUN_WORKS_MENU), swLastPosition, &bres);
        }


    // add BundleWorks Recurse menu item
    sprintf(pcCallback, BUN_WORKS_EXPORT_RECURSE_STR, BUN_WORKS_DLL_NAME,
        BUN_WORKS_EXPORT_RECURSE, BUN_WORKS_EXPORT_RECURSE_UPDATE);
    hres = pFrame->AddMenuItem(
                auT(BUN_WORKS_MENU), auT(BUN_WORKS_MENU_ITEM_RECURSE), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add BundleWorks Directory Structure menu item
    sprintf(pcCallback, BUN_WORKS_EXPORT_DIRSTRUCT_STR, BUN_WORKS_DLL_NAME,
        BUN_WORKS_EXPORT_DIRSTRUCT, BUN_WORKS_EXPORT_DIRSTRUCT_UPDATE);
    hres = pFrame->AddMenuItem(
                auT(BUN_WORKS_MENU), auT(BUN_WORKS_MENU_ITEM_DIRSTRUCT), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

	// add separator
	hres = pFrame->AddMenuItem(
					auT(BUN_WORKS_MENU), NULL, swLastPosition,
					NULL,
					&bres);

    // add BundleWorks Register menu item
    sprintf(pcCallback, BUN_WORKS_EXPORT_REGISTER_STR, BUN_WORKS_DLL_NAME,
        BUN_WORKS_EXPORT_REGISTER, BUN_WORKS_EXPORT_REGISTER_UPDATE);
    hres = pFrame->AddMenuItem(
                auT(BUN_WORKS_MENU), auT(BUN_WORKS_MENU_ITEM_REGISTER), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add BundleWorks Help menu item
    sprintf(pcCallback, BUN_WORKS_EXPORT_HELP_STR, BUN_WORKS_DLL_NAME,
        BUN_WORKS_EXPORT_HELP);
    hres = pFrame->AddMenuItem(
                auT(BUN_WORKS_MENU), auT(BUN_WORKS_MENU_ITEM_HELP), swLastPosition,
                _bstr_t(pcCallback),
                &bres);

    // add BundleWorks About menu item
    sprintf(pcCallback, BUN_WORKS_EXPORT_ABOUT_STR, BUN_WORKS_DLL_NAME,
        BUN_WORKS_EXPORT_ABOUT);
    hres = pFrame->AddMenuItem(
                auT(BUN_WORKS_MENU), auT(BUN_WORKS_MENU_ITEM_ABOUT), swLastPosition,
                _bstr_t(pcCallback),
                &bres);


    // clean up
    pFrame->Release();
}
// ----------------------------------------------------------------
void CBundleWorksApp::RemoveMenus(void)
{
    HRESULT         hres;
    VARIANT_BOOL    bres;

    if (TRUE == m_bSWMenu)
        {
        // remove save-as item
        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_PRT), swDocPART, &bres);

        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_ASM), swDocASSEMBLY, &bres);

        hres = m_pSldWorks->RemoveFileSaveAsItem(auT(BUN_WORKS_EXPORT_SAVE_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_DRW), swDocDRAWING, &bres);

        // remove file open item
        hres = m_pSldWorks->RemoveFileOpenItem(auT(BUN_WORKS_EXPORT_OPEN_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_PRT), &bres);

        hres = m_pSldWorks->RemoveFileOpenItem(auT(BUN_WORKS_EXPORT_OPEN_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_ASM), &bres);

        hres = m_pSldWorks->RemoveFileOpenItem(auT(BUN_WORKS_EXPORT_OPEN_AS),
                    _bstr_t(BUN_WORKS_DESCRIP_DRW), &bres);
        }

    // remove menus and save-as items from each document type
    if (m_bPartMenu)
        docRemoveMenu(swDocPART);

    if (m_bAssemblyMenu)
        docRemoveMenu(swDocASSEMBLY);

    if (m_bDrawingMenu)
        docRemoveMenu(swDocDRAWING);
}
// ----------------------------------------------------------------
// removes a menu and save-as item to the currently active document type
//
void CBundleWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT      hres;
    VARIANT_BOOL bres;

    //remove menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(BUN_WORKS_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CBundleWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
// ----------------------------------------------------------------
bool CBundleWorksApp::RemoveEvent(CObject* swEventHandler)
{
    POSITION pos;

    // remove from the object list
    pos = m_EventList.Find(swEventHandler);
    if (pos == 0)
        return FALSE;

    m_EventList.RemoveAt(pos);
    return TRUE;
}

// --------------------------------
//  helper functions
// --------------------------------

void CBundleWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
// ----------------------------------------------------------------
void CBundleWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
    {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
    }
}
// ----------------------------------------------------------------
void CBundleWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}
// ----------------------------------------------------------------
LPSLDWORKS CBundleWorksApp::GetSWApp(void)
{
    return m_pSldWorks;
}
// ----------------------------------------------------------------
void CBundleWorksApp::SavePrefs(void)
{
    // save preferences
    TCHAR      TempUStr[20];

    // document recursion flag
    _stprintf(TempUStr, _T("%d"), m_bRecurse);
    WritePrivateProfileString(
        BUN_WORKS_INI_FILE_PREFS_SECT,
        BUN_WORKS_INI_FILE_RECURSE,
        TempUStr,
        BUN_WORKS_INI_FILE_NAME);

    // save directory structure flag
    _stprintf(TempUStr, _T("%d"), m_bDirStructure);
    WritePrivateProfileString(
        BUN_WORKS_INI_FILE_PREFS_SECT,
        BUN_WORKS_INI_FILE_DIRSTRUCT,
        TempUStr,
        BUN_WORKS_INI_FILE_NAME);
}
// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------

