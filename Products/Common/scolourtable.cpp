/*
History:
    [01]    TDE     26May00     added more debugging code
*/

#include "stdafx.h"
#include "SColourTable.hpp"
#include "SBetterThanMFC.hpp"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL (SColourTableEntry,CObject,1)

SColourTable*	SColourTable::sm_Instance = 0;
CString			SColourTable::sm_Path;

COLORREF SColourTableEntry::ColourRef 
(
	int HiLight
)const 
{
	if (HiLight == 0)
		return m_ColourRef;
	else
		return HighlightValue (m_ColourRef,HiLight);
	//if
}//SColourTableEntry::ColourRef

COLORREF SColourTableEntry::HighlightValue
(
	COLORREF	Base,
	int			Level
)
{
	if (Level == 0)
		return Base;
	//if

	int R = GetRValue (Base);
	int G = GetGValue (Base);
	int B = GetBValue (Base);

	int Grey = (R + G + B)/3;

	switch (Level)
	{
		default:
		case 1: return RGB (Grey,Grey,Grey);
		case 2: return RGB (R + (255 - R)/2,G + (255 - G)/2,B + (255 - B)/2);
	}//switch
}//SColourTableEntry::HighlightValue

COLORREF SColourTableEntry::HLS 
(
	double	H,
	double	L,
	double	S
)
{
	double R;
	double G;
	double B;

	double m2;

//	H *= 360.0/ 6.28318530718;

	if (L <= 0.5) 
		m2 = L * (1.0 + S);
	else
		m2 = L + S - (L * S);
	//if

	double m1 = (2.0 * L) - m2;

	if (S <= 0.00000000001)
		R = G = B = L;
	else
	{
		R = Val (m1,m2,H + 0.33333);
		G = Val (m1,m2,H);
		B = Val (m1,m2,H - 0.33333);
	}//if

	return RGB (255 * R,255 * G,255 * B);
}//SColourTableEntry::HLS 

double SColourTableEntry::Val
(
	double n1,
	double n2,
	double h
)
{
	if (h < 0.0)
		h += 1.0;
	else if (h > 1.0)
		h -= 1.0;
	//if

	if (h < (1.0/6.0))
		return n1 + ((n2 - n1) * h * 6.0);
	else if (h < 0.5)
		return n2;
	else if (h < 0.666666)
		return n1 + ((n2 - n1) * (0.66666 - h) * 6.0);
	else
		return n1;
	//if
}//SColourTableEntry::Val

SColourTableEntry::SColourTableEntry ()
:m_ColourRef (0),
 m_NoDirectEdit (false)
{
}//SColourTableEntry::SColourTableEntry

void SColourTableEntry::SetHLS 
(
	double h,
	double l,
	double s
)
{
	m_ColourRef = HLS (h,l,s);
}//SColourTableEntry::SetHLS

void SColourTableEntry::SetRGB 
(
	unsigned char r,
	unsigned char g,
	unsigned char b
)
{
	m_ColourRef = RGB (r,g,b);
}//SColourTableEntry::SetRGB

void SColourTableEntry::Serialize 
(
	CArchive& Ar
)
{
	if (Ar.IsStoring ())
	{
		Ar << m_ColourRef;
		Ar << m_Name;
		Ar << m_NoDirectEdit;
	}
	else
	{
		Ar >> m_ColourRef;
		Ar >> m_Name;
		Ar >> m_NoDirectEdit;
	}//if
}//SColourTableEntry::Serialize

SColourTable::SColourTable 
(
	const CString& TableName
)
:m_TableName (TableName)
{
	if (TableName == "")
		m_TableName = "DefaultColourTable";
	else
		m_TableName = TableName;
	//if

	Load ();

	if (GetSize () == 0)
	{
		GetAt (COLOUR_COASTLINE).SetHLS (0.288,0.683,0.1);
		GetAt (COLOUR_CONTOUR_1).SetHLS (0.076,0.605,0.357);
		GetAt (COLOUR_CONTOUR_2).SetHLS (0.076,0.505,0.357);
		GetAt (COLOUR_CONTOUR_3).SetHLS (0.076,0.405,0.357);
		GetAt (COLOUR_CONTOUR_4).SetHLS (0.076,0.305,0.357);
		GetAt (COLOUR_CONTOUR_5).SetHLS (0.638,0.74,0.1);
		GetAt (COLOUR_CONTOUR_6).SetHLS (0.678,0.966,0.088);

		GetAt (COLOUR_BLACK).SetRGB (0,0,0);
		GetAt (COLOUR_WHITE).SetRGB (255,255,255);
		GetAt (COLOUR_RED).SetRGB (255,0,0);
		GetAt (COLOUR_GREEN).SetRGB (0,255,0);
		GetAt (COLOUR_BLUE).SetRGB (0,0,255);
		GetAt (COLOUR_YELLOW).SetRGB (255,255,0);
		GetAt (COLOUR_MAGENTA).SetRGB (255,0,255);
		GetAt (COLOUR_CYAN).SetRGB (0,255,255);
		GetAt (PASTEL_RED).SetRGB (255,127,127);
		GetAt (PASTEL_GREEN).SetRGB (127,255,127);
		GetAt (PASTEL_BLUE).SetRGB (127,127,255);
		GetAt (DARK_RED).SetRGB (127,0,0);
		GetAt (DARK_GREEN).SetRGB (0,127,0);
		GetAt (DARK_BLUE).SetRGB (0,0,127);
		GetAt (DARK_YELLOW).SetRGB (127,127,0);
		GetAt (DARK_CYAN).SetRGB (127,0,127);
		GetAt (DARK_MAGENTA).SetRGB (0,127,127);
		GetAt (COLOUR_ORANGE).SetRGB (255,127,0);
		GetAt (STATE_RED).SetRGB (255,0,0);
		GetAt (STATE_AMB).SetRGB (255,150,0);
		GetAt (STATE_YLO).SetRGB (255,255,0);
		GetAt (STATE_GRN).SetRGB (0,255,0);
		GetAt (STATE_WHT).SetRGB (255,255,255);
		GetAt (STATE_BLU).SetRGB (0,0,255);

		GetAt (COLOUR_BLACK).Name () = "Black";
		GetAt (COLOUR_WHITE).Name () = "White";
		GetAt (COLOUR_RED).Name () = "Red";
		GetAt (COLOUR_GREEN).Name () = "Green";
		GetAt (COLOUR_BLUE).Name () = "Blue";
		GetAt (COLOUR_CYAN).Name () = "Cyan";
		GetAt (COLOUR_MAGENTA).Name () = "Magenta";
		GetAt (COLOUR_YELLOW).Name () = "Yellow";
		GetAt (COLOUR_ORANGE).Name () = "Orange";
		GetAt (PASTEL_RED).Name () = "PastelRed";
		GetAt (PASTEL_GREEN).Name () = "PastelGreen";
		GetAt (PASTEL_BLUE).Name () = "PastelBlue";
		GetAt (DARK_RED).Name () = "DarkRed";
		GetAt (DARK_GREEN).Name () = "DarkGreen";
		GetAt (DARK_BLUE).Name () = "DarkBlue";
		GetAt (DARK_CYAN).Name () = "DarkCyan";
		GetAt (DARK_MAGENTA).Name () = "DarkMagenta";
		GetAt (DARK_YELLOW).Name () = "DarkYellow";
		GetAt (DARK_GREY).Name () = "DarkGrey";
		GetAt (MID_GREY).Name () = "MidGrey";
		GetAt (LIGHT_GREY).Name () = "LightGrey";
		GetAt (COLOUR_OCEAN).Name () = "Ocean";
		GetAt (COLOUR_COASTLINE).Name () = "Coastline";
		GetAt (COLOUR_CONTOUR_1).Name () = "1000Feet";
		GetAt (COLOUR_CONTOUR_2).Name () = "2000Feet";
		GetAt (COLOUR_CONTOUR_3).Name () = "3000Feet";
		GetAt (COLOUR_CONTOUR_4).Name () = "4000Feet";
		GetAt (COLOUR_CONTOUR_5).Name () = "5000Feet";
		GetAt (COLOUR_CONTOUR_6).Name () = "6000Feet";
		GetAt (COLOUR_CONTOUR_7).Name () = "7000Feet";
		GetAt (COLOUR_CONTOUR_8).Name () = "8000Feet";
		GetAt (COLOUR_CONTOUR_9).Name () = "9000Feet";
		GetAt (COLOUR_CONTOUR_10).Name () = "10000Feet";
		GetAt (COLOUR_CONTOUR_11).Name () = "11000Feet";
		GetAt (COLOUR_CONTOUR_12).Name () = "12000Feet";
		GetAt (COLOUR_CONTOUR_13).Name () = "13000Feet";
		GetAt (COLOUR_CONTOUR_14).Name () = "14000Feet";
		GetAt (COLOUR_CONTOUR_15).Name () = "15000Feet";
		GetAt (COLOUR_CONTOUR_16).Name () = "16000Feet";
		GetAt (COLOUR_CONTOUR_17).Name () = "17000Feet";
		GetAt (COLOUR_CONTOUR_18).Name () = "18000Feet";
		GetAt (COLOUR_RIV_MAJ).Name () = "MajorRivers";
		GetAt (COLOUR_RIV_MIN).Name () = "MinorRivers";
		GetAt (COLOUR_LAKE).Name () = "Lakes";
		GetAt (COLOUR_BORDER_NAT).Name () = "NationalBorders";
		GetAt (COLOUR_BORDER_PRO).Name () = "ProvincialBorders";
		GetAt (STATE_RED).Name () = "RED";
		GetAt (STATE_GRN).Name () = "GRN";
		GetAt (STATE_BLU).Name () = "BLU";
		GetAt (STATE_WHT).Name () = "WHT";
		GetAt (STATE_YLO).Name () = "YLO";
		GetAt (STATE_AMB).Name () = "AMB";
		GetAt (BIRDTAMS_GRID).Name () = "Birdtams Grid";
		GetAt (BIRDTAMS_LABEL).Name () = "Birdtams Grid Labels";
		GetAt (BIRDTAM_CELL_TEXT).Name () = "Birdtams Cell Text";
		GetAt (BIRDTAM_SHADE_1).Name () = "Birdtams Shade Level 1";
		GetAt (BIRDTAM_SHADE_2).Name () = "Birdtams Shade Level 2";
		GetAt (BIRDTAM_SHADE_3).Name () = "Birdtams Shade Level 3";
		GetAt (BIRDTAM_SHADE_4).Name () = "Birdtams Shade Level 4";
		GetAt (BIRDTAM_SHADE_5).Name () = "Birdtams Shade Level 5";
		GetAt (BIRDTAM_SHADE_6).Name () = "Birdtams Shade Level 6";
		GetAt (BIRDTAM_SHADE_7).Name () = "Birdtams Shade Level 7";
		GetAt (BIRDTAM_SHADE_8).Name () = "Birdtams Shade Level 8";
		GetAt (BIRDTAM_TEXT_BACK).Name () = "Birdtams Text Background";
		GetAt (COLOUR_LL_GRID).Name () = "Lat/Long Grid";
		GetAt (COLOUR_LL_LABEL).Name () = "Lat/Long Labels";

		GetAt (STATE_RED).NoDirectEdit () = true;
		GetAt (STATE_GRN).NoDirectEdit () = true;
		GetAt (STATE_BLU).NoDirectEdit () = true;
		GetAt (STATE_WHT).NoDirectEdit () = true;
		GetAt (STATE_YLO).NoDirectEdit () = true;
		GetAt (STATE_AMB).NoDirectEdit () = true;

		GetAt (COLOUR_FREE_BASE).Name () = "";

		Save ();
	}//if
}//SColourTable::SColourTable

SColourTable::~SColourTable ()
{
	for (int i = 0; i < m_Colours.GetSize (); i++)
		delete m_Colours[i];
	//for
}//SColourTable::~SColourTable

void SColourTable::Extend 
(
	int Idx
)
{
	if (Idx >= m_Colours.GetSize ())
	{
		int Start = m_Colours.GetSize ();

		m_Colours.SetSize (Idx + 1);

		for (int i = Start; i < m_Colours.GetSize (); i++)
			m_Colours[i] = new SColourTableEntry;
		//for
	}//if
}//SColourTable::Extend

int SColourTable::GetNewColour 
(
	COLORREF Ref,
	const CString& Name
)
{
	int RetVal = m_Colours.GetSize ();

	SColourTableEntry& Entry = GetAt (RetVal);

	Entry.ColourRef () = Ref;
	Entry.Name ()	   = Name;

	return RetVal;
}//SColourTable::GetNewColour

const SColourTableEntry& SColourTable::GetAt 
(
	int Idx
)const
{
	((SColourTable*)this)->Extend (Idx);

	return *((SColourTableEntry*)m_Colours[Idx]);
}//SColourTable::GetAt

SColourTableEntry& SColourTable::GetAt 
(
	int Idx
)
{
	Extend (Idx);

	return *((SColourTableEntry*)m_Colours[Idx]);
}//SColourTable::GetAt

const SColourTableEntry& SColourTable::GetAt 
(
	ColourEnums Idx
)const
{
	return GetAt ((int)Idx);
}//SColourTable::GetAt

SColourTableEntry& SColourTable::GetAt 
(
	ColourEnums Idx
)
{
	return GetAt ((int)Idx);
}//SColourTable::GetAt

void SColourTable::Destroy ()
{
	if (sm_Instance)
	{
		delete sm_Instance;
		sm_Instance = 0;
	}//if
//	LEAVE NOW
}//SColourTable::Destroy

SColourTable* SColourTable::Instance 
(
	const CString& TableName
)
{
	if (TableName == "")
	{
		if (!sm_Instance)
		{
			sm_Instance = new SColourTable ("DefaultColourTable");
		}//if
	}
	else
	{
		if (!sm_Instance)
			sm_Instance = new SColourTable (TableName);
		else if (sm_Instance->TableName () != TableName)
		{
			delete sm_Instance;
			sm_Instance = new SColourTable (TableName);
		}//if
	}//if

	return sm_Instance;
}//SColourTable::Instance

void SColourTable::Save () const
{
	SColourTable* Self = (SColourTable*)this;

	CFile OutFile;

	OutFile.Open (sm_Path^m_TableName + ".ctb",CFile::modeCreate|CFile::modeWrite);

	CArchive Arc (&OutFile,CArchive::store);

	Self->m_Colours.Serialize (Arc); 
}//SColourTable::Save

void SColourTable::Load ()
{
	CFile InFile;

	for (int i = 0; i < m_Colours.GetSize (); i++)
		delete m_Colours[i];
	//for

	if (InFile.Open (sm_Path ^ m_TableName + ".ctb",CFile::modeRead))
	{
		CArchive Arc (&InFile,CArchive::load);
		m_Colours.Serialize (Arc);
	}//if
}//SColourTable::Load

bool SColourTable::Readonly () const
{
	CFile InFile;

	bool Readable = InFile.Open (sm_Path ^ m_TableName + ".ctb",CFile::modeRead);

	if (!Readable)
		return false;
	else
	{
		InFile.Close ();
		return !InFile.Open (sm_Path ^ m_TableName + ".ctb",CFile::modeWrite);
	}//if
}//SColourTable::Readonly

void SColourTable::GetAllTableNames 
(
	CStringArray& Names
)
{
	Names.RemoveAll ();

	CFileFind		Finder;

	BOOL NotDone = Finder.FindFile (sm_Path ^ "*.ctb");

	while (NotDone)
	{
		NotDone = Finder.FindNextFile ();

		CString Name = Finder.GetFileName ();

		Names.Add (Name.Left (Name.GetLength ()- 4));
	}//while
}//SColourTable::GetAllTableNames

bool SColourTable::SchemeExists 
(
	const CString& Table
)
{
	CFileFind		Finder;
 
	return Finder.FindFile (sm_Path ^ Table + ".ctb");
}//SColourTable::SchemeExists

void SColourTable::DeleteTable 
(
	const CString Table
)
{
	try
	{
		CFile::Remove (sm_Path ^ Table + ".ctb");
	}
	catch (CFileException* e)
	{
		e->Delete ();
	}
	catch (...)
	{
        ASSERT (FALSE);     // [01]
	}//try
}//SColourTable::DeleteTable
