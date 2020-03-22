#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include "SPoints.hpp"
#include "SGreatCircle.hpp"
//#include "SPositions.hpp"
//#include "SProjection.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

double SFlatWorldPoint::DistanceFrom 
(
	const SFlatWorldPoint& RVal
)const
{
	double dx = m_X - RVal.m_X;
	double dy = m_Y - RVal.m_Y;
	
	return sqrt (dx * dx + dy * dy);
}//SFlatWorldPoint::DistanceFrom

void SPaperBox::Fit 
(
	const CPoint& Point
)
{
	if (m_Virgin)
	{
		m_Virgin = false;
		m_TL = m_BR = Point;
	}
	else
	{
		m_TL.x = __min (m_TL.x,Point.x);
		m_TL.y = __min (m_TL.y,Point.y);
		m_BR.x = __max (m_BR.x,Point.x);
		m_BR.y = __max (m_BR.y,Point.y);
	}//if
}//SPaperBox::Fit

void SPaperBox::Fit 
(
	const SPaperBox&   Box
)
{
	Fit (Box.m_TL);
	Fit (Box.m_BR);
}//SPaperBox::Fit

void SPaperBox::Fit 
(
	const CRect& Rect
)
{
	Fit (Rect.TopLeft ());
	Fit (Rect.BottomRight ());
}//SPaperBox::Fit

bool SPaperBox::Normalize ()
{
	bool RetVal = false;

	if (m_TL.x > m_BR.x)
	{
		short Temp	= m_TL.x;
		m_TL.x		= m_BR.x;
		m_BR.x		= Temp;

		RetVal = true;
	}//if

	if (m_TL.y > m_BR.y)
	{
		short Temp	= m_TL.y;
		m_TL.y		= m_BR.y;
		m_BR.y		= Temp;

		RetVal = true;
	}//if

	return RetVal;
}//SPaperBox::Normalize

bool SPaperBox::Contains 
(
	const CPoint& Point
)const
{
	if (m_Virgin)
		return false;
	else
		return (Point.x >= m_TL.x)
			&& (Point.y >= m_TL.y)
			&& (Point.x <= m_BR.x)
			&& (Point.y <= m_BR.y);
	//if
}//SPaperBox::Contains

bool SPaperBox::Overlaps 
(
	const SPaperBox& Box
)const
{
	if (m_Virgin || Box.m_Virgin)
		return false;
	//if

//	Do they overlap in X?
	bool InX = ((m_BR.x > Box.m_TL.x) && (m_BR.x <= Box.m_BR.x))
			|| ((Box.m_BR.x > m_TL.x) && (Box.m_BR.x <= m_BR.x));

	if (!InX)
		return false;
	//if

//	Just return if they overlap in Y;

	return ((m_BR.y > Box.m_TL.y) && (m_BR.y <= Box.m_BR.y))
		|| ((Box.m_BR.y > m_TL.y) && (Box.m_BR.y <= m_BR.y));
}//SPaperBox::Overlaps

void SPaperBox::Reset ()
{
//	"I knew Doris Day before she was a virgin"
	m_Virgin = true;
}//SPaperBox::Reset

int SPaperBox::Width () const
{
	return m_BR.x - m_TL.x;
}//SPaperBox::Width
	
int SPaperBox::Height () const
{
	return m_BR.y - m_TL.y;
}//SPaperBox::Height

void SFlatWorldBox::Inflate 
(
	double Percent
)
{
	double dx = (m_BR.m_X - m_TL.m_X) * Percent/200;
	double dy = (m_BR.m_Y - m_TL.m_Y) * Percent/200;

	m_BR.m_X += dx;
	m_BR.m_Y += dy;
	m_TL.m_X -= dx;
	m_TL.m_Y -= dy;
}//SFlatWorldBox::Inflate

void SFlatWorldBox::Fit 
(
	const SFlatWorldPoint& Point
)
{
	if (m_Virgin)
	{
		m_Virgin = false;
		m_TL = m_BR = Point;
	}
	else
	{
		m_TL.m_X = __min (m_TL.m_X,Point.m_X);
		m_BR.m_X = __max (m_BR.m_X,Point.m_X);
		m_TL.m_Y = __max (m_TL.m_Y,Point.m_Y);
		m_BR.m_Y = __min (m_BR.m_Y,Point.m_Y);
	}//SFlatWorldBox::Fit
}//SFlatWorldBox::Fit 

void SFlatWorldBox::Fit 
(
	const SFlatWorldBox& Box
)
{
	Fit (Box.m_TL);
	Fit (Box.m_BR);
}//SFlatWorldBox::Fit

bool SFlatWorldBox::Contains 
(
	const SFlatWorldPoint& Point
)const
{
	if (m_Virgin)
		return false;
	else
		return (Point.m_X >= m_TL.m_X)
			&& (Point.m_Y >= m_BR.m_Y)
			&& (Point.m_X <= m_BR.m_X)
			&& (Point.m_Y <= m_TL.m_Y);
	//if
}//SFlatWorldBox::Contains

bool SFlatWorldBox::Overlaps 
(
	const SFlatWorldBox& Box
)const
{
	if (m_Virgin || Box.m_Virgin)
		return false;
	//if

//	Do they overlap in x?
	bool InX = ((m_BR.m_X > Box.m_TL.m_X) && (m_BR.m_X <= Box.m_BR.m_X))
			|| ((Box.m_BR.m_X > m_TL.m_X) && (Box.m_BR.m_X <= m_BR.m_X));

	if (!InX)
		return false;
	//if

//	And in y?
	return ((m_BR.m_Y > Box.m_BR.m_Y) && (m_BR.m_Y <= Box.m_TL.m_Y))
		|| ((Box.m_BR.m_Y > m_BR.m_Y) && (Box.m_BR.m_Y <= m_TL.m_Y));
	//if
}//SFlatWorldBox::Overlaps

void SFlatWorldBox::Reset ()
{
	m_Virgin = true; // Miraculous
}//SFlatWorldBox::Reset

double SFlatWorldBox::Width () const
{
	return m_BR.m_X - m_TL.m_X;
}//SFlatWorldBox::Width

double SFlatWorldBox::Height () const
{
	return m_TL.m_Y - m_BR.m_Y;
}//SFlatWorldBox::Height

void SSimpleGlobalBox::Fit 
(
	const SGlobalPoint& Point
)
{
	if (m_Virgin)
	{
		m_Virgin = false;
		m_BottomLat = m_TopLat = Point.m_Lat;
		m_LeftLong = m_RightLong = Point.m_Long;
	}
	else if (Contains (Point))
		return;
	else if (m_CoversNP)
		m_BottomLat = min (m_BottomLat,Point.m_Lat);
	else if (m_CoversSP)
		m_TopLat    = max (m_TopLat,Point.m_Lat);
	else
	{
		m_BottomLat = min (m_BottomLat,Point.m_Lat);
		m_TopLat    = max (m_TopLat,Point.m_Lat);

		if (m_LeftLong == m_RightLong)
		{
			if ((m_LeftLong - Point.m_Long) > 0.0)
				m_LeftLong = Point.m_Long;
			else
				m_RightLong = Point.m_Long;
			//if
		}
		else if (!Point.m_Long.Between (m_LeftLong,m_RightLong,1.0))
		{
			if (fabs (m_LeftLong - Point.m_Long) < fabs (Point.m_Long - m_RightLong))
				m_LeftLong = Point.m_Long;
			else
				m_RightLong = Point.m_Long;
			//if
		}//if
	}//if
}//SSimpleGlobalBox::Fit

void SSimpleGlobalBox::Fit 
(	
	const SGlobalPoint& PointA,
	const SGlobalPoint& PointB
)
{
	Fit (PointA);
	Fit (PointB);

	if (fabs (PointA.m_Long - PointB.m_Long) < 2.1)
		return;
	//if

	if (fabs (PointA.m_Lat - PointB.m_Lat) < 2.1)
		return;
	//if

	SGreatCircle GC (PointA,PointB);

	SGlobalPoint Max = GC.PointOfMaxLat ();
	SGlobalPoint Min (-Max.m_Lat,Max.m_Long + SLongitudeDelta (180.0));

	if (Max.m_Long.Between (PointA.m_Long,PointB.m_Long,PointB.m_Long - PointA.m_Long))
		Fit (Max);
	//if

	if (Min.m_Long.Between (PointA.m_Long,PointB.m_Long,PointB.m_Long - PointA.m_Long))
		Fit (Min);
	//if
}//SSimpleGlobalBox::Fit

void SSimpleGlobalBox::MakeLongContain 
(
	const SLongitude& Long
)
{
	if (!Long.Between (m_LeftLong,m_RightLong,1.0))
	{
		SLongitude Temp = m_LeftLong;
		m_LeftLong = m_RightLong;
		m_RightLong = Temp;
	}//if
}//SSimpleGlobalBox::MakeLongContain

SSimpleGlobalBox::ELongOrders SSimpleGlobalBox::GetLongOrder 
(
	const SLongitudeDelta& MyLMyR,
	const SLongitudeDelta& MyLYoL,
	const SLongitudeDelta& MyLYoR
)const
{
	if ((MyLMyR < MyLYoL) && (MyLMyR < MyLYoR))
	{
		if (MyLYoL < MyLYoR)
			return O_MYL_MYR_YOL_YOR;
		else
			return O_MYL_MYR_YOR_YOL;
		//if
	}
	else if ((MyLYoL < MyLMyR) && (MyLYoL < MyLYoR))
	{
		if (MyLMyR < MyLYoR)
			return O_MYL_YOL_MYR_YOR;
		else
			return O_MYL_YOL_YOR_MYR;
		//if
	}
	else // MyLYoR is smallest
	{
		if (MyLMyR < MyLYoL)
			return O_MYL_YOR_MYR_YOL;
		else
			return O_MYL_YOR_YOL_MYR;
		//if
	}//if
}//SSimpleGlobalBox::GetLongOrder

void SSimpleGlobalBox::Fit 
(
	const SSimpleGlobalBox&  Box
)
{
	if (Box.m_Virgin)
		return;
	else if (m_Virgin)
		*this = Box;
	else
	{
		m_CoversNP		= m_CoversNP || Box.m_CoversNP;
		m_CoversSP		= m_CoversSP || Box.m_CoversSP;
		m_CoversAllLong = m_CoversAllLong || Box.m_CoversAllLong;

		if (m_CoversNP && m_CoversSP)
			return;
		else if (m_CoversNP)
			m_BottomLat = min (m_BottomLat,Box.m_BottomLat);
		else if (m_CoversSP)
			m_TopLat    = max (m_TopLat,Box.m_TopLat);
		else
		{
			m_BottomLat = min (m_BottomLat,Box.m_BottomLat);
			m_TopLat    = max (m_TopLat,Box.m_TopLat);

			if (!m_CoversAllLong)
			{
				SLongitudeDelta MyLeftToMyRight   = m_RightLong.Separation (m_LeftLong,1.0);
				SLongitudeDelta MyLeftToYourLeft  = Box.m_LeftLong.Separation (m_LeftLong,1.0);
				SLongitudeDelta MyLeftToYourRight = Box.m_RightLong.Separation (m_LeftLong,1.0);
	
				SLongitudeDelta YourLeftToMyRight = m_RightLong.Separation (Box.m_LeftLong,1.0);

				ELongOrders Order = GetLongOrder (MyLeftToMyRight,MyLeftToYourLeft,MyLeftToYourRight);

				switch (Order)
				{
					default:
					case O_MYL_YOL_YOR_MYR:		// You entirely contained in me
												break;	

												// Me entirely contained in you
					case O_MYL_MYR_YOR_YOL:		m_LeftLong  = Box.m_LeftLong;
												m_RightLong = Box.m_RightLong;
												break;

					case O_MYL_YOR_YOL_MYR:		// Covers all long
												m_CoversAllLong = true;
												break;

					case O_MYL_MYR_YOL_YOR:		// Separate chunks, look for smaller
												if (YourLeftToMyRight < MyLeftToYourRight)
													m_LeftLong = Box.m_LeftLong;
												else
													m_RightLong = Box.m_RightLong;
												//if

												break;

					case O_MYL_YOL_MYR_YOR:		// Overlap to my right
												m_RightLong = Box.m_RightLong;
												break;

					case O_MYL_YOR_MYR_YOL:		//  Overlap to my left
												m_LeftLong = Box.m_LeftLong;
												break;
				}//switch
			}//if
		}//if
	}//if
}//SSimpleGlobalBox::Fit

bool SSimpleGlobalBox::IncludesMeridian	
(
	const SLongitude&	Long,
	bool				Inclusive
)const
{
	return m_CoversNP || m_CoversSP || m_CoversAllLong || Long.Between (m_LeftLong,m_RightLong,1.0,Inclusive);
}//SSimpleGlobalBox::IncludesMeridian

bool SSimpleGlobalBox::Contains			
(
	const SGlobalPoint& Point
)const
{
	if (m_Virgin)
		return false;
	else if (m_CoversNP && m_CoversSP)
		return true;
	else
		return (Point.m_Lat < m_TopLat)
			&& (Point.m_Lat > m_BottomLat)
			&& (m_CoversAllLong || Point.m_Long.Between (m_LeftLong,m_RightLong,1.0));
	//if
}//SSimpleGlobalBox::Contains

bool SSimpleGlobalBox::Overlaps			
(
	const SSimpleGlobalBox& Box
)const
{
	if (m_Virgin || Box.m_Virgin)
		return false;
	else if ((m_CoversNP && Box.m_CoversNP) || (m_CoversSP && Box.m_CoversSP))
		return true;
	else if (m_CoversNP || Box.m_CoversSP)
		return m_BottomLat < Box.m_TopLat;
	else if (m_CoversSP || Box.m_CoversNP)
		return m_TopLat > Box.m_BottomLat;
	else
	{
		bool InLat = !((Box.m_TopLat <= m_BottomLat) || (Box.m_BottomLat >= m_TopLat));

		return InLat 
			&& (m_CoversAllLong 
			 || Box.m_CoversAllLong 
			 || Box.m_LeftLong.Between  (m_LeftLong,m_RightLong,1.0) 
			 || Box.m_RightLong.Between (m_LeftLong,m_RightLong,1.0)
			 || m_LeftLong.Between      (Box.m_LeftLong,Box.m_RightLong,1.0));
	}//if
}//SSimpleGlobalBox::Overlaps

bool SSimpleGlobalBox::EntirelyContains	
(	
	const SSimpleGlobalBox& Box
)const
{
	if (m_Virgin || Box.m_Virgin)
		return false;
	else if (m_CoversNP)
		return m_BottomLat <= Box.m_BottomLat;
	else if (m_CoversSP)
		return m_TopLat    >= Box.m_TopLat;
	else
	{
		bool InLat = (m_BottomLat <= Box.m_BottomLat) && (m_TopLat >= Box.m_TopLat);

		return InLat 
			&& (m_CoversAllLong ||(Box.m_LeftLong.Between  (m_LeftLong,m_RightLong) 
			                       && Box.m_RightLong.Between (m_LeftLong,m_RightLong)));
	}//if
}//SSimpleGlobalBox::EntirelyContains

void SSimpleGlobalBox::Reset ()
{
	m_Virgin = true;
	m_CoversNP = m_CoversSP = m_CoversAllLong = false;
}//SSimpleGlobalBox::Reset

void SSimpleGlobalBox::SetFlat 
(
	double MinLat,
	double MaxLat,
	double LeftLong,
	double RightLong
)
{
	m_BottomLat = MinLat;
	m_TopLat    = MaxLat;
	m_LeftLong  = LeftLong;
	m_RightLong = RightLong;

	if (MinLat < -89.999)
		m_CoversSP = true;
	//if
	
	if (MaxLat > 89.999)
		m_CoversNP = true;
	//if

	if (fabs (RightLong - LeftLong) > 359.999)
		m_CoversAllLong = true;
	//if

	m_Virgin = false;
}//SSimpleGlobalBox::SetFlat

SSimpleGlobalBox& SSimpleGlobalBox::operator = 
(
	const SSimpleGlobalBox& RVal
)
{
	m_BottomLat		= RVal.m_BottomLat;
	m_TopLat		= RVal.m_TopLat;
	m_LeftLong		= RVal.m_LeftLong;
	m_RightLong		= RVal.m_RightLong;
	m_CoversNP		= RVal.m_CoversNP;
	m_CoversSP		= RVal.m_CoversSP;
	m_Virgin		= RVal.m_Virgin;
	m_CoversAllLong = RVal.m_CoversAllLong;

	return *this;
}//SSimpleGlobalBox::operator = 

void SSimpleGlobalBox::AddBorder 
(
	double BorderWidth
)
{
	if (fabs (m_LeftLong - m_RightLong) <= (2 * BorderWidth))
		m_CoversAllLong = true;
	else
	{
		m_LeftLong  -= SLongitudeDelta (BorderWidth);
		m_RightLong += SLongitudeDelta (BorderWidth);
	}//if

	m_BottomLat -= BorderWidth;
	m_TopLat    += BorderWidth;

	if (m_BottomLat < -90.0)
		m_CoversSP = true;
	//if

	if (m_TopLat > 90.0)
		m_CoversNP = true;
	//if
}//SSimpleGlobalBox::AddBorder

void SSimpleGlobalBox::SetNPCover 
(
	double MinLat
)
{
	m_Virgin = false;
	m_CoversNP = true;
	m_BottomLat = MinLat;
}//SSimpleGlobalBox::SetNPCover

void SSimpleGlobalBox::SetSPCover 
(
	double MaxLat
)
{
	m_Virgin = false;
	m_CoversSP = true;
	m_TopLat = MaxLat;
}//SSimpleGlobalBox::SetSPCover

void SSimpleGlobalBox::SetAllLongCover 
(
	double MinLat,
	double MaxLat
)
{
	m_Virgin = false;
	m_CoversAllLong = true;
	m_BottomLat = MinLat;
	m_TopLat	= MaxLat;
}//SSimpleGlobalBox::SetAllLongCover

bool SSimpleGlobalBox::TouchesRight		
(
	const SLongitude& Long
)const
{
	return m_RightLong == Long;
}//SSimpleGlobalBox::TouchesRight

bool SSimpleGlobalBox::TouchesLeft		
(
	const SLongitude& Long
)const
{
	return m_LeftLong == Long;
}//SSimpleGlobalBox::TouchesRight

void SSimpleGlobalBox::FinishOff ()
{
	if (m_BottomLat < -89.999)
		m_CoversSP = true;
	//if
	
	if (m_TopLat > 89.999)
		m_CoversNP = true;
	//if

	SLongitudeDelta Diff = m_RightLong - m_LeftLong;

	if (Diff > -1.5 && Diff < 0.0)
		m_CoversAllLong = true;
	//if
}//SSimpleGlobalBox::FinishOff

SPaperPointList::SPaperPointList 
(
	const SPaperPointList& RVal
)
:m_Allocated	(RVal.m_Allocated),
 m_Length		(RVal.m_Length)
{
	for (int i = 0; i < RVal.m_Breaks.GetSize (); i++)
		m_Breaks.Add (RVal.m_Breaks[i]);
	//for

	if (m_Length > 0)
	{
		m_PointArray = new CPoint [m_Length];

		memcpy (m_PointArray,RVal.m_PointArray,m_Length * sizeof (CPoint));
	}//if
}//SPaperPointList::SPaperPointList

SPaperPointList::~SPaperPointList ()
{
	if (m_PointArray)
		delete [] m_PointArray;
	//if
}//SPaperPointList::~SPaperPointList

void SPaperPointList::Reset ()
{
	if (m_PointArray)
		delete [] m_PointArray;
	//if
	
	m_Breaks.RemoveAll ();
	m_Breaks.Add (0);

	m_PointArray = 0;
	m_Length	 = 0;
	m_Allocated	 = 0;
}//SPaperPointList::Reset

void SPaperPointList::Add 
(
	const CPoint& Point
)
{
	Add (Point.x,Point.y);
}//SPaperPointList::Add 

void SPaperPointList::Add 
(
	long X,
	long Y
)
{
	if (m_Length > 0
	 && (m_Breaks.GetSize () == 0 || m_Breaks[m_Breaks.GetUpperBound ()] != m_Length)
	 && m_PointArray[m_Length - 1].x == X 
	 && m_PointArray[m_Length - 1].y == Y)
		return;
	//if

	if (m_Length >= m_Allocated)
		Resize ((m_Allocated + 5) * 2);
	//if

	m_PointArray[m_Length].x = X;
	m_PointArray[m_Length].y = Y;

	m_Length++;
}//SPaperPointList::Add

void SPaperPointList::Resize
(
	int NewSize
)
{
	CPoint* NewArray = new CPoint[NewSize];

	if (m_PointArray)
	{
		for (int i = 0; i < m_Length; i++)
			NewArray[i] = m_PointArray[i];
		//for

		delete [] m_PointArray;
	}//if

	m_PointArray = NewArray;
	m_Allocated  = NewSize;
}//SPaperPointList::Resize

int SPaperPointList::GetNearestPoint 
(
	const CPoint&	Point
)const
{	
	long BestDist = 1000000000;
	int RetVal = 0;

	for (int i = 0; i < GetArrayLength (); i++)
	{
		int dx = Point.x - m_PointArray[i].x;
		int dy = Point.y - m_PointArray[i].y;

		long Dist = (dx * dx) + (dy * dy);

		if (Dist < BestDist)
		{
			BestDist = Dist;
			RetVal = i;
		}//if
	}//for

	return RetVal;
}//SPaperPointList::GetNearestPoint

void SPaperPointList::BreakHere ()
{
	m_Breaks.Add (m_Length);
}//SPaperPointList::BreakHere

int	SPaperPointList::GetSegmentCount () const
{
	return m_Breaks.GetSize ();
}//SPaperPointList::GetSegmentCount

const CPoint* SPaperPointList::GetSegment 
(
	int Idx
)const
{
	return m_PointArray + m_Breaks[Idx];
}//SPaperPointList::GetSegment
	
int	SPaperPointList::GetSegmentLength 
(
	int Idx
)const
{
	if (Idx == (m_Breaks.GetSize () - 1))
		return m_Length - m_Breaks[Idx];
	else
		return m_Breaks[Idx + 1] - m_Breaks[Idx];
	//if
}//SPaperPointList::GetSegment

	
