#ifndef __SInstanceLimiter_hpp
#define __SInstanceLimiter_hpp

#include "SString.hpp"

class CSemaphore;

class SInstanceLimiter
{
private:

	CSemaphore*			m_Semaphore;
	bool				m_LockedOkay;
	CString				m_ImageName;
	SString				m_RegistryValue;
	int					m_DefaultNum;
	int					m_NumAllowed;

public:

	SInstanceLimiter (const CString& ImageName,int NumAllowed);
	SInstanceLimiter (const CString& ImageName,const CString& RegistryVal = "General\\InstanceLimit",int Default = 1);

	virtual ~SInstanceLimiter ();

	bool CanIStartUp ();
	void ActivateSomeoneElse ();
};//SInstanceLimiter

#endif

