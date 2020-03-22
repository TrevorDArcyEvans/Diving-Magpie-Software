// Dialogs.cpp : implementation file
//

#include "stdafx.h"
#include "FI_Demo.h"
#include "Dialogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRotation dialog


DlgRotation::DlgRotation(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRotation::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRotation)
	m_Angle = 0;
	//}}AFX_DATA_INIT
}


void DlgRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRotation)
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRotation, CDialog)
	//{{AFX_MSG_MAP(DlgRotation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// DlgImageInfos dialog


DlgImageInfos::DlgImageInfos(CWnd* pParent /*=NULL*/)
	: CDialog(DlgImageInfos::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgImageInfos)
	m_Class = _T("");
	m_Depth = 0;
	m_Height = 0;
	m_ResX = 0;
	m_ResY = 0;
	m_Width = 0;
	//}}AFX_DATA_INIT
}


void DlgImageInfos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgImageInfos)
	DDX_Text(pDX, IDC_IF_CLASS, m_Class);
	DDX_Text(pDX, IDC_IF_DEPTH, m_Depth);
	DDX_Text(pDX, IDC_IF_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_IF_RESX, m_ResX);
	DDX_Text(pDX, IDC_IF_RESY, m_ResY);
	DDX_Text(pDX, IDC_IF_WIDTH, m_Width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgImageInfos, CDialog)
	//{{AFX_MSG_MAP(DlgImageInfos)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// DlgFloat dialog


DlgFloat::DlgFloat(CWnd* pParent /*=NULL*/)
	: CDialog(DlgFloat::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgFloat)
	m_FloatName = _T("");
	m_FloatValue = 0.0f;
	//}}AFX_DATA_INIT
}


void DlgFloat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgFloat)
	DDX_Text(pDX, IDC_FLOAT_NAME, m_FloatName);
	DDX_Text(pDX, IDC_FLOAT_VALUE, m_FloatValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgFloat, CDialog)
	//{{AFX_MSG_MAP(DlgFloat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgFloat message handlers

BOOL DlgFloat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_sCaption);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
