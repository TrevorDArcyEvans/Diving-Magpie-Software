#include "stdafx.h"
#include "SUseful.hpp"
#include "SGeometricConstants.hpp"
#include <stdlib.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int SUseful::MinOf 
(
	int p1,
	int p2,
	int p3,
	int p4
)
{
	int TheMin = __min (p1,__min (p2,__min (p3,p4)));

	if (TheMin == p1)
		return 0;
	else if (TheMin == p2)
		return 1;
	else if (TheMin == p3)
		return 2;
	else 
		return 3;
	//if
}//SUseful::MinOf

bool SUseful::CloseEnoughFract
(
	double L,
	double R,
	double FractAllowed
)
{
	return fabs (R - L) <= fabs ((L + R) * FractAllowed);
}//SUseful::CloseEnoughFract

bool SUseful::CloseEnoughAbs
(
	double L,
	double R,
	double Lemen
)
{
	return fabs (R - L) <= Lemen;
}//SUseful::CloseEnoughAbs

double SUseful::HeadingDegToRotationRad 
(
	double Degrees
)
{
//	Go to anticlockwise from three o'clock
	Degrees = 90 - Degrees;

//	Get in 0-360
	while (Degrees >= 360)
		Degrees -= 360;
	//while

	while (Degrees < 0)
		Degrees += 360;
	//while

//	Convert to radians
	return Degrees * RADIANS_PER_DEGREE;
}//SUseful::HeadingDegToRotationRad

SDoubleArray::SDoubleArray 
(
	const SDoubleArray& RVal
)
{
	Copy (RVal);
}//SDoubleArray::SDoubleArray

SDoubleArray& SDoubleArray::operator = 
(
	const SDoubleArray& RVal
)
{
	Copy (RVal);
	return *this;
}//SDoubleArray::operator =

bool SDoubleArray::operator != 
(	
	const SDoubleArray& RVal
)const
{
	if (GetSize () != RVal.GetSize ())
		return true;
	//if

	for (int i = 0; i < GetSize (); i++)
	{
		if (GetAt (i) != RVal.GetAt (i))
			return true;
		//if
	}//for

	return true;
}//SDoubleArray::operator != 

void SDoubleArray::Sort ()
{
	bool Changed = true;

	while (Changed)
	{
		Changed = false;

		for (int i = 1; i < GetSize (); i++)
		{
			if (GetAt (i - 1) > GetAt (i))
			{
				double Temp = GetAt (i);
				SetAt (i,GetAt (i - 1));
				SetAt (i - 1,Temp);

				Changed = true;
			}//if
		}//for
	}//while
}//SDoubleArray::Sort



