#ifndef __SString_hpp
#define __SString_hpp

#include <stdafx.h>   

#ifndef __AFX_H__  // Not Including MFC
#include "MFCStringImpl.h"
using NotMFC::CString ;
#endif



class COleDateTime;
class SString;

class SElementExtractor
{
friend class SString;

private:

  CString   m_Delim;
  LPCTSTR   m_Start;

  SElementExtractor (const CString& Delim,LPCTSTR Start):m_Delim (Delim),m_Start (Start) {}

public:

  SElementExtractor (const SElementExtractor& RVal):m_Delim (RVal.m_Delim),m_Start (RVal.m_Start) {}

  bool Active () {return m_Start != 0 ;}
};//SElementExtractor

class SString:public CString 
{
private:

  void HelperBetweenBrackets (int& Start,int& End,TCHAR Open = _T('('),TCHAR Close = _T('.')) const;

public:

  SString ():CString (){}
  SString (const CString& RVal):CString (RVal) {}
  SString (LPCTSTR    RVal):CString (RVal) {}

  SString& MakeDespace ();
  SString  Despace () const;

  SString Element (const SString& Delim = _T(","),int Number = 0) const;

  SString& MakeBetweenBrackets (TCHAR Open = _T('('),TCHAR Close = _T('.'));
  SString  TakeBetweenBrackets (TCHAR Open = _T('('),TCHAR Close = _T('.'));
  SString  BetweenBrackets   (TCHAR Open = _T('('),TCHAR Close = _T('.')) const;

  SString Upper () const;

  SString& SetDegMinSec (double Degrees,TCHAR NSorEW = _T(' '));

  SString Replace (const CString& Findee,const CString& With = _T("")) const;
  SString ReplaceRange (const CString& With,int First,int Last = -1) const;

  int FindAfter (const CString& SubStr,int PosStart) const;
  int FindFirst (const CString& One,const CString& Other) const;

  SElementExtractor ExtractStart (const CString& Delim);
  SString ExtractNext (SElementExtractor& Ex);

  int Count (TCHAR Character) const;

  SString TakeLine ();

  SString TrimSpace () const;
  SString& MakeTrimSpace ();

  bool IsAlphaWild() const ;  // Tests whether string is alphabetic only ( wildcards permitted *,? )
  bool IsNumericWild() const ;// Tests whether string is numeric only ( wildcards permitted *, ? )

};//SString

#endif

