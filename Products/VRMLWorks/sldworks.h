// -------------------------------------------------------------------
//
//                Copyright 1997 (Unpublished material)
//                       SolidWorks Corporation
//
// -------------------------------------------------------------------
//
//     Filename: SldWorks.h
//  Description: Includes the SolidWorks include files plus string
//               functions for Unicode and MBCS
//
// -------------------------------------------------------------------

#if !defined(SOLIDWORKS_H)
#define SOLIDWORKS_H

#include <amapp.h>
#include <swconst.h>

#ifdef _MBCS

class auT
{
public:
	auT( LPCTSTR val ) : iValue( val ), iBStr( NULL ) { }

	~auT( )
	{ if( iBStr != NULL )	::SysFreeString( iBStr ); }

	operator BSTR()         
	{
		if( iBStr != NULL )
			{ ::SysFreeString( iBStr );	iBStr = NULL; }
		iBStr = iValue.AllocSysString();
		return iBStr;
	}
	
private:
	BSTR iBStr;
	CString iValue;
};

#define au2B( STUFF ) auT(STUFF)

#else

#define auT _T

#define au2B( STUFF ) (LPTSTR)((LPCTSTR)STUFF)

#endif

#endif

// --------------------------------
//  End of SldWorks.h
// --------------------------------
