#include "stdafx.h"
#include "SMultiExtMDIDocTemplate.hpp"
#include "SString.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDocTemplate::Confidence SMultiExtMDIDocTemplate::MatchDocType
(
	const char* pszPathName, 
	CDocument*& rpDocMatch
)
{
    ASSERT(pszPathName != NULL);
    rpDocMatch = NULL;

    // go through all documents
    POSITION pos = GetFirstDocPosition();
    while (pos != NULL)
    {
       CDocument* pDoc = GetNextDoc(pos);
       if (pDoc->GetPathName() == pszPathName) {
          // already open
          rpDocMatch = pDoc;
          return yesAlreadyOpen;
       }
    }  // end while

    // see if it matches either suffix
    SString strFilterExt;

    AfxExtractSubString(strFilterExt, m_strDocStrings, (int)CDocTemplate::filterExt);

	strFilterExt.MakeLower ();	// Lower so comparison is insensitive

    if (!strFilterExt.IsEmpty())
    {
		int i = 0;

		CString PathName (pszPathName);

		PathName.MakeLower (); // Lower so comparison is insensitive

		while (true)
		{
			CString Suffix = strFilterExt.Element (";",i++);
			
			if (Suffix.IsEmpty ())
				return yesAttemptForeign;
			//if
			
			if (PathName.Find (Suffix) == PathName.GetLength () - Suffix.GetLength ())
				return yesAttemptNative;
			//if
		}//while
	}//if

    return yesAttemptForeign; //unknown document type
}//SMultiExtMDIDocTemplate::MatchDocType
 
BOOL SMultiExtMDIDocTemplate::GetDocString
(
	CString& rString, 
	enum DocStringIndex i
)const
{
    SString strTemp;

	if (m_NewCount != 0 && i == CDocTemplate::fileNewName)
	{
		strTemp = "";

		if (m_NewCount > 0)
			m_NewCount--;
		//if
	}
	else
	    AfxExtractSubString(strTemp, m_strDocStrings, (int)i);
	//if

    if((i == CDocTemplate::filterExt) && (strTemp.Find (";") != -1))  
	{
		int j = 0;

		while (true)
		{
			CString Suffix = strTemp.Element (";",j++);

			if (Suffix.IsEmpty ())
				break;
			//if
			
			if (j == 1)
				rString = Suffix;
			else
				rString += (CString)";*" + Suffix;
			//if

		}//while
	}
	else			
		rString = strTemp;
	//if

	return TRUE;
}