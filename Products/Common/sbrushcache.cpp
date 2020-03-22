/*
History:
    [01]    TDE     16May00     changed to use Pencil.h & SPencil2.h
                                TODO remove brush cache towards end of step 1 revisions
*/

#include "stdafx.h"
#include "SBrushCache.hpp"
#include "Pencil.h" // [01]
#include "SPencil2.h" // [01]
#include "SColourTable.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SBrushCache* SBrushCache::sm_Instance = 0;

SBrushCache::~SBrushCache ()
{
    int Size = m_Pens.GetSize ();

    for (int i = 0; i < Size; i++)
    {
        if (m_Pens[i].m_Pen)
            delete m_Pens[i].m_Pen;
        //if
    }//for

    Size = m_Brushes.GetSize ();

    for (i = 0; i < Size; i++)
    {
        if (m_Brushes[i].m_Brush)
            delete m_Brushes[i].m_Brush;
        //if
    }//for

    Size = m_Fonts.GetSize ();

    for (i = 0; i < Size; i++)
    {
        if (m_Fonts[i].m_Font)
            delete m_Fonts[i].m_Font;
        //if
    }//for
}//SBrushCache::~SBrushCache

void SBrushCache::Destroy ()
{
    if (sm_Instance)
    {
        delete sm_Instance;
        sm_Instance = 0;
    }//if

//    LEAVE NOW
}//SBrushCache::Destroy

SBrushCache* SBrushCache::Instance ()
{
    if (!sm_Instance)
        sm_Instance = new SBrushCache;
    //if

    return sm_Instance;
}//SBrushCache::Instance

void SBrushCache::RemapColours ()
{
    for (int i = 0; i < m_Brushes.GetSize (); i++)
    {
        m_Brushes[i].m_Brush->DeleteObject ();
        m_Brushes[i].m_Brush->CreateSolidBrush (m_Brushes[i].m_Colour.GetColourRef ());
    }//for

    for (i = 0; i < m_Pens.GetSize (); i++)
    {
        m_Pens[i].m_Pen->DeleteObject ();
        m_Pens[i].m_Pen->CreatePen (PS_SOLID,m_Pens[i].m_Width,m_Pens[i].m_Colour.GetColourRef ());
    }//for
}//SBrushCache::RemapColours

CPen* SBrushCache::GetPen
(
    int                Width,
    const SColour&    Colour,
    int                LineStyle
)
{
    for (int i = 0; i < m_Pens.GetSize (); i++)
    {
        if ((m_Pens[i].m_Width == Width)
         && (m_Pens[i].m_Colour == Colour)
         && (m_Pens[i].m_LineStyle == LineStyle))
            return m_Pens[i].m_Pen;
        //if
    }//for

    SPenEntry NewPen;

    NewPen.m_Colour    = Colour;
    NewPen.m_Width       = Width;
    NewPen.m_LineStyle = LineStyle;
    NewPen.m_Pen    = new CPen (LineStyle,Width,Colour.GetColourRef ());

    m_Pens.Add (NewPen);

    return NewPen.m_Pen;
}//SBrushCache::GetPen

CBrush* SBrushCache::GetBrush
(
    const SColour& Colour
)
{
    for (int i = 0; i < m_Brushes.GetSize (); i++)
    {
        if (m_Brushes[i].m_Colour == Colour)
            return m_Brushes[i].m_Brush;
        //if
    }//for

    SBrushEntry NewBrush;

    NewBrush.m_Colour = Colour;
    NewBrush.m_Brush  = new CBrush (Colour.GetColourRef ());

    m_Brushes.Add (NewBrush);

    return NewBrush.m_Brush;
}//SBrushCache::GetBrush

CFont* SBrushCache::GetFont
(
    int                PointSize,
    const CString&    Typeface,
    int                TextStyle
)
{
    for (int i = 0; i < m_Fonts.GetSize (); i++)
    {
        if ((m_Fonts[i].m_PointSize == PointSize)
         && (m_Fonts[i].m_Typeface  == Typeface)
         && (m_Fonts[i].m_TextStyle == TextStyle))
            return m_Fonts[i].m_Font;
        //if
    }//for

    SFontEntry NewFont;

    NewFont.m_PointSize = PointSize;
    NewFont.m_Typeface  = Typeface;
    NewFont.m_TextStyle = TextStyle;

    CDC DisplayDC;
    DisplayDC.CreateCompatibleDC (0);

    int Height = -((DisplayDC.GetDeviceCaps (LOGPIXELSY) * PointSize)/72);

    if (Height == 0)
        Height = -1;
    //if

    bool Bold = TextStyle & SPencil2::T_BOLD;           // [01]
    bool Ital = TextStyle & SPencil2::T_ITALIC;         // [01]
    bool Unde = TextStyle & SPencil2::T_UNDERSCORE;     // [01]
    bool Stri = TextStyle & SPencil2::T_STRIKETHROUGH;  // [01]

    NewFont.m_Font = new CFont ();
    NewFont.m_Font->CreateFont (Height,0,0,0,Bold?FW_BOLD:FW_NORMAL,Ital,Unde,Stri,
                                DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
                                DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,
                                Typeface);

    m_Fonts.Add (NewFont);

    return NewFont.m_Font;
}//SBrushCache::GetFont



