#include "stdafx.h"
#include "STriState.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace NTriStateStates;

const STriState& STriState::operator += 
(
	bool RVal
)
{
	if (m_Virgin)
	{
		m_Virgin = false;
		m_State = RVal?True:False;
	}
	else if ((RVal?True:False) != m_State)
		m_State = Indeterminate;
	//if

	return *this;
}//STriState::operator +=


