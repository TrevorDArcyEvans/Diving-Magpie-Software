#ifndef _STimeStuff_hpp
#define _STimeStuff_hpp

#include <afx.h>

namespace STimeStuff
{
	COleDateTime& InvalidTime ();

	COleDateTime CreateOleFromWMO (const CString& WMOString);
	COleDateTime CreateOleFromWMO (long WMOLong);
	COleDateTime CreateOleFromHHMM (const CString& HHMM,const COleDateTime& Day = COleDateTime::GetCurrentTime (),bool Nearest = false);
	COleDateTime CreateOleFromDDxMMxYY (const CString& DDxMMxYY);
	COleDateTime CreateOleFromMetis (const CString& MetisString);

	int NearestFourDigYear (int TwoDigYear);

	static LPCTSTR WMOFormat   = _T("%d%H%M");
	static LPCTSTR MetisFormat = _T("%y%m%d-%H%M");
}//STimeStuff

#endif

