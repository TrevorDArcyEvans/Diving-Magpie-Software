#include "stdafx.h"
#include "SLicenceChecker.h"

BOOL gCheckLicence ();

SLicenceChecker* SLicenceChecker::sm_Instance = 0;
	
SLicenceChecker* SLicenceChecker::Instance ()
{
	if (!sm_Instance)
		sm_Instance = new SLicenceChecker;
	//if

	return sm_Instance;
}//SLicenceChecker::Instance

bool SLicenceChecker::LicenceOK ()
{
	if (!m_Checked)
	{
		m_OK = ::gCheckLicence ();
		m_Checked = true;
	}//if

	return m_OK;
}//SLicenceChecker::LicenceOK
