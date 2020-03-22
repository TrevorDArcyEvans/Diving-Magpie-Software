#ifndef __SColourTable_hpp
#define __SColourTable_hpp

#include <afx.h>

class SColourTableEntry:public CObject
{
DECLARE_SERIAL (SColourTableEntry)

private:

	COLORREF	m_ColourRef;
	CString		m_Name;
	BOOL		m_NoDirectEdit;


public:

	SColourTableEntry ();
	virtual ~SColourTableEntry () {}

	COLORREF ColourRef (int HiLight = 0) const;
	COLORREF& ColourRef () {return m_ColourRef;}

	static COLORREF HighlightValue (COLORREF Base,int Level);

	const CString& Name () const {return m_Name;}
	CString& Name () {return m_Name;}

	void SetHLS (double h,double l,double s);
	void SetRGB (unsigned char r,unsigned char g,unsigned char b);

	void Serialize (CArchive& Ar);

	BOOL NoDirectEdit () const {return m_NoDirectEdit;}
	BOOL& NoDirectEdit () {return m_NoDirectEdit;}

	static COLORREF HLS (double	H,double L,double S);
	static double Val (double n1,double n2,double h);
};//SColourTableEntry

class SColourTable
{
public:

	enum ColourEnums {COLOUR_BLACK		= 0,
					  COLOUR_WHITE		= 1,
					  COLOUR_RED		= 2,
					  COLOUR_GREEN		= 3,
					  COLOUR_BLUE		= 4,
					  COLOUR_CYAN		= 5,
					  COLOUR_MAGENTA	= 6,
					  COLOUR_YELLOW		= 7,
					  COLOUR_ORANGE		= 8,
					  PASTEL_RED		= 9,
					  PASTEL_GREEN		= 10,
					  PASTEL_BLUE		= 11,
					  DARK_RED			= 12,
					  DARK_GREEN		= 13,
					  DARK_BLUE			= 14,
					  DARK_CYAN			= 15,
					  DARK_MAGENTA		= 16,
					  DARK_YELLOW		= 17,
					  DARK_GREY			= 18,
					  MID_GREY			= 19,
					  LIGHT_GREY		= 20,
					  COLOUR_OCEAN		= 21,
					  COLOUR_COASTLINE	= 22,
					  COLOUR_CONTOUR_1	= 23,
					  COLOUR_CONTOUR_2	= 24,
					  COLOUR_CONTOUR_3	= 25,
					  COLOUR_CONTOUR_4	= 26,
					  COLOUR_CONTOUR_5	= 27,
					  COLOUR_CONTOUR_6	= 28,
					  COLOUR_CONTOUR_7	= 29,
					  COLOUR_CONTOUR_8	= 30,
					  COLOUR_CONTOUR_9	= 31,
					  COLOUR_CONTOUR_10	= 32,
					  COLOUR_CONTOUR_11	= 33,
					  COLOUR_CONTOUR_12	= 34,
					  COLOUR_CONTOUR_13	= 35,
					  COLOUR_CONTOUR_14	= 36,
					  COLOUR_CONTOUR_15	= 37,
					  COLOUR_CONTOUR_16	= 38,
					  COLOUR_CONTOUR_17	= 39,
					  COLOUR_CONTOUR_18	= 40,
					  COLOUR_RIV_MAJ	= 41,
					  COLOUR_RIV_MIN	= 42,
					  COLOUR_LAKE		= 43,
					  COLOUR_BORDER_NAT	= 44,
					  COLOUR_BORDER_PRO	= 45,
					  STATE_RED			= 46,
					  STATE_GRN			= 47,
					  STATE_BLU			= 48,
					  STATE_WHT			= 49,
					  STATE_YLO			= 50,
					  STATE_AMB			= 51,
					  BIRDTAMS_GRID		= 52,
					  BIRDTAMS_LABEL	= 53,
					  BIRDTAM_CELL_TEXT	= 54,
					  BIRDTAM_SHADE_1	= 55,
					  BIRDTAM_SHADE_2	= 56,
					  BIRDTAM_SHADE_3	= 57,
					  BIRDTAM_SHADE_4	= 58,
					  BIRDTAM_SHADE_5	= 59,
					  BIRDTAM_SHADE_6	= 60,
					  BIRDTAM_SHADE_7	= 61,
					  BIRDTAM_SHADE_8	= 62,
					  BIRDTAM_TEXT_BACK = 63,
					  COLOUR_LL_GRID	= 64,
					  COLOUR_LL_LABEL	= 65,
					  WIND_ARROWS		= 66,
					  COLOUR_FREE_BASE  = 100};

	static bool IsFixedIndex (ColourEnums Idx) {return Idx <= WIND_ARROWS;}

private:

	CObArray		m_Colours;

	CString			m_TableName;
	static CString	sm_Path;

	void Extend (int Idx);

protected:

	static SColourTable*	sm_Instance;

public:

	SColourTable (const CString& TableName = "");
	virtual ~SColourTable ();

	static void SetPath (const CString& Path) {sm_Path = Path;}

	static SColourTable* Instance (const CString& TableName = "");

	static void Destroy ();

	bool Readonly () const;

	const CString& TableName () const {return m_TableName;}
	CString& TableName () {return m_TableName;}
	
	int GetSize () const {return m_Colours.GetSize ();}

	const SColourTableEntry& GetAt (int Idx) const;
	SColourTableEntry& GetAt (int Idx);

	const SColourTableEntry& GetAt (ColourEnums Idx) const;
	SColourTableEntry& GetAt (ColourEnums Idx);

	const SColourTableEntry& operator [] (int Idx) const {return GetAt (Idx);}
	SColourTableEntry& operator [] (int Idx) {return GetAt (Idx);}

	const SColourTableEntry& operator [] (ColourEnums Idx) const {return GetAt (Idx);}
	SColourTableEntry& operator [] (ColourEnums Idx) {return GetAt (Idx);}

	int GetNewColour (COLORREF Ref,const CString& Name = "");

	static void GetAllTableNames (CStringArray& Names);
	static bool SchemeExists (const CString& Table);
	static void DeleteTable (const CString Table);

	void Save () const;
	void Load ();
};//SColourTable

#endif
