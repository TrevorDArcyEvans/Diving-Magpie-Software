#ifndef __STriState_hpp
#define __STriState_hpp

namespace NTriStateStates
{
	enum States {False,True,Indeterminate};
};//NTriStateStates

class STriState
{
private:

	NTriStateStates::States	m_State;
	bool					m_Virgin;

public:

	STriState ():m_State (NTriStateStates::Indeterminate),m_Virgin (true) {}
	virtual ~STriState () {}

	void Reset () {m_State = NTriStateStates::Indeterminate; m_Virgin = true;}

	bool Valid () const {return m_State != NTriStateStates::Indeterminate;}
	bool State () const {return m_State == NTriStateStates::True;}

	const STriState& operator += (bool RVal);
};//STriState

#endif

