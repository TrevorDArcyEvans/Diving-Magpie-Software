#ifndef __SSelectabilityHint_hpp
#define __SSelectabilityHint_hpp

#include <afx.h>

class SSelectabilityHint:public CObject
{
private:

	SFeature*	m_Feature;
	bool		m_On;

public:

	SSelectabilityHint (SFeature* Feature,bool On):m_Feature (Feature),m_On (On) {}
	virtual ~SSelectabilityHint () {}

	SFeature* Feature () const {return m_Feature;}
	bool	  On () const {return m_On;}
};//SSelectabilityHint

class SSelectableQueryHint:public CObject
{
private:

	const SFeature*	m_Feature;
	bool			m_IsSelectable;

public:

	SSelectableQueryHint (const SFeature* Feature):m_Feature (Feature),m_IsSelectable (false) {}
	virtual ~SSelectableQueryHint () {}

	bool IsSelectable () const {return m_IsSelectable;}
	void SetSelectable (bool On) {m_IsSelectable = On;}

	const SFeature* Feature () const {return m_Feature;}
};//SSelectableQueryHint

#endif
