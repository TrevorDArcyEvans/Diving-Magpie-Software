#ifndef _SLicenceChecker_h
#define _SLicenceChecker_h

class SLicenceChecker
{
private:

	bool m_Checked;
	bool m_OK;

	static SLicenceChecker*	sm_Instance;

	SLicenceChecker ():m_Checked (false),m_OK (false) {}
	virtual ~SLicenceChecker () {}

public:

	static SLicenceChecker* Instance ();

	bool LicenceOK ();

};//SLicenceChecker

#endif
