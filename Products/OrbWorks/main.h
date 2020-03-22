//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
#include <mmsystem.h>
#include "Regi1632.hpp"
#include "Just1_32.hpp"
#include "async32.hpp"
#include <vcl\ComCtrls.hpp>
#include "cspin.h"
#include "WinRoll.hpp"
//---------------------------------------------------------------------------
#define NUM_BUTTONS			6
#define NUM_AXES			6
//---------------------------------------------------------------------------
#define ORB_WORKS_TITLE		"OrbWorks v2.2"

// title used for software security
// have to update for v3.x releases etc
#define ORB_WORKS_TITLE_CODE    "OrbWorks v2.x"
//---------------------------------------------------------------------------
struct AxisType
	{
    int			OptionNum;
    int			Threshold;
    bool		Enabled;
    bool		OppSense;
    long		Value;
    };

struct ButtonType
	{
    int			OptionNum;
    bool		Enabled;
    bool		Pressed;
    };
//---------------------------------------------------------------------------
#ifdef	MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
#ifdef	MAIN
char    *ddlAxisName[NUM_AXES] =
    {
    "ddlXaxis",
    "ddlYaxis",
    "ddlZaxis",
    "ddlRaxis",
    "ddlUaxis",
    "ddlVaxis",
    };

char    *ddlButtonName[NUM_BUTTONS] =
    {
    "ddlButton1",
    "ddlButton2",
    "ddlButton3",
    "ddlButton4",
    "ddlButton5",
    "ddlButton6",
    };

char    *chkAxisName[NUM_AXES] =
    {
    "chkXaxis",
    "chkYaxis",
    "chkZaxis",
    "chkRaxis",
    "chkUaxis",
    "chkVaxis",
    };

char    *chkAxisSenseName[NUM_AXES] =
    {
    "chkXsense",
    "chkYsense",
    "chkZsense",
    "chkRsense",
    "chkUsense",
    "chkVsense",
    };

char    *chkButtonName[NUM_BUTTONS] =
    {
    "chkButton1",
    "chkButton2",
    "chkButton3",
    "chkButton4",
    "chkButton5",
    "chkButton6",
    };

char    *sedAxisName[NUM_AXES] =
    {
    "sedXaxis",
    "sedYaxis",
    "sedZaxis",
    "sedRaxis",
    "sedUaxis",
    "sedVaxis",
    };

bool				bOrbPresent;
#else
extern char    *chkAxisName		[NUM_AXES	];
extern char    *ddlAxisName		[NUM_AXES	];
extern char    *chkAxisSenseName[NUM_AXES	];
extern char    *chkButtonName	[NUM_BUTTONS];
extern char    *ddlButtonName	[NUM_BUTTONS];
extern char    *sedAxisName		[NUM_AXES	];

extern bool		bOrbPresent;
#endif
//---------------------------------------------------------------------------
GLOBAL volatile bool            bSW_Running;
GLOBAL volatile bool	        bJoystick_Running;
GLOBAL volatile HWND            swWindow;
//---------------------------------------------------------------------------
class TfrmOrb : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblComPort;
	TLabel *lblAutoSave;
	TLabel *lblEnable;
	TLabel *lblNormal;
	TComboBox *ddlXaxis;
	TComboBox *ddlButton1;
	TCheckBox *chkXaxis;
	TCheckBox *chkYaxis;
	TCheckBox *chkZaxis;
	TCheckBox *chkRaxis;
	TCheckBox *chkUaxis;
	TCheckBox *chkVaxis;
	TCheckBox *chkButton1;
	TCheckBox *chkButton2;
	TCheckBox *chkButton3;
	TCheckBox *chkButton4;
	TComboBox *ddlYaxis;
	TComboBox *ddlZaxis;
	TComboBox *ddlRaxis;
	TComboBox *ddlUaxis;
	TComboBox *ddlVaxis;
	TComboBox *ddlButton2;
	TComboBox *ddlButton3;
	TComboBox *ddlButton4;
	TCheckBox *chkAutoSaveInt;
	TCheckBox *chkStartMin;
	TCheckBox *chkButton5;
	TCheckBox *chkButton6;
	TComboBox *ddlButton5;
	TComboBox *ddlButton6;
	TMainMenu *mnuMain;
	TMenuItem *mnuFile;
	TMenuItem *mnuOpen;
	TMenuItem *mnuSave;
	TMenuItem *mnuSaveAs;
	TMenuItem *N3;
	TMenuItem *mnuExit;
	TMenuItem *Help1;
	TMenuItem *mnuContents;
	TMenuItem *N1;
	TMenuItem *mnuAbout;
	TTimer *tmrAutoSave;
	TLabel *lblThreshold;
	TOpenDialog *dlgOpen;
	TSaveDialog *dlgSave;
	TRegistry1632 *regSettings;
	TJustOne32 *JustOne32;
	TComboBox *ddlComPort;
	TComm32 *Comm32;
	TStatusBar *stbOrb;
	TTimer *tmrOrb;
	TLabel *lblPollFreq;
	TCheckBox *chkXsense;
	TLabel *lblSense;
	TCheckBox *chkYsense;
	TCheckBox *chkZsense;
	TCheckBox *chkRsense;
	TCheckBox *chkUsense;
	TCheckBox *chkVsense;
    TCSpinEdit *sedXaxis;
    TCSpinEdit *sedYaxis;
    TCSpinEdit *sedZaxis;
    TCSpinEdit *sedRaxis;
    TCSpinEdit *sedUaxis;
    TCSpinEdit *sedVaxis;
    TCSpinEdit *sedUpdateFreq;
    TCSpinEdit *sedAutoSaveInt;
    TWinRoller *WinRoller;
    TMenuItem *mnuRegister;
    TMenuItem *N2;
    TTimer *tmrSecurity;
    TTimer *tmrRedraw;
    TTimer *tmrWindow;
    TTimer *tmrEnum;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mnuSaveClick(TObject *Sender);
	
	void __fastcall mnuContentsClick(TObject *Sender);
	void __fastcall mnuAboutClick(TObject *Sender);
	void __fastcall mnuExitClick(TObject *Sender);
	void __fastcall chkXaxisClick(TObject *Sender);
	void __fastcall chkYaxisClick(TObject *Sender);
	void __fastcall chkZaxisClick(TObject *Sender);
	void __fastcall chkRaxisClick(TObject *Sender);
	void __fastcall chkUaxisClick(TObject *Sender);
	void __fastcall chkVaxisClick(TObject *Sender);
	void __fastcall chkButton1Click(TObject *Sender);
	void __fastcall chkButton2Click(TObject *Sender);
	void __fastcall chkButton3Click(TObject *Sender);
	void __fastcall chkButton4Click(TObject *Sender);
	void __fastcall chkButton5Click(TObject *Sender);
	void __fastcall chkButton6Click(TObject *Sender);
	void __fastcall ddlXaxisChange(TObject *Sender);
	void __fastcall ddlYaxisChange(TObject *Sender);
	void __fastcall ddlZaxisChange(TObject *Sender);
	void __fastcall ddlRaxisChange(TObject *Sender);
	void __fastcall ddlUaxisChange(TObject *Sender);
	void __fastcall ddlVaxisChange(TObject *Sender);
	
	

	
	
	
	void __fastcall ddlButton1Change(TObject *Sender);
	void __fastcall ddlButton2Change(TObject *Sender);
	void __fastcall ddlButton3Change(TObject *Sender);
	void __fastcall ddlButton4Change(TObject *Sender);
	void __fastcall ddlButton5Change(TObject *Sender);
	void __fastcall ddlButton6Change(TObject *Sender);
	void __fastcall sedXaxisChange(TObject *Sender);
	void __fastcall sedYaxisChange(TObject *Sender);
	void __fastcall sedZaxisChange(TObject *Sender);
	void __fastcall sedRaxisChange(TObject *Sender);
	void __fastcall sedUaxisChange(TObject *Sender);
	void __fastcall sedVaxisChange(TObject *Sender);
	void __fastcall mnuOpenClick(TObject *Sender);
	void __fastcall mnuSaveAsClick(TObject *Sender);
	void __fastcall Comm32RxCharSignal(TObject *Sender, int Count);
	void __fastcall ddlComPortChange(TObject *Sender);
	void __fastcall chkAutoSaveIntClick(TObject *Sender);

	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall sedUpdateFreqChange(TObject *Sender);
	void __fastcall tmrOrbTimer(TObject *Sender);
	void __fastcall chkXsenseClick(TObject *Sender);
	void __fastcall chkYsenseClick(TObject *Sender);
	void __fastcall chkZsenseClick(TObject *Sender);
	void __fastcall chkRsenseClick(TObject *Sender);
	void __fastcall chkUsenseClick(TObject *Sender);
	void __fastcall chkVsenseClick(TObject *Sender);
    void __fastcall mnuRegisterClick(TObject *Sender);
    void __fastcall tmrSecurityTimer(TObject *Sender);
    void __fastcall tmrRedrawTimer(TObject *Sender);
    void __fastcall tmrWindowTimer(TObject *Sender);
    void __fastcall tmrEnumTimer(TObject *Sender);
private:	// User declarations
    JOYCAPS         	jcJoyCaps;
    JOYINFOEX 			pjiJoyInfo;

    bool	            bDoingGraphics, bGraphicsRedrawReq;

    struct ButtonType	Button[NUM_BUTTONS	];
    struct AxisType		Axis  [NUM_AXES		];

    void	swOleProcedure(
    		int             	SW_OleType 		,
			const String& 		SW_OleProcName	,
    		int             	SW_OleNumParam	,
            int					SW_OleParam1	);

	void	CalculateOrb(
				JOYINFOEX 			&pji_ex	,
    			JOYCAPS         	&pjc_jc	,
    			struct ButtonType	*Button	,
                struct AxisType		*Axis	);

	void	ProcessOrb(
				JOYINFOEX 			&pji_ex	,
    			JOYCAPS         	&pjc_jc	,
    			struct ButtonType	*Button	,
                struct AxisType		*Axis	);

	bool	ReadSettings(
				AnsiString			IniFileName);

	void	InitInterface(void);

public:		// User declarations
	__fastcall TfrmOrb(TComponent* Owner);

	Variant 			swApp, swModelDoc, swModelView, swPart, swAssy;
    long                swDateCode;
};
//---------------------------------------------------------------------------
extern TfrmOrb *frmOrb;
//---------------------------------------------------------------------------
#endif
