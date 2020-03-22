// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'bi_timer.pas' rev: 5.00

#ifndef bi_timerHPP
#define bi_timerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Bi_timer
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBI_Timer;
class PASCALIMPLEMENTATION TBI_Timer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FEnabled;
	unsigned FInterval;
	Classes::TNotifyEvent FOnTimer;
	Classes::TThread* FTimerThread;
	Classes::TThreadPriority FThreadPriority;
	void __fastcall UpdateTimer(void);
	void __fastcall SetOnTimer(Classes::TNotifyEvent Value);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall SetThreadPriority(Classes::TThreadPriority Value);
	
protected:
	DYNAMIC void __fastcall Timer(void);
	
public:
	__fastcall virtual TBI_Timer(Classes::TComponent* AOwner);
	__fastcall virtual ~TBI_Timer(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=1000};
	__property Classes::TThreadPriority ThreadPriority = {read=FThreadPriority, write=SetThreadPriority
		, default=3};
	__property Classes::TNotifyEvent OnTimer = {read=FOnTimer, write=SetOnTimer};
	__property Name ;
};


class DELPHICLASS bi_t_thread;
class PASCALIMPLEMENTATION bi_t_thread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	TBI_Timer* FOwner;
	bool FWaitForTerminate;
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	__fastcall bi_t_thread(TBI_Timer* timer);
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~bi_t_thread(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Bi_timer */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Bi_timer;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// bi_timer
