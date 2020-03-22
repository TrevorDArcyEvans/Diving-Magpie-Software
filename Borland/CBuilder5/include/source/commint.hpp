// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CommInt.pas' rev: 4.00

#ifndef CommIntHPP
#define CommIntHPP

#pragma delphiheader begin
#pragma option push -w-
#include <CommObjs.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Commint
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ECommError;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION ECommError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	int ErrorCode;
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ECommError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ECommError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ECommError(int Ident, Extended Dummy) : Sysutils::Exception(
		Ident, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ECommError(int Ident, const System::TVarRec * Args, 
		const int Args_Size) : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ECommError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(
		Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ECommError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ECommError(int Ident, int AHelpContext) : Sysutils::Exception(
		Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ECommError(int Ident, const System::TVarRec * Args
		, const int Args_Size, int AHelpContext) : Sysutils::Exception(Ident, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ECommError(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

typedef void __fastcall (__closure *TCommEvent)(System::TObject* Sender, unsigned Status);

#pragma option push -b-
enum TCommEventType { evBreak, evCts, evDsr, evError, evRing, evRlsd, evRxChar, evRxFlag, evTxEmpty 
	};
#pragma option pop

typedef Set<TCommEventType, evBreak, evTxEmpty>  TCommEventTypes;

class DELPHICLASS TCommEventThread;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TCommEventThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	unsigned FCommHandle;
	Commobjs::TSimpleEvent* FEvent;
	unsigned FEventMask;
	TCommEvent FOnSignal;
	
protected:
	virtual void __fastcall Execute(void);
	HIDESBASE void __fastcall Terminate(void);
	void __fastcall DoOnSignal(void);
	
public:
	__fastcall TCommEventThread(unsigned Handle, TCommEventTypes Events);
	__fastcall virtual ~TCommEventThread(void);
	__property TCommEvent OnSignal = {read=FOnSignal, write=FOnSignal};
};

#pragma pack(pop)

class DELPHICLASS TCommEventChars;
class DELPHICLASS TCustomComm;
#pragma option push -b-
enum TBaudrate { br110, br300, br600, br1200, br2400, br4800, br9600, br14400, br19200, br38400, br56000, 
	br57600, br115200, br128000, br256000 };
#pragma option pop

#pragma option push -b-
enum TParity { paNone, paOdd, paEven, paMark, paSpace };
#pragma option pop

#pragma option push -b-
enum TStopbits { sb10, sb15, sb20 };
#pragma option pop

#pragma option push -b-
enum TDatabits { da4, da5, da6, da7, da8 };
#pragma option pop

#pragma option push -b-
enum TCommOption { coParityCheck, coDsrSensitivity, coIgnoreXOff, coErrorChar, coNullStrip };
#pragma option pop

typedef Set<TCommOption, coParityCheck, coNullStrip>  TCommOptions;

#pragma option push -b-
enum TFlowControl { fcNone, fcCTS, fcDTR, fcSoftware, fcDefault };
#pragma option pop

typedef void __fastcall (__closure *TCommErrorEvent)(System::TObject* Sender, int Errors);

typedef void __fastcall (__closure *TCommRxCharEvent)(System::TObject* Sender, int Count);

#pragma pack(push, 4)
class PASCALIMPLEMENTATION TCustomComm : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	unsigned FHandle;
	_DCB FDCB;
	AnsiString FDeviceName;
	Commobjs::TSimpleEvent* FEvent;
	Commobjs::TCriticalSection* FCriticalSection;
	int FReadTimeout;
	int FWriteTimeout;
	int FReadBufSize;
	int FWriteBufSize;
	TCommEventTypes FMonitorEvents;
	TBaudrate FBaudRate;
	TParity FParity;
	TStopbits FStopbits;
	TDatabits FDatabits;
	TCommEventThread* FEventThread;
	TCommEventChars* FEventChars;
	TCommOptions FOptions;
	TFlowControl FFlowControl;
	Classes::TNotifyEvent FOnBreak;
	Classes::TNotifyEvent FOnCts;
	Classes::TNotifyEvent FOnDsr;
	TCommErrorEvent FOnError;
	Classes::TNotifyEvent FOnRing;
	Classes::TNotifyEvent FOnRlsd;
	TCommRxCharEvent FOnRxChar;
	Classes::TNotifyEvent FOnRxFlag;
	Classes::TNotifyEvent FOnTxEmpty;
	void __fastcall SetDeviceName(const AnsiString Value);
	void __fastcall SetMonitorEvents(TCommEventTypes Value);
	void __fastcall SetReadBufSize(int Value);
	void __fastcall SetWriteBufSize(int Value);
	void __fastcall SetBaudRate(TBaudrate Value);
	void __fastcall SetParity(TParity Value);
	void __fastcall SetStopbits(TStopbits Value);
	void __fastcall SetDatabits(TDatabits Value);
	void __fastcall SetOptions(TCommOptions Value);
	void __fastcall SetFlowControl(TFlowControl Value);
	bool __fastcall GetModemState(int Index);
	bool __fastcall GetComState(int Index);
	void __fastcall Lock(void);
	void __fastcall Unlock(void);
	void __fastcall CheckOpen(void);
	void __fastcall EscapeComm(int Flag);
	void __fastcall InitHandshaking(_DCB &DCB);
	void __fastcall UpdateCommTimeouts(void);
	
protected:
	virtual void __fastcall CreateHandle(void);
	void __fastcall DestroyHandle(void);
	void __fastcall HandleCommEvent(System::TObject* Sender, unsigned Status);
	void __fastcall UpdateDataControlBlock(void);
	__property AnsiString DeviceName = {read=FDeviceName, write=SetDeviceName};
	__property int ReadTimeout = {read=FReadTimeout, write=FReadTimeout, default=1000};
	__property int WriteTimeout = {read=FWriteTimeout, write=FWriteTimeout, default=1000};
	__property int ReadBufSize = {read=FReadBufSize, write=SetReadBufSize, default=4096};
	__property int WriteBufSize = {read=FWriteBufSize, write=SetWriteBufSize, default=2048};
	__property TCommEventTypes MonitorEvents = {read=FMonitorEvents, write=SetMonitorEvents, nodefault}
		;
	__property TBaudrate BaudRate = {read=FBaudRate, write=SetBaudRate, default=6};
	__property TParity Parity = {read=FParity, write=SetParity, default=0};
	__property TStopbits Stopbits = {read=FStopbits, write=SetStopbits, default=0};
	__property TDatabits Databits = {read=FDatabits, write=SetDatabits, default=4};
	__property TCommEventChars* EventChars = {read=FEventChars};
	__property TCommOptions Options = {read=FOptions, write=SetOptions, nodefault};
	__property TFlowControl FlowControl = {read=FFlowControl, write=SetFlowControl, default=4};
	__property Classes::TNotifyEvent OnBreak = {read=FOnBreak, write=FOnBreak};
	__property Classes::TNotifyEvent OnCts = {read=FOnCts, write=FOnCts};
	__property Classes::TNotifyEvent OnDsr = {read=FOnDsr, write=FOnDsr};
	__property Classes::TNotifyEvent OnRing = {read=FOnRing, write=FOnRing};
	__property Classes::TNotifyEvent OnRlsd = {read=FOnRlsd, write=FOnRlsd};
	__property TCommErrorEvent OnError = {read=FOnError, write=FOnError};
	__property TCommRxCharEvent OnRxChar = {read=FOnRxChar, write=FOnRxChar};
	__property Classes::TNotifyEvent OnRxFlag = {read=FOnRxFlag, write=FOnRxFlag};
	__property Classes::TNotifyEvent OnTxEmpty = {read=FOnTxEmpty, write=FOnTxEmpty};
	
public:
	__fastcall virtual TCustomComm(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomComm(void);
	void __fastcall Open(void);
	void __fastcall Close(void);
	bool __fastcall Enabled(void);
	int __fastcall Write(void *Buf, int Count);
	int __fastcall Read(void *Buf, int Count);
	int __fastcall InQueCount(void);
	int __fastcall OutQueCount(void);
	void __fastcall PurgeIn(void);
	void __fastcall PurgeOut(void);
	void __fastcall SetDTRState(bool State);
	void __fastcall SetRTSState(bool State);
	void __fastcall SetBREAKState(bool State);
	void __fastcall SetXONState(bool State);
	__property bool CTS = {read=GetModemState, index=1, nodefault};
	__property bool DSR = {read=GetModemState, index=2, nodefault};
	__property bool RING = {read=GetModemState, index=3, nodefault};
	__property bool RLSD = {read=GetModemState, index=4, nodefault};
	__property bool CtsHold = {read=GetComState, index=1, nodefault};
	__property bool DsrHold = {read=GetComState, index=2, nodefault};
	__property bool RlsdHold = {read=GetComState, index=3, nodefault};
	__property bool XoffHold = {read=GetComState, index=4, nodefault};
	__property bool XOffSent = {read=GetComState, index=5, nodefault};
	__property unsigned Handle = {read=FHandle, nodefault};
};

#pragma pack(pop)

#pragma pack(push, 4)
class PASCALIMPLEMENTATION TCommEventChars : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomComm* FOwner;
	char FXonChar;
	char FXoffChar;
	char FErrorChar;
	char FEofChar;
	char FEvtChar;
	void __fastcall SetEventChar(int Index, char Value);
	
public:
	__fastcall TCommEventChars(TCustomComm* Owner);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property char XonChar = {read=FXonChar, write=SetEventChar, index=1, default=17};
	__property char XoffChar = {read=FXoffChar, write=SetEventChar, index=2, default=19};
	__property char ErrorChar = {read=FErrorChar, write=SetEventChar, index=3, default=0};
	__property char EofChar = {read=FEofChar, write=SetEventChar, index=4, default=0};
	__property char EvtChar = {read=FEvtChar, write=SetEventChar, index=5, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TCommEventChars(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

class DELPHICLASS TComm;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TComm : public TCustomComm 
{
	typedef TCustomComm inherited;
	
__published:
	__property DeviceName ;
	__property ReadTimeout ;
	__property WriteTimeout ;
	__property ReadBufSize ;
	__property WriteBufSize ;
	__property MonitorEvents ;
	__property BaudRate ;
	__property Parity ;
	__property Stopbits ;
	__property Databits ;
	__property EventChars ;
	__property Options ;
	__property FlowControl ;
	__property OnBreak ;
	__property OnCts ;
	__property OnDsr ;
	__property OnRing ;
	__property OnRlsd ;
	__property OnError ;
	__property OnRxChar ;
	__property OnRxFlag ;
	__property OnTxEmpty ;
public:
	#pragma option push -w-inl
	/* TCustomComm.Create */ inline __fastcall virtual TComm(Classes::TComponent* AOwner) : TCustomComm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomComm.Destroy */ inline __fastcall virtual ~TComm(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define DefaultDeviceName "Com2"
extern PACKAGE void __fastcall Register(void);

}	/* namespace Commint */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Commint;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CommInt
