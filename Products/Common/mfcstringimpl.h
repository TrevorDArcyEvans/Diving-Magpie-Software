//    MFCStringImpl.h
//
//////////////////////////////////////////////////////////////////////////////

#if !defined(MFCSTRINGIMPL_H__CE71ED33_972C_11d0_9733_46963F000000__INCLUDED_)
#define MFCSTRINGIMPL__CE71ED33_972C_11d0_9733_46963F000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <TCHAR.h>
#include <stdarg.h>
#include "MFCString.h"


//////////////////////////////////////////////////////////////////////////////


namespace NotMFC
{

    template<typename T>
    T    CStringT<T>::sm_Empty = T (0); // Null char (or wchar_t) for construction from null pointer - JK

///////////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline CStringT<T>::CStringT()
      :  std::basic_string<T>() {}

   template<typename T> inline CStringT<T>::CStringT(const CStringT& strInput)
      :  std::basic_string<T>(strInput) {}

   template<typename T> inline CStringT<T>::CStringT(const std::basic_string<T>& strInput)
      :  std::basic_string<T>(strInput) {}

   template<typename T> inline CStringT<T>::CStringT(const T* strInput)
       :  std::basic_string<T>(strInput?strInput:&sm_Empty) {}

   template<typename T> inline CStringT<T>::CStringT(T ch, int nRepeat /* = 1*/)
      :  std::basic_string<T>(nRepeat, ch) {}

   template<typename T> inline CStringT<T>::CStringT(const T* strInput, int Length )
      :  std::basic_string<T>( strInput?strInput:&sm_Empty, Length ) {}

///////////////////////////////////////////////////////////////////////////
// The string as an array
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline int CStringT<T>::GetLength() const
   {
      return length();
   };

   template<typename T> inline bool CStringT<T>::IsEmpty() const
   {
      return empty();
   };

   template<typename T> inline void CStringT<T>::Empty()
   {
      erase();
      return;
   };

   template<typename T> inline T CStringT<T>::GetAt(int nIndex) const
   {
      return at(nIndex);
   };

   template<typename T> inline void CStringT<T>::SetAt(int nIndex, T ch)
   {
      at(nIndex) = ch;
      return;
   };

///////////////////////////////////////////////////////////////////////////
// Comparison
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline int CStringT<T>::Compare(const T* psz) const
   {
      return compare(psz);
   };

   template<typename T> inline int CStringT<T>::Compare(const CStringT& str) const
   {
      return compare(str);
   };

   template<typename T> inline int CStringT<T>::CompareNoCase(const T* psz) const
   {
      return _tcsicmp(c_str(), psz);
   };

   template<typename T> inline int CStringT<T>::CompareNoCase(const CStringT& str) const
   {
      return _tcsicmp(c_str(), str.c_str());
   };

   template<typename T> inline int CStringT<T>::Collate(const T* psz) const
   {
      return _tcscoll(c_str(), psz);
   };

   template<typename T> inline int CStringT<T>::Collate(const CStringT& str) const
   {
      return _tcscoll(c_str(), str.c_str());
   };

///////////////////////////////////////////////////////////////////////////
// Extraction
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline CStringT<T> CStringT<T>::Mid(int nFirst) const
   {
      return substr(nFirst);
   };

   template<typename T> inline CStringT<T> CStringT<T>::Mid(int nFirst, int nCount) const
   {
      return substr(nFirst, nCount);
   };

   template<typename T> inline CStringT<T> CStringT<T>::Left(int nCount) const
   {
      return substr(0, nCount);
   };

   template<typename T> inline CStringT<T> CStringT<T>::Right(int nCount) const
   {
      return substr(length() - nCount, nCount);
   };

   template<typename T> inline CStringT<T> CStringT<T>::SpanIncluding(const T* pszCharSet) const
   {
      return substr(0, find_first_not_of(pszCharSet));
   };

   template<typename T> inline CStringT<T> CStringT<T>::SpanExcluding(const T* pszCharSet) const
   {
      return substr(0, find_first_of(pszCharSet));
   };

///////////////////////////////////////////////////////////////////////////
// Other Conversions
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline void CStringT<T>::MakeUpper()
   {
      T* pszTemp = new T[length() + 1];
      _tcscpy(pszTemp, c_str());
      _tcsupr(pszTemp);
      *this = pszTemp;
      delete [] pszTemp;
      // std::for_each(begin(), end(), _totupper);
      // Can't do this because toupper alters the iterator?
      return;
   };

   template<typename T> inline void CStringT<T>::MakeLower()
   {
      T* pszTemp = new T[length() + 1];
      _tcscpy(pszTemp, c_str());
      _tcslwr(pszTemp);
      *this = pszTemp;
      delete [] pszTemp;
      return;
   };

   template<typename T> inline void CStringT<T>::MakeReverse()
   {
      std::reverse(begin(), end());
      return;
   };

   template<typename T> inline void CStringT<T>::TrimLeft()
   {
	   while (_istspace(at(0)))
		   erase(0, 1);
      return;
   };

   template<typename T> inline void CStringT<T>::TrimRight()
   {
	   while (_istspace( at(length() - 1) ))
		   erase(length() - 1, 1);
      return;
   };

   // Only works if the final string is less than 512 characters
   // TODO: make it work properly
   template<typename T> inline void CStringT<T>::Format(const T* pszFormat, ... )
   {
      // Doesn't have all the features of CString::Format()
      va_list vl;
      va_start(vl, pszFormat);

      T* pszTemp = NULL;
      int nBufferSize = 0;
      int nRetVal = -1;

      do
      {
         // Increment the buffer 512 characters at a time
         // I'm not sure whether this is robust!
		 // This is NOT robust - vstprintf will overrun the buffer
         nBufferSize += 512;
         delete [] pszTemp;
         pszTemp = new T [nBufferSize];
         nRetVal = _vstprintf(pszTemp, pszFormat, vl);
      } while (nRetVal < 0);

      *this = pszTemp;
      delete [] pszTemp;

      va_end(vl);
      return;
   };

///////////////////////////////////////////////////////////////////////////
// Searching
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline int CStringT<T>::Find(const T& ch, int Posn  ) const
   {
      // npos == -1 in this implementation, but it might not always be, so this is
      // a bit dodgy.
      return find(ch, Posn );
   };

   template<typename T> inline int CStringT<T>::Find(const T* psz, int Posn ) const
   {
      return find(psz, Posn );
   };

   template<typename T> inline int CStringT<T>::ReverseFind(const T& ch) const
   {
      return rfind(ch);
   };

   template<typename T> inline int CStringT<T>::FindOneOf(const T* psz) const
   {
      return find_first_of(psz);
   };

///////////////////////////////////////////////////////////////////////////
// Operators
///////////////////////////////////////////////////////////////////////////

   template<typename T> inline CStringT<T>::operator const T*() const
   { return c_str(); };

   template<typename T> inline T CStringT<T>::operator[](int nIndex) const
   { return at(nIndex); };

template<typename T> inline bool operator==(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) == 0; }
template<typename T> inline bool operator==(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) == 0; }
template<typename T> inline bool operator==(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) == 0; }

template<typename T> inline bool operator!=(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) != 0; }
template<typename T> inline bool operator!=(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) != 0; }
template<typename T> inline bool operator!=(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) != 0; }

template<typename T> inline bool operator<(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) < 0; }
template<typename T> inline bool operator<(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) < 0; }
template<typename T> inline bool operator<(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) > 0; }

template<typename T> inline bool operator>(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) > 0; }
template<typename T> inline bool operator>(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) > 0; }
template<typename T> inline bool operator>(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) < 0; }

template<typename T> inline bool operator<=(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) <= 0; }
template<typename T> inline bool operator<=(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) <= 0; }
template<typename T> inline bool operator<=(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) >= 0; }

template<typename T> inline bool operator>=(const CStringT<T>& s1, const CStringT<T>& s2)
	{ return s1.compare(s2) >= 0; }
template<typename T> inline bool operator>=(const CStringT<T>& s1, const T* s2)
	{ return s1.compare(s2) >= 0; }
template<typename T> inline bool operator>=(const T* s1, const CStringT<T>& s2)
	{ return s2.compare(s1) <= 0; }

template< typename T> int	CStringT<T>::Delete( int index, int count )
{
	erase( index, count ) ;
	return 0 ;
}



}; // namespace NotMFC

//////////////////////////////////////////////////////////////////////////////


#endif // !defined(MFCSTRINGIMPL_H__CE71ED33_972C_11d0_9733_46963F000000__INCLUDED_)