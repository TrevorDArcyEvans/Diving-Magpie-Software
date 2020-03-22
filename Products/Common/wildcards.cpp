/* Wildcards.cpp - Implementation of wildcard functions
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

   Originally developed (in C) by Florian Schintke (TU Berlin).

   For a description of the wildcards see the MatchWildcard function. 

   For a list of examples, see the bottom of this file.

$History: Wildcards.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Hans         Date: 21-07-00   Time: 7:10
 * Updated in $/METCOM/Projects/BulletinFilterServer
 * with IsValidFilter

*/
#include "stdafx.h"
#include <string>

#include "StringFunctions.h"

using namespace std;
using namespace NStringFunctions;

/* The classes CWildcardTester* are defined as module-local classes.
   They should not be used in client code.
*/

class CWildcardTesterAnsii
{
private:

    int set ( const char **wildcard , const char **test );
    int asterisk ( const char **wildcard , const char **test );

public:

    int wildcardfit ( const char *wildcard , const char *test );
} ;

class CWildcardTesterUnicode 
{
private:

    int set ( const wchar_t **wildcard , const wchar_t **test );
    int asterisk ( const wchar_t **wildcard , const wchar_t **test );

public:

    int wildcardfit ( const wchar_t *wildcard , const wchar_t *test );
} ;


/* wildcardfit - test a string against a wildcard

   Input : wildcard - NUL-terminated character array with wildcards:
                      "*" = Matches any string, any number of characters long. 
                            For example, "a*a" could represent "ada", "alfa", 
                            "alfalfa", "appalacia", or "abcdefghijklmnopqrstua".
                      "?" = Matches any single character. For example, "a?a" could 
                            represent "aba", "aca", "aaa", or "a9a".
                      "[]"= Matches either a list or a range of characters to a 
                            single character. For example, "a[b19]a" would match 
                            "aba" and "a9a", but not "aca". Also, "a[a-f]a" would match
                            "aaa" and "afa", but not "aga" or "aza".
           test     - NUL-terminated character array with test string.

   Returns: 0 - NOT matching
            1 - Matching
*/
int CWildcardTesterAnsii::wildcardfit (const char *wildcard , const char *test) 
{
    int fit = 1;

    for ( ; ( '\000' != *wildcard ) && ( 1 == fit ) && ( '\000' != *test ); wildcard++ ) {

        switch (*wildcard) {

            case '[':   
                wildcard++ ; /* leave out the opening square bracket */
                fit = set ( &wildcard , &test );
                /* we don't need to decrement the wildcard as in case */
                /* of asterisk because the closing ] is still there */
                break;

            case '?':   
                test++ ;
                break;

            case '*':  
                fit = asterisk (&wildcard, &test);
                /* the asterisk was skipped by asterisk() but the loop will */
                /* increment by itself. So we have to decrement */
                wildcard-- ;
                break;

            default:
                fit = (int)(*wildcard == *test);
                test++ ;
                break;
        } //switch
    } //for

    while ( (*wildcard == '*') && (1 == fit) ) {
        /* here the teststring is empty otherwise you cannot */
        /* leave the previous loop */
        wildcard++ ;
    }

    return (int) ( (1 == fit) && ('\0' == *test) && ('\0' == *wildcard) );
}

/* set - Scans a set of characters 

         wildcard is set to the closing ] and test is unmodified if mismatched 
         and otherwise the char pointer is pointing to the next character.

   Input:   wildcard - address of NUL-terminated character array
            test     - address of NUL-terminated character array
   
   Returns: returns 0 if the set mismatches at this 
            position in the teststring and 1 if it is matching                    
*/
int CWildcardTesterAnsii::set ( const char **wildcard , const char **test ) 
{
    int fit = 0;
    int negation = 0;
    int at_beginning = 1;

    if ( '!' == **wildcard ) {
        negation = 1;
        (*wildcard)++ ;
    } //if

    while ( ( ']' != **wildcard ) || ( 1 == at_beginning ) ) {

        if ( 0 == fit ) {
            if (    ('-' == **wildcard)
                 && ( ( *(*wildcard - 1) ) < ( *(*wildcard + 1) ) )
                 && ( ']' != *(*wildcard + 1) )
                 && ( 0 == at_beginning ) ) {

                    if (    ( (**test) >= ( *(*wildcard - 1) ) )
                         && ( (**test) <= ( *(*wildcard + 1) ) ) ) {

                        fit = 1;
                        (*wildcard)++ ;
                    }
            }
            else if ( (**wildcard) == (**test) ) {
                fit = 1;
            } //if
        } //if
        (*wildcard)++ ;
        at_beginning = 0;
    } //while

    if (1 == negation)
        fit = 1 - fit; /* change from zero to one and vice versa */

    if (1 == fit)
        (*test)++ ;

    return (fit);
}

/*  asterisk - scans an asterisk 

    Input:   wildcard - address of NUL-terminated character array, 
                        starting with asterisk
             test     - address of NUL-terminated character array
   
    Returns: 0 = NOT matching
             1 = matching
*/
int CWildcardTesterAnsii::asterisk ( const char **wildcard, const char **test ) 
{
    /* Warning: uses multiple returns */

    int fit = 1;
    const char *oldwildcard;
    const char *oldtest;

    /* erase the leading asterisk */
    (*wildcard)++ ;

    while (    ('\000' != (**test))
            && ( ('?' == **wildcard) || ('*' == **wildcard) ) ) {

            if ( '?' == **wildcard )
                (*test)++ ;

            (*wildcard)++ ;
    } //while

    /* Now it could be that test is empty and wildcard contains */
    /* aterisks. Then we delete them to get a proper state */
    while ( '*' == (**wildcard) )
        (*wildcard)++ ;

    if ( ( '\0' == (**test) ) && ( '\0' != (**wildcard) ) )
        return (fit = 0);

    if ( ( '\0' == (**test) ) && ( '\0' == (**wildcard) ) )
        return (fit = 1);
    else {
        /* Neither test nor wildcard are empty!          */
        /* the first character of wildcard isn't in [*?] */
        oldwildcard = *wildcard;
        oldtest = *test;
        do {
            if ( 0 == wildcardfit( *wildcard , ( *test ) ) )
                oldtest++ ;

            *wildcard = oldwildcard;
            *test = oldtest;
            /* skip as much characters as possible in the teststring */
            /* stop if a character match occurs */
            while (    ( (**wildcard) != (**test) )
                    && ( '['  != (**wildcard) )
                    && ( '\0' != (**test) ) ) {

                (*test)++ ;

            } //while

            oldwildcard = *wildcard;
            oldtest = *test;
        } while ( ( ('\0' != **test) ) 
                       ? ( 0 == wildcardfit(*wildcard, (*test)) )
                       : ( 0 != (fit = 0) ) );

        if ( ('\0' == **test) && ('\0' == **wildcard) )
            fit = 1;

        return (fit);
    } //else
}


/* wildcardfit - UNICODE version
*/
int CWildcardTesterUnicode::wildcardfit (const wchar_t *wildcard, const wchar_t *test) 
{
    int fit = 1;

    for ( ; ( L'\000' != *wildcard ) && ( 1 == fit ) && ( L'\000' != *test ); wildcard++ ) {

        switch (*wildcard) {

            case L'[':   
                wildcard++ ; /* leave out the opening square bracket */
                fit = set ( &wildcard , &test );
                /* we don't need to decrement the wildcard as in case */
                /* of asterisk because the closing ] is still there */
                break;

            case L'?':   
                test++ ;
                break;

            case L'*':  
                fit = asterisk (&wildcard, &test);
                /* the asterisk was skipped by asterisk() but the loop will */
                /* increment by itself. So we have to decrement */
                wildcard-- ;
                break;

            default:
                fit = (int)(*wildcard == *test);
                test++ ;
                break;
        } //switch
    } //for

    while ( (*wildcard == L'*') && (1 == fit) ) {
        /* here the teststring is empty otherwise you cannot */
        /* leave the previous loop */
        wildcard++ ;
    }

    return (int) ( (1 == fit) && (L'\0' == *test) && (L'\0' == *wildcard) );
}

/* set - Scans a set of characters 
*/
int CWildcardTesterUnicode::set ( const wchar_t **wildcard , const wchar_t **test ) 
{
    int fit = 0;
    int negation = 0;
    int at_beginning = 1;

    if ( L'!' == **wildcard ) {
        negation = 1;
        (*wildcard)++ ;
    } //if

    while ( ( L']' != **wildcard ) || ( 1 == at_beginning ) ) {

        if ( 0 == fit ) {
            if (    (L'-' == **wildcard)
                 && ( ( *(*wildcard - 1) ) < ( *(*wildcard + 1) ) )
                 && ( L']' != *(*wildcard + 1) )
                 && ( 0 == at_beginning ) ) {

                    if (    ( (**test) >= ( *(*wildcard - 1) ) )
                         && ( (**test) <= ( *(*wildcard + 1) ) ) ) {

                        fit = 1;
                        (*wildcard)++ ;
                    }
            }
            else if ( (**wildcard) == (**test) ) {
                fit = 1;
            } //if
        } //if
        (*wildcard)++ ;
        at_beginning = 0;
    } //while

    if (1 == negation)
        fit = 1 - fit; /* change from zero to one and vice versa */

    if (1 == fit)
        (*test)++ ;

    return (fit);
}

/*  asterisk - scans an asterisk
*/
int CWildcardTesterUnicode::asterisk ( const wchar_t **wildcard, const wchar_t **test ) 
{
    /* Warning: uses multiple returns */

    int fit = 1;
    const wchar_t *oldwildcard;
    const wchar_t *oldtest;

    /* erase the leading asterisk */
    (*wildcard)++ ;

    while (    (L'\000' != (**test))
            && ( (L'?' == **wildcard) || (L'*' == **wildcard) ) ) {

            if ( L'?' == **wildcard )
                (*test)++ ;

            (*wildcard)++ ;
    } //while

    /* Now it could be that test is empty and wildcard contains */
    /* aterisks. Then we delete them to get a proper state */
    while ( L'*' == (**wildcard) )
        (*wildcard)++ ;

    if ( ( L'\0' == (**test) ) && ( L'\0' != (**wildcard) ) )
        return (fit = 0);

    if ( ( L'\0' == (**test) ) && ( L'\0' == (**wildcard) ) )
        return (fit = 1);
    else {
        /* Neither test nor wildcard are empty!          */
        /* the first character of wildcard isn't in [*?] */
        oldwildcard = *wildcard;
        oldtest = *test;
        do {
            if ( 0 == wildcardfit( *wildcard , ( *test ) ) )
                oldtest++ ;

            *wildcard = oldwildcard;
            *test = oldtest;
            /* skip as much characters as possible in the teststring */
            /* stop if a character match occurs */
            while (    ( (**wildcard) != (**test) )
                    && ( L'['  != (**wildcard) )
                    && ( L'\0' != (**test) ) ) {

                (*test)++ ;

            } //while

            oldwildcard = *wildcard;
            oldtest = *test;
        } while ( ( (L'\0' != **test) ) 
                       ? ( 0 == wildcardfit(*wildcard, (*test)) )
                       : ( 0 != (fit = 0) ) );

        if ( (L'\0' == **test) && (L'\0' == **wildcard) )
            fit = 1;

        return (fit);
    } //else
}

/* MatchWildcard - Test for a wildcard match

   Input : wildcard - NUL-terminated character array with wildcards:
                      "*" = Matches any string, any number of characters long. 
                            For example, "a*a" could represent "ada", "alfa", 
                            "alfalfa", "appalacia", or "abcdefghijklmnopqrstua".
                      "?" = Matches any single character. For example, "a?a" could 
                            represent "aba", "aca", "aaa", or "a9a".
                      "[]"= Matches either a list or a range of characters to a 
                            single character. For example, "a[b19]a" would match 
                            "aba" and "a9a", but not "aca". Also, "a[a-f]a" would match
                            "aaa" and "afa", but not "aga" or "aza".
           test     - NUL-terminated character array with test string.

   Returns: TRUE if matching
*/
bool NStringFunctions::MatchWildcard(const char *wildcard, const char *test) 
{
    CWildcardTesterAnsii tester;
    return tester.wildcardfit(wildcard, test) ? true : false;
}

bool NStringFunctions::MatchWildcard(const string &wildcard, const string &test)
{
    return MatchWildcard(wildcard.c_str(), test.c_str());
}

bool NStringFunctions::MatchWildcard( const wchar_t *wildcard, const wchar_t *test ) 
{
    CWildcardTesterUnicode tester;
    return tester.wildcardfit(wildcard, test) ? true : false;
}

bool NStringFunctions::MatchWildcard(const wstring &wildcard, const wstring &test)
{
    return MatchWildcard(wildcard.c_str(), test.c_str());
}

/* IsValidFilter - Validates a filter (i.e. any string with wild cards)

   Input: filter - a string with wildcards ('*' or '?'), e.g. "SA*01 EHAM"
          sample - a format string with:
                      'A' - any alphanumerical character
                      '0' - any digit
                      other characters should literally match

   Returns : TRUE if valid
*/
bool NStringFunctions::IsValidFilter(const basic_string<TCHAR>& filter, const basic_string<TCHAR>& sample)
{
	// Is it the correct length
	if ((filter.length() < 1) || (filter.length() > sample.length()))
		return false;

	basic_string<TCHAR> wildcard = filter;

	for (basic_string<TCHAR>::size_type i = 0; i < filter.length(); i++)
	{
		if ( _istalpha(wildcard[i]) )
			wildcard[i] = _T('A');
		else if ( _istdigit(wildcard[i]) )
			wildcard[i] = _T('0');
	}

	return NStringFunctions::MatchWildcard(wildcard, sample);	
}

#if 0
Examples of test results. 
Note: 
"(tt)" means: both requested and actual result match. 
"(ff)" means: both requested and actual result don't match. 

(tt) ['', '']
(ff) ['', 'a']
(tt) ['a', 'a']
(ff) ['a', 'b']
(tt) ['?', 'b']
(tt) ['??', 'bc']
(tt) ['?c', 'bc']
(tt) ['b?', 'bc']
(tt) ['[a-z]', 'b']
(ff) ['[A-Z]', 'b']
(tt) ['*', 'a']
(tt) ['**', 'a']
(tt) ['*', '']
(tt) ['*bc*hij', 'abcdfghij']
(ff) ['*b*a*', 'b']
(ff) ['*bc*hik', 'abcdfghij']
(tt) ['abc*', 'abc']
(tt) ['abc**', 'abc']
(tt) ['[!]]', '!']
(ff) ['[!]]', ']']
(tt) ['[!abc]', 'd']
(ff) ['[!abc]', 'b']
(tt) ['*???', 'abc']
(ff) ['*???', 'ab']
(tt) ['*???', 'abcd']
(tt) ['*?*', 'abcd']
(tt) ['*bc', 'abc']
(ff) ['*cc', 'abc']
(ff) ['[a-c]*', 'd']
(tt) ['*[a-e]', 'd']
(ff) ['*a*', 'de']
(ff) ['*[a-c]', 'd']
(ff) ['[a-c]', 'd']
(ff) ['[b-d]', 'a']
(tt) ['[]abc]', 'b']
(ff) ['[]abc]', 'd']
(tt) ['[z-a]', '-']
(ff) ['[z-a]', 'b']
(tt) ['[A-]', '-']
(ff) ['[A-]', ']']
(tt) ['[-a]', '-']
(tt) ['[-[]', '-']
(tt) ['[-]', '-']
(tt) ['[!-b]', 'a']
(ff) ['[!-b]', '-']
(ff) ['[-b]', 'a']
(tt) ['[a-g]lorian', 'florian']
(ff) ['[a-g]*rorian', 'f']
(tt) ['*???*', '123']

#endif