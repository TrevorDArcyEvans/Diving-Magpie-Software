#ifndef _SResizeMFCTemplate_h
#define _SResizeMFCTemplate_h

#include "SResizeBase.h"
#include "SRegistryAccess.hpp"
#include "TypeInfo.h"

//	Template for the actual concrete window class
//  T must be derived from CWnd and SResizeBase
template <class T>
class SResizeMFCTemplate : public T
{
	DECLARE_MESSAGE_MAP()

private:

	const HWND& GetHWND () const {return m_hWnd;}

public:
	
	virtual BOOL OnInitDialog();

    afx_msg void OnSize(UINT Type, int cx, int cy);
	afx_msg	void OnGetMinMaxInfo (MINMAXINFO* lpMMI);
	afx_msg	void OnDestroy ();
};//SResizeMFCTemplate

template <class T>
BOOL SResizeMFCTemplate<T>::OnInitDialog ()
{
    BOOL RetVal = T::OnInitDialog ();

    SRegistryAccess RegAc;

//  Use type info for unique registry name
    CString SubKey = _T ("Dialog Sizes\\");

    SubKey += typeid (T).name ();

    int Top    = RegAc.ReadInt (SubKey,_T ("Top"),-1);
    int Left   = RegAc.ReadInt (SubKey,_T ("Left"),-1);
    int Width  = RegAc.ReadInt (SubKey,_T ("Width"),-1);
    int Height = RegAc.ReadInt (SubKey,_T ("Height"),-1);

    if (Top > -1)   // Only resize if there are entries
    {
        MoveWindow (0,0,2000,2000,FALSE);   // Force to the maximum size to prevent clipping
        MoveWindow (Left,Top,Width,Height,FALSE);
    }//if

    return RetVal;
}//SResizeMFCTemplate<T>::OnInitDialog ()

template <class T>
void SResizeMFCTemplate<T>::OnDestroy ()
{
    CRect Rect;

    GetWindowRect (Rect);

    SRegistryAccess RegAc;

//  Use type info for unique registry name
    CString SubKey = _T ("Dialog Sizes\\");

    SubKey += typeid (T).name ();

    RegAc.WriteInt (SubKey,_T ("Top"),Rect.top);
    RegAc.WriteInt (SubKey,_T ("Left"),Rect.left);
    RegAc.WriteInt (SubKey,_T ("Width"),Rect.Width ());
    RegAc.WriteInt (SubKey,_T ("Height"),Rect.Height ());

    T::OnDestroy ();
}//SResizeMFCTemplate<T>::OnDestroy

template <class T>
void SResizeMFCTemplate<T>::OnSize
(
	UINT	Type, 
	int		cx, 
	int		cy
) 
{
	SResizeBase::InnerOnSize (Type,cx,cy);
	T::OnSize (Type,cx,cy);
}//SResizeMFCTemplate<T>::OnSize

template <class T>
void SResizeMFCTemplate<T>::OnGetMinMaxInfo 
(
	MINMAXINFO* lpMMI
)
{
	SResizeBase::InnerGetMinMax (lpMMI);
}//SResizeMFCTemplate<T>::OnGetMinMaxInfo

// Expansion of BEGIN_MESSAGE_MAP macro for template
template <class T>
const AFX_MSGMAP* PASCAL SResizeMFCTemplate<T>::_GetBaseMessageMap() 
{ 
	return &T::messageMap; 
} 

template <class T>
const AFX_MSGMAP* SResizeMFCTemplate<T>::GetMessageMap() const
{ 
	return &SResizeMFCTemplate<T>::messageMap; 
} 

template <class T>
AFX_COMDAT AFX_DATADEF const AFX_MSGMAP SResizeMFCTemplate<T>::messageMap = 
{ 
	&SResizeMFCTemplate<T>::_GetBaseMessageMap, 
	&SResizeMFCTemplate<T>::_messageEntries[0] 
};

template <class T>
AFX_COMDAT const AFX_MSGMAP_ENTRY SResizeMFCTemplate<T>::_messageEntries[] = 
{ 
//	End of expansion

//	Message map entries
	ON_WM_SIZE ()
	ON_WM_GETMINMAXINFO ()
    ON_WM_DESTROY ()
END_MESSAGE_MAP ()

#endif

