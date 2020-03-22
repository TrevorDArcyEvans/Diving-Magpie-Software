// FI_Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FI_Demo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "FI_Doc.h"
#include "FI_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char BASED_CODE szFilterOpen[] =
"All image files|*.tif;*.bmp;*.dib;*.ico;*.jpg;*.png;*.pcd;*.pgm;*.pbm;*.ppm;*.pcx;*.tga;*.ras|\
All Files (*.*)|*.*|\
Tag Image File Format (.tif)|*.tif|Windows Bitmap (.bmp .dib .ico)|*.bmp; *.dib; *.ico|\
JPEG File Interchange Format (.jpg)|*.jpg|PNG (Portable Network Graphics) (.png)|*.png|\
CD Photo Kodak (.pcd)|*.pcd|Portable Anymap File Format (.pgm, .pbm .ppm)|*.pgm; *.pbm; *.ppm|\
Zsoft PC Paintbrush (.pcx)|*.pcx|Sun rasterfile (.ras)|*.ras|Targa Truevision (.tga)|*.tga||";


/////////////////////////////////////////////////////////////////////////////
// CFI_App

BEGIN_MESSAGE_MAP(CFI_App, CWinApp)
	//{{AFX_MSG_MAP(CFI_App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFI_App construction

CFI_App::CFI_App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFI_App object

CFI_App theApp;

/////////////////////////////////////////////////////////////////////////////
// CFI_App initialization

BOOL CFI_App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("FreeImage"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_FI_DEMTYPE,
		RUNTIME_CLASS(CFI_Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFI_View));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

    // Alter behaviour to not open window immediately
	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Accept dropped files from the Windows File Manager
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Copyright;
	CString	m_Version;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_Copyright = FreeImage_GetCopyrightMessage();
	m_Version = _T("FreeImage version : ") + CString(FreeImage_GetVersion());
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_ABOUT_COPYRIGHT, m_Copyright);
	DDX_Text(pDX, IDC_ABOUT_VERSION, m_Version);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFI_App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFI_App commands

void CFI_App::OnFileOpen() 
{
	//Bring up the File Open dialog with the customized filter string
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilterOpen, NULL);
	if (dlgFile.DoModal() == IDOK)
		AfxGetApp()->OpenDocumentFile(dlgFile.GetPathName());	
}

