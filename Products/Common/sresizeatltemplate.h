#ifndef _SResizeATLTemplate_h
#define _SResizeATLTemplate_h

#include "SResizeBase.h"
#include "SPhysicalConstants.hpp"

//	Template for the actual concrete window class
//  T must be derived from CWindow and and SResizeBase
template <class T>
class SResizeATLTemplate : public T
{
private:

    SIZE                m_DesiredExtent;

	const HWND& GetHWND   () const {return m_hWnd;}
    SIZE GetDesiredExtent () const {return m_DesiredExtent;}       // Returns the size the dialog would like to be

public:

    SResizeATLTemplate ();

//	Message map
BEGIN_MSG_MAP(SResizeATLTemplate <T>)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(T)
END_MSG_MAP()

//	Handlers
	LRESULT OnSize (UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    HRESULT SetObjectRects (LPRECT r1,LPRECT r2) {return S_OK;}
};//SResizeATLTemplate

template <class T>
SResizeATLTemplate <T>::SResizeATLTemplate <T> () 
{
//  Get the control's natural size
    IOleObjectImpl <T>* Self = this;

    Self->GetExtent (DVASPECT_CONTENT,&m_DesiredExtent);

//  The size is in 0.01 mm. We need pixels
    HDC DC = ::CreateCompatibleDC (0);

    int xPixPerInch = GetDeviceCaps(DC,LOGPIXELSX);
	int yPixPerInch = GetDeviceCaps(DC,LOGPIXELSY);

    m_DesiredExtent.cx = m_DesiredExtent.cx * INCHES_PER_MM * xPixPerInch / 100;
    m_DesiredExtent.cy = m_DesiredExtent.cy * INCHES_PER_MM * yPixPerInch / 100;
}

template <class T>
LRESULT SResizeATLTemplate <T>::OnGetMinMaxInfo
(
	UINT	uMsg, 
	WPARAM	wParam, 
	LPARAM	lParam, 
	BOOL&	bHandled
)
{
	SResizeBase::InnerGetMinMax ((MINMAXINFO*)lParam);

	bHandled = TRUE;

	return 0;
}

template <class T>
LRESULT SResizeATLTemplate <T>::OnSetFocus 
(
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam,
	BOOL&	bHandled
)
{
//  Stop extra sizing problem 
    m_bUIActive = TRUE;

    bHandled = TRUE;

    return 0;
}

template <class T>
LRESULT SResizeATLTemplate <T>::OnSize 
(
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam,
	BOOL&	bHandled
)
{
	if (SResizeBase::IsFirstTime ())
	{
//		Let the In Place stuff know the new size
		RECT R;

		R.top = R.left = 0;

		R.bottom = HIWORD (lParam);
		R.right  = LOWORD (lParam);

		T::DoVerbUIActivate (&R,0);
    }//if

//	Do the resizing
	SResizeBase::InnerOnSize (wParam,LOWORD (lParam),HIWORD (lParam));

	bHandled = TRUE;

	return 0;
}

#endif
