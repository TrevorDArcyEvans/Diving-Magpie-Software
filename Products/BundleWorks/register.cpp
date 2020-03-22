// Register.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Register.h"

#include "crc_32.h"
#include "BundleWorks.h"
#include "utils.h"
#include "WinUtil.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	DDX_Text(pDX, IDC_CODE, m_cstrCode);
	DDX_Text(pDX, IDC_MACHINE_ID, m_cstrMachineID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegister, CDialog)
	//{{AFX_MSG_MAP(CRegister)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegister message handlers


int CRegister::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    m_cstrMachineID = GetMachineID();
	
	return 0;
}

void CRegister::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);

	char *MachineIDStr  = new char[m_cstrMachineID  .GetLength() + 10];
	char *CodeStr       = new char[m_cstrCode       .GetLength() + 10];

    wu_strcpy(MachineIDStr  , m_cstrMachineID   );
    wu_strcpy(CodeStr       , m_cstrCode        );

    if (CheckCode(MachineIDStr, (char *) LPCTSTR(BUN_WORKS_TITLE_CODE), CodeStr) == true)
        {
        MessageBox(_T("Successfully registered!"), BUN_WORKS_TITLE,
            MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION);

        WritePrivateProfileString(
            BUN_WORKS_INI_FILE_SECTION,
            BUN_WORKS_INI_FILE_KEY,
            m_cstrCode,
            BUN_WORKS_INI_FILE_NAME); 

        // disable menu item
        g_bRegistered = true;
        }
    else
        {
        MessageBox(_T("Incorrect code!"), BUN_WORKS_TITLE,
            MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);
        }


	delete MachineIDStr;
	delete CodeStr;

	CDialog::OnOK();
}
