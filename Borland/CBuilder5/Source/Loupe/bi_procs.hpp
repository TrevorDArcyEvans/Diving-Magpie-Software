// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'bi_procs.pas' rev: 5.00

#ifndef bi_procsHPP
#define bi_procsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Buttons.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Bi_procs
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct myrgb
{
	Byte r;
	Byte g;
	Byte b;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int HSLRange;
extern PACKAGE void __fastcall StretchBitmapRectTransparent(Graphics::TCanvas* Dest, int X, int Y, int 
	W, int H, const Windows::TRect &Rect, Graphics::TBitmap* Bitmap, Graphics::TColor TransparentColor)
	;
extern PACKAGE void __fastcall DrawBitmapRectTransparent(Graphics::TCanvas* Dest, int XOrigin, int YOrigin
	, const Windows::TRect &Rect, Graphics::TBitmap* Bitmap, Graphics::TColor TransparentColor);
extern PACKAGE void __fastcall DrawBitmapTransparent(Graphics::TCanvas* Dest, int XOrigin, int YOrigin
	, Graphics::TBitmap* Bitmap, Graphics::TColor TransparentColor);
extern PACKAGE void __fastcall RGBTOCMYK(Byte R, Byte G, Byte B, Byte &C, Byte &M, Byte &Y, Byte &K)
	;
extern PACKAGE void __fastcall CMYKTORGB(Byte C, Byte M, Byte Y, Byte K, Byte &R, Byte &G, Byte &B);
	
extern PACKAGE void __fastcall mygrayedbmp(Graphics::TBitmap* &bmp1, const Graphics::TColor c1, const 
	Graphics::TColor c2);
extern PACKAGE void __fastcall DrawPopupMark(Graphics::TCanvas* theCanvas, int x, int y);
extern PACKAGE void __fastcall HSLtoRGB(double H, double S, double L, Byte &r, Byte &g, Byte &b);
extern PACKAGE void __fastcall HSLRangeToRGB(int H, int S, int L, Byte &r, Byte &g, Byte &b);
extern PACKAGE void __fastcall RGBtoHSL(Byte r, Byte g, Byte b, double &H, double &S, double &L);
extern PACKAGE void __fastcall RGBtoHSLRange(Byte r, Byte g, Byte b, Byte &H, Byte &S, Byte &L);
extern PACKAGE Byte __fastcall getcolorcaps(void);
extern PACKAGE void __fastcall myDrawButtonFace(Graphics::TCanvas* Canvas, const Windows::TRect &Client
	, int BevelWidth, bool IsDown, Graphics::TColor c1, Graphics::TColor c2);
extern PACKAGE int __fastcall booltoint(const bool b1);

}	/* namespace Bi_procs */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Bi_procs;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// bi_procs
