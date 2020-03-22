#ifndef __SLocker_h
#define __SLocker_h

#include <atlcom.h>

class SLocker	//	Lock the CComObject root and unlocks on destruction
{
private:

	CComObjectRoot*	m_Root;

public:

	SLocker (CComObjectRoot* Root):m_Root (Root) {if (m_Root) m_Root->Lock ();}
	~SLocker () {if (m_Root) m_Root->Unlock ();}
};

#endif