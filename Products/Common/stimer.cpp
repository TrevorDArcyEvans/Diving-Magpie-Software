#include "stdafx.h"
#include "STimer.hpp"
#include "SException.hpp"

std::vector <STimer*> STimer::sm_These;

void CALLBACK STimer::TimerCallback 
(
	HWND	Window,
	UINT	Msg,
	UINT	ID,
	DWORD	Time
)
{
	STimer* Timer;

	for (int i = 0; i < sm_These.size (); i++)
	{
		Timer = (STimer*)sm_These[i];

		if (ID == Timer->m_ID)
		{
			if (Timer->m_Started)
				Timer->DoCallback ();
			//if

			return;
		}//if
	}//for
}//STimer::TimerCallback

void STimer::DoCallback ()
{
	if (m_CallbackObject)
		m_CallbackObject->Timeout ();
	//if
}//STimer::DoCallback

void STimer::Start ()
{
	if (!m_Started)
	{
		if ((m_ID = SetTimer (0,0,m_Period,TimerCallback)) == 0)
			throw new SException (_T ("Out of timers."));
		//if

		m_Started = true;
	}//if
}//STimer::Start

void STimer::Stop  ()
{
	if (m_Started)
	{
		KillTimer (0,m_ID);

		m_Started = false;
	}//if
}//STimer::Stop

STimer::STimer 
(
	DWORD	Period,
	bool	Repeat,
	bool	StartNow
)
:m_Period			(Period),
 m_Repeat			(Repeat),
 m_Started			(false),
 m_CallbackObject	(0),
 m_ID				(-1)
{
	sm_These.push_back (this);

	if (StartNow)
		Start ();
	//if
}//STimer::STimer

STimer::STimer 
(
	DWORD			Period,
	ITimeoutable*	CallbackObj,
	bool			Repeat,
	bool			StartNow
)
:m_Period			(Period),
 m_Repeat			(Repeat),
 m_Started			(false),
 m_CallbackObject	(CallbackObj),
 m_ID				(-1)
{
	sm_These.push_back (this);

	if (StartNow)
		Start ();
	//if
}//STimer::STimer

STimer::STimer ()
:m_Period			(0),
 m_Repeat			(false),
 m_Started			(false),
 m_CallbackObject	(0)	,
 m_ID				(-1)
{
}//STimer::STimer

void STimer::CreateTimer
(
	DWORD			Period,
	ITimeoutable*	CallbackObj,
	bool			Repeat,
	bool			StartNow
)
{
	if (m_ID > -1)
		throw new SException (_T ("Attempt to create timer twice."));
	//if

	m_Period			= Period;
	m_Repeat			= Repeat;
	m_CallbackObject	= CallbackObj;

	sm_These.push_back (this);

	if (StartNow)
		Start ();
	//if
}//STimer::CreateTimer

void STimer::CreateTimer
(
	DWORD			Period,
	bool			Repeat,
	bool			StartNow
)
{
	CreateTimer (Period,0,Repeat,StartNow);
}//STimer::CreateTimer

STimer::~STimer ()
{
	if (m_Started)
		Stop ();
	//if

	std::vector <STimer*>::iterator it;

	for (it = sm_These.begin (); it != sm_These.end (); it++)
	{
		if (*it == this)
		{
			sm_These.erase (it);
			break;
		}//if
	}//for
}//STimer::~STimer
