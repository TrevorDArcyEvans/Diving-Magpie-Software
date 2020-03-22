#ifndef __SGreatCircle_hpp
#define __SGreatCircle_hpp

#include "SLongitude.hpp"
#include "SGlobalPoint.hpp"
#include "S3DVector.hpp"

class SGreatCircle
{
public:

	S3DVector	m_Axis;

	SGreatCircle () {}
	SGreatCircle (const SGlobalPoint& First,const SGlobalPoint& Second);
	virtual ~SGreatCircle () {}

	SGlobalPoint PointOfMaxLat () const;

	SGlobalPoint GetPoint (const SGlobalPoint& FixedPoint,const SLongitudeDelta& Along,const SLongitudeDelta& OffLine = 0.0) const;
	SLongitudeDelta GetSeparation (const SGlobalPoint& To,const SGlobalPoint& From,bool Strict = false,const S3DVector& PointOfView = S3DVector (0.0,0.0,0.0)) const;

	SGlobalPoint MoveOffLine (const SGlobalPoint& Point,const SLongitudeDelta& OffLine) const;

	SGreatCircle GetPerpCirc (const SGlobalPoint& At);

	bool Contains (const SGlobalPoint& Point,double WithinDegrees = 0.0001) const;

	double GetLatFromLong (const SLongitude& Long,bool WestToEast) const;
};//SGreatCircle

class SGreatArc
{
public:

	SGreatCircle	m_Circle;
	SGlobalPoint	m_Start;
	SGlobalPoint	m_End;

	SGreatArc () {}

	SLongitudeDelta GetTotalLength () const;
	SLongitudeDelta GetAlong (const SGlobalPoint& Point,bool Strict = false) const;
	SGlobalPoint    GetPointAlong (const SLongitudeDelta& Along) const;
	bool			Contains (const SGlobalPoint& Point,double WidthInKm = 1.0) const;
};//SGreatArc

#endif

