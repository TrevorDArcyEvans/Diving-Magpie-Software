// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FindFile.pas' rev: 4.00

#ifndef FindFileHPP
#define FindFileHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Dialogs.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Findfile
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TAttrOption { ffReadOnly, ffHidden, ffSystem, ffVolumeID, ffDirectory, ffArchive };
#pragma option pop

typedef Set<TAttrOption, ffReadOnly, ffArchive>  TAttrOptions;

typedef void __fastcall (__closure *TNewPathEvent)(System::TObject* Sender, AnsiString NewPath, bool 
	&Abort);

class DELPHICLASS TFindFile;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TFindFile : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FAbort;
	int FTotalSpace;
	int FTotalDir;
	int FTotalFile;
	TAttrOptions FAttribs;
	AnsiString FDirectory;
	bool FRecurse;
	AnsiString FFilter;
	Classes::TStrings* FFiles;
	Classes::TNotifyEvent FBeforeExecute;
	Classes::TNotifyEvent FAfterExecute;
	TNewPathEvent FOnNewPath;
	void __fastcall SearchCurrentDirectory(AnsiString Directory);
	void __fastcall SearchRecursive(AnsiString Directory);
	bool __fastcall FindSubDirectory(Classes::TStringList* strDirs, AnsiString Directory);
	
protected:
	void __fastcall SetFiles(Classes::TStrings* Value);
	
public:
	__fastcall virtual TFindFile(Classes::TComponent* AOwner);
	__fastcall virtual ~TFindFile(void);
	DYNAMIC void __fastcall Execute(void);
	__property int TotalSpace = {read=FTotalSpace, write=FTotalSpace, nodefault};
	__property int TotalDir = {read=FTotalDir, write=FTotalDir, nodefault};
	__property int TotalFile = {read=FTotalFile, write=FTotalFile, nodefault};
	__property bool Abort = {read=FAbort, write=FAbort, default=0};
	
__published:
	__property bool Recurse = {read=FRecurse, write=FRecurse, default=0};
	__property AnsiString Directory = {read=FDirectory, write=FDirectory};
	__property AnsiString Filter = {read=FFilter, write=FFilter};
	__property Classes::TStrings* Files = {read=FFiles, write=SetFiles};
	__property TAttrOptions Attributes = {read=FAttribs, write=FAttribs, default=39};
	__property Classes::TNotifyEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property Classes::TNotifyEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
	__property TNewPathEvent OnNewPath = {read=FOnNewPath, write=FOnNewPath};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Findfile */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Findfile;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FindFile
