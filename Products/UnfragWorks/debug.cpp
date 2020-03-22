// Break.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------

void	UW_OutputDebugString(
			// pointer to string to be displayed
			LPCTSTR lpOutputString
			)
{
// tde
// todo - conditional compiles but need more configurations
OutputDebugString(lpOutputString);
}

//------------------------------------------------------
