#include "stdafx.h"
#include "SLongitude.hpp"
#include "SException.hpp"
#include <math.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static double Normalize (double Val)
{
	if (::_isnan (Val))
		throw new SException (_T ("Bad angle"));
	//if

	while (Val > 180.0)
		Val -= 360.0;
	//while

	while (Val <= -180.0)
		Val += 360.0;
	//while

	return Val;
}//Normalize

SLongitude::operator double () const
{
	return Normalize (m_Value);
}//SLongitude::operator

SLongitude& SLongitude::operator = 
(
	const SLongitude& RVal
)
{
	m_Value = RVal.m_Value;

	return *this;
}//SLongitude::operator = 

bool SLongitude::operator == 
(
	const SLongitude& RVal
)const
{
	return Normalize (m_Value) == Normalize (RVal.m_Value);
}//SLongitude::operator ==

SLongitude SLongitude::operator + 
(
	const SLongitudeDelta& RVal
)const
{
	return SLongitude (m_Value + RVal.m_Value);
}//SLongitude::operator +

SLongitude& SLongitude::operator += 
(
	const SLongitudeDelta& RVal
)
{
	m_Value += RVal.m_Value;

	return *this;
}//SLongitude::operator +=

SLongitude SLongitude::operator - () const
{
	return SLongitude (-m_Value);
}//SLongitude::operator -

SLongitude SLongitude::operator - 
(
	const SLongitudeDelta& RVal
)const
{
	return SLongitude (m_Value - RVal.m_Value);
}//SLongitude::operator -

SLongitude& SLongitude::operator -= 
(
	const SLongitudeDelta& RVal
)
{
	m_Value -= RVal.m_Value;

	return *this;
}//SLongitude::operator -=

SLongitudeDelta SLongitude::operator - 
(
	const SLongitude& RVal
)const
{
	double Diff = Normalize (m_Value) - Normalize (RVal.m_Value);

	if (fabs (Diff) <= 180.0)
		return SLongitudeDelta (Diff);
	else if (Diff < 0)
		return SLongitudeDelta (Diff + 360.0);
	else
		return SLongitudeDelta (Diff - 360.0);
	//if
}//SLongitude::operator -

SLongitudeDelta SLongitude::Separation 
(
	const SLongitude&		To,
	const SLongitudeDelta&	Direction
)const
{
	SLongitudeDelta RetVal = (*this) - To;

//	If they have the same sign
	if ((RetVal.m_Value * Direction.m_Value) >= 0.0)
		return RetVal;
	else if (RetVal > 0.0)
		return RetVal - SLongitudeDelta (360.0);
	else 
		return RetVal + SLongitudeDelta (360.0);
	//if
}//SLongitude::Separation

bool SLongitude::Between 
(
	const SLongitude& Start,
	const SLongitude& Finish
)const
{
	return Between (Start,Finish,Finish - Start);
}//SLongitude::Between

bool SLongitude::Between 
(
	const SLongitude&		Start,
	const SLongitude&		Finish,
	const SLongitudeDelta&	Direction,
	bool					Inclusive
)const
{
	if (Start == Finish)
		return Inclusive && (Start == (*this));
	//if

	if (Direction.m_Value == 0.0)
		throw new SException (_T ("SLongitude::Between requires non-zero direction."));
	//if

	double ds ;
	double df;
	double me = Normalize (m_Value);

	if (Direction.m_Value > 0.0)
	{
		ds = Start;
		df = Finish;
	}
	else
	{
		ds = Finish;
		df = Start;
	}//if

	if (df < ds)
		df += 360.0;
	//if
	
	if (Inclusive)
	{
		if (me < ds)
			me += 360.0;
		//if

		return me <= df;
	}
	else
	{
		if (me <= ds)
			me += 360.0;
		//if

		return me < df;
	}//if
}//SLongitude::Between

SLongitude SLongitude::Midway 
(
	const SLongitude&	RVal,
	bool				Shortest
)const
{
	if (Shortest)
		return *this + (RVal.Separation (*this,RVal - *this))/2;
	else
		return *this + (RVal.Separation (*this,1.0))/2;
	//if
}//SLongitude::Midway

SLongitudeDelta::operator double () const
{
	return m_Value;
}//SLongitudeDelta::operator double ()

SLongitudeDelta& SLongitudeDelta::operator = 
(
	const SLongitudeDelta& RVal
)
{
	m_Value = RVal.m_Value;

	return *this;
}//SLongitudeDelta::operator =

bool SLongitudeDelta::operator == 
(
	const SLongitudeDelta& RVal
)const
{
	return Normalize (m_Value) == Normalize (RVal.m_Value);
}//SLongitudeDelta::operator ==

SLongitudeDelta SLongitudeDelta::operator + 
(
	const SLongitudeDelta& RVal
)const
{
	return SLongitudeDelta (m_Value + RVal.m_Value);
}//SLongitudeDelta::operator +

SLongitudeDelta& SLongitudeDelta::operator += 
(
	const SLongitudeDelta& RVal
)
{	
	m_Value += RVal.m_Value;

	return *this;
}//SLongitudeDelta::operator +=

SLongitudeDelta SLongitudeDelta::operator - () const
{
	return SLongitudeDelta (-m_Value);
}//SLongitudeDelta::operator -

SLongitudeDelta SLongitudeDelta::operator - 
(
	const SLongitudeDelta& RVal
)const
{
	return SLongitudeDelta (m_Value - RVal.m_Value);
}//SLongitudeDelta::operator -


SLongitudeDelta& SLongitudeDelta::operator -= 
(
	const SLongitudeDelta& RVal
)
{	
	m_Value -= RVal.m_Value;

	return *this;
}//SLongitudeDelta::operator -=

SLongitudeDelta SLongitudeDelta::operator * 
(
	double RVal
)const
{
	return SLongitudeDelta (m_Value * RVal);
}//SLongitudeDelta::operator * 

SLongitudeDelta SLongitudeDelta::operator /
(
	double RVal
)const
{
	return SLongitudeDelta (m_Value/RVal);
}//SLongitudeDelta::operator /

SLongitudeDelta SLongitudeDelta::operator * 
(
	int RVal
)const
{
	return SLongitudeDelta (m_Value * RVal);
}//SLongitudeDelta::operator * 

SLongitudeDelta SLongitudeDelta::operator /
(
	int RVal
)const
{
	return SLongitudeDelta (m_Value/RVal);
}//SLongitudeDelta::operator /

double SLongitudeDelta::operator /
(
	const SLongitudeDelta& RVal
)const
{
	return m_Value/RVal.m_Value;
}//SLongitudeDelta::operator /

