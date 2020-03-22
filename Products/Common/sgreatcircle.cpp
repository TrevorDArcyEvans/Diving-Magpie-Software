#include "stdafx.h"
#include "SGreatCircle.hpp"
#include "SGeometricConstants.hpp"
#include "S3DMatrix.hpp"
#include "SException.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SGreatCircle::SGreatCircle
(
	const SGlobalPoint& First,
	const SGlobalPoint& Second
)
{
	if (First == Second)
		throw new SException (_T ("Great circle creation requires two distinct points"));
	//if
	
	S3DVector FV = First;
	S3DVector SV = Second;

	m_Axis = FV^SV;

	m_Axis = m_Axis/m_Axis.Mod ();
}//SGreatCircle::SGreatCircle

bool SGreatCircle::Contains 
(
	const SGlobalPoint& Point,
	double				WithinDegrees
)const
{
	S3DVector PV = Point;

	double AngleToAx = m_Axis.AngleTo (PV);

	return fabs (90.0 - AngleToAx) <= WithinDegrees;
}//SGreatCircle::Contains

SGlobalPoint SGreatCircle::PointOfMaxLat () const
{
	if (m_Axis.z () > 0.0)
		return m_Axis;
	else
		return SGlobalPoint (m_Axis.Phi () - 90.0,m_Axis.Theta () + SLongitudeDelta (180.0));
	//if
}//SGreatCircle::PointOfMaxLat

SGlobalPoint SGreatCircle::GetPoint 
(
	const SGlobalPoint&		FixedPoint,
	const SLongitudeDelta&	Along,
	const SLongitudeDelta&	OffLine
)const
{
	S3DVector Fixed = FixedPoint;

	S3DVector RetVec = Fixed.Rotate (m_Axis,Along);

	if (OffLine != 0.0)
	{
		S3DVector OffAxis = m_Axis ^ RetVec;

		RetVec = RetVec.Rotate (OffAxis,OffLine);
	}//if

	return RetVec;
}//SGreatCircle::GetPoint

SGlobalPoint SGreatCircle::MoveOffLine 
(
	const SGlobalPoint&		Point,
	const SLongitudeDelta&	OffLine
)const
{
	if (OffLine != 0.0)
	{
		S3DVector GloVec (Point);
		
		S3DVector OffAxis = m_Axis ^ GloVec;

		return GloVec.Rotate (OffAxis,OffLine);
	}
	else
		return Point;
	//if
}//SGreatCircle::MoveOffLine

double SGreatCircle::GetLatFromLong 
(
	const SLongitude&	Long,
	bool				WestToEast
)const
{
//	Find the point at which this great circle and the meridian of the requested longitude cross
	S3DVector Merid (90.0,Long + SLongitudeDelta (90.0));

//	Which is their cross product
	if (WestToEast)
		return 90.0 - (Merid ^ m_Axis).Phi ();
	else
		return 90.0 - (m_Axis ^ Merid).Phi ();
	//if
}//SGreatCircle::GetLatFromLong
	
SLongitudeDelta SGreatCircle::GetSeparation
(
	const SGlobalPoint& To,
	const SGlobalPoint& From,
	bool				Strict,
	const S3DVector&	PointOfView
)const
{
	S3DVector ToOrg = To;
	S3DVector FromOrg = From;

	if (Strict)
	{
//		Rotate both vectors onto the circle
		SLongitudeDelta ToAng   = m_Axis.AngleTo (ToOrg);
		S3DVector		ToAbout = ToOrg ^ m_Axis;

		ToOrg.Rotate (ToAbout,90.0 - ToAng);
	
		SLongitudeDelta FromAng   = m_Axis.AngleTo (FromOrg);
		S3DVector		FromAbout = FromOrg ^ m_Axis;

		FromOrg.Rotate (FromAbout,90.0 - FromAng);
	}//if

	if (PointOfView.IsNull ())
		return FromOrg.AngleTo (ToOrg);
	else
		return FromOrg.AngleTo (ToOrg,PointOfView);
	//if
}//SGreatCircle::GetSeparation

SGreatCircle SGreatCircle::GetPerpCirc 
(
	const SGlobalPoint& At
)
{
	SGreatCircle RetVal;

	RetVal.m_Axis = m_Axis ^ At;

	return RetVal;
}//SGreatCircle::GetPerpCirc

SLongitudeDelta SGreatArc::GetTotalLength () const
{
	return m_Circle.GetSeparation (m_End,m_Start);
}//SGreatArc::GetTotalLength

SLongitudeDelta SGreatArc::GetAlong 
(
	const SGlobalPoint& Point,
	bool				Strict
)const
{
	S3DVector POV = ((S3DVector)m_Start) ^ m_End;

	return m_Circle.GetSeparation (Point,m_Start,Strict,POV);
}//SGreatArc::GetAlong

SGlobalPoint SGreatArc::GetPointAlong 
(
	const SLongitudeDelta& Along
)const
{
	return m_Circle.GetPoint (m_Start,Along);
}//SGreatArc::GetPointAlong

bool SGreatArc::Contains 
(
	const SGlobalPoint& Point,
	double				WidthInKm
)const
{
	if (m_Circle.Contains (Point,WidthInKm/(2.0 * MEAN_KM_PER_SURF_DEGREE))) // Divide by 2.0 for offset of half thickness
	{
		SLongitude Sep = GetAlong (Point);

		return Sep >= 0.0 && Sep <= GetTotalLength (); 
	}
	else
		return false;
	//if
}//SGreatArc::Contains
