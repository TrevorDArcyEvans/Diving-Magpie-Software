#include "stdafx.h"
#include "STimeStuff.hpp"
#include "SException.hpp"

COleDateTime& STimeStuff::InvalidTime ()
{
	static bool FirstTime = true;
	static COleDateTime Invalid;

	if (FirstTime)
	{
		FirstTime = false;
		Invalid.SetStatus (COleDateTime::invalid);
	}//if

	return Invalid;
}//STimeStuff::InvalidTime

COleDateTime STimeStuff::CreateOleFromWMO 
(
	long WMOLong
)
{
	CString AsStr;

	AsStr.Format (_T("%d"),WMOLong);

	return CreateOleFromWMO (AsStr);
}//STimeStuff::CreateOleFromWMO

COleDateTime STimeStuff::CreateOleFromWMO 
(
	const CString& WMOString
)
{
	CString WorkString = WMOString;
	
	WorkString.TrimLeft  (_T(" "));
	WorkString.TrimRight (_T(" "));

	if (WorkString.GetLength () != 6)
		return STimeStuff::InvalidTime ();
	//if

	int Day  = _ttoi (WorkString.Left (2));
	int Hour = _ttoi (WorkString.Mid (2,2));
	int Min  = _ttoi (WorkString.Right (2));

	if (Day > 31 || Day < 1 || Hour > 23 || Hour < 0 || Min > 59 || Min < 0)
		return STimeStuff::InvalidTime ();
	//if

	COleDateTime Now = COleDateTime::GetCurrentTime ();

	COleDateTime RetVal (Now.GetYear (),Now.GetMonth (),Day,Hour,Min,0);

	return RetVal;
}//STimeStuff::CreateOleFromWMO

COleDateTime STimeStuff::CreateOleFromHHMM 
(
	const CString&		HHMM,
	const COleDateTime& Day,
	bool				Nearest
)
{
	CString WorkString = HHMM;
	
	WorkString.TrimLeft  (_T(" "));
	WorkString.TrimRight (_T(" "));

	if (WorkString.GetLength () != 4)
		return STimeStuff::InvalidTime ();
	//if

	int Hour = _ttoi (WorkString.Left (2));
	int Min  = _ttoi (WorkString.Right (2));

	if (Hour > 23 || Hour < 0 || Min > 59 || Min < 0)
		return STimeStuff::InvalidTime ();
	//if
	
	if (Nearest)
	{
		COleDateTime Try (Day.GetYear (),Day.GetMonth (),Day.GetDay (),Hour,Min,0);

		COleDateTimeSpan Delta = Try - Day;

		static COleDateTimeSpan HalfDay (0,12,0,0);

		if (Delta > HalfDay)
			return COleDateTime (Day.GetYear (),Day.GetMonth (),Day.GetDay () - 1,Hour,Min,0);
		else if (Delta < -HalfDay)
			return COleDateTime (Day.GetYear (),Day.GetMonth (),Day.GetDay () + 1,Hour,Min,0);
		else
			return COleDateTime (Day.GetYear (),Day.GetMonth (),Day.GetDay (),Hour,Min,0);
		//if
	}
	else
		return COleDateTime (Day.GetYear (),Day.GetMonth (),Day.GetDay (),Hour,Min,0);
	//if
}//STimeStuff::CreateOleFromHHMM

COleDateTime STimeStuff::CreateOleFromDDxMMxYY 
(
	const CString& DDxMMxYY
)
{
	CString WorkString = DDxMMxYY;
	
	WorkString.TrimLeft  (_T(" "));
	WorkString.TrimRight (_T(" "));

	if (WorkString.GetLength () != 8)
		return STimeStuff::InvalidTime ();
	//if

	int DD = _ttoi (WorkString.Left (2));
	int MM = _ttoi (WorkString.Mid (3,2));
	int YY = _ttoi (WorkString.Right (2));

	if (DD > 31 || DD < 1 || MM > 12 || MM  < 1)
		return STimeStuff::InvalidTime ();
	//if

	COleDateTime RetVal (STimeStuff::NearestFourDigYear (YY),MM,DD,0,0,0);

	return RetVal;
}//STimeStuff::CreateOleFromDDxMMxYY

COleDateTime STimeStuff::CreateOleFromMetis 
(
	const CString& MetisString
)
{
	CString WorkString = MetisString;
	
	WorkString.TrimLeft  (_T(" "));
	WorkString.TrimRight (_T(" "));

	if (WorkString.GetLength () != 11)
		return STimeStuff::InvalidTime ();
	//if

	int YY = _ttoi (WorkString.Left (2));
	int MM = _ttoi (WorkString.Mid (2,2));
	int DD = _ttoi (WorkString.Mid (4,2));
	int HH = _ttoi (WorkString.Mid (7,2));
	int mm = _ttoi (WorkString.Right (2));

	if (DD > 31 || DD < 1 || MM > 12 || MM  < 1 || HH > 23 || HH < 0 || mm > 59 || mm < 0)
		return STimeStuff::InvalidTime ();
	//if

	return COleDateTime (STimeStuff::NearestFourDigYear (YY),MM,DD,HH,mm,0);
}//STimeStuff::CreateOleFromMetis

int STimeStuff::NearestFourDigYear 
(
	int TwoDigYear
)
{
	int ThisYear = COleDateTime::GetCurrentTime ().GetYear ();
	int ThisCentury = ThisYear / 100;

	int TryYear = (ThisCentury - 1) * 100 + TwoDigYear;

	while (abs (ThisYear - TryYear) > 50)
	{
		TryYear += 100;

//		Bail out
		if ((TryYear - ThisYear) > 200)
			throw new SException (_T("Bad logic"));
		//if
	}//while

	return TryYear;
}//STimeStuff::NearestFourDigYear