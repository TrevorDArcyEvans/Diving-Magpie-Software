/*
$History: SMutex.h $
 * 
 * *****************  Version 1  *****************
 * User: Jasper       Date: 29-07-00   Time: 17:44
 * Created in $/CMIDS/Projects/Common
*/

#ifndef _SMutex_h
#define _SMutex_h

//  No MFC version of CMutex
//  Note: Named mutexes have not been tested
class SMutex
{
private:

    HANDLE  m_MutexHandle;              // Handle to the actual mutex

public:

    SMutex (LPCTSTR Name = 0);

//  Returns the result of the wait 
//  WAIT_ABANDONED : The thread holding the mutex died
//  WAIT_TIMEOUT   : Timeout occured before the other thread yielded
//  WAIT_OBJECT_0  : Caller got hold of the mutex
    DWORD EnterMutex (DWORD Timeout = INFINITE);   
    
    void LeaveMutex ();
};//SMutex

//  Class to enter mutex on construction an leave it on destruction
class SMutexLock
{
private:

    SMutex& m_Mutex;

public:

    SMutexLock (SMutex& Mutex):m_Mutex (Mutex) {m_Mutex.EnterMutex ();}
    ~SMutexLock () {m_Mutex.LeaveMutex ();}
};//SMutexLock

#endif

