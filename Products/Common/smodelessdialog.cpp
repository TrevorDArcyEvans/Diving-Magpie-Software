#include "stdafx.h"
#include "SModelessDialog.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CObArray SModelessDialog::sm_AllDialogs;

SModelessDialog::SModelessDialog 
(
	int IDD,
	CWnd* pParent
)
:SResizeDialog(IDD, pParent),
 m_IDD (IDD),
 m_AlreadyCreated (false),
 m_SelfDestruct (true),
 m_IsOpen (false),
 m_ShowStyle (SW_SHOW),
 m_IsShown (false)
{
	sm_AllDialogs.Add (this);
}//SModelessDialog::SModelessDialog

SModelessDialog::~SModelessDialog ()
{
	for (int i = 0; i < sm_AllDialogs.GetSize (); i++)
	{
		if (sm_AllDialogs[i] == this)
		{
			sm_AllDialogs.RemoveAt (i);
			break;
		}//if
	}//for
}//SModelessDialog::~SModelessDialog

BOOL SModelessDialog::OnInitDialog()
{
	BOOL RetVal = SResizeDialog::OnInitDialog ();

//	Modal dialogs call this for us
	InitializeNow ();

	return RetVal;
}//SModelessDialog::OnInitDialog

void SModelessDialog::SetNoAutoClose ()
{
	for (int i = 0; i < sm_AllDialogs.GetSize (); i++)
	{
		if (sm_AllDialogs[i] == this)
		{
			sm_AllDialogs.RemoveAt (i);
			break;
		}//if
	}//for
}//SModelessDialog::SetNoAutoClose

void SModelessDialog::CloseAll ()
{
	for (int i = 0; i < sm_AllDialogs.GetSize (); i++)
	{
		SModelessDialog* Dlg = (SModelessDialog*)sm_AllDialogs[i];
		sm_AllDialogs[i] = 0;

		Dlg->SetSelfDestruct (true);
		Dlg->OnOK ();
	}//for

	sm_AllDialogs.RemoveAll ();
}//SModelessDialog::CloseAll

bool SModelessDialog::DoModeless 
(
	CWnd* Parent
)
{
	bool RetVal = true;

	if (!m_AlreadyCreated)
	{
		RetVal = CDialog::Create(m_IDD,0);
		m_AlreadyCreated = true;
	}//if

    if (::IsWindow(m_hWnd))
    {
	    ShowWindow (SW_SHOW);
 
	    m_IsShown = true;
	    m_IsOpen = true;
    }//if

	return RetVal;
}//SModelessDialog::DoModeless

void SModelessDialog::PostNcDestroy ()
{
	m_IsOpen = false;

	CDialog::PostNcDestroy ();

	if (m_SelfDestruct)
		delete this;
	else
		m_AlreadyCreated = false;
	//if
}//SModelessDialog::PostNcDestroy

void SModelessDialog::OnCancel () 
{
	DestroyWindow ();
}//SModelessDialog::OnCancel 

void SModelessDialog::OnOK () 
{
	DestroyWindow ();
}//SModelessDialog::OnOK 

void SModelessDialog::Close ()
{
	OnOK ();
}//SModelessDialog::Close

bool SModelessDialog::IsOpen () const
{
	return m_IsOpen;
}//SModelessDialog::IsOpen

void SModelessDialog::Show ()
{
	if (!m_IsShown)
	{
		ShowWindow (m_ShowStyle);
		m_IsShown = true;
	}//if
}//SModelessDialog::Show

void SModelessDialog::Hide ()
{
	if (m_IsShown)
	{
        if (::IsWindow(m_hWnd))
        {
		    ShowWindow (SW_HIDE);
		    m_IsShown = false;
        }//if

		TransferCurrentPos ();
	}//if
}//SModelessDialog::Hide

