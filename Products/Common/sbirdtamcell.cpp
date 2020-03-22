#include "SBirdtamCell.hpp"
#include "STimeStuff.hpp"

SBirdtamCell::SBirdtamCell 
(
	const CString& Cell
)
{
	if (Cell.GetLength () == 2)
	{
		m_XLetter = Cell[0];
		m_YLetter = Cell[1];
	}
	else
	{
		m_XLetter = 'A';
		m_YLetter = 'A';
	}//if
}//SBirdtamCell::SBirdtamCell

CString SBirdtamCell::CellName () const
{
	return (CString)m_XLetter + (CString)m_YLetter;
}//SBirdtamCell::SBirdtamCell

bool SBirdtamCell::OutOfDate 
(
	const COleDateTime& Now
)const
{
	COleDateTime EndValid = STimeStuff::CreateOleFromWMO (m_EndValid);

	if (EndValid.GetStatus () == COleDateTime::valid)
		return Now > EndValid;
	else
		return true;
	//if
}//SBirdtamCell::OutOfDate

CString SBirdtamCell::LimitString () const
{
	CString RetVal;

	RetVal.Format ("%d-%d",m_LowLimit,m_HiLimit);

	return RetVal;
}//SBirdtamCell::LimitString

CString SBirdtamCell::ValidString () const
{
	CString BV;
	CString EV;

	BV.Format ("%d",m_BeginValid);
	EV.Format ("%d",m_EndValid);

	if (BV.GetLength () < 6)
		BV = "0" + BV;
	//if

	if (EV.GetLength () < 6)
		EV = "0" + EV;
	//if

	return "(" + BV + "/" + EV + ")";
}//SBirdtamCell::ValidString

SBirdtamCell& SBirdtamCell::operator = 
(
	const SBirdtamCell& RVal
)
{
	m_BeginValid = RVal.m_BeginValid;
	m_EndValid = RVal.m_EndValid;
	m_HiLimit = RVal.m_HiLimit;
	m_LowLimit = RVal.m_LowLimit;
	m_Intensity = RVal.m_Intensity;
	m_XLetter = RVal.m_XLetter;
	m_YLetter = RVal.m_YLetter;

	return *this;
}//SBirdtamCell::operator = 









