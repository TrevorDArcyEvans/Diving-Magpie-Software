/* +++Date last modified: 05-Jul-1997 */

/*
** header file for:
**
**  XSTRCMP.c - Simple string pattern matching functions using DOS
**              wildcards ('?' & '*').
**
**  Derived from code by Arjan Kentner (submitted by Steve Summit),
**  modified by Bob Stout.
*/

#ifndef XSTRCMP_H
#define XSTRCMP_H

#include <stdio.h>                  /* For NULL                         */
#include <ctype.h>                  /* For toupper()                    */
#include <assert.h>                 /* For assert()                     */

typedef enum {Error_ = -1, Success_, False_ = 0, True_} Boolean_T;

Boolean_T   xstrcmp  (LPCTSTR pat,LPCTSTR str);
Boolean_T   xstricmp (LPCTSTR pat,LPCTSTR str);

#endif /* XSTRCMP_H */

