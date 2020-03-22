#ifndef _SMoveMeHint_hpp
#define _SMoveMeHint_hpp

#include <afx.h>

class SMoveMeHint:public CObject
{
private:

	SFeature*	m_MoveFeature;
	CPoint		m_StartPoint;

public:

	SMoveMeHint (SFeature* MoveFeature,const CPoint& StartPoint):m_MoveFeature (MoveFeature),m_StartPoint (StartPoint) {}
	virtual ~SMoveMeHint () {}

	SFeature* GetMoveFeature () const {return m_MoveFeature;}
	const CPoint& StartPoint () const {return m_StartPoint;}
};//SMoveMeHint

#endif
