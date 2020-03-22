//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "scrb4.h"
#include "scrb4_values.h"
#include "Regi1632.hpp"
//---------------------------------------------------------------------------
#ifdef    MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
#define     SP_MARQUEE_TEXT1        "SolidPartners - No 1 for SolidWorks addins"
#define     SP_MARQUEE_TEXT2        "      http://www.SolidPartners.com"

#define     ACT_MARQUEE_TEXT1       "Visualized by Actify"
#define     ACT_MARQUEE_TEXT2       "      http://www.Actify.com"
//---------------------------------------------------------------------------
GLOBAL String       g_strVarBanner, g_strVarWebSite,
                    g_strVarName;     // VAR name can be empty - beware

GLOBAL bool         g_bIsSolidPartners;     // true if the SolidPartners screensaver
GLOBAL double       g_Radius;

//---------------------------------------------------------------------------
class TMainForm : public TDataModule
{
__published:	// IDE-managed Components
    TScrControl *ScrControl;
    TScrVSysCorners *Corners;
    TScrVSysPasswordDelay *PasswordDelay;
    TScrVSysMute *Mute;
    TScrVSysDisableActiveConfig *DisableActiveConfig;
    TScrVSysMouseThreshold *MouseThreshold;
    TScrVString *SW_DirName;
    TRegistry1632 *regVar;
    TScrVBoolean *SubDir;
    TScrVInteger *FileChange;
    TScrVInteger *TumbleSpeed;
    void __fastcall MainFormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

