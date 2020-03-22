#ifndef __SMatrix_hpp
#define __SMatrix_hpp

#include "SPoints.hpp"

class SMatrix
{
protected:

	double	m_M11;
	double	m_M12;
	double	m_M21;
	double	m_M22;

	int		m_dX;
	int		m_dY;

	bool	m_Pinned;

public:

	SMatrix (double	M11 = 1.0,
			 double	M12 = 0.0,
			 double	M21 = 0.0,
			 double	M22 = 1.0,
			 int	dX  = 0,
			 int	dY  = 0):m_M11 (M11),m_M12 (M12),m_M21 (M21),m_M22 (M22),m_dX (dX), m_dY (dY), m_Pinned (false) {}

	CPoint				WorldToPaper (const SFlatWorldPoint& Point) const;
	SPaperBox			WorldToPaper (const SFlatWorldBox& Box) const;
	SLargeRangePoint	LargeRangeWorldToPaper (const SFlatWorldPoint& Point) const;
	SFlatWorldPoint		PaperToWorld (const CPoint& Point) const;
	SFlatWorldBox		PaperToWorld (const SPaperBox& Box) const;

	SFlatWorldBox		WorldToWorld (const SFlatWorldBox& Box) const;
	SFlatWorldPoint		WorldToWorld (const SFlatWorldPoint& Point) const;

	void Reset ();

	void Offset (int dX,int dY);

	void Zoom   (double Factor,const CPoint& CentreOn);
	void Zoom   (double Factor,const SFlatWorldPoint& CentreOn = SFlatWorldPoint (0.0,0.0));

	void Rotate (double Radians,const CPoint& CentreOn);
	void Rotate (double Radians,const SFlatWorldPoint& CentreOn = SFlatWorldPoint (0.0,0.0));

	SMatrix& operator *= (const SMatrix& RVal);

	double GetPaperPerWorld () const;
	void   SetPaperPerWorld (double Factor);

	double GetAbsoluteZoom () const;
	double GetAbsoluteRotation () const;

	void Align (const SFlatWorldPoint& WorldPoint,const CPoint& PaperPoint);
	void AlignUpwards (const CPoint& CentreOn,double Bearing);

	bool Pin ();
	bool Unpin ();

	void Get (double& M11,double& M12,double& M21,double& M22,long& dx,long& dy) const;
	void Set (double M11,double M12,double M21,double M22,long dx,long dy);

	bool OnlyShiftDifferent (const SMatrix& RVal) const;
	int DeltaX (const SMatrix& RVal) const;
	int DeltaY (const SMatrix& RVal) const;
};//SMatrix

#endif

