#include "stdafx.h"
#include "SResizeDialog.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(SResizeDialog, CDialog)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_GETMINMAXINFO ()
END_MESSAGE_MAP()

SSizeSaverArray SResizeDialog::sm_Sizes;

SResizeDialog::~SResizeDialog () 
{
	TransferCurrentPos ();
}

void SResizeDialog::InitializeNow ()
{
	if (!m_InitializeNowCalled)
	{
		m_InitializeNowCalled = true;

		CRect Rect;
		GetClientRect (Rect);

		m_Sizer.Initialize (CSize (Rect.Width (),Rect.Height ()));
	}//if
}//SResizeDialog::InitializeNow

void SResizeDialog::OnMove(int x, int y) 
{
	CDialog::OnMove (x,y);

	GetWindowRect (m_CurrWindRect);
	GetClientRect (m_CurrClientRect);
}//SResizeDialog::OnMove

void SResizeDialog::OnSize(UINT nType, int cx, int cy) 
{
	if (m_RegName == "")
		return;
	//if

	if (m_FirstTime)
		InitializeNow ();
	else
	{
		m_Sizer.Resize (CSize (cx,cy));

		if (::IsWindow (m_hWnd))
			DoDeferSize (cx,cy);
		//if
	}//if

	CDialog::OnSize(nType, cx, cy);

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
		GetWindowRect (m_CurrWindRect);
		GetClientRect (m_CurrClientRect);
	}//if
}

void SResizeDialog::InitResizing ()
{
	LoadSizeFromReg ();

	if (m_RegName != "")
	{
		for (int i = 0; i < sm_Sizes.GetSize (); i++)
		{
			if (sm_Sizes[i].m_Name == m_RegName)
			{
				m_SizeIdx = i;

				SetWindowPos (0,
							  sm_Sizes[m_SizeIdx].m_WindowTLX,
							  sm_Sizes[m_SizeIdx].m_WindowTLY,
							  0,0,
							  SWP_NOSIZE|SWP_NOZORDER);

				break;
			}//if
		}//for
	}//if
}//SResizeDialog::LoadNow

BOOL SResizeDialog::OnInitDialog()
{
	BOOL RetVal = CDialog::OnInitDialog ();

	return RetVal;
}//SResizeDialog::OnInitDialog

void SResizeDialog::TransferCurrentPos () const
{
	if (m_SizeIdx > -1)
	{
		sm_Sizes[m_SizeIdx].m_WindowTLX = m_CurrWindRect.left;
		sm_Sizes[m_SizeIdx].m_WindowTLY = m_CurrWindRect.top;
		sm_Sizes[m_SizeIdx].m_WindowWidth = m_CurrWindRect.Width ();
		sm_Sizes[m_SizeIdx].m_WindowHeight = m_CurrWindRect.Height ();
		sm_Sizes[m_SizeIdx].m_ClientWidth = m_CurrClientRect.Width ();
		sm_Sizes[m_SizeIdx].m_ClientHeight = m_CurrClientRect.Height ();
	}//if
}//SResizeDialog::TransferCurrentPos

void SResizeDialog::LoadSizeFromReg ()
{	
	if (m_RegName != "")
	{
		for (int i = 0; i < sm_Sizes.GetSize (); i++)
		{
			if (sm_Sizes[i].m_Name == m_RegName)
			{
				m_SizeIdx = i;

				SetWindowPos (0,
							  sm_Sizes[m_SizeIdx].m_WindowTLX,
							  sm_Sizes[m_SizeIdx].m_WindowTLY,
							  sm_Sizes[m_SizeIdx].m_WindowWidth,
							  sm_Sizes[m_SizeIdx].m_WindowHeight,
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
								  App->GetProfileInt (Key,_T ("ClientWidth"),RectC.Width ()),
								  App->GetProfileInt (Key,_T ("ClientHeight"),RectC.Height ()),
								  App->GetProfileInt (Key,_T ("WindowWidth"),RectW.Width ()),
								  App->GetProfileInt (Key,_T ("WindowHeight"),RectW.Height ()),
								  App->GetProfileInt (Key,_T ("WindowTLX"),RectW.left),
								  App->GetProfileInt (Key,_T ("WindowTLY"),RectW.top)));

		m_SizeIdx = sm_Sizes.GetSize () - 1;

		SetWindowPos (0,
					  sm_Sizes[m_SizeIdx].m_WindowTLX,
					  sm_Sizes[m_SizeIdx].m_WindowTLY,
					  sm_Sizes[m_SizeIdx].m_WindowWidth,
					  sm_Sizes[m_SizeIdx].m_WindowHeight,
					  SWP_NOMOVE|SWP_NOZORDER|SWP_NOREPOSITION);
	}//if
}//SResizeDialog::LoadSizeFromReg

void SResizeDialog::SaveSizesToReg ()
{
	for (int i = 0; i < sm_Sizes.GetSize (); i++)
	{
		sm_Sizes[i].SaveSizeToReg ();
	}//for
}//SResizeDialog::SaveSizesToReg

void SResizeDialog::OnGetMinMaxInfo
(
	MINMAXINFO* lpMMI 
)
{
	lpMMI->ptMinTrackSize.x = m_MinSize.cx;
	lpMMI->ptMinTrackSize.y = m_MinSize.cy;

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
}//SResizeDialog::OnGetMinMaxInfo

void SSizeSaver::SaveSizeToReg () const
{
	if (m_Name != "")
	{
		CString  Key = m_Name + "DlgSize";
		CWinApp* App = AfxGetApp ();

		App->WriteProfileInt	(Key,_T ("WindowWidth"),m_WindowWidth);
		App->WriteProfileInt	(Key,_T ("WindowHeight"),m_WindowHeight);
		App->WriteProfileInt	(Key,_T ("ClientWidth"),m_ClientWidth);
		App->WriteProfileInt	(Key,_T ("ClientHeight"),m_ClientHeight);
		App->WriteProfileInt	(Key,_T ("WindowTLX"),m_WindowTLX);
		App->WriteProfileInt	(Key,_T ("WindowTLY"),m_WindowTLY);
	}//if
}//SSizeSaver::SaveSizeToReg

