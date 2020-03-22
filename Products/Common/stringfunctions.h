/* StringFunctions.h - global routines for string and buffer handling
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

    This file contains overloaded versions for 
    - NUL-terminated ANSI character arrays (C-Style)
    - NUL-terminated UNICODE/wide character arrays
    - STL strings (ANSI strings)
    - STL wstrings (UNICODE/wide character strings)

    Note: the implementation is not complete.

History:
    [00]    HB  20Mar00 Originally developed by ES

*/

#ifndef STRINGFUNCTIONS
#define STRINGFUNCTIONS

#include <string>

namespace NStringFunctions
{
    // Case Conversion 
    char       * UpcaseString(char *s);
    wchar_t    * UpcaseString(wchar_t *s);
    std::string  UpcaseString(const std::string& str);
    std::wstring UpcaseString(const std::wstring& str);

    std::string  LowercaseString(const std::string& str);
    std::wstring LowercaseString(const std::wstring& str);

    // String Conversion
    char       * RemoveChars(char *s, const char c);
    wchar_t    * RemoveChars ( wchar_t * s , const wchar_t c );
    void         CompressString( TCHAR *s );
    void         TrimString(TCHAR *s);
    TCHAR      * ReplaceChars(TCHAR *s , TCHAR old_char , TCHAR new_char) ;
    void         ReplaceStrings(TCHAR *s , TCHAR *substring, TCHAR *newstring, TCHAR *resultstring, int size);

    // String Counting
    int          CharCount ( const TCHAR *s , TCHAR c ) ;
    int          StringCount ( const TCHAR *s , const TCHAR *substring ) ;
    
    // Delimited Strings
    int          GetWord (const char *s, int wordnr, char separator, char *word, int max_word_size );
    int          GetWord (const wchar_t *s, int wordnr, wchar_t separator, wchar_t *word, int max_word_size );

    std::string  GetWord (const char *s, int wordnr, char separator);
    std::wstring GetWord (const wchar_t *s, int wordnr, wchar_t separator);
    std::string  GetWord (const std::string& s, int wordnr, char separator);
    std::wstring GetWord (const std::wstring& s , int wordnr, wchar_t separator);

    // String Validation 
    int          TestFormat(const char* s, const char* format, int count = -1);
    int          TestFormat(const wchar_t* s, const wchar_t* format, int count = -1);
    int          TestFormat2(const char* s, const char* format, int count = -1, bool match_case = false);
    int          TestFormat2(const wchar_t* s, const wchar_t* format, int count = -1, bool match_case = false);
    
    // String Compare
    int          CompareNoCase(const std::string& str1, const std::string& str2);
    int          CompareNoCase(const std::wstring& str1, const std::wstring& str2);
    int          CompareNoCase(const std::string& str, const char *pchar); 
    int          CompareNoCase(const char *pchar, const std::string& str);
    int          CompareNoCase(const std::wstring& str, const wchar_t *pchar); 
    int          CompareNoCase(const wchar_t *pchar, const std::wstring& str);

    // Buffers - General
    void*        CopyBuffer(void* pSourceBuffer, int SourceBufferSize, int ExtendBy = 1, char FillChar = '\0');
    char*        WriteNumberToBuffer(char* pBuffer, int Number, int nDigits = -1);
    char*        WriteStringToBuffer(char* pBuffer,  const char* pString);
    std::string  ReadStringFromBuffer(const char* pBuffer, int Length = -1);

    // Buffers with Lines
    const char*  GetStartOfNextLine (const char *s);
    bool         IsLineSeparationCharacter (char c);
    const char*  ExtractLine(const char* source, char* target, int size);
    
    // Tagged strings
    int          StartTagLength(const char *pString);
    int          EndTagLength(const char *pString);
    int          TagPairLength(const char *pString);
    
    // Buffers with tagged strings
    std::string  ExtractTaggedString(const char* pBuffer, const std::string& strStartTag, const std::string& strEndTag);
    int          ExtractTaggedNumber(const char* pBuffer, const std::string& strStartTag, const std::string& strEndTag);
    
    // Single-String Pattern Matching
    bool         MatchWildcard(const char *wildcard, const char *test);
    bool         MatchWildcard(const std::string &wildcard, const std::string &test);
    bool         MatchWildcard(const wchar_t *wildcard, const wchar_t *test);
    bool         MatchWildcard(const std::wstring &wildcard, const std::wstring &test);
    bool         IsValidFilter(const std::basic_string<TCHAR>& filter, const std::basic_string<TCHAR>& sample);
} ;

#endif // STRINGFUNCTIONS
