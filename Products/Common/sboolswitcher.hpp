#ifndef __SBoolSwitcher_hpp
#define __SBoolSwitcher_hpp

class SBoolSwitcher
{
private:

	bool&	m_Bool;
	bool	m_KeepAs;

public:

	SBoolSwitcher (bool& TheBool,bool KeepAs = true):m_Bool (TheBool),m_KeepAs (KeepAs) {m_Bool = m_KeepAs;}
	virtual ~SBoolSwitcher () {m_Bool = !m_KeepAs;}
};//SBoolSwitcher

#endif
