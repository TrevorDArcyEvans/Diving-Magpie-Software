#include "stdafx.h"
#include <math.h>
#include "SMatrix.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SMatrix::Reset ()
{
	(*this) = SMatrix ();
}//SMatrix::Reset

bool SMatrix::Pin ()
{
	bool RetVal = m_Pinned;

	m_Pinned = true;

	return RetVal;
}//SMatrix::Pin

bool SMatrix::Unpin ()
{
	bool RetVal = m_Pinned;

	m_Pinned = false;

	return RetVal;
}//SMatrix::Unpin

void SMatrix::Get 
(
	double& M11,
	double& M12,
	double& M21,
	double& M22,
	long&   dx,
	long&   dy
)const
{
	M11 = m_M11;
	M12 = m_M12;
	M21 = m_M21;
	M22 = m_M22;

	dx  = m_dX;
	dy  = m_dY;
}//SMatrix::Get

void SMatrix::Set 
(
	double M11,
	double M12,
	double M21,
	double M22,
	long   dx,
	long   dy
)
{
	m_M11 = M11;
	m_M12 = M12;
	m_M21 = M21;
	m_M22 = M22;

	m_dX  = dx;
	m_dY  = dy;

	m_Pinned = false;
}//SMatrix::Set

CPoint SMatrix::WorldToPaper 
(
	const SFlatWorldPoint& Point
)const
{
	long x = (long)(Point.m_X * m_M11 + Point.m_Y * m_M12) + m_dX;
	long y = -(long)(Point.m_X * m_M21 + Point.m_Y * m_M22) - m_dY;
	
	CPoint RetVal;

	if (x > 32000)
		RetVal.x = 32000;
	else if (x < -32000)
		RetVal.x = -32000;
	else
		RetVal.x = x;
	//if

	if (y > 32000)
		RetVal.y = 32000;
	else if (x < -32000)
		RetVal.y = -32000;
	else
		RetVal.y = y;
	//if

	return RetVal;
}//SMatrix::WorldToPaper

SPaperBox SMatrix::WorldToPaper 
(
	const SFlatWorldBox& Box
)const
{
	CPoint TL (WorldToPaper (Box.TL ()));
	CPoint BR (WorldToPaper (Box.BR ()));

	return SPaperBox (TL.x,TL.y,BR.x,BR.y);
}//SMatrix::WorldToPaper

SFlatWorldBox SMatrix::WorldToWorld 
(
	const SFlatWorldBox& Box
)const
{
	return SFlatWorldBox (WorldToWorld (Box.TL ()),WorldToWorld (Box.BR ()));
}//SMatrix::WorldToWorld

SFlatWorldPoint	SMatrix::WorldToWorld 
(
	const SFlatWorldPoint& Point
)const
{
	SFlatWorldPoint RetVal;

	RetVal.m_X = (Point.m_X * m_M11 + Point.m_Y * m_M12) + m_dX;
	RetVal.m_Y = -(long)(Point.m_X * m_M21 + Point.m_Y * m_M22) - m_dY;
	
	return RetVal;
}//SMatrix::WorldToWorld

SLargeRangePoint SMatrix::LargeRangeWorldToPaper 
(
	const SFlatWorldPoint& Point
)const
{
	SLargeRangePoint RetVal;

	RetVal.m_X = (long)(Point.m_X * m_M11 + Point.m_Y * m_M12) + m_dX;
	RetVal.m_Y = -(long)(Point.m_X * m_M21 + Point.m_Y * m_M22) - m_dY;
	
	return RetVal;
}//SMatrix::LargeRangeWorldToPaper

SFlatWorldPoint SMatrix::PaperToWorld
(
	const CPoint& Point
)const
{
	SFlatWorldPoint RetVal;

	double Denom = m_M12 * m_M21 - m_M11 * m_M22;
	long   TrlX  =  Point.x - m_dX;
	long   TrlY  = -Point.y - m_dY;

	RetVal.m_X = (TrlY * m_M12 - TrlX * m_M22)/Denom;
	RetVal.m_Y = (TrlX * m_M21 - TrlY * m_M11)/Denom;

	return RetVal;
}//SMatrix::PaperToWorld

SFlatWorldBox SMatrix::PaperToWorld
(
	const SPaperBox& Box
)const
{
	SFlatWorldBox RetVal;

	RetVal.Fit (PaperToWorld (Box.TL ()));
	RetVal.Fit (PaperToWorld (Box.TR ()));
	RetVal.Fit (PaperToWorld (Box.BL ()));
	RetVal.Fit (PaperToWorld (Box.BR ()));
	
	return RetVal;
}//SMatrix::PaperToWorld

void SMatrix::Offset 
(
	int dX,
	int dY
)
{
	m_dX += dX;
	m_dY += dY;

	m_Pinned = false;
}//SMatrix::Offset

double SMatrix::GetAbsoluteZoom () const
{
	double AB = m_M11 + m_M12;
	double CD = m_M21 + m_M22;

	return sqrt (((AB * AB) + (CD * CD))/2.0);
}//SMatrix::GetAbsoluteZoom

void SMatrix::Zoom
(
	double					Factor,
	const SFlatWorldPoint&	CentreOn
)
{
//	Where the fixed point went before the zoom
	CPoint OldCentre = WorldToPaper (CentreOn);

	m_M11 *= Factor;
	m_M12 *= Factor;
	m_M21 *= Factor;
	m_M22 *= Factor;

//	Where the fixed point went after the zoom
	SLargeRangePoint NewCentre = LargeRangeWorldToPaper (CentreOn);

//	Translate to keep the fixed point in the same place
	m_dX += OldCentre.x - NewCentre.m_X;
	m_dY -= OldCentre.y - NewCentre.m_Y;

	m_Pinned = false;
}//SMatrix::Zoom

void SMatrix::Zoom   
(
	double	Factor,
	const	CPoint& CentreOn
)
{
//	Centre on the world point that this paper point represents
	Zoom (Factor,PaperToWorld (CentreOn));
}//SMatrix::Zoom

SMatrix& SMatrix::operator *= 
(
	const SMatrix& RVal
)
{
	double OM11 = m_M11;
	double OM12 = m_M12;
	double OM21 = m_M21;
	double OM22 = m_M22;

	m_M11 = RVal.m_M11 * OM11 + RVal.m_M12 * OM21;
	m_M12 = RVal.m_M11 * OM12 + RVal.m_M12 * OM22;
	m_M21 = RVal.m_M11 * OM21 + RVal.m_M21 * OM22;
	m_M22 = RVal.m_M12 * OM21 + RVal.m_M22 * OM22;

	return *this;
}//SMatrix::operator *=

void SMatrix::Rotate 
(
	double		  Radians,
	const CPoint& CentreOn
)
{
	Rotate (Radians,PaperToWorld (CentreOn));
}//SMatrix::Rotate

void SMatrix::Rotate 
(
	double					Radians,
	const SFlatWorldPoint&	CentreOn
)
{
//	Where the fixed point went before the rotate
	CPoint OldCentre = WorldToPaper (CentreOn);

	SMatrix RotMat (cos (Radians),sin (Radians),-sin (Radians),cos (Radians));

	(*this) *= RotMat;

//	Where the fixed point went after the zoom
	SLargeRangePoint NewCentre = LargeRangeWorldToPaper (CentreOn);

//	Translate to keep the fixed point in the same place
	m_dX += OldCentre.x - NewCentre.m_X;
	m_dY -= OldCentre.y - NewCentre.m_Y;

	m_Pinned = false;
}//SMatrix::Rotate

double SMatrix::GetAbsoluteRotation () const
{
	return atan2 (m_M21,m_M11);
}//SMatrix::GetAbsoluteRotation

double SMatrix::GetPaperPerWorld () const
{
	return sqrt ((m_M11 * m_M11) + (m_M21 * m_M21));
}//SMatrix::GetPaperPerWorld

void SMatrix::SetPaperPerWorld
(
	double Factor
)
{
	Zoom (Factor/GetPaperPerWorld ());

	m_Pinned = false;
}//SMatrix::SetPaperPerWorld

void SMatrix::Align 
(
	const SFlatWorldPoint&	WorldPoint,
	const CPoint&			PaperPoint
)
{
	SLargeRangePoint WrongPoint = LargeRangeWorldToPaper (WorldPoint);

	m_dX -= WrongPoint.m_X - PaperPoint.x;
	m_dY += WrongPoint.m_Y - PaperPoint.y;

	m_Pinned = false;
}//SMatrix::Align 

bool SMatrix::OnlyShiftDifferent 
(
	const SMatrix& RVal
)const
{
	return (m_M11 == RVal.m_M11)
	    && (m_M12 == RVal.m_M12)
		&& (m_M21 == RVal.m_M21)
		&& (m_M22 == RVal.m_M22)
		&& ((m_dX != RVal.m_dX) || (m_dY != RVal.m_dY));
}//SMatrix::OnlyShiftDifferent

int SMatrix::DeltaX 
(
	const SMatrix& RVal
)const
{
	return m_dX - RVal.m_dX;
}//SMatrix::DeltaX

int SMatrix::DeltaY 
(
	const SMatrix& RVal
)const
{
	return m_dY - RVal.m_dY;
}//SMatrix::DeltaY




