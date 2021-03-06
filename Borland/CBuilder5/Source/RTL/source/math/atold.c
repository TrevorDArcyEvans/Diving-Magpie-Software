/*------------------------------------------------------------------------
 * filename - atold.c
 *
 * function(s)
 *        _atold - converts a string to a long double
 *        _wtold - converts a wide-character string to a long double
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 10.0
 *
 *      Copyright (c) 1987, 2000 by Inprise Corporation
 *      All Rights Reserved.
 *
 */

/* $Revision:   9.0  $        */

#include <stdlib.h>
#include <tchar.h>

/*--------------------------------------------------------------------------*

Name            _atold, _wtold - converts a string to a long double number

Usage           long double _atold(const char *strP);
                long double _atold(const wchar_t *strP);

Prototype in    stdlib.h & math.h

Description     _atold converts a string pointed to by strP to a long double;
                this functions recognizes:
                        - an optional string of tabs and spaces
                        - an optional sign
                        - the  a string of  digits and an  optional decimal
                          point
                        - the  an optional e  or E followed  by an optional
                          signed integer

                The first unrecognized character ends the conversion. There
                are no provisions for overflow.

Return value    _atold returns  the converted value  of the input  string. If
                the  string cannot  be converted  to a  number of  the type
                long double, the return value is 0.

*---------------------------------------------------------------------------*/

long double _RTLENTRY _EXPFUNC _ttold(const _TCHAR *strP)
{
    return _tcstold(strP, NULL);
}
