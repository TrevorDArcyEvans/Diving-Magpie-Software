#include "stdafx.h"
#include "SResizeDialogBar.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(SResizeDialogBar, CDialogBar)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO ()
END_MESSAGE_MAP()

void SResizeDialogBar::OnSize(UINT nType, int cx, int cy) 
{
//	if (m_RegName == "")
//		return;
	//if

	if (m_FirstTime)
	{
		CRect Rect;
		GetClientRect (Rect);

		m_Sizer.Initialize (CSize (Rect.Width (),Rect.Height ()));
	}
	else
	{
		m_Sizer.Resize (CSize (cx,cy));

		if (::IsWindow (m_hWnd))
			DoDeferSize (cx,cy);
		//if
	}//if

	CDialogBar::OnSize(nType, cx, cy);

	m_FirstTime = false;

	Invalidate ();

/*
	if (m_FirstTime)
	{
		m_FirstTime = false;

		LoadSizeFromReg ();

		if (m_FixedWidth != 0)
			m_FixedWidth = sm_Sizes[m_SizeIdx].m_WindowWidth;
		//if

		if (m_FixedHeight != 0)
			m_FixedHeight = sm_Sizes[m_SizeIdx].m_WindowHeight;
		//if

		PostMessage (WM_SIZE,0,
				     MAKELPARAM (sm_Sizes[m_SizeIdx].m_ClientWidth,
					             sm_Sizes[m_SizeIdx].m_ClientHeight));
	}
	else
	{	
		CRect Rect;
		GetWindowRect (Rect);

		sm_Sizes[m_SizeIdx].m_WindowWidth = Rect.Width ();
		sm_Sizes[m_SizeIdx].m_WindowHeight = Rect.Height ();

		GetClientRect (Rect);

		sm_Sizes[m_SizeIdx].m_ClientWidth = Rect.Width ();
		sm_Sizes[m_SizeIdx].m_ClientHeight = Rect.Height ();
	}//if
*/
}//SResizeDialogBar

void SResizeDialogBar::LoadSizeFromReg ()
{	
/*
	if (m_RegName != "")
	{
		for (int i = 0; i < sm_Sizes.GetSize (); i++)
		{
			if (sm_Sizes[i].m_Name == m_RegName)
			{
				m_SizeIdx = i;

				SetWindowPos (0,0,0,
							  sm_Sizes[i].m_WindowWidth,
							  sm_Sizes[i].m_WindowHeight,
							  SWP_NOMOVE|SWP_NOZORDER|SWP_NOREPOSITION);

				return;
			}//if
		}//for

		CString  Key = m_RegName + "DlgSize";
		CWinApp* App = AfxGetApp ();

		CRect RectC;
		GetClientRect (RectC);
		CRect RectW;
		GetWindowRect (RectW);

		sm_Sizes.Add (SSizeSaver (m_RegName,
								  App->GetProfileInt (Key,"ClientWidth",RectC.Width ()),
								  App->GetProfileInt (Key,"ClientHeight",RectC.Height ()),
								  App->GetProfileInt (Key,"WindowWidth",RectW.Width ()),
								  App->GetProfileInt (Key,"WindowHeight",RectW.Height ())));

		m_SizeIdx = sm_Sizes.GetSize () - 1;

		SetWindowPos (0,0,0,
					  sm_Sizes[m_SizeIdx].m_WindowWidth,
					  sm_Sizes[m_SizeIdx].m_WindowHeight,
					  SWP_NOMOVE|SWP_NOZORDER|SWP_NOREPOSITION);
	}//if
*/
}//SResizeDialogBar::LoadSizeFromReg

void SResizeDialogBar::SaveSizesToReg ()
{
/*
	for (int i = 0; i < sm_Sizes.GetSize (); i++)
	{
		sm_Sizes[i].SaveSizeToReg ();
	}//for
*/
}//SResizeDialogBar::SaveSizesToReg

void SResizeDialogBar::OnGetMinMaxInfo
(
	MINMAXINFO* lpMMI 
)
{
	if (m_FixedWidth > 0)
	{
		lpMMI->ptMaxTrackSize.x = m_FixedWidth;
		lpMMI->ptMinTrackSize.x = m_FixedWidth;
	}//if

	if (m_FixedHeight > 0)
	{
		lpMMI->ptMaxTrackSize.y = m_FixedHeight;
		lpMMI->ptMinTrackSize.y = m_FixedHeight;
	}//if
}//SResizeDialogBar::OnGetMinMaxInfo


