//---------------------------------------------------------------------------
#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>
#include "CSPIN.h"
#include "Regi1632.hpp"
#include <stdlib.h>

#include <shellapi.h>
#include <ExtCtrls.hpp>
#include "browsefoldersdialog.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#ifdef MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
GLOBAL  UINT            g_nBytesSaved;
GLOBAL  bool            g_bRegistered;
GLOBAL  TStringList     *g_strsFileList;
GLOBAL  bool            g_bIsUnfraggingNow;

//---------------------------------------------------------------------------
#define WM_UNFRAG_ICON_MESSAGE      (WM_USER + 1)
//---------------------------------------------------------------------------
#define UW_HANDLE_REG_ERROR     \
            if (regUnfragWksSV->WasError == true) { WasError = true; goto CLEAN_UP; }

// TDE have to do something here for Gold version
#define UNFRAG_WORKS_HELP                   "\\Program Files\\SolidPartners\\UnfragWorks Server\\UnfragWorksSv.HLP"

#ifdef UWSV_GOLD
#define UNFRAG_WORKS_TITLE                  "UnfragWorks Server Gold v2.1"
#define UNFRAG_WORKS_TITLE_CODE             "UnfragWorks Server Gold v2.x"
#else
#define UNFRAG_WORKS_TITLE                  "UnfragWorks Server v2.1"
#define UNFRAG_WORKS_TITLE_CODE             "UnfragWorks Server v2.x"
#endif

#define UNFRAG_WORKS_INI_FILE_SECTION       "Security"
#define UNFRAG_WORKS_INI_FILE_KEY           "code"
//---------------------------------------------------------------------------
const int NUM_DIR       = 5;
#ifdef UWSV_GOLD
const int NUM_FILTER    = 6;
#else
const int NUM_FILTER    = 3;
#endif

#ifdef MAIN
const char    *chkDirEnabled[NUM_DIR] =
    {
    "chkDirEnabled01",
    "chkDirEnabled02",
    "chkDirEnabled03",
    "chkDirEnabled04",
    "chkDirEnabled05",
    };

const char    *chkSubDirName[NUM_DIR] =
    {
    "chkDirSub01",
    "chkDirSub02",
    "chkDirSub03",
    "chkDirSub04",
    "chkDirSub05",
    };

const char    *edtBrowseName[NUM_DIR] =
    {
    "edtDirName01",
    "edtDirName02",
    "edtDirName03",
    "edtDirName04",
    "edtDirName05",
    };

const char    *btnDirBrowseName[NUM_DIR] =
    {
    "btnDirBrowse01",
    "btnDirBrowse02",
    "btnDirBrowse03",
    "btnDirBrowse04",
    "btnDirBrowse05",
    };

const char    *IniDirName[NUM_DIR] =
    {
    "Dir01",
    "Dir02",
    "Dir03",
    "Dir04",
    "Dir05",
    };

const char    *dirwUnfragName[NUM_DIR] =
    {
    "dirwUnfrag01",
    "dirwUnfrag02",
    "dirwUnfrag03",
    "dirwUnfrag04",
    "dirwUnfrag05",
    };

// TDE have to do something here for Gold version
const char    *cFileFilter[NUM_FILTER] =
    {
    "*.sldprt",
    "*.sldasm",
    "*.slddrw",
    #ifdef UWSV_GOLD
    "*.doc",
    "*.xls",
    "*.ppt",
    #endif
    };
#else
extern const char    *chkDirEnabled   [NUM_DIR    ];
extern const char    *chkSubDirName   [NUM_DIR    ];
extern const char    *edtBrowseName   [NUM_DIR    ];
extern const char    *btnDirBrowseName[NUM_DIR    ];

extern const char    *IniDirName      [NUM_DIR    ];
extern const char    *dirwUnfragName  [NUM_DIR    ];

extern const char    *cFileFilter     [NUM_FILTER ];
#endif
//---------------------------------------------------------------------------
class TfrmConfig : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pcMain;
    TTabSheet *tsDirectories;
    TTabSheet *tsServer;
    TButton *btnRead;
    TButton *btnWrite;
    TMainMenu *mnuMain;
    TMenuItem *mnuFile;
    TMenuItem *mnuExit;
    TMenuItem *mnuEdit;
    TMenuItem *mnuPaste;
    TMenuItem *mnuCopy;
    TMenuItem *mnuCut;
    TMenuItem *mnuHelp;
    TMenuItem *mnuAbout;
    TMenuItem *mnuContents;
    TTabSheet *tsLogging;
    TCheckBox *chkStartStopService;
    TCheckBox *chkStartStopUnfrag;
    TCheckBox *chkFilesExamineUnfrag;
    TCheckBox *chkBytesSaved;
    TTabSheet *tsSchedule;
    TDateTimePicker *dtUnfragTime;
    TComboBox *cmbSchedDayType;
    TLabel *Label1;
    TLabel *Label2;
    TCSpinEdit *sedTimeout;
    TLabel *Label3;
    TLabel *Label4;
    TCSpinEdit *sedThreads;
    TComboBox *cmbPriority;
    TLabel *Label5;
    TCheckBox *chkDirSub01;
    TEdit *edtDirName01;
    TButton *btnDirBrowse01;
    TCheckBox *chkRemovePreview;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TTabSheet *tsAdmin;
    TEdit *edtMachID;
    TEdit *edtCode;
    TButton *btnRegister;
    TEdit *edtDirName02;
    TEdit *edtDirName03;
    TEdit *edtDirName04;
    TEdit *edtDirName05;
    TButton *btnDirBrowse02;
    TButton *btnDirBrowse03;
    TButton *btnDirBrowse04;
    TButton *btnDirBrowse05;
    TCheckBox *chkDirSub02;
    TCheckBox *chkDirSub03;
    TCheckBox *chkDirSub04;
    TCheckBox *chkDirSub05;
    TCheckBox *chkRemoveGeom;
    TRegistry1632 *regUnfragWksSV;
    TStatusBar *stbUnfragWks;
    TMenuItem *mnuRead;
    TMenuItem *mnuWrite;
    TMenuItem *N1;
    TTimer *tmrConfig;
    TPopupMenu *pmnuConfig;
    TMenuItem *pmnuConfigure;
    TMenuItem *N2;
    TMenuItem *pmnuAbout;
    TMenuItem *pmnuHelp;
    TLabel *Label9;
    TCheckBox *chkDirEnabled01;
    TCheckBox *chkDirEnabled02;
    TCheckBox *chkDirEnabled03;
    TCheckBox *chkDirEnabled04;
    TCheckBox *chkDirEnabled05;
    TLabel *Label10;
    TComboBox *cmbSchedHourType;
    TLabel *Label11;
    TLabel *Label12;
    TBrowseFoldersDialog *BrowseFoldersDialog;
    TButton *btnViewLog;
    TMenuItem *pmnuViewLog;
    void __fastcall btnDirBrowse01Click(TObject *Sender);
    void __fastcall btnDirBrowse02Click(TObject *Sender);
    void __fastcall btnDirBrowse03Click(TObject *Sender);
    void __fastcall btnDirBrowse04Click(TObject *Sender);
    void __fastcall btnDirBrowse05Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnReadClick(TObject *Sender);
    void __fastcall btnWriteClick(TObject *Sender);
    void __fastcall mnuAboutClick(TObject *Sender);
    void __fastcall mnuExitClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall tmrConfigTimer(TObject *Sender);
    void __fastcall pmnuConfigureClick(TObject *Sender);
    void __fastcall pmnuAboutClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall mnuContentsClick(TObject *Sender);
    void __fastcall chkDirEnabled01Click(TObject *Sender);
    void __fastcall chkDirEnabled02Click(TObject *Sender);
    void __fastcall chkDirEnabled03Click(TObject *Sender);
    void __fastcall chkDirEnabled04Click(TObject *Sender);
    void __fastcall chkDirEnabled05Click(TObject *Sender);
    void __fastcall btnRegisterClick(TObject *Sender);
    void __fastcall mnuCutClick(TObject *Sender);
    void __fastcall mnuCopyClick(TObject *Sender);
    void __fastcall mnuPasteClick(TObject *Sender);
    void __fastcall cmbSchedHourTypeChange(TObject *Sender);
    void __fastcall btnViewLogClick(TObject *Sender);
    void __fastcall pmnuViewLogClick(TObject *Sender);
    
private:	// User declarations
    NOTIFYICONDATA      IconData;
    void __fastcall	    UnfragIconMessage(TMessage& Msg);
    void                AddIcon();

    void __fastcall     WMDrawClipboard(TMessage* Message);
    void __fastcall     WMChangeCBChain(TMessage* Message);
    HWND                hNextHandle;

public:		// User declarations
    __fastcall TfrmConfig(TComponent* Owner);
    void DirBrowse(int Index);
    void DirEnable(int Index);
    void UpdateDirWatch(int Index);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_UNFRAG_ICON_MESSAGE, TMessage, UnfragIconMessage)
        MESSAGE_HANDLER(WM_DRAWCLIPBOARD, TMessage*, WMDrawClipboard)
        MESSAGE_HANDLER(WM_CHANGECBCHAIN, TMessage*, WMChangeCBChain)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
#endif

