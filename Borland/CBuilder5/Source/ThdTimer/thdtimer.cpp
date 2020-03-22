////////////////////////////////////////////////////////////////////////////////
// TThreadedTimer component - Heart 5.0
//
// Component which allows to have an accurate timer (based on Delphi
// Developper's Journal, issue of May 1996)
//
// by Alan GARNY
//    gry@physiol.ox.ac.uk
//    http://www.physiol.ox.ac.uk/~gry
//
// © Copyright 1996-97
////////////////////////////////////////////////////////////////////////////////
// Date of Creation: 24/01/97
//
// Modifications: (model: [<initials>, dd/mm/yy] <what has been done>)
//
////////////////////////////////////////////////////////////////////////////////

#include <vcl\vcl.h>
#pragma hdrstop

#include "ThdTimer.h"

////////////////////////////////////////////////////////////////////////////////
// TThreadedTimer

////////////////////////////////////////////////////////////////////////////////
// TThreadedTimer: constructor

__fastcall TThreadedTimer::TThreadedTimer(TComponent *aOwner)
   : TComponent(aOwner),
     FEnabled(true),
     FInterval(1000),
     FOnTimer(NULL),
     FThreadPriority(tpNormal)
{
   FTimerThread = new TTimerThread(false);

   FTimerThread->OwnerTimer = this;
}

////////////////////////////////////////////////////////////////////////////////
// TThreadedTimer: destructor

__fastcall TThreadedTimer::~TThreadedTimer()
{
   FEnabled = false;

   UpdateTimer();

   delete FTimerThread;
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::Timer()
{
   if (FOnTimer)
      FOnTimer(this);
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::UpdateTimer()
{
   if (!FTimerThread->Suspended)
      FTimerThread->Suspend();

   if (FInterval && FEnabled && FOnTimer)
      if (FTimerThread->Suspended)
         FTimerThread->Resume();
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::SetEnabled(const bool Value)
{
   if (Value != FEnabled)
   {
      FEnabled = Value;

      UpdateTimer();
   }
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::SetInterval(const WORD Value)
{
   if (Value != FInterval)
   {
      FInterval = Value;

      UpdateTimer();
   }
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::SetOnTimer(const TNotifyEvent Value)
{
   FOnTimer = Value;

   UpdateTimer();
}

////////////////////////////////////////////////////////////////////////////////

void __fastcall TThreadedTimer::SetThreadPriority(const TThreadPriority Value)
{
   if (Value != FThreadPriority)
   {
      FThreadPriority = Value;

      UpdateTimer();
   }
}

////////////////////////////////////////////////////////////////////////////////
// TTimerThread

void __fastcall TTimerThread::Execute()
{
   Priority = OwnerTimer->ThreadPriority;

   do
   {
      SleepEx(OwnerTimer->Interval, false) ;

      Synchronize(OwnerTimer->Timer);
   } while (!Terminated);
}

////////////////////////////////////////////////////////////////////////////////
// Registration

namespace Thdtimer
{
   void __fastcall Register()
   {
      TComponentClass classes[1] = {__classid(TThreadedTimer)};

      RegisterComponents("System", classes, 0);
   }
}

// End of file
////////////////////////////////////////////////////////////////////////////////

