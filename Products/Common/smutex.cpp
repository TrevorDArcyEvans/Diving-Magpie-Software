#include "stdafx.h"
#include "SMutex.h"

SMutex::SMutex 
(
    LPCTSTR Name
)
{
//  Just create the mutes, without owning it
    m_MutexHandle = ::CreateMutex (0,FALSE,Name);
}//SMutex::SMutex

DWORD SMutex::EnterMutex 
(
    DWORD Timeout
)
{
    return ::WaitForSingleObject (m_MutexHandle,Timeout);
}//SMutex::EnterMutex

void SMutex::LeaveMutex ()
{
    ::ReleaseMutex (m_MutexHandle);
}//SMutex::LeaveMutex
