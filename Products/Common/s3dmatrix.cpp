#include "stdafx.h"
#include "S3DMatrix.hpp"
#include "S3DVector.hpp"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

S3DMatrix::S3DMatrix ()
:m_11 (1.0),m_21 (0.0),m_31 (0.0),
 m_12 (0.0),m_22 (1.0),m_32 (0.0),
 m_13 (0.0),m_23 (0.0),m_33 (1.0)
{
}//S3DMatrix::S3DMatrix

void S3DMatrix::RotateAboutX 
(
	double Radians
)
{
	double Sin = ::sin (Radians);
	double Cos = ::cos (Radians);

	S3DMatrix JustX;

	JustX.m_22 = Cos;
	JustX.m_32 = Sin;
	JustX.m_23 = -Sin;
	JustX.m_33 = Cos;

	(*this) = (*this) * JustX;
}//S3DMatrix::RotateAboutX

void S3DMatrix::RotateAboutY
(
	double Radians
)
{
	double Sin = ::sin (Radians);
	double Cos = ::cos (Radians);

	S3DMatrix JustY;

	JustY.m_11 = Cos;
	JustY.m_13 = -Sin;
	JustY.m_31 = Sin;
	JustY.m_33 = Cos;

	(*this) = (*this) * JustY;
}//S3DMatrix::RotateAboutY

void S3DMatrix::RotateAboutZ
(
	double Radians
)
{
	double Sin = ::sin (Radians);
	double Cos = ::cos (Radians);

	S3DMatrix JustZ;

	JustZ.m_11 = Cos;
	JustZ.m_12 = -Sin;
	JustZ.m_21 = Sin;
	JustZ.m_22 = Cos;

	(*this) = (*this) * JustZ;
}//S3DMatrix::RotateAboutZ

S3DMatrix S3DMatrix::operator * 
(
	const S3DMatrix& RVal
)const
{
	S3DMatrix RetVal;

	RetVal.m_11 = m_11 * RVal.m_11 + m_21 * RVal.m_12 + m_31 * RVal.m_13;
	RetVal.m_21 = m_11 * RVal.m_21 + m_21 * RVal.m_22 + m_31 * RVal.m_23;
	RetVal.m_31 = m_11 * RVal.m_31 + m_21 * RVal.m_32 + m_31 * RVal.m_33;

	RetVal.m_12 = m_12 * RVal.m_11 + m_22 * RVal.m_12 + m_32 * RVal.m_13;
	RetVal.m_22 = m_12 * RVal.m_21 + m_22 * RVal.m_22 + m_32 * RVal.m_23;
	RetVal.m_32 = m_12 * RVal.m_31 + m_22 * RVal.m_32 + m_32 * RVal.m_33;

	RetVal.m_13 = m_13 * RVal.m_11 + m_23 * RVal.m_12 + m_33 * RVal.m_13;
	RetVal.m_23 = m_13 * RVal.m_21 + m_23 * RVal.m_22 + m_33 * RVal.m_23;
	RetVal.m_33 = m_13 * RVal.m_31 + m_23 * RVal.m_32 + m_33 * RVal.m_33;

	return RetVal;
}//S3DMatrix::operator * 

double S3DMatrix::Determinant () const
{
	return m_11 * (m_22 * m_33 - m_23 * m_32)
		 - m_21 * (m_12 * m_33 - m_13 * m_32)
		 + m_31 * (m_12 * m_23 - m_13 * m_22);
}//S3DMatrix::Determinant

S3DMatrix S3DMatrix::operator ~ () const
{
	double Det = Determinant ();

	S3DMatrix RetVal;

	RetVal.m_11 =  (m_22 * m_33 - m_23 * m_32)/Det;
	RetVal.m_12 = -(m_12 * m_33 - m_13 * m_32)/Det;
	RetVal.m_13 =  (m_12 * m_23 - m_13 * m_22)/Det;

	RetVal.m_21 = -(m_21 * m_33 - m_31 * m_23)/Det; 
	RetVal.m_22 =  (m_11 * m_33 - m_13 * m_31)/Det;
	RetVal.m_23 = -(m_11 * m_23 - m_13 * m_21)/Det;

	RetVal.m_31 =  (m_21 * m_32 - m_22 * m_31)/Det;
	RetVal.m_32 = -(m_11 * m_32 - m_12 * m_31)/Det;
	RetVal.m_33 =  (m_11 * m_22 - m_12 * m_21)/Det;

	return RetVal;
}//S3DMatrix::operator ~

S3DVector operator * 
(
	const S3DVector& Vec,
	const S3DMatrix& Mat
)
{
	return S3DVector (Vec.m_x * Mat.m_11 + Vec.m_y * Mat.m_21 + Vec.m_z * Mat.m_31,
					  Vec.m_x * Mat.m_12 + Vec.m_y * Mat.m_22 + Vec.m_z * Mat.m_32,
					  Vec.m_x * Mat.m_13 + Vec.m_y * Mat.m_23 + Vec.m_z * Mat.m_33);
}//operator *

