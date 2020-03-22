#include "stdafx.h"
#include "StringToLatLong.h"
#include <sstream>

//typedef std::basic_istringstream <TCHAR> tstrstream;

bool StringToLatLong 
(
	LPCTSTR AsString,
	TCHAR	NSorEW,
	double& AsDouble
)
{
	try
	{
//		This whole routine only works with ANSI chars, because of stringstream
//		Will compile either as ANSI or UNICODE, but always converts to ANSI
		USES_CONVERSION;

		std::stringstream Stream (T2CA (AsString));

		double   Deg, Min, Sec;
		char InChar,PlusCharHi,MinusCharHi,PlusCharLow,MinusCharLow;
		char DegChar = '°';
		char MinChar = '\'';
		char SecChar = '\"';

		if (NSorEW == _T('N') || NSorEW == _T('n') 
		 || NSorEW == _T('S') || NSorEW == _T('S'))
		{
			PlusCharHi   = 'N';		// This is latitude, so north is positive
			PlusCharLow  = 'n';
			MinusCharHi  = 'S';		// And south is negative;
			MinusCharLow = 's';
		}
		else
		{
			PlusCharHi   = 'E';		// This is longitude, so east is positive
			PlusCharLow  = 'e';
			MinusCharHi  = 'W';		// And west is negative;
			MinusCharLow = 'w';
		}//if

		if (!(Stream >> Deg)) throw 0;							// Get degrees
		if (!(Stream >> InChar)) throw 1;
		{
			if (InChar != DegChar)								// Next char must be ° or NESW
			{
				if (InChar == PlusCharLow || InChar == PlusCharHi)
				{
					AsDouble = Deg;
					return true;
				}
				else if (InChar == MinusCharLow || InChar == MinusCharHi)
				{
					AsDouble = -Deg;
					return true;
				}
				else
					throw 2;
				//if
			}//if
		}//if
		if (!(Stream >> Min))									// May be minutes, may be N,E,S or W
		{
			Stream.clear ();									// Clear error flag

			if (Stream >> InChar)								// Okay, it's NES or W
			{
				if (InChar == PlusCharLow || InChar == PlusCharHi)
				{
					AsDouble = Deg;
					return true;
				}
				else if (InChar == MinusCharLow || InChar == MinusCharHi)
				{
					AsDouble = -Deg;
					return true;
				}
				else
					throw 2;
				//if
			}
			else
				throw 3;
			//if
		}//if
		if (!(Stream >> InChar) || InChar != MinChar) throw 4;	// Must be '
		if (!(Stream >> Sec))									// May be seconds of NES or W
		{
			Stream.clear ();									// Clear error flag

			if (Stream >> InChar)								// Okay, it's NES or W
			{
				if (InChar == PlusCharLow || InChar == PlusCharHi)
				{
					AsDouble = Deg + Min/60.0;
					return true;
				}
				else if (InChar == MinusCharLow || InChar == MinusCharHi)
				{
					AsDouble = - (Deg + Min/60.0);
					return true;
				}
				else
					throw 5;
				//if
			}
			else
				throw 6;
			//if
		}//if
		if (!(Stream >> InChar) || InChar != SecChar) throw 7;	// Must be "
		if (Stream >> InChar)									// Expecting NES or W
		{
			Stream.clear ();									// Clear error flag

			if (InChar == PlusCharLow || InChar == PlusCharHi)
			{
				AsDouble = Deg + Min/60.0 + Sec/3600.0;
				return true;
			}
			else if (InChar == MinusCharLow || InChar == MinusCharHi)
			{
				AsDouble = - (Deg + Min/60.0 + Sec/3600.0);
				return true;
			}
			else
				throw 8;
			//if
		}
		else
			throw 9;
		//if
	}
	catch (...)
	{
		return false;
	}//try
}//StringToLatLong
