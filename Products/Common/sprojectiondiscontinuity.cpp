#include "stdafx.h"
#include "SProjectionDiscontinuity.hpp"
#include "SPoints.hpp"
#include "SPositions.hpp"
#include "SPolylinePrimitive.hpp"
#include "SFillareaPrimitive.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool SProjectionDiscontinuity::operator == 
(
	const SProjectionDiscontinuity& RVal
)const
{
//	This will do as long as all discontinuities are created static
	return this == &RVal;
}//SProjectionDiscontinuity::operator == 

SParallelBoundInvalidRegion::SParallelBoundInvalidRegion 
(
	double Min,
	double Max
)
{
	if (Min <= -90.0)
		m_Box.SetSPCover (Max);
	else if (Max >= 90.0)
		m_Box.SetNPCover (Min);
	else
		m_Box.SetAllLongCover (Min,Max);
	//if
}//SParallelBoundInvalidRegion::SParallelBoundInvalidRegion

bool SParallelBoundInvalidRegion::AnyEffect 
(
	const SGlobalBox& Box
)const 
{
	return false;
}//SParallelBoundInvalidRegion::AnyEffect

bool SParallelBoundInvalidRegion::EntirelyContains 
(
	const SGlobalBox& Box
)const
{
	return m_Box.EntirelyContains (Box);
}//SParallelBoundInvalidRegion::EntirelyContains

bool SMeridianSplit::AnyEffect 
(
	const SGlobalBox& Box
)const
{
	return !Box.Valid ()
		|| Box.IncludesMeridian (m_SplitAt,false)
		|| Box.TouchesRight (m_SplitAt)
		|| Box.TouchesLeft (m_SplitAt);
}//SMeridianSplit::AnyEffect

void SMeridianSplit::Split 
(
	SPointsPrimitive* Primitive
)const
{
	bool WasFixed = Primitive->PositionFixed ();

	Primitive->SetPositionFixed (false);
	
	SPositionList& Points = Primitive->Points ();

	if (Primitive->GlobalBoundingBox ().CoversAllLong ())
	{
		SLongitudeDelta Delta;

		for (int i = 0; i < Points.GetSize (); i++)
		{
			SGlobalPoint Pt = Points.GetGlobalPoint (i);

			if (Pt.m_Long != m_SplitAt)
			{
				if ((Pt.m_Long - m_SplitAt) > 0.0)
					Delta = 0.0001;
				else
					Delta = -0.0001;
				//if

				break;
			}
		}//for

		for (i = 0; i < Points.GetSize (); i++)
		{
			SGlobalPoint Pt = Points.GetGlobalPoint (i);

			if (Pt.m_Long == m_SplitAt)
				Points.SetGlobalPoint (i,Pt.m_Lat,Pt.m_Long + Delta);
			else
			{
				if ((Pt.m_Long - m_SplitAt) > 0.0)
					Delta = 0.0001;
				else
					Delta = -0.0001;
				//if
			}//if
		}//for
	}
	else if (Primitive->GlobalBoundingBox ().TouchesRight (m_SplitAt))
	{
		for (int i = 0; i < Points.GetSize (); i++)
		{
			SGlobalPoint Pt = Points.GetGlobalPoint (i);

			if (Pt.m_Long == m_SplitAt)
				Points.SetGlobalPoint (i,Pt.m_Lat,Pt.m_Long - SLongitudeDelta (0.0001));
			//if
		}//for

		Primitive->CalcBoundingBox ();
	}
	else if (Primitive->GlobalBoundingBox ().TouchesLeft (m_SplitAt))
	{
		for (int i = 0; i < Points.GetSize (); i++)
		{
			SGlobalPoint Pt = Points.GetGlobalPoint (i);

			if (Pt.m_Long == m_SplitAt)
				Points.SetGlobalPoint (i,Pt.m_Lat,Pt.m_Long + SLongitudeDelta (0.0001));
			//if
		}//for

		Primitive->CalcBoundingBox ();
	}//if

	SPolylinePrimitive* Poly = dynamic_cast <SPolylinePrimitive*> (Primitive);
	SFillareaPrimitive* Fill = dynamic_cast <SFillareaPrimitive*> (Primitive);

	if (Points.GetSegments ().GetSize () == 0)
	{
		if (Poly)
			SplitPolyline (Points,0,Points.GetSize () - 1);
		else if (Fill)
			SplitFillarea (Fill,0,Points.GetSize () - 1);
		//if
	}
	else
	{
		for (int i = 0; i < Points.GetSegments ().GetSize (); i++)
		{
			if (Poly)
				SplitPolyline (Points,Points.GetSegments ()[i].m_Start,Points.GetSegments ()[i].m_End);
			else if (Fill)
				SplitFillarea (Fill,Points.GetSegments ()[i].m_Start,Points.GetSegments ()[i].m_End);
			//if
		}//for
	}//if

	Primitive->SetPositionFixed (WasFixed);
}//SMeridianSplit::Split

void SMeridianSplit::SplitPolyline 
(
	SPositionList&	Points,
	int				First,
	int				Last
)const
{
	for (int i = First + 1; i <= Last; i++)
	{
		SGlobalPoint PM1 = Points.GetGlobalPoint (i - 1);
		SGlobalPoint P   = Points.GetGlobalPoint (i);

		int NewStart = -1;

		if (P.m_Long == m_SplitAt) 
			NewStart = 1;		// Don't need the old point
		else if (m_SplitAt.Between (PM1.m_Long,P.m_Long))
			NewStart = 0;		// Use the old point in the new lines
		//if

		if (NewStart > -1)
		{
			SGlobalPoint PointL = PM1.InterpolateOnLong (P,m_SplitAt - SLongitudeDelta (0.0001));
			SGlobalPoint PointR = PM1.InterpolateOnLong (P,m_SplitAt + SLongitudeDelta (0.0001));

			bool LeftInOld = PointL.m_Long.Between (PM1.m_Long,m_SplitAt);

			if (NewStart == 1)
			{
				Points.SetGlobalPoint (i,PointL);

				if (LeftInOld)
				{
					Points.InsertGlobalPointAfter (i,PointR);
					Points.SplitAfter (i);
				}
				else
				{
					Points.InsertGlobalPointBefore (i,PointR);
					Points.SplitAfter (i);
				}//if

				i += 1;
			}
			else
			{
				if (LeftInOld)
				{
					Points.InsertGlobalPointAfter (i - 1,PointR);
					Points.InsertGlobalPointAfter (i - 1,PointL);
				}
				else
				{
					Points.InsertGlobalPointAfter (i - 1,PointL);
					Points.InsertGlobalPointAfter (i - 1,PointR);
				}//if

				Points.SplitAfter (i);

				i += 2;
			}//if
		}//if
	}//for
}//SMeridianSplit::SplitPolyline

void SMeridianSplit::SplitFillarea 
(
	SFillareaPrimitive*		Fillarea,
	int				First,
	int				Last
)const
{
//	This may need implementing later
/*	
	Fillarea->MakeCountAnticlockwise ();

	SPositionList& Points = Fillarea->Points ();

	int Northest = -1;
	int NextNorthest = -1;

	double NorthestLat = -100.0;
	double NextNorthestLat = -100.0;

	for (int i = 1; i < Points.GetSize (); i++)
	{
		SGlobalPosition* PM1 = dynamic_cast <SGlobalPosition*> (Points[i - 1]);
		SGlobalPosition* P = dynamic_cast <SGlobalPosition*> (Points[i]);

		if ((P->Get ().m_Long == m_SplitAt) || (m_SplitAt.Between (PM1->Get ().m_Long,P->Get ().m_Long)))
		{
			if (P->Get ().m_Lat > NextNorthestLat)
			{
				if (P->Get ().m_Lat > NorthestLat)
				{
					NextNorthest = Northest;
					NextNorthestLat = NorthestLat;

					Northest = i;
					NorthestLat = P->Get ().m_Lat;
				}
				else
				{
					NextNorthest = i;
					NextNorthestLat = P->Get ().m_Lat;
				}//if
			}//if
		}//if
	}//for

	if (Northest >=0 && NextNorthest >= 0)
	{
		int First  = min (Northest,NextNorthest);
		int Second = max (Northest,NextNorthest);

		SGlobalPosition* PF = dynamic_cast <SGlobalPosition*> (Points[First]);

		SGlobalPoint FirstPointL;
		SGlobalPoint FirstPointR;

		bool FirstOn;

		if (PF->Get ().m_Long == m_SplitAt)
		{
			FirstPointL = FirstPointR = PF->Get ();
			FirstPointL.m_Long -= SLongitudeDelta (0.0001);
			FirstPointR.m_Long -= SLongitudeDelta (0.0001);
			FirstOn = true;
		}
		else
		{
			SGlobalPosition* PFM1 = dynamic_cast <SGlobalPosition*> (Points[First - 1]);

			FirstPointL = PFM1->Get ().InterpolateOnLong (PF->Get (),m_SplitAt - SLongitudeDelta (0.0001));
			FirstPointR = PFM1->Get ().InterpolateOnLong (PF->Get (),m_SplitAt + SLongitudeDelta (0.0001));
			FirstOn = false;
		}//if

		SGlobalPosition* PS = dynamic_cast <SGlobalPosition*> (Points[Second]);

		SGlobalPoint SecondPointL;
		SGlobalPoint SecondPointR;

		bool SecondOn;

		if (PS->Get ().m_Long == m_SplitAt)
		{
			SecondPointL = SecondPointR = PS->Get ();
			SecondPointL.m_Long -= SLongitudeDelta (0.0001);
			SecondPointR.m_Long -= SLongitudeDelta (0.0001);
			SecondOn = true;
		}
		else
		{
			SGlobalPosition* PSM1 = dynamic_cast <SGlobalPosition*> (Points[Second - 1]);

			SecondPointL = PSM1->Get ().InterpolateOnLong (PS->Get (),m_SplitAt - SLongitudeDelta (0.0001));
			SecondPointR = PSM1->Get ().InterpolateOnLong (PS->Get (),m_SplitAt + SLongitudeDelta (0.0001));
			SecondOn= false;
		}//if

		SFillareaPrimitive* NewFill = (SFillareaPrimitive*)Fillarea->Clone (false);

		bool OldOnLeft = (dynamic_cast <SGlobalPosition*> (Points[0]))->Get ().m_Long < m_SplitAt;

		NewFill->Points ().AddPosition (OldOnLeft?FirstPointR:FirstPointL);

		int js = FirstOn?(First + 1):First;
		int jf = SecondOn?Second:(Second - 1);

		for (int j = js; j <= jf;j++)
		{
			NewFill->Points ().AddPosition (Points[j],false);
			Points.ForgetPoint (j);
		}//for

		NewFill->Points ().AddPosition (OldOnLeft?SecondPointR:SecondPointL);

		SFullPositionList Insertions;

		if (!OldOnLeft)
		{
			Insertions.AddPosition (FirstPointL);
			Insertions.AddPosition (SecondPointL);
		}
		else
		{
			Insertions.AddPosition (FirstPointR);
			Insertions.AddPosition (SecondPointR);
		}//if

		Points.ReplaceRange (First,Second,Insertions,false,false);

		Insertions.Forget ();

		Fillarea->Points () = NewFill->Points ();

		Fillarea->CalcBoundingBox ();

		delete NewFill;
	}//if
*/
}//SMeridianSplit::SplitFillarea

			
			
