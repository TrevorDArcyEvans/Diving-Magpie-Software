#ifndef __SUseful_hpp
#define __SUseful_hpp

#include <afxtempl.h>

class SUseful
{
public:

	static int MinOf (int p1,int p2,int p3, int p4);
	static bool CloseEnoughFract (double L,double R,double FractAllowed = 0.01);
	static bool CloseEnoughAbs   (double L,double R,double Lemen);
	static double HeadingDegToRotationRad (double Degrees);
};//SUseful

typedef CArray <double,const double&> SDoubleArrayBase;

class SDoubleArray:public SDoubleArrayBase
{
public:

	SDoubleArray () {}
	SDoubleArray (const SDoubleArray& RVal);
	SDoubleArray& operator = (const SDoubleArray& RVal);
	bool operator != (const SDoubleArray& RVal) const;
	void Sort ();
};//SDoubleArray

typedef CArray <short,short> SShortArray;

#endif

