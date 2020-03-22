//    MFCString.h
//
//////////////////////////////////////////////////////////////////////////////

#if !defined(MFCSTRING_H__CE71ED37_972C_11D0_9733_46963F000000__INCLUDED_)
#define MFCSTRING__CE71ED37_972C_11D0_9733_46963F000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////

#include <string>

//////////////////////////////////////////////////////////////////////////////

namespace NotMFC
{
   template<typename T>
   class CStringT : public std::basic_string<T> // T should be either char or wchar_t
   {
   private:

       static T    sm_Empty;                    // Null char (or wchar_t) for construction from null pointer - JK

   public:
      // Constructors
      CStringT();
      CStringT(const CStringT& strInput);
      CStringT(const std::basic_string<T>& strInput);
      CStringT(const T* strInput);
      CStringT(const T* strInput, int Length ) ;  //TG
      CStringT(T ch, int nRepeat = 1);

      // The string as an array
      int GetLength() const;
      bool IsEmpty() const;
      void Empty();
      T GetAt(int nIndex) const;
      void SetAt(int nIndex, T ch);

      // Comparison
      int Compare(const T* psz) const;
      int Compare(const CStringT& str) const;
      int CompareNoCase(const T* psz) const;
      int CompareNoCase(const CStringT& str) const;
      int Collate(const T* psz) const;
      int Collate(const CStringT& str) const;

      // Extraction
      CStringT Mid(int nFirst) const;
      CStringT Mid(int nFirst, int nCount) const;
      CStringT Left(int nCount) const;
      CStringT Right(int nCount) const;
      CStringT SpanIncluding(const T* pszCharSet) const;
      CStringT SpanExcluding(const T* pszCharSet) const;

		

      // Other Conversions
      void MakeUpper();
      void MakeLower();
      void MakeReverse();
      void TrimLeft();
      void TrimRight();
      void Format(const T* pszFormat, ... );

      // Searching
      int Find(const T& ch, int Posn = 0 ) const;
      int Find(const T* psz, int Posn = 0 ) const;
      int ReverseFind(const T& ch) const;
      int FindOneOf(const T* pszCharSet) const;

      // Operators
      operator const T*() const;
      T operator[](int nIndex) const;

			// TG
			int	Delete( int index, int count = 1 ) ;
   };


   #if defined UNICODE
     typedef CStringT<wchar_t> CString;
   #else
     typedef CStringT<char> CString;
   #endif


}; // namespace NotMFC

//////////////////////////////////////////////////////////////////////////////
#endif // !defined(MFCSTRING_H__CE71ED37_972C_11D0_9733_46963F000000__INCLUDED_)