#include "stdafx.h"

#include "SString.hpp"
#include <math.h>


#ifdef __AFX_H__  // MFC  Only

#include <afx.h>
#include <afxdisp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#endif // __AFX_H__



SString& SString::MakeDespace ()
{
  return (*this) = Despace ();
}//SString::MakeTrimSpace

SString SString::Despace () const
{
  bool InQuote = false;

  SString RetVal;

  for (int i = 0; i < GetLength (); i++)
  {
    if (GetAt (i) == _T('"'))
      InQuote = !InQuote;
    //if

    if (InQuote || (GetAt (i) != _T(' ')))
      RetVal += GetAt (i);
    //if
  }//for

  return RetVal;
}//SString::Despace
  
int SString::FindAfter
(
  const CString&  SubStr,
  int       PosStart
)const
{
  LPCTSTR Buf = (LPCTSTR)(*this) ;

  LPTSTR Found = _tcsstr (Buf + PosStart + 1,SubStr);

  if (!Found)
    return -1;
  else
    return Found - Buf;
  //if
}//SString::FindAfter

int SString::FindFirst 
( 
  const CString& One,
  const CString& Other
)const
{
  int POne = Find (One);
  int POther = Find (Other);

  if (POne == -1)
    return POther;
  else
    return min (POne,POther);
  //if
}//SString::FindFirst

SElementExtractor SString::ExtractStart 
(
  const CString& Delim
)
{
  return SElementExtractor (Delim, (LPCTSTR)(*this) );
}//SString::ExtractStart

SString SString::ExtractNext
(
  SElementExtractor& Ex
)
{
  if (!Ex.m_Start)
    return _T("");
  //if

  LPTSTR Next = _tcsstr (Ex.m_Start,Ex.m_Delim);

  if (!Next)
  {
    SString RetVal = Ex.m_Start;
    Ex.m_Start = 0;
    return RetVal;
  }
  else
  {
    CString RetVal (Ex.m_Start,Next - Ex.m_Start);
    Ex.m_Start = Next + Ex.m_Delim.GetLength ();
    return RetVal;
  }//if
}//SString::ExtractNext

SString SString::Element 
(
  const SString&  Delim,
  int       Number
)const
{
  SString RetVal = (*this);
  int Pos ;

  for (int i = 0; i < Number; i++)
  {
    Pos = RetVal.Find (Delim);
    
    if (Pos >= 0)
      RetVal = RetVal.Mid (Pos + Delim.GetLength ());
    else if (i > 0 || Number > 0)
      return _T("");
    //if
  }//for

  Pos = RetVal.Find (Delim);

  if (Pos >= 0)
    RetVal = RetVal.Left (Pos);
  //if

  return RetVal;
}//SString::Element

SString& SString::MakeBetweenBrackets 
(
  TCHAR Open,
  TCHAR Close
)
{
  return (*this) = BetweenBrackets (Open,Close);
}//SString::MakeBetweenBrackets

SString SString::BetweenBrackets 
(
  TCHAR Open,
  TCHAR Close
)const
{
  int Start;
  int End;

  HelperBetweenBrackets (Start,End,Open,Close);

  if ((Start < 0) || (End < 0))
    return _T("");
  else
    return Mid (Start + 1,End - Start - 1);
  //if
}//SString::BetweenBrackets

void SString::HelperBetweenBrackets 
(
  int&  Start,
  int&  End,
  TCHAR Open,
  TCHAR Close
)const
{
  if (Close == _T('.'))
  {
    if (Open == _T('('))
      Close = _T(')');
    else if (Open == _T('['))
      Close = _T(']');
    else if (Open == _T('{'))
      Close = _T('}');
    else if (Open == _T('<'))
      Close = _T('>');
    else
      Close = _T(')');
    //if
  }//if

  Start = Find (Open);

  if (Start < 0)
    return;
  //if

  int Depth = 1;
  
  for (End = Start + 1; End < GetLength (); End++)
  {
    if (GetAt (End) == Close)
      Depth--;
    else if (GetAt (End) == Open) 
      Depth++;
    //if

    if (Depth <= 0)
      break;
    //if
  }//for
}//SString::HelperBetweenBrackets

SString SString::TakeBetweenBrackets
(
  TCHAR Open,
  TCHAR Close
)
{
  int Start;
  int End;

  HelperBetweenBrackets (Start,End,Open,Close);

  if ((Start < 0) || (End < 0))
    return _T("");
  else
  {
    SString RetVal = Mid (Start + 1,End - Start - 1);
    SString NewThis = Left (Start) + Mid (End + 1);

    (*this) = NewThis;

    return RetVal;
  }//if
}//SString::TakeBetweenBrackets

int SString::Count 
(
  TCHAR Character
)const
{
  int RetVal = 0;

  for (int i = 0; i < GetLength (); i++)
  {
    if (GetAt (i) == Character)
      RetVal++;
    //if
  }//for

  return RetVal;
}//SString::Count

SString SString::Upper () const
{
  SString RetVal = *this;

  RetVal.MakeUpper ();

  return RetVal;
}//SString::Upper

#pragma warning (disable:4244)

SString& SString::SetDegMinSec 
(
  double  Degrees,
  TCHAR NSorEW
)
{
  bool Positive = Degrees >= 0.0;

  Degrees = fabs (Degrees);

  int Deg = Degrees;

  Degrees -= Deg;
  Degrees = fabs (Degrees);

  int Min = Degrees * 60;

  int Secs = ((Degrees * 60) - Min) * 60;

  CString Template;

  switch (NSorEW)
  {
    default:  if (Positive)
            Template = _T("%d°%d'%d\"");
          else
            Template = _T("-%d°%d'%d\"");
          //if
          break;
    case 'N':
    case 'n':
    case 'S':
    case 's': if (Positive)
            Template = _T("%d°%d'%d\"N");
          else
            Template = _T("%d°%d'%d\"S");
          //if
          break;
    case 'E':
    case 'e':
    case 'W':
    case 'w': if (Positive)
            Template = _T("%d°%d'%d\"E");
          else
            Template = _T("%d°%d'%d\"W");
          //if
          break;
  }//switch

  Format (Template,Deg,Min,Secs);

  return *this;
}//SString::SetDegMinSec

#pragma warning (default:4244)

SString SString::ReplaceRange 
(
  const CString&  With,
  int       First,
  int       Last
)const
{
  SString FirstBit = Left (First);
  SString LastBit;

  if (Last > -1)
    LastBit = Mid (Last);
  //if

  return FirstBit + With + LastBit;
}//SString::ReplaceRange

SString SString::Replace 
(
  const CString& Findee,
  const CString& With
)const
{
  int Pos = Find (Findee);

  if (Pos == -1)
    return *this;
  else
    return Left (Pos) + With + Mid (Pos + Findee.GetLength ());
  //if
}//SString::Replace

SString SString::TakeLine ()
{
  SString RetVal;

  int Pos = FindFirst (_T("\r"),_T("\n"));

  if (Pos == -1)
  {
    RetVal = *this;
    *this = _T("");
  }
  else
  {
    RetVal = Left (Pos);

    while ((GetAt (Pos) == _T('\r')) || (GetAt (Pos) == _T('\n')))
      Pos++;
    //while

    *this = Mid (Pos);
  }//if

  return RetVal;
}//SString::TakeLine

SString SString::TrimSpace () const
{
  SString RetVal;

  int Length = GetLength ();

  bool WasSpace = false;

  for (int i = 0; i < Length; i++)
  {
    if (GetAt (i) == _T(' '))
    {
      if (!WasSpace)
      {
        RetVal += GetAt (i);
        WasSpace = true;
      }//if
    }
    else
    {
      RetVal += GetAt (i);
      WasSpace = false;
    }
  }//for

  return RetVal;
}//SString::TrimSpace

SString& SString::MakeTrimSpace ()
{
  return *this = TrimSpace ();
}//SString::MakeTrimSpace

    
bool SString::IsAlphaWild() const
{
  try
  {
    bool Result = true ;
    int  Length = GetLength() ;

    if ( Length == 0  )
      return false ;

    for ( int i = 0; i < GetLength(); i++ )
    {
      TCHAR t = GetAt(i) ;

      if ( !( _istalpha(t) || ( t == '*' ) || ( t =='?' )) )
      {
        Result = false ;
        break ;
      }
    }

    return Result ;
  }
  catch (...)
  {
    return false ;  
  }
}

bool SString::IsNumericWild() const
{
  try
  {
    bool Result = true ;
    int  Length = GetLength() ;

    if ( Length == 0  )
      return false ;

    for ( int i = 0; i < GetLength(); i++ )
    {
      TCHAR t = GetAt(i) ;

      if ( !( _istdigit(t) || ( t == '*' ) || ( t =='?' )) )
      {
        Result = false ;
        break ;
      }
    }

    return Result ;
  }
  catch (...)
  {
    return false ;  
  }
}








