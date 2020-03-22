#ifndef _SHResult_hpp
#define _SHResult_hpp

#include <comdef.h>

class SHResult
{
private:

	HRESULT m_hr;

public:

	SHResult (HRESULT hr = 0):m_hr (hr) {if (!SUCCEEDED (hr)) throw _com_error (hr);}

	const SHResult& operator = (HRESULT hr) {if (!SUCCEEDED (hr)) throw _com_error (hr); 
											 m_hr = hr; 
											 return *this;}

	operator HRESULT () const {return m_hr;}

};//SHResult

#endif




