#include "stdafx.h"
#include "SLogShell.hpp"
#include "Logger.h"

SLogShell* SLogShell::sm_Instance = 0;

SLogShell::SLogShell ()
:m_Logger (0)
{
	HRESULT res = CoCreateInstance (CLSID_SLogger,
									0,
									CLSCTX_ALL,
									IID_ILogger,
									(void**)&m_Logger);

	if (!SUCCEEDED (res))
		m_Logger = 0;
	//if
}//SLogShell::SLogShell

SLogShell::~SLogShell ()
{
	if (m_Logger)
		m_Logger->Release ();
	//if
}//SLogShell::~SLogShell

SLogShell* SLogShell::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SLogShell ;
	//if

	return sm_Instance;
}//SLogShell::Instance

void SLogShell::Destroy ()
{
	if (sm_Instance)
	{
		delete sm_Instance;
		sm_Instance = 0;
	}//if
}//SLogShell::Destroy

void SLogShell::LogMessage 
(
	const CString& Message,
	const CString& SourceApp,
	short Severity
)const
{
	if (m_Logger)
		m_Logger->LogMessage (Message.AllocSysString (),SourceApp.AllocSysString (),Severity);
	//if
}//SLogShell::LogMessage

