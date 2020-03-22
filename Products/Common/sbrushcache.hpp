#ifndef __SBrushCache_hpp
#define __SBrushCache_hpp

#include "stdafx.h"
#include <afxtempl.h>
#include "SColour.hpp"

class SBrushEntry
{
public:

	SColour	m_Colour;
	CBrush*	m_Brush;

	SBrushEntry ():m_Brush (0) {}
};//SBrushEntry

class SPenEntry
{
public:

	SColour	m_Colour;
	int		m_Width;
	int		m_LineStyle;
	CPen*	m_Pen;

	SPenEntry ():m_Width (0),m_Pen (0),m_LineStyle (PS_SOLID) {}
};//SPenEntry

class SFontEntry
{
public:
	
	int		m_PointSize;
	CString	m_Typeface;
	int		m_TextStyle;
	CFont*	m_Font;

	SFontEntry ():m_PointSize (0),m_Font (0) {}
};//SFontEntry

typedef CArray <SBrushEntry,SBrushEntry&>	SBrushArray;
typedef CArray <SPenEntry,SPenEntry&>		SPenArray;
typedef CArray <SFontEntry,SFontEntry&>		SFontArray; 

class SBrushCache
{
private:

	SBrushArray			m_Brushes;
	SPenArray			m_Pens;
	SFontArray			m_Fonts;

	static SBrushCache*	sm_Instance;

	SBrushCache () {}
	~SBrushCache ();

public:

	static void Destroy ();

	static SBrushCache* Instance ();

	CPen*   GetPen   (int Width,const SColour& Colour,int LineStyle);
	CBrush*	GetBrush (const SColour& Colour);
	CFont*	GetFont	 (int PointSize,const CString& Typeface,int TextStyle);

	void FreePen   (int Width,const SColour& Colour) {}
	void FreeBrush (const SColour& Colour) {}
	void FreeFont  (int PointSize,const CString& Typeface);

	void RemapColours ();
};//SBrushCache

#endif

