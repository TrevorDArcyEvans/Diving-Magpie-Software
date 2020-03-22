/*
History:
    [01]    TDE     26May00     added more debugging code
*/

#include "stdafx.h"
#include "SThread.hpp"
#include "SMethodLock.hpp"
#include "LogEvent.h"
#include <process.h>
#include <typeinfo>

#ifndef _AFX
#include "MFCStringImpl.h"
using NotMFC::CString;
#else
#include <afx.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SThread::~SThread ()
{
}//SThread::~SThread

void SThread::Run (DWORD CoInitFlag )
{
	SMethodLock Lock (m_Section);

  m_CoInitFlag = CoInitFlag ;

	if (!m_Running)		// Only run it once
	{
		m_Starting = true;

        unsigned long Res = _beginthread (ThreadFunc,
                                          0,    // Default stack size
                                          (void*)this);
	}//if
}//SThread::Run

void SThread::Kill ()
{
	SMethodLock Lock (m_Section);

	m_Stopping = true;
	m_KillEvent.SetEvent ();
}//SThread::Kill

void SThread::Jog ()
{
	SMethodLock Lock (m_Section);

	m_Jogged = true;

	m_KillEvent.SetEvent ();
}//SThread::Jog

bool SThread::WasJogged ()
{
	SMethodLock Lock (m_Section);

	bool RetVal = m_Jogged;

	m_KillEvent.ResetEvent ();

	m_Jogged = false;

	return RetVal;
}//SThread::WasJogged

void SThread::TemplateEntryPoint ()
{

    CString ClassName;

    try
    {
//      Determine the derived class name
//      Do this now in case this is corrupted when we need the name
        USES_CONVERSION;

        ClassName = A2T (typeid (*this).name ());
    }
    catch (...)
    {
        ClassName = _T("Not Known");
    }//try

	try 
	{
        m_Section.Lock ();
		m_Running = true;
		m_Starting = false;
		m_Section.Unlock ();

		EntryPoint ();

		m_Section.Lock ();
		m_Running = false;
		m_Stopping = false;
		m_RunningEvent.SetEvent ();
		m_Section.Unlock ();

		if (m_SelfDestruct)
		{
			delete this;
    }

	}
	catch (...)
	{
		LogEvent (_T ("Unknown exception in SThread::TemplateEntryPoint. Derived class is: %s"),(LPCTSTR)ClassName);
	}//try


}//SThread::TemplateEntryPoint

void SThread::ThreadFunc 
(
	LPVOID Param
)
{

  if ( ((SThread*)Param)->m_CoInitFlag != -1 )
    CoInitializeEx( NULL, ((SThread*)Param)->m_CoInitFlag ) ;

	((SThread*)Param)->TemplateEntryPoint ();

  if ( ((SThread*)Param)->m_CoInitFlag != -1 )
    CoUninitialize() ;  // Clean Up COM

    _endthread ();
}//SThread::ThreadFunc

void SThread::SetSelfDestruct 
(
	bool Destruct
)
{
	SMethodLock Lock (m_Section);

	m_SelfDestruct = Destruct;
}//SThread::SetSelfDestruct

bool SThread::IsRunning () const 
{
	SMethodLock Lock (m_Section);

	return m_Running;
}//SThread::IsRunning

bool SThread::IsStarting () const
{
	SMethodLock Lock (m_Section);

	return m_Starting;
}//SThread::IsStarting

bool SThread::IsStopping () const
{
	SMethodLock Lock (m_Section);

	return m_Stopping;
}//SThread::IsStopping

bool SThread::WaitToFinish 
(
	DWORD Milliseconds
)const
{
	if (Milliseconds == 0)
		Milliseconds = INFINITE;
	//if

	if (::WaitForSingleObject (m_RunningEvent,Milliseconds) == WAIT_TIMEOUT)
		return false;
	else
		return true;
	//if
}//SThread::WaitToFinish

