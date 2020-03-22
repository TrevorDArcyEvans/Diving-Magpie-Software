#ifndef __SProjectionDiscontinuity_hpp
#define __SProjectionDiscontinuity_hpp

#include "SLongitude.hpp"
#include "SPoints.hpp"
#include "SGlobalBox.hpp"

class SPointsPrimitive;
class SPositionList;
class SFillareaPrimitive;

class SProjectionDiscontinuity
{
protected:

	SProjectionDiscontinuity () {}

public:

	virtual ~SProjectionDiscontinuity () {}
	virtual bool AnyEffect (const SGlobalBox& Box) const = 0;

	virtual void Split (SPointsPrimitive* Primitive) const {}

	virtual bool operator == (const SProjectionDiscontinuity& RVal) const;
};//SProjectionDiscontinuity

class SMeridianSplit:public SProjectionDiscontinuity
{
private:

	SLongitude m_SplitAt;

	void SplitPolyline (SPositionList& Points,int First,int Last) const;
	void SplitFillarea (SFillareaPrimitive* Fill,int First,int Last) const;

public:

	SMeridianSplit (const SLongitude& SplitAt):m_SplitAt (SplitAt) {}
	virtual ~SMeridianSplit () {}

	const SLongitude& SplitAt () const {return m_SplitAt;}
	bool AnyEffect (const SGlobalBox& Box) const;

	void Split (SPointsPrimitive* Primitive) const;

};//SMeridianSplit

class SInvalidProjectionRegion:public SProjectionDiscontinuity
{
protected:

	SGlobalBox	m_Box;

	SInvalidProjectionRegion () {}

public:

	virtual ~SInvalidProjectionRegion  () {}

	virtual bool EntirelyContains (const SGlobalBox& Box) const = 0;
};//SInvalidProjectionRegion

class SParallelBoundInvalidRegion:public SInvalidProjectionRegion
{
public:

	SParallelBoundInvalidRegion (double Min,double Max);
	virtual ~SParallelBoundInvalidRegion () {}

	bool EntirelyContains (const SGlobalBox& Box) const;
	bool AnyEffect (const SGlobalBox& Box) const;

	double GetMinInvalidLat () const {return m_Box.MinLat ();}
	double GetMaxInvalidLat () const {return m_Box.MaxLat ();}
};//SParallelBoundInvalidRegion

#endif

