// Dlg_Files.cpp : implementation file
//

#include "stdafx.h"
#include "BMPWorks.h"
#include "Dlg_Files.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Files dialog


CDlg_Files::CDlg_Files(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Files::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Files)
	m_nFileIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlg_Files::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Files)
	DDX_CBIndex(pDX, IDC_COMBO_FILES, m_nFileIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Files, CDialog)
	//{{AFX_MSG_MAP(CDlg_Files)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Files message handlers

BOOL CDlg_Files::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CComboBox*  pComboBox = (CComboBox *) GetDlgItem(IDC_COMBO_FILES);

    CString     cstrSearchFileSpec = m_cstrFileName.Mid(1, m_cstrFileName.GetLength() - 2);
    cstrSearchFileSpec += '*';
    //MessageBox(cstrSearchFileSpec, "Search File Spec", MB_OK);


    WIN32_FIND_DATA         fd;
    HANDLE hFind = FindFirstFile(cstrSearchFileSpec, &fd);
    if (hFind != INVALID_HANDLE_VALUE)
        {
        do
            {
            if (!(fd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
                FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM |
                FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE |
                FILE_ATTRIBUTE_TEMPORARY)))
                {
                //MessageBox(fd.cFileName, "File Find", MB_OK);
                pComboBox->AddString(fd.cFileName);
                }
            } while (FindNextFile(hFind, &fd));
        FindClose(hFind);
        }

    pComboBox->SetCurSel(0);

    if (1 == pComboBox->GetCount())
        {
        //MessageBox(m_cstrFileName, "Only one", MB_OK);
        OnOK();
        }


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Files::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);

    m_cstrFileName.Empty();

    CComboBox*  pComboBox = (CComboBox *) GetDlgItem(IDC_COMBO_FILES);

    pComboBox->GetLBText(0, m_cstrFileName);
	
	CDialog::OnOK();
}
