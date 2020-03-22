// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FngDirWatch.pas' rev: 4.00

#ifndef FngDirWatchHPP
#define FngDirWatchHPP

#pragma delphiheader begin
#pragma option push -w-
#include <SyncObjs.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fngdirwatch
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EDirWatchError;
#pragma pack(push, 1)
class PASCALIMPLEMENTATION EDirWatchError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EDirWatchError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDirWatchError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDirWatchError(int Ident, Extended Dummy) : Sysutils::Exception(
		Ident, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDirWatchError(int Ident, const System::TVarRec * Args
		, const int Args_Size) : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDirWatchError(const AnsiString Msg, int AHelpContext)
		 : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDirWatchError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDirWatchError(int Ident, int AHelpContext) : Sysutils::Exception(
		Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDirWatchError(int Ident, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Ident, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDirWatchError(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

#pragma option push -b-
enum TDirWatchOption { dw_file_name, dw_dir_name, dw_file_attr, dw_file_size, dw_file_write_date, dw_file_access_date, 
	dw_file_creation_date, dw_file_security };
#pragma option pop

typedef Set<TDirWatchOption, dw_file_name, dw_file_security>  TDirWatchOptions;

typedef void __fastcall (__closure *TFileChangeNotifyEvent)(System::TObject* Sender, int Action, const 
	AnsiString FileName);

class DELPHICLASS TFnugryDirWatch;
#pragma pack(push, 1)
class PASCALIMPLEMENTATION TFnugryDirWatch : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Classes::TThread* FWatchThread;
	TDirWatchOptions FOptions;
	HWND FWndHandle;
	AnsiString FErrorMsg;
	bool FWatchSubtree;
	AnsiString FDirectory;
	Classes::TNotifyEvent FOnChange;
	TFileChangeNotifyEvent FOnNotify;
	bool __fastcall GetEnabled(void);
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetOptions(const TDirWatchOptions Value);
	void __fastcall WatchWndProc(Messages::TMessage &M);
	unsigned __fastcall MakeFilter(void);
	void __fastcall SetWatchSubTree(const bool Value);
	AnsiString __fastcall GetDirectory();
	void __fastcall SetDirectory(const AnsiString Value);
	void __fastcall EvWatchNotify(System::TObject* Sender);
	void __fastcall EvWatchError(System::TObject* Sender);
	
protected:
	void __fastcall AllocWatchThread(void);
	void __fastcall ReleaseWatchThread(void);
	void __fastcall RestartWatchThread(void);
	virtual void __fastcall Change(void);
	virtual void __fastcall Notify(int Action, const AnsiString FileName);
	
public:
	__fastcall virtual TFnugryDirWatch(Classes::TComponent* AOwner);
	__fastcall virtual ~TFnugryDirWatch(void);
	AnsiString __fastcall ActionName(int Action);
	__property AnsiString ErrorMsg = {read=FErrorMsg};
	
__published:
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, nodefault};
	__property TDirWatchOptions Options = {read=FOptions, write=SetOptions, nodefault};
	__property bool WatchSubTree = {read=FWatchSubtree, write=SetWatchSubTree, nodefault};
	__property AnsiString Directory = {read=GetDirectory, write=SetDirectory};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TFileChangeNotifyEvent OnNotify = {read=FOnNotify, write=FOnNotify};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#if 0
static const Shortint FILE_ACTION_ADDED = 0x1;
static const Shortint FILE_ACTION_REMOVED = 0x2;
static const Shortint FILE_ACTION_MODIFIED = 0x3;
static const Shortint FILE_ACTION_RENAMED_OLD_NAME = 0x4;
static const Shortint FILE_ACTION_RENAMED_NEW_NAME = 0x5;
#endif
#define FILE_ACTION_ADDED               0x1
#define FILE_ACTION_REMOVED             0x2
#define FILE_ACTION_MODIFIED            0x3
#define FILE_ACTION_RENAMED_OLD_NAME    0x4
#define FILE_ACTION_RENAMED_NEW_NAME    0x5

extern PACKAGE void __fastcall Register(void);

}	/* namespace Fngdirwatch */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Fngdirwatch;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FngDirWatch
