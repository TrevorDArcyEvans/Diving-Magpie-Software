// FileName.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "FileName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileName dialog


CFileName::CFileName(CWnd* pParent /*=NULL*/)
	: CDialog(CFileName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZW_FileName)
	m_FileName = _T("");
	//}}AFX_DATA_INIT
}


void CFileName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZW_FileName)
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_FileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileName, CDialog)
	//{{AFX_MSG_MAP(CZW_FileName)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileName message handlers

void CFileName::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here
	
}
