#ifndef __SVectors_hpp
#define __SVectors_hpp

#include <math.h>

class SVector
{
public:

	double m_X;
	double m_Y;

	SVector (double X = 0.0,double Y = 0.0):m_X (X),m_Y (Y) {}
	virtual ~SVector () {}

	SVector operator + (const SVector& RVal) const;
	SVector operator - (const SVector& RVal) const;

	SVector operator - () const;

	double operator * (const SVector& RVal) const;
	double operator ^ (const SVector& RVal) const;

	SVector operator * (double RVal) const;
	SVector operator / (double RVal) const;

	SVector Perp () const;

	SVector Hat () const;

	SVector ComponentAlong (const SVector& RVal) const;
	SVector ComponentPerp  (const SVector& RVal) const;

	double ModSq () const {return m_X * m_X + m_Y * m_Y;}
	double Mod   () const {return sqrt (ModSq ());}

	double Arg () const {return atan2 (m_Y,m_X);}

	double Gradient () const {return m_Y/m_X;}
};//SVector

class SVPoint
{
public:

	double m_X;
	double m_Y;

	SVPoint (double X = 0.0,double Y = 0.0):m_X (X),m_Y (Y) {}
	virtual ~SVPoint () {}

	SVector operator - (const SVPoint& RVal) const;
	SVPoint operator + (const SVector& RVal) const;
	SVPoint operator - (const SVector& RVal) const;
};//SVPoint

class SVLine:public SVector
{
protected:

	SVPoint	m_Point;

public:

	SVLine (double VX = 0.0,double VY = 0.0,double PX = 0.0,double PY = 0.0):SVector (VX,VY),
																			 m_Point (PX,PY) {}
	SVLine (const SVPoint& Start,const SVPoint& End);
	SVLine (const SVPoint& Start,const SVector& Vector);
	virtual ~SVLine () {}

	const SVPoint& Point () const {return m_Point;}
	SVLine LineTo (const SVPoint& RVal) const;
	SVPoint MidPoint () const;

	bool SameSide (const SVPoint& A,const SVPoint& B) const;
};//SVLine

class SVectors
{
public:

	static SVLine Bisector (const SVPoint& A,const SVPoint& B);
};//SVectors

#endif
