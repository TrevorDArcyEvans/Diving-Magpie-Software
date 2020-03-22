////////////////////////////////////////////////////////////////////////////////
// TThreadedTimer component - Heart 5.0
//
// Component which allows to have an accurate timer (based on Delphi
// Developer's Journal, issue of May 1996)
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

#ifndef ThdTimerH
#define ThdTimerH

////////////////////////////////////////////////////////////////////////////////

#include <vcl\sysutils.hpp>
#include <vcl\controls.hpp>
#include <vcl\classes.hpp>
#include <vcl\forms.hpp>

////////////////////////////////////////////////////////////////////////////////

class TTimerThread;

class TThreadedTimer: public TComponent
{
   private:
      bool FEnabled;
      WORD FInterval;
      TNotifyEvent FOnTimer;
      TTimerThread *FTimerThread;
      TThreadPriority FThreadPriority;

      void __fastcall UpdateTimer();
      void __fastcall SetEnabled(const bool Value);
      void __fastcall SetInterval(const WORD Value);
      void __fastcall SetOnTimer(const TNotifyEvent Value);
      void __fastcall SetThreadPriority(const TThreadPriority Value);

   public:
      virtual __fastcall TThreadedTimer(TComponent *aOwner);
      virtual __fastcall ~TThreadedTimer();

      virtual void __fastcall Timer();

   __published:
      __property bool Enabled = {read=FEnabled, write=SetEnabled, default=true};
      __property WORD Interval = {read=FInterval, write=SetInterval, default=1000};
      __property TNotifyEvent OnTimer = {read=FOnTimer, write=SetOnTimer, default=NULL};
      __property TThreadPriority ThreadPriority = {read=FThreadPriority, write=SetThreadPriority, default=3};
};

class TTimerThread: public TThread
{
   public:
      TThreadedTimer *OwnerTimer;

      virtual __fastcall TTimerThread(bool CreateSuspended): TThread(CreateSuspended) {};
      virtual __fastcall ~TTimerThread() {};

      virtual void __fastcall Execute();
};

////////////////////////////////////////////////////////////////////////////////

#endif

// End of file
////////////////////////////////////////////////////////////////////////////////

