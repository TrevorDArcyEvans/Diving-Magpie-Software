#include "stdafx.h"
#include "SInstanceLimiter.hpp"
#include <afxmt.h>
#include <afxwin.h>

SInstanceLimiter::SInstanceLimiter
(
	const CString&	ImageName,
	int				NumAllowed
)
:m_LockedOkay		(false),
 m_Semaphore		(0),
 m_ImageName		(ImageName),
 m_NumAllowed		(NumAllowed)
{
}//SInstanceLimiter::SInstanceLimiter

SInstanceLimiter::SInstanceLimiter 
(
	const CString& ImageName,
	const CString& RegistryVal,
	int			   Default
)
:m_LockedOkay		(false),
 m_Semaphore		(0),
 m_ImageName		(ImageName),
 m_NumAllowed		(-1),
 m_RegistryValue	(RegistryVal),
 m_DefaultNum		(Default)
{
}//SInstanceLimiter::SInstanceLimiter

SInstanceLimiter::~SInstanceLimiter ()
{
	if (m_Semaphore)
	{
		if (m_LockedOkay)
			m_Semaphore->Unlock ();
		//if

		delete m_Semaphore;
	}//if
}//SInstanceLimiter::~SInstanceLimiter

bool SInstanceLimiter::CanIStartUp ()
{
	if (m_Semaphore)
		return m_LockedOkay;
	//if
	
	if (m_NumAllowed < 0)
	{
		CString Key = m_RegistryValue.Element ("\\",0);
		CString Val = m_RegistryValue.Element ("\\",1);

		m_NumAllowed = AfxGetApp ()->GetProfileInt (Key,Val,m_DefaultNum);
	}//if

	if (m_NumAllowed > 0)
		m_Semaphore = new CSemaphore (m_NumAllowed,m_NumAllowed,m_ImageName);
	else
		m_Semaphore = 0;
	//if

	if (m_Semaphore)
	{
		m_LockedOkay = m_Semaphore->Lock (0);

		return m_LockedOkay;
	}
	else
		return true;
	//if
}//SInstanceLimiter::CanIStartUp

void SInstanceLimiter::ActivateSomeoneElse ()
{
	HWND hWnd = GetTopWindow (0);

	CWnd  WndTemp;
	CWnd* Wnd = &WndTemp;

	Wnd->Attach (hWnd);

	while (Wnd && ::IsWindow (Wnd->m_hWnd))
	{
		CString Name;

		Wnd->GetWindowText (Name);

		if ((Name == m_ImageName)
		 ||	(Name.Find (m_ImageName + " - [") == 0)
		 || (Name.Find (m_ImageName + " - ") == 0) && (Name.Find ("[") == -1))
		{
			if (Wnd->IsIconic ())
				Wnd->ShowWindow (SW_RESTORE);
			//if

			Wnd->SetForegroundWindow ();

			break;
		}//if

		Wnd = Wnd->GetNextWindow (GW_HWNDNEXT);
	}//while

	WndTemp.Detach ();
}//SInstanceLimiter::ActivateSomeoneElse

