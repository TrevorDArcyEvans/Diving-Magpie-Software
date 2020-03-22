//---------------------------------------------------------------------------
// Borland C++Builder
// Copyright (c) 1987, 1998 Inprise Corporation. All Rights Reserved.
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TrayCompH
#define TrayCompH
//---------------------------------------------------------------------------
#include <System.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ShellAPI.hpp>
#include <StdLib.h>

//---------------------------------------------------------------------------
#define WM_SYSTEM_TRAY_NOTIFY (WM_USER + 100)

enum TTrayCompButtonClick {arLeftClick, arLeftDblClick, arLeftClickUp,
                  arRightClick, arRightDblClick, arRightClickUp, arNone};

//---------------------------------------------------------------------------
class PACKAGE TTrayComp : public TComponent
{
private:
   TNotifyIconData FNid;
   TIcon *FIcon;
   TImageList* FIconList;
   TPopupMenu* FPopupMenu;
   TTimer *FTimer;
   String FHint;
   int FIconIndex;
   bool FVisible;
   bool FHide;
   TTrayCompButtonClick FAppRestore;
        TTrayCompButtonClick FPopupMenuShow;

   TNotifyEvent FOnMinimize;
   TNotifyEvent FOnRestore;
   TNotifyEvent FOnLButtonDblClick;
   TNotifyEvent FOnLButtonDown;
   TNotifyEvent FOnLButtonUp;
   TNotifyEvent FOnRButtonDblClick;
   TNotifyEvent FOnRButtonDown;
   TNotifyEvent FOnRButtonUp;

protected:
   virtual void __fastcall SetVisible(bool Value);
   virtual void __fastcall TrayCompMinimize(TObject* Sender);
   virtual void __fastcall TrayCompRestore(TObject* Sender);
   virtual void __fastcall SetHint(String Hint);
   virtual void __fastcall SetHide(bool Value);
   virtual int __fastcall GetInterval();
   virtual void __fastcall SetInterval(int Value);
   virtual bool __fastcall GetAnimate();
   virtual void __fastcall SetAnimate(bool Value);

   virtual void __fastcall OnMessage(TMessage &Message);
   virtual void __fastcall LButtonDown();
   virtual void __fastcall LButtonUp();
   virtual void __fastcall LButtonDblClick();
   virtual void __fastcall RButtonDown();
   virtual void __fastcall RButtonUp();
   virtual void __fastcall RButtonDblClick();
   virtual void __fastcall EndSession();

   virtual void __fastcall Loaded();

public:
   __fastcall TTrayComp(TComponent* Owner);
   virtual __fastcall ~TTrayComp();

   virtual void __fastcall Minimize();
   virtual void __fastcall Restore();
   virtual void __fastcall Update();
   virtual void __fastcall ShowMenu();
   virtual void __fastcall SetIconIndex(int Value);
   virtual void __fastcall OnAnimation(TObject* Sender);
   virtual void __fastcall SetDefaultIcon();

__published:
   // Properties
   __property bool Visible = {read=FVisible,write=SetVisible,default=false};
   __property String Hint = {read=FHint,write=SetHint};
   __property TPopupMenu* PopupMenu = {read=FPopupMenu,write=FPopupMenu};
   __property bool Hide = {read=FHide,write=SetHide};
   __property TTrayCompButtonClick RestoreOn = {read=FAppRestore,write=FAppRestore};
   __property TTrayCompButtonClick PopupMenuOn = {read=FPopupMenuShow,write=FPopupMenuShow};
   __property TImageList* Icons = {read=FIconList,write=FIconList};
   __property int IconIndex = {read=FIconIndex,write=SetIconIndex,default=0};
   __property int Interval = {read=GetInterval,write=SetInterval,default=1000};
   __property bool Animate = {read=GetAnimate,write=SetAnimate,default=false};

   // Events
   __property TNotifyEvent OnMinimize = {read=FOnMinimize,write=FOnMinimize};
   __property TNotifyEvent OnRestore = {read=FOnRestore,write=FOnRestore};
   __property TNotifyEvent OnLButtonDblClick = {read=FOnLButtonDblClick,write=FOnLButtonDblClick};
   __property TNotifyEvent OnLButtonDown = {read=FOnLButtonDown,write=FOnLButtonDown};
   __property TNotifyEvent OnLButtonUp = {read=FOnLButtonUp,write=FOnLButtonUp};
   __property TNotifyEvent OnRButtonDblClick = {read=FOnRButtonDblClick,write=FOnRButtonDblClick};
   __property TNotifyEvent OnRButtonDown = {read=FOnRButtonDown,write=FOnRButtonDown};
   __property TNotifyEvent OnRButtonUp = {read=FOnRButtonUp,write=FOnRButtonUp};
};
//---------------------------------------------------------------------------
#endif