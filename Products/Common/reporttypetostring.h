#ifndef _ReportTypeToString_h
#define _ReportTypeToString_h

#include"MeteoDataTypes.h"

static LPCTSTR ReportTypeToString
(
    WmoReportTypeEnum Type
)
{
    switch (Type)
    {
        default                      :   return _T ("Unknown");
        case DEC_FM_SYNOP            :   return _T ("SYNOP"); 
        case DEC_FM_SHIP             :   return _T ("SHIP");
        case DEC_FM_SYNOP_MOBIL      :   return _T ("SYNOP MOBIL");
        case DEC_FM_METAR            :   return _T ("METAR");
        case DEC_FM_SPECI            :   return _T ("SPECI");
        case DEC_FM_BUOY             :   return _T ("BUOY");
        case DEC_FM_RADOB            :   return _T ("RADOB");
        case DEC_FM_RADREP           :   return _T ("RADREP");
        case DEC_FM_PILOT            :   return _T ("PILOT");
        case DEC_FM_PILOT_SHIP       :   return _T ("PILOT SHIP");
        case DEC_FM_PILOT_MOBIL      :   return _T ("PILOT MOBIL");
        case DEC_FM_TEMP             :   return _T ("TEMP");
        case DEC_FM_TEMP_SHIP        :   return _T ("TEMP SHIP");
        case DEC_FM_TEMP_DROP        :   return _T ("TEMP DROP");
        case DEC_FM_TEMP_MOBIL       :   return _T ("TEMP MOBIL");
        case DEC_FM_ROCOB            :   return _T ("ROCOB");
        case DEC_FM_ROCOB_SHIP       :   return _T ("ROCOB SHIP");
        case DEC_FM_CODAR            :   return _T ("CODAR");
        case DEC_FM_AMDAR            :   return _T ("AMDAR");
        case DEC_FM_ICEAN            :   return _T ("ICEAN");
        case DEC_FM_IAC              :   return _T ("IAC");
        case DEC_FM_IAC_FLEET        :   return _T ("IAC FLEET");
        case DEC_FM_GRID             :   return _T ("GRID");
        case DEC_FM_GRAF             :   return _T ("GRAF");
        case DEC_FM_WINTEM           :   return _T ("WINTEM");
        case DEC_FM_TAF              :   return _T ("TAF");
        case DEC_FM_ARFOR            :   return _T ("ARFOR");
        case DEC_FM_ROFOR            :   return _T ("ROFOR");
        case DEC_FM_RADOF            :   return _T ("RADOF");
        case DEC_FM_MAFOR            :   return _T ("MAFOR");
        case DEC_FM_TRACKOB          :   return _T ("TRACKOB");
        case DEC_FM_BATHY            :   return _T ("BATHY");
        case DEC_FM_TESAC            :   return _T ("TESAC");
        case DEC_FM_WAVEOB           :   return _T ("WAVEOB");
        case DEC_FM_HYDRA            :   return _T ("HYDRA");
        case DEC_FM_HYFOR            :   return _T ("HYFOR");
        case DEC_FM_CLIMAT           :   return _T ("CLIMAT");
        case DEC_FM_CLIMAT_SHIP      :   return _T ("CLIMAT SHIP");
        case DEC_FM_NACLI            :   return _T ("NACLI");
        case DEC_FM_CLIMAT_TEMP      :   return _T ("CLIMAT TEMP");
        case DEC_FM_CLIMAT_TEMP_SHIP :   return _T ("CLIMAT TEMP SHIP");
        case DEC_FM_SFAZI            :   return _T ("SFAZI");
        case DEC_FM_SFLOC            :   return _T ("SFLOC");
        case DEC_FM_SFAZU            :   return _T ("SFAZU");
        case DEC_FM_SAREP            :   return _T ("SAREP");
        case DEC_FM_SATEM            :   return _T ("SATEM");
        case DEC_FM_SARAD            :   return _T ("SARAD");
        case DEC_FM_SATOB            :   return _T ("SATOB");
        case DEC_FM_GRIB             :   return _T ("GRIB");
        case DEC_FM_BUFR             :   return _T ("BUFR");
        case DEC_SIGWX               :   return _T ("SIGWX");       
        case DEC_SIGMET              :   return _T ("SIGMET");
        case DEC_FAX                 :   return _T ("FAX");
    }//switch
}
#endif
