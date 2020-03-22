#ifndef __SRedrawHint_hpp
#define __SRedrawHint_hpp

#include <afx.h>

class SRedrawHint:public CObject
{
private:

	bool	m_PrioVisChange;
	bool	m_RecalcBoxes;
	bool	m_RedrawNow;

public:

	SRedrawHint (bool PrioVisChange = false,
				 bool RecalcBoxes = false,
				 bool RedrawNow = false):m_PrioVisChange (PrioVisChange),
										 m_RecalcBoxes (RecalcBoxes),
										 m_RedrawNow (RedrawNow) {}

	bool PrioVisChange () const {return m_PrioVisChange;}
	bool RecalcBoxes () const {return m_RecalcBoxes;}
	bool RedrawNow () const {return m_RedrawNow;}
};//SRedrawHint

#endif

