#ifndef _SGlobalPoint_hpp
#define _SGlobalPoint_hpp

#include "SLongitude.hpp"
#include "SVectors.hpp"
#include "S3DVector.hpp"

class SGlobalPoint
{
private:

	static double sm_CloseEnough;

public:

	double		m_Lat;
	SLongitude	m_Long;

	SGlobalPoint (double Lat = 0.0,SLongitude Long = SLongitude (0.0)):m_Lat (Lat),m_Long (Long) {}
	SGlobalPoint (const SVPoint& VPoint):m_Lat (VPoint.m_Y),m_Long (VPoint.m_X) {}
	SGlobalPoint (const S3DVector& Vec);

	operator S3DVector () const;

	double SepSq (const SGlobalPoint& Point) const;

	bool operator == (const SGlobalPoint& RVal) const;

	SGlobalPoint& operator = (const SGlobalPoint& RVal);

	static double& CloseEnough () {return sm_CloseEnough;}

	SGlobalPoint InterpolateOnLong (const SGlobalPoint& Point,const SLongitude& Long) const;

	SVPoint AsVPoint () const {return SVPoint (m_Long,m_Lat);}

	SGlobalPoint MidPoint (const SGlobalPoint& Other) const;

	CString AsString () const;
};//SGlobalPoint

#endif
