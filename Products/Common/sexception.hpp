#ifndef __SException_hpp
#define __SException_hpp

#include "MFCStringImpl.h"

class SException
{
private:

    NotMFC::CString	m_Message;
	NotMFC::CString m_Filename;
	int			    m_LineNo;

public:

	SException (const NotMFC::CString& Message = _T ("Unspecified Exception."),bool Break = true):m_Message (Message),m_Filename (_T("Unknown")),m_LineNo (0) 
	{
#ifdef _DEBUG
		if (Break)
			DebugBreak ();
		//if
#endif
	}

	virtual ~SException () {}

	void SetWhere (const NotMFC::CString& Filename,int LineNo) {m_Filename = Filename; m_LineNo = LineNo;}
	void GetWhere (NotMFC::CString& Filename,int& LineNo) const  {Filename = m_Filename; LineNo = m_LineNo;}

	const NotMFC::CString& GetMessage () const {return m_Message;}
};//SException

class SComConnectionException:public SException
{
private:

	NotMFC::CString m_Interface;

public:

	SComConnectionException (const NotMFC::CString& IFace,const NotMFC::CString& Message = _T ("Failed to connect to COM object"))
		:SException (Message),m_Interface (IFace) {}
	virtual ~SComConnectionException () {}

	const NotMFC::CString& GetInterface () const {return m_Interface;}
};//SComConnectionException

class SAbortQuietlyException:public SException
{
public:

	SAbortQuietlyException (const NotMFC::CString& Message = _T ("Intentional Quit")):SException (Message,false) {}
};//SAbortQuietlyException

class SNotYetImplementedException:public SException
{
public:

	SNotYetImplementedException (const NotMFC::CString& Message):SException (Message) {}
};//SNotYetImplementedException

class SComException:public SException
{
private:

	HRESULT	m_hr;

public:

	SComException (HRESULT hr):SException (_T ("A COM error has occured."),false),m_hr (hr) {}

	HRESULT GetHRes () const {return m_hr;}
};//SComException

#endif
