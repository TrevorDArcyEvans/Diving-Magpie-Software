#include "stdafx.h"
#include "SGeometricAlgorithms.hpp"
#include <afxwin.h>
#include "SVectors.hpp"

bool SGeometricAlgorithms::FillContains 
(
	const CPoint&	Point,
	const CPoint*	Fillarea,
	int				FillSize
)
{
//	Imaginary line going up from point. Count number of crosses. Blah, blah blah.
	int Crosses = 0;

	int From;
	int To = FillSize - 1;

	for (int i = 0; i < FillSize; i++)
	{
		From = To;
		To = i;
		
		if (((Fillarea[From].x <= Point.x) && (Fillarea[To].x > Point.x))
		 || ((Fillarea[From].x > Point.x) && (Fillarea[To].x <= Point.x)))
		{
			if ((Fillarea[From].y <= Point.y) && (Fillarea[To].y <= Point.y))
				Crosses++;
			else if (((Fillarea[From].y <= Point.y) && (Fillarea[To].y > Point.y))
				  || ((Fillarea[From].y >= Point.y) && (Fillarea[To].y < Point.y)))
			{
				double Along = ((double)Point.x - Fillarea[From].x)/(Fillarea[To].x - Fillarea[From].x);

				int LineYAtMyX = Fillarea[From].y + (Fillarea[To].y - Fillarea[From].y) * Along;

				if (LineYAtMyX <= Point.y)
					Crosses++;
				//if
			}//if
		}//if
	}//for

	if (Crosses & 1)
		return true;
	else
		return false;
	//if
}//SGeometricAlgorithms::FillContains

bool SGeometricAlgorithms::LineContains 
(
	const CPoint&	Point,
	const CPoint*	Polyline,
	int				LineSize,
	short			LineWidth
)
{
	double Wid = max (1.2,LineWidth);

	for (int i = 1; i < LineSize; i++)
	{
		SVector BP (Point.x - Polyline[i - 1].x,Point.y - Polyline[i - 1].y);

		SVector BA (Polyline[i].x - Polyline[i - 1].x,Polyline[i].y - Polyline[i - 1].y);

		double MagBA = BA.Mod ();

		double h = abs ((BA ^ BP)/MagBA);	// Perpendicular distance of point from line

		if (h < Wid)
		{
			double o = (BP * BA)/MagBA;		// Distance of point alonmg the line

			if (o > -Wid && o < (MagBA + Wid))
				return true;
			//if
		}//if
	}//for

	return false;
}//SGeometricAlgorithms::LineContains


