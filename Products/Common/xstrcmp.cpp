/* +++Date last modified: 05-Jul-1997 */

/*
**  XSTRCMP.C - Simple string pattern matching functions using DOS
**              wildcards ('?' & '*').
**
**  Derived from code by Arjan Kentner (submitted by Steve Summit),
**  modified by Bob Stout.
*/

#include "stdafx.h"
#include "xStrCmp.h"

/*
**  Arguments: 1 - Pattern to match
**             2 - String to match
**
**  Returns: True_ if match
**           False_ if no match
**           Error_ if passed a null pointer (see below)
**
**  Notes: 1. Two versions are supplied, one case-sensitive and one not.
**         2. Each version consists of a recursive static function which
**            does all the work, and a wrapper which checks for null
**            pointers before calling the static function.
**         3. If assert() is enabled (i.e. if NDEBUG is undefined or false),
**            the wrapper functions will abort with an assertion error in
**            case a null pointer is passed.
**         4. If assert() is disabled (i.e. if NDEBUG is defined), the
**            wrapper function will return Error_ to the calling program in
**            case a null pointer is passed.
*/

/*
**  Case-sensitive version
*/

static Boolean_T patmat (LPCTSTR pat,LPCTSTR str)
{
      switch (*pat)
      {
      case '\0':
            return (Boolean_T ) (!*str);

      case '*' :
            return (Boolean_T ) (patmat(pat+1, str) || *str && patmat(pat, str+1));

      case '?' :
            return (Boolean_T ) (*str && patmat(pat+1, str+1));

      default  :
            return (Boolean_T ) ((*pat == *str) && patmat(pat+1, str+1));
      }
}

Boolean_T xstrcmp (LPCTSTR pat,LPCTSTR str)
{
      assert(str && pat);
      if (NULL == str || NULL == pat)
            return Error_;
      else  return(patmat(pat, str));
}

/*
**  Case-insensitive version
*/

static Boolean_T patimat (LPCTSTR pat,LPCTSTR str)
{
      switch (*pat)
      {
      case '\0':
            return (Boolean_T ) (!*str);

      case '*' :
            return (Boolean_T ) (patimat(pat+1, str) || *str && patimat(pat, str+1));

      case '?' :
            return (Boolean_T ) (*str && patimat(pat+1, str+1));

      default  :
            return (Boolean_T ) ((toupper(*pat) == toupper(*str)) && patimat(pat+1, str+1));
      }
}

Boolean_T xstricmp (LPCTSTR pat,LPCTSTR str)
{
      assert(str && pat);
      if (NULL == str || NULL == pat)
            return Error_;
      else  return(patimat(pat, str));
}

#ifdef TEST

#include <stdio.h>

main(int argc, char *argv[])
{
      if (3 != argc)
      {
            puts("Usage: XSTRCMP mask string");
            return -1;
      }
      printf("xstrcmp(\"%s\", \"%s\") returned %d\n", argv[1], argv[2],
            xstrcmp(argv[1], argv[2]));

      printf("xstricmp(\"%s\", \"%s\") returned %d\n", argv[1], argv[2],
            xstricmp(argv[1], argv[2]));

      printf("xstricmp(NULL, \"%s\") returned %d\n", argv[2],
            xstricmp(NULL, argv[2]));

      printf("xstricmp(\"%s\", NULL) returned %d\n", argv[1],
            xstricmp(argv[1], NULL));

      printf("xstricmp(NULL, NULL) returned %d\n", xstricmp(NULL, NULL));

      return 0;
}

#endif /* TEST */

