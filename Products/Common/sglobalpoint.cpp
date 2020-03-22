#include "stdafx.h"
#include "SGlobalPoint.hpp"
#include "SString.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

double SGlobalPoint::sm_CloseEnough = 0.0001;

SGlobalPoint::SGlobalPoint 
(	
	const S3DVector& Vec
)
:m_Lat (90.0 - Vec.Phi ()),
 m_Long (Vec.Theta ())
{
}//SGlobalPoint::SGlobalPoint

SGlobalPoint::operator S3DVector () const
{
	return S3DVector (90.0 - m_Lat,m_Long);
}//SGlobalPoint::operator S3DVector

CString SGlobalPoint::AsString () const
{
	SString LatLab;
	SString LongLab;

	LatLab.SetDegMinSec (m_Lat);
	LongLab.SetDegMinSec (m_Long);

	return "(" + LatLab + "," + LongLab + ")";
}//SGlobalPoint::AsString

bool SGlobalPoint::operator == 
(
	const SGlobalPoint& RVal
)const 
{
	return (fabs (m_Lat - RVal.m_Lat)   < sm_CloseEnough)
	    && (fabs (m_Long - RVal.m_Long) < sm_CloseEnough);
}//SGlobalPoint::operator == 

SGlobalPoint& SGlobalPoint::operator = 
(
	const SGlobalPoint& RVal
)
{
	m_Lat  = RVal.m_Lat;
	m_Long = RVal.m_Long;

	return *this;
}//SGlobalPoint::operator = 

double SGlobalPoint::SepSq 
(
	const SGlobalPoint& Point
)const
{
	double DLat  = m_Lat  - Point.m_Lat;
	double DLong = m_Long - Point.m_Long;

	return (DLat * DLat) + (DLong * DLong);
}//SGlobalPoint::SepSq 

SGlobalPoint SGlobalPoint::InterpolateOnLong 
(
	const SGlobalPoint& Point,
	const SLongitude&	Long
)const
{
	double Lat = m_Lat + (Point.m_Lat - m_Lat) * ((Long - m_Long)/(Point.m_Long - m_Long));

	return SGlobalPoint (Lat,Long);
}//SGlobalPoint::InterpolateOnLong

SGlobalPoint SGlobalPoint::MidPoint 
(
	const SGlobalPoint& Other
)const
{
	return SGlobalPoint ((m_Lat + Other.m_Lat)/2,m_Long.Midway (Other.m_Long,true));
}//SGlobalPoint::MidPoint

