//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
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
#include "CSPIN.h"
#include "WinRoll.hpp"
#include <Graphics.hpp>
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
struct AxisType
	{
    int			OptionNum;
    int			ModOptionNum;
    int			Threshold;
    bool		Enabled;
    bool		OppSense;
    float		Value;
    int			Sensitivity;
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

char    *sedAxisSensName[NUM_AXES] =
    {
    "sedXsens",
    "sedYsens",
    "sedZsens",
    "sedRsens",
    "sedUsens",
    "sedVsens",
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
extern char    *sedAxisSensName [NUM_AXES   ];
#endif
//---------------------------------------------------------------------------
class TfrmJoystick : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *stbJoystick;
	TRegistry1632 *regSettings;
    TPageControl *pcJoystick;
    TTabSheet *tsAxes;
    TTabSheet *tsButtons;
    TTabSheet *tsPOV;
    TLabel *lblThreshold;
    TLabel *lblEnable;
    TLabel *lblNormal;
    TLabel *lblNormalMod;
    TComboBox *ddlXaxis;
    TCheckBox *chkXaxis;
    TComboBox *ddlXmodaxis;
    TCheckBox *chkYaxis;
    TCheckBox *chkZaxis;
    TCheckBox *chkRaxis;
    TCheckBox *chkUaxis;
    TCheckBox *chkVaxis;
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
    TComboBox *ddlButton1;
    TCheckBox *chkButton1;
    TCheckBox *chkButton2;
    TCheckBox *chkButton3;
    TCheckBox *chkButton4;
    TComboBox *ddlButton2;
    TComboBox *ddlButton3;
    TComboBox *ddlButton4;
    TCheckBox *chkButton5;
    TCheckBox *chkButton6;
    TComboBox *ddlButton5;
    TComboBox *ddlButton6;
    TImage *imgPOVfront;
    TImage *imgPOVleft;
    TImage *imgPOVback;
    TImage *imgPOVright;
    TComboBox *ddlPOVfront;
    TComboBox *ddlPOVback;
    TComboBox *ddlPOVleft;
    TComboBox *ddlPOVright;
    TCheckBox *chkPOVfront;
    TCheckBox *chkPOVback;
    TCheckBox *chkPOVleft;
    TCheckBox *chkPOVright;
    TTabSheet *tsMisc;
    TLabel *lblPollFreq;
    TButton *btnCalibrate;
    TCSpinEdit *sedPollFreq;
    TLabel *lblSense;
    TLabel *Label1;
    TCSpinEdit *sedXSens;
    TCSpinEdit *sedYSens;
    TCSpinEdit *sedZSens;
    TCSpinEdit *sedRSens;
    TCSpinEdit *sedUSens;
    TCSpinEdit *sedVSens;
    TButton *btnOK;
    TButton *btnCancel;
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
	void __fastcall btnCalibrateClick(TObject *Sender);
	
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
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chkButton5Click(TObject *Sender);
    void __fastcall chkButton6Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ddlButton5Change(TObject *Sender);
    void __fastcall ddlButton6Change(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall sedXSensChange(TObject *Sender);
    void __fastcall sedYSensChange(TObject *Sender);
    void __fastcall sedZSensChange(TObject *Sender);
    void __fastcall sedRSensChange(TObject *Sender);
    void __fastcall sedUSensChange(TObject *Sender);
    void __fastcall sedVSensChange(TObject *Sender);
private:	// User declarations
    JOYCAPS         	jcJoyCaps;
    JOYINFOEX 			pjiJoyInfo;
    bool                bDirty;

    struct ButtonType	Button[NUM_BUTTONS	];
    struct ButtonType	POV   [NUM_POV	    ];
    struct AxisType		Axis  [NUM_AXES		];

	bool	ReadSettings (void);
	void	InitInterface(void);

	void	CheckAxisClick      (int  nIndex);
    void    CheckSenseClick     (int  nIndex);
	void	CheckButtonClick    (int  nIndex);
	void	DDLAxisChange       (int  nIndex);
	void	DDLModAxisChange    (int  nIndex);
	void	DDLButtonChange     (int  nIndex);
	void	SEDAxisChange       (int  nIndex);
    void    CheckPOVClick       (int  nIndex);
	void	DDLPOVChange        (int  nIndex);
    void    SEDAxisSensChange   (int  nIndex);

public:		// User declarations
	__fastcall TfrmJoystick(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmJoystick *frmJoystick;
//---------------------------------------------------------------------------
#endif

