// comdate.h
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1998-1999 Chris Sells
// All rights reserved.
//
// NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK.
//
// To contact the author with suggestions or comments, use csells@sellsbrothers.com.
/////////////////////////////////////////////////////////////////////////////
// History:
//  27/3/00 - Now() function changed to avoid year 2038 bug
//   6/9/99 - Fixed a problem in Maketm where tm_isdst was not being set
//            (as is required by the CRT). Thanks to Jim Hoffman
//            [JHoffman@Enerx.com] for pointing it out.
//  4/18/99 - Fixed a problem in Format to provide a work-around in the
//            VC6 implementation of wcsftime. Thanks for Joe O'Leary for
//            pointing it out.
//            Even better, Joe also contributed FormatDate and FormatTime
//            to wrap the National Language Support functions GetTimeFormat()
//            and GetDateFormat(). Thanks, Joe!
//            Also, Juan Rivera (juanc@kodak.com) pointed out a missing operator=
//            declaration. Thanks, Juan.
// 12/24/98 - Based on a suggestion by Ronald Laeremans [RonaldL@mvps.org],
//            replaced all of the manual Maketm code w/ VariantToSystemTime.
//            Also updated MakeDATE to use SystemTimeToVariantTime. Thanks, Ron!
// 12/23/98 - Fixed a bug Ward pointed out in CComDATE::operator=(const time_t&).
// 12/21/98 - Ward Fuller <wfuller@tsisoft.com> pointed out a BSTR leak in
//            the Format implementation. It's plugged. Thanks, Ward!
// 12/21/98 - Initial release.
/////////////////////////////////////////////////////////////////////////////
// The file provides two class for use with dates and times under Windows.
//
// CComDATE: Wraps the COM DATE type, providing conversions from VARIANT,
//           DATE, ANSI string, UNICODE string, time_t, SYSTEMTIME, FILETIME,
//           DOS time and DBTIMESTAMP data types.
//
// CComSpan: Represents the result of subtracting one CComDATE from another.
//           Useful for time/date math.
//
// NOTE: This usage of these classes are based loosely on the MFC classes
//       COleDateTime and COleDateTimeSpan. However, the implementation is 90% mine.

#pragma once
#ifndef __COMDATE_H__
#define __COMDATE_H__

#include "stdafx.h"

#include <time.h>

/////////////////////////////////////////////////////////////////////////////
// CComDATE class

class CComSpan; // Forward declaration


class CComDATE
{
public:
    static CComDATE Now();
    
    CComDATE();
    CComDATE(const CComDATE& dtSrc);
    CComDATE(const VARIANT& varSrc);
    CComDATE(DATE dtSrc);
    CComDATE(const char* pszSrc);
    CComDATE(const wchar_t* pszSrc);
    CComDATE(time_t timeSrc);
    CComDATE(const SYSTEMTIME& systimeSrc);
    CComDATE(const FILETIME& filetimeSrc);
    CComDATE(long nYear, long nMonth, long nDay, long nHour = 0, long nMin = 0, long nSec = 0);
    CComDATE(WORD wDosDate, WORD wDosTime);
    
#ifdef __oledb_h__
    CComDATE(const DBTIMESTAMP& dbts);
#endif
    
public:
    bool  IsValid() const;
    long  Year() const;
    long  Month() const;     // month of year (1 = Jan)
    long  Day() const;       // day of month (0-31)
    long  Hour() const;      // hour in day (0-23)
    long  Minute() const;    // minute in hour (0-59)
    long  Second() const;    // second in minute (0-59)
    long  DayOfWeek() const; // 1=Sun, 2=Mon, ..., 7=Sat
    long  DayOfYear() const; // days since start of year, Jan 1 = 1
    
    bool  IsLeapYear() const;   // Whether it's a leap year or not
    bool  IsNoon() const;       // Whether it's 12:00:00pm or not
    bool  IsMidnight() const;   // Whether it's 12:00:00am or not
    
    // Operations
public:
    const CComDATE& operator=(const CComDATE& dtSrc);
    const CComDATE& operator=(const VARIANT& varSrc);
    const CComDATE& operator=(DATE dtSrc);
    const CComDATE& operator=(const char* pszSrc);
    const CComDATE& operator=(const wchar_t* pszSrc);
    
    const CComDATE& operator=(const time_t& timeSrc);
    const CComDATE& operator=(const SYSTEMTIME& systimeSrc);
    const CComDATE& operator=(const FILETIME& filetimeSrc);

#ifdef __oledb_h__
    const CComDATE& CComDATE::operator=(const DBTIMESTAMP& dbts);
#endif

    bool operator==(const CComDATE& date) const;
    bool operator!=(const CComDATE& date) const;
    bool operator<(const CComDATE& date) const;
    bool operator>(const CComDATE& date) const;
    bool operator<=(const CComDATE& date) const;
    bool operator>=(const CComDATE& date) const;
    
    // Date math
    const CComDATE& operator+=(const CComSpan& span);
    const CComDATE& operator-=(const CComSpan& span);
    
    friend CComDATE operator+(const CComDATE& date, const CComSpan& span);
    friend CComDATE operator-(const CComDATE& date, const CComSpan& span);
    friend CComDATE operator+(const CComSpan& span, const CComDATE& date);
    friend CComSpan operator-(const CComDATE& date1, const CComDATE& date2);
    
    operator DATE() const;
    DATE* operator&();
    
    bool  SetDateTime(long nYear, long nMonth, long nDay, long nHour, long nMin, long nSec);
    bool  SetDate(long nYear, long nMonth, long nDay);
    bool  SetTime(long nHour, long nMin, long nSec);
    bool  ParseDateTime(const char* lpszDate, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT);
    bool  ParseDateTime(const wchar_t* lpszDate, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT);
    
    // Formatting
    LPTSTR Format(LPTSTR pszOut, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT) const;
    LPTSTR Format(LPTSTR pszOut, LPCTSTR lpszFormat) const;
#ifdef __ATLCOM_H__
    LPTSTR Format(LPTSTR pszOut, UINT nFormatID, HINSTANCE hinst = _Module.GetResourceInstance()) const;
#else
    LPTSTR Format(LPTSTR pszOut, UINT nFormatID, HINSTANCE hinst = GetModuleHandle(0)) const;
#endif

	// Formatting using National Language Support functions GetTimeFormat() and GetDateFormat()
	LPTSTR	FormatTime(LPTSTR pszOut, LPCTSTR szFmt=NULL, DWORD dwFlags=0, LCID lcid=LOCALE_USER_DEFAULT) const;
	LPTSTR	FormatDate(LPTSTR pszOut, LPCTSTR szFmt=NULL, DWORD dwFlags=0, LCID lcid=LOCALE_USER_DEFAULT) const;

    unsigned int DaysInMonth() const;

    bool AddYears  (int nCount);
    bool AddMonths (int nCount);  
    bool AddDays   (int nCount);
    bool AddHours  (int nCount);
    bool AddMinutes(int nCount);

    void Invalidate();

protected:
    DATE  m_date;

//	Sigmex additions
public:

	static CComDATE NowGMT ();
};

/////////////////////////////////////////////////////////////////////////////
// CComSpan class
class CComSpan
{
public:
    CComSpan();
    CComSpan(double dblSpanSrc);
    CComSpan(const CComSpan& dateSpanSrc);
    CComSpan(long nDays, long nHours = 0, long nMins = 0, long nSecs = 0);
    
    bool IsValid() const;
    
    double TotalDays() const;    // span in days (about -3.65e6 to 3.65e6)
    double TotalHours() const;   // span in hours (about -8.77e7 to 8.77e6)
    double TotalMinutes() const; // span in minutes (about -5.26e9 to 5.26e9)
    double TotalSeconds() const; // span in seconds (about -3.16e11 to 3.16e11)
    
    long Days() const;       // component days in span
    long Hours() const;      // component hours in span (-23 to 23)
    long Minutes() const;    // component minutes in span (-59 to 59)
    long Seconds() const;    // component seconds in span (-59 to 59)
    
public:
    const CComSpan& operator=(double dblSpanSrc);
    const CComSpan& operator=(const CComSpan& dateSpanSrc);
    
    bool operator==(const CComSpan& dateSpan) const;
    bool operator!=(const CComSpan& dateSpan) const;
    bool operator<(const CComSpan& dateSpan) const;
    bool operator>(const CComSpan& dateSpan) const;
    bool operator<=(const CComSpan& dateSpan) const;
    bool operator>=(const CComSpan& dateSpan) const;
    
    // Math
    const CComSpan& operator+=(const CComSpan& rhs);
    const CComSpan& operator-=(const CComSpan& rhs);
    CComSpan operator-() const;
    
    friend CComSpan operator+(const CComSpan& span1, const CComSpan& span2);
    friend CComSpan operator-(const CComSpan& span1, const CComSpan& span2);
    
    operator double() const;
    
    void SetSpan(long nDays, long nHours, long nMins, long nSecs);

    void Invalidate();

protected:

    double  m_span;

};

/////////////////////////////////////////////////////////////////////////////
// CComDATE inline implementations

inline CComDATE CComDATE::Now()
{ SYSTEMTIME st; GetLocalTime(&st); return CComDATE(st);}
// {return CComDATE(::time(0)); } not year-2038 proof

inline CComDATE CComDATE::NowGMT ()
{
	SYSTEMTIME st; GetSystemTime(&st); return CComDATE(st);
}

inline CComDATE::CComDATE()
{ Invalidate(); }

inline CComDATE::CComDATE(const CComDATE& dtSrc)
{ m_date = dtSrc.m_date; }

inline CComDATE::CComDATE(const VARIANT& varSrc)
{ *this = varSrc; }

inline CComDATE::CComDATE(DATE dtSrc)
{ m_date = dtSrc; }

inline CComDATE::CComDATE(const char* pszSrc)
{ ParseDateTime(pszSrc); }

inline CComDATE::CComDATE(const wchar_t* pszSrc)
{ ParseDateTime(pszSrc); }

inline CComDATE::CComDATE(time_t timeSrc) // avoid for year-2038 bug
{ *this = timeSrc; }

inline CComDATE::CComDATE(const SYSTEMTIME& systimeSrc)
{ *this = systimeSrc; }

inline CComDATE::CComDATE(const FILETIME& filetimeSrc)
{ *this = filetimeSrc; }

inline CComDATE::CComDATE(long nYear, long nMonth, long nDay, long nHour, long nMin, long nSec)
{ SetDateTime(nYear, nMonth, nDay, nHour, nMin, nSec); }

inline CComDATE::CComDATE(WORD wDosDate, WORD wDosTime)
{ if( !DosDateTimeToVariantTime(wDosDate, wDosTime, &m_date) ) Invalidate(); }

inline const CComDATE& CComDATE::operator=(const CComDATE& dtSrc)
{ m_date = dtSrc.m_date; return *this; }

inline const CComDATE& CComDATE::operator=(const char* pszSrc)
{ ParseDateTime(pszSrc); return *this; }

inline const CComDATE& CComDATE::operator=(const wchar_t* pszSrc)
{ ParseDateTime(pszSrc); return *this; }

inline bool CComDATE::operator==(const CComDATE& date) const
{ return (m_date == date.m_date); }

inline bool CComDATE::operator!=(const CComDATE& date) const
{ return (m_date != date.m_date); }

inline CComDATE::operator DATE() const
{ return m_date; }

inline DATE* CComDATE::operator&()
{ return &m_date; }

inline bool CComDATE::SetDate(long nYear, long nMonth, long nDay)
{ return SetDateTime(nYear, nMonth, nDay, 0, 0, 0); }

// Set date to zero date - 12/30/1899
inline bool CComDATE::SetTime(long nHour, long nMin, long nSec)
{ return SetDateTime(1899, 12, 30, nHour, nMin, nSec); }

inline const CComDATE& CComDATE::operator+=(const CComSpan& span)
{ *this = *this + span; return *this; }

inline const CComDATE& CComDATE::operator-=(const CComSpan& span)
{ *this = *this - span; return *this; }

#ifdef __oledb_h__
inline CComDATE::CComDATE(const DBTIMESTAMP& dbts)
{ SetDateTime(dbts.year, dbts.month, dbts.day, dbts.hour, dbts.minute, dbts.second); }

inline const CComDATE& CComDATE::operator=(const DBTIMESTAMP& dbts)
{ SetDateTime(dbts.year, dbts.month, dbts.day, dbts.hour, dbts.minute, dbts.second); return *this; }

#endif  // __oledb_h__

/////////////////////////////////////////////////////////////////////////////
// CComSpan inline implementations

inline CComSpan::CComSpan()
{ Invalidate(); }

inline CComSpan::CComSpan(double db) : m_span(db) {}

inline CComSpan::CComSpan(const CComSpan& rhs)
{ m_span = rhs.m_span; }

inline CComSpan::CComSpan(long nDays, long nHours, long nMins, long nSecs)
{ SetSpan(nDays, nHours, nMins, nSecs); }

inline const CComSpan& CComSpan::operator=(double db)
{ m_span = db; return *this; }

inline const CComSpan& CComSpan::operator=(const CComSpan& span)
{ m_span = span.m_span; return *this; }

inline double CComSpan::TotalDays() const
{ _ASSERTE(IsValid()); return m_span; }

inline double CComSpan::TotalHours() const
{ _ASSERTE(IsValid()); return m_span * 24; }

inline double CComSpan::TotalMinutes() const
{ _ASSERTE(IsValid()); return m_span * 24 * 60; }

inline double CComSpan::TotalSeconds() const
{ _ASSERTE(IsValid()); return m_span * 24 * 60 * 60; }

inline long CComSpan::Days() const
{ _ASSERTE(IsValid()); return (long)m_span; }

inline bool CComSpan::operator==(const CComSpan& rhs) const
{ return m_span == rhs.m_span; }

inline bool CComSpan::operator!=(const CComSpan& rhs) const
{ return m_span != rhs.m_span; }

inline bool CComSpan::operator<(const CComSpan& rhs) const
{ return m_span < rhs.m_span; }

inline bool CComSpan::operator>(const CComSpan& rhs) const
{ return m_span > rhs.m_span; }

inline bool CComSpan::operator<=(const CComSpan& rhs) const
{ return m_span <= rhs.m_span; }

inline bool CComSpan::operator>=(const CComSpan& rhs) const
{ return m_span >= rhs.m_span; }

inline const CComSpan& CComSpan::operator+=(const CComSpan& rhs)
{ return (*this = *this + rhs); }

inline const CComSpan& CComSpan::operator-=(const CComSpan& rhs)
{ return (*this = *this - rhs); }

inline CComSpan CComSpan::operator-() const
{ return CComSpan(-m_span); }

inline CComSpan::operator double() const
{ return m_span; }

#endif  // __COMDATE_H__
