// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CommObjs.pas' rev: 5.00

#ifndef CommObjsHPP
#define CommObjsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Commobjs
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS THandleObject;
class PASCALIMPLEMENTATION THandleObject : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	unsigned FHandle;
	int FError;
	
public:
	__fastcall virtual ~THandleObject(void);
	__property unsigned Handle = {read=FHandle, nodefault};
	__property int Error = {read=FError, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall THandleObject(void) : System::TObject() { }
	#pragma option pop
	
};


#pragma option push -b-
enum TEventWaitResult { wrSignaled, wrTimeout, wrAbandoned, wrError };
#pragma option pop

class DELPHICLASS TEvent;
class PASCALIMPLEMENTATION TEvent : public THandleObject 
{
	typedef THandleObject inherited;
	
public:
	__fastcall TEvent(Windows::PSecurityAttributes EventAttributes, bool ManualReset, bool InitialState
		, const AnsiString Name);
	TEventWaitResult __fastcall WaitFor(unsigned Timeout);
	void __fastcall SetEvent(void);
	void __fastcall ResetEvent(void);
public:
	#pragma option push -w-inl
	/* THandleObject.Destroy */ inline __fastcall virtual ~TEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSimpleEvent;
class PASCALIMPLEMENTATION TSimpleEvent : public TEvent 
{
	typedef TEvent inherited;
	
public:
	__fastcall TSimpleEvent(void);
public:
	#pragma option push -w-inl
	/* THandleObject.Destroy */ inline __fastcall virtual ~TSimpleEvent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCriticalSection;
class PASCALIMPLEMENTATION TCriticalSection : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	_RTL_CRITICAL_SECTION FSection;
	
public:
	__fastcall TCriticalSection(void);
	__fastcall virtual ~TCriticalSection(void);
	void __fastcall Acquire(void);
	void __fastcall Release(void);
	void __fastcall Enter(void);
	void __fastcall Leave(void);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Commobjs */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Commobjs;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CommObjs
