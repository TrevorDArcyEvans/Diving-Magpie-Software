#ifndef __SBirdtamCell_hpp
#define __SBirdtamCell_hpp

#include <afx.h>
#include <afxtempl.h>
#include <afxdisp.h>

class SBirdtamCell:public CObject
{
private:

	char	m_XLetter;
	char	m_YLetter;
	short	m_Intensity;
	short	m_LowLimit;
	short	m_HiLimit;
	long	m_BeginValid;
	long	m_EndValid;

public:

	SBirdtamCell (const CString& Cell = "AA");
	SBirdtamCell (char XLetter,char YLetter):m_XLetter (XLetter),m_YLetter (YLetter) {}

	char XLetter () const {return m_XLetter;}
	char YLetter () const {return m_YLetter;}

	CString CellName () const;

	bool OutOfDate (const COleDateTime& Now) const;

	const short& Intensity () const {return m_Intensity;}	
	short& Intensity () {return m_Intensity;}

	const short& LowLimit () const {return m_LowLimit;}
	short& LowLimit () {return m_LowLimit;}

	const short& HiLimit () const {return m_HiLimit;}
	short& HiLimit () {return m_HiLimit;}

	const long& BeginValid () const {return m_BeginValid;}
	long& BeginValid () {return m_BeginValid;}

	const long& EndValid () const {return m_EndValid;}
	long& EndValid () {return m_EndValid;}

	CString LimitString () const;
	CString ValidString () const;

	SBirdtamCell& operator = (const SBirdtamCell& RVal);
};//SBirdtamCell

typedef CArray <SBirdtamCell,SBirdtamCell&> SBirdtamArray;

#endif

