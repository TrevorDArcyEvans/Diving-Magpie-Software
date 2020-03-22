// SQueueThread.cpp: implementation of the SQueueThread class.
// Basically, a templated class that maintains a queue of data and signals
// clients via a seperate thread that there is new data available.
// It decouples the Queue writer from the Queue Reader. Based heavily
// on SFileReader.
//////////////////////////////////////////////////////////////////////

#ifndef _SQUEUETHREADIMPL_
#define _SQUEUETHREADIMPL_

#include "stdafx.h"
#include "SQueueThread.h"
#include "SMethodLock.hpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
template < typename T >
SQueueThread<T>::SQueueThread( DWORD Timeout ) : m_Timeout( Timeout ), m_RunQueue(true)
{
  SetSelfDestruct (true);
}

template< typename T >
SQueueThread<T>::~SQueueThread()
{
  ClearQueue() ;

}

template< typename T >
int SQueueThread<T>::NotifieeCount () const
{
  try
  {
	  SMethodLock Lock (m_NotifieeSema);

	  return m_Notifiees.GetSize ();
  }
  catch( ...)
  {
    return 0 ;
  }

}//SQueueThread::NotifieeCount


template< typename T >
void SQueueThread<T>::AddNotifiee ( SQueueNotifiable<T>* Notifiee )
{
  try
  {
	  SMethodLock Lock (m_NotifieeSema);

	  for (int i = 0; i < m_Notifiees.GetSize (); i++)
	  {
		  if (m_Notifiees[i] == Notifiee)
			  return;
		  //if
	  }//for

	  m_Notifiees.Add (Notifiee);
  }
  catch(...)
  {
    return ;
  }

}//SQueueThread::AddNotifiee



template < typename T >
void SQueueThread<T>::RemoveNotifiee (const SQueueNotifiable<T>* Notifiee )
{
  try
  {
	  SMethodLock Lock (m_NotifieeSema);

	  for (int i = 0; i < m_Notifiees.GetSize (); i++)
	  {
		  if (m_Notifiees[i] == Notifiee)
		  {
			  m_Notifiees.RemoveAt (i);
			  return;
		  }//if
	  }//for
  }
  catch ( ... )
  {
    return ;
  }

}//SQueueThread::RemoveNotifiee

template< typename T>
void SQueueThread<T>::AddEntry( T &NewEntry )
{
  try
  {
    SMethodLock Lock(m_QueueSema) ;

	  if ( IsRunning () )
	  {
		  m_Queue.push_back( NewEntry ) ;

		  if ( m_RunQueue ) 
        SetEvent( m_DataAvailable ) ;
	  }
  }
  catch ( ... )
  {
    return ;
  }
}
 
template <  typename T >
void SQueueThread<T>::EntryPoint ()
{

  try
  {
	  HANDLE  hEventVector[2] = { m_KillEvent, m_DataAvailable  };
	  DWORD   stat = 0 ;
	  HRESULT hr = S_OK;

  
    while ( true )
    {
	    stat = WaitForMultipleObjects(2, (void * const *)&hEventVector, false, m_Timeout ) ;
	    if ( stat == WAIT_FAILED )
	    {
		    ATLTRACE( _T("SQueueThread::EntryPoint WaitForMultipleObjects() failed\n" ));
        return ;
	    }
	    else if ( stat == WAIT_OBJECT_0 )								  // We are told to stop Waiting
	    {																                
        ClearQueue()  ;                                  // Clear the Data Queue
		    return ;
	    }
	    else if ( stat == WAIT_OBJECT_0+1 )								// Data is available
	    {
		    NotifyAll ( ) ;		
	    }
	    else if ( stat == WAIT_TIMEOUT )								  // Timed Out Waiting For Data
	    {
        TimedOut( ) ;
		  }
    } // while

	  return ;
  }
  catch (...)
  {
    return ;
  }
}


template <  typename T >
void SQueueThread<T>::NotifyAll()
{
  T   QueueEntry ;
  try
  {
    bool bListEmpty = true ;

    {   // Lock the Input Queue 

        SMethodLock Lock(m_QueueSema) ;	
       
        // Only Process, if the Queue is Running

        if ( m_RunQueue ) 
			    bListEmpty = m_Queue.empty() ;

	  } // Release lock

	  while ( !bListEmpty )
	  {
		  { // Pop the Input Queue
        SMethodLock Lock(m_QueueSema) ;	
				  
			  QueueEntry = m_Queue.front() ;

			  m_Queue.pop_front() ;

			  bListEmpty = m_Queue.empty() ;

		  } //

      // Notify Every One


      SMethodLock Lock( m_NotifieeSema ) ;

      for (int i = 0; i < m_Notifiees.GetSize (); i++)
    	  m_Notifiees[i]->OnNewEntry ( QueueEntry );
      
    }
  }
  catch( ... )
  {
    ATLTRACE(_T("SQueueThread<T>::NotifyAll(): Exception\n") ) ;
    //delete pQueueEntry ; // Delete the QueueEntry, if we have a proble
  }

}


template <  typename T >
void SQueueThread<T>::TimedOut()
{

  SMethodLock Lock( m_NotifieeSema ) ;

  for (int i = 0; i < m_Notifiees.GetSize (); i++)
    m_Notifiees[i]->OnTimeOut () ;

}


template < typename T >
void SQueueThread<T>::ClearQueue()
{
  try
  {
    SMethodLock Lock(m_QueueSema) ;		
    T   Entry ;

/*
    QUEUELIST::iterator itr ;

	  for ( itr = m_Queue.begin(); itr != m_Queue.end(); itr++ )
		{
			if ( *itr )
			{
				pEntry = *itr ;
				delete pEntry ;
				*itr = 0 ;
			 }
		 }
*/

     m_Queue.erase(m_Queue.begin(),m_Queue.end() ) ;
  }
  catch( ... )
  {
    return ;
  }
}


// Enable Notification of new data in the queue

template < typename T >
void SQueueThread<T>::StartQueue()
{
  SMethodLock Lock(m_QueueSema) ;
  m_RunQueue = true ;
	SetEvent( m_DataAvailable ) ; // Trigger processing of queued data
}
  

// Disable the Notification of new data in the queue

template < typename T >
void SQueueThread<T>::StopQueue()
{
  SMethodLock Lock(m_QueueSema) ;
  m_RunQueue = false ;
}

// Get the Notification State of the Queue

template < typename T >
bool SQueueThread<T>::IsQueueRunning()
{
  SMethodLock Lock(m_QueueSema) ;
  return m_RunQueue ;
}

// Get the Queue Length

template < typename T >
int SQueueThread<T>::GetQueueLength()
{
  SMethodLock Lock(m_QueueSema) ;
  return m_Queue.size() ;
}


#endif

