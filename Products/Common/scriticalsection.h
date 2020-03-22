#ifndef _SCriticalSection_h
#define _SCriticalSection_h

class SCriticalSection
{
private:

	CRITICAL_SECTION	m_Section;
public:

	SCriticalSection ();
	virtual ~SCriticalSection ();

	void Lock ();
	void Unlock ();
};

#endif

