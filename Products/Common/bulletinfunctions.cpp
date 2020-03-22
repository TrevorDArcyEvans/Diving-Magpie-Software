/* BulletinFunctions.cpp - global functions for bulletins in character arrays
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

  Note: This file contains hard-coded FM codes. Symbolic names for FM codes are 
        defined in MeteoDataTypes.idl. 
        Since we want to avoid a dependency on this file, the FM codes are
        hard-coded.

$History: BulletinFunctions.cpp $
 * 
 * *****************  Version 18  *****************
 * User: Hans         Date: 13-09-00   Time: 14:43
 * Updated in $/Common/Projects/MeteoObjects
 * processing of report time and validity period changed
 * 
 * *****************  Version 17  *****************
 * User: Hans         Date: 5-09-01    Time: 17:29
 * Updated in $/Common/Projects/MeteoObjects
 * with method SetMessageBodyFromFile
 * 
 * *****************  Version 16  *****************
 * User: Hans         Date: 29-08-00   Time: 14:44
 * Updated in $/Common/Projects/MeteoObjects
 * with wide-char version of IsSigmet
 * 
 * *****************  Version 15  *****************
 * User: Hans         Date: 25-07-00   Time: 7:07
 * Updated in $/Common/Projects/MeteoObjects
 * with UNICODE versions of IsWmoBinary() etc.
 * 
 * *****************  Version 14  *****************
 * User: Hans         Date: 21-07-00   Time: 4:36
 * Updated in $/METCOM/Projects/BulletinFilterServer
 * with GetFmCode() to convert report type string back to FM code
 * 
 * *****************  Version 13  *****************
 * User: Hans         Date: 21-07-00   Time: 4:24
 * Updated in $/METCOM/Projects/BulletinFilterServer
 * with IsNilReport

*/

#include "stdafx.h"
#include "StringFunctions.h"
#include "BulletinFunctions.h"
#include <ctype.h>
#include <vector>
#include <algorithm>

#pragma warning (disable:4786)

using namespace std;
using namespace NStringFunctions;

/* IsWmoHeader - Test if a line can be identified as a WMO header

   NOTE: the header is IDENTIFIED, not VALIDATED!

   IN      : pLine - pointer to line to be tested, ends with NUL, CR or LF.
 
   RETURNS : TRUE if WMO header line
*/
bool NBulletinFunctions::IsWmoHeader(const char* pLine)
{
    const int MAXLENGTH = 10;

    char szHeader[MAXLENGTH + 1]; // buffer with start of WMO header
    const char *ptr = pLine;
    bool        bHeaderFound = false;
    int         i = 0;
    int         j = 0;

    memset(szHeader, 0, MAXLENGTH + 1);

    // Copy line to NUL-terminated buffer
    for (i = 0, j = 0; 
         i < MAXLENGTH && pLine[i] && pLine[i] != '\r' && pLine[i] != '\n';
         i++) {
         szHeader[j++] = pLine[i];
    } //for
    szHeader[j] = '\0'; // Add NUL character

    // Search for SMBX01 or SMBX1
    if (   TestFormat(szHeader, "AAAA99S", 7) 
        || TestFormat(szHeader, "AAAA9S", 6)) {
        bHeaderFound = true;
    } //if

    return bHeaderFound;
}

/* IsRbiLine - Test if a line is a RBI (Redundant Bulletin Information)

   For some WMO bulletins, the line following the abbreviated header line
   contains a code name or common information that can be applied to all 
   reports in the bulletin. The typical description in WMO manual 306 is:

   "The code name XXX shall be included at the beginning of an individual
    report; in case of a meteorological bulletin, which may consist of one
    or more than one report, the code name XXX shall be included at the 
    beginning of the text of the bulletin."

    This functions tests the format of the known RBI lines described in
    WMO manual 306.

    IN      : pLine - pointer to line to be tested, ends with NUL, CR or LF.
 
    RETURNS : TRUE if valid RBI line
*/
bool NBulletinFunctions::IsRbiLine(const char *pLine)
{
    const int MAXRBI = 64;

    char szRbiBuffer[MAXRBI + 1]; // buffer with RBI line and spaces removed
    const char *ptr = pLine;
    bool        bRbiFound = false;
    int         i = 0;
    int         j = 0;

    memset(szRbiBuffer, 0, MAXRBI + 1);

    // Copy RBI line without spaces to NUL-terminated buffer
    for (i = 0, j = 0; 
         i < MAXRBI && pLine[i] && pLine[i] != '\r' && pLine[i] != '\n';
         i++) {
        if (!isspace(pLine[i])) {
            szRbiBuffer[j++] = pLine[i];
        } //if
    } //for
    szRbiBuffer[j] = '\0'; // Add NUL character

    // Perform case-insensitive compares
    if (_strnicmp(szRbiBuffer, "AAXX", 4) == 0) {
        if (TestFormat(&szRbiBuffer[4], "99999\0", 6)) {
            // SYNOP with timestamp and windindicator
            bRbiFound = true;
        }
    } else if (_stricmp(szRbiBuffer, "METAR") == 0) {
        // METAR without timestamp
        bRbiFound = 1;
    } else if (_strnicmp(szRbiBuffer, "METAR", 5) == 0) {
        if (TestFormat(&szRbiBuffer[5], "9999A\0", 6)) { 
            // METAR with timestamp
            bRbiFound = true;
        }
    } else if (_stricmp(szRbiBuffer, "TAF") == 0) {
        // TAF
        bRbiFound = true;
    } else if (_stricmp(szRbiBuffer, "TAFAMD") == 0) {
        // TAF AMD
        bRbiFound = true;
    } else if (_stricmp(szRbiBuffer, "SPECI") == 0) {
        // SPECI
        bRbiFound = true;
    } else if (_stricmp(szRbiBuffer, "BBXX") == 0) {
        // SYNOP SHIP
        bRbiFound = true;
    }  else if (_stricmp(szRbiBuffer, "OOXX") == 0) {
        // SYNOP MOBIL
        bRbiFound = true;
    } else if (_stricmp(szRbiBuffer, "LLXX") == 0) {
        // CODAR
        bRbiFound = true;
    } else if (_stricmp(szRbiBuffer, "MAFOR") == 0) {
        // MAFOR
        bRbiFound = true;
    } else if (_strnicmp(szRbiBuffer, "AMDAR", 5) == 0) {
        if (TestFormat(&szRbiBuffer[5], "9999\0", 5)) {
            // AMDAR with timestamp
            bRbiFound = true;
        }
    } else if (_strnicmp(szRbiBuffer, "HHXX", 4) == 0) {
        if (TestFormat(&szRbiBuffer[4], "9999\0", 5)) {
            // HYDRA with timestamp
            bRbiFound = true;
        }
    } else if (_strnicmp(szRbiBuffer, "HHXX", 4) == 0) {
        if (TestFormat(&szRbiBuffer[4], "9999BBBBB\0", 10)) {
            // HYDRA with timestamp and country indicator
            bRbiFound = true;
        }
    } else if (_stricmp(szRbiBuffer, "HYFOR") == 0) {
            // HYFOR without country indicator
            bRbiFound = true;
    } else if (_strnicmp(szRbiBuffer, "HYFOR", 5) == 0) {
        if (szRbiBuffer[11] == '\0') {
            // HYFOR with country indicator
            bRbiFound = true;
        }
    }

    /* TODO
    CLIMAT // climat or climat ship
    NACLI
    CLINP
    SPCLI
    CLISA
    INCLI
    CLIMAT TEMP
    CLIMAT TEMP SHIP
    SFAZI
    SFLOC
    SFAZU
    */

    return bRbiFound;
}

/* IsGroupSeparationCharacter - Returns TRUE when a character is
                                a group separation character
*/
bool NBulletinFunctions::IsGroupSeparationCharacter ( char c ) 
{
    return isspace(c) ? true : false;
}

bool NBulletinFunctions::IsGroupSeparationCharacter ( wchar_t c ) 
{
    return iswspace(c) ? true : false;
}

bool NBulletinFunctions::IsReportTerminationCharacter ( char c ) 
{
    return (c == '=') ? true : false;
}

bool NBulletinFunctions::IsReportTerminationCharacter ( wchar_t c ) 
{
    return (c == L'=') ? true : false;
}

/* GetStartOfNextGroup - Move a character pointer to the start of the next 
                         group in a character buffer with groups delimited
                         by whitespace.

   Note   : This function calls IsGroupSeparationCharacter to determine
            the start of a new group. 
   Input  : pGroupPointer : pointer to a NUL-terminated character array.
   Returns: Pointer to the next group or pointer to the NUL when the
            next group was not found or pointer to the report terminator 
*/
const char* NBulletinFunctions::GetStartOfNextGroup ( const char *pGroupPointer )
{
   const char *ptr = pGroupPointer;

   if (pGroupPointer) {

       // step over non separation characters
       while ( ( *ptr != '\0' ) && ( ! IsGroupSeparationCharacter ( *ptr ) ) )  { 
          ptr++ ;
       }

       // step over separation characters
       while ( IsGroupSeparationCharacter ( *ptr ) ) {         
          ptr++ ;
       }
   }
   return ptr ;
}

const wchar_t* NBulletinFunctions::GetStartOfNextGroup ( const wchar_t *pGroupPointer )
{
    const wchar_t *ptr = pGroupPointer;

    if (pGroupPointer) {

        // step over non separation characters
        while ( ( *ptr != L'\0' ) && ( ! IsGroupSeparationCharacter ( *ptr ) ) )  {  
            ptr++ ;
        }

        // step over separation characters
        while ( IsGroupSeparationCharacter ( *ptr ) ) {
            ptr++ ;
        }
    }

    return ptr ;
}

/* GetStartOfPreviousGroup - Move pointer to start of previous group

   Input  : pGroupPointer - pointer to current group in report
                            (NUL-terminated character array)
          : pStartPointer - pointer to start of report
                            (NUL-terminated character array)
                        
   Returns: pointer to start of previous group or pointer to start of report
            or NULL pointer if error
*/
const char* NBulletinFunctions::GetStartOfPreviousGroup( const char *pGroupPointer, const char *pStartPointer )
{
   const char *ptr = pGroupPointer;

   if (pGroupPointer) {

       // Move to the last whitespace character before the current group
       while (ptr > pStartPointer && !IsGroupSeparationCharacter(*ptr)) 
           ptr--;

       // Move to the end of previous group
       while (ptr > pStartPointer && IsGroupSeparationCharacter(*ptr)) 
           ptr--;

       // Move to the last whitespace character before the previous group
       while (ptr > pStartPointer && !IsGroupSeparationCharacter(*ptr)) 
           ptr--;

       // Move to the first character of the previous group
       if (ptr > pStartPointer && *ptr != '\0') 
           ptr++;
   }

   return ptr ;
}

/* DetermineGroupLength 

   The groups in a breakdown report are separated by separation characters. This function 
   determines the length of the group at which the group_pointer is pointing starting 
   from the pointed position.
   
   IN     : group_pointer : pointer to the start of a group in a report. 
            The report must be a nul-terminating character-array (c-string)
   RETURN : length of the group (0 if group pointer does not point to a group)
*/
int NBulletinFunctions::DetermineGroupLength ( const char* group_pointer )
{
   int n = 0 ;

   while (    ( group_pointer[n] != '\0' ) 
           && ( ! IsGroupSeparationCharacter ( group_pointer[n] ) ) 
           && ( ! IsReportTerminationCharacter ( group_pointer[n] ) ) ) {

      n++ ;
   }

   return n ;
}

int NBulletinFunctions::DetermineGroupLength ( const wchar_t* group_pointer )
{
   int n = 0 ;

   while (    ( group_pointer[n] != L'\0' ) 
           && ( ! IsGroupSeparationCharacter ( group_pointer[n] ) ) 
           && ( ! IsReportTerminationCharacter ( group_pointer[n] ) ) ) {

      n++ ;
   }

   return n ;
}

/* GetFmCode - Determine the FM code of a bulletin

   NOTE   : this function only supports the most common FM codes

   IN     : TT  - the TT code (NUL-terminated character array)
            RBI - the RBI line or the start of a report with the same groups
                  (NUL-terminated character array)
 
   RETURNS: the FM code or 0 if not recognized
*/ 
int NBulletinFunctions::GetFmCode(const char *TT, const char *RBI)
{
    int FM = 0;

    if (_strnicmp(TT, "SA", 2) == 0)
        FM = 15; //METAR
    else if (_strnicmp(TT, "SP", 2) == 0)
        FM = 16; //SPECI
    else if (_strnicmp(TT, "SN", 2) == 0 && _strnicmp(RBI, "AAXX", 4) == 0)
        FM = 12; //SYNOP
    else if (_strnicmp(TT, "SM", 2) == 0 && _strnicmp(RBI, "AAXX", 4) == 0)
        FM = 12;
    else if (_strnicmp(TT, "SI", 2) == 0 && _strnicmp(RBI, "AAXX", 4) == 0)
        FM = 12;
    else if (_strnicmp(TT, "SN", 2) == 0 && _strnicmp(RBI, "BBXX", 4) == 0)
        FM = 13; //SHIP
    else if (_strnicmp(TT, "SM", 2) == 0 && _strnicmp(RBI, "BBXX", 4) == 0)
        FM = 13;
    else if (_strnicmp(TT, "SI", 2) == 0 && _strnicmp(RBI, "BBXX", 4) == 0)
        FM = 13;
    else if (_strnicmp(TT, "SN", 2) == 0 && _strnicmp(RBI, "OOXX", 4) == 0)
        FM = 14; //SYNOP MOBIL
    else if (_strnicmp(TT, "SM", 2) == 0 && _strnicmp(RBI, "OOXX", 4) == 0)
        FM = 14;
    else if (_strnicmp(TT, "SI", 2) == 0 && _strnicmp(RBI, "OOXX", 4) == 0)
        FM = 14; 
    else if (_strnicmp(TT, "FC", 2) == 0)
        FM = 51; //TAF
    else if (_strnicmp(TT, "FT", 2) == 0)
        FM = 51; //TAF
    else if (_strnicmp(TT, "SS", 2) == 0)
        FM = 18; //BUOY
 
    else if (_strnicmp(TT, "UE", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35; //TEMP
    else if (_strnicmp(TT, "UF", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35;
    else if (_strnicmp(TT, "UK", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35;
    else if (_strnicmp(TT, "UL", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35;
    else if (_strnicmp(TT, "UM", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35;
    else if (_strnicmp(TT, "US", 2) == 0 && _strnicmp(RBI, "TT", 2) == 0)
        FM = 35;

    else if (_strnicmp(TT, "UE", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36; //TEMP SHIP
    else if (_strnicmp(TT, "UF", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36;
    else if (_strnicmp(TT, "UK", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36;
    else if (_strnicmp(TT, "UL", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36;
    else if (_strnicmp(TT, "UM", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36;
    else if (_strnicmp(TT, "US", 2) == 0 && _strnicmp(RBI, "UU", 2) == 0)
        FM = 36;

    else if (_strnicmp(TT, "UE", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38; //TEMP MOBIL
    else if (_strnicmp(TT, "UF", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38;
    else if (_strnicmp(TT, "UK", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38;
    else if (_strnicmp(TT, "UL", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38;
    else if (_strnicmp(TT, "UM", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38;
    else if (_strnicmp(TT, "US", 2) == 0 && _strnicmp(RBI, "II", 2) == 0)
        FM = 38;

    else if (_strnicmp(TT, "WC", 2) == 0)
        FM = 32764; //SIGMET
    else if (_strnicmp(TT, "WS", 2) == 0)
        FM = 32764;
    else if (_strnicmp(TT, "WV", 2) == 0)
        FM = 32764;

    return FM;
}

/* ExtractReports - Extract reports, delimited by '=', and place reports in 
                    a vector.

   Note: Use HasWmoReports() to determine if a bulletin has reports delimited
         by '='.

   INPUT  :  pBuffer - pointer to NUL-terminated character array, should point to first report
   IN/OUT :  reports - string vector, receives reports
   RETURNS:  number of reports found
*/ 
int NBulletinFunctions::ExtractReports(const char* pBuffer, vector<string>& reports)
{
    const char *ptr = pBuffer;
    int         i = 0;

    if (pBuffer == NULL) return 0;

    try {
        string strReport;

        while (*ptr) {
            strReport = "";
            // Copy characters until terminator found
            while (*ptr && !IsReportTerminationCharacter(*ptr)) {
                strReport += *ptr;
                ptr++;
            } //while

            if (IsReportTerminationCharacter(*ptr)) {
                // Include terminator in report
                strReport += *ptr;
                ptr++;
                ptr = GetStartOfNextLine(ptr);  // Move to next report
                // [01] Test on NIL bulletin before counting
                if (strReport == "NIL=")        // Skip NIL bulletin
                    continue;
                i++; // count report
                reports.push_back(strReport);   // Store report in list
            }

        } //while
    } catch (...) {
    }

    return i;
}

/* GetEndOfReport  - Move the pointer to the end of the report

   Input  : ptr - pointer to NUL-terminated character array

   Returns: pointer to report terminator or pointer to NUL (if not found)
            or NULL pointer (if error)
*/
const char* NBulletinFunctions::GetEndOfReport(const char* ptr)
{
    if (ptr == NULL) return 0;

    while (*ptr && !IsReportTerminationCharacter(*ptr)) {
        ptr++;
    } //while

    return ptr;
}

/* GetStartOfSigmetReport - Move pointer to the start a SIGMET report

   Input  : start_ptr - pointer to the start of SIGMET report
                        (a NUL-terminated character array)
                        A SIGMET report starts with:
                        1. CCCC SIGMET
                        2. SIGMET

   Returns: pointer to the start of the next SIGMET report or pointer to NUL 
            (if not found) or NULL pointer (if error)
*/
const char* NBulletinFunctions::GetStartOfNextSigmetReport(const char* start_ptr)
{
    char ICAO_code[5] = {0};

    const char *group_pointer = start_ptr;

    if (group_pointer == NULL) return 0;

    while (group_pointer[0] != '\0') {

        // Search for SIGMET keyword (terminated by a space)
        if ( strncmp(group_pointer, "SIGMET ", 7) == 0 ) {
            // Move group pointer to previous group
            group_pointer = GetStartOfPreviousGroup(group_pointer, start_ptr);

            // Test for cancellation
            if ( strncmp(group_pointer, "CANC", 4) == 0 ) {
                // Did we pass a cancellation? skip; because it belongs to present report
                // 1. Move to SIGMET
                group_pointer = GetStartOfNextGroup(group_pointer) ;  
                // 2. Move to first group after SIGMET
                group_pointer = GetStartOfNextGroup(group_pointer) ;  
            } else {  
                // It is not a cancellation; a new SIGMET is found. 
                // Now find the exact start of the report.

                // Does the report start with an ICAO indicator? Take it with the report
                ICAO_code[0] = '\0';
                if (DetermineGroupLength(group_pointer) == 4) {
                    strncpy(ICAO_code, group_pointer, 4);
                    ICAO_code[4] = '\0';
                }

                if (IsIcaoCode(ICAO_code)) {
                    // Start of new Sigmet
                    return group_pointer;
                } else {
                    // Move to the SIGMET group
                    group_pointer = GetStartOfNextGroup(group_pointer) ;  
                    return group_pointer;
                }//if valid string "SIGMET" is found ; following report
            }
        } else {
            // string "SIGMET" not found
            group_pointer = GetStartOfNextGroup(group_pointer) ;  
        }
     }//while there are alphanumeric characters

    return group_pointer;
}

/* ValidTTAndTime - Validate a TT/GG combination
   
   Note   :  This function assumes TT and GG are valid. It just tests
             the combination of TT and GG. 

   INPUT  :  TT - pointer to NUL-terminated character array.
                  The TT code contains the first 2 characters in a WMO header.
             GG - pointer to NUL-terminated character array. 
                  GG is the hours field in a WMO header.
   RETURNS:  TRUE if valid
*/ 
bool NBulletinFunctions::ValidTTAndTime (const char *pTT, const char *pGG)
{
    int hour = atoi(pGG);

    // SM = Main hour
    // SI = Intermediate hour
    // SN = Other hour

    if (pTT == NULL || pGG == NULL) return false;

    if ( ( _strnicmp ( pTT, "SM", 2 ) == 0 && hour != 0  && hour != 6  && hour != 12 && hour != 18 ) ||
         ( _strnicmp ( pTT, "SI", 2 ) == 0 && hour != 3  && hour != 9  && hour != 15 && hour != 21 ) ||
         ( _strnicmp ( pTT, "SN", 2 ) == 0 && hour != 1  && hour != 2  && hour != 4  && hour != 5
                                           && hour != 7  && hour != 8  && hour != 10 && hour != 11
                                           && hour != 13 && hour != 14 && hour != 16 && hour != 17
                                           && hour != 19 && hour != 20 && hour != 22 && hour != 23 ) ) {
        return false; 
    } //if

    return true;
}

/* IsWmoFax - Returns TRUE when the message is a WMO fax
   
   Input : pBulletin - NUL-terminated character array
           When the bulletin is complete, this function will be
           able to perform the most valid check.
*/
bool NBulletinFunctions::IsWmoFax(const char* pBulletin)
{
    char T1;

    if (pBulletin) {
        T1 = toupper(pBulletin[0]);
        return (T1 == 'P' || T1 == 'Q');
    }

    return false;
}
bool NBulletinFunctions::IsWmoFax(const wchar_t* pBulletin)
{
    wchar_t T1;

    if (pBulletin) {
        T1 = towupper(pBulletin[0]);
        return (T1 == L'P' || T1 == L'Q');
    }

    return false;
}

/* IsWmoGrib - Returns TRUE when the message is a WMO GRIB

   Input : pBulletin - NUL-terminated character array
           When the bulletin is complete, this function will be
           able to perform the most valid check.

*/
bool NBulletinFunctions::IsWmoGrib(const char* pBulletin)
{
    char T1;
    char T2;

    // "HA" is an exception from the WMO rules
    if (pBulletin) {
        T1 = toupper(pBulletin[0]);
        T2 = toupper(pBulletin[1]);
        return ((T1 == 'H' && T2 != 'A') || T1 == 'Y' || T1 == 'O');
    }

    return false;
}
bool NBulletinFunctions::IsWmoGrib(const wchar_t* pBulletin)
{
    wchar_t T1;
    wchar_t T2;

    // "HA" is an exception from the WMO rules
    if (pBulletin) {
        T1 = towupper(pBulletin[0]);
        T2 = towupper(pBulletin[1]);
        return ((T1 == L'H' && T2 != L'A') || T1 == L'Y' || T1 == L'O');
    }

    return false;
}

/* IsWmoBufr - Returns TRUE when the message is a WMO BUFR

   Input : pBulletin - NUL-terminated character array
           When the bulletin is complete, this function will be
           able to perform the most valid check.
*/
bool NBulletinFunctions::IsWmoBufr(const char* pBulletin)
{
    char T1;

    if (pBulletin) {
        T1 = toupper(pBulletin[0]);
        return (T1 == 'I' || T1 == 'J');
    }

    return false;
}
bool NBulletinFunctions::IsWmoBufr(const wchar_t* pBulletin)
{
    wchar_t T1;

    if (pBulletin) {
        T1 = towupper(pBulletin[0]);
        return (T1 == L'I' || T1 == L'J');
    }

    return false;
}

/* IsWmoBinary - Returns TRUE when the message is a WMO binary bulletin

   Input : pBulletin - NUL-terminated character array
           When the bulletin is complete, this function will be
           able to perform the most valid check.

*/
bool NBulletinFunctions::IsWmoBinary(const char* pBulletin)
{
    return (IsWmoFax(pBulletin) || IsWmoGrib(pBulletin) || IsWmoBufr(pBulletin));
}
bool NBulletinFunctions::IsWmoBinary(const wchar_t* pBulletin)
{
    return (IsWmoFax(pBulletin) || IsWmoGrib(pBulletin) || IsWmoBufr(pBulletin));
}

/* IsSigmet - Returns TRUE when the message is a SIGMET

   Input : pBulletin - NUL-terminated character array
           When the bulletin is complete, this function will be
           able to perform the most valid check.
*/
bool NBulletinFunctions::IsSigmet(const char* pBulletin)
{
    char T1;
    char T2;

    if (pBulletin) {
        T1 = toupper(pBulletin[0]);
        if (T1 == 'W') {
            T2 = toupper(pBulletin[1]);
            if (T2 == 'C' || T2 == 'S' || T2 == 'V')
                return true;
        }
    }

    return false;
}

bool NBulletinFunctions::IsSigmet(const wchar_t *pBulletin)
{
    wchar_t T1;
    wchar_t T2;

    if (pBulletin) {
        T1 = towupper(pBulletin[0]);
        if (T1 == L'W') {
            T2 = towupper(pBulletin[1]);
            if (T2 == L'C' || T2 == L'S' || T2 == L'V')
                return true;
        }
    }

    return false;
}

/* IsProtocolStartEnvelopeCharacter - Returns TRUE when the character is a
                                      protocol start envelope character
   
   Note: this function does not take into account ZCZC or the channel
   identifier in AFTN messages.
*/
bool NBulletinFunctions::IsProtocolStartEnvelopeCharacter(char c)
{
    // Test on SOH, space, CR, LF and digits (from CSN)
    return (c == 0x01 || c == '\r' || c == '\n' || c == ' ' || isdigit(c));
}


/* IsProtocolEndEnvelopeCharacter - Returns TRUE when the character is a
                                    protocol end envelope character
   
   Note: this function does not take into account NNNN or the channel
   identifier in AFTN messages.
*/
bool NBulletinFunctions::IsProtocolEndEnvelopeCharacter(char c)
{
    // Test on ETX
    return (c == 0x03);
}

/* GetBodyInProtocolEnvelope - Get pointers to the start and the end
                               of the body in a bulletin with a 
                               protocol envelope.

   Input  : pBulletin     - pointer to NUL-terminated character array
            BulletinSize  - size of array (including NUL)
                            Note: the BulletinSize shall be specified
                            to support bulletins with binary data.
                            A NUL-terminated array is required to support
                            text-based helper functions.
   Out    : ppStart       - address of pointer, receives a pointer to 
                            the start of the body (if found).
            ppEnd         - address of pointer, receives a pointer to 
                            one after end of the body. In case of
                            success, it will always point to a valid 
                            character. This can be the NUL or another character.
   Returns: The length of the body (or 0 is not found).
*/
int NBulletinFunctions::GetBodyInProtocolEnvelope(
    const char* pBulletin, int BulletinSize, const char **ppStart, const char **ppEnd)
{
    bool fZCZCfound = false;

    if (pBulletin == NULL || BulletinSize == 0 || ppStart == NULL || ppEnd == NULL)
        return 0;

    *ppStart = pBulletin;
    *ppEnd = &pBulletin[BulletinSize - 1];

    if (**ppEnd != '\0') return 0; // Incorrect argument

    // Eat protocol at the start
    while (*ppStart < *ppEnd && IsProtocolStartEnvelopeCharacter(**ppStart)) 
        (*ppStart)++;

    // Test for ZCZC
    if (*ppEnd - *ppStart > 4) {
        if (_strnicmp(*ppStart, "zczc", 4) == 0) {
            (*ppStart) += 4;

            fZCZCfound = true;

            // If ZCZC found, skip CSN etc after ZCZC
            while (*ppStart < *ppEnd && IsProtocolStartEnvelopeCharacter(**ppStart)) 
                (*ppStart)++;
        }
    }

    // Test for "ABC123" in AFTN message header
    if (*ppEnd - *ppStart > 6) {
        if (TestFormat(*ppStart, "AAA999", 6)) {
            (*ppStart) += 6;
            // If ZCZC found, skip CSN etc after ZCZC
            while (*ppStart < *ppEnd && IsProtocolStartEnvelopeCharacter(**ppStart)) 
                (*ppStart)++;
        }
    }

    // Eat protocol at the end
    if (*ppEnd > *ppStart)
        (*ppEnd)--; // Go before NUL

    // Skip trailing CR and LF 
    while(*ppEnd > *ppStart && (**ppEnd == '\r' || **ppEnd == '\n'))
        (*ppEnd)--;

    if (fZCZCfound) {
        // Skip NNNN
        while (*ppEnd > *ppStart && toupper(**ppEnd) == 'N')
            (*ppEnd)--;
    } else {
        // Skip ETX 
        while (*ppEnd > *ppStart && IsProtocolEndEnvelopeCharacter(**ppEnd)) 
            (*ppEnd)--;
    }

    // We do not remove CR and LF before NNNN or ETX because these
    // might belong to the message content (e.g. a message with
    // empty lines at the end).

    // Move pointer to one after the end of the body (STL style)
    if (**ppEnd != '\0' && *ppEnd > *ppStart) 
        (*ppEnd)++;

    return *ppEnd - *ppStart;
}

/* GetWmoBody - Get the WMO body in a bulletin

   Input  : pBulletin     - pointer to NUL-terminated character array
            BulletinSize  - size of array (NUL included)
                            Note: the BulletinSize shall be specified
                            to support bulletins with binary data.
                            A NUL-terminated array is required to support
                            text-based helper functions.
   Out    : pStart        - address of pointer, receives a pointer to 
                            the start of the WMO header (if found)
            pEnd          - address of pointer, receives a pointer to 
                            the one after the end of the WMO bulletin. 
                            Note: The bulletin should not contain more than
                            1 bulletin.
   Returns: The length of the WMO bulletin (or 0 is not found).
*/
int NBulletinFunctions::GetWmoBody( 
    const char* pBulletin, int BulletinSize, const char **ppStart, const char **ppEnd)    
{
    const int MAX_SEARCH_LINES = 10;

    const char *ptr = pBulletin;
    bool        bHeaderFound = false;
    const char *pBodyStart = NULL;
    const char *pBodyEnd = NULL;
    int         BodyLength;
 
    if (pBulletin == NULL || BulletinSize == 0 || ppStart == NULL || ppEnd == NULL)
        return 0;

    *ppStart = pBulletin;
    *ppEnd = &pBulletin[BulletinSize - 1];

    if (**ppEnd != '\0') return 0; // Incorrect argument

    BodyLength = GetBodyInProtocolEnvelope(pBulletin, BulletinSize, &pBodyStart, &pBodyEnd);
    if (BodyLength > 0) {

        ptr = pBodyStart;
        for (int i = 0; ptr < pBodyEnd && i < MAX_SEARCH_LINES && !bHeaderFound; i++) {

            bHeaderFound = false;

            // Search for SMBX01 or SMBX1
            if (IsWmoHeader(ptr)) {
                bHeaderFound = true;
            } //if

            if (!bHeaderFound) {
               // Goto next line
                ptr = GetStartOfNextLine(ptr);
            } //if
        } //for       
    }

    if (bHeaderFound) {
        *ppStart = ptr;
        *ppEnd = pBodyEnd;
        return *ppEnd - *ppStart;
    } else {
        return 0;
    }
}


/* IsIcaoCode - Returns TRUE if a station code has a valid ICAO code format

   This function does NOT compare the code with a list with known codes.
   It checks just the format.

   In : pIcao - pointer to NUL-terminated character array
*/
bool NBulletinFunctions::IsIcaoCode(const char *pIcao)
{
    return (pIcao && strlen(pIcao) == 4 && TestFormat(pIcao, "AAAA"));
}

bool NBulletinFunctions::IsIcaoCode(const wchar_t *pIcao)
{
    return (pIcao && wcslen(pIcao) == 4 && TestFormat(pIcao, L"AAAA"));
}

/* IsWmoCode - Returns TRUE if a station code has a valid WMO code format

   This function does NOT compare the code with a list with known codes.
   It checks just the format.

   In : pWmo - pointer to NUL-terminated character array
*/
bool NBulletinFunctions::IsWmoCode(const char *pWmo)
{
    return (pWmo && strlen(pWmo) == 5 && TestFormat(pWmo, "99999"));
}

bool NBulletinFunctions::IsWmoCode(const wchar_t *pWmo)
{
   return (pWmo && wcslen(pWmo) == 5 && TestFormat(pWmo, L"99999"));
}

/* IsWmoTime - Returns TRUE if the time is a WMO time

   This function does not compare or expand the time to system time.
   It just checks the string "as is".

   In : pWmoTime - pointer to NUL-terminated character array
*/
bool NBulletinFunctions::IsWmoTime(const char *pWmoTime)
{
    char YY[3] = {0};
    char GG[3] = {0};
    char gg[3] = {0};

    // Check on all digits before performing an atoi.
    // (atoi returns a valid number even if the input is invalid).

    if (pWmoTime && strlen(pWmoTime) == 6 && TestFormat(pWmoTime, "999999")) {
        strncpy(YY, &pWmoTime[0], 2);
        strncpy(GG, &pWmoTime[2], 2);
        strncpy(gg, &pWmoTime[4], 2);
        if (atoi(YY) > 31) return false;
        if (atoi(GG) > 23) return false;
        if (atoi(gg) > 59) return false;
        return true;
    }

    return false;
}

/* IsGGgg - Returns TRUE if the time is a valid UTC time (hours + minutes)

   This function does not compare or expand the time to system time.
   It just checks the string "as is".

   In : pGGgg - pointer to NUL-terminated character array
*/
bool NBulletinFunctions::IsGGgg(const char *pGGgg)
{
    char GG[3] = {0};
    char gg[3] = {0};

    // Check on all digits before performing an atoi.
    // (atoi returns a valid number even if the input is invalid).

    if (pGGgg && strlen(pGGgg) == 4 && TestFormat(pGGgg, "9999")) {
        strncpy(GG, &pGGgg[0], 2);
        strncpy(gg, &pGGgg[2], 2);
        if (atoi(GG) > 23) return false; //NOTREACHED
        if (atoi(gg) > 59) return false;
        return true;
    }

    return false;
}

/* IsTTCode - Returns TRUE if the code is a WMO TT code

   This function does NOT compare the code with a list with known codes.
   It checks just the format.

   Input : pTT - pointer to NUL-terminated array
*/
bool NBulletinFunctions::IsTTCode(const char* pTT)
{
    return (pTT && strlen(pTT) == 2 && TestFormat(pTT, "AA"));
}

/* IsAACode - Returns TRUE if the code is a WMO AA code

   This function does NOT compare the code with a list with known codes.
   It checks just the format.

   Input : pAA - pointer to NUL-terminated array
*/
bool NBulletinFunctions::IsAACode(const char* pAA)
{
    return (pAA && strlen(pAA) == 2 && TestFormat(pAA, "AA"));
}

/* IsIICode - Returns TRUE if the code is a WMO ii code

   Input : pII - pointer to NUL-terminated array
*/
bool NBulletinFunctions::IsIICode(const char* pII)
{
    return (pII && strlen(pII) == 2 && TestFormat(pII, "99"));
}

/* IsBBBCode - Returns TRUE if the code is a WMO BBB code

   This function accepts both old and modern style BBB codes.

   Input : pBBB - pointer to NUL-terminated array
*/
bool NBulletinFunctions::IsBBBCode(const char* pBBB)
{
    if (pBBB && strlen(pBBB) == 3) {
        if (TestFormat(pBBB, "AAA", 3)) {
            if (   TestFormat2(pBBB, "COR") 
                || TestFormat2(pBBB, "RTD") 
                || TestFormat2(pBBB, "AMD") 
                || TestFormat2(pBBB, "CC?") 
                || TestFormat2(pBBB, "AA?") 
                || TestFormat2(pBBB, "RR?")
                || TestFormat2(pBBB, "P??")){ // Segmented bulletin
                return true;
            }
        }
    }
    return false;
}

/* SkipWhiteSpace - The groups in a breakdown report are separated by whitespace. 
                    This function skips any whitespace

   In      : char* s : pointer to a position in a report. 
                       The report must be a NUL-terminated character-array (c-string)
   Returns : pointer to the next non-whitespace character or '\0'.
*/
const char* NBulletinFunctions::SkipWhiteSpace ( const char* s)
{
    const char* ptr = s;

    while ( IsGroupSeparationCharacter ( *ptr ) )                                   
        ptr++ ;
   
   return ptr ;
} 

const wchar_t *NBulletinFunctions::SkipWhiteSpace ( const wchar_t* s)
{
    const wchar_t* ptr = s;

    while ( IsGroupSeparationCharacter ( *ptr ) )                                   
        ptr++ ;
   
   return ptr ;
} 

/* GetStationCode - Get the station code from a report

   Input  :  FmCode  - WMO FM code
             pReport - pointer to NUL-terminated character array

   Returns:  the station code
*/
string NBulletinFunctions::GetStationCode(int FmCode, const char* pReport)
{
    string strResult;
    const char* group_pointer = pReport;

    if (pReport == NULL) 
        return strResult;

    group_pointer = SkipWhiteSpace(group_pointer);
    if (group_pointer[0] == '\0') 
        return strResult;

    if (FmCode == 15 || FmCode == 16 || FmCode == 51) { // METAR, SPECI, TAF

        // Check keywords
        if(    _strnicmp(group_pointer, "METAR", 5) == 0 
            || _strnicmp(group_pointer, "SPECI", 5) == 0) {

            group_pointer = GetStartOfNextGroup(group_pointer);

        } else if(_strnicmp(group_pointer, "TAF", 3) == 0) {
            group_pointer = GetStartOfNextGroup(group_pointer);
            if(_strnicmp(group_pointer, "AMD", 3) == 0) {
               group_pointer = GetStartOfNextGroup(group_pointer);
            }
        }

        // Check station code format
        strResult = ReadStringFromBuffer(group_pointer);
        if (!IsIcaoCode(strResult.c_str()))
            strResult = "";

    } else if (FmCode == 12) { // SYNOP

        // Check station code format
        strResult = ReadStringFromBuffer(group_pointer);
        if (!IsWmoCode(strResult.c_str()))
            strResult = "";

    } else if (FmCode == 32764) { // SIGMET

        // Check station code format
        strResult = ReadStringFromBuffer(group_pointer);
        if (!IsIcaoCode(strResult.c_str()))
            strResult = "";
    }

    // TODO: Temp, Pilot etc.

    return strResult;
}

/* LocateReportTime - Locate the time group in a report

   Input   :  FmCode  - WMO FM code
              pReport - pointer to NUL-terminated character array
   Output  :  strTime - the extracted time group if found
   Returns :  pointer to the time group or NULL if not found
*/
const char *NBulletinFunctions::LocateReportTime(int FmCode, const char* pReport, string& strTime)
{
    const char* group_pointer = pReport;
    int         group_length;
    char        szYYGGgg[7];
    char        szGGgg[5];
    string      strStation;

    strTime = "";

    if (pReport == NULL) 
        return NULL;

    group_pointer = SkipWhiteSpace(group_pointer);
    if (group_pointer[0] == '\0') 
        return NULL;

    if (FmCode == 15 || FmCode == 16) { // METAR, SPECI

        //(METAR) or (SPECI) (reserved keywords)
        if(    _strnicmp(group_pointer, "METAR", 5) == 0 
            || _strnicmp(group_pointer, "SPECI", 5) == 0) {

            group_pointer = GetStartOfNextGroup(group_pointer);

        } 

        strStation = ReadStringFromBuffer(group_pointer);
        if (IsIcaoCode(strStation.c_str())) {

            group_pointer = GetStartOfNextGroup(group_pointer);
            group_length = DetermineGroupLength(group_pointer);

            // (YYGGggZ) or (YYGGgg) or (GGgg) or (GGggZ) = report time
            if (    (group_length == 4) 
                 || (group_length == 5 && group_pointer[4] == 'Z') 
                 || (group_length == 6) 
                 || (group_length == 7 && group_pointer[6] == 'Z')) {

                if (group_length == 4 || group_length == 5) {
                    strncpy(szGGgg, group_pointer, 4);
                    szGGgg[4] = '\0';
                    if (IsGGgg(szGGgg)) {
                        strTime = szGGgg;
                        return group_pointer;
                    }
                } else if (group_length == 6 || group_length == 7) {
                    strncpy(szYYGGgg, group_pointer, 6);
                    szYYGGgg[6] = '\0';
                    if (IsWmoTime(szYYGGgg)) {
                        strTime = szYYGGgg;
                        return group_pointer;
                    }
                }
            }
        }
    }

    if (FmCode == 51) { // TAF

        //(TAF) (reserved keywords)
        if(_strnicmp(group_pointer, "TAF", 3) == 0) {
            group_pointer = GetStartOfNextGroup(group_pointer);
            if(_strnicmp(group_pointer, "AMD", 3) == 0) {
               group_pointer = GetStartOfNextGroup(group_pointer);
            }
        }

        strStation = ReadStringFromBuffer(group_pointer);
        if (IsIcaoCode(strStation.c_str())) {

            group_pointer = GetStartOfNextGroup(group_pointer);
            group_length = DetermineGroupLength(group_pointer);

            // (YYGGggZ) or (GGggZ) = report time
            // Do not confuse YYGGGG group (can also be YYGG in some cases)
            if (    (group_length == 5 && group_pointer[4] == 'Z') 
                 || (group_length == 7 && group_pointer[6] == 'Z')) {

                if (group_length == 5) {
                    strncpy(szGGgg, group_pointer, 4);
                    szGGgg[4] = '\0';
                    if (IsGGgg(szGGgg)) {
                        strTime = szGGgg;
                        return group_pointer;
                    }
                } else if (group_length == 7) {
                    strncpy(szYYGGgg, group_pointer, 6);
                    szYYGGgg[6] = '\0';
                    if (IsWmoTime(szYYGGgg)) {
                        strTime = szYYGGgg;
                        return group_pointer;
                    }
                }
            }
        }
    }
    // TODO: SIGMET

    return NULL;
}

/* GetReportTime - Get the report time from a report (if reported)

   Input   :  FmCode  - WMO FM code
              pReport - pointer to NUL-terminated character array
   Returns :  the time as YYGGgg or YYGG, without terminating 'Z', or empty string
              if not reported
*/
string NBulletinFunctions::GetReportTime(int FmCode, const char* pReport)
{
    string      strResult;

    LocateReportTime(FmCode, pReport, strResult);
    return strResult;
}

/* SetReportTime - Set the report time in a report

   If the report does not contain a time group, this function does nothing.

   Input   :  FmCode  - WMO FM code
              pReport - pointer to NUL-terminated character array
              strTime - the new time in YYGGgg or GGgg format
   Returns :  TRUE if updated
*/
bool NBulletinFunctions::SetReportTime(int FmCode, char* pReport, string strTime)
{
    string      strResult;
    bool        fResult = false;
    char*       group_pointer;

    group_pointer = (char*)LocateReportTime(FmCode, pReport, strResult);
    if (group_pointer) {
        if (strResult.length() == 4) //GGgg
            strncpy(group_pointer, strTime.c_str(), 4);
        else if (strResult.length() == 6)  //YYGGgg
            strncpy(group_pointer, strTime.c_str(), 6);
        fResult = true;
    } //if

    return fResult;
}

/* HasWmoReports - Returns TRUE when a bulletin 
                   contains reports described in WMO manual 306 Part A.
                   These reports are delimited by '='.
                   (see WMO manual 386 regulation 2.3.3.2.2)

   Returns FALSE when the FM code belongs to a binary report 
   (described in Part B).

   Note: For SIGMET, this functions returns FALSE since SIGMETs
         have no standard report terminators ('='). Furthermore,
         a SIGMET does not have a standard WMO format.
*/
bool NBulletinFunctions::HasWmoReports(int FmCode)
{
    const int ARRAY_SIZE = 49;

    // The last array element is not initialized.
    // See the documentation of the "find" algorithm
    // for details.
    
    int AlphaNumericalFmCodes[ARRAY_SIZE] = 
        { 12, 13, 14, 15, 16, 18, 20, 22, 32, 33, 
          34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 
          45, 46, 47, 49, 50, 51, 53, 54, 57, 61, 
          62, 63, 64, 65, 67, 68, 71, 72, 73, 75, 
          76, 81, 82, 83, 85, 86, 87, 88};

    int *plocation ;   
    bool fResult = false;

    plocation = find(AlphaNumericalFmCodes, 
                     AlphaNumericalFmCodes + ARRAY_SIZE, 
                     FmCode);

    if (plocation != AlphaNumericalFmCodes + ARRAY_SIZE)  {
        fResult = true;
    }

    return fResult;
}

/* IsAftnAddressLine - Test if a line can be identified as an Aftn address line

   NOTE: the header is IDENTIFIED, not VALIDATED!

   IN      : pLine - pointer to line to be tested, ends with NUL, CR or LF.
 
   RETURNS : TRUE if AFTN header line
*/
bool NBulletinFunctions::IsAftnAddressLine(const char* pLine)
{
    const int MAXLENGTH = 10;

    char szLine[MAXLENGTH + 1]; // buffer with start of WMO header
    const char *ptr = pLine;
    bool        fIsAddressLine = false;
    int         i = 0;
    int         j = 0;

    memset(szLine, 0, MAXLENGTH + 1);

    // Copy line to NUL-terminated buffer
    for (i = 0, j = 0; 
         i < MAXLENGTH && pLine[i] && pLine[i] != '\r' && pLine[i] != '\n';
         i++) {
         szLine[j++] = pLine[i];
    } //for
    szLine[j] = '\0'; // Add NUL character

    // Search for "FF ", "GG ", etc.
    if ( TestFormat(szLine, "AAS", 3) && szLine[0] == szLine[1]) {
        fIsAddressLine = true;
    } //if

    return fIsAddressLine;
}

/* GetReportType

   Input  : FmCode - FmCode
   Returns: report type as string
*/
basic_string<TCHAR> NBulletinFunctions::GetReportTypeString(int FmCode)
{ 
    switch (FmCode) {
        case 12:    return _T("SYNOP");
        case 13:    return _T("SHIP");
        case 14:    return _T("SYNOP MOBIL");
        case 15:    return _T("METAR");
        case 16:    return _T("SPECI");
        case 18:    return _T("BUOY");
        case 20:    return _T("RADOB");
        case 22:    return _T("RADREP");
        case 32:    return _T("PILOT");
        case 33:    return _T("PILOT SHIP");
        case 34:    return _T("PILOT MOBIL");
        case 35:    return _T("TEMP");
        case 36:    return _T("TEMP SHIP");
        case 37:    return _T("TEMP DROP");
        case 38:    return _T("TEMP MOBIL");
        case 39:    return _T("ROCOB");
        case 40:    return _T("ROCOB SHIP");
        case 41:    return _T("CODAR");
        case 42:    return _T("AMDAR");
        case 44:    return _T("ICEAN");
        case 45:    return _T("IAC");
        case 46:    return _T("IAC FLEET");
        case 47:    return _T("GRID");
        case 49:    return _T("GRAF");
        case 50:    return _T("WINTEM");
        case 51:    return _T("TAF");
        case 53:    return _T("ARFOR");
        case 54:    return _T("ROFOR");
        case 57:    return _T("RADOF");
        case 61:    return _T("MAFOR");
        case 62:    return _T("TRACKOB");
        case 63:    return _T("BATHY");
        case 64:    return _T("TESAC");
        case 65:    return _T("WAVEOB");
        case 67:    return _T("HYDRA");
        case 68:    return _T("HYFOR");
        case 71:    return _T("CLIMAT");
        case 72:    return _T("CLIMAT SHIP");
        case 75:    return _T("CLIMAT TEMP");
        case 76:    return _T("CLIMAT TEMP SHIP");
        case 81:    return _T("SFAZI");
        case 82:    return _T("SFLOC");
        case 83:    return _T("SFAZU");
        case 85:    return _T("SAREP");
        case 86:    return _T("SATEM");
        case 87:    return _T("SARAD");
        case 88:    return _T("SATOB");
        case 92:    return _T("GRIB");
        case 94:    return _T("BUFR");
        case 32763: return _T("SIGWX");
        case 32764: return _T("SIGMET");
        case 32765: return _T("FAX");
        default:    return _T("unknown report type");
    }

    return _T("unknown report type");
}

/* GetFmCode

   Input  : ReportType - A report type generated by GetReportTypeString above
   Returns: the FM code or 0 if invalid
*/
int NBulletinFunctions::GetFmCode(basic_string<TCHAR> &ReportType)
{ 
	if (ReportType == _T ("SYNOP"))
		return 12;
	else if (ReportType == _T ("SHIP"))
		return 13;
	else if (ReportType == _T ("SYNOP MOBIL"))
		return 14;
	else if (ReportType == _T ("METAR"))
		return 15;
	else if (ReportType == _T ("SPECI"))
		return 16;
	else if (ReportType == _T ("BUOY"))
		return 18;
	else if (ReportType == _T ("RADOB"))
		return 20;
	else if (ReportType == _T ("RADREP"))
		return 22;
	else if (ReportType == _T ("PILOT"))
		return 32;
	else if (ReportType == _T ("PILOT SHIP"))
		return 33;
	else if (ReportType == _T ("PILOT MOBIL"))
		return 34;
	else if (ReportType == _T ("TEMP"))
		return 35;
	else if (ReportType == _T ("TEMP SHIP"))
		return 36;
	else if (ReportType == _T ("TEMP DROP"))
		return 37;
	else if (ReportType == _T ("TEMP MOBIL"))
		return 38;
	else if (ReportType == _T ("ROCOB"))
		return 39;
	else if (ReportType == _T ("ROCOB SHIP"))
		return 40;
	else if (ReportType == _T ("CODAR"))
		return 41;
	else if (ReportType == _T ("AMDAR"))
		return 42;
	else if (ReportType == _T ("ICEAN"))
		return 44;
	else if (ReportType == _T ("IAC"))
		return 45;
	else if (ReportType == _T ("IAC FLEET"))
		return 46;
	else if (ReportType == _T ("GRID"))
		return 47;
	else if (ReportType == _T ("GRAF"))
		return 49;
	else if (ReportType == _T ("WINTEM"))
		return 50;
	else if (ReportType == _T ("TAF"))
		return 51;
	else if (ReportType == _T ("ARFOR"))
		return 53;
	else if (ReportType == _T ("ROFOR"))
		return 54;
	else if (ReportType == _T ("RADOF"))
		return 57;
	else if (ReportType == _T ("MAFOR"))
		return 61;
	else if (ReportType == _T ("TRACKOB"))
		return 62;
	else if (ReportType == _T ("BATHY"))
		return 63;
	else if (ReportType == _T ("TESAC"))
		return 64;
	else if (ReportType == _T ("WAVEOB"))
		return 65;
	else if (ReportType == _T ("HYDRA"))
		return 67;
	else if (ReportType == _T ("HYFOR"))
		return 68;
	else if (ReportType == _T ("CLIMAT"))
		return 71;
	else if (ReportType == _T ("CLIMAT SHIP"))
		return 72;
	else if (ReportType == _T ("CLIMAT TEMP"))
		return 75;
	else if (ReportType == _T ("CLIMAT TEMP SHIP"))
		return 76;
	else if (ReportType == _T ("SFAZI"))
		return 81;
	else if (ReportType == _T ("SFLOC"))
		return 82;
	else if (ReportType == _T ("SFAZU"))
		return 83;
	else if (ReportType == _T ("SAREP"))
		return 85;
	else if (ReportType == _T ("SATEM"))
		return 86;
	else if (ReportType == _T ("SARAD"))
		return 87;
	else if (ReportType == _T ("SATOB"))
		return 88;
	else if (ReportType == _T ("GRIB"))
		return 92;
	else if (ReportType == _T ("BUFR"))
		return 94;
	else if (ReportType == _T ("SIGWX"))
		return 32763;
	else if (ReportType == _T ("SIGMET"))
		return 32764;
	else if (ReportType == _T ("FAX"))
		return 32765;

    return 0;
}

/* IsNilReport - Returns TRUE if report is a NIL report

   Input : pReport - NUL-terminated character array
*/
bool NBulletinFunctions::IsNilReport(const char *pReport)
{
    const char* group_pointer = pReport;

    if (pReport == NULL) 
        return false; //NOTREACHED 

    // NIL should be one of the first 4 groups (do not search the whole report)
    // The following formats can be expected:
    // 1. <station code> NIL=                          (e.g. EHDB NIL=)
    // 2. <code name> <station code> NIL=              (e.g. METAR EHDB NIL=)
    // 3. <station code> <time group> NIL=             (e.g. EHDB 061200Z NIL=)
    // 4. <code name> <station code> <time group> NIL= (e.g. METAR EHDB 061200Z NIL=)
    // 5. NIL (this is more a NIL bulletin)
    group_pointer = SkipWhiteSpace(group_pointer);
    if (group_pointer[0] != '\0') {

        if (_stricmp(group_pointer, "NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_stricmp(group_pointer, "NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_stricmp(group_pointer, "NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_stricmp(group_pointer, "NIL=") == 0)
            return true; //NOTREACHED
    } //if

    return false;
}

/* IsNilReport - Returns TRUE if report is a NIL report

   Input : pReport - NUL-terminated character array
*/
bool NBulletinFunctions::IsNilReport(const wchar_t *pReport)
{
    const wchar_t *group_pointer = pReport;

    if (pReport == NULL) 
        return false; //NOTREACHED 

    // NIL should be one of the first 4 groups (do not search the whole report)
    group_pointer = SkipWhiteSpace(group_pointer);
    if (group_pointer[0] != '\0') {

        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_wcsicmp(group_pointer, L"NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_wcsicmp(group_pointer, L"NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_wcsicmp(group_pointer, L"NIL=") == 0)
            return true; //NOTREACHED
        group_pointer = GetStartOfNextGroup(group_pointer);
        if (_wcsicmp(group_pointer, L"NIL=") == 0)
            return true; //NOTREACHED
    } //if

    return false;
}

/* LocateValidityPeriod - Locate the validity period group in a report

   Input   :  FmCode  - WMO FM code
              pReport - pointer to NUL-terminated character array
   Output  :  strTime - the extracted validity time group if found
   Returns :  pointer to the validity period group or NULL if not found
*/
const char *NBulletinFunctions::LocateValidityPeriod(
    int FmCode, const char* pReport, string& strPeriod)
{
    const char* group_pointer = pReport;
    int         group_length;
    char        szYYGGGG[7];
    char        szGGGG[5];
    string      strStation;

    strPeriod = "";

    if (pReport == NULL) 
        return NULL;

    group_pointer = SkipWhiteSpace(group_pointer);
    if (group_pointer[0] == '\0') 
        return NULL;

    if (FmCode == 51) { // TAF

        //(TAF) (reserved keywords)
        if(_strnicmp(group_pointer, "TAF", 3) == 0) {
            group_pointer = GetStartOfNextGroup(group_pointer);
            if(_strnicmp(group_pointer, "AMD", 3) == 0) {
               group_pointer = GetStartOfNextGroup(group_pointer);
            }
        }

        strStation = ReadStringFromBuffer(group_pointer);
        if (IsIcaoCode(strStation.c_str())) {

            group_pointer = GetStartOfNextGroup(group_pointer);
            group_length = DetermineGroupLength(group_pointer);

            // (YYGGggZ) or (GGggZ) = report time
            if (    (group_length == 5 && group_pointer[4] == 'Z') 
                 || (group_length == 7 && group_pointer[6] == 'Z')) {

                group_pointer = GetStartOfNextGroup(group_pointer);
                group_length = DetermineGroupLength(group_pointer);
            }

            // standard is: day + start hour + end hour
            // (with two digits for day and hours)
            if (group_length == 6) {
                strncpy(szYYGGGG, group_pointer, 6);
                szYYGGGG[6] = '\0';
                strPeriod = szYYGGGG;
                return group_pointer;
            }
            if (group_length == 4) { // not standard: assume day missing
                strncpy(szGGGG, group_pointer, 4);
                szGGGG[4] = '\0';
                strPeriod = szGGGG;
                return group_pointer;
            }
        }
    }

    return NULL;
}

/* GetValidityPeriod

   Input  :  FmCode  - WMO format code
             pReport - NUL-terminated character array

   Returns:  the validity period
*/
string NBulletinFunctions::GetValidityPeriod(const int FmCode, const char *pReport)
{
    string strResult;

    LocateValidityPeriod(FmCode, pReport, strResult);
    return strResult;
}