#ifndef __S3DVector_hpp
#define __S3DVector_hpp

#include "SLongitude.hpp"

class S3DMatrix;

class S3DVector
{
friend S3DVector operator * (const S3DVector& Vec,const S3DMatrix& Mat);

private:

	double	m_x;
	double	m_y;
	double	m_z;

public:

	S3DVector ();
	S3DVector (double x,double y,double z);
	S3DVector (double Phi /* Colatitude */,const SLongitude& Theta /* Longitude */,double r = 1.0);
	virtual ~S3DVector () {}

	S3DVector operator ^ (const S3DVector& RVal) const;	// Cross Product
	double    operator * (const S3DVector& RVal) const;	// Dot Product

	S3DVector operator / (double By) const;

	double Phi () const;
	SLongitude Theta () const;

	SLongitudeDelta AngleTo (const S3DVector& To) const;
	SLongitudeDelta AngleTo (const S3DVector& To,const S3DVector& PointOfView) const;

	double x () const;
	double y () const;
	double z () const;

	bool IsNull () const {return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);}

	double Mod () const;

	S3DVector Rotate (const S3DVector& About,const SLongitudeDelta& By) const;
};//S3DVector

#endif

