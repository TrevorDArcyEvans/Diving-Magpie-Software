#ifndef __SMethodLock_hpp
#define __SMethodLock_hpp

class SCriticalSection;

class SMethodLock
{
private:

	SCriticalSection&	m_Obj;

public:

	SMethodLock (SCriticalSection& Obj):m_Obj (Obj) {m_Obj.Lock ();}
	virtual ~SMethodLock () {m_Obj.Unlock ();}
};//SMethodLock

#endif
