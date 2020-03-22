// Configure.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "Configure.h"
#include "StickWorks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigure dialog

CConfigure::CConfigure(CWnd* pParent /*=NULL*/)
    : CDialog(CConfigure::IDD, pParent)
{
    //{{AFX_DATA_INIT(CConfigure)
    m_nSensitivity = 0;
    m_nThreshold = 0;
    //}}AFX_DATA_INIT
}
// -------------------------------------------------------------------
void CConfigure::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigure)
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_nSensitivity);
    DDV_MinMaxInt(pDX, m_nSensitivity, 0, 100);
    DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_nThreshold);
    DDV_MinMaxInt(pDX, m_nThreshold, 0, 25);
    //}}AFX_DATA_MAP
}
// -------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CConfigure, CDialog)
    //{{AFX_MSG_MAP(CConfigure)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigure message handlers

void CConfigure::OnOK() 
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();

    UpdateData(true);

    char    cTemp[80];

    // write sensitivity & threshold to ini file
    sprintf(cTemp, "%d", m_nThreshold);
    WritePrivateProfileString(
        STICK_WORKS_INI_SECTION_CONFIG,
        STICK_WORKS_INI_KEY_THRESHOLD,
        ::CString(cTemp),
        STICK_WORKS_INI_FILE_NAME); 

    sprintf(cTemp, "%d", m_nSensitivity);
    WritePrivateProfileString(
        STICK_WORKS_INI_SECTION_CONFIG,
        STICK_WORKS_INI_KEY_SENSITIVITY,
        ::CString(cTemp),
        STICK_WORKS_INI_FILE_NAME); 

    // update global sensitivity & threshold
    g_nThreshold   = m_nThreshold;
    g_nSensitivity = m_nSensitivity;
}
// -------------------------------------------------------------------
int CConfigure::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // TODO: Add your specialized creation code here
    m_nThreshold   = g_nThreshold;
    m_nSensitivity = g_nSensitivity;
    
    return 0;
}
// -------------------------------------------------------------------
BOOL CConfigure::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CSpinButtonCtrl     *pTempSpin = new CSpinButtonCtrl();

    pTempSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_THRESHOLD);
    pTempSpin->SetRange(0, 25);

    pTempSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_SENSITIVITY);
    pTempSpin->SetRange(0, 100);

    delete pTempSpin;

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
// -------------------------------------------------------------------
