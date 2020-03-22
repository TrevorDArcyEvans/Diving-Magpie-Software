/* TimeFunctions.cpp
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

Description: Common time functions - NOT linked to MFC.
             
$History: NTimeFunctions.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Jasper       Date: 26-07-00   Time: 10:43
 * Updated in $/CMIDS/Projects/Common
 * Make it include the right header
 * 
 * *****************  Version 1  *****************
 * User: Jasper       Date: 26-07-00   Time: 10:30
 * Created in $/CMIDS/Projects/Common
 * 
 * *****************  Version 1  *****************
 * User: Jasper       Date: 26-07-00   Time: 10:20
 * Created in $/CMIDS/Projects/Common
    [00]    HB  08Mar00 Created
*/

#include "stdafx.h"
#include "NTimeFunctions.h"

using namespace std;

/* ExpandTime - Expand and validate a Metis or Wmo time

   INPUT   : time_string - Valid formats are:
                               YYMMDD-HHMM
                               MMDD-HHMM
                               DD-HHMM
                               HHMM
                               MM
                               DDHHMM
             expand_mode - MINIMAL_DIFFERENCE or ALL_CURRENT_TIME

   RETURNS : a CComDATE object (use IsValid() to test for validity)
*/
CComDATE NTimeFunctions::ExpandTime(LPCTSTR input_time, int expand_mode)
{
	int    iYear;		
	int    iMonth;
	int    iDay;
	int    iHour;
	int    iMinute;
    t_string strYear;
    t_string strMonth;
    t_string strDay;
    t_string strMinute;
    t_string strHour;
	int    length; // The length of the input t_string

    CComDATE resultDate;
    bool fValid = true;

    int iCorrectHour  = 0; // Corrections for expand mode MINIMAL_DIFFERENCE
    int iCorrectDay   = 0;
    int iCorrectMonth = 0;
    int iCorrectYear  = 0;

	// Get the full Time stamp
    t_string time_string(input_time);
	length = time_string.length();

	// replace the '-' char to zero to check if the input is valid
    fValid = true;
    if (length > 4 && length != 6) { 
        if (time_string[length - 5] == '-') {
            time_string[length - 5] = '0';
        } else {
            fValid = false;
        }
    }

	// Now all characters should be digits
    for (int i = 0; i < length; i++) {
        if (!isdigit (time_string[i])) {
			fValid = false;
        }
	} // for
	
    if (fValid) {
	
        // Get actual date/time and use these elements as defaults when 
        // a partial time t_string is given. If the expand mode is
        // MINIMAL_DIFFERENCE, the resulting time is corrected later.
		CComDATE actualDate = CComDATE::Now();

		iYear   = actualDate.Year();
		iMonth  = actualDate.Month();
		iDay    = actualDate.Day();
		iHour   = actualDate.Hour();
		iMinute = actualDate.Minute();

		switch (length)
		{
		case 0:	    // current time
					break;
		case 1:	
		case 2:	    // minutes
					iMinute = _ttoi (time_string.c_str());

                    // Calculate corrections when the expand mode
                    // is based on minimal difference
                    if (expand_mode == MINIMAL_DIFFERENCE) {
                        if (iMinute > 50 && actualDate.Minute() < 10)
                            iCorrectHour = -1;
                        if (actualDate.Minute() > 50 && iMinute < 10)
                            iCorrectHour = 1;
                    }
                    break;

		case 4:	    // hour minutes
                    strHour   = time_string.substr(2, 2);
                    strMinute = time_string.substr(0, 2);
					iHour = _ttoi (strHour.c_str());	 
					iMinute = _ttoi (strMinute.c_str());	

                    // Calculate corrections when the expand mode
                    // is based on minimal difference
                    if (expand_mode == MINIMAL_DIFFERENCE) {
                        if (iHour > 18 && actualDate.Hour() < 6)
                            iCorrectDay = -1;
                        if (actualDate.Hour() > 18 && iHour < 6)
                            iCorrectDay = 1;
                    }
					break;

		case 6:	
		case 7:	    // day - hour minutes
                    strDay = time_string.substr(0, 2);
					iDay = _ttoi (strDay.c_str());   
                    if (length == 6) { // WMO time YYGGgg
					    strHour = time_string.substr(2,2);
                        strMinute = time_string.substr(4,2);
                    } else {
					    strHour = time_string.substr(3,2);
					    strMinute = time_string.substr(5,2);
                    }
 				    iHour = _ttoi (strHour.c_str());
					iMinute = _ttoi (strMinute.c_str());

                    // Calculate corrections when the expand mode
                    // is based on minimal difference
                    if (expand_mode == MINIMAL_DIFFERENCE) {
                        if (iDay > 24 && actualDate.Day() < 10)
                            iCorrectMonth = -1;
                        if (actualDate.Day() > 24 && iDay < 10)
                            iCorrectMonth = 1;
                    }
					break;

		case 9:	    // month day - hour minutes
                    strMonth  = time_string.substr(0, 2);
                    strDay    = time_string.substr(2, 2);
                    strHour   = time_string.substr(5, 2);
                    strMinute = time_string.substr(7, 2);

					iMonth = _ttoi (strMonth.c_str());
					iDay = _ttoi (strDay.c_str());		  
					iHour = _ttoi (strHour.c_str());	     
                    iMinute = _ttoi (strMinute.c_str());	  

                    // Calculate corrections when the expand mode
                    // is based on minimal difference
                    if (expand_mode == MINIMAL_DIFFERENCE) {
                        if (iMonth > 10 && actualDate.Month() < 3)
                            iCorrectYear = -1;
                        if (actualDate.Month() > 10 && iMonth < 3)
                            iCorrectYear = 1;
                    }
					break;

		case 11:	// complete
                    strYear   = time_string.substr(0, 2);
                    strMonth  = time_string.substr(2, 2);
                    strDay    = time_string.substr(4, 2);
                    strHour   = time_string.substr(7, 2);
                    strMinute = time_string.substr(9, 2);

                    iYear     = _ttoi (strYear.c_str());	     
					iMonth    = _ttoi (strMonth.c_str());	 
					iDay      = _ttoi (strDay.c_str());		  
					iHour     = _ttoi (strHour.c_str());	     
					iMinute   = _ttoi (strMinute.c_str());	 

					if (iYear < 85)
						iYear += 2000;
					else
						iYear += 1900;
					break;

		default:	fValid = false;
                    break;
				
		} // switch
	} // else

    if (fValid) {
        // Set date & time based on current time and given time elements
	    resultDate.SetDateTime (iYear, iMonth, iDay, iHour, iMinute, 0);

        // Oops - 30 feb is illegal, but may be 30 jan was intended if expand
        // mode is based on minimal difference
        if (!resultDate.IsValid() && iDay >= 28 && iMonth == 2 &&
            iCorrectMonth == -1) {

            iMonth = 1;
    	    resultDate.SetDateTime (iYear, iMonth, iDay, iHour, iMinute, 0);
            iCorrectMonth = 0; // No further corrections
        }
        
        // Now perform corrections if requested
        if (resultDate.IsValid()) {

            if (iCorrectHour) 
                resultDate.AddHours(iCorrectHour);
            else if (iCorrectDay) 
                resultDate.AddDays(iCorrectDay);
            else if (iCorrectMonth) 
                resultDate.AddMonths(iCorrectMonth);
            else if (iCorrectYear) 
                resultDate.AddYears(iCorrectYear);
        }
    }

    return resultDate;
}

/* MetisNullTime - Returns Metis NULL time "000000-0000"
*/
t_string NTimeFunctions::MetisNullTime()
{
    return t_string(_T ("000000-0000"));
}

/* WmoNullTime - Returns Wmo NULL time "000000"
*/
t_string NTimeFunctions::WmoNullTime()
{
    return t_string(_T ("000000"));
}

/* ToMetisTime - Converts a CComDATE object to a METIS time t_string

   INPUT  : date - a CComDATE object
   RETURNS: Metis time (YYMMDD-HHMM) or Metis NULL time when time
            is invalid
*/
t_string NTimeFunctions::ToMetisTime(const CComDATE& date)
{
    t_string str;
    TCHAR  szBuffer[132];

    if (date.IsValid()) {
        str = date.Format(szBuffer, _T("%y%m%d-%H%M"));
    } else {
        str = MetisNullTime();
    }

    return str;
}

/* ToWmoTime - Converts a CComDATE object to a WMO time t_string

   INPUT  : date - a CComDATE object
   RETURNS: WMO time (DDHHMM) or WMO NULL time when time
            is invalid
*/
t_string  NTimeFunctions::ToWmoTime(const CComDATE& date)
{
    t_string  str;
    TCHAR   szBuffer[132];

    if (date.IsValid()) {
        str = date.Format(szBuffer, _T("%d%H%M") );
    } else {
        str = WmoNullTime();
    }

    return str;
}

/* MetisTimeToComDATE - Converts a METIS time t_string to a CComDATE

   INPUT  : metis_time - time in DDHHMM format
   RETURNS: CComDATE object
*/
CComDATE NTimeFunctions::MetisTimeToComDATE(LPCTSTR metis_time)
{
    CComDATE result;

    result.Invalidate();

    if (_tcslen (metis_time) == MetisTimeLength)
        result = ExpandTime(metis_time, MINIMAL_DIFFERENCE);

    return result;
}

/* WmoTimeToComDATE - Converts a Wmo time t_string to a CComDATE

   INPUT  : wmo_time - time in DDHHMM format
   RETURNS: CComDATE object
*/
CComDATE NTimeFunctions::WmoTimeToComDATE(LPCTSTR wmo_time)
{
    CComDATE result;

    result.Invalidate();

    if (_tcslen (wmo_time) == WmoTimeLength)
        result = ExpandTime(wmo_time, MINIMAL_DIFFERENCE);

    return result;
}

