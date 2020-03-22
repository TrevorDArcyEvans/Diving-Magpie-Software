// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TreeNT.pas' rev: 5.00

#ifndef TreeNTHPP
#define TreeNTHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ComCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Commctrl.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Treent
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TreeNT__1 { toAutoExpand, toAutoScroll, toCheckSupport, toNoEraseBkgnd, toEvenHeight, toFullRowSelect, 
	toHideSelection, toHotTrack, toInfoTip, toLevelSelectConstraint, toMultiSelect, toNoScroll, toReadOnly, 
	toRightClickSelect, toToolTips, toShowButtons, toShowLines, toShowRoot, toSingleExpand, toWantReturn 
	};
#pragma option pop

typedef Set<TreeNT__1, toAutoExpand, toWantReturn>  TTreeOptions;

class DELPHICLASS TTreeNTNode;
class DELPHICLASS TTreeNTNodes;
class DELPHICLASS TCustomTreeNT;
#pragma option push -b-
enum TreeNT__7 { sdLeft, sdUp, sdRight, sdDown };
#pragma option pop

typedef Set<TreeNT__7, sdLeft, sdDown>  TScrollDirection;

#pragma option push -b-
enum TSortType { stNone, stData, stText, stBoth };
#pragma option pop

struct TSelectRec
{
	bool Pending;
	int StartX;
	int StartY;
	Windows::TRect Rect;
} ;

class DELPHICLASS TTreeNodeList;
#pragma option push -b-
enum TCheckState { csUnchecked, csChecked, csGrayed, csCheckedGrayed };
#pragma option pop

#pragma option push -b-
enum TCheckType { ctNone, ctCheckBox, ctCheckBoxGrayed, ctRadioButton };
#pragma option pop

#pragma option push -b-
enum TNodeState { nsChecked, nsCut, nsDisabled, nsDropHilited, nsExpanded, nsExpandedOnce, nsExpandPartial, 
	nsFocused, nsGrayed, nsHot, nsIndeterminate, nsMarked, nsSelected };
#pragma option pop

#pragma option push -b-
enum TAddMode { taAddFirst, taAdd, taInsert };
#pragma option pop

struct TNodeInfo;
typedef TNodeInfo *PNodeInfo;

#pragma option push -b-
enum TNodeAttachMode { naAdd, naAddFirst, naAddChild, naAddChildFirst, naInsert };
#pragma option pop

class PASCALIMPLEMENTATION TTreeNTNode : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TTreeNTNodes* FOwner;
	AnsiString FText;
	void *FData;
	_TREEITEM *FItemId;
	Graphics::TFont* FFont;
	TTreeNTNode* FParent;
	bool FExpanded;
	bool FParentColor;
	bool FParentFont;
	int FImageIndex;
	int FSelectedIndex;
	int FOverlayIndex;
	int FStateIndex;
	bool FDeleting;
	Graphics::TColor FColor;
	bool FInTree;
	int FUpdateCount;
	TTreeNodeList* FChildList;
	TCheckState FCheckState;
	TCheckType FCheckType;
	bool FEnabled;
	bool __fastcall DoCanExpand(bool Expand);
	void __fastcall DoCheckClick(void);
	void __fastcall DoExpand(bool Expand);
	void __fastcall ExpandItem(bool Expand, bool Recurse);
	int __fastcall GetAbsoluteCount(void);
	int __fastcall GetAbsoluteIndex(void);
	Graphics::TColor __fastcall GetColor(void);
	int __fastcall GetIndex(void);
	bool __fastcall GetExpanded(void);
	bool __fastcall GetExpandedOnce(void);
	bool __fastcall GetExpandedPartial(void);
	int __fastcall GetLevel(void);
	bool __fastcall GetChildren(void);
	bool __fastcall GetCut(void);
	bool __fastcall GetDropTarget(void);
	bool __fastcall GetFocused(void);
	Graphics::TFont* __fastcall GetFont(void);
	int __fastcall GetIntegralHeight(void);
	TTreeNTNode* __fastcall GetItem(int Index);
	TTreeNTNode* __fastcall GetParent(void);
	bool __fastcall GetSelected(void);
	bool __fastcall GetState(TNodeState NodeState);
	int __fastcall GetCount(void);
	TCustomTreeNT* __fastcall GetTreeNT(void);
	void __fastcall InternalMove(TTreeNTNode* ParentNode, TTreeNTNode* Node, HTREEITEM HItem, TAddMode 
		AddMode);
	bool __fastcall IsEqual(TTreeNTNode* Node);
	bool __fastcall IsNodeVisible(void);
	void __fastcall SetCheckState(TCheckState Value);
	void __fastcall SetCheckType(TCheckType Value);
	void __fastcall SetChildren(bool Value);
	void __fastcall SetColor(Graphics::TColor AValue);
	void __fastcall SetCut(bool Value);
	void __fastcall SetData(void * Value);
	void __fastcall SetDropTarget(bool Value);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetFont(Graphics::TFont* AFont);
	void __fastcall SetItem(int Index, TTreeNTNode* Value);
	void __fastcall SetExpanded(bool Value);
	void __fastcall SetExpandedPartial(bool Value);
	void __fastcall SetFocused(bool Value);
	void __fastcall SetImageIndex(int Value);
	void __fastcall SetIntegralHeight(int Value);
	void __fastcall SetOverlayIndex(int Value);
	void __fastcall SetParentColor(bool AValue);
	void __fastcall SetParentFont(bool AValue);
	void __fastcall SetSelectedIndex(int Value);
	void __fastcall SetSelected(bool Value);
	void __fastcall SetStateIndex(int Value);
	void __fastcall SetText(const AnsiString S);
	
protected:
	void __fastcall FontChanged(System::TObject* Sender);
	virtual void __fastcall ReadData(Classes::TStream* Stream, PNodeInfo Info);
	int __fastcall ReadStrings(char * &S, int CurrentLevel);
	virtual void __fastcall WriteData(Classes::TStream* Stream, PNodeInfo Info);
	void __fastcall WriteStrings(Classes::TStream* Stream, int Level);
	
public:
	__fastcall TTreeNTNode(TTreeNTNodes* AOwner);
	__fastcall virtual ~TTreeNTNode(void);
	bool __fastcall AlphaSort(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall BeginUpdate(void);
	void __fastcall Collapse(bool Recurse);
	bool __fastcall CustomSort(PFNTVCOMPARE SortProc, int Data);
	void __fastcall Delete(void);
	void __fastcall DeleteChildren(void);
	Windows::TRect __fastcall DisplayRect(bool TextOnly);
	bool __fastcall EditText(void);
	void __fastcall EndEdit(bool Cancel);
	void __fastcall EndUpdate(void);
	void __fastcall Expand(bool Recurse);
	TTreeNTNode* __fastcall GetFirstChild(void);
	HWND __fastcall GetHandle(void);
	TTreeNTNode* __fastcall GetLastChild(void);
	TTreeNTNode* __fastcall GetNext(void);
	TTreeNTNode* __fastcall GetNextChild(TTreeNTNode* Value);
	TTreeNTNode* __fastcall GetNextSelected(void);
	TTreeNTNode* __fastcall GetNextSibling(void);
	TTreeNTNode* __fastcall GetNextVisible(void);
	TTreeNTNode* __fastcall GetPrev(void);
	TTreeNTNode* __fastcall GetPrevChild(TTreeNTNode* Value);
	TTreeNTNode* __fastcall GetPrevSelected(void);
	TTreeNTNode* __fastcall GetPrevSibling(void);
	TTreeNTNode* __fastcall GetPrevVisible(void);
	bool __fastcall HasAsParent(TTreeNTNode* Value);
	int __fastcall IndexOf(TTreeNTNode* Value);
	bool __fastcall IsUpdating(void);
	void __fastcall MakeVisible(void);
	void __fastcall MoveTo(TTreeNTNode* Destination, TNodeAttachMode Mode);
	__property int AbsoluteCount = {read=GetAbsoluteCount, nodefault};
	__property int AbsoluteIndex = {read=GetAbsoluteIndex, nodefault};
	__property TCheckState CheckState = {read=FCheckState, write=SetCheckState, nodefault};
	__property TCheckType CheckType = {read=FCheckType, write=SetCheckType, nodefault};
	__property Graphics::TColor Color = {read=GetColor, write=SetColor, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property bool Cut = {read=GetCut, write=SetCut, nodefault};
	__property void * Data = {read=FData, write=SetData};
	__property bool Deleting = {read=FDeleting, nodefault};
	__property bool DropTarget = {read=GetDropTarget, write=SetDropTarget, nodefault};
	__property bool Focused = {read=GetFocused, write=SetFocused, nodefault};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property bool Expanded = {read=GetExpanded, write=SetExpanded, nodefault};
	__property bool ExpandedOnce = {read=GetExpandedOnce, nodefault};
	__property bool ExpandedPartial = {read=GetExpandedPartial, write=SetExpandedPartial, nodefault};
	__property Graphics::TFont* Font = {read=GetFont, write=SetFont};
	__property HWND Handle = {read=GetHandle, nodefault};
	__property bool HasChildren = {read=GetChildren, write=SetChildren, nodefault};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, nodefault};
	__property int Index = {read=GetIndex, nodefault};
	__property int IntegralHeight = {read=GetIntegralHeight, write=SetIntegralHeight, nodefault};
	__property bool IsVisible = {read=IsNodeVisible, nodefault};
	__property TTreeNTNode* Item[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property HTREEITEM ItemId = {read=FItemId};
	__property int Level = {read=GetLevel, nodefault};
	__property int OverlayIndex = {read=FOverlayIndex, write=SetOverlayIndex, nodefault};
	__property TTreeNTNodes* Owner = {read=FOwner};
	__property TTreeNTNode* Parent = {read=GetParent};
	__property bool ParentColor = {read=FParentColor, write=SetParentColor, default=1};
	__property bool ParentFont = {read=FParentFont, write=SetParentFont, default=1};
	__property bool Selected = {read=GetSelected, write=SetSelected, nodefault};
	__property int SelectedIndex = {read=FSelectedIndex, write=SetSelectedIndex, nodefault};
	__property int StateIndex = {read=FStateIndex, write=SetStateIndex, nodefault};
	__property AnsiString Text = {read=FText, write=SetText};
	__property TCustomTreeNT* TreeView = {read=GetTreeNT};
};


typedef TTreeNTNode* TNodeList[134217727];

typedef TTreeNTNode* *PNodeList;

class PASCALIMPLEMENTATION TTreeNodeList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TTreeNTNode* *FList;
	int FCount;
	int FCapacity;
	TTreeNTNode* __fastcall Get(int Index);
	void __fastcall Put(int Index, TTreeNTNode* Item);
	
protected:
	virtual void __fastcall Grow(void);
	void __fastcall SetCapacity(int NewCapacity);
	void __fastcall SetCount(int NewCount);
	
public:
	__fastcall virtual ~TTreeNodeList(void);
	int __fastcall Add(TTreeNTNode* Item);
	DYNAMIC void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	/*         class method */ static void __fastcall Error(TMetaClass* vmt, const AnsiString Msg, int 
		Data);
	void __fastcall Exchange(int Index1, int Index2);
	TTreeNodeList* __fastcall Expand(void);
	TTreeNTNode* __fastcall First(void);
	int __fastcall IndexOf(TTreeNTNode* Item);
	void __fastcall Insert(int Index, TTreeNTNode* Item);
	TTreeNTNode* __fastcall Last(void);
	void __fastcall Move(int CurIndex, int NewIndex);
	int __fastcall Remove(TTreeNTNode* Item);
	void __fastcall Pack(void);
	void __fastcall Sort(PFNTVCOMPARE Compare, int Data);
	__property int Capacity = {read=FCapacity, write=SetCapacity, nodefault};
	__property int Count = {read=FCount, write=SetCount, nodefault};
	__property TTreeNTNode* Items[int Index] = {read=Get, write=Put/*, default*/};
	__property PNodeList List = {read=FList};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TTreeNodeList(void) : System::TObject() { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TTVPaintEvent)(System::TObject* Sender);

typedef Set<TNodeState, nsChecked, nsSelected>  TNodeStates;

typedef void __fastcall (__closure *TTVAfterItemPaintEvent)(System::TObject* Sender, TTreeNTNode* Node
	, const Windows::TRect &ItemRect, TNodeStates NodeStates);

typedef void __fastcall (__closure *TTVBeforeItemPaintEvent)(System::TObject* Sender, TTreeNTNode* Node
	, const Windows::TRect &ItemRect, TNodeStates NodeStates, bool &OwnerDraw);

typedef void __fastcall (__closure *TTVEditingEvent)(System::TObject* Sender, TTreeNTNode* Node, bool 
	&AllowEdit);

typedef void __fastcall (__closure *TTVEditedEvent)(System::TObject* Sender, TTreeNTNode* Node, AnsiString 
	&S);

typedef void __fastcall (__closure *TTVExpandedEvent)(System::TObject* Sender, TTreeNTNode* Node);

typedef void __fastcall (__closure *TTVExpandingEvent)(System::TObject* Sender, TTreeNTNode* Node, bool 
	&AllowExpansion);

typedef void __fastcall (__closure *TTVCollapsingEvent)(System::TObject* Sender, TTreeNTNode* Node, 
	bool &AllowCollapse);

typedef void __fastcall (__closure *TTVChangingEvent)(System::TObject* Sender, TTreeNTNode* Node, bool 
	&AllowChange);

typedef void __fastcall (__closure *TTVChangedEvent)(System::TObject* Sender, TTreeNTNode* Node);

typedef void __fastcall (__closure *TTVCompareEvent)(System::TObject* Sender, TTreeNTNode* Node1, TTreeNTNode* 
	Node2, int Data, int &Compare);

typedef void __fastcall (__closure *TTVHintEvent)(System::TObject* Sender, TTreeNTNode* Node, AnsiString 
	&NewText);

typedef void __fastcall (__closure *TTVSingleExpandingEvent)(System::TObject* Sender, TTreeNTNode* Node
	, bool &AutoCollapse);

typedef TMetaClass*TTreeNTNodeClass;

typedef void __fastcall (__closure *TTVCreateNodeEvent)(System::TObject* Sender, TMetaClass* &NodeClass
	);

typedef void __fastcall (__closure *TTVCheckingEvent)(System::TObject* Sender, TTreeNTNode* Node, bool 
	&AllowCheck);

typedef void __fastcall (__closure *TTVCheckedEvent)(System::TObject* Sender, TTreeNTNode* Node);

typedef void __fastcall (__closure *TTVPopupEvent)(System::TObject* Sender, TTreeNTNode* Node, bool 
	&AskParent, Menus::TPopupMenu* &PopupMenu);

typedef void __fastcall (__closure *TTVHelpContextEvent)(System::TObject* Sender, TTreeNTNode* Node, 
	int &HelpContext);

typedef void __fastcall (__closure *TLevelErrorEvent)(int Line, bool &RaiseException);

#pragma option push -b-
enum TSelectType { stSet, stReset, stToggle };
#pragma option pop

#pragma option push -b-
enum THitTest { htAbove, htBelow, htNowhere, htOnItem, htOnButton, htOnIcon, htOnIndent, htOnLabel, 
	htOnRight, htOnStateIcon, htToLeft, htToRight };
#pragma option pop

typedef Set<THitTest, htAbove, htToRight>  THitTests;

class PASCALIMPLEMENTATION TCustomTreeNT : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	Forms::TFormBorderStyle FBorderStyle;
	Controls::TImageList* FImages;
	Controls::TImageList* FStateImages;
	Imglist::TChangeLink* FImageChangeLink;
	Imglist::TChangeLink* FStateChangeLink;
	Extctrls::TTimer* FExpandTimer;
	Extctrls::TTimer* FScrollTimer;
	TScrollDirection FScrollDirection;
	Controls::TImageList* FDragImage;
	TTreeNTNodes* FTreeNTNodes;
	TSortType FSortType;
	int FSaveTopIndex;
	int FSaveIndex;
	int FSaveIndent;
	int FSaveItemHeight;
	int FScrollTime;
	Classes::TMemoryStream* FMemStream;
	void *FEditInstance;
	void *FDefEditProc;
	HWND FEditHandle;
	bool FDragged;
	bool FClicked;
	bool FRClicked;
	TTreeOptions FOptions;
	bool FManualNotify;
	TTreeNTNode* FLastDropTarget;
	TTreeNTNode* FDragNode;
	Controls::TDragObject* FDragObject;
	TTreeNTNode* FRClickNode;
	Graphics::TCanvas* FCanvas;
	unsigned FLastFont;
	bool FStateChanging;
	TTreeNTNode* FFirstSelection;
	TSelectRec FSelectRec;
	TTreeNodeList* FHitList;
	TTreeNTNode* FCheckNode;
	Graphics::TColor FColorUnfocusedSelected;
	Graphics::TColor FColorSelected;
	Graphics::TColor FColorDropSelected;
	TTVPaintEvent FOnAfterPaint;
	TTVPaintEvent FOnBeforePaint;
	TTVAfterItemPaintEvent FOnAfterItemPaint;
	TTVBeforeItemPaintEvent FOnBeforeItemPaint;
	TTVEditingEvent FOnEditing;
	TTVEditedEvent FOnEdited;
	TTVExpandedEvent FOnExpanded;
	TTVExpandingEvent FOnExpanding;
	TTVExpandedEvent FOnCollapsed;
	TTVCollapsingEvent FOnCollapsing;
	TTVChangingEvent FOnChanging;
	TTVChangedEvent FOnChange;
	TTVCompareEvent FOnCompare;
	TTVExpandedEvent FOnDeletion;
	TTVExpandedEvent FOnGetImageIndex;
	TTVExpandedEvent FOnGetSelectedIndex;
	TTVHintEvent FOnHint;
	TTVSingleExpandingEvent FOnSingleExpanded;
	TTVCreateNodeEvent FOnCreateNode;
	TTVCheckingEvent FOnChecking;
	TTVCheckedEvent FOnChecked;
	TTVPopupEvent FOnGetPopupMenu;
	TTVHelpContextEvent FOnGetHelpContext;
	TLevelErrorEvent FOnLevelError;
	HIDESBASE MESSAGE void __fastcall CMColorChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMCtl3DChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMDrag(Controls::TCMDrag &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMSysColorChange(Messages::TMessage &Message);
	MESSAGE void __fastcall CNNotify(Messages::TWMNotify &Message);
	void __fastcall DoDragExpand(System::TObject* Sender);
	void __fastcall DoScroll(System::TObject* Sender);
	void __fastcall DoDragOver(Controls::TDragObject* Source, int X, int Y, bool CanDrop);
	void __fastcall EditWndProc(Messages::TMessage &Message);
	HIDESBASE void __fastcall FontChanged(System::TObject* Sender);
	int __fastcall GetChangeDelay(void);
	TTreeNTNode* __fastcall GetDropTarget(void);
	void __fastcall GetImageIndex(TTreeNTNode* Node);
	int __fastcall GetIndent(void);
	Graphics::TColor __fastcall GetInsertMarkColor(void);
	Shortint __fastcall GetItemHeight(void);
	TTreeNTNode* __fastcall GetLastVisibleNode(void);
	TTreeNTNode* __fastcall GetNodeFromItem(const tagTVITEMA &Item);
	int __fastcall GetScrollTime(void);
	AnsiString __fastcall GetSearchString();
	void __fastcall GetSelectedIndex(TTreeNTNode* Node);
	TTreeNTNode* __fastcall GetSelection(void);
	TTreeNTNode* __fastcall GetTopItem(void);
	int __fastcall GetTreeHeight(void);
	int __fastcall GetTreeWidth(void);
	void __fastcall HandleDrawSelection(Classes::TShiftState Shift, const Windows::TRect &Rect);
	void __fastcall HandleMultiSelection(TTreeNTNode* LastNode, TSelectType OldState, TTreeNTNode* NewNode
		, TSelectType NewState, Classes::TShiftState Shift);
	void __fastcall ImageListChange(System::TObject* Sender);
	void __fastcall OnChangeTimer(System::TObject* Sender);
	void __fastcall SetBorderStyle(Forms::TBorderStyle Value);
	void __fastcall SetCheckImage(TTreeNTNode* Node, int Image);
	void __fastcall SetColorDropSelected(Graphics::TColor Color);
	void __fastcall SetColorSelected(Graphics::TColor Color);
	void __fastcall SetColorUnfocusedSelected(Graphics::TColor Color);
	void __fastcall SetChangeDelay(int Value);
	void __fastcall SetDropTarget(TTreeNTNode* Value);
	void __fastcall SetImageList(unsigned Value, int Flags);
	void __fastcall SetIndent(int Value);
	void __fastcall SetInsertMarkColor(Graphics::TColor Value);
	void __fastcall SetImages(Controls::TImageList* Value);
	void __fastcall SetItemHeight(Shortint Value);
	void __fastcall SetOptions(TTreeOptions Values);
	void __fastcall SetScrollTime(int Value);
	void __fastcall SetSelection(TTreeNTNode* Value);
	void __fastcall SetSortType(TSortType Value);
	void __fastcall SetStateImages(Controls::TImageList* Value);
	void __fastcall SetStyle(int Value, bool UseStyle);
	void __fastcall SetTreeNTNodes(TTreeNTNodes* Value);
	void __fastcall SetTopItem(TTreeNTNode* Value);
	HIDESBASE MESSAGE void __fastcall WMDestroy(Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall WMKeyDown(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMRButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMRButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Messages::TWMNCHitTest &Message);
	HIDESBASE MESSAGE void __fastcall WMNotify(Messages::TWMNotify &Message);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	
protected:
	Extctrls::TTimer* FChangeTimer;
	DYNAMIC bool __fastcall CanCheck(TTreeNTNode* Node);
	DYNAMIC bool __fastcall CanEdit(TTreeNTNode* Node);
	DYNAMIC bool __fastcall CanChange(TTreeNTNode* Node);
	DYNAMIC bool __fastcall CanCollapse(TTreeNTNode* Node);
	DYNAMIC bool __fastcall CanExpand(TTreeNTNode* Node);
	DYNAMIC void __fastcall Change(TTreeNTNode* Node);
	DYNAMIC void __fastcall Check(TTreeNTNode* Node);
	DYNAMIC void __fastcall Collapse(TTreeNTNode* Node);
	virtual TTreeNTNode* __fastcall CreateNode(void);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall DestroyWnd(void);
	virtual void __fastcall DoAutoScroll(int X, int Y);
	virtual void __fastcall DoChange(TTreeNTNode* Node);
	DYNAMIC void __fastcall DoEndDrag(System::TObject* Target, int X, int Y);
	DYNAMIC void __fastcall DoStartDrag(Controls::TDragObject* &DragObject);
	void __fastcall DrawFocusRect(const Windows::TRect &Rect);
	DYNAMIC void __fastcall Edit(const tagTVITEMA &Item);
	DYNAMIC void __fastcall Expand(TTreeNTNode* Node);
	virtual Controls::TDragImageList* __fastcall GetDragImages(void);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	virtual void __fastcall SetDragMode(Controls::TDragMode Value);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	__property Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=1};
	__property int ChangeDelay = {read=GetChangeDelay, write=SetChangeDelay, default=0};
	__property Graphics::TColor ColorDropSelected = {read=FColorDropSelected, write=SetColorDropSelected
		, default=-2147483633};
	__property Graphics::TColor ColorSelected = {read=FColorSelected, write=SetColorSelected, default=-2147483635
		};
	__property Graphics::TColor ColorUnfocusedSelected = {read=FColorUnfocusedSelected, write=SetColorUnfocusedSelected
		, default=-2147483626};
	__property Controls::TImageList* Images = {read=FImages, write=SetImages};
	__property int Indent = {read=GetIndent, write=SetIndent, nodefault};
	__property Graphics::TColor InsertMarkColor = {read=GetInsertMarkColor, write=SetInsertMarkColor, nodefault
		};
	__property Shortint ItemHeight = {read=GetItemHeight, write=SetItemHeight, nodefault};
	__property TTreeNTNodes* Items = {read=FTreeNTNodes, write=SetTreeNTNodes};
	__property TTreeOptions Options = {read=FOptions, write=SetOptions, default=237651};
	__property int ScrollTime = {read=GetScrollTime, write=SetScrollTime, default=100};
	__property AnsiString SearchString = {read=GetSearchString};
	__property TSortType SortType = {read=FSortType, write=SetSortType, default=0};
	__property Controls::TImageList* StateImages = {read=FStateImages, write=SetStateImages};
	__property TTVPaintEvent OnAfterPaint = {read=FOnAfterPaint, write=FOnAfterPaint};
	__property TTVAfterItemPaintEvent OnAfterItemPaint = {read=FOnAfterItemPaint, write=FOnAfterItemPaint
		};
	__property TTVPaintEvent OnBeforePaint = {read=FOnBeforePaint, write=FOnBeforePaint};
	__property TTVBeforeItemPaintEvent OnBeforeItemPaint = {read=FOnBeforeItemPaint, write=FOnBeforeItemPaint
		};
	__property TTVCheckedEvent OnChecked = {read=FOnChecked, write=FOnChecked};
	__property TTVCheckingEvent OnChecking = {read=FOnChecking, write=FOnChecking};
	__property TTVCollapsingEvent OnCollapsing = {read=FOnCollapsing, write=FOnCollapsing};
	__property TTVExpandedEvent OnCollapsed = {read=FOnCollapsed, write=FOnCollapsed};
	__property TTVChangingEvent OnChanging = {read=FOnChanging, write=FOnChanging};
	__property TTVChangedEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TTVCompareEvent OnCompare = {read=FOnCompare, write=FOnCompare};
	__property TTVCreateNodeEvent OnCreateNode = {read=FOnCreateNode, write=FOnCreateNode};
	__property TTVExpandedEvent OnDeletion = {read=FOnDeletion, write=FOnDeletion};
	__property TTVEditingEvent OnEditing = {read=FOnEditing, write=FOnEditing};
	__property TTVEditedEvent OnEdited = {read=FOnEdited, write=FOnEdited};
	__property TTVExpandingEvent OnExpanding = {read=FOnExpanding, write=FOnExpanding};
	__property TTVExpandedEvent OnExpanded = {read=FOnExpanded, write=FOnExpanded};
	__property TTVHelpContextEvent OnGetHelpContext = {read=FOnGetHelpContext, write=FOnGetHelpContext}
		;
	__property TTVExpandedEvent OnGetImageIndex = {read=FOnGetImageIndex, write=FOnGetImageIndex};
	__property TTVPopupEvent OnGetPopupMenu = {read=FOnGetPopupMenu, write=FOnGetPopupMenu};
	__property TTVExpandedEvent OnGetSelectedIndex = {read=FOnGetSelectedIndex, write=FOnGetSelectedIndex
		};
	__property TTVHintEvent OnHint = {read=FOnHint, write=FOnHint};
	__property TTVSingleExpandingEvent OnSingleExpanded = {read=FOnSingleExpanded, write=FOnSingleExpanded
		};
	
public:
	__fastcall virtual TCustomTreeNT(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomTreeNT(void);
	bool __fastcall AlphaSort(void);
	void __fastcall ClearSelection(void);
	bool __fastcall CustomSort(PFNTVCOMPARE SortProc, int Data);
	void __fastcall DrawTo(Graphics::TCanvas* ACanvas);
	void __fastcall FullCollapse(void);
	void __fastcall FullExpand(void);
	THitTests __fastcall GetHitTestInfoAt(int X, int Y);
	TTreeNTNode* __fastcall GetNodeAt(int X, int Y);
	HWND __fastcall GetToolTips(void);
	bool __fastcall IsEditing(void);
	bool __fastcall IsMouseSelecting(void);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall Print(int XPos, int YPos, int Width);
	void __fastcall SaveToFile(const AnsiString FileName, bool Complete);
	void __fastcall SaveToStream(Classes::TStream* Stream, bool Complete);
	Windows::TPoint __fastcall ScreenToClientEx(const Windows::TPoint &Point);
	HWND __fastcall SetToolTips(HWND TTHandle);
	void __fastcall ShowInsertMark(TTreeNTNode* Node, bool After);
	__property Graphics::TCanvas* Canvas = {read=FCanvas};
	__property TTreeNTNode* DropTarget = {read=GetDropTarget, write=SetDropTarget};
	__property TTreeNTNode* LastVisibleNode = {read=GetLastVisibleNode};
	__property TTreeNTNode* Selected = {read=GetSelection, write=SetSelection};
	__property TTreeNTNode* TopItem = {read=GetTopItem, write=SetTopItem};
	__property int TreeHeight = {read=GetTreeHeight, nodefault};
	__property int TreeWidth = {read=GetTreeWidth, nodefault};
	__property TLevelErrorEvent OnLevelError = {read=FOnLevelError, write=FOnLevelError};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomTreeNT(HWND ParentWindow) : Controls::TWinControl(
		ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TreeNT__4 { ffText, ffData };
#pragma option pop

typedef Set<TreeNT__4, ffText, ffData>  TFindFlags;

class PASCALIMPLEMENTATION TTreeNTNodes : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomTreeNT* FOwner;
	int FUpdateCount;
	bool FCoreSelecting;
	bool FDeleting;
	TTreeNTNode* FRoot;
	TTreeNodeList* FItemCache;
	TTreeNodeList* FSelection;
	int FSelLockCount;
	TCheckType FRootCheckType;
	int FLastSelLevel;
	void __fastcall AddedNode(TTreeNTNode* ParentNode);
	HWND __fastcall GetHandle(void);
	void __fastcall ReadData(Classes::TStream* Stream);
	void __fastcall Repaint(TTreeNTNode* Node);
	void __fastcall SetCheckType(TCheckType Value);
	void __fastcall WriteData(Classes::TStream* Stream);
	
protected:
	HTREEITEM __fastcall AddItem(HTREEITEM Parent, HTREEITEM Target, const tagTVITEMA &Item, TAddMode AddMode
		);
	void __fastcall AddToSelection(TTreeNTNode* Node);
	TTreeNTNode* __fastcall InternalAddObject(TTreeNTNode* Node, const AnsiString S, void * Ptr, TAddMode 
		AddMode);
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	tagTVITEMA __fastcall CreateItem(TTreeNTNode* Node);
	void __fastcall FillCache(void);
	int __fastcall GetCount(void);
	int __fastcall GetSelectedCount(void);
	void __fastcall SelectNode(TTreeNTNode* Node, TSelectType Value);
	void __fastcall SelectNodes(TTreeNTNode* NodeFrom, TTreeNTNode* NodeTo, bool AddOnly);
	void __fastcall SetItem(int Index, TTreeNTNode* Value);
	void __fastcall SetUpdateState(bool Updating);
	void __fastcall ToggleSelectionRange(TTreeNTNode* NodeFrom, TTreeNTNode* NodeTo);
	void __fastcall ReadStrings(Classes::TStream* Stream);
	void __fastcall RemoveFromSelection(TTreeNTNode* Node);
	void __fastcall WriteStrings(Classes::TStream* Stream);
	
public:
	__fastcall TTreeNTNodes(TCustomTreeNT* AOwner);
	__fastcall virtual ~TTreeNTNodes(void);
	TTreeNTNode* __fastcall AddChildFirst(TTreeNTNode* Node, const AnsiString S);
	TTreeNTNode* __fastcall AddChild(TTreeNTNode* Node, const AnsiString S);
	TTreeNTNode* __fastcall AddChildObjectFirst(TTreeNTNode* Node, const AnsiString S, void * Ptr);
	TTreeNTNode* __fastcall AddChildObject(TTreeNTNode* Node, const AnsiString S, void * Ptr);
	TTreeNTNode* __fastcall AddFirst(TTreeNTNode* Node, const AnsiString S);
	TTreeNTNode* __fastcall Add(TTreeNTNode* Node, const AnsiString S);
	TTreeNTNode* __fastcall AddObjectFirst(TTreeNTNode* Node, const AnsiString S, void * Ptr);
	TTreeNTNode* __fastcall AddObject(TTreeNTNode* Node, const AnsiString S, void * Ptr);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall BeginUpdate(void);
	void __fastcall Clear(void);
	void __fastcall Delete(TTreeNTNode* Node);
	void __fastcall DeleteSelectedNodes(void);
	void __fastcall EndUpdate(void);
	TTreeNTNode* __fastcall FindNode(TFindFlags Flags, AnsiString AText, void * AData);
	TTreeNTNode* __fastcall GetFirstNode(void);
	TTreeNTNode* __fastcall GetFirstSelectedNode(void);
	TTreeNTNode* __fastcall GetNode(HTREEITEM ItemId);
	TTreeNTNode* __fastcall GetNodeFromIndex(int Index);
	TTreeNTNode* __fastcall Insert(TTreeNTNode* Node, const AnsiString S);
	TTreeNTNode* __fastcall InsertObject(TTreeNTNode* Node, const AnsiString S, void * Ptr);
	virtual void __fastcall InvalidateItemCache(void);
	bool __fastcall IsDeleting(void);
	bool __fastcall IsUpdating(void);
	int __fastcall LockSelection(void);
	void __fastcall SelectAll(void);
	int __fastcall UnlockSelection(void);
	__property int Count = {read=GetCount, nodefault};
	__property HWND Handle = {read=GetHandle, nodefault};
	__property TTreeNTNode* Item[int Index] = {read=GetNodeFromIndex/*, default*/};
	__property int SelectedCount = {read=GetSelectedCount, nodefault};
	__property TCustomTreeNT* Owner = {read=FOwner};
	__property TCheckType TopLevelCheckType = {read=FRootCheckType, write=SetCheckType, nodefault};
};



typedef TTreeNTNode* TNodeList[134217727];

typedef TTreeNTNode* *PNodeList;

#pragma pack(push, 1)
struct TNodeInfo
{
	int ImageIndex;
	int SelectedIndex;
	int StateIndex;
	int OverlayIndex;
	int IntegralHeight;
	TCheckState CheckState;
	TCheckType CheckType;
	bool Enabled;
	bool Expanded;
	bool Selected;
	void *Data;
	int Count;
	Graphics::TColor Color;
	bool ParentColor;
	bool ParentFont;
	Graphics::TFontData FontData;
	Graphics::TColor FontColor;
	System::SmallString<255>  Text;
} ;
#pragma pack(pop)

class DELPHICLASS ETreeNTError;
class PASCALIMPLEMENTATION ETreeNTError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ETreeNTError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETreeNTError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETreeNTError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETreeNTError(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETreeNTError(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETreeNTError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETreeNTError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETreeNTError(System::PResStringRec ResStringRec, 
		const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETreeNTError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTreeNT;
class PASCALIMPLEMENTATION TTreeNT : public TCustomTreeNT 
{
	typedef TCustomTreeNT inherited;
	
__published:
	__property Align ;
	__property Anchors ;
	__property BiDiMode ;
	__property BorderStyle ;
	__property BorderWidth ;
	__property ChangeDelay ;
	__property Color ;
	__property ColorDropSelected ;
	__property ColorSelected ;
	__property ColorUnfocusedSelected ;
	__property Ctl3D ;
	__property Constraints ;
	__property DragKind ;
	__property DragCursor ;
	__property DragMode ;
	__property Enabled ;
	__property Font ;
	__property Images ;
	__property Indent ;
	__property InsertMarkColor ;
	__property Items ;
	__property ItemHeight ;
	__property Options ;
	__property ParentBiDiMode ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property ScrollTime ;
	__property SearchString ;
	__property SortType ;
	__property StateImages ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnAfterPaint ;
	__property OnAfterItemPaint ;
	__property OnBeforePaint ;
	__property OnBeforeItemPaint ;
	__property OnChange ;
	__property OnChanging ;
	__property OnChecked ;
	__property OnChecking ;
	__property OnClick ;
	__property OnCollapsed ;
	__property OnCollapsing ;
	__property OnCompare ;
	__property OnCreateNode ;
	__property OnDeletion ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEdited ;
	__property OnEditing ;
	__property OnEndDock ;
	__property OnEnter ;
	__property OnExit ;
	__property OnExpanded ;
	__property OnExpanding ;
	__property OnEndDrag ;
	__property OnGetHelpContext ;
	__property OnGetImageIndex ;
	__property OnGetPopupMenu ;
	__property OnGetSelectedIndex ;
	__property OnHint ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnSingleExpanded ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TCustomTreeNT.Create */ inline __fastcall virtual TTreeNT(Classes::TComponent* AOwner) : TCustomTreeNT(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomTreeNT.Destroy */ inline __fastcall virtual ~TTreeNT(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TTreeNT(HWND ParentWindow) : TCustomTreeNT(ParentWindow
		) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Byte CDRF_NOTIFYITEMERASE = 0x80;
static const Shortint ckEmpty = 0x0;
static const Shortint ckCheckEmpty = 0x1;
static const Shortint ckCheckChecked = 0x2;
static const Shortint ckCheckDisabled = 0x3;
static const Shortint ckCheckGrayed = 0x4;
static const Shortint ckRadioEmpty = 0x5;
static const Shortint ckRadioChecked = 0x6;
static const Shortint ckRadioDisabled = 0x7;
static const Shortint ckRadioGrayed = 0x8;
#define DefaultOptions (System::Set<TreeNT__1, toAutoExpand, toWantReturn> () )

}	/* namespace Treent */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Treent;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TreeNT
