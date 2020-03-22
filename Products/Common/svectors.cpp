#include "stdafx.h"
#include "SVectors.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SVector SVector::operator + 
(
	const SVector& RVal
)const
{
	return SVector (m_X + RVal.m_X,m_Y + RVal.m_Y);
}//SVector::operator +

SVector SVector::operator - 
(
	const SVector& RVal
)const
{
	return SVector (m_X - RVal.m_X,m_Y - RVal.m_Y);
}//SVector::operator - 

SVector SVector::operator - () const
{
	return SVector (-m_X,-m_Y);
}//SVector::operator -

double SVector::operator * 
(
	const SVector& RVal
)const
{
	return m_X * RVal.m_X + m_Y * RVal.m_Y;
}//SVector::operator * 

double SVector::operator ^ 
(
	const SVector& RVal
)const
{
	return m_X * RVal.m_Y - m_Y * RVal.m_X;
}//SVector::operator ^ 

SVector SVector::operator * 
(
	double RVal
)const
{
	return SVector (m_X * RVal,m_Y * RVal);
}//SVector::operator * 

SVector SVector::operator / 
(
	double RVal
)const
{
	return SVector (m_X / RVal,m_Y / RVal);
}//	SVector::operator / 

SVector SVector::ComponentAlong 
(
	const SVector& RVal
)const
{
	return RVal * ((RVal * (*this))/RVal.ModSq ());
}//SVector::ComponentAlong

SVector SVector::ComponentPerp  
(
	const SVector& RVal
)const
{
	return ComponentAlong (RVal.Perp ());
}//SVector::ComponentPerp

SVector SVector::Perp () const
{
	return SVector (-m_Y,m_X);
}//SVector::Perp

SVector SVector::Hat () const
{
	double MyMod = Mod ();

	return SVector (m_X/MyMod,m_Y/MyMod);
}//SVector::Hat

SVector SVPoint::operator - 
(
	const SVPoint& RVal
)const
{
	return SVector (m_X - RVal.m_X,m_Y - RVal.m_Y);
}//SVector::operator - 

SVPoint SVPoint::operator + 
(
	const SVector& RVal
)const
{
	return SVPoint (m_X + RVal.m_X,m_Y + RVal.m_Y);
}//SVPoint::operator + 

SVPoint SVPoint::operator - 
(
	const SVector& RVal
)const
{
	return SVPoint (m_X - RVal.m_X,m_Y - RVal.m_Y);
}//SVPoint::operator

SVLine::SVLine
(
	const SVPoint& Start,
	const SVPoint& End
)
:SVector (End - Start),
 m_Point (Start)
{
}//SVLine::SVLine

SVLine::SVLine 
(
	const SVPoint& Start,
	const SVector& Vector
)
:SVector (Vector),
 m_Point (Start)
{
}//SVLine::SVLine

bool SVLine::SameSide 
(	
	const SVPoint& A,
	const SVPoint& B
)const
{
	SVector AComp = (A - m_Point).ComponentPerp (*this);
	SVector BComp = (B - m_Point).ComponentPerp (*this);

	return AComp * BComp > 0.0;
}//SVLine::SameSide

SVLine SVLine::LineTo 
(
	const SVPoint& RVal
)const
{
	SVector PerpVect = (RVal - m_Point).ComponentPerp (*this);

	return SVLine (RVal - PerpVect,RVal);
}//SVLine::LineTo

SVPoint SVLine::MidPoint () const
{
	return m_Point + (*this)/2;
}//SVLine::MidPoint

SVLine SVectors::Bisector 
(
	const SVPoint& A,
	const SVPoint& B
)
{
	SVLine AB (A,B);

	return SVLine (AB.MidPoint (),AB.Perp ());
}//SVectors::Bisector
