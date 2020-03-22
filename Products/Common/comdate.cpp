// comdate.cpp
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1998 Chris Sells
// All rights reserved.
//
// NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK.
//
// To contact the author with suggestions or comments, use csells@sellsbrothers.com.

#include "stdafx.h"
#include "comdate.h"
#include <tchar.h>
#include <limits.h>
#include <math.h>
#include <winnls.h>

/////////////////////////////////////////////////////////////////////////////
// CComDATE class HELPER definitions

#define COMDATE_ERROR INT_MIN
#define MIN_DATE      (-657434L)      // About year 100
#define MAX_DATE      2958465L        // About year 9999
#define INVALID_DATE  (MIN_DATE-1)    // Used to indicate invalid date
#define HALF_SECOND   (1.0/172800.0)  // Half a second, expressed in days

// One-based array of days in year at month start
static short  rgMonthDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// Array used by DaysInMonth function
static char   GauDays[]	= { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static bool   IsValidDate(const DATE& dt);
static bool   MakeDATE(DATE* pdtDest, WORD wYear, WORD wMonth, WORD wDay, WORD wHour, WORD wMinute, WORD wSecond);
static bool   Maketm(struct tm* ptmDest, DATE dtSrc);
static double DATEAsDouble(DATE dtSrc);
static DATE   MakeDATE(double dbSrc);

/////////////////////////////////////////////////////////////////////////////
// CComDATE class

bool CComDATE::IsValid() const
{ return IsValidDate(m_date); }

void CComDATE::Invalidate()
{ m_date = INVALID_DATE; }

long CComDATE::Year() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_year + 1900;
    return COMDATE_ERROR;
}

long CComDATE::Month() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_mon + 1;
    return COMDATE_ERROR;
}

long CComDATE::Day() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_mday;
    return COMDATE_ERROR;
}

long CComDATE::Hour() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_hour;
    return COMDATE_ERROR;
}

long CComDATE::Minute() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_min;
    return COMDATE_ERROR;
}

long CComDATE::Second() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_sec;
    return COMDATE_ERROR;
}

long CComDATE::DayOfWeek() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_wday + 1;
    return COMDATE_ERROR;
}

long CComDATE::DayOfYear() const
{
    struct tm tmDest;
    if( IsValid() && Maketm(&tmDest, m_date) ) return tmDest.tm_yday + 1;
    return COMDATE_ERROR;
}

bool CComDATE::IsLeapYear() const
{
    long year = Year();
    return ((year != COMDATE_ERROR) && ((year & 3) == 0) && ((year % 100) != 0 || (year % 400) == 0));
}

bool CComDATE::IsNoon() const
{
    return Hour() == 12 && Minute() == 0 && Second() == 0;
}

bool CComDATE::IsMidnight() const
{
    return Hour() == 0 && Minute() == 0 && Second() == 0;
}

const CComDATE& CComDATE::operator=(const VARIANT& varSrc)
{
    if( varSrc.vt == VT_DATE )
    {
        m_date = varSrc.date;
    }
    else
    {
        VARIANT varDest = { 0 };
        if( SUCCEEDED(VariantChangeType(&varDest, const_cast<VARIANT*>(&varSrc), 0, VT_DATE)) )
        {
            m_date = varDest.date;
            VariantClear(&varDest);
        }
        else
        {
            Invalidate();
        }
    }
    
    return *this;
}

const CComDATE& CComDATE::operator=(DATE dtSrc)
{
    m_date = dtSrc;
    return *this;
}

const CComDATE& CComDATE::operator=(const time_t& tmSrc)
{
    // Convert time_t to struct tm
    tm *ptm = localtime(&tmSrc);
    
    if( !ptm ||
        !MakeDATE(&m_date,
                  (WORD)(ptm->tm_year + 1900),
                  (WORD)(ptm->tm_mon + 1),
                  (WORD)ptm->tm_mday,
                  (WORD)ptm->tm_hour,
                  (WORD)ptm->tm_min,
                  (WORD)ptm->tm_sec) )
    {
        // Local time must have failed (tmSrc before 1/1/70 12am)
        Invalidate();
    }
    
    return *this;
}

const CComDATE& CComDATE::operator=(const SYSTEMTIME& systmSrc)
{
    if( !MakeDATE(&m_date,
                  systmSrc.wYear,
                  systmSrc.wMonth,
                  systmSrc.wDay,
                  systmSrc.wHour,
                  systmSrc.wMinute,
                  systmSrc.wSecond) )
    {
        Invalidate();
    }
    
    return *this;
}

const CComDATE& CComDATE::operator=(const FILETIME& ftSrc)
{
    // Assume UTC FILETIME, so convert to LOCALTIME
    FILETIME ftLocal;
    if( !FileTimeToLocalFileTime( &ftSrc, &ftLocal) )
    {
#ifdef ATLTRACE
        ATLTRACE("\nFileTimeToLocalFileTime failed. Error = %lu.\n\t", GetLastError());
#endif
        Invalidate();
    }
    else
    {
        // Take advantage of SYSTEMTIME -> FILETIME conversion
        SYSTEMTIME  systime;
        
        // At this polong systime should always be valid, but...
        if( !FileTimeToSystemTime(&ftLocal, &systime) ||
            !MakeDATE(&m_date,
                      systime.wYear,
                      systime.wMonth,
                      systime.wDay,
                      systime.wHour,
                      systime.wMinute,
                      systime.wSecond) )
        {
            Invalidate();
        }
    }
    
    return *this;
}

bool CComDATE::operator<(const CComDATE& date) const
{
    _ASSERTE(IsValid());
    _ASSERTE(date.IsValid());
    
    // Handle negative dates
    return DATEAsDouble(m_date) < DATEAsDouble(date.m_date);
}

bool CComDATE::operator>(const CComDATE& date) const
{
    _ASSERTE(IsValid());
    _ASSERTE(date.IsValid());
    
    // Handle negative dates
    return DATEAsDouble(m_date) > DATEAsDouble(date.m_date);
}

bool CComDATE::operator<=(const CComDATE& date) const
{
    _ASSERTE(IsValid());
    _ASSERTE(date.IsValid());
    
    // Handle negative dates
    return DATEAsDouble(m_date) <= DATEAsDouble(date.m_date);
}

bool CComDATE::operator>=(const CComDATE& date) const
{
    _ASSERTE(IsValid());
    _ASSERTE(date.IsValid());
    
    // Handle negative dates
    return DATEAsDouble(m_date) >= DATEAsDouble(date.m_date);
}

bool CComDATE::SetDateTime(
    long nYear,
    long nMonth,
    long nDay,
    long nHour,
    long nMin,
    long nSec)
{
    if( !MakeDATE(&m_date, (WORD)nYear, (WORD)nMonth, (WORD)nDay, (WORD)nHour, (WORD)nMin, (WORD)nSec) )
    {
        Invalidate();
    }
    
    return IsValid();
}

bool CComDATE::ParseDateTime(const char* lpszDate, DWORD dwFlags, LCID lcid)
{
    USES_CONVERSION;
    return ParseDateTime(A2OLE(lpszDate), dwFlags, lcid);
}

bool CComDATE::ParseDateTime(const wchar_t* lpszDate, DWORD dwFlags, LCID lcid)
{
    if( FAILED(VarDateFromStr(const_cast<wchar_t*>(lpszDate), lcid, dwFlags, &m_date)) )
    {
        Invalidate();
    }
    
    return IsValid();
}

LPTSTR CComDATE::Format(LPTSTR pszOut, DWORD dwFlags, LCID lcid) const
{
    *pszOut = 0;
    
    // If invalid, return empty string
    if (!IsValid()) return pszOut;
    
    BSTR  bstr = 0;
    if( SUCCEEDED(VarBstrFromDate(m_date, lcid, dwFlags, &bstr)) )
    {
#ifdef _UNICODE
        wcscpy(pszOut, bstr);
#else
        wcstombs(pszOut, bstr, wcslen(bstr) + 1);
#endif
        
        SysFreeString(bstr);
    }
    
    return pszOut;
}

LPTSTR CComDATE::Format(LPTSTR pszOut, LPCTSTR pFormat) const
{
    *pszOut = 0;
    
    // If invalild, return empty string
    struct tm tmDest;
    if (!IsValid() || !Maketm(&tmDest, m_date) ) return pszOut;
    
    // Fill in the buffer, disregard return value as it's not necessary
    // NOTE: 4096 is an arbitrary value picked lower than INT_MAX
    // as the VC6 implementation of wcsftime allocates memory based
    // on the 2nd parameter for some reason.
    _tcsftime(pszOut, 4096, pFormat, &tmDest);
    return pszOut;
}

LPTSTR CComDATE::Format(LPTSTR pszOut, UINT nFormatID, HINSTANCE hinst) const
{
    *pszOut = 0;
    
    TCHAR   sz[256];
    if( LoadString(hinst, nFormatID, sz, sizeof(sz)/sizeof(*sz)) )
    {
        return Format(pszOut, sz);
    }
    
    return pszOut;
}

// The FormatDate and FormatTime functions were provided by Joe O'Leary (joleary@artisoft.com) to
// wrap he Win32 National Language Support functions ::GetDateFormat() and ::GetTimeFormat().
// The format strings used here are specified in the on-line help for those functions.
// The default format is the current user locale.

LPTSTR CComDATE::FormatDate(LPTSTR pszOut, LPCTSTR szFmt, DWORD dwFlags, LCID lcid) const
{
	_ASSERTE((szFmt==NULL) || (dwFlags==0));// if format is non-NULL, 'dwFlags' MUST be zero

	SYSTEMTIME st;
	memset(&st, 0, sizeof(SYSTEMTIME));
	*pszOut = NULL;

	if ( !VariantTimeToSystemTime(m_date, &st) )
	{
#ifdef ATLTRACE
        ATLTRACE("\nVariantTimeToSystemTime failed. Error = %lu.\n\t", GetLastError());
#endif
	}
	else if ( GetDateFormat(lcid, dwFlags, &st, szFmt, pszOut, 255) == 0 )
	{
#ifdef ATLTRACE
        ATLTRACE("\nGetDateFormat failed. Error = %lu.\n\t", GetLastError());
#endif
	}

	return pszOut;
}

LPTSTR CComDATE::FormatTime(LPTSTR pszOut, LPCTSTR szFmt, DWORD dwFlags, LCID lcid) const
{
	_ASSERTE((szFmt==NULL) || (dwFlags==0));// if format is non-NULL, 'dwFlags' MUST be zero

	SYSTEMTIME st;
	memset(&st, 0, sizeof(SYSTEMTIME));
	*pszOut = NULL;

	if ( !VariantTimeToSystemTime(m_date, &st) )
	{
#ifdef ATLTRACE
        ATLTRACE("\nVariantTimeToSystemTime failed. Error = %lu.\n\t", GetLastError());
#endif
	}
	else if ( GetTimeFormat(lcid, dwFlags, &st, szFmt, pszOut, 255) == 0 )
	{
#ifdef ATLTRACE
        ATLTRACE("\nGetTimeFormat failed. Error = %lu.\n\t", GetLastError());
#endif
	}

	return pszOut;
}

unsigned int CComDATE::DaysInMonth() const
{
    long month = Month();
    if  (IsValid()) 
       return (unsigned int) (GauDays[month] + (month==2 && IsLeapYear()));
    else
       return 0;
}

bool CComDATE::AddMinutes(int nCount)
{
	CComSpan span;
	span.SetSpan(0,0,nCount,0);
    if (span.IsValid()) *this += span;

	return IsValid();
}

bool CComDATE::AddHours(int nCount)
{
	CComSpan span;
	span.SetSpan(0,nCount,0,0);
    if (span.IsValid()) *this += span;

	return IsValid();
}

bool CComDATE::AddDays(int nCount)
{
	CComSpan span;
	span.SetSpan(nCount,0,0,0);
    if (span.IsValid()) *this += span;

	return IsValid();
}

bool CComDATE::AddMonths(int nCount)
{
   	long year  = Year();
	long month = Month();
    long day   = Day();

    int  nDays;
 
	month += (short) nCount;

	while (month < 1)
	{
        month += 12;
        year--;
	}

	while (month > 12)
	{
        month -= 12;
        year++;
	}

    nDays = (unsigned int) DaysInMonth();

    if (day > nDays)                    // Bump up the month by one if day is
    {                                   // greater than # of days in new month
        month++;                        // and assigned the difference as the
        day -= nDays;                   // day value for the new month! - TML
    }

    return SetDateTime(year, month, day, Hour(), Minute(), Second());
}

bool CComDATE::AddYears(int nCount)
{
    return SetDateTime(Year() + nCount, Month(), Day(), Hour(), Minute(), Second());
}

bool IsValidDate(const DATE& dt)
{
    // About year 100 to about 9999
    return (dt >= MIN_DATE && dt <= MAX_DATE);
}

bool Maketm(struct tm* ptmDest, DATE dtSrc)
{
    SYSTEMTIME  st;
    if( !VariantTimeToSystemTime(dtSrc, &st) ) return false;
    
    struct tm& tmDest = *ptmDest; // Convenience
    tmDest.tm_sec = st.wSecond;
    tmDest.tm_min = st.wMinute;
    tmDest.tm_hour = st.wHour;
    tmDest.tm_mday = st.wDay;
    tmDest.tm_mon = st.wMonth - 1;
    tmDest.tm_year = st.wYear - 1900;
    tmDest.tm_wday = st.wDayOfWeek;
    tmDest.tm_isdst = -1;   // Force DST checking
    mktime(&tmDest);        // Normalize
    
    return true;
}

double DATEAsDouble(DATE dt)
{
    // No problem if positive
    if (dt >= 0) return dt;
    
    // If negative, must convert since negative dates not continuous
    // (examples: -1.25 to -.75, -1.50 to -.50, -1.75 to -.25)
    double temp = ceil(dt);
    return temp - (dt - temp);
}

DATE MakeDATE(double dbl)
{
    // No problem if positive
    if (dbl >= 0) return dbl;
    
    // If negative, must convert since negative dates not continuous
    // (examples: -.75 to -1.25, -.50 to -1.50, -.25 to -1.75)
    double temp = floor(dbl); // dbl is now whole part
    return temp + (temp - dbl);
}

bool MakeDATE(
    DATE* pdtDest,
    WORD  wYear,
    WORD  wMonth,
    WORD  wDay,
    WORD  wHour,
    WORD  wMinute,
    WORD  wSecond)
{
    SYSTEMTIME st = { 0 };
    st.wYear = wYear;
    st.wMonth = wMonth;
    st.wDay = wDay;
    st.wHour = wHour;
    st.wMinute = wMinute;
    st.wSecond = wSecond;
    
    return SystemTimeToVariantTime(&st, pdtDest) ? true : false;
}

/////////////////////////////////////////////////////////////////////////////
// CComSpan class helpers

#define MAX_SPAN      3615897L
#define MIN_SPAN      (-MAX_SPAN)
#define INVALID_SPAN  (MIN_SPAN-1)    // Used to indicate invalid span

/////////////////////////////////////////////////////////////////////////////
// CComSpan class

bool CComSpan::IsValid() const
{ return (m_span >= MIN_SPAN && m_span <= MAX_SPAN); }

void CComSpan::Invalidate()
{ m_span = INVALID_SPAN; }

long CComSpan::Hours() const
{
    _ASSERTE(IsValid());
    
    // Truncate days and scale up
    double dbTemp = modf(m_span, &dbTemp);
    return (long)(dbTemp * 24);
}

long CComSpan::Minutes() const
{
    _ASSERTE(IsValid());
    
    // Truncate hours and scale up
    double dbTemp = modf(m_span * 24, &dbTemp);
    return (long)(dbTemp * 60);
}

long CComSpan::Seconds() const
{
    _ASSERTE(IsValid());
    
    // Truncate minutes and scale up
    double dbTemp = modf(m_span * 24 * 60, &dbTemp);
    return (long)(dbTemp * 60);
}

void CComSpan::SetSpan(
    long  nDays,
    long  nHours,
    long  nMins,
    long  nSecs)
{
    // Set date span by breaking longo fractional days (all input ranges valid)
    m_span = nDays +
             ((double)nHours)/24 +
             ((double)nMins)/(24*60) +
             ((double)nSecs)/(24*60*60);
}

/////////////////////////////////////////////////////////////////////////////
// CComDATE/CComSpan math friend functions

// date2 = date1 + span;
CComDATE operator+(const CComDATE& date1, const CComSpan& span)
{
    CComDATE  date2;
    
    if( date1.IsValid() && span.IsValid() )
    {
        // Compute the actual date difference by adding underlying data
        date2 = MakeDATE(DATEAsDouble(static_cast<DATE>(date1)) + static_cast<double>(span));
    }
    
    return date2;
}

// date2 = span + date1;
CComDATE operator+(const CComSpan& span, const CComDATE& date1)
{
    CComDATE  date2;
    
    if( date1.IsValid() && span.IsValid() )
    {
        // Compute the actual date difference by adding underlying data
        date2 = MakeDATE(DATEAsDouble(static_cast<DATE>(date1)) + static_cast<double>(span));
    }
    
    return date2;
}

// date2 = date1 - span;
CComDATE operator-(const CComDATE& date1, const CComSpan& span)
{
    CComDATE  date2;
    
    if( date1.IsValid() && span.IsValid() )
    {
        // Compute the actual date difference by adding underlying data
        date2 = MakeDATE(DATEAsDouble(static_cast<DATE>(date1)) - static_cast<double>(span));
    }
    
    return date2;
}

// span = date1 - date2;
CComSpan operator-(const CComDATE& date1, const CComDATE& date2)
{
    CComSpan span;
    
    if( date1.IsValid() && date2.IsValid() )
    {
        span = DATEAsDouble(static_cast<DATE>(date1)) - DATEAsDouble(static_cast<DATE>(date2));
    }
    
    return span;
}

// span3 = span1 + span2;
CComSpan operator+(const CComSpan& span1, const CComSpan& span2)
{
    CComSpan span3;
    if( span1.IsValid() && span2.IsValid() ) span3 = span1.m_span + span2.m_span;
    return span3;
}

// span3 = span1 - span2;
CComSpan operator-(const CComSpan& span1, const CComSpan& span2 )
{
    return span1 + (-span2);
}