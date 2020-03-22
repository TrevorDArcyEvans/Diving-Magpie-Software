//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#if 0
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
#include <mmsystem.h>

//#include <utilcls.h>

#include "Regi1632.hpp"
#include "Just1_32.hpp"
#include "cspin.h"
#include "WinRoll.hpp"
#include <Buttons.hpp>
#include "CSPIN.h"
#include <Graphics.hpp>
//#include <rw/stdmutex.h>
#endif

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>

#include <utilcls.h>

#include <Comobj.hpp>
#include <vcl\Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <Regi1632.hpp>
#include <memory>     //for STL auto_ptr
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <except.h> //for xmsg
#include <cstring.h>

#include <mmsystem.h>

#include <process.h>
#include <dos.h>

#include "Regi1632.hpp"
#include "Just1_32.hpp"
#include "cspin.h"
#include "WinRoll.hpp"
#include <Buttons.hpp>
#include "CSPIN.h"

//---------------------------------------------------------------------------
#define NUM_BUTTONS			    6
#define NUM_AXES			    6
#define NUM_POV 			    4
//---------------------------------------------------------------------------
#define STK_WORKS_TITLE		    "StickWorks v2.1"

// title used for software security
// have to update for v3.x releases etc
#define STK_WORKS_TITLE_CODE    "StickWorks v2.x"
//---------------------------------------------------------------------------
struct AxisType
	{
    int			OptionNum;
    int			ModOptionNum;
    int			Threshold;
    bool		Enabled;
    bool		OppSense;
    float		Value;
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

char    *ddlModAxisName[NUM_AXES] =
    {
    "ddlXmodaxis",
    "ddlYmodaxis",
    "ddlZmodaxis",
    "ddlRmodaxis",
    "ddlUmodaxis",
    "ddlVmodaxis",
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

char    *ddlPOVName[NUM_POV] =
    {
    "ddlPOVfront",
    "ddlPOVback",
    "ddlPOVleft",
    "ddlPOVright",
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

char    *chkPOVName[NUM_POV] =
    {
    "chkPOVfront",
    "chkPOVback",
    "chkPOVleft",
    "chkPOVright",
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
#else
extern char    *ddlAxisName		[NUM_AXES	];
extern char    *ddlModAxisName	[NUM_AXES	];
extern char    *ddlButtonName	[NUM_BUTTONS];
extern char    *ddlPOVName	    [NUM_POV    ];
extern char    *chkAxisName		[NUM_AXES	];
extern char    *chkAxisSenseName[NUM_AXES	];
extern char    *chkButtonName	[NUM_BUTTONS];
extern char    *chkPOVName	    [NUM_POV    ];
extern char    *sedAxisName		[NUM_AXES	];
#endif
//---------------------------------------------------------------------------
GLOBAL volatile bool            bSW_Running;
GLOBAL volatile bool	        bJoystick_Running;
GLOBAL volatile HWND            swWindow;
//---------------------------------------------------------------------------
class TfrmJoystick : public TForm
{
__published:	// IDE-managed Components
	TTimer *tmrJoystick;
	TStatusBar *stbJoystick;
	TMainMenu *mnuMain;
	TMenuItem *mnuFile;
	TMenuItem *mnuExit;
	TMenuItem *Help1;
	TMenuItem *mnuAbout;
	TLabel *lblPollFreq;
	TComboBox *ddlXaxis;
	TComboBox *ddlButton1;
	TLabel *lblThreshold;
	TLabel *lblAutoSave;
	TCheckBox *chkXaxis;
	TLabel *lblEnable;
	TComboBox *ddlXmodaxis;
	TCheckBox *chkYaxis;
	TCheckBox *chkZaxis;
	TCheckBox *chkRaxis;
	TCheckBox *chkUaxis;
	TCheckBox *chkVaxis;
	TCheckBox *chkButton1;
	TCheckBox *chkButton2;
	TCheckBox *chkButton3;
	TCheckBox *chkButton4;
	TLabel *lblNormal;
	TLabel *lblNormalMod;
	TComboBox *ddlYaxis;
	TComboBox *ddlYmodaxis;
	TComboBox *ddlZaxis;
	TComboBox *ddlZmodaxis;
	TComboBox *ddlRaxis;
	TComboBox *ddlRmodaxis;
	TComboBox *ddlUaxis;
	TComboBox *ddlUmodaxis;
	TComboBox *ddlVaxis;
	TComboBox *ddlVmodaxis;
	TComboBox *ddlButton2;
	TComboBox *ddlButton3;
	TComboBox *ddlButton4;
	TTimer *tmrAutoSave;
	TCheckBox *chkAutoSaveInt;
	TMenuItem *mnuOpen;
	TMenuItem *mnuSave;
	TMenuItem *mnuSaveAs;
	TMenuItem *N3;
	TSaveDialog *dlgSave;
	TOpenDialog *dlgOpen;
	TButton *btnCalibrate;
	TRegistry1632 *regSettings;
	TMenuItem *mnuContents;
	TMenuItem *N1;
	TCheckBox *chkStartMin;
	TCheckBox *chkButton5;
	TCheckBox *chkButton6;
	TComboBox *ddlButton5;
	TComboBox *ddlButton6;
	TJustOne32 *JustOne32;
	TLabel *lblSense;
	TCheckBox *chkXsense;
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
    TCSpinEdit *sedPollFreq;
    TCSpinEdit *sedAutoSaveInt;
    TWinRoller *WinRoller;
    TComboBox *ddlPOVfront;
    TComboBox *ddlPOVback;
    TComboBox *ddlPOVleft;
    TComboBox *ddlPOVright;
    TCheckBox *chkPOVfront;
    TCheckBox *chkPOVback;
    TCheckBox *chkPOVleft;
    TCheckBox *chkPOVright;
    TTimer *tmrRedraw;
    TMenuItem *mnuRegister;
    TTimer *tmrSecurity;
    TTimer *tmrWindow;
    TTimer *tmrEnum;
    TImage *imgPOVfront;
    TImage *imgPOVleft;
    TImage *imgPOVback;
    TImage *imgPOVright;
	void __fastcall tmrJoystickTimer(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mnuAboutClick(TObject *Sender);
	void __fastcall mnuExitClick(TObject *Sender);
	void __fastcall sedPollFreqChange(TObject *Sender);

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
	void __fastcall chkAutoSaveIntClick(TObject *Sender);
	void __fastcall ddlXaxisChange(TObject *Sender);
	void __fastcall ddlYaxisChange(TObject *Sender);
	void __fastcall ddlZaxisChange(TObject *Sender);
	void __fastcall ddlRaxisChange(TObject *Sender);
	void __fastcall ddlUaxisChange(TObject *Sender);
	void __fastcall ddlVaxisChange(TObject *Sender);
	void __fastcall ddlXmodaxisChange(TObject *Sender);
	void __fastcall ddlYmodaxisChange(TObject *Sender);
	void __fastcall ddlZmodaxisChange(TObject *Sender);
	void __fastcall ddlRmodaxisChange(TObject *Sender);
	void __fastcall ddlUmodaxisChange(TObject *Sender);
	void __fastcall ddlVmodaxisChange(TObject *Sender);
	void __fastcall ddlButton1Change(TObject *Sender);
	void __fastcall ddlButton2Change(TObject *Sender);
	void __fastcall ddlButton3Change(TObject *Sender);
	void __fastcall ddlButton4Change(TObject *Sender);
	void __fastcall sedXaxisChange(TObject *Sender);
	void __fastcall sedYaxisChange(TObject *Sender);
	void __fastcall sedZaxisChange(TObject *Sender);
	void __fastcall sedRaxisChange(TObject *Sender);
	void __fastcall sedUaxisChange(TObject *Sender);
	void __fastcall sedVaxisChange(TObject *Sender);
	void __fastcall sedAutoSaveIntChange(TObject *Sender);
	void __fastcall mnuOpenClick(TObject *Sender);
	void __fastcall mnuSaveAsClick(TObject *Sender);

	void __fastcall tmrAutoSaveTimer(TObject *Sender);
	void __fastcall btnCalibrateClick(TObject *Sender);
	
	void __fastcall mnuSaveClick(TObject *Sender);
	void __fastcall mnuContentsClick(TObject *Sender);
	
	void __fastcall chkXsenseClick(TObject *Sender);
	void __fastcall chkYsenseClick(TObject *Sender);
	void __fastcall chkZsenseClick(TObject *Sender);
	void __fastcall chkRsenseClick(TObject *Sender);
	void __fastcall chkUsenseClick(TObject *Sender);
	void __fastcall chkVsenseClick(TObject *Sender);

    void __fastcall chkPOVfrontClick(TObject *Sender);
    void __fastcall chkPOVbackClick(TObject *Sender);
    void __fastcall chkPOVleftClick(TObject *Sender);
    void __fastcall chkPOVrightClick(TObject *Sender);
    void __fastcall ddlPOVfrontChange(TObject *Sender);
    void __fastcall ddlPOVbackChange(TObject *Sender);
    void __fastcall ddlPOVleftChange(TObject *Sender);
    void __fastcall ddlPOVrightChange(TObject *Sender);
    void __fastcall tmrRedrawTimer(TObject *Sender);
    
    void __fastcall mnuRegisterClick(TObject *Sender);
    void __fastcall tmrSecurityTimer(TObject *Sender);
    
    void __fastcall tmrWindowTimer(TObject *Sender);
    void __fastcall tmrEnumTimer(TObject *Sender);
private:	// User declarations
    JOYCAPS         	jcJoyCaps;
    JOYINFOEX 			pjiJoyInfo;

    bool	            bDoingGraphics, bGraphicsRedrawReq;

    struct ButtonType	Button[NUM_BUTTONS	];
    struct ButtonType	POV   [NUM_POV	    ];
    struct AxisType		Axis  [NUM_AXES		];

    void	swOleProcedure(
        		int             	SW_OleType 		,
	    		const String& 		SW_OleProcName	,
    	    	int             	SW_OleNumParam	,
                int					SW_OleParam1	,
                float               Value           );

	void	CalculateJoystick(
				JOYINFOEX 			&pji_ex	,
    			JOYCAPS         	&pjc_jc	,
    			struct ButtonType	*Button	,
                struct AxisType		*Axis	);

	void	ProcessJoystick(
				JOYINFOEX 			&pji_ex	,
    			JOYCAPS         	&pjc_jc	,
    			struct ButtonType	*Button	,
                struct AxisType		*Axis	);

	bool	ReadSettings(
				AnsiString			IniFileName);

	void	InitInterface(void);

public:		// User declarations
	__fastcall TfrmJoystick(TComponent* Owner);

	Variant 			swApp, swModelDoc, swModelView, swPart, swAssy;
    long                swDateCode;
};
//---------------------------------------------------------------------------
extern TfrmJoystick *frmJoystick;
//---------------------------------------------------------------------------
#endif

