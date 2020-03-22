#ifndef _SEvent_h
#define _SEvent_h

class SEvent
{
public:

//	Enums rather than bools to cover historical confusion over meanings of bools
	enum ResetTypes		{E_MANUAL,E_AUTOMATIC};	
	enum InitialStates	{E_SET,E_UNSET};			

private:

	HANDLE	m_Handle;

public:

	SEvent (InitialStates Init = E_UNSET,ResetTypes Reset = E_AUTOMATIC,LPCTSTR Name = _T(""));
	virtual ~SEvent ();

	void SetEvent ();
	void ResetEvent ();
	void PulseEvent ();

	operator HANDLE () const {return m_Handle;}
};

#endif


