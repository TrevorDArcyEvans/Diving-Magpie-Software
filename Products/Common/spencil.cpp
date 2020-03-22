#include "stdafx.h"
#include "SPencil.hpp"
#include "SBrushCache.hpp"
#include "SException.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL (SPencil,CObject,1)

SPencil::SPencil ()
:m_Width			(0),
 m_CachedPen		(0),
 m_CachedBrush		(0),
 m_CachedFont		(0),
 m_PointSize		(8),
 m_Typeface			("MS Sans Serif"),
 m_TextAlign		(TA_CENTER|TA_BOTTOM),
 m_CentreVert		(false),
 m_Opacity			(100),
 m_LineStyle		(PS_SOLID),
 m_TextStyle		(0)
{
	m_BackColour.SetTransparent (TRUE);
}//SPencil::SPencil

SPencil::SPencil 
(
	const SPencil& RVal
)
:m_Colour			(RVal.m_Colour),
 m_Width			(RVal.m_Width),
 m_CachedPen		(0),
 m_CachedBrush		(0),
 m_CachedFont		(0),
 m_BackColour		(RVal.m_BackColour),
 m_PointSize		(RVal.m_PointSize),
 m_Typeface			(RVal.m_Typeface),
 m_TextAlign		(RVal.m_TextAlign),
 m_CentreVert		(RVal.m_CentreVert),
 m_Opacity			(RVal.m_Opacity),
 m_LineStyle		(RVal.m_LineStyle),
 m_TextStyle		(RVal.m_TextStyle)
{
}//SPencil::SPencil

SPencil::~SPencil ()
{
	Invalidate ();
}//SPencil::~SPencil

SPencil* SPencil::Clone () const
{
	return new SPencil (*this);
}//SPencil::Clone

void SPencil::ColourTableChanged ()
{
	throw new SException ("Colour table change needs reimplementing.");
}//SPencil::ColourTableChanged

SPencil& SPencil::operator = 
(
	const SPencil& RVal
)
{
	m_Colour     = RVal.m_Colour;
	m_Width      = RVal.m_Width;
	m_BackColour = RVal.m_BackColour;
	m_PointSize	 = RVal.m_PointSize;
	m_Typeface	 = RVal.m_Typeface;
	m_TextAlign	 = RVal.m_TextAlign;
	m_CentreVert = RVal.m_CentreVert;
	m_Opacity	 = RVal.m_Opacity;
	m_LineStyle	 = RVal.m_LineStyle;
	m_TextStyle	 = RVal.m_TextStyle;

	Invalidate ();

	return *this;
}//SPencil::operator = 

bool SPencil::operator != 
(
	const SPencil& RVal
)const
{
	return	m_Colour     != RVal.m_Colour ||
			m_Width      != RVal.m_Width ||
			m_BackColour != RVal.m_BackColour ||
			m_PointSize	 != RVal.m_PointSize ||
			m_Typeface	 != RVal.m_Typeface ||
			m_TextAlign	 != RVal.m_TextAlign ||
			m_CentreVert != RVal.m_CentreVert ||
			m_Opacity	 != RVal.m_Opacity ||
			m_LineStyle	 != RVal.m_LineStyle;
}//SPencil::operator != 

void SPencil::Serialize 
(
	CArchive& Archive
)
{
	m_Colour.Serialize (Archive);
	m_BackColour.Serialize (Archive);

	if (Archive.IsStoring ())
		Archive << m_Width
				<< m_LineStyle
				<< m_Opacity
				<< m_TextStyle
				<< m_PointSize
				<< m_Typeface
				<< m_TextAlign
				<< m_CentreVert;
	else
	{
		Archive >> m_Width
				>> m_LineStyle
				>> m_Opacity
				>> m_TextStyle
				>> m_PointSize
				>> m_Typeface
				>> m_TextAlign
				>> m_CentreVert;
		Invalidate ();
	}//if
}//SPencil::Serialize

void SPencil::Invalidate ()
{
	if (m_CachedPen)
	{
		m_CachedPen = 0;
	}//if

	if (m_CachedBrush)
	{
		m_CachedBrush = 0;
	}//if

	if (m_CachedFont)
	{
		m_CachedFont = 0;
	}//if
}//SPencil::Invalidate

SDCCheats SPencil::ApplyToDC 
(
	CDC& DC,
	bool Line,
	bool Fill,
	bool Text,
	int	 HighlightLevel
)const
{
	SDCCheats RetVal;

	RetVal.m_DC = &DC;

	if (Text)
	{
		if (BackColour ().Transparent ())
			DC.SetBkMode (TRANSPARENT);
		else
		{
			DC.SetBkMode (OPAQUE);
			DC.SetBkColor (BackColour ().GetColourRef (HighlightLevel));
		}//if

		DC.SetTextColor (GetColour ().GetColourRef (HighlightLevel));
		DC.SelectObject (&Font ());

		DC.SetTextAlign (TextAlign ());

		if (CentreVert ())
		{
			TEXTMETRIC Met;

			DC.GetTextMetrics (&Met);

			RetVal.m_YOffset = Met.tmAscent/2; 
		}//if
	}//if

	if (Line || Fill)
		DC.SelectObject (&Pen ());
	//if

	if (Fill)
		DC.SelectObject (&Brush ());
	//if

	return RetVal;
}//SPencil::ApplyToDC

CPen& SPencil::Pen () const
{
	if (!m_CachedPen)
		m_CachedPen = SBrushCache::Instance ()->GetPen (m_Width,m_Colour,m_LineStyle);
	//if

	return *m_CachedPen;
}//SPencil::Pen

CBrush& SPencil::Brush () const
{
	if (!m_CachedBrush)
		m_CachedBrush = SBrushCache::Instance ()->GetBrush (m_Colour);
	//if

	return *m_CachedBrush;
}//SPencil::Brush

CFont& SPencil::Font () const
{
	if (!m_CachedFont)
		m_CachedFont = SBrushCache::Instance ()->GetFont (m_PointSize,m_Typeface,m_TextStyle);
	//if

	return *m_CachedFont;
}//SPencil::Font

void SPencil::SetTextAlign 
(
	unsigned	Align,
	bool		CentreVert
)
{
	m_TextAlign = Align;
	
	if (CentreVert)
		m_TextAlign |= TA_BOTTOM;
	//if

	m_CentreVert = CentreVert;
}//SPencil::SetTextAlign

void SPencil::SetTextStyle 
(
	ETextStyles Style,
	bool		On
)
{
	if (On)
		m_TextStyle |= Style;
	else
		m_TextStyle &= ~Style;
	//if
}//SPencil::SetTextStyle
