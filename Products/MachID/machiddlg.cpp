// MachIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MachID.h"
#include "MachIDDlg.h"

#include "crc_32.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMachIDDlg dialog

CMachIDDlg::CMachIDDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CMachIDDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMachIDDlg)
    m_cstrMachID = _T("");
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMachIDDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMachIDDlg)
    DDX_Text(pDX, IDC_EDIT_MACH_ID, m_cstrMachID);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMachIDDlg, CDialog)
    //{{AFX_MSG_MAP(CMachIDDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMachIDDlg message handlers

BOOL CMachIDDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    

    char        cTempStr[_MAX_PATH];

    GetMachineID(cTempStr);
    m_cstrMachID = cTempStr;

    UpdateData(FALSE);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMachIDDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMachIDDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

