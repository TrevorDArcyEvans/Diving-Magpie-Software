#ifndef __SThread_hpp
#define __SThread_hpp

#include "stdafx.h"
#include "SEvent.h"
#include "SCriticalSection.h"

class SThread			// Class to make thread handling easier
{
private:

	mutable SCriticalSection	m_Section;	

	bool						m_Running;		// Is the thread running
	bool						m_SelfDestruct;	// Should object delete on thread termination
	bool						m_Starting;		// Thread has been launched but is not yet running
	bool						m_Stopping;		// Thread has be killed but has not yet terminated
	bool						m_Jogged;		// Set by Jog ()
							
	static void ThreadFunc (void* Param);		// Entry point for thread
	void TemplateEntryPoint ();					// Template method for thread entry

	SEvent						m_RunningEvent;	// Set when thread is finishing

protected:

	SThread ()://m_Thread (0),
               m_Running (false),
               m_SelfDestruct (false),
               m_Starting (false),
               m_Stopping (false),
               m_RunningEvent (SEvent::E_UNSET,SEvent::E_MANUAL),
               m_KillEvent (SEvent::E_UNSET,SEvent::E_MANUAL) {}
	virtual ~SThread ();

	bool WasJogged ();							// See if kill event set because it was jogged

	SEvent		m_KillEvent;					// Indicates a thread shutdown requested
  DWORD     m_CoInitFlag ;

public:

	void Run ( DWORD CoInitFlag = -1 );								// Start the thread
	void Kill ();								// Stop the thread
	void Jog ();								// Use the KillEvent to cycle the thread

	void SetSelfDestruct (bool Destruct);		// Set m_SelfDestruct

	bool IsRunning () const;					// Is it running
	bool IsStarting ()const;					// Is it starting
	bool IsStopping ()const;					// Is it stopping

	bool WaitToFinish (DWORD Milliseconds) const;	// Block until thread shuts down

	virtual void EntryPoint () = 0;				// Override for your thread function
};//SThread

#endif

