#include "stdafx.h"
#include "S3DVector.hpp"
#include "SGeometricConstants.hpp"
#include <math.h>
#include "S3DMatrix.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

S3DVector::S3DVector ()
:m_x (0.0),
 m_y (0.0),
 m_z (0.0)
{
}//S3DVector::S3DVector

S3DVector::S3DVector 
(
	double x,
	double y,
	double z
)
:m_x (x),
 m_y (y),
 m_z (z)
{
}//S3DVector::S3DVector

S3DVector::S3DVector 
(
	double				Phi,
	const SLongitude&	Theta,
	double				r

)
{
	m_y		 = r * cos (Phi * RADIANS_PER_DEGREE);
	double c = r * sin (Phi * RADIANS_PER_DEGREE);
	m_z		 = c * cos (Theta * RADIANS_PER_DEGREE);
	m_x		 = c * sin (Theta * RADIANS_PER_DEGREE);
}//S3DVector::S3DVector

S3DVector S3DVector::operator ^ 
(
	const S3DVector& RVal
)const
{
	S3DVector RetVal;

	RetVal.m_x = m_y * RVal.m_z - m_z * RVal.m_y;
	RetVal.m_y = m_z * RVal.m_x - m_x * RVal.m_z;
	RetVal.m_z = m_x * RVal.m_y - m_y * RVal.m_x;

	return RetVal;
}//S3DVector::operator ^

S3DVector S3DVector::operator / 
(
	double By
)const
{
	return S3DVector (m_x/By,m_y/By,m_z/By);
}//S3DVector::operator

double S3DVector::operator * 
(
	const S3DVector& RVal
)const
{
	return m_x * RVal.m_x + m_y * RVal.m_y + m_z * RVal.m_z;
}//S3DVector::operator *

double S3DVector::Mod () const
{
	return ::sqrt (m_x * m_x + m_y * m_y + m_z * m_z);
}//S3DVector::Mod

SLongitudeDelta S3DVector::AngleTo 
(
	const S3DVector& To
)const
{
	double abcos = (*this) * To;

	S3DVector vecabsin = (*this) ^ To;

	double absin = vecabsin.Mod ();

	return atan2 (absin,abcos) * DEGREES_PER_RADIAN;
}//S3DVector::AngleTo

SLongitudeDelta S3DVector::AngleTo 
(
	const S3DVector& To,
	const S3DVector& PointOfView
)const
{
	double abcos = (*this) * To;

	S3DVector vecabsin = (*this) ^ To;

	double absin = vecabsin.Mod ();

	SLongitudeDelta RetVal = atan2 (absin,abcos) * DEGREES_PER_RADIAN;

	if ((vecabsin * PointOfView) > 0.0)
		return RetVal;
	else
		return -RetVal;
	//if	
}//S3DVector::AngleTo

double S3DVector::Phi () const
{
	double r = sqrt (m_x * m_x + m_y * m_y + m_z * m_z);

	return acos (m_y/r) * DEGREES_PER_RADIAN;
}//S3DVector::Phi

SLongitude S3DVector::Theta () const
{
	return atan2 (m_x,m_z) * DEGREES_PER_RADIAN;
}//S3DVector::Theta

double S3DVector::x () const
{
	return m_x;
}//S3DVector::x

double S3DVector::y () const
{
	return m_y;
}//S3DVector::y

double S3DVector::z () const
{
	return m_z;
}//S3DVector::z

S3DVector S3DVector::Rotate 
(
	const S3DVector&		About,
	const SLongitudeDelta&	By
)const
{
	S3DMatrix XOnly;
	S3DMatrix YOnly;

	XOnly.RotateAboutX (About.Phi () * RADIANS_PER_DEGREE);
	YOnly.RotateAboutY (-About.Theta () * RADIANS_PER_DEGREE);

	S3DMatrix RotMat;

	RotMat.RotateAboutY (By * RADIANS_PER_DEGREE);

	S3DMatrix Combi = XOnly * YOnly;

	return (*this) * Combi * RotMat * ~Combi;
}//S3DVector::Rotate

