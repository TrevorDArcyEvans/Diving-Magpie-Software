/* StringFunctions.cpp - functions for NUL-terminated strings
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

$History: StringFunctions.cpp $
 * 
 * *****************  Version 7  *****************
 * User: Hans         Date: 21-07-00   Time: 7:12
 * Updated in $/METCOM/Projects/DupHeaderFilterServer
 * IsValidFilter moved to Wildcard.cpp
 * 
 * *****************  Version 6  *****************
 * User: Hans         Date: 21-07-00   Time: 5:15
 * Updated in $/METCOM/Projects/BulletinFilterServer
 * with IsValidFilter

*/

#include "stdafx.h"
#include <string.h>
#include <ctype.h>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include "StringFunctions.h"

using namespace std;

/* UpcaseString - Convert the characters of a zero-terminated string to uppercase

   INOUT   : char * s                  
   RETURNS : pointer to s              
*/
char * NStringFunctions::UpcaseString ( char *s )
{
  int i ;

  i = 0 ;
  while ( s[i] )
  {
    s[i] = toupper ( s[i] ) ;
    i++ ;
  } // while
  return s ;

} // function upcase_string

/* UpcaseString - UNICODE version
*/
wchar_t * NStringFunctions::UpcaseString ( wchar_t *s )
{
  int i ;

  i = 0 ;
  while ( s[i] )
  {
    s[i] = towupper ( s[i] ) ;
    i++ ;
  } // while
  return s ;

} // function upcase_string

/* UpcaseString  -  Convert all characters in a (w)string to upper case
                    STL version for ANSI strings

   Parameter: takes const reference to string
   Returns  : string converted to upper case
*/
string NStringFunctions::UpcaseString(const string& str)
{
    string newstr(str);

    for (size_t index = 0; index < str.length(); index++) {
        if (islower(str[index])) {
                    newstr[index] = toupper(str[index]);
        }
    }
    return newstr;
}

/* UpcaseString  -  Convert all characters in a wstring to upper case
                    STL version for UNICODE strings

   Parameter: takes const reference to string
   Returns  : wstring converted to upper case
*/
wstring NStringFunctions::UpcaseString(const wstring& str)
{
    wstring newstr(str);

    for (size_t index = 0; index < str.length(); index++) {
        if (iswlower(str[index])) {
                    newstr[index] = towupper(str[index]);
        }
    }
    return newstr;
}
   

/* RemoveChars - Remove all occurences of a character from a zero-terminated string

  IN      : char c : character to be removed                                 
  INOUT   : char * s                  
  RETURNS : pointer to s
*/
char *NStringFunctions::RemoveChars ( char * s , const char c )
{
int i,j ;

  i = 0 ;
  j = 0 ;
  while ( s[j] )
  {
    if ( s[j] != c ) s[i++] = s[j];
    j++ ;
  }  // while
  s[i] = '\0' ;
  return s ;
} // function remove_chars

wchar_t *NStringFunctions::RemoveChars ( wchar_t * s , const wchar_t c )
{
int i,j ;

  i = 0 ;
  j = 0 ;
  while ( s[j] )
  {
    if ( s[j] != c ) s[i++] = s[j];
    j++ ;
  }  // while
  s[i] = L'\0' ;
  return s ;
} // function remove_chars

/* CompressString - Replace multiple spaces by a single space in a zero-terminated string

   INOUT   : char * s                  
*/
void NStringFunctions::CompressString ( TCHAR * s )
{
  TCHAR * t ;

  t = s ;
  if ( *s ) 
    s++ ;
  while ( *s )
  {
    if ( ! ( ( ( *s ) == _T(' ') ) && ( ( *t ) == _T(' ') ) ) )
    {
      t++ ;
      *t = *s ;
    } // if
    s++ ;
  } // while
  if ( *t ) 
    t++ ;
  *t = _T('\0') ;
} // function compress_string

/* TrimString - Remove leading and trailing spaces from a zero-terminated string.\

   INOUT   : s  
*/                 
void NStringFunctions::TrimString (TCHAR * s)
{
  if (s)
  {
    TCHAR* t = s ;

    while (*s == _T(' ')) s++ ;
    while (*s) *t++ = *s++ ;
    *t = _T(' ') ;
    while (*t == _T(' ')) t-- ;
    *++t = _T('\0') ;
  } // if

} // function trim_string

/*  CharCount - Count the number of occurences of a character in a zero-terminated string.

    IN      : char * s : pointer to string                                     
              char c   : character to be counted                               
    RETURN  : number of characters found
*/
int NStringFunctions::CharCount ( const TCHAR *s , TCHAR c )
{
int n ;

  n = 0 ;
  while ( *s )
  {
    if ( *s  == c ) n++ ;
    s++ ;
  } // while
  return n ;
} // function char_count

/*  StringCount - Count the number of occurences of a zero-terminated substring in a zero-terminated string.

    IN      : s : pointer to string to search in                        
              substring : pointer to string to be searched for          
    RETURN  : number of strings found   
*/
int NStringFunctions::StringCount ( const TCHAR *s , const TCHAR *substring ) 
{
  int n ;
  TCHAR *cp ;

  n = 0 ;
  do 
  {
    cp = _tcsstr ( s , substring ) ;
    if ( cp ) n++ ;
    s = cp + 1 ;
  }
  while ( cp ) ;
  return n ;
} // function

/*  ReplaceChars - Replace characters in a string

    IN      : old_char : character to be replaced                              
              new_char : replace-character                                     
    INOUT   : char * s                  
    RETURNS : pointer to s
*/
TCHAR * NStringFunctions::ReplaceChars ( TCHAR *s , TCHAR old_char , TCHAR new_char )
{
int i ;

  i = 0 ;
  while ( s[i] )
  {
    if ( s[i] == old_char )
      s[i] = new_char ;
    i++ ;
  } // while
  return s ;
} // function replace_chars


/* ReplaceStrings - Replace substrings in a string                                   

   IN      : char *s             : string in which substrings must be replaced
             char *substring     : substring to be replaced                   
             char *newstring     : string to replace substring by             
   OUT     : char * resultstring : resulting string                           
             int size            : max size of resultstring                   
*/
void NStringFunctions::ReplaceStrings ( TCHAR *s , TCHAR *substring , TCHAR *newstring , TCHAR * resultstring , int size )
{
  TCHAR *cp ;

  _tcscpy ( resultstring , _T("") ) ;
  do
  { 
    cp = _tcsstr ( s , substring ) ;
    if ( cp )    // substring found in s ?
    {
      *cp = _T('\0');
      if ( _tcslen ( resultstring ) + _tcslen ( s ) < (size_t)size ) _tcscat ( resultstring , s ) ;
      if ( _tcslen ( resultstring ) + _tcslen ( newstring ) < (size_t)size ) _tcscat ( resultstring , newstring ) ;
      s = cp + _tcslen ( substring ) ;
    } // if 
  }
  while ( cp ) ;
  if ( _tcslen ( resultstring ) + _tcslen ( s ) < (size_t)size ) _tcscat ( resultstring , s ) ;
} // function replace_strings


/*  GetWord - Determines the 'wordnr'-th word in a string 's' where words are separated by a 'separator'-character.
              The result is placed in 'word'                                   

    IN      : char *s           : string with words                            
              int wordnr        : word-number that has to be extracted (first word is number 1)                       
              char separator    : words are separated by this character        
              int max_word_size : number of characters reserved to store 'word' (including terminating 0-character)   
    OUT     : char * word               
    RETURN  : 0 = ERROR (not so many words in s)                               
              1 = OK                    
*/
int NStringFunctions::GetWord ( const char * s , int wordnr , char separator , char * word , int max_word_size )
{
  int i ;
  int j ;

  strcpy ( word , "" ) ;

  // Find the start of the 'wordnr'-th word -> i
  i = 0;
  while ( ( wordnr > 1 ) && ( s[i] != '\0' ) )
  {
    if (s[i] == separator) 
      wordnr-- ;
    i++ ;
  } // while

  // Find the first separator-character following position 'i'
  j = i ;
  while ( ( s[j] != '\0' ) && ( s[j] != separator ) )
    j++ ;

  if ( s[i] != '\0' )
  {
    if ( (j - i) >= max_word_size ) 
      j = i + max_word_size - 1 ;
    strncpy ( word , &s[i] , j - i ) ;
    word[j-i] = '\0' ;
  } // if 

  return ( s[i] != '\0' ) ;
} // function get_word 


int NStringFunctions::GetWord ( const wchar_t * s , int wordnr , wchar_t separator , wchar_t * word , int max_word_size )
{
  int i ;
  int j ;

  wcscpy ( word , L"" ) ;

  // Find the start of the 'wordnr'-th word -> i
  i = 0;
  while ( ( wordnr > 1 ) && ( s[i] !=  '\0' ) )
  {
    if (s[i] == separator) 
      wordnr-- ;
    i++ ;
  } // while

  // Find the first separator-character following position 'i'
  j = i ;
  while ( ( s[j] != '\0' ) && ( s[j] != separator ) )
    j++ ;

  if ( s[i] != '\0' )
  {
    if ( (j - i) >= max_word_size ) 
      j = i + max_word_size - 1 ;
     wcsncpy ( word , &s[i] , j - i ) ;
    word[j-i] = '\0' ;
  } // if 

  return ( s[i] != '\0' ) ;
} // function get_word 



/* GetWord - ANSI STL versions 

   Returns: the specified word or an empty string if not found
*/
string NStringFunctions::GetWord ( const char * s , int wordnr , char separator )
{
    const int MAX_WORD = 256;
    char   word[MAX_WORD];
    string strResult;

    if (GetWord(s, wordnr, separator, word, MAX_WORD)) {
        strResult = word;
    }
    return strResult;
}

string NStringFunctions::GetWord ( const string& s , int wordnr , char separator )
{
    return GetWord(s.c_str(), wordnr, separator);
}

/* GetWord - UNICODE STL versions

   Returns: the specified word or an empty string if not found
*/

wstring NStringFunctions::GetWord ( const wchar_t * s , int wordnr , wchar_t separator )
{
    const int MAX_WORD = 256;
    wchar_t  word[MAX_WORD];
    wstring  strResult;

    if (GetWord(s, wordnr, separator, word, MAX_WORD)) {
        strResult = word;
    }
    return strResult;
}

wstring NStringFunctions::GetWord ( const wstring& s, int wordnr, wchar_t separator )
{
    return GetWord(s.c_str(), wordnr, separator);
}

/* TestFormat  - Test if a string matches a specified format                                   
 
   IN      : s      - string to be tested
             format - format string (case-insensitive)
                         A  = alphabetic character [A..Z] or [a..z]
                         9  = digit [0..9]
                         S  = space, ASCII [0x09..0x0D] or 0x20
                         B  = alphabetic character or digit 
                         P  = printable character
                         .  = punctuation character
                         \0 = NULL character
                         ?  = any character
             count   - number of characters to test
                       count should not exceed the allocated buffer sizes 
                       of s or format
                       if count < 0, all characters in s are tested (s should be
                       NUL-terminated)
    RETURNS : 0 = ERROR
              1 = OK 

    Note: this function returns int, not bool, because isspace etc return int
*/
int NStringFunctions::TestFormat(const char* s, const char* format, int count)
{
    int  nResult;
    int  i;
    char chTest;
    char chFormat;

    if (s == NULL || format == NULL)
        return 0;

    if (count < 0) // special case
        count = strlen(s);

    if (count == 0)
        return 1;

    i = 0;
    do {
        chFormat = toupper(format[i]);
        chTest   = s[i];

        nResult = 0;
        if (chFormat == 'A') {
            nResult = isalpha(chTest);
        } else if (chFormat == '9') {
            nResult = isdigit(chTest);
        } else if (chFormat == 'S') {
            nResult = isspace(chTest);
        } else if (chFormat == 'B') {
            nResult = isalnum(chTest);
        } else if (chFormat == 'P') {
            nResult = isprint(chTest);
        } else if (chFormat == '.') {
            nResult = ispunct(chTest);
        } else if (chFormat == '\0') {
            nResult = (chTest == '\0');  // NULL character
        } else if (chFormat == '?') {
            nResult = 1;     //  any character
        }
        i++;
    } while (i < count && nResult);

    return nResult;
}

int NStringFunctions::TestFormat(const wchar_t* s, const wchar_t* format, int count)
{
    int  nResult;
    int  i;
    wchar_t chTest;
    wchar_t chFormat;

    if (s == NULL || format == NULL)
        return 0;

    if (count < 0) // special case
        count =  wcslen (s);

    if (count == 0)
        return 1;

    i = 0;
    do {
        chFormat = towupper(format[i]);
        chTest   = s[i];

        nResult = 0;
        if (chFormat == L'A') {
            nResult = iswalpha(chTest);
        } else if (chFormat == L'9') {
            nResult = iswdigit(chTest);
        } else if (chFormat == L'S') {
            nResult = iswspace(chTest);
        } else if (chFormat == L'B') {
            nResult = iswalnum(chTest);
        } else if (chFormat == L'P') {
            nResult = iswprint(chTest);
        } else if (chFormat == L'.') {
            nResult = iswpunct(chTest);
        } else if (chFormat == L'\0') {
            nResult = (chTest == L'\0');  // NULL character
        } else if (chFormat == L'?') {
            nResult = 1;     //  any character
        }
        i++;
    } while (i < count && nResult);

    return nResult;
}

/* TestFormat2   - Test if a string matches a specified format                                   
 
   IN      : s          - string to be tested
             format     - format string
                          Every character in the format string, not being a '?'
                          should match the character at the same position in
                          the test string.
             count      - number of characters to test
                          count should not exceed the allocated buffer sizes 
                          of s or format
                          if count < 0, all characters in s are tested (s should be
                          NUL-terminated)
             match_case - if TRUE, the test is case-sensitive

   RETURNS : 0 = ERROR  // To be compatable with TestFormat
             1 = OK                                 
*/
int NStringFunctions::TestFormat2(const char *s, const char *format, int count, bool match_case)
{
    int  nResult;
    int  i;
    char chTest;
    char chFormat;

    if (s == NULL || format == NULL)
        return 0;

    if (count < 0) // special case
        count = strlen(s);

    if (count == 0)
        return 1;

    i = 0;
    do {
        if (match_case) {
            chFormat = format[i];
            chTest   = s[i];
        } else {
            chFormat = toupper(format[i]);  // convert to same case
            chTest   = toupper(s[i]);
        }

        nResult = 0;
        if (chFormat == '?') {
            nResult = 1;     //  any character
        } else {
            nResult = (chTest == chFormat);
        }
        i++;
    } while (i < count && nResult);

    return nResult;
}

int NStringFunctions::TestFormat2(const wchar_t *s, const wchar_t *format, int count, bool match_case)
{
    int  nResult;
    int  i;
    wchar_t chTest;
    wchar_t chFormat;

    if (s == NULL || format == NULL)
        return 0;

    if (count < 0) // special case
        count = wcslen(s);

    if (count == 0)
        return 1;

    i = 0;
    do {
        if (match_case) {
            chFormat = format[i];
            chTest   = s[i];
        } else {
            chFormat = towupper(format[i]);  // convert to same case
            chTest   = towupper(s[i]);
        }

        nResult = 0;
        if (chFormat == L'?') {
            nResult = 1;     //  any character
        } else {
            nResult = (chTest == chFormat);
        }
        i++;
    } while (i < count && nResult);

    return nResult;
}

/* GetStartOfNextLine - Get a pointer to the start of the next line

   INPUT   : s - pointer to NUL-terminated character array
   RETURNS : pointer to the start of the next line 
             OR pointer to terminating NUL character (if no next line found)
             OR s (if pointer not valid)
*/
const char* NStringFunctions::GetStartOfNextLine ( const char *s )
{
    const char *ptr = s;

    if (s) {
        while (*ptr != '\0' && *ptr != '\n')
            ptr++;

        if (*ptr == '\n')
            ptr++;
    }

    return ptr;
}

/* IsLineSeparationCharacter - test on line separation characters
  
   INPUT   :  c - character to be tested
   RETURNS :  TRUE is character is a line-separation character
*/
bool NStringFunctions::IsLineSeparationCharacter ( char c ) 
{
    return (c == '\r' || c == '\n');
}

/* ExtractLine - extract a line from a buffer

   The line is terminated by a line-separation character (CR, LF) or NUL.
   Line-sepearation characters are not copied.

   IN     : source  - pointer to source buffer
            size    - size of target buffer
   OUT    : target  - pointer to target buffer

   RETURNS: pointer to NUL-terminated target buffer

*/
const char* NStringFunctions::ExtractLine(const char* source, char* target, int size)
{
    int i;

    if (source && target) {
        for (i = 0; 
             i < (size-1) && source[i] != '\0' && !IsLineSeparationCharacter(source[i]);
             i++) {
            target[i] = source[i];
        }
        target[i] = '\0'; // Add a NUL character
    }

    return target;
}

/* LowercaseString  -  Convert all characters in a (w)string to lower case

   Input    : takes const reference to (w)string
   Returns  : (w)string converted to lower case
*/
string NStringFunctions::LowercaseString(const string& str) 
{
    string newstr(str);

    for (size_t index = 0; index < str.length(); index++) {
        if (isupper(str[index])) {
                    newstr[index] = tolower(str[index]);
        }
    }
    return newstr;
}

wstring NStringFunctions::LowercaseString(const wstring& str) 
{
    wstring newstr(str);

    for (size_t index = 0; index < str.length(); index++) {
        if (iswupper(str[index])) {
                    newstr[index] = towlower(str[index]);
        }
    }
    return newstr;
}

/* CompareNoCase  -  Performs case-insensitive string compare 

   Input    : str1 const reference to (w)string
              str2 const reference to (w)string
   Returns  : 0 if identical, <0 if (str1 < str2), >0 if (str1 > str2).
*/
int NStringFunctions::CompareNoCase(const string& str1, const string& str2) 
{
    return (_stricmp(str1.c_str(), str2.c_str()));
}

int NStringFunctions::CompareNoCase(const wstring& str1, const wstring& str2) 
{
    return (_wcsicmp(str1.c_str(), str2.c_str()));
}

int NStringFunctions::CompareNoCase(const string& str, const char *pchar) 
{
    return (_stricmp(str.c_str(), pchar));
}

int NStringFunctions::CompareNoCase(const char *pchar, const string& str)
{
    return (_stricmp(pchar, str.c_str()));
}

int NStringFunctions::CompareNoCase(const wstring& str, const wchar_t *pchar) 
{
    return (_wcsicmp(str.c_str(), pchar));
}

int NStringFunctions::CompareNoCase(const wchar_t *pchar, const wstring& str)
{
    return (_wcsicmp(pchar, str.c_str()));
}

/*  StartTagLength - Returns the tag length when a string is
                     converted to a XML start tag.
*/
int NStringFunctions::StartTagLength(const char *pString)
{
    return strlen(pString) + strlen("<>");
}
/*  EndTagLength - Returns the tag length when a string is
                   converted to a XML end tag.
*/
int NStringFunctions::EndTagLength(const char *pString)
{
    return strlen(pString) + strlen("</>");
}
/*  TagPairLength - Returns the length when a string is
                    used as a XML start/end tag pair.
*/
int NStringFunctions::TagPairLength(const char *pString)
{
    return StartTagLength(pString) + EndTagLength(pString);
}

/* WriteNumberToBuffer - Write a number as a string to a buffer

   In     : Number   - number to convert
            nDigits  - Minimum number of digits, if < 0 the digits
   In/Out : pBuffer  - Buffer to write (caller is responsable for allocating
                       sufficient memory.

   Returns: pointer to the first free byte after the number.
*/
char* NStringFunctions::WriteNumberToBuffer(char* pBuffer, int Number, int nDigits)
{
    char *ptr = pBuffer;
    int CharsWritten = 0;

    if (nDigits > 0) 
        CharsWritten = sprintf(ptr, "%0*d", nDigits, Number);
    else
        CharsWritten = sprintf(ptr, "%d", Number);

    ptr += CharsWritten;
    return ptr;
}

/* WriteStringToBuffer - Write a string to a buffer

   In     : pString  - NUL-terminated char array
   In/Out : pBuffer  - Buffer to write (caller is responsable for allocating
                       sufficient memory.

   Returns: pointer to the first free byte after the string.
*/
char* NStringFunctions::WriteStringToBuffer(char* pBuffer, const char* pString)
{
    char *ptr = pBuffer;
    int length = strlen(pString);

    memmove(ptr, pString, length);
    ptr += length;
    return ptr;
}

/* ExtractTaggedString - Extract a String contained within tags
                         <StartTag>string<EndTag>

   The tags can be located anywhere in the buffer. The StartTag
   should precede the EndTag.

   Input  : pBuffer      - pointer to NUL-terminated character array
            strStartTag  - Start Tag
            strEndTag    - End Tag

   Returns: extracted string
*/
string NStringFunctions::ExtractTaggedString(
   const char* pBuffer, const string& strStartTag, const string& strEndTag)
{
    const char* pStart;
    const char* pEnd;
    string strResult;

    pStart = strstr(pBuffer, strStartTag.c_str());
    if (pStart) {
        pEnd = strstr(pStart, strEndTag.c_str());
        if (pEnd) {
            pStart += strStartTag.length();
            for (const char* ptr = pStart; ptr < pEnd; ptr++) {
                strResult += *ptr;
            } //for
        }
    }

    return strResult;
}

/* ExtractTaggedNumber - Extract a Number contained within tags
                         <StartTag>number<EndTag>

   Input  : pBuffer      - pointer to buffer
            strStartTag  - Start Tag
            strEndTag    - End Tag

   Returns: extracted number or 0 if number invalid
*/
int NStringFunctions::ExtractTaggedNumber(
   const char* pBuffer, const string& strStartTag, const string& strEndTag)
{
    string strResult;
    strResult = ExtractTaggedString(pBuffer, strStartTag, strEndTag);
    if (!strResult.empty())
        return atoi(strResult.c_str());
    else 
        return 0;
}

/* CopyBuffer - Copy a buffer to another buffer

   In : pSourceBuffer    = pointer to source buffer
        SourceBufferSize = size of source buffer
        ExtendBy         = how many bytes target buffer will be greater than source buffer
                           (negative value allowed)
        FillChar         = fill character for target buffer

   Returns : pointer to a new buffer or NULL if error. 
             *** Delete the buffer with "delete" ***
             The original buffer is not deleted.
*/
void* NStringFunctions::CopyBuffer(void* pSourceBuffer, int SourceBufferSize, int ExtendBy, char FillChar)
{
    if (pSourceBuffer == NULL) return NULL;
    if (SourceBufferSize <= 0) return NULL;

    int TargetBufferSize = SourceBufferSize + ExtendBy;
    char* pTargetBuffer = new char[TargetBufferSize];
    if (TargetBufferSize > SourceBufferSize) {
        memset(pTargetBuffer, FillChar, TargetBufferSize);
    }
    memmove(pTargetBuffer, pSourceBuffer, __min(SourceBufferSize, TargetBufferSize));
    return (void*)pTargetBuffer;
}

/* ReadStringFromBuffer - Read a string from a buffer.
   
   Reading stops when
   1. The specified maximum number of characters have been read.
   2. Whitespace is detected (space, tab or newline).
   3. a NUL is detected

   Input  :  pBuffer - pointer to NUL-terminated character array.
             Length  - maximum characters to read. When < 0, 
                       reading stops on the detection of the first 
                       whitespace or NUL character.

   Returns:  a string with the characters read 
*/
string  NStringFunctions::ReadStringFromBuffer(const char* pBuffer, int Length)
{
    const int MAX_LENGTH = 132;
    string strResult;
    char   szString[MAX_LENGTH + 1] = {0};
    char   szFormat[12];

    if (pBuffer == NULL) 
        return strResult;

    if (Length < 0)
        Length = MAX_LENGTH;

    sprintf(szFormat, "%c%d%c", '%', Length, 's');
    sscanf(pBuffer, szFormat, szString);
    strResult = szString;

    return strResult;
}


