#if !defined(FMVIEW_H)
#define FMVIEW_H

#if _MSC_VER >= 1000
#pragma once
#endif

/*****************************************************************************/
// CLASS DEFINITIONS
/*****************************************************************************/

// Forward definitions
class CFMView;                  // The class that controls our Feature Manager Tab
class CFMTreeCtrl;              // SubClass of CTreeCtrl for the Tree Control
class FMFeatureManagerEvents;   // Handles Feature Manager Notifications


/*****************************************************************************/
// class CFMTreeCtrl
// SubClass the CTreeCtrl so that we can find when the user is starting to
// do a Label Edit operation and set the focus.
/*****************************************************************************/

// Class definition
class CFMTreeCtrl : public CTreeCtrl
{
private:
    CFMView*                        m_FMView;

    CString GetComponentID(const CString& Name);

public:
    LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
    void UpdateSelection();
    void SetFMView(CFMView* pFMView) { m_FMView = pFMView; }

    void TrickleDown(HTREEITEM Start, BOOL bCheck);
    void ExpandAll  (HTREEITEM Start);
    void HideOrShowAll(HTREEITEM Start, bool bHide);

    void Hide();
    void Show();

    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
};

/*****************************************************************************/
// Class CFMView
// Manage creation/destruction and activation of the Feature Manager View
// Also gets the TVN_ENDLABELEDIT when the user finishes editing a label
// in the tree control.
/*****************************************************************************/
class CFMView : public CWnd
{
public:
    BOOL Create();

    #if 0
    // not used - keep for reference
    BOOL Add();
    #endif

    void Initialise();
    void TraverseComponent
    (
        int                         RecurseLevel,
        CFMView*                    pFMView     ,
        HTREEITEM                   Item        ,
        CComPtr <IComponent>        pComponent
    );

    virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
    BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    void GetTreeRect(CRect ParentRect, CRect& Rect);
    void GetShowRect(CRect ParentRect, CRect& Rect);
    void GetHideRect(CRect ParentRect, CRect& Rect);

protected:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
    afx_msg void OnBtnHide();
    afx_msg void OnBtnShow();

    BOOL OnDestroyNotify(bool bDeleteNotificationObject);

    DECLARE_MESSAGE_MAP()

// Data
public:
    // The actual Tree control
    CFMTreeCtrl                     m_TreeCtrl;
    CButton                         m_BtnShow;
    CButton                         m_BtnHide;

private:
    // Parent View of our window
    CWnd*                           m_pParent;

    // Holds the image in the SolidWorks Tab
    CBitmap                         m_Bitmap;


    // Receives FeatureManager notifications from SolidWorks
    FMFeatureManagerEvents*         m_pEventHandler;

    // Receives ModelDoc notifications from SolidWorks
    FMFeatureManagerEvents*         m_pModelEventHandler;

    friend class FMFeatureManagerEvents;
    friend class CFMTreeCtrl;
};


/*****************************************************************************/
// class FMFeatureManagerEvents
// Class to handle notifications from SolidWorks for the Feature Manager View
/*****************************************************************************/
class FMFeatureManagerEvents : public  CControlItem
{
public:
    ~FMFeatureManagerEvents();
    DECLARE_EVENTSINK_MAP()

    // ole event handlers
    HRESULT ActivateNotify  (VARIANT*       View);
    HRESULT DeactivateNotify(VARIANT*       View);
    HRESULT DestroyNotify   (VARIANT*       View);
    HRESULT OnNewSelection();

// Data
protected:
    CFMView*                        m_pFMView;

    friend class CFMView;
};

#endif
