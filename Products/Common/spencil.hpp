#ifndef __SPencil_hpp
#define __SPencil_hpp

#include <afx.h>
#include <afxwin.h>	
#include "SColour.hpp"
#include "SDCCheats.hpp"

class SPencil:public CObject
{
DECLARE_SERIAL (SPencil)

public:

	enum ETextStyles {T_NONE = 0,T_BOLD = 1,T_ITALIC = 2,T_UNDERSCORE = 4,T_STRIKETHROUGH = 8};
private:

	mutable CPen*		m_CachedPen;
	mutable CBrush*		m_CachedBrush;
	mutable	CFont*		m_CachedFont;

protected:

	SColour			m_BackColour;
	SColour			m_Colour;
	int				m_Width;
	int				m_LineStyle;
	int				m_Opacity;
	int				m_TextStyle;

	int				m_PointSize;
	CString			m_Typeface;
	unsigned		m_TextAlign;
	BOOL			m_CentreVert;

	void Invalidate ();

public:

	SPencil ();
	SPencil (const SPencil& RVal);
	virtual ~SPencil ();

	SPencil* Clone () const;

	SPencil& operator = (const SPencil& RVal);
	bool operator != (const SPencil& RVal) const;

	void Serialize (CArchive& Archive);

	SColour& GetColour () {Invalidate (); return m_Colour;}
	const SColour& GetColour () const {return m_Colour;}

	int& Width () {Invalidate (); return m_Width;}
	const int& Width () const {return m_Width;}

	int& LineStyle () {Invalidate (); return m_LineStyle;}
	const int& LineStyle () const {return m_LineStyle;}

	const int& Opacity () const {return m_Opacity;}
	int& Opacity () {return m_Opacity;}

	SColour& BackColour () {Invalidate (); return m_BackColour;}
	const SColour& BackColour () const {return m_BackColour;}

	int& PointSize () {Invalidate (); return m_PointSize;}
	const int& PointSize () const {return m_PointSize;}

	CString& Typeface () {Invalidate (); return m_Typeface;}
	const CString& Typeface () const {return m_Typeface;}

	unsigned TextAlign () const {return m_TextAlign;}

	void SetTextAlign (unsigned Align,bool CentreVert = false);

	bool CentreVert () const {return m_CentreVert;}

	int GetTextStyle () const {return m_TextStyle;}
	void SetTextStyle (int Style) {m_TextStyle = Style;}

	bool Bold () const {return m_TextStyle & T_BOLD;}
	bool Italic () const {return m_TextStyle & T_ITALIC;}
	bool Underscore () const {return m_TextStyle & T_UNDERSCORE;}
	bool StrikeThrough () const {return m_TextStyle & T_STRIKETHROUGH;}

	void SetBold (bool On) {SetTextStyle (T_BOLD,On);}
	void SetItalic (bool On) {SetTextStyle (T_ITALIC,On);}
	void SetUnderscore (bool On) {SetTextStyle (T_UNDERSCORE,On);}
	void SetStrikeThrough (bool On) {SetTextStyle (T_STRIKETHROUGH,On);}

	void SetTextStyle (ETextStyles Style,bool On);

	CPen&	Pen	  () const;
	CBrush& Brush () const;
	CFont&  Font  () const;

	SDCCheats ApplyToDC (CDC& DC,bool Line = true,bool Fill = true,bool Text = true,int HighlightLevel = 0) const;

	static void ColourTableChanged ();
};//SPencil

#endif

