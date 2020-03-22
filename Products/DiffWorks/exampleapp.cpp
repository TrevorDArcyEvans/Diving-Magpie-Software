// -------------------------------------------------------------------
//
//     Filename: ExampleApp.cpp
//  Description: Implements the CDiffWorksApp class which is the
//               basis for the entire example application.
//
// -------------------------------------------------------------------

#include <stdafx.h>

#include "DiffWorks.h"
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
CDiffWorksApp::CDiffWorksApp(LPSLDWORKS pSldWorks)
{
    // application
    m_pSldWorks         = pSldWorks;
    m_pActiveDoc        = NULL;

    // menus
    m_bMainMenu         = FALSE;
    m_bPartMenu         = FALSE;
    m_bAssemblyMenu     = FALSE;
    m_bDrawingMenu      = FALSE;


    // Save the current resource handle
    HINSTANCE                   SaveResource = AfxGetResourceHandle();
    HINSTANCE                   DW_ResourceHandle = GetModuleHandle(DIFF_DLL_NAME);

    // Switch to the Application resources
    AfxSetResourceHandle(DW_ResourceHandle);

    try
        {
        // initialise COM for this thread
        CoInitialize(NULL);

        HRESULT                             hres = S_OK;
        CComBSTR                            sMessage;

        hres = m_DMS_DiffWks.CoCreateInstance(__uuidof(DMS_DiffWorks), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
        ASSERT(SUCCEEDED(hres));
        hres = m_DMS_DiffWks->put_Icon((long ) LoadIcon(DW_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DIFF_WKS)));

        hres = m_DMS_ProgPipe.CoCreateInstance(__uuidof(DMS_ProgPipe), NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER);
        ASSERT(SUCCEEDED(hres));
        hres = m_DMS_ProgPipe->put_Icon((long ) LoadIcon(DW_ResourceHandle, MAKEINTRESOURCE(IDI_ICON_DIFF_WKS)));

        hres = m_DMS_ProgPipe->put_Title(CComBSTR(DIFF_WORKS_TITLE));

        sMessage = CComBSTR(DIFF_WORKS_TITLE);
        sMessage.Append(CComBSTR(_T("\nCopyright © 2000\nTrevor D'Arcy-Evans")));
        hres = m_DMS_ProgPipe->put_Message(sMessage);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    CLEAN_UP :
        ;
    // Reset to previous resource handle
    AfxSetResourceHandle(SaveResource);
}
//---------------------------------------------------------------------
CDiffWorksApp::~CDiffWorksApp()
{
    try
        {
        // get rid of our dialogs
        m_DMS_DiffWks .Release();
        m_DMS_DiffWks  = NULL;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    try
        {
        // get rid of our dialogs
        m_DMS_ProgPipe.Release();
        m_DMS_ProgPipe = NULL;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }


    // before we shut down COM for this thread
    CoUninitialize();
}

// --------------------------------
//  Functionality
// --------------------------------

// --------------------------------
//  Load/Unload
// --------------------------------

bool CDiffWorksApp::StartApplication(void)
{
    // add menus to the active document
    AddMenus();

    // create a control item to handle application-level events
    swAppEvents* eventApp = new swAppEvents;
    eventApp->OnCreate(m_pSldWorks);

    return TRUE;
}
//------------------------------------------------------------------------
void CDiffWorksApp::TerminateApplication(void)
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
         delete headEvent;          // destructor will remove it from list with RemoveAt(pos)
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

#define swMenuPosition  5   // add your menu after Tools and before Window
#define swLastPosition -1

//  Add a menu to the active document frame.  This is to be done
//  only ONCE for each document type.
//  
void CDiffWorksApp::AddMenus(void)
{
    HRESULT                     res;
    CComPtr <IModelDoc>         pModelDoc;
    long                        doctype;

    res = m_pSldWorks->get_IActiveDoc(&pModelDoc);
    if (pModelDoc == NULL)
        {
        if (!m_bMainMenu)
            {
            docCreateMenu(swNONE);

            m_bMainMenu = TRUE;
            }

        return;
        }

    // get the document type
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
}
//------------------------------------------------------------------------
// adds a menu and save-as item to the currently active document type
//
void CDiffWorksApp::docCreateMenu(long DocumentType)
{
    HRESULT                 hres;
    VARIANT_BOOL            bres;
    LPFRAME                 pFrame;

    hres = m_pSldWorks->IFrameObject(&pFrame);

    // add DiffWorks menu
    hres = pFrame->AddMenu(auT(DIFF_MENU), swLastPosition, &bres);

    if (FALSE == bres)
        {
        // add top level (SolidPartners) menu
        hres = pFrame->AddMenu(auT(SP_MENU), swLastPosition, &bres);

        // add DiffWorks submenu
        hres = pFrame->AddMenu(auT(DIFF_MENU), swLastPosition, &bres);
        }

    // add Compare menu item
    hres = pFrame->AddMenuItem(
                    auT(DIFF_MENU), auT(DIFF_MENU_ITEM_COMPARE), swLastPosition,
                    auT(DIFF_EXPORT_COMPARE),
                    &bres);

    // add Show Last menu item
    hres = pFrame->AddMenuItem(
                    auT(DIFF_MENU), auT(DIFF_MENU_ITEM_SHOW), swLastPosition,
                    auT(DIFF_EXPORT_SHOW),
                    &bres);

    // add separator
    hres = pFrame->AddMenuItem(
                    auT(DIFF_MENU), NULL, swLastPosition,
                    NULL,
                    &bres);

    // add Register menu item
    hres = pFrame->AddMenuItem(
                auT(DIFF_MENU), auT(DIFF_MENU_ITEM_REGISTER), swLastPosition,
                auT(DIFF_EXPORT_REGISTER),
                &bres);

    // add Help menu item
    hres = pFrame->AddMenuItem(
                auT(DIFF_MENU), auT(DIFF_MENU_ITEM_HELP), swLastPosition,
                auT(DIFF_EXPORT_HELP),
                &bres);

    // add About menu item
    hres = pFrame->AddMenuItem(
                    auT(DIFF_MENU), auT(DIFF_MENU_ITEM_ABOUT), swLastPosition,
                    auT(DIFF_EXPORT_ABOUT),
                    &bres);


    // clean up
    pFrame->Release();
}
//------------------------------------------------------------------------
void CDiffWorksApp::RemoveMenus(void)
{
    // remove menus and save-as items from each document type
    if (m_bMainMenu)
        {
        docRemoveMenu(swDocNONE);
        }

    if (m_bPartMenu)
        {
        docRemoveMenu(swDocPART);
        }

    if (m_bAssemblyMenu)
        {
        docRemoveMenu(swDocASSEMBLY);
        }

    if (m_bDrawingMenu)
        {
        docRemoveMenu(swDocDRAWING);
        }
}
//------------------------------------------------------------------------
// removes a menu and save-as item to the currently active document type
//
void CDiffWorksApp::docRemoveMenu(long DocumentType)
{
    HRESULT                 hres;
    VARIANT_BOOL            bres;
    LPFRAME                 pFrame;

    if (swDocNONE == DocumentType)
        {
        hres = m_pSldWorks->IFrameObject(&pFrame);

        // remove from SolidWorks top level menu
        hres = pFrame->RemoveMenu(auT(DIFF_MENU));

        // clean up
        pFrame->Release();
        }

    // remove from SolidPartners menu
    hres = m_pSldWorks->RemoveMenu(DocumentType, auT(DIFF_MENU), NULL, &bres);
}

// --------------------------------
//  Events
// --------------------------------

void CDiffWorksApp::AddEvent(CObject* swEventHandler)
{
    // add to the object list
    m_EventList.AddTail(swEventHandler);
}
//------------------------------------------------------------------------
bool CDiffWorksApp::RemoveEvent(CObject* swEventHandler)
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

void CDiffWorksApp::SetResource()
{
    // Save the original SolidWorks resource instance handle
    // replacing it with the instance handle of the DiffWorks.dll.
    if( m_hSaveInst == NULL)
    {
        m_hSaveInst = ::AfxGetResourceHandle();
        ::AfxSetResourceHandle( ::AfxGetInstanceHandle());
    }
}
//------------------------------------------------------------------------
void CDiffWorksApp::ResetResource()
{
    // Reset the SolidWorks resource instance handle
    if( m_hSaveInst != NULL)
    {
        ::AfxSetResourceHandle( m_hSaveInst);
        m_hSaveInst = NULL;
    }
}
//------------------------------------------------------------------------
void CDiffWorksApp::ChangeActiveDoc(void)
{
    // release the refence count on the previously active document
    if (m_pActiveDoc != NULL)
        m_pActiveDoc->Release();

    // Set the new active document
    HRESULT res;
    res = m_pSldWorks->get_IActiveDoc(&m_pActiveDoc);
}
//------------------------------------------------------------------------
void CDiffWorksApp::DestroyDoc(LPMODELDOC DocBeingDestroyed)
{
    // Determine if the part being destroyed was the active document.
    // If so, release a reference to it, and set m_pActiveDoc to NULL
    if (DocBeingDestroyed == m_pActiveDoc)
    {
        m_pActiveDoc->Release();
        m_pActiveDoc = NULL;
    }
}
//------------------------------------------------------------------------
void CDiffWorksApp::SetSWApp(LPSLDWORKS pSldWorks)
{
    m_pSldWorks = pSldWorks;
}
//------------------------------------------------------------------------

// --------------------------------
//  End of ExampleApp.cpp
// --------------------------------
