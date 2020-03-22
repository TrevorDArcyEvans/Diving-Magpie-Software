#include "stdafx.h"
#include "DDX_LatLong.h"
#include "SString.hpp"
#include "StringToLatLong.h"

// Cut and pasted from secret MFC code
static BOOL SimpleFloatParse(LPCTSTR lpszText, double& d)
{
	ASSERT(lpszText != NULL);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	TCHAR chFirst = lpszText[0];
	d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	if (d == 0.0 && chFirst != '0')
		return FALSE;   // could not convert
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (*lpszText != '\0')
		return FALSE;   // not terminated properly

	return TRUE;
}

void DDX_LatLong 
(
	CDataExchange*	pDX, 
	int				nIDC, 
	double&			value, 
	TCHAR			NSorEW
)
{
//	Get a window on the control
	CWnd* CtrlWnd = CWnd::FromHandle (pDX->PrepareEditCtrl(nIDC));

	if (pDX->m_bSaveAndValidate)
	{
		SString Field;
			
//		Get the text
		CtrlWnd->GetWindowText (Field);		

//		Try for a normal float
		if (SimpleFloatParse(Field,value))
//			Good enough for us
			return;
		else if (StringToLatLong (Field,NSorEW,value))
//			Still okay
			return;
		else
		{
			AfxMessageBox(_T ("Invalid Lat/Long format"));
			pDX->Fail();            // throws exception
		}//if
	}
	else
	{
//		From data to dialog, so just convert to string
		SString AsString;

		AsString.SetDegMinSec (value,NSorEW);

		CtrlWnd->SetWindowText (AsString);
	}//if
}//DDX_LatLong


