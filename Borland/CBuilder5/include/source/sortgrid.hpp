// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SortGrid.pas' rev: 4.00

#ifndef SortGridHPP
#define SortGridHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Grids.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sortgrid
{
//-- type declarations -------------------------------------------------------
typedef int __fastcall (*TSortCompare)(const AnsiString Str1, const AnsiString Str2);

#pragma option push -b-
enum TSortDirection { sdAscending, sdDescending };
#pragma option pop

#pragma option push -b-
enum TSortStyle { ssAutomatic, ssAlphabetic, ssNumeric, ssDateTime, ssTime, ssCustom };
#pragma option pop

#pragma option push -b-
enum TSortSymbol { sgNone, sgArrow, sgGlyph, sgCustom };
#pragma option pop

#pragma option push -b-
enum TSortState { ssUnsorted, ssSorted };
#pragma option pop

#pragma pack(push, 4)
struct TSortOptions
{
	TSortStyle SortStyle;
	TSortDirection SortDirection;
	bool SortCaseSensitive;
	TSortCompare SortCompare;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TSortedListEntry
{
	AnsiString Str;
	int RowNum;
} ;
#pragma pack(pop)

typedef TSortedListEntry *pSortedListEntry;

class DELPHICLASS TSortedList;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TSortedList : public Classes::TList 
{
	typedef Classes::TList inherited;
	
public:
	pSortedListEntry __fastcall GetItem(const int i);
	void __fastcall Reset(void);
public:
	#pragma option push -w-inl
	/* TList.Destroy */ inline __fastcall virtual ~TSortedList(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TSortedList(void) : Classes::TList() { }
	#pragma option pop
	
};

#pragma pack(pop)

#pragma option push -b-
enum TCellBevelStyle { cbNone, cbRaised, cbLowered };
#pragma option pop

#pragma pack(push, 4)
struct TCellBevel
{
	TCellBevelStyle Style;
	Graphics::TColor UpperLeftColor;
	Graphics::TColor LowerRightColor;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TVertAlignment { taTopJustify, taBottomJustify, taMiddle };
#pragma option pop

#pragma pack(push, 4)
struct TFormatOptions
{
	Graphics::TBrush* Brush;
	Graphics::TFont* Font;
	Classes::TAlignment AlignmentHorz;
	TVertAlignment AlignmentVert;
	TCellBevel Bevel;
	bool HideText;
} ;
#pragma pack(pop)

typedef void __fastcall (__closure *TFormatDrawCellEvent)(System::TObject* Sender, int Col, int Row, 
	Grids::TGridDrawState State, TFormatOptions &FormatOptions);

typedef void __fastcall (__closure *TClickSortEvent)(System::TObject* Sender, int Col, int Row, TSortOptions 
	&SortOptions);

typedef void __fastcall (__closure *TUpdateGridEvent)(System::TObject* Sender, int Index);

typedef void __fastcall (__closure *TSizeChangedEvent)(System::TObject* Sender, int OldColCount, int 
	OldRowCount);

typedef void __fastcall (__closure *TBeginSortEvent)(System::TObject* Sender, int Col, TSortOptions 
	&SortOptions);

typedef void __fastcall (__closure *TEndSortEvent)(System::TObject* Sender, int Col);

typedef void __fastcall (__closure *TCellValidateEvent)(System::TObject* Sender, int Col, int Row, AnsiString 
	&Value, bool &Valid);

class DELPHICLASS TSortGrid;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TSortGrid : public Grids::TStringGrid 
{
	typedef Grids::TStringGrid inherited;
	
private:
	TSortedList* fSortedList;
	Classes::TAlignment fAlignmentHorz;
	TVertAlignment fAlignmentVert;
	TCellBevelStyle fBevelStyle;
	TSortState fSortState;
	TSortDirection fSortDirection;
	bool fProportionalScrollBars;
	bool fCaseSensitive;
	bool fExtendedKeys;
	bool fSorting;
	bool fModified;
	bool fOldModifiedValue;
	bool fEntered;
	bool fSortOnClick;
	bool fSortFooter;
	AnsiString fOldCellText;
	int fOldCol;
	int fOldRow;
	TSortSymbol fSortSymbol;
	int fSortSpacingHor;
	int fSortSpacingVert;
	int fSortColumn;
	int fFooterRows;
	int gFooterSub;
	Graphics::TBitmap* fSortBMA;
	Graphics::TBitmap* fSortBMD;
	Graphics::TColor fFooterColor;
	Graphics::TFont* fFooterFont;
	TCellBevelStyle fFooterBevelStyle;
	TFormatDrawCellEvent fOnGetCellFormat;
	TClickSortEvent fOnClickSort;
	TUpdateGridEvent fOnRowInsert;
	TUpdateGridEvent fOnRowDelete;
	TUpdateGridEvent fOnColumnInsert;
	TUpdateGridEvent fOnColumnDelete;
	Classes::TNotifyEvent fOnColumnWidthsChanged;
	Classes::TNotifyEvent fOnRowHeightsChanged;
	TSizeChangedEvent fOnSizeChanged;
	TBeginSortEvent fOnBeginSort;
	TEndSortEvent fOnEndSort;
	TCellValidateEvent fOnCellValidate;
	Classes::TNotifyEvent fOnMouseEnter;
	Classes::TNotifyEvent fOnMouseLeave;
	Graphics::TBitmap* GSortBM;
	bool GASE;
	AnsiString GFindString;
	int GStartRow;
	int GEndRow;
	int GStartCol;
	int GEndCol;
	void __fastcall SetSortBMA(Graphics::TBitmap* Value);
	void __fastcall SetSortBMD(Graphics::TBitmap* Value);
	void __fastcall SetSortSymbol(TSortSymbol Value);
	void __fastcall SetBevelStyle(TCellBevelStyle Value);
	void __fastcall SetSortColumn(int Value);
	void __fastcall SetSortOnClick(bool Value);
	void __fastcall SetSortFooter(bool Value);
	void __fastcall SetAlignmentHorz(Classes::TAlignment Value);
	void __fastcall SetAlignmentVert(TVertAlignment Value);
	void __fastcall SetSortDirection(TSortDirection Value);
	void __fastcall SetSortSpacingHor(int Value);
	void __fastcall SetSortSpacingVert(int Value);
	void __fastcall SetProportionalScrollBars(bool Value);
	void __fastcall SetFooterRows(int Value);
	void __fastcall SetFooterColor(Graphics::TColor Value);
	void __fastcall SetFooterFont(Graphics::TFont* Value);
	void __fastcall SetFooterBevelStyle(TCellBevelStyle Value);
	void __fastcall SetGSortSymbol(void);
	bool __fastcall CheckRange(int startcr, int endcr, bool IsRow);
	void __fastcall SetResetASE(bool SetASE);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(void *Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(void *Message);
	
protected:
	virtual void __fastcall ListQuickSort(const int aCol, const TSortOptions &SortOptions);
	virtual TSortStyle __fastcall DetermineSortStyle(const int aCol);
	void __fastcall InitializeFormatOptions(const int aCol, const int aRow, TFormatOptions &FmtOpts);
	virtual void __fastcall DrawCell(int aCol, int aRow, const Windows::TRect &aRect, Grids::TGridDrawState 
		aState);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	DYNAMIC void __fastcall ColWidthsChanged(void);
	DYNAMIC void __fastcall RowHeightsChanged(void);
	DYNAMIC void __fastcall SizeChanged(int OldColCount, int OldRowCount);
	virtual void __fastcall UpdateScrollPage(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall SetEditText(int aCol, int aRow, const AnsiString Value);
	DYNAMIC void __fastcall Click(void);
	DYNAMIC void __fastcall DoEnter(void);
	DYNAMIC void __fastcall DoExit(void);
	virtual void __fastcall InitValidate(void);
	DYNAMIC void __fastcall KeyPress(char &Key);
	void __fastcall DrawSortSymbol(int x, int y);
	
public:
	int GSortBMWidth;
	int GSortBMHeight;
	__property bool Sorting = {read=fSorting, default=0};
	__property bool Modified = {read=fModified, write=fModified, default=0};
	__property TSortState SortState = {read=fSortState, nodefault};
	__fastcall virtual TSortGrid(Classes::TComponent* AOwner);
	__fastcall virtual ~TSortGrid(void);
	virtual void __fastcall MoveTo(int aCol, int aRow);
	virtual bool __fastcall Clear(void);
	virtual bool __fastcall ClearFrom(int FromRow);
	virtual void __fastcall InsertRow(int aRow);
	virtual void __fastcall InsertColumn(int aCol);
	HIDESBASE virtual void __fastcall DeleteRow(int aRow);
	HIDESBASE virtual void __fastcall DeleteColumn(int aCol);
	HIDESBASE virtual void __fastcall MoveRow(int FromIndex, int ToIndex);
	HIDESBASE virtual void __fastcall MoveColumn(int FromIndex, int ToIndex);
	virtual void __fastcall SwapRows(int aRow1, int aRow2);
	virtual void __fastcall SwapColumns(int aCol1, int aCol2);
	virtual void __fastcall AutoSizeCol(const int aCol);
	virtual void __fastcall AutoSizeColumns(const bool DoFixedCols, const int Padding);
	virtual void __fastcall SortByColumn(const int aCol, const TSortOptions &SortOptions);
	virtual bool __fastcall IsCell(const AnsiString Value, int &aCol, int &aRow);
	virtual void __fastcall LoadFromFile(const AnsiString FileName, const char Delimiter);
	virtual void __fastcall SaveToFile(const AnsiString FileName, const char Delimiter);
	virtual bool __fastcall CanUndoSort(void);
	virtual void __fastcall UndoSort(void);
	Grids::TGridDrawState __fastcall GetCellDrawState(const int aCol, const int aRow);
	virtual bool __fastcall SelectCell(int aCol, int aRow);
	virtual void __fastcall ValidateCell(void);
	virtual bool __fastcall InsertRows(int aRow, int rCount);
	virtual bool __fastcall InsertCols(int aCol, int cCount);
	virtual bool __fastcall ClearRows(int sRow, int eRow);
	virtual bool __fastcall RemoveRows(int sRow, int eRow);
	virtual bool __fastcall RemoveCols(int sCol, int eCol);
	virtual bool __fastcall ClearCols(int sCol, int eCol);
	bool __fastcall FindFirst(const AnsiString aStr, int &sCol, int &sRow, int eCol, int eRow);
	bool __fastcall FindNext(int &aCol, int &aRow);
	
__published:
	__property bool CaseSensitive = {read=fCaseSensitive, write=fCaseSensitive, nodefault};
	__property Classes::TAlignment AlignmentHorz = {read=fAlignmentHorz, write=SetAlignmentHorz, nodefault
		};
	__property TVertAlignment AlignmentVert = {read=fAlignmentVert, write=SetAlignmentVert, nodefault};
		
	__property TCellBevelStyle BevelStyle = {read=fBevelStyle, write=SetBevelStyle, default=0};
	__property bool ProportionalScrollBars = {read=fProportionalScrollBars, write=SetProportionalScrollBars
		, nodefault};
	__property bool ExtendedKeys = {read=fExtendedKeys, write=fExtendedKeys, nodefault};
	__property TSortSymbol SortSymbol = {read=fSortSymbol, write=SetSortSymbol, default=0};
	__property int SortSpacingHor = {read=fSortSpacingHor, write=SetSortSpacingHor, default=2};
	__property int SortSpacingVert = {read=fSortSpacingVert, write=SetSortSpacingVert, default=0};
	__property TSortDirection SortDirection = {read=fSortDirection, write=SetSortDirection, default=0};
		
	__property Graphics::TBitmap* SortBitMapA = {read=fSortBMA, write=SetSortBMA};
	__property Graphics::TBitmap* SortBitMapD = {read=fSortBMD, write=SetSortBMD};
	__property int SortColumn = {read=fSortColumn, write=SetSortColumn, default=1};
	__property bool SortOnClick = {read=fSortOnClick, write=SetSortOnClick, default=0};
	__property bool SortFooter = {read=fSortFooter, write=SetSortFooter, default=0};
	__property int FooterRows = {read=fFooterRows, write=SetFooterRows, default=0};
	__property Graphics::TColor FooterColor = {read=fFooterColor, write=SetFooterColor, default=16776960
		};
	__property Graphics::TFont* FooterFont = {read=fFooterFont, write=SetFooterFont};
	__property TCellBevelStyle FooterBevelStyle = {read=fFooterBevelStyle, write=SetFooterBevelStyle, default=0
		};
	__property TFormatDrawCellEvent OnGetCellFormat = {read=fOnGetCellFormat, write=fOnGetCellFormat};
	__property TClickSortEvent OnClickSort = {read=fOnClickSort, write=fOnClickSort};
	__property TUpdateGridEvent OnRowInsert = {read=fOnRowInsert, write=fOnRowInsert};
	__property TUpdateGridEvent OnRowDelete = {read=fOnRowDelete, write=fOnRowDelete};
	__property TUpdateGridEvent OnColumnInsert = {read=fOnColumnInsert, write=fOnColumnInsert};
	__property TUpdateGridEvent OnColumnDelete = {read=fOnColumnDelete, write=fOnColumnDelete};
	__property Classes::TNotifyEvent OnColumnWidthsChanged = {read=fOnColumnWidthsChanged, write=fOnColumnWidthsChanged
		};
	__property Classes::TNotifyEvent OnRowHeightsChanged = {read=fOnRowHeightsChanged, write=fOnRowHeightsChanged
		};
	__property TSizeChangedEvent OnSizeChanged = {read=fOnSizeChanged, write=fOnSizeChanged};
	__property TBeginSortEvent OnBeginSort = {read=fOnBeginSort, write=fOnBeginSort};
	__property TEndSortEvent OnEndSort = {read=fOnEndSort, write=fOnEndSort};
	__property TCellValidateEvent OnCellValidate = {read=fOnCellValidate, write=fOnCellValidate};
	__property Classes::TNotifyEvent OnMouseEnter = {read=fOnMouseEnter, write=fOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=fOnMouseLeave, write=fOnMouseLeave};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TSortGrid(HWND ParentWindow) : Grids::TStringGrid(
		ParentWindow) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall StringCompare(const AnsiString Str1, const AnsiString Str2);
extern PACKAGE int __fastcall DateTimeCompare(const AnsiString Str1, const AnsiString Str2);
extern PACKAGE int __fastcall TimeCompare(const AnsiString Str1, const AnsiString Str2);
extern PACKAGE int __fastcall NumericCompare(const AnsiString Str1, const AnsiString Str2);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Sortgrid */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Sortgrid;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SortGrid
