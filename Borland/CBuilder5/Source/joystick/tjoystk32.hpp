// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'tjoystk32.pas' rev: 5.00

#ifndef tjoystk32HPP
#define tjoystk32HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MMSystem.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tjoystk32
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *DCTimerEvent)(void);

typedef void __fastcall (__closure *TJoyMoveEvent)(System::TObject* Sender, int Position);

typedef void __fastcall (__closure *TButtonNotifyEvent)(System::TObject* Sender, bool Pushed);

#pragma option push -b-
enum TRepeatButton { Button01, Button02, Button03, Button04, Button05, Button06, Button07, Button08, 
	Button09, Button10, Button11, Button12, Button13, Button14, Button15, Button16, Button17, Button18, 
	Button19, Button20, Button21, Button22, Button23, Button24, Button25, Button26, Button27, Button28, 
	Button29, Button30, Button31, Button32 };
#pragma option pop

#pragma option push -b-
enum TRepeatPosition { X, Y, Z, R, U, V, POV };
#pragma option pop

typedef Set<TRepeatButton, Button01, Button32>  TRepeatButtons;

typedef Set<TRepeatPosition, X, POV>  TRepeatPositions;

class DELPHICLASS DCThread;
class PASCALIMPLEMENTATION DCThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	DCTimerEvent FOnTimer;
	bool FEnabled;
	bool FRun;
	int FInterval;
	
protected:
	virtual void __fastcall Execute(void);
	
__published:
	__property DCTimerEvent OnTimer = {read=FOnTimer, write=FOnTimer};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property bool Run = {read=FRun, write=FRun, nodefault};
	__property int Interval = {read=FInterval, write=FInterval, nodefault};
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall DCThread(bool CreateSuspended) : Classes::TThread(CreateSuspended
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~DCThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TJoystick;
class PASCALIMPLEMENTATION TJoystick : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Word JoyId;
	tagJOYCAPSA JoyCaps;
	joyinfoex_tag JoyInfoEx;
	unsigned MinX;
	unsigned MinY;
	unsigned MinZ;
	unsigned MinR;
	unsigned MinU;
	unsigned MinV;
	unsigned DeltaX;
	unsigned DeltaY;
	unsigned DeltaZ;
	unsigned DeltaR;
	unsigned DeltaU;
	unsigned DeltaV;
	unsigned LastX;
	unsigned LastY;
	unsigned LastZ;
	unsigned LastR;
	unsigned LastU;
	unsigned LastV;
	unsigned LastP;
	bool LastButton[32];
	DCThread* FTimer;
	bool FEnabled;
	int FGamePort;
	int FNotifyRangeR;
	int FNotifyRangeU;
	int FNotifyRangeV;
	int FNotifyRangeX;
	int FNotifyRangeY;
	int FNotifyRangeZ;
	int FPollRate;
	Classes::TThreadPriority FPollPriority;
	TRepeatPositions FRepeatPositions;
	TRepeatButtons FRepeatButtons;
	TButtonNotifyEvent FOnButton01;
	TButtonNotifyEvent FOnButton02;
	TButtonNotifyEvent FOnButton03;
	TButtonNotifyEvent FOnButton04;
	TButtonNotifyEvent FOnButton05;
	TButtonNotifyEvent FOnButton06;
	TButtonNotifyEvent FOnButton07;
	TButtonNotifyEvent FOnButton08;
	TButtonNotifyEvent FOnButton09;
	TButtonNotifyEvent FOnButton10;
	TButtonNotifyEvent FOnButton11;
	TButtonNotifyEvent FOnButton12;
	TButtonNotifyEvent FOnButton13;
	TButtonNotifyEvent FOnButton14;
	TButtonNotifyEvent FOnButton15;
	TButtonNotifyEvent FOnButton16;
	TButtonNotifyEvent FOnButton17;
	TButtonNotifyEvent FOnButton18;
	TButtonNotifyEvent FOnButton19;
	TButtonNotifyEvent FOnButton20;
	TButtonNotifyEvent FOnButton21;
	TButtonNotifyEvent FOnButton22;
	TButtonNotifyEvent FOnButton23;
	TButtonNotifyEvent FOnButton24;
	TButtonNotifyEvent FOnButton25;
	TButtonNotifyEvent FOnButton26;
	TButtonNotifyEvent FOnButton27;
	TButtonNotifyEvent FOnButton28;
	TButtonNotifyEvent FOnButton29;
	TButtonNotifyEvent FOnButton30;
	TButtonNotifyEvent FOnButton31;
	TButtonNotifyEvent FOnButton32;
	TJoyMoveEvent FOnJoyMoveR;
	TJoyMoveEvent FOnJoyMoveU;
	TJoyMoveEvent FOnJoyMoveV;
	TJoyMoveEvent FOnJoyMoveX;
	TJoyMoveEvent FOnJoyMoveY;
	TJoyMoveEvent FOnJoyMoveZ;
	TJoyMoveEvent FOnJoyMovePOV;
	int __fastcall GetGamePort(void);
	void __fastcall SetGamePort(int Val);
	int __fastcall GetNotifyRangeR(void);
	void __fastcall SetNotifyRangeR(int Val);
	int __fastcall GetNotifyRangeU(void);
	void __fastcall SetNotifyRangeU(int Val);
	int __fastcall GetNotifyRangeV(void);
	void __fastcall SetNotifyRangeV(int Val);
	int __fastcall GetNotifyRangeX(void);
	void __fastcall SetNotifyRangeX(int Val);
	int __fastcall GetNotifyRangeY(void);
	void __fastcall SetNotifyRangeY(int Val);
	int __fastcall GetNotifyRangeZ(void);
	void __fastcall SetNotifyRangeZ(int Val);
	int __fastcall GetPollRate(void);
	void __fastcall SetPollRate(int Val);
	Classes::TThreadPriority __fastcall GetPollPriority(void);
	void __fastcall SetPollPriority(Classes::TThreadPriority Val);
	unsigned __fastcall CalculateRange(char Axxis, unsigned Position);
	void __fastcall MakeTimer(void);
	void __fastcall ThreadRoutine(void);
	void __fastcall CallButton(int ButtonNumber);
	void __fastcall CallPosition(char Axxis);
	bool __fastcall StatusPosition(char Axxis);
	bool __fastcall StatusButton(int Buttonnumber);
	
protected:
	void __fastcall SetDefaults(void);
	
public:
	__fastcall virtual TJoystick(Classes::TComponent* AOwner);
	__fastcall virtual ~TJoystick(void);
	unsigned __fastcall Buttons(unsigned Port);
	unsigned __fastcall Devices(void);
	void __fastcall Calibrate(void);
	int __fastcall GetJoyX(void);
	int __fastcall GetJoyY(void);
	int __fastcall GetJoyZ(void);
	int __fastcall GetJoyR(void);
	int __fastcall GetJoyU(void);
	int __fastcall GetJoyV(void);
	int __fastcall GetJoyPOV(void);
	bool __fastcall GetButton(int ButtonNumber);
	
__published:
	__property int GamePort = {read=GetGamePort, write=SetGamePort, default=1};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property int NotifyRangeR = {read=GetNotifyRangeR, write=SetNotifyRangeR, default=20};
	__property int NotifyRangeU = {read=GetNotifyRangeU, write=SetNotifyRangeU, default=20};
	__property int NotifyRangeV = {read=GetNotifyRangeV, write=SetNotifyRangeV, default=20};
	__property int NotifyRangeX = {read=GetNotifyRangeX, write=SetNotifyRangeX, default=20};
	__property int NotifyRangeY = {read=GetNotifyRangeY, write=SetNotifyRangeY, default=20};
	__property int NotifyRangeZ = {read=GetNotifyRangeZ, write=SetNotifyRangeZ, default=20};
	__property int PollRate = {read=GetPollRate, write=SetPollRate, default=50};
	__property Classes::TThreadPriority PollPriority = {read=GetPollPriority, write=SetPollPriority, default=3
		};
	__property TRepeatPositions StatusPositionChange = {read=FRepeatPositions, write=FRepeatPositions, 
		nodefault};
	__property TRepeatButtons StatusButtonChange = {read=FRepeatButtons, write=FRepeatButtons, nodefault
		};
	__property TButtonNotifyEvent OnButton01 = {read=FOnButton01, write=FOnButton01};
	__property TButtonNotifyEvent OnButton02 = {read=FOnButton02, write=FOnButton02};
	__property TButtonNotifyEvent OnButton03 = {read=FOnButton03, write=FOnButton03};
	__property TButtonNotifyEvent OnButton04 = {read=FOnButton04, write=FOnButton04};
	__property TButtonNotifyEvent OnButton05 = {read=FOnButton05, write=FOnButton05};
	__property TButtonNotifyEvent OnButton06 = {read=FOnButton06, write=FOnButton06};
	__property TButtonNotifyEvent OnButton07 = {read=FOnButton07, write=FOnButton07};
	__property TButtonNotifyEvent OnButton08 = {read=FOnButton08, write=FOnButton08};
	__property TButtonNotifyEvent OnButton09 = {read=FOnButton09, write=FOnButton09};
	__property TButtonNotifyEvent OnButton10 = {read=FOnButton10, write=FOnButton10};
	__property TButtonNotifyEvent OnButton11 = {read=FOnButton11, write=FOnButton11};
	__property TButtonNotifyEvent OnButton12 = {read=FOnButton12, write=FOnButton12};
	__property TButtonNotifyEvent OnButton13 = {read=FOnButton13, write=FOnButton13};
	__property TButtonNotifyEvent OnButton14 = {read=FOnButton14, write=FOnButton14};
	__property TButtonNotifyEvent OnButton15 = {read=FOnButton15, write=FOnButton15};
	__property TButtonNotifyEvent OnButton16 = {read=FOnButton16, write=FOnButton16};
	__property TButtonNotifyEvent OnButton17 = {read=FOnButton17, write=FOnButton17};
	__property TButtonNotifyEvent OnButton18 = {read=FOnButton18, write=FOnButton18};
	__property TButtonNotifyEvent OnButton19 = {read=FOnButton19, write=FOnButton19};
	__property TButtonNotifyEvent OnButton20 = {read=FOnButton20, write=FOnButton20};
	__property TButtonNotifyEvent OnButton21 = {read=FOnButton21, write=FOnButton21};
	__property TButtonNotifyEvent OnButton22 = {read=FOnButton22, write=FOnButton22};
	__property TButtonNotifyEvent OnButton23 = {read=FOnButton23, write=FOnButton23};
	__property TButtonNotifyEvent OnButton24 = {read=FOnButton24, write=FOnButton24};
	__property TButtonNotifyEvent OnButton25 = {read=FOnButton25, write=FOnButton25};
	__property TButtonNotifyEvent OnButton26 = {read=FOnButton26, write=FOnButton26};
	__property TButtonNotifyEvent OnButton27 = {read=FOnButton27, write=FOnButton27};
	__property TButtonNotifyEvent OnButton28 = {read=FOnButton28, write=FOnButton28};
	__property TButtonNotifyEvent OnButton29 = {read=FOnButton29, write=FOnButton29};
	__property TButtonNotifyEvent OnButton30 = {read=FOnButton30, write=FOnButton30};
	__property TButtonNotifyEvent OnButton31 = {read=FOnButton31, write=FOnButton31};
	__property TButtonNotifyEvent OnButton32 = {read=FOnButton32, write=FOnButton32};
	__property TJoyMoveEvent OnJoyMoveR = {read=FOnJoyMoveR, write=FOnJoyMoveR};
	__property TJoyMoveEvent OnJoyMoveU = {read=FOnJoyMoveU, write=FOnJoyMoveU};
	__property TJoyMoveEvent OnJoyMoveV = {read=FOnJoyMoveV, write=FOnJoyMoveV};
	__property TJoyMoveEvent OnJoyMoveX = {read=FOnJoyMoveX, write=FOnJoyMoveX};
	__property TJoyMoveEvent OnJoyMoveY = {read=FOnJoyMoveY, write=FOnJoyMoveY};
	__property TJoyMoveEvent OnJoyMoveZ = {read=FOnJoyMoveZ, write=FOnJoyMoveZ};
	__property TJoyMoveEvent OnJoyMovePOV = {read=FOnJoyMovePOV, write=FOnJoyMovePOV};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Tjoystk32 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Tjoystk32;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// tjoystk32
