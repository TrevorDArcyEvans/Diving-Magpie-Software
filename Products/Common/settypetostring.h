#ifndef _SetTypeToString_h
#define _SetTypeToString_h

#include "MeteoDataTypes.h"



static LPCTSTR SetTypeToString
(
    SetType s
)
{
    switch (s)
    {
        default                      :   return _T ("User");
        case E_SYSTEM                :	 return _T("System") ;
        case E_USER		               :   return _T("User") ;
    }//switch
}


static SetType SetTypeFromString ( LPCTSTR Str )
{
  if ( _tcscmp( Str, _T("User")) == 0 )
    return E_USER ;
  else if ( _tcscmp( Str, _T("System")) == 0 )
    return E_SYSTEM ;
  else
    return E_USER ;    
}

#endif
