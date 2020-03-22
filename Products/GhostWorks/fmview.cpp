// -------------------------------------------------------------------
//
//                       SolidWorks Corporation
//                Copyright 1998 (Unpublished material)
//
// This code is for demonstration only, no responsibility for its
// functionality or suitability for applications can be accepted by
// SolidWorks Corporation.
//
// -------------------------------------------------------------------
//
//  Filename:    FMView.cpp
//  Description: Example code to demonstrate adding an MFC TreeCtrl
//               control in the SolidWorks Feature Manager.
//
//               A container window and a tree control are created in the
//               SolidWorks Feature Manager Window.
//
//               For simplicity all class definitions and implementation
//               code is held in the same file.
//
//  Notes:       1 There is an extra window in the heirachy because the
//               CTreeCtrl sends a TVN_ENDLABELEDIT to its parent window
//               when the user finishes editing.  If the label editing
//               is swithed off then this extra layer is not necessary
//               2 - The resizing of the feature manager window and scroll
//               bar in the Tree when the Tree draws one are not handled.
//
//  Usage:       Call the extern function CreateFeatureManagerView
//               whenever a new window is created in SolidWorks.
//
// -------------------------------------------------------------------

#include "stdafx.h"
#include "Afxcview.h"
#include "amapp.h"
#include "swconst.h"
#include "ccitem.h"
#include "ExampleApp.h"
#include "resource.h"
#include "FMView.h"
#include "debug.h"

#include "SLogError.h"
#include <shlwapi.h>

//------------------------------------------------------------------------


BEGIN_EVENTSINK_MAP(FMFeatureManagerEvents, CControlItem)
    ON_EVENT (FMFeatureManagerEvents, (unsigned int)-1, swFMViewActivateNotify          , ActivateNotify    , VTS_VARIANT   )
    ON_EVENT (FMFeatureManagerEvents, (unsigned int)-1, swFMViewDeactivateNotify        , DeactivateNotify  , VTS_VARIANT   )
    ON_EVENT (FMFeatureManagerEvents, (unsigned int)-1, swFMViewDestroyNotify           , DestroyNotify     , VTS_VARIANT   )
    ON_EVENT (FMFeatureManagerEvents, (unsigned int)-1, swPartNewSelectionNotify        , OnNewSelection    , VTS_NONE      )
    ON_EVENT (FMFeatureManagerEvents, (unsigned int)-1, swAssemblyNewSelectionNotify    , OnNewSelection    , VTS_NONE      )
END_EVENTSINK_MAP()


//------------------------------------------------------------------------
// FMFeatureManagerEvents::~FMFeatureManagerEvents
// Destructor - called when the application is cleaning up
// delete the TAB but not the notification object
FMFeatureManagerEvents::~FMFeatureManagerEvents()
{
    try
        {
        Release();

        if ( m_pFMView != NULL )
            {
            m_pFMView->OnDestroyNotify(false);
            }
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
HRESULT FMFeatureManagerEvents::DestroyNotify(VARIANT* View)
{
    try
        {
        SW_OutputDebugString(_T("FMFeatureManagerEvents::DestroyNotify\n"));

        // View will be of type VT_ERROR when we are just deleting a component
        if (m_pFMView != NULL && View->vt != VT_ERROR)
            {
            // must be definitely destroying the FeatureManager view
            m_pFMView->OnDestroyNotify(true);
            }
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
    return S_OK;
}
//------------------------------------------------------------------------
HRESULT FMFeatureManagerEvents::ActivateNotify(VARIANT* View)
{
    SW_OutputDebugString(_T("FMFeatureManagerEvents::ActivateNotify\n"));

    // force the tree and buttons to be repositioned
    // note using dummy parameters
    m_pFMView->OnSize(0, 0 ,0);

    return S_OK;
}
//------------------------------------------------------------------------
HRESULT FMFeatureManagerEvents::DeactivateNotify(VARIANT* View)
{
    try
        {
        SW_OutputDebugString(_T("FMFeatureManagerEvents::DeactivateNotify\n"));
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
    return S_OK;
}
//------------------------------------------------------------------------
HRESULT FMFeatureManagerEvents::OnNewSelection()
{
    try
        {
        SW_OutputDebugString(_T("FMFeatureManagerEvents::OnNewSelection\n"));
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
    return S_OK;
}
//------------------------------------------------------------------------


BEGIN_MESSAGE_MAP(CFMTreeCtrl, CTreeCtrl)
    ON_WM_SIZE()
END_MESSAGE_MAP()


//------------------------------------------------------------------------
// CFMTreeCtrl::UpdateSelection
// if an item in the tree is selected, this will then select the corresponding
// component in the assembly
void CFMTreeCtrl::UpdateSelection()
{
    try
        {
        USES_CONVERSION;

        CComBSTR                    Name;
        TCHAR                       FullName[MAX_PATH];
        CString                     SWSelItemText;
        CComPtr <IModelDoc>         pModelDoc;
        long                        DocType;
        VARIANT_BOOL                bRetVal;

        HTREEITEM                   SelItem = GetSelectedItem();

        if (NULL == SelItem)
            {
            // nothing in tree selected, so go home
            return;
            }


        STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
        SASSERT_BOOL_COM(pModelDoc != NULL);

        STEST_HR(pModelDoc->ClearSelection());

        if (GetRootItem() == SelItem)
            {
            // top level component needs special handling
            STEST_HR(pModelDoc->GetTitle(&Name));
            STEST_HR(pModelDoc->GetType(&DocType));
            if (swDocPART == DocType)
                {
                // especially parts where we have to strip off the file extension
                _tcscpy(FullName, OLE2T(Name.m_str));
                PathRemoveExtension(FullName);
                Name = FullName;
                }

            SWSelItemText = Name;
            }
        else
            {
            // get the component's ID string for selecting
            CComPtr <IComponent>        pComponent = (IComponent *) GetItemData(SelItem);
            if (pComponent != NULL)
                {
                STEST_HR(pComponent->get_Name(&Name));
                SWSelItemText = GetComponentID(CString(Name));
                }
            }

        // then select in SW
        STEST_HR(pModelDoc->SelectByID(CComBSTR(SWSelItemText), CComBSTR(_T("COMPONENT")), 0.0, 0.0, 0.0, &bRetVal));
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//----------------------------------------------------------------------------
// CFMTreeCtrl::GetComponentID
//
// parameters
//      Name
//          the component name, as returned from Component::get_Name()
//
// returns
//      CString
//          ID
//
// notes
//      makes a ID for this component
//      ID format is:
//          ParentAsm-instance@GrandParrentAsm[/ChildAsm-instance@ParentAsm[/Part-instance@ChildAsm]]
CString CFMTreeCtrl::GetComponentID(const CString& Name)
{
    _TCHAR              RootName[_MAX_FNAME];
    _tsplitpath(GetItemText(GetRootItem()), NULL, NULL, RootName, NULL); //get file name

    int                 ipos = 0;
    CString             strRootName = RootName;
    CString             strID = _T("");
    CString             strParent = strRootName;
    CString             strChild;
    CString             strList = Name;

    while (ipos > -1)
        {
        ipos = strList.Find(_T('/'));
        if (ipos != -1)
            {
            strChild = strList.Left(ipos);

            if (strID.GetLength() > 0)  //It is not 1st component
                {
                strID += _T("/");
                }

            strID += strChild;
            strID += _T("@");
            strID += strParent;

            strList = strList.Mid(ipos + 1);
            
            int             pos = 0;
            pos = strChild.Find(_T('-'));
            if (ipos != -1)
                {
                strChild = strChild.Left(pos);
                }
            strParent = strChild;
            }
        else
            {
            if (strList.GetLength()> 0)
                {
                if (strID.GetLength() > 0)
                    {
                    strID += _T("/");
                    }
                strID += strList;
                strID += _T("@");
                strID += strParent;
                }
            }
        }

    return strID;
}
//------------------------------------------------------------------------
// CFMTreeCtrl::TrickleDown
// starts at the specified tree node and then recursively sets the state
// of the check boxes on all child nodes below it to the specified state
//
// parameters
//      Start
//          node at which to start
//
//      bCheck
//          true
//              if checkboxes are to be set to checked
//          false
//              if checkboxes are to be set to unchecked
//
// notes
//      function is called recursively
//
//      does not take into account whether or not the current node is checked
void CFMTreeCtrl::TrickleDown(HTREEITEM Start, BOOL bCheck)
{
    if (ItemHasChildren(Start))
        {
        HTREEITEM           hNextItem;
        HTREEITEM           hChildItem = GetChildItem(Start);
        CString             ChildText;
        CString             NextText;

        while (NULL != hChildItem)
            {
            SetCheck(hChildItem, bCheck);
            hNextItem = GetNextItem(hChildItem, TVGN_NEXT);

            ChildText = GetItemText(hChildItem);
            NextText  = GetItemText(hNextItem );

            if (NULL != hChildItem)
                {
                // recurse
                TrickleDown(hChildItem, bCheck);
                }

            hChildItem = hNextItem;
            }
        }
}
//------------------------------------------------------------------------
// CFMTreeCtrl::ExpandAll
// starts at the specified tree node and then recursively expands the node
// and all child nodes below it
//
// parameters
//      Start
//          node at which to start
//
// notes
//      function is called recursively
//
//      does not take into account whether or not the current node is expanded
void CFMTreeCtrl::ExpandAll  (HTREEITEM Start)
{
    Expand(Start, TVE_EXPAND);

    if (ItemHasChildren(Start))
        {
        HTREEITEM           hNextItem;
        HTREEITEM           hChildItem = GetChildItem(Start);
        CString             ChildText;
        CString             NextText;

        while (NULL != hChildItem)
            {
            hNextItem = GetNextItem(hChildItem, TVGN_NEXT);

            ChildText = GetItemText(hChildItem);
            NextText  = GetItemText(hNextItem );

            if (NULL != hChildItem)
                {
                // recurse
                ExpandAll(hChildItem);
                }

            hChildItem = hNextItem;
            }
        }
}
//------------------------------------------------------------------------
// CFMTreeCtrl::HideOrShowAll
// starts at the specified tree node and then recursively either hides or 
// shows all child nodes below it
//
// parameters
//      Start
//          node at which to start
//
//      bHide
//          true
//              if this node and all children are to be hidden
//          false
//              if this node and all children are to be shown
//
// notes
//      function is called recursively
//
//      will try to alter visibility of component regardless of its current
//      state
void CFMTreeCtrl::HideOrShowAll(HTREEITEM Start, bool bHide)
{
    HTREEITEM           hNextItem;
    HTREEITEM           hChildItem = GetChildItem(Start);
    CString             StartText  = GetItemText (Start);
    CString             ChildText;
    CString             NextText;

    do
        {
        if (TRUE == GetCheck(Start))
            {
            try
                {
                // checked, so hide this component
                CComPtr   <IModelDoc>       pModelDoc;
                CComQIPtr <IAssemblyDoc>    pAssyDoc;

                CComPtr <IComponent>        pComponent = (IComponent *) GetItemData(Start);
                CComBSTR                    Name;
                CString                     SWSelItemText;
                VARIANT_BOOL                bRetVal;

                STEST_HR(pComponent->get_Name(&Name));
                SWSelItemText = GetComponentID(CString(Name));

                // then select in SW
                STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
                SASSERT_BOOL_COM(pModelDoc != NULL);

                STEST_HR(pModelDoc->ClearSelection());

                STEST_HR(pModelDoc->SelectByID(CComBSTR(SWSelItemText), CComBSTR(_T("COMPONENT")), 0.0, 0.0, 0.0, &bRetVal));

                pAssyDoc = pModelDoc;
                SASSERT_BOOL_COM(pAssyDoc != NULL);

                if (true == bHide)
                    {
                    STEST_HR(pAssyDoc->HideComponent());
                    }
                else
                    {
                    STEST_HR(pAssyDoc->ShowComponent());
                    }

                STEST_HR(pModelDoc->ClearSelection());
                }
            catch (_com_error& e)
                {
                (void ) e;
                }
            catch (...)
                {
                }
            }

        hNextItem = GetNextItem(hChildItem, TVGN_NEXT);

        ChildText = GetItemText(hChildItem);
        NextText  = GetItemText(hNextItem );

        if (NULL != hChildItem)
            {
            // recurse
            HideOrShowAll(hChildItem, bHide);
            }

        hChildItem = hNextItem;
        } while (NULL != hChildItem);
}
//------------------------------------------------------------------------
// CFMTreeCtrl::Hide
// starts at the the top of the assembly and forcibly hides all components 
// which are checked in the tree
//
// notes
//      will try to hide components which are already hidden
void CFMTreeCtrl::Hide()
{
    try
        {
        SW_OutputDebugString(_T("CFMTreeCtrl::Hide\n"));
        HideOrShowAll(GetRootItem(), true);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
// CFMTreeCtrl::Show
// starts at the the top of the assembly and forcibly shows all components
// which are checked in the tree
//
// notes
//      will try to show components which are already showing
void CFMTreeCtrl::Show()
{
    try
        {
        SW_OutputDebugString(_T("CFMTreeCtrl::Show\n"));
        HideOrShowAll(GetRootItem(), false);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
void CFMTreeCtrl::OnSize(UINT nType, int cx, int cy)
{
    try
        {
        // just delegate to the view which contains us
        m_FMView->OnSize(nType, cx, cy);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
// CFMTreeCtrl::WindowProc
LRESULT CFMTreeCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    try
        {
        // LMB = select SW item
        if (WM_LBUTTONDOWN == message)
            {
            UINT                uFlags;
            CPoint              point(lParam);
            HTREEITEM           HitItem = HitTest(point, &uFlags);
            BOOL                bCheck;

            if (NULL == HitItem)
                {
                // nothing in tree selected, so use default handler
                goto DEFAULT;
                }

            if (!(TVHT_ONITEM & uFlags))
                {
                // not on anything, so use default handler
                goto DEFAULT;
                }

            // select it in the tree
            SelectItem(HitItem);

            // highlight in SW
            UpdateSelection();

            // trickle down the check box status to all
            // children and grandchildren
            bCheck  = !GetCheck(HitItem);

            TrickleDown(HitItem, bCheck);
            }// WM_LBUTTONDOWN


        // resize the window
        if (WM_SIZE == message)
            {
            SW_OutputDebugString(_T("CFMTreeCtrl::WindowProc : WM_SIZE\n"));

            // just extract parameters and delegate
            UINT                nType   = wParam;
            int                 cx      = LOWORD(lParam);
            int                 cy      = HIWORD(lParam);

            OnSize(nType, cx, cy);
            }

        if (WM_SIZING == message)
            {
            SW_OutputDebugString(_T("CFMTreeCtrl::WindowProc : WM_SIZING\n"));
            }
        }//try
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    DEFAULT :
        ;
    return CTreeCtrl::WindowProc(message, wParam, lParam);
}

//------------------------------------------------------------------------
// Class CFMView
// Manage creation/destruction and activation of the Feature Manager View
// Also gets the TVN_ENDLABELEDIT when the user finishes editing a label
// in the tree control.


BEGIN_MESSAGE_MAP(CFMView, CWnd)
    ON_WM_SIZE()
    ON_WM_SIZING()
    ON_BN_CLICKED(IDC_BTN_HIDE, OnBtnHide)
    ON_BN_CLICKED(IDC_BTN_SHOW, OnBtnShow)
END_MESSAGE_MAP()


//------------------------------------------------------------------------

static const int   BUTTON_WIDTH        = 50;
static const int   BUTTON_HEIGHT       = 24;


// vertical space to allow for buttons.  Used when setting the size of the
// tree control
static const int   BUTTON_SPACE        = 80;


// vertical position of buttons *above* the bottom of the parent window
static const int   FIRST_BUTTON_POS    = 20;
static const int   SECOND_BUTTON_POS   = 50;

//------------------------------------------------------------------------
// CFMView::GetTreeRect
// calculates size and position of tree control window, relative to parent
// window
//
// notes
//      will leave space at bottom of parent window for 'Show' and 'Hide'
//      buttons
void CFMView::GetTreeRect(CRect ParentRect, CRect& Rect)
{
    Rect.left   = ParentRect.left;
    Rect.top    = ParentRect.top;
    Rect.right  = ParentRect.right;
    Rect.bottom = ParentRect.bottom - BUTTON_SPACE;
}
//------------------------------------------------------------------------
// CFMView::GetShowRect
// calculates size and position of 'Show' button, relative to parent
// window
//
// notes
//      'Show' button is above 'Hide' button
void CFMView::GetShowRect(CRect ParentRect, CRect& Rect)
{
    Rect.left   = (ParentRect.right - ParentRect.left) / 2 + BUTTON_WIDTH / 2;
    Rect.top    = ParentRect.bottom - SECOND_BUTTON_POS - BUTTON_HEIGHT;
    Rect.right  = (ParentRect.right - ParentRect.left) / 2 - BUTTON_WIDTH / 2;
    Rect.bottom = ParentRect.bottom - SECOND_BUTTON_POS;
}
//------------------------------------------------------------------------
// CFMView::GetHideRect
// calculates size and position of 'Hide' button, relative to parent
// window
//
// notes
//      'Hide' button is below 'Show' button
void CFMView::GetHideRect(CRect ParentRect, CRect& Rect)
{
    Rect.left   = (ParentRect.right - ParentRect.left) / 2 + BUTTON_WIDTH / 2;
    Rect.top    = ParentRect.bottom - FIRST_BUTTON_POS - BUTTON_HEIGHT;
    Rect.right  = (ParentRect.right - ParentRect.left) / 2 - BUTTON_WIDTH / 2;
    Rect.bottom = ParentRect.bottom - FIRST_BUTTON_POS;
}
//------------------------------------------------------------------------
// CFMView::Create
// creates the tree control and buttons in the Feature Manager window
BOOL CFMView::Create()
{
    try
        {
        CComPtr <IModelDoc>             pModelDoc;
        CComPtr <IFeatMgrView>          pFeatMgr;
        CRect                           Rect;
        CRect                           TreeRect;
        CRect                           ShowRect;
        CRect                           HideRect;

        // Get the active doc and create a feature manager view in it
        STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));

        // Ensure we are using our resources
        TheApplication->SetResources();

        m_Bitmap.LoadMappedBitmap(IDB_BITMAP_GHOST_WKS);

        // Reset to SolidWorks resources
        TheApplication->ResetResources();

        STEST_HR(pModelDoc->ICreateFeatureMgrView((long *)&m_Bitmap, &pFeatMgr));
        SASSERT_BOOL_COM(pFeatMgr != NULL)

        // Create a control item to handle FeatureManager events for the PartDoc
        m_pEventHandler = new FMFeatureManagerEvents;
        m_pEventHandler->OnCreate(pFeatMgr);
        m_pEventHandler->m_pFMView = this;

        // Create a control item to handle ModelDoc events for the PartDoc
        m_pModelEventHandler = new FMFeatureManagerEvents;
        m_pModelEventHandler->OnCreate(pModelDoc);
        m_pModelEventHandler->m_pFMView = this;

        // Create a window in the Feature Manager window
        pFeatMgr->GetFeatMgrViewWnd((long *) &m_pParent);
        m_pParent->GetClientRect (&Rect);
        CWnd::Create (NULL, _T(""), WS_CHILD | WS_VISIBLE, Rect, m_pParent, 1);

        GetTreeRect(Rect, TreeRect);
        TreeRect.NormalizeRect();

        // Create the Tree Control in our new window
        m_TreeCtrl.Create(
                    TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_CHECKBOXES,
                    TreeRect, this, 1);

        GetShowRect(Rect, ShowRect);
        ShowRect.NormalizeRect();

        GetHideRect(Rect, HideRect);
        HideRect.NormalizeRect();

        m_BtnShow.Create(_T("Show"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, ShowRect, this, IDC_BTN_SHOW);
        m_BtnHide.Create(_T("Hide"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, HideRect, this, IDC_BTN_HIDE);


        m_TreeCtrl.SetFMView(this);


        // Display the windows
        ShowWindow(SW_SHOW);
        MoveWindow(&Rect);

        m_TreeCtrl.ShowWindow (SW_SHOW);
        m_TreeCtrl.MoveWindow (&TreeRect);

        m_BtnShow.ShowWindow (SW_SHOW);
        m_BtnShow.MoveWindow (&ShowRect);

        m_BtnHide.ShowWindow (SW_SHOW);
        m_BtnHide.MoveWindow (&HideRect);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    return true;
}


//------------------------------------------------------------------------
// CFMView::Add
// Create and size the windows
#if 0
// not used - keep for reference
BOOL CFMView::Add()
{
    try
        {
        LPMODELDOC              pModelDoc;
        LPFEATMGRVIEW           pFeatMgr;
        CRect                   rect;
        CMyView                 MyView;
        VARIANT_BOOL            retval;

        // Get the active doc and create a feature manager view in it
        if (CFeatureMgrApp::GetSWApp()->get_IActiveDoc( &pModelDoc ) == S_OK)
            {
            // Ensure we are using our resources
            CFeatureMgrApp::SetResources();

            m_Bitmap.LoadMappedBitmap(IDB_BITMAP_MASS_WKS);

            // Reset to SolidWorks resources
            CFeatureMgrApp::ResetResources();

            if (pModelDoc->AddFeatureMgrView((long*)&m_Bitmap, (long*)&MyView, &retval) == S_OK)
                {
                // Create a control item to handle events for the PartDoc
                m_pEventHandler = new FMFeatureManagerEvents;
                m_pEventHandler->OnCreate(pFeatMgr);
                m_pEventHandler->m_pFMView = this;

                // Create a window in the Feature Manager window
                pFeatMgr->GetFeatMgrViewWnd((long*)&m_pParent);
                m_pParent->GetClientRect (&rect);
                CWnd::Create (NULL, _T(""), WS_CHILD | WS_VISIBLE, rect, m_pParent, 1);

                // Create the Tree Control in our new window
                m_TreeCtrl.Create(TVS_HASLINES | TVS_HASBUTTONS | TVS_EDITLABELS, rect, this, 1);

                // Display the windows
                ShowWindow (SW_SHOW);
                MoveWindow (&rect);
                m_TreeCtrl.ShowWindow (SW_SHOW);
                m_TreeCtrl.MoveWindow (&rect);

                pFeatMgr->Release();
                }
            pModelDoc->Release();
            }
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    return true;
}
#endif

//------------------------------------------------------------------------
// CFMView::OnSize
// resizes the tree control and repositions the Hide and Show buttons
//
// notes
//      seems to be a problem when the parent window is resized to a size
//      which is larger than when the tree control and buttons were 
//      originally created.  The symptoms are the buttons are now trying to
//      be positioned outside the bounds of the original window and any
//      portion of the buttons outside this original window are not drawn
//      at all.  Most odd...
void CFMView::OnSize(UINT nType, int cx, int cy)
{
    try
        {
        SW_OutputDebugString(_T("CFMView::OnSize\n"));

        CRect                           Rect;
        CRect                           TreeRect;
        CRect                           ShowRect;
        CRect                           HideRect;

        m_pParent->GetClientRect(&Rect);

        GetTreeRect(Rect, TreeRect);
        TreeRect.NormalizeRect();

        GetShowRect(Rect, ShowRect);
        ShowRect.NormalizeRect();

        GetHideRect(Rect, HideRect);
        HideRect.NormalizeRect();

        m_TreeCtrl.ShowWindow (SW_SHOW  );
        m_TreeCtrl.MoveWindow (&TreeRect);

        m_BtnShow.ShowWindow  (SW_SHOW  );
        m_BtnShow.MoveWindow  (&ShowRect);

        m_BtnHide.ShowWindow  (SW_SHOW  );
        m_BtnHide.MoveWindow  (&HideRect);
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    CWnd::OnSize(nType, cx, cy);
}


//------------------------------------------------------------------------
// CFMView::OnSizing
void CFMView::OnSizing(UINT fwSide, LPRECT pRect)
{
    try
        {
        SW_OutputDebugString(_T("CFMView::OnSizing\n"));
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    CWnd::OnSizing(fwSide, pRect);
}
//------------------------------------------------------------------------
void CFMView::OnBtnHide()
{
    try
        {
        SW_OutputDebugString(_T("CFMView::OnBtnHide\n"));

        CWaitCursor                 wait;

        m_TreeCtrl.Hide();
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
void CFMView::OnBtnShow()
{
    try
        {
        SW_OutputDebugString(_T("CFMView::OnBtnShow\n"));

        CWaitCursor                 wait;

        m_TreeCtrl.Show();
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// CFMView::PreTranslateMessage
BOOL CFMView::PreTranslateMessage(MSG* pMsg) 
{
    try
        {
        //SW_OutputDebugString(_T("CFMView::PreTranslateMessage\n"));

        // handle keyboard navigation
        if (WM_KEYDOWN == pMsg->message)
            {
            if (VK_UP == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_UP\n"));
                }
            if (VK_DOWN == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_DOWN\n"));
                }
            if (VK_LEFT == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_LEFT\n"));
                }
            if (VK_RIGHT == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_RIGHT\n"));
                }

            if (VK_SPACE == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_SPACE\n"));
                }
            if (VK_RETURN == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_ENTER\n"));
                }

            if (VK_ADD == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_ADD\n"));
                }
            if (VK_SUBTRACT == pMsg->wParam)
                {
                SW_OutputDebugString(_T("CFMView::PreTranslateMessage : VK_SUBTRACT\n"));
                }

            m_TreeCtrl.WindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);

            m_TreeCtrl.UpdateSelection();

            return TRUE;
            }// if WM_KEYDOWN

        if (WM_SIZE == pMsg->message)
            {
            // CHECK        untested code!
            SW_OutputDebugString(_T("CFMView::PreTranslateMessage : WM_SIZE\n"));

            UINT            nType   = pMsg->wParam;
            int             cx      = LOWORD(pMsg->lParam);
            int             cy      = HIWORD(pMsg->lParam);

            OnSize(nType, cx, cy);

            return TRUE;
            }// if WM_SIZE

        if (WM_SIZING == pMsg->message)
            {
            // CHECK        untested code!
            SW_OutputDebugString(_T("CFMView::PreTranslateMessage : WM_SIZING\n"));

            UINT            fwSide  = pMsg->wParam;
            LPRECT          pRect   = (LPRECT ) pMsg->lParam;

            OnSizing(fwSide, pRect);

            return TRUE;
            }// if WM_SIZING
        }//try
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    // if we haven't handled it, pass it on
    return CWnd::PreTranslateMessage(pMsg);
}


//------------------------------------------------------------------------
// CFMView::OnNotify
// Received when the user finishes editing,
// Update the tree text or pass the message on
BOOL CFMView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    try
        {
        NMHDR*                  pNMHDR = (NMHDR*)lParam;
        int                     nCode = pNMHDR->code;

        if (nCode == TVN_ENDLABELEDIT)
            {
            TV_DISPINFO*            tvInfo = (TV_DISPINFO*)lParam;
            TV_ITEM                 tvItem;
            TCHAR                   buffer[256];

            tvItem.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_STATE | TVIF_SELECTEDIMAGE; 
            tvItem.stateMask = TVIS_EXPANDED;
            tvItem.hItem = tvInfo->item.hItem;
            tvItem.pszText = buffer;
            tvItem.cchTextMax = 256;
            m_TreeCtrl.GetItem(&tvItem);

            CString             newName = tvInfo->item.pszText;
            if (!newName.IsEmpty())
                {
                tvItem.pszText = (TCHAR*)LPCTSTR(newName);
                }
            tvItem.mask = TVIF_TEXT; 
            m_TreeCtrl.SetItem(&tvItem);

            return TRUE;
            }
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    return CWnd::OnNotify(wParam, lParam, pResult);
}

//------------------------------------------------------------------------
// CFMView::OnDestroyNotify
// Handle the window being destroyed
BOOL CFMView::OnDestroyNotify(bool bDeleteNotificationObject)
{
    try
        {
        CComPtr <IModelDoc>             pModelDoc;

        // Delete the notification handler unless we are being unloaded
        // when it is being deleted automatically
        m_pEventHandler     ->m_pFMView = NULL;
        m_pModelEventHandler->m_pFMView = NULL;

        if (bDeleteNotificationObject)
            {
            delete m_pEventHandler;
            delete m_pModelEventHandler;
            }

        // Get the active doc and destroy the feature manager view in it
        if (TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc) == S_OK)
            {
            // Delete the TAB
            pModelDoc->DeleteFeatureMgrView((long *)m_pParent);
            }

        // Destroy the windows
        delete this;
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }

    return TRUE;
}
//------------------------------------------------------------------------
// CFMView::Initialise
// removes all items in the tree and recreates it afresh
void CFMView::Initialise()
{
    try
        {
        m_TreeCtrl.DeleteAllItems();

        HTREEITEM                   root = m_TreeCtrl.GetRootItem();
        CComPtr <IConfiguration>    pConfiguration;
        CComPtr <IComponent>        pRootComponent;
        CComPtr <IModelDoc>         pModelDoc;

        STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
        SASSERT_BOOL_COM(pModelDoc != NULL);

        // Get the active configuration and root component
        STEST_HR(pModelDoc->IGetActiveConfiguration(&pConfiguration));
        STEST_HR(pConfiguration->IGetRootComponent(&pRootComponent));
        TraverseComponent(0, this, root, pRootComponent);

        m_TreeCtrl.ExpandAll(m_TreeCtrl.GetRootItem());
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
// CFMView::TraverseComponent
// starts at specified node in the tree and recursively constructs a tree
// of the assembly.
//
// At each node of the tree, we store a pointer to the SW component in that
// node's data storage member.
//
// Also, at each node, we set the image according to whether the component
// at that node is a part or a sub-assembly.  Each node is also labelled with
// the name of the part or sub-assembly.
//
// parameters
//      RecurseLevel
//          0 means the top level component ie the assembly itself
//          this requires special handling
//
//          also used for debugging to track the level of recursion
//
//      pFMView
//          view containing the tree control to which to add nodes
//
//      Item
//          tree node at which to start
//
//      pComponent
//          SW component corresponding to the tree node
//
// notes
//      function is called recursively
void CFMView::TraverseComponent
(
    int                         RecurseLevel,
    CFMView*                    pFMView     ,
    HTREEITEM                   Item        ,
    CComPtr <IComponent>        pComponent
)
{
    USES_CONVERSION;

    try
        {
        CComBSTR                    Name;
        TCHAR                       FullName[MAX_PATH];
        int                         nChildren = 0;
        int                         i = 0;
        CComPtr <IModelDoc>         pModelDoc;
        CComPtr <IComponent>        pComponentData;
        CComPtr <IComponent>        *pChildren = NULL;
        HTREEITEM                   ItemNext;

        if (pComponent != NULL)
            {
            // must be an assy
            STEST_HR(pComponent->IGetChildrenCount(&nChildren));
            }


        // retrieve the component name
        if (0 == RecurseLevel)
            {
            // special case of top level assembly or a part
            STEST_HR(TheApplication->GetSWApp()->get_IActiveDoc(&pModelDoc));
            SASSERT_BOOL_COM(pModelDoc != NULL);

            // get the name and remove the file extension
            STEST_HR(pModelDoc->GetTitle(&Name));
            _tcscpy(FullName, OLE2T(Name.m_str));
            PathRemoveExtension(FullName);

            // add top level assembly or part at root of tree
            ItemNext = pFMView->m_TreeCtrl.InsertItem(FullName);

            if (pComponent != NULL)
                {
                // handle assemblies slightly differently
                CComPtr <IComponent>        pComponentDataAssy;
                pComponent.CopyTo(&pComponentDataAssy);
                pFMView->m_TreeCtrl.SetItemData(ItemNext, (DWORD ) pComponentDataAssy.Detach());

                pFMView->m_TreeCtrl.SetItemImage(ItemNext, 0, 1);
                }
            else
                {
                // handle parts here
                CComPtr <IModelDoc>        pComponentDataPart;
                pModelDoc.CopyTo(&pComponentDataPart);
                pFMView->m_TreeCtrl.SetItemData(ItemNext, (DWORD ) pComponentDataPart.Detach());

                pFMView->m_TreeCtrl.SetItemImage(ItemNext, 2, 3);
                }
            }
        else
            {
            // just a sub-component here, either a part or sub-assy
            CString                     FullName;
            int                         Pos;

            STEST_HR(pComponent->get_Name(&Name));
            FullName = Name;

            // strip off SolidWorks path details
            // see SW API help on:
            //      Component::Name
            Pos = FullName.ReverseFind(_T('/'));
            if (-1 != Pos)
                {
                FullName.Delete(0, Pos + 1);
                }

            ItemNext = pFMView->m_TreeCtrl.InsertItem(FullName, Item);

            // store SolidWorks component for this node
            pComponent.CopyTo(&pComponentData);
            pFMView->m_TreeCtrl.SetItemData(ItemNext, (DWORD ) pComponentData.Detach());

            // check for a part or sub-assy based on whether it has any children
            // and set appropriate icon
            if (nChildren > 0)
                {
                // some kids, so must be a sub-assy
                pFMView->m_TreeCtrl.SetItemImage(ItemNext, 0, 1);
                }
            else
                {
                // no kids, so must be a part
                pFMView->m_TreeCtrl.SetItemImage(ItemNext, 2, 3);
                }
            }

        if (nChildren > 0)
            {
            pChildren = new CComPtr <IComponent> [nChildren];

            STEST_HR(pComponent->IGetChildren((LPCOMPONENT **) &pChildren));

            // recursively traverse the children
            for (i = 0; i < nChildren; i++)
                {
                // recurse
                TraverseComponent(RecurseLevel + 1, pFMView, ItemNext, pChildren[i]);
                pChildren[i] = NULL;
                }

            delete [] pChildren;
            }
        }
    catch (_com_error& e)
        {
        (void ) e;
        }
    catch (...)
        {
        }
}
//------------------------------------------------------------------------
// CreateFeatureManagerView
// creates or adds a tab to the Feature Manager and then populates the tree
// with the currently loaded SW model
//
// parameters
//      bCreateView
//          true
//              if a new Feature Manager tab is to be created
//          false
//              if a new Feature Manager tab is to be added
//
// returns
//      CFMView*
//          pointer to the view object containing the tree view and buttons
//
// notes
//      caller is responsible for calling CFMView::OnDestroyNotify() to free
//      the memory for this object
extern CFMView* CreateFeatureManagerView(bool bCreateView)
{
    try
        {
        CFMView*        view = new CFMView;

        if (bCreateView)
            {
            view->Create();
            }
        #if 0
        // not used - keep for reference
        else
            {
            view->Add();
            }
        #endif

        view->Initialise();

        return view;
        }
    catch (_com_error& e)
        {
        (void ) e;

        return NULL;
        }
    catch (...)
        {
        return NULL;
        }
}
//------------------------------------------------------------------------
