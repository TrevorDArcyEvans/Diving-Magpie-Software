#include "stdafx.h"
#include <math.h>
#include "SProjection.hpp"
#include "SGeometricConstants.hpp"
#include "SUseful.hpp"
#include "SException.hpp"
#include "SProjectionDiscontinuity.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SProjection::SProjection 
(
	const SProjection& RVal
)
:m_Matrix	        (RVal.m_Matrix),
 m_Previous         (0),
 m_LastUsed         (0),
 m_NoMatrixChange   (RVal.m_NoMatrixChange),
 m_ScreenRect       (RVal.m_ScreenRect)
{
}//SProjection::SProjection

SProjection::~SProjection ()
{
}//SProjection::~SProjection

void SProjection::SwitchPrevious ()
{
	if (m_Previous)
    {
		delete m_Previous;
        m_Previous = 0;
    }//if


	m_Previous = m_LastUsed;
	m_LastUsed = Clone ();
}//SProjection::SwitchPrevious

bool SProjection::Pin ()
{
	return m_Matrix.Pin ();
}//SProjection::Pin

bool SProjection::Unpin ()
{
	return  m_Matrix.Unpin ();
}//SProjection::Unpin

SProjection* SProjection::RevertToPrevious  ()
{
	if (!m_Previous)
		return this;
	else
	{
		m_Previous->m_Previous = this;
		m_Previous->m_LastUsed = m_LastUsed;
		return m_Previous;
	}//if
}//SProjection::RevertToPrevious

void SProjection::SetMatrix	   
(
	const SMatrix& Matrix
)
{
	m_Matrix = Matrix;
}//SProjection::SetMatrix

double SProjection::GetLatPerPaper
(
	const CPoint&	Locality
)const
{
	SGlobalPoint GlobLoc = PaperToGlobal (Locality);

	return 1.0/GetPaperUnitsPerDegreeLat (GlobLoc);
}//SProjection::GetLatPerPaper

double SProjection::GetPaperUnitsPerDegreeLat
(
	const SGlobalPoint& Locality
)const
{
	return m_Matrix.GetPaperPerWorld () * MetresPerDegreeLat (Locality);
}//SProjection::GetPaperUnitsPerDegreeLat

void  SProjection::SetPaperUnitsPerDegreeLat 
(
	const SGlobalPoint& Locality,
	double				Ratio
)
{
	m_Matrix.SetPaperPerWorld (Ratio/MetresPerDegreeLat (Locality));
}//SProjection::SetPaperUnitsPerDegreeLat

double SProjection::MetresPerDegreeLat
(
	const SGlobalPoint& Locality
)const
{
	SFlatWorldPoint P1 = GlobalToPlane (SGlobalPoint (Locality.m_Lat - 0.1,Locality.m_Long));
	SFlatWorldPoint P2 = GlobalToPlane (SGlobalPoint (Locality.m_Lat + 0.1,Locality.m_Long));

	return 5.0 * P1.DistanceFrom (P2);
}//SProjection::MetresPerDegreeLat

double SProjection::MetresPerDegreeLong
(
	const SGlobalPoint& Locality
)const
{
	SFlatWorldPoint P1 = GlobalToPlane (SGlobalPoint (Locality.m_Lat,Locality.m_Long - SLongitudeDelta (0.1)));
	SFlatWorldPoint P2 = GlobalToPlane (SGlobalPoint (Locality.m_Lat,Locality.m_Long + SLongitudeDelta (0.1)));

	return 5.0 * P1.DistanceFrom (P2);
}//SProjection::MetresPerDegreeLong

double SProjection::DegreesLatPerPaperUnit 
(
	const SGlobalPoint& Locality
)const
{
	CPoint LocalPaper = GlobalToPaper (Locality);

	LocalPaper.y -= 1;
	SGlobalPoint P1 = PaperToGlobal (LocalPaper);

	LocalPaper.y += 2;
	SGlobalPoint P2 = PaperToGlobal (LocalPaper);

	return 0.5 * sqrt (P1.SepSq (P2));
}//SProjection::DegreesLatPerPaperUnit

CPoint SProjection::GlobalToPaper 
(
	const SGlobalPoint& Point
)const
{
//	Some projections may know a quicker way, but this at least works
	return m_Matrix.WorldToPaper (GlobalToPlane (Point));
}//SProjection::GlobalToPaper

CPoint SProjection::GlobalToPaper	
(
	double Lat,
	double Long
)const
{
	return m_Matrix.WorldToPaper (GlobalToPlane (Lat,Long));
}//SProjection::GlobalToPaper

SFlatWorldPoint	SProjection::GlobalToPlane	
(
	double Lat,
	double Long
)const
{
	return GlobalToPlane (SGlobalPoint (Lat,Long));
}//SProjection::GlobalToPlane

SPaperBox SProjection::GlobalToPaper	
(
	const SGlobalBox& Box
)const
{
	return Box.CreatePaperBox (*this);
}//SProjection::GlobalToPaper

SGlobalBox SProjection::PaperToGlobal	
(
	const SPaperBox& Box
)const
{
	return PlaneToGlobalBox (m_Matrix.PaperToWorld (Box));
}//SProjection::PaperToGlobal

SGlobalPoint SProjection::PaperToGlobal	
(
	const CPoint&  Point
)const
{
	return PlaneToGlobal (m_Matrix.PaperToWorld (Point));
}//SProjection::PaperToGlobal

SFlatWorldPoint	SProjection::NaturalToPlane	
(
	const SPosition* Position
)const
{
	const SGlobalPosition* GPos = dynamic_cast <const SGlobalPosition*> (Position);

	if (GPos)
		return GlobalToPlane (GPos->Get ());
	else
	{
		throw new SException (_T ("XY points with geographic projection."));

		return SFlatWorldPoint ();
	}//if
}//SProjection::NaturalToPlane

void SProjection::Align 
(
	const SGlobalPoint& GlobalPoint,
	const CPoint&		PaperPoint
)
{
	m_Matrix.Align (GlobalToPlane (GlobalPoint),PaperPoint);
}//SProjection::Align

void SProjection::AlignNorth 
(
	const CPoint&	Centre
)
{
	SGlobalPoint GCen = PaperToGlobal (Centre);
	
	double Bearing = GetProjectedNorth (GCen) * RADIANS_PER_DEGREE;

	double Old = m_Matrix.GetAbsoluteRotation ();

	m_Matrix.Rotate (Old - Bearing,Centre);

	double test = m_Matrix.GetAbsoluteRotation ();
}//SProjection::AlignNorth

void SProjection::MatchView 
(
	const SProjection&	Projection,
	const SGlobalPoint& Centre
)
{
	double LocalScale = Projection.GetPaperUnitsPerDegreeLat (Centre);

	SetPaperUnitsPerDegreeLat (Centre,LocalScale);

	CPoint VisibleRef = Projection.GlobalToPaper (Centre);

	Align (Centre,VisibleRef);
}//SProjection::MatchView 

const SProjectionDiscontinuity* SProjection::GetDiscontinuity 
(
	int Idx
)const
{
	throw new SException (_T ("Requested projection discontinuity out of range."));

	return 0;
}//SProjection::GetDiscontinuity

double SGeographicProjection::GetPaperUnitsPerDegreeLong 
(
	const SGlobalPoint& Locality
)const
{
	return m_Matrix.GetPaperPerWorld () * MetresPerDegreeLong (Locality);
}//SGeographicProjection::GetPaperUnitsPerDegreeLong

SGreenwichCylindricalProjection::SGreenwichCylindricalProjection 
(
	const SGreenwichCylindricalProjection& RVal
)
:SGeographicProjection (RVal),
 m_MinPlaneX (RVal.m_MinPlaneX),
 m_MaxPlaneX (RVal.m_MaxPlaneX),
 m_MinPlaneY (RVal.m_MinPlaneY),
 m_MaxPlaneY (RVal.m_MaxPlaneY)
{
}//SGreenwichCylindricalProjection::SGreenwichCylindricalProjection

void SGreenwichCylindricalProjection::Initialize ()
{
	SFlatWorldPoint Min = GlobalToPlane (SGlobalPoint (-90.0,-179.999));
	SFlatWorldPoint Max = GlobalToPlane (SGlobalPoint (90.0,179.999));

	m_MinPlaneX = Min.m_X;
	m_MaxPlaneX = Max.m_X;
	m_MinPlaneY = Min.m_Y;
	m_MaxPlaneY = Max.m_Y;
}//SGreenwichCylindricalProjection::Initialize

double SGreenwichCylindricalProjection::GetFiltrationSepSqDeg () const
{
	SGlobalPoint IshyWorst (15.0,0.0);

	double LatSep  = 1.0/GetPaperUnitsPerDegreeLat (IshyWorst);	
	double LongSep = 1.0/GetPaperUnitsPerDegreeLong (IshyWorst);	

	return LatSep * LongSep;
}//SGreenwichCylindricalProjection::GetFiltrationSepSqDeg

SGlobalBox SGreenwichCylindricalProjection::PlaneToGlobalBox
(
	const SFlatWorldBox& Box
)const
{
	SGlobalBox RetVal;

	SGlobalPoint GTL = PlaneToGlobal(Box.TL ());
	SGlobalPoint GBR = PlaneToGlobal(Box.BR ());

	double MaxLat;
	double MinLat;
	SLongitude MinLong;
	SLongitude MaxLong;

	if (Box.TL ().m_Y >= m_MaxPlaneY)
		MaxLat = 90.0;
	else
		MaxLat = GTL.m_Lat;
	//if

	if (Box.BR ().m_Y <= m_MinPlaneY)
		MinLat = -90.0;
	else
		MinLat = GBR.m_Lat;
	//if

	if ((Box.TL ().m_X <= m_MinPlaneX) && (Box.BR ().m_X >= m_MaxPlaneX))
		RetVal.SetAllLongCover (MinLat,MaxLat);
	else
	{
		if (Box.TL ().m_X <= m_MinPlaneX)
		{
			MinLong = -180.0;
			MaxLong = GBR.m_Long;
		}
		else if (Box.BR ().m_X  >= m_MaxPlaneX)
		{
			MinLong = GTL.m_Long;
			MaxLong = 180.0;
		}
		else
		{
			MinLong = GTL.m_Long;
			MaxLong = GBR.m_Long;
		}//if
		
		RetVal.Fit (SGlobalPoint (MinLat,MinLong));
		RetVal.Fit (SGlobalPoint(MinLat,MaxLong));
		RetVal.Fit (SGlobalPoint(MaxLat,MaxLong));
		RetVal.Fit (SGlobalPoint(MinLat,MaxLong));
		RetVal.MakeLongContain (MinLong.Midway (MaxLong));
	}//if

	return RetVal;
}//SGreenwichCylindricalProjection::PlaneToGlobalBox

int SGreenwichCylindricalProjection::GetDiscontinuityCount () const
{
	return 1;
}//SGreenwichCylindricalProjection::GetDiscontinuityCount

const SProjectionDiscontinuity* SGreenwichCylindricalProjection::GetDiscontinuity 
(
	int Idx
)const
{
	if (Idx != 0)
		throw new SException (_T ("Requested projection discontinuity out of range."));
	//if

	static SMeridianSplit Split (SLongitude (180.0));

	return &Split;
}//SGreenwichCylindricalProjection::GetDiscontinuity

SFlatWorldPoint SFlatEarthProjection::GlobalToPlane 
(
	const SGlobalPoint& Point
)const
{
//	100000 ~ metres per degree of latitude
	return SFlatWorldPoint (Point.m_Long * 100000.0,Point.m_Lat * 100000.0);
}//SFlatEarthProjection::GlobalToPlane

SGlobalPoint SFlatEarthProjection::PlaneToGlobal 
(
	const SFlatWorldPoint& Point
)const
{
	return SGlobalPoint (Point.m_Y/100000.,Point.m_X/100000.);
}//SFlatEarthProjection::PlaneToGlobal

SFlatWorldBox SFlatEarthProjection::PlaneWorldBox 
(
	const SGlobalPoint& Locality
)const
{
	static SFlatWorldBox RetVal (GlobalToPlane (SGlobalPoint (90.0,-179.999)),
								 GlobalToPlane (SGlobalPoint (-90.0,179.999)));

	return RetVal;
}//SFlatEarthProjection::PlaneWorldBox

IMPLEMENT_VIRTUAL_CONSTRUCTOR(SFlatEarthProjection)

double SNPStereographicProjection::GetFiltrationSepSqDeg () const
{
	SGlobalPoint IshyWorst (75.0,0.0);

	double LatSep  = 1.0/GetPaperUnitsPerDegreeLat (IshyWorst);	
	double LongSep = 1.0/GetPaperUnitsPerDegreeLong (IshyWorst);	

	return LatSep * LongSep;
}//SNPStereographicProjection::GetFiltrationSepSqDeg

SFlatWorldPoint SNPStereographicProjection::GlobalToPlane 
(
	const SGlobalPoint& Point
)const
{
	double Chi   = (90.0 - Point.m_Lat) * RADIANS_PER_DEGREE;
	double Theta = Point.m_Long * RADIANS_PER_DEGREE;

	double Radius = 6371000.0 * 2.0 * tan (Chi/2);

	return SFlatWorldPoint (Radius * sin (Theta),-Radius * cos (Theta));
}//SNPStereographicProjection::GlobalToPlane

SGlobalPoint SNPStereographicProjection::PlaneToGlobal 
(
	const SFlatWorldPoint& Point
)const
{
	double Radius = sqrt (Point.m_X * Point.m_X + Point.m_Y * Point.m_Y)/6371000.0;
	double Chi    = 2.0 * atan (Radius/2.0);
	double Theta  = atan2 (Point.m_X,-Point.m_Y);

	return SGlobalPoint (90.0 - Chi/RADIANS_PER_DEGREE,Theta/RADIANS_PER_DEGREE);
}//SNPStereographicProjection::PlaneToGlobal

SGlobalBox SNPStereographicProjection::PlaneToGlobalBox	
(
	const SFlatWorldBox& Box
)const
{
	SGlobalBox RetVal;

	if (Box.Contains (GlobalToPlane (SGlobalPoint (90.0,0.0))))
		RetVal.SetNPCover (90.0);
	else if (Box.TL ().m_X < 0.0 && Box.BR ().m_X > 0.0)
	{
//		Highest latitude of rectangle is on x = 0
		if (Box.TL ().m_Y <= 0.0)
			RetVal.Fit (PlaneToGlobal (SFlatWorldPoint (0.0,Box.TL ().m_Y)));
		else
			RetVal.Fit (PlaneToGlobal (SFlatWorldPoint (0.0,Box.BR ().m_Y)));
		//if
	}
	else if (Box.TL ().m_Y > 0.0 && Box.BR ().m_Y < 0.0)
	{
//		Highest latitude of rectangle is on y = 0
		if (Box.BR ().m_X <= 0.0)
			RetVal.Fit (PlaneToGlobal (SFlatWorldPoint (Box.BR ().m_X ,0.0)));
		else
			RetVal.Fit (PlaneToGlobal (SFlatWorldPoint (Box.TL ().m_X ,0.0)));
		//if
	}//if

	RetVal.Fit (PlaneToGlobal(Box.TL ()));
	RetVal.Fit (PlaneToGlobal(Box.TR ()));
	RetVal.Fit (PlaneToGlobal(Box.BR ()));
	RetVal.Fit (PlaneToGlobal(Box.BL ()));

	return RetVal;
}//SNPStereographicProjection::PlaneToGlobalBox

double SNPStereographicProjection::GetProjectedNorth 
(
	const SGlobalPoint& At
)const 
{
	return -At.m_Long;
}//SNPStereographicProjection::GetProjectedNorth

int SNPStereographicProjection::GetDiscontinuityCount () const
{
	return 1;
}//SNPStereographicProjection::GetDiscontinuityCount

SFlatWorldBox SNPStereographicProjection::PlaneWorldBox 
(
	const SGlobalPoint& Locality
)const
{
	SLongitude Rot = -m_Matrix.GetAbsoluteRotation ();

	SMatrix LocMat;

	LocMat.Rotate (Rot);

	SFlatWorldPoint Left  = GlobalToPlane (SGlobalPoint (0.0,-90.0));
	SFlatWorldPoint Bot   = GlobalToPlane (SGlobalPoint (0.0,0.0));

	SFlatWorldBox RetVal = SFlatWorldBox (Left.m_X,-Bot.m_Y,-Left.m_X,Bot.m_Y);

	return LocMat.WorldToWorld (RetVal);
}//SNPStereographicProjection::PlaneWorldBox

const SProjectionDiscontinuity* SNPStereographicProjection::GetDiscontinuity 
(
	int Idx
)const
{
	if (Idx != 0)
		throw new SException (_T ("Requested projection discontinuity out of range."));
	//if

	static SParallelBoundInvalidRegion Region (-90.0,0.0);

	return &Region;
}//SNPStereographicProjection::GetDiscontinuity

IMPLEMENT_VIRTUAL_CONSTRUCTOR(SNPStereographicProjection)

SGallsStereographicProjection::SGallsStereographicProjection () 
{
	Initialize ();
}//SGallsStereographicProjection::SGallsStereographicProjection

SFlatWorldPoint SGallsStereographicProjection::GlobalToPlane 
(
	const SGlobalPoint& Point
)const
{
	static const double A = ROOT_TWO_ON_TWO * RADIANS_PER_DEGREE;
	static const double B = RADIANS_PER_DEGREE/2.0;

	return SFlatWorldPoint (A * Point.m_Long,
							ROOT_TWO_PLUS_TWO_ON_TWO * tan (B * Point.m_Lat));
}//SGallsStereographicProjection::GlobalToPlane

SGlobalPoint SGallsStereographicProjection::PlaneToGlobal 
(
	const SFlatWorldPoint& Point
)const
{
	static const double A = ROOT_TWO_ON_TWO * RADIANS_PER_DEGREE;
	static const double B = RADIANS_PER_DEGREE/2.0;

	return SGlobalPoint (atan (Point.m_Y/ROOT_TWO_PLUS_TWO_ON_TWO)/B,
						 Point.m_X/A);
}//SGallsStereographicProjection::PlaneToGlobal

SFlatWorldBox SGallsStereographicProjection::PlaneWorldBox 
(
	const SGlobalPoint& Locality
)const
{
	static SFlatWorldBox RetVal (GlobalToPlane (SGlobalPoint (90.0,-179.999)),
								 GlobalToPlane (SGlobalPoint (-90.0,179.999)));

	return RetVal;
}//SGallsStereographicProjection::PlaneWorldBox


IMPLEMENT_VIRTUAL_CONSTRUCTOR(SGallsStereographicProjection)

