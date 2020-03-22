#ifndef _SStringPasser_hpp
#define _SStringPasser_hpp

#include <atlconv.h> 

namespace SStringPasser
{
	inline CString GetCString (const BSTR& String) { USES_CONVERSION; 
													 CString RetVal = OLE2T (String);
													 ::SysFreeString (String);
													 return RetVal;}
}//SStringPasser

#endif
