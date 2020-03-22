#ifndef __SVersionInfoGetter_hpp
#define __SVersionInfoGetter_hpp

#include <afx.h>

class SVersionInfoGetter
{
private:

	char*	m_Buffer;

	char* GetSection (const CString& Section) const;

public:

	SVersionInfoGetter ();
	virtual ~SVersionInfoGetter ();

	CString ProductName () const;
	CString Version () const;
	CString Copyright () const;
};//SVersionInfoGetter

#endif

