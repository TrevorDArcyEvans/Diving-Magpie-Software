// SQueueThread.h: interface for the SQueueThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQUEUETHREAD_H__EF019445_5305_11D4_9447_006008B6C78C__INCLUDED_)
#define AFX_SQUEUETHREAD_H__EF019445_5305_11D4_9447_006008B6C78C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SThread.hpp"
#include "SEvent.h"
#include <deque>

template < typename T >
class SQueueNotifiable
{
public:
	virtual void OnNewEntry ( T &NewEntry) = 0;
  virtual void OnTimeOut() = 0 ;
};


template < typename T >
class SQueueThread : public SThread  
{

public:
  typedef std::deque<T>  QUEUELIST ;

protected:
  QUEUELIST                             m_Queue ;
	CSimpleArray < SQueueNotifiable<T>* > m_Notifiees;

	mutable SCriticalSection	            m_NotifieeSema;
  mutable SCriticalSection              m_QueueSema ;

	SEvent						                    m_DataAvailable ;
  DWORD                                 m_Timeout ;

  bool                                  m_RunQueue ;

  virtual void NotifyAll( ) ;           // Called When Data Arrived ;
  virtual void TimedOut( ) ;            // Called When Timeout Expired
  virtual void ClearQueue() ;           // Clear the Data Queue

public:
	SQueueThread( DWORD Timeout = 60000 );
	virtual ~SQueueThread();

	int     NotifieeCount () const;

	void AddNotifiee    ( SQueueNotifiable<T>* Notifiee);
	void RemoveNotifiee (const SQueueNotifiable<T>* Notifiee);

  void AddEntry( T &NewEntry ) ;
  void EntryPoint ();

  void StartQueue() ;
  void StopQueue() ;
  bool IsQueueRunning() ;
  int  GetQueueLength() ;

};

#endif // !defined(AFX_SQUEUETHREAD_H__EF019445_5305_11D4_9447_006008B6C78C__INCLUDED_)
