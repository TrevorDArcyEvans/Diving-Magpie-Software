#include "stdafx.h"
#include "SEvent.h"

SEvent::SEvent 
(
	InitialStates	Init,
	ResetTypes		Reset,
	LPCTSTR			Name
)
{
	m_Handle = ::CreateEvent (0,Reset == E_MANUAL,Init == E_SET,Name);
}//SEvent::SEvent

SEvent::~SEvent ()
{
	::CloseHandle (m_Handle);
}//SEvent::~SEvent

void SEvent::SetEvent ()
{
	::SetEvent (m_Handle);
}

void SEvent::ResetEvent ()
{
	::ResetEvent (m_Handle);
}

void SEvent::PulseEvent ()
{
	::PulseEvent (m_Handle);
}
