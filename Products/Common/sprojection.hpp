#ifndef __SProjection_hpp
#define __SProjection_hpp

#include "SMatrix.hpp"
#include "SPoints.hpp"
#include "SVirtualConstructor.hpp"
#include "SGlobalBox.hpp"
//#include "SPositions.hpp"
#include "SXYPosition.hpp"
#include "SNeutralBox.hpp"

class SProjectionDiscontinuity;

class SProjection
{
DECLARE_VIRTUAL_CONSTRUCTOR_BASE

private:

	SProjection*	m_Previous;
	SProjection*	m_LastUsed;

	bool			m_NoMatrixChange;	// The matirx has not changed since the last draw

	CRect			m_ScreenRect;

protected:

	SMatrix		m_Matrix;

	virtual void DoSetMatrix (const SMatrix& Matrix) {}

	virtual double GetPaperUnitsPerDegreeLat (const SGlobalPoint& Locality) const;
	virtual void   SetPaperUnitsPerDegreeLat (const SGlobalPoint& Locality,double Ratio);

public:

	SProjection ():m_Previous (0),m_LastUsed (0),m_NoMatrixChange (false) {}
	SProjection (const SProjection& RVal);
	virtual ~SProjection ();

	const CRect& ScreenRect () const {return m_ScreenRect;}
	CRect& ScreenRect ()  {return m_ScreenRect;}

	bool NoMatrixChange () const {return m_NoMatrixChange;}
	bool SetNoMatrixChange (bool Set) {bool RetVal = m_NoMatrixChange; m_NoMatrixChange = Set; return RetVal;}

	bool		 PreviousAvailable () const {return m_Previous;}
	SProjection* RevertToPrevious  ();

	virtual CString GetDisplayName () const = 0;

	virtual SProjection* Clone () const = 0;

	virtual double GetFullWorldAspRat () const = 0;

	virtual double GetFiltrationSepSqDeg () const = 0;

	virtual SFlatWorldPoint	GlobalToPlane	(const SGlobalPoint&	Point) const = 0;
	virtual SFlatWorldPoint	GlobalToPlane	(double Lat,double Long) const;
	virtual CPoint			GlobalToPaper	(const SGlobalPoint&	Point) const;
	virtual CPoint			GlobalToPaper	(double Lat,double Long) const;

	virtual CPoint			GenericToPaper  (const SXYPoint& Point) const = 0;
	virtual SPaperBox		GenericToPaper  (const SNeutralBox& Box) const = 0;
	virtual SFlatWorldPoint	GenericToPlane  (const SXYPoint& Point) const = 0;
	virtual SXYPoint		PaperToGeneric  (const CPoint&   Point) const = 0;

	virtual SPaperBox		GlobalToPaper	(const SGlobalBox&		Box) const;

	virtual SGlobalPoint	PlaneToGlobal	(const SFlatWorldPoint& Point) const = 0;
	virtual SGlobalPoint	PaperToGlobal	(const CPoint&			Point) const;

	virtual SPosition*		PaperToNatural	(const CPoint&			Point) const {return new SGlobalPosition (PaperToGlobal (Point));}
	virtual SFlatWorldPoint	NaturalToPlane	(const SPosition*	Position) const;

	virtual SGlobalBox		PlaneToGlobalBox(const SFlatWorldBox&	Box) const = 0;
	virtual SGlobalBox		PaperToGlobal	(const SPaperBox&		Box) const;

	virtual double GetProjectedNorth (const SGlobalPoint& At) const = 0;

	virtual double MetresPerDegreeLong (const SGlobalPoint& Locality) const;
	virtual double MetresPerDegreeLat (const SGlobalPoint& Locality) const;
	virtual double DegreesLatPerPaperUnit (const SGlobalPoint& Locality) const;
	virtual double GetYUnitsPerPaperUnit (const SXYPoint& Locality) const = 0;

	virtual void Align (const SGlobalPoint& GlobalPoint,const CPoint& PaperPoint);

	virtual void AlignNorth (const CPoint& Centre);

	double GetLatPerPaper (const CPoint& Locality) const;
	virtual double GetYPerPaper	  (const CPoint& Locality) const = 0;

	virtual SFlatWorldBox PlaneWorldBox (const SGlobalPoint& Locality) const = 0;
	virtual SPaperBox     PaperWorldBox (const SGlobalPoint& Locality) const {return m_Matrix.WorldToPaper (PlaneWorldBox (Locality));}
	SPaperBox			  PaperWorldBox (const CPoint& Locality) const {return PaperWorldBox (PaperToGlobal (Locality));}

	void SetMatrix	(const SMatrix& Matrix);

	void MatchView (const SProjection& Projection,const SGlobalPoint& Centre);

	const SMatrix& Matrix () const {return m_Matrix;}
	SMatrix& Matrix () {return m_Matrix;}

	virtual bool Pin ();
	virtual bool Unpin ();
	void SwitchPrevious ();

	CString Name () const {return vctor_GetName ();}

	virtual double GetPaperUnitsPerXUnit (const SXYPoint& Locality) const = 0;

	virtual bool EquidistantYLines () const = 0;

	virtual bool StraightYLines () const {return true;}
	virtual bool StraightParallels    () const = 0;
	virtual int  GetDiscontinuityCount () const {return 0;}
	virtual const SProjectionDiscontinuity* GetDiscontinuity (int Idx) const;
	virtual bool NPIsPoint () const {return false;}
	virtual bool SPIsPoint () const {return false;}

	virtual bool IsGeographic () const = 0;
};//SProjection

class SGeographicProjection:public SProjection
{
public:

	double GetYUnitsPerPaperUnit (const SXYPoint& Locality) const {return DegreesLatPerPaperUnit (SGlobalPoint (Locality.m_Y,Locality.m_X));}

	virtual double GetPaperUnitsPerDegreeLong (const SGlobalPoint& Locality) const;
	double GetPaperUnitsPerXUnit (const SXYPoint& Locality) const {return GetPaperUnitsPerDegreeLong (SGlobalPoint (Locality.m_Y,Locality.m_X));}

	virtual bool EquidistantMeridians () const = 0;
	bool EquidistantYLines () const {return EquidistantMeridians ();}

	bool IsGeographic () const {return true;}

	CPoint			GenericToPaper (const SXYPoint& Point) const {return GlobalToPaper (Point.m_Y,Point.m_X);}
	SFlatWorldPoint	GenericToPlane (const SXYPoint& Point) const {return GlobalToPlane (Point.m_Y,Point.m_X);}
	SXYPoint		PaperToGeneric (const CPoint&   Point) const {SGlobalPoint RetVal = PaperToGlobal (Point); return SXYPoint (RetVal.m_Long,RetVal.m_Lat);}
	double			GetYPerPaper   (const CPoint& Locality) const {return GetLatPerPaper (Locality);}
	SPaperBox		GenericToPaper (const SNeutralBox& Box) const {ASSERT (Box.IsGlobal ()); return GlobalToPaper (Box.GlobalBox ());}
};//SGeographicProjection

class SGreenwichCylindricalProjection:public SGeographicProjection
{
protected:

	double	m_MinPlaneX;
	double	m_MaxPlaneX;
	double	m_MinPlaneY;
	double	m_MaxPlaneY;

	void Initialize ();

public:

	SGreenwichCylindricalProjection () {}
	SGreenwichCylindricalProjection (const SGreenwichCylindricalProjection&);

	virtual ~SGreenwichCylindricalProjection () {}

	SGlobalBox		PlaneToGlobalBox (const SFlatWorldBox&	Box) const;

	double GetFiltrationSepSqDeg () const;
	
	double GetProjectedNorth (const SGlobalPoint& At) const {return 0.0;}

	bool EquidistantMeridians () const {return true;}
	bool StraightParallels    () const {return true;}

	int GetDiscontinuityCount () const;
	const SProjectionDiscontinuity* GetDiscontinuity (int Idx) const;
};//SGreenwichCylindricalProjection

class SFlatEarthProjection:public SGreenwichCylindricalProjection
{
DECLARE_VIRTUAL_CONSTRUCTOR

public:

	SFlatEarthProjection () {Initialize ();}
	SFlatEarthProjection (const SFlatEarthProjection& RVal):SGreenwichCylindricalProjection (RVal) {}
	virtual ~SFlatEarthProjection () {}

	double GetFullWorldAspRat () const {return 0.5;}

	static CString GetDisplayNameStatic () {return "&Plate Caree";}
	CString GetDisplayName () const {return "&Plate Caree";}

	SProjection* Clone () const {return new SFlatEarthProjection (*this);}

	SFlatWorldPoint GlobalToPlane (const SGlobalPoint&    Point) const;
	SGlobalPoint	PlaneToGlobal (const SFlatWorldPoint& Point) const;

	SFlatWorldBox PlaneWorldBox (const SGlobalPoint& Locality) const;
};//SFlatEarthProjection

class SNPStereographicProjection:public SGeographicProjection
{
DECLARE_VIRTUAL_CONSTRUCTOR

public:

	SNPStereographicProjection () {}
	SNPStereographicProjection (const SNPStereographicProjection& RVal):SGeographicProjection (RVal) {}
	virtual ~SNPStereographicProjection () {}

	double GetFullWorldAspRat () const {return 1.0;}

	double GetFiltrationSepSqDeg () const;
	
	static CString GetDisplayNameStatic () {return "&North Polar Stereographic";}
	CString GetDisplayName () const {return "&North Polar Stereographic";}

	SProjection* Clone () const {return new SNPStereographicProjection (*this);}

	SFlatWorldPoint GlobalToPlane (const SGlobalPoint&   Point) const;
	SGlobalPoint	PlaneToGlobal (const SFlatWorldPoint& Point) const;
	SGlobalBox		PlaneToGlobalBox (const SFlatWorldBox&	Box) const;

	double GetProjectedNorth (const SGlobalPoint& At) const;

	bool EquidistantMeridians () const {return true;}
	bool StraightParallels    () const {return false;}

	int GetDiscontinuityCount () const;
	const SProjectionDiscontinuity* GetDiscontinuity (int Idx) const;

	SFlatWorldBox PlaneWorldBox (const SGlobalPoint& Locality) const;

	bool NPIsPoint () const {return true;}
};//SNPStereographicProjection

class SGallsStereographicProjection:public SGreenwichCylindricalProjection
{
DECLARE_VIRTUAL_CONSTRUCTOR

public:

	SGallsStereographicProjection ();
	SGallsStereographicProjection (const SGallsStereographicProjection& RVal):SGreenwichCylindricalProjection (RVal) {}
	virtual ~SGallsStereographicProjection () {}

	double GetFullWorldAspRat () const {SFlatWorldBox Box = PlaneWorldBox (SGlobalPoint (0.0)); return Box.Height ()/Box.Width ();}

	static CString GetDisplayNameStatic () {return "&Gall's Stereographic";}
	CString GetDisplayName () const {return "&Gall's Stereographic";}

	SProjection* Clone () const {return new SGallsStereographicProjection (*this);}

	SFlatWorldPoint GlobalToPlane (const SGlobalPoint&   Point) const;
	SGlobalPoint	PlaneToGlobal (const SFlatWorldPoint& Point) const;

	SFlatWorldBox PlaneWorldBox (const SGlobalPoint& Locality) const;
};//SGallsStereographicProjection

#endif

