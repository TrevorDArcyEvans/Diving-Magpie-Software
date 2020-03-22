// Register.cpp : implementation file
//

#include "stdafx.h"
#include "Register.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "crc_32.h"
#include "ZipWorks.h"
#include "utils.h"
#include "WinUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CRegister dialog


CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CRegister::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegister)
	m_cstrCode = _T("");
	m_cstrMachineID = _T("");
	//}}AFX_DATA_INIT
}


void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegister)
	DDX_Text(pDX, IDC_EDIT_CODE, m_cstrCode);
	DDX_Text(pDX, IDC_EDIT_MACHINE_ID, m_cstrMachineID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegister, CDialog)
	//{{AFX_MSG_MAP(CRegister)
	ON_BN_CLICKED(IDOK, OnButtonRegister)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegister message handlers

void CRegister::OnButtonRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	char *MachineIDStr  = new char[m_cstrMachineID  .GetLength() + 10];
	char *CodeStr       = new char[m_cstrCode       .GetLength() + 10];

    wu_strcpy(MachineIDStr  , m_cstrMachineID   );
    wu_strcpy(CodeStr       , m_cstrCode        );

    if (CheckCode(MachineIDStr, (char *) LPCTSTR(ZIP_WORKS_TITLE_CODE), CodeStr) == true)
        {
        MessageBox(_T("Successfully registered!"), _T(ZIP_WORKS_TITLE),
            MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION);

        WritePrivateProfileString(
            ZIP_WORKS_INI_FILE_SECTION,
            ZIP_WORKS_INI_FILE_KEY,
            m_cstrCode,
            ZIP_WORKS_INI_FILE_NAME); 

        // disable menu item & set running flag
        g_bRegistered = true;
        g_bRunning = true;
        }
    else
        {
        MessageBox(_T("Incorrect code!"), ZIP_WORKS_TITLE,
            MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
        }

	delete MachineIDStr;
	delete CodeStr;

	OnOK();	
}

int CRegister::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    m_cstrMachineID = GetMachineID();
	
	return 0;
}
