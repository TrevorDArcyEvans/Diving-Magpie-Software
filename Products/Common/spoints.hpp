#ifndef __SPoints_hpp
#define __SPoints_hpp

#include <afxtempl.h>
#include "stdafx.h"
#include "SVectors.hpp"
#include "SLongitude.hpp"
#include "SGlobalPoint.hpp"

class SProjection;
class SPosition;

enum BoxCorners {B_TL,B_TR,B_BR,B_BL,BOX_CORNER_SIZE};

// CPoint has a max range of +/- 32000, which sometimes isn't enough

class SLargeRangePoint
{
public:

	long	m_X;
	long	m_Y;

	SLargeRangePoint (int X = 0,int Y = 0):m_X (X),m_Y (Y) {}
};//SLargeRangePoint

class SOffsetPoint
{
public:

	int		m_dX;
	int		m_dY;

	SOffsetPoint (int dX = 0,int dY = 0):m_dX (dX),m_dY (dY) {}
	SOffsetPoint (const CPoint& To,const CPoint& From):m_dX (To.x - From.x),m_dY (To.y - From.y) {}

	void Scale (double Factor) {m_dX *= Factor; m_dY *= Factor;}

	const SOffsetPoint& operator += (const SOffsetPoint& RVal) {m_dX += RVal.m_dX; m_dY += RVal.m_dY; return *this;}

	SOffsetPoint operator * (double Factor) const {return SOffsetPoint (m_dX * Factor, m_dY * Factor);}
};//SOffsetPoint

class SFlatWorldPoint
{
public:

	double	m_X;
	double  m_Y;

	SFlatWorldPoint (double X = 0.0,double Y = 0.0):m_X (X), m_Y (Y) {} 

	double DistanceFrom (const SFlatWorldPoint& RVal) const;

	bool operator == (const SFlatWorldPoint& RVal) const {return (m_X == RVal.m_X) && (m_Y == RVal.m_Y);}
};//SFlatWorldPoint

class SPaperBox
{
protected:

	CPoint	m_TL;
	CPoint	m_BR;

	bool	m_Virgin;

public:

	SPaperBox ():m_Virgin (true) {}
	SPaperBox (const CRect& Rect):m_TL (Rect.TopLeft ()),m_BR (Rect.BottomRight ()),m_Virgin (false) {}
	SPaperBox (int TLX,int TLY,int BRX,int BRY):m_TL (TLX,TLY),m_BR (BRX,BRY),m_Virgin (false) {}
	~SPaperBox () {}

	void Fit (const CPoint&		Point);
	void Fit (const SPaperBox&  Box);
	void Fit (const CRect&		Rect);

	bool Contains (const CPoint&	Point) const;
	bool Overlaps (const SPaperBox& Box) const;

	void Reset ();
	bool Valid () const {return !m_Virgin;}

	int Width  () const;
	int Height () const;

	bool IsUnity () const {return (m_TL.x == m_BR.x) && (m_TL.y == m_BR.y);}

	const CPoint& TL () const {return m_TL;}
	const CPoint& BR () const {return m_BR;}
	CPoint TR () const {return CPoint (m_BR.x,m_TL.y);}
	CPoint BL () const {return CPoint (m_TL.x,m_BR.y);}

	bool Normalize ();

	CRect Rect () const {return CRect (m_TL.x,m_TL.y,m_BR.x,m_BR.y);}
};//SPaperBox

class SFlatWorldBox
{
protected:

	SFlatWorldPoint	m_TL;
	SFlatWorldPoint m_BR;

	bool			m_Virgin;


public:

	SFlatWorldBox (double TLX,double TLY,double BRX,double BRY):m_TL (TLX,TLY),
																m_BR (BRX,BRY),
																m_Virgin (false) {}
	SFlatWorldBox (const SFlatWorldPoint& TL,const SFlatWorldPoint& BR):m_TL (TL),m_BR (BR),m_Virgin (false) {}
	SFlatWorldBox ():m_Virgin (true) {}
	~SFlatWorldBox () {}

	void Fit (const SFlatWorldBox&   Box);
	void Fit (const SFlatWorldPoint& Point);

	bool Contains (const SFlatWorldPoint& Point) const;
	bool Overlaps (const SFlatWorldBox&   Box) const;

	void Reset ();
	bool Valid () const {return !m_Virgin;}

	double Width  () const;
	double Height () const;

	const SFlatWorldPoint& TL () const {return m_TL;}
	const SFlatWorldPoint& BR () const {return m_BR;}
	SFlatWorldPoint TR () const {return SFlatWorldPoint (m_BR.m_X,m_TL.m_Y);}
	SFlatWorldPoint BL () const {return SFlatWorldPoint (m_TL.m_X,m_BR.m_Y);}
	SFlatWorldPoint TopMiddle    () const {return SFlatWorldPoint ((m_TL.m_X + m_BR.m_X)/2,m_TL.m_Y);}
	SFlatWorldPoint BottomMiddle () const {return SFlatWorldPoint ((m_TL.m_X + m_BR.m_X)/2,m_BR.m_Y);}

	SFlatWorldPoint CentrePoint () const {return SFlatWorldPoint ((m_TL.m_X + m_BR.m_X)/2,(m_TL.m_Y + m_BR.m_Y)/2);}

	void Inflate (double Percent);

};//SFlatWorldBox

class SSimpleGlobalBox
{
private:

	enum ELongOrders {O_MYL_MYR_YOL_YOR,
					  O_MYL_MYR_YOR_YOL,
					  O_MYL_YOL_MYR_YOR,
					  O_MYL_YOL_YOR_MYR,
					  O_MYL_YOR_MYR_YOL,
					  O_MYL_YOR_YOL_MYR};

	ELongOrders GetLongOrder (const SLongitudeDelta& MyLMyR,
		                      const SLongitudeDelta& MyLYoL,
							  const SLongitudeDelta& MyLYoR) const;

	bool operator == (const SSimpleGlobalBox& RVal) const;

protected:

	double			m_BottomLat;
	double			m_TopLat;
	SLongitude		m_LeftLong;
	SLongitude		m_RightLong;

	bool			m_CoversNP;
	bool			m_CoversSP;
	bool			m_CoversAllLong;

	bool			m_Virgin;

public:

	SSimpleGlobalBox ():m_Virgin (true),m_CoversNP (false),m_CoversSP (false),m_CoversAllLong (false),m_TopLat (-91.0),m_BottomLat (91.0) {}
	virtual ~SSimpleGlobalBox () {}

	void SetNPCover (double MinLat);
	void SetSPCover (double MaxLat);
	void SetAllLongCover (double MinLat,double MaxLat);

	void SetFlat (double MinLat,double MaxLat,double LeftLong,double RightLong);

	void Fit (const SGlobalPoint& Point);
	void Fit (const SGlobalPoint& PointA,const SGlobalPoint& PointB);
	void Fit (const SSimpleGlobalBox&   Box);

	bool Contains			(const SGlobalPoint& Point) const;
	bool Overlaps			(const SSimpleGlobalBox&   Box) const;
	bool EntirelyContains	(const SSimpleGlobalBox&   Box) const;
	bool IncludesMeridian	(const SLongitude&	 Long,bool Inclusive = false) const;

	bool TouchesRight		(const SLongitude& Long) const;
	bool TouchesLeft		(const SLongitude& Long) const;

	bool CoversAllLong () const {return m_CoversAllLong;}

	const SLongitude& LeftLong () const {return m_LeftLong;}
	const SLongitude& RightLong () const {return m_RightLong;}
	double MinLat () const {return m_CoversSP?-90.0:m_BottomLat;}
	double MaxLat () const {return m_CoversNP?90.0:m_TopLat;}

	void MakeLongContain (const SLongitude& Long);

	void Reset ();
	bool Valid () const {return !m_Virgin;}

	SSimpleGlobalBox& operator = (const SSimpleGlobalBox& RVal);

	void AddBorder (double BorderWidth);

	void FinishOff ();
};//SSimpleGlobalBox

class SPaperPointList
{
protected:

	CUIntArray	m_Breaks;
	CPoint*		m_PointArray;
	int			m_Length;
	int			m_Allocated;

	void Resize (int NewSize);

public:

	SPaperPointList (const SPaperPointList& RVal);
	SPaperPointList ():m_PointArray (0),m_Length (0),m_Allocated (0) {m_Breaks.Add (0);}
	virtual ~SPaperPointList ();

	const CPoint* GetPointArray () const {return m_PointArray;}
	CPoint* GetPointArray () {return m_PointArray;}

	int GetArrayLength () const {return m_Length;}

	void Reset ();

	void Add (long X,long Y);
	void Add (const CPoint& Point);

	void BreakHere ();

	int	 GetSegmentCount () const;
	const CPoint* GetSegment (int Idx) const;
	int	 GetSegmentLength (int Idx) const;

	int GetNearestPoint (const CPoint& Point) const;
};//SPaperPointList

#endif









