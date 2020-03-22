#include "stdafx.h"
#include "SCriticalSection.h"

SCriticalSection::SCriticalSection ()
{
	::InitializeCriticalSection (&m_Section);
}

SCriticalSection::~SCriticalSection ()
{
	::DeleteCriticalSection (&m_Section);
}

void SCriticalSection::Lock ()
{
	::EnterCriticalSection (&m_Section);
}

void SCriticalSection::Unlock ()
{
	::LeaveCriticalSection (&m_Section);
}

