#ifndef _AlertSourceTypeToString_h
#define _AlertSourceTypeToString_h

#include "AlertSourceTypeEnum.h"




static LPCTSTR AlertSourceTypeToString
(
    AlertSourceTypeEnum Type
)
{
    switch (Type)
    {
        default                      :   return _T ("Unknown");
        case E_STATION_TYPE          :	 return _T("Station Type") ;
        case E_FIR_TYPE		           :   return _T("FIR Type") ;
        case E_UIR_TYPE		           :   return _T("UIR Type") ;
        case E_COUNTRY_TYPE	         :   return _T("Country Type") ;
        case E_STATION_SET_TYPE      :   return _T("Station Set Type") ;
    }//switch
}


static AlertSourceTypeEnum AlertSourceTypeFromString ( LPCTSTR Str )
{

  if ( _tcscmp( Str, _T("Station Type")) == 0 )
    return E_STATION_TYPE ;
  else if ( _tcscmp( Str, _T("FIR Type")) == 0 )
    return E_FIR_TYPE ;
  else if ( _tcscmp( Str, _T("UIR Type")) == 0 )
    return E_UIR_TYPE ;
  else if ( _tcscmp( Str, _T("Country Type")) == 0 )
    return E_COUNTRY_TYPE ;
  else if ( _tcscmp( Str, _T("Station Set Type")) == 0 )
    return E_STATION_SET_TYPE ;
  else
    return E_STATION_TYPE ;    

}



#endif
