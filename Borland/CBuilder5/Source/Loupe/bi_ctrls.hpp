// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'bi_ctrls.pas' rev: 5.00

#ifndef bi_ctrlsHPP
#define bi_ctrlsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <bi_timer.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Bi_ctrls
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBI_Loupe;
class PASCALIMPLEMENTATION TBI_Loupe : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Bi_timer::TBI_Timer* _timer;
	int x;
	int y;
	HDC DC;
	HDC dcpuffer;
	HDC puffer;
	double fzoom;
	bool factive;
	Graphics::TBitmap* mybuffer;
	int finterval;
	Controls::TBevelCut fbeveli;
	Controls::TBevelCut fbevelo;
	Controls::TBevelWidth fbevelwidth;
	bool fdesign;
	void __fastcall _mypaint(System::TObject* sender);
	void __fastcall Resized(void);
	void __fastcall SetZoom(double value);
	void __fastcall SetInterval(int value);
	void __fastcall SetActive(bool value);
	void __fastcall SetDesign(bool value);
	void __fastcall SetBeveLi(Controls::TBevelCut value);
	void __fastcall SetBeveLo(Controls::TBevelCut value);
	void __fastcall SetBevelWidth(Controls::TBevelWidth value);
	void __fastcall PaintCrosshairs(void);
	
protected:
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TBI_Loupe(Classes::TComponent* AOwner);
	__fastcall virtual ~TBI_Loupe(void);
	void __fastcall SaveToFile(AnsiString s1);
	
__published:
	__property double ZoomLevel = {read=fzoom, write=SetZoom};
	__property int Interval = {read=finterval, write=SetInterval, nodefault};
	__property bool Active = {read=factive, write=SetActive, nodefault};
	__property Controls::TBevelCut BevelInner = {read=fbeveli, write=SetBeveLi, nodefault};
	__property Controls::TBevelCut BevelOuter = {read=fbevelo, write=SetBeveLo, nodefault};
	__property Controls::TBevelWidth Bevelwidth = {read=fbevelwidth, write=SetBevelWidth, nodefault};
	__property bool DrawDesigning = {read=fdesign, write=SetDesign, nodefault};
	__property Visible ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property ShowHint ;
	__property ParentFont ;
	__property Align ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Bi_ctrls */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Bi_ctrls;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// bi_ctrls
