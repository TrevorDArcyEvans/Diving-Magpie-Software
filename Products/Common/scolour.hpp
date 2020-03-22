/*
History:
    TODO    to be removed towards the end of stage 1 changes
*/

#ifndef _SColour_hpp
#define _SColour_hpp

#include "SColourTable.hpp"

class CArchive;

class SColour
{
private:

	long	m_Value;		// Either a COLORREF or index into the table
	BOOL	m_UseTable;
	BOOL	m_Transparent;

public:

	SColour ();
	SColour (const SColour& RVal);
	virtual ~SColour () {}

	COLORREF GetColourRef () const;
	COLORREF GetColourRef (int HiLiteLevel) const;

	void SetColorRef (COLORREF Ref);
	void SetIndex	 (SColourTable::ColourEnums Index);
	void SetIndex    (int Index);

	const BOOL& Transparent () const {return m_Transparent;}
	void SetTransparent (BOOL Transparent) {m_Transparent = Transparent;}

	void Serialize (CArchive& ar);

	bool operator == (const SColour& RVal) const;
	bool operator != (const SColour& RVal) const;

	const SColour& operator = (const SColour& RVal);
};//SColour

#endif

