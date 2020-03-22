#ifndef __SRemoveMeHint_hpp
#define __SRemoveMeHint_hpp

#include <afxwin.h>

class SRemoveMeHint:public CObject
{
private:

	SFeature*	m_Feature;

public:

	SRemoveMeHint (SFeature* Feature):m_Feature (Feature) {}
	virtual ~SRemoveMeHint () {}

	SFeature* GetFeature () const {return m_Feature;}
};//SRemoveMeHint

#endif
