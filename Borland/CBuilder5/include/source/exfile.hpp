// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ExFile.pas' rev: 4.00

#ifndef ExFileHPP
#define ExFileHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Exfile
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TProcCompleted)(System::TObject* sender, AnsiString evFileName, 
	AnsiString evIdentifier, int evRetValue, bool evTimedOut);

typedef void __fastcall (__closure *TLaunchFailed)(System::TObject* sender, AnsiString evFileName, AnsiString 
	evIdentifier, int evErrorCode, AnsiString evErrorMessage);

#pragma option push -b-
enum TWindowType { wtNorm, wtMinimize, wtMaximize, wtHide, wtMinNoActivate, wtShowNoActivate };
#pragma option pop

typedef Word TWindowTypes[6];

#pragma option push -b-
enum TErrMsg { emZero, emDuplicateProc, emOnlyOneMeth, emTimedOut, emInValidDir, emUnknown };
#pragma option pop

typedef System::SmallString<55>  TErrMsgs[6];

#pragma option push -b-
enum TUseEvent { ueAll, ueOnLaunchFailed, ueOnProcCompleted, ueNone };
#pragma option pop

#pragma option push -b-
enum TPriorityClass { prNormal, prIdle, prHigh, prRealTime };
#pragma option pop

typedef Word TPriorityClasses[4];

#pragma option push -b-
enum TStartType { NonThreadedWait, ThreadedWait, Independent };
#pragma option pop

typedef AnsiString TVersion;

#pragma option push -b-
enum TProcInfo { PrhProcess, PrDwProcessId, PrHWND };
#pragma option pop

struct AThreadRecord;
typedef AThreadRecord *PProcList;

#pragma pack(push, 4)
struct AThreadRecord
{
	AnsiString PrName;
	AnsiString PrProcIdentifier;
	unsigned PrhProcess;
	unsigned PrDwProcessId;
	unsigned PrhThread;
	HWND PrHWND;
	TStartType PrStartType;
} ;
#pragma pack(pop)

class DELPHICLASS TExFile;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TExFile : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TLaunchFailed FOnLaunchFailed;
	TProcCompleted FOnProcCompleted;
	AnsiString FProcFileName;
	AnsiString FProcFileNamelc;
	AnsiString FFParams;
	AnsiString FProcIdentifier;
	AnsiString FProcCurrentDir;
	TWindowType FWindowType;
	bool FWaitUntilDone;
	TPriorityClass FPriorityClass;
	_STARTUPINFOA StartUpInfo;
	_PROCESS_INFORMATION ProcessInfo;
	unsigned hEventHandle;
	unsigned hMutex;
	int FErrorCode;
	int FExitCode;
	TUseEvent FUseEvent;
	int FTimeOutSec;
	bool FTimedOut;
	unsigned FMilliSeconds;
	
protected:
	Classes::TList* HandLst;
	AThreadRecord *AProcList;
	AnsiString FVersion;
	char *PCurDir;
	void __fastcall SetVersion(AnsiString Value);
	void __fastcall SetWindowType(TWindowType Value);
	void __fastcall SetPriorityClass(TPriorityClass Value);
	void __fastcall SetTimeOutSec(int Value);
	void __fastcall SetProcFileName(AnsiString Value);
	void __fastcall ListMaint(void);
	void __fastcall AddToList(TStartType StartType);
	bool __fastcall GethProcess(AnsiString StatProcName, AnsiString StatProcIdentifier, int &Hidx);
	bool __fastcall GetExitCode(unsigned hProcess);
	bool __fastcall DuplicateProc(void);
	bool __fastcall StartProcess(TStartType StartType);
	void __fastcall ErrorEvent(int efError, AnsiString efMessage);
	bool __fastcall AlreadyRunning(TStartType GRT);
	bool __fastcall AssignCurrentDir(void);
	
public:
	bool __fastcall Execute(void);
	bool __fastcall CloseProcess(void);
	bool __fastcall GetProcStatus(void);
	bool __fastcall CloseThreads(void);
	int __fastcall GetErrorCode(void);
	int __fastcall GetReturnCode(void);
	AnsiString __fastcall ExErrorMessage(int ExErrorCode);
	void __fastcall ResetProps(void);
	bool __fastcall GetProcInfo(TProcInfo GPIType, int &GPIReturn);
	__fastcall virtual TExFile(Classes::TComponent* Aowner);
	__fastcall virtual ~TExFile(void);
	
__published:
	__property AnsiString Version = {read=FVersion, write=SetVersion, stored=false};
	__property AnsiString ProcFileName = {read=FProcFileName, write=SetProcFileName};
	__property AnsiString ProcParameters = {read=FFParams, write=FFParams};
	__property AnsiString ProcIdentifier = {read=FProcIdentifier, write=FProcIdentifier};
	__property AnsiString ProcCurrentDir = {read=FProcCurrentDir, write=FProcCurrentDir};
	__property TProcCompleted OnProcCompleted = {read=FOnProcCompleted, write=FOnProcCompleted};
	__property TLaunchFailed OnLaunchFailed = {read=FOnLaunchFailed, write=FOnLaunchFailed};
	__property TWindowType WindowType = {read=FWindowType, write=SetWindowType, nodefault};
	__property bool WaitUntilDone = {read=FWaitUntilDone, write=FWaitUntilDone, nodefault};
	__property TUseEvent UseEvent = {read=FUseEvent, write=FUseEvent, nodefault};
	__property TPriorityClass Priority = {read=FPriorityClass, write=SetPriorityClass, nodefault};
	__property int TimeOutSec = {read=FTimeOutSec, write=SetTimeOutSec, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TProcThread;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TProcThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	unsigned thArray[2];
	AnsiString thFileName;
	AnsiString thIdentifier;
	unsigned thRetVal;
	TProcCompleted FOnThreadDone;
	unsigned thMutex;
	TUseEvent thUseEvent;
	unsigned thMilliseconds;
	bool thRetType;
	
protected:
	virtual void __fastcall Execute(void);
	HIDESBASE void __fastcall CallOnTerminate(void);
	__fastcall TProcThread(unsigned vProcHandle, unsigned vProcEventHandle, AnsiString vFileName, AnsiString 
		vProcIdentifier, TProcCompleted vDoneMethod, unsigned vMutex, TUseEvent vUseEvent, unsigned vMilliseconds
		);
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TProcThread(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Exfile */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Exfile;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ExFile
