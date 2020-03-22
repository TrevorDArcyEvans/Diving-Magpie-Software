/*
History:
    TODO    to be removed towards the end of stage 1 changes
*/

#include "stdafx.h"
#include "SColour.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SColour::SColour ()
:m_Value		(RGB (0,0,0)),
 m_UseTable		(FALSE),
 m_Transparent	(FALSE)
{
}//SColour::SColour

SColour::SColour 
(
	const SColour& RVal
)
:m_UseTable		(RVal.m_UseTable),
 m_Value		(RVal.m_Value),
 m_Transparent	(RVal.m_Transparent)
{
}//SColour::SColour

COLORREF SColour::GetColourRef () const
{
	if (m_Transparent)
		return RGB (0,0,0);
	else if (m_UseTable)
		return SColourTable::Instance ()->GetAt (m_Value).ColourRef ();
	else
		return (COLORREF)m_Value;
	//if
}//SColour::GetColourRef

COLORREF SColour::GetColourRef 
(
	int HiLiteLevel
)const
{
	if (m_Transparent)
		return RGB (0,0,0);
	else if (m_UseTable)
		return SColourTable::Instance ()->GetAt (m_Value).ColourRef (HiLiteLevel);
	else if (HiLiteLevel > 0)
		return SColourTableEntry::HighlightValue ((COLORREF)m_Value,HiLiteLevel);
	else
		return (COLORREF)m_Value;
	//if
}//SColour::GetColourRef

void SColour::SetColorRef
(
	COLORREF Ref
)
{
	m_Value			= (long)Ref;
	m_UseTable		= FALSE;
	m_Transparent	= FALSE;
}//SColour::Set

void SColour::SetIndex 
(
	SColourTable::ColourEnums Index
)
{
	m_Value			= (long)Index;
	m_UseTable		= TRUE;
	m_Transparent	= FALSE;
}//SColour::SetIndex

void SColour::SetIndex 
(
	int Index
)
{	
	m_Value			= (long)Index;
	m_UseTable		= TRUE;
	m_Transparent	= FALSE;
}//SColour::SetIndex

void SColour::Serialize 
(
	CArchive& ar
)
{
	if (ar.IsStoring ())
	{
		ar << m_Transparent;

		if (!m_Transparent)
		{
			if (m_UseTable)
			{
				if (SColourTable::IsFixedIndex ((SColourTable::ColourEnums)m_Value))
				{
					ar << TRUE;
					ar << m_Value;
				}
				else
				{
					ar << FALSE;
					ar << (long)(SColourTable::Instance ()->GetAt (m_Value).ColourRef ());
				}//if
			}
			else
			{
				ar << FALSE;
				ar << m_Value;
			}//if
		}//if
	}
	else
	{
		ar >> m_Transparent;

		if (!m_Transparent)
		{
			ar >> m_UseTable;
			ar >> m_Value;
		}//if
	}//if
}//SColour::Serialize

bool SColour::operator == 
(
	const SColour& RVal
)const
{
	return (m_Transparent && RVal.m_Transparent) || (GetColourRef () == RVal.GetColourRef ());
}//SColour::operator ==

bool SColour::operator != 
(
	const SColour& RVal
)const
{
	return !(m_Transparent && RVal.m_Transparent) && (GetColourRef () != RVal.GetColourRef ());
}//SColour::operator != 

const SColour& SColour::operator = 
(
	const SColour& RVal
)
{
	m_UseTable		= RVal.m_UseTable;
	m_Value			= RVal.m_Value;
	m_Transparent	= RVal.m_Transparent;

	return *this;
}//SColour& SColour::operator =