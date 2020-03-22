/* BulletinFunctions.h - functions related to meteo bulletins
Copyright:   (C) Sigmex BV, 2000. All rights reserved.

   Basic functions for bulletin handling. Most functions are written
   in ANSI since bulletins are received in ANSI form.

$History: BulletinFunctions.h $
 * 
 * *****************  Version 13  *****************
 * User: Hans         Date: 5-09-01    Time: 17:30
 * Updated in $/Common/Projects/MeteoObjects
 * with method SetMessageBodyFromFile
 * 
 * *****************  Version 12  *****************
 * User: Hans         Date: 29-08-00   Time: 14:44
 * Updated in $/Common/Projects/MeteoObjects
 * with wide-char version of IsSigmet
 * 
 * *****************  Version 11  *****************
 * User: Hans         Date: 25-07-00   Time: 7:07
 * Updated in $/Common/Projects/MeteoObjects
 * with UNICODE versions of IsWmoBinary() etc.
 * 
 * *****************  Version 10  *****************
 * User: Hans         Date: 21-07-00   Time: 4:36
 * Updated in $/METCOM/Projects/BulletinFilterServer
 * with GetFmCode() to convert report type string back to FM code

*/

#ifndef BULLETINFUNCTIONS
#define BULLETINFUNCTIONS

#include <vector>
#include <string>

namespace NBulletinFunctions
{
    bool           IsGroupSeparationCharacter(char c);
    bool           IsGroupSeparationCharacter(wchar_t c);
    bool           IsReportTerminationCharacter ( char c );
    bool           IsReportTerminationCharacter ( wchar_t c );
    const char*    GetStartOfNextGroup(const char *pGroupPointer);
    const char*    GetStartOfPreviousGroup( const char *pGroupPointer, const char *pStartPointer );
    const wchar_t* GetStartOfNextGroup ( const wchar_t *pGroupPointer );
    int            DetermineGroupLength(const char* group_pointer);
    int            DetermineGroupLength(const wchar_t* group_pointer);
    const char*    SkipWhiteSpace ( const char* s );
    const wchar_t* SkipWhiteSpace ( const wchar_t* s);
    bool           IsWmoHeader(const char *pLine);
    bool           IsRbiLine(const char *pLine);
    int            ExtractReports(const char* pBuffer, std::vector<std::string>& reports);
    const char*    GetEndOfReport(const char* ptr);
    const char*    GetStartOfNextSigmetReport(const char* start_ptr);
    int            GetFmCode(const char *pTT, const char *pRBI);
    bool           ValidTTAndTime (const char *pTT, const char *pGG);
    bool           IsWmoFax(const char *pBulletin);
    bool           IsWmoFax(const wchar_t *pBulletin);
    bool           IsWmoGrib(const char *pBulletin);
    bool           IsWmoGrib(const wchar_t *pBulletin);
    bool           IsWmoBufr(const char *pBulletin);
    bool           IsWmoBufr(const wchar_t *pBulletin);
    bool           IsWmoBinary(const char *pBulletin);
    bool           IsWmoBinary(const wchar_t *pBulletin);
    bool           IsSigmet(const char *pBulletin);
    bool           IsSigmet(const wchar_t *pBulletin);
    bool           IsProtocolStartEnvelopeCharacter(char c);
    bool           IsProtocolEndEnvelopeCharacter(char c);
    int            GetBodyInProtocolEnvelope(const char* pBulletin, int BulletinSize, const char **ppStart, const char **ppEnd);
    int            GetWmoBody(const char *pBulletin, int BulletinSize, const char **ppStart, const char **ppEnd);
    bool           IsIcaoCode(const char * pIcao);
    bool           IsIcaoCode(const wchar_t * pIcao);
    bool           IsWmoCode(const char * pWmo);
    bool           IsWmoCode(const wchar_t * pWmo);
    bool           IsWmoTime(const char * pYYGGgg);
    bool           IsGGgg(const char *pGGgg);
    bool           IsTTCode(const char* pTT);
    bool           IsAACode(const char* pAA);
    bool           IsIICode(const char* pII);
    bool           IsBBBCode(const char* pBBB);
    bool           HasWmoReports(int FmCode);
    std::string    GetStationCode(int FmCode, const char* pReport);
    std::string    GetReportTime(int FmCode, const char* pReport);
    bool           SetReportTime(int FmCode, char* pReport, std::string strTime);
    bool           IsAftnAddressLine(const char* pLine);
    const char    *LocateReportTime(int FmCode, const char* pReport, std::string& strTime);
    bool           IsNilReport(const char* pReport);
    bool           IsNilReport(const wchar_t *pReport);
    std::string    GetValidityPeriod(int FmCode, const char* pReport);
    const char    *LocateValidityPeriod(int FmCode, const char* pReport, std::string& strTime);

    std::basic_string<TCHAR> GetReportTypeString(int FmCode);
    int GetFmCode(std::basic_string<TCHAR> &ReportTypeString);


} ;

#endif