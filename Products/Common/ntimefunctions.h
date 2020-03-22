/* TimeFunctions.h - functions related to time functions
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

$History: NTimeFunctions.h $
 * 
 * *****************  Version 1  *****************
 * User: Jasper       Date: 26-07-00   Time: 10:30
 * Created in $/CMIDS/Projects/Common
 * 
 * *****************  Version 1  *****************
 * User: Jasper       Date: 26-07-00   Time: 10:20
 * Created in $/CMIDS/Projects/Common
    [00]    HB  27Mar00 
*/

#ifndef TIMEFUNCTIONS
#define TIMEFUNCTIONS

#include <string>
#include "comdate.h"

// Define char size independent t_string
#ifdef _UNICODE
typedef std::wstring t_string;
#else
typedef std::string t_string;
#endif

namespace NTimeFunctions 
{
    const int MetisTimeLength = 11;
    const int WmoTimeLength = 6;

    // ALL_CURRENT_TIME   - Extract all missing time fields from the current time
    //                      e.g. "2300" when the current time is 000607-0200 
    //                      becomes "000607-2300"
    // MINIMAL_DIFFERENCE - Minimize the difference between the expanded time
    //                      and the current time, e.g. "2300" when the current
    //                      time is 000607-0200 becomes "000606-2300" since 
    //                      a difference of 3 hours is less than a difference
    //                      of 21 hours
    enum ExpandModes {ALL_CURRENT_TIME,  MINIMAL_DIFFERENCE};

    CComDATE      ExpandTime(LPCTSTR input_time, int expand_mode);

    t_string   ToMetisTime(const CComDATE& date);
    t_string   ToWmoTime(const CComDATE& date);
    CComDATE   MetisTimeToComDATE(LPCTSTR metis_time);
    CComDATE   WmoTimeToComDATE(LPCTSTR wmo_time);
    t_string   MetisNullTime();
    t_string   WmoNullTime();
};

#endif