//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WinRoll.hpp"
#include <OleCtrls.hpp>
#include <Menus.hpp>
#include "Regi1632.hpp"
#include <ComCtrls.hpp>
#include <Comobj.hpp>
#include <utilcls.h>
#include "VspelocxLib_OCX.h"
//---------------------------------------------------------------------------
#ifdef	MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
#define SPELL_WORKS_TITLE		    "SpellWorks v1.0"

// title used for software security
// have to update for v3.x releases etc
#define SPELL_WORKS_TITLE_CODE    "SpellWorks v1.x"
//---------------------------------------------------------------------------
GLOBAL volatile bool            g_bSW_Running;
GLOBAL          bool            g_bRegistered;
GLOBAL          int             g_nNumSpell;
//---------------------------------------------------------------------------
#define CATCH_OLE_ERROR     \
    catch(EOleException& e)                         \
	    {                                           \
        frmMain->stbSpell->SimpleText =             \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
	    }                                           \
                                                    \
    catch(EOleSysError& e)                          \
	    {                                           \
        frmMain->stbSpell->SimpleText =             \
            "OLE Error:  " + e.Message              \
            + "(" + e.ErrorCode + ")";              \
  	    }                                           \
                                                    \
    catch(EOleError& e)                             \
	    {                                           \
        frmMain->stbSpell->SimpleText =             \
            "OLE Error:  " + e.Message;             \
        }                                           \
                                                    \
    catch(...)                                      \
	    {                                           \
        frmMain->stbSpell->SimpleText =             \
            "OLE Error:  unknown error";            \
        }
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TWinRoller *WinRoll;
    TMemo *memText;
    TButton *btnUpdate;
    TButton *btnCheck;
    TPopupMenu *pnmuMenu;
    TMenuItem *mnuHelp;
    TMenuItem *N1;
    TMenuItem *mnuRegister;
    TMenuItem *mnuAbout;
    TMenuItem *mnuOnTop;
    TMenuItem *N2;
    TButton *btnImport;
    TRegistry1632 *regSpell;
    TStatusBar *stbSpell;
    TVSSpell *splSpell;
    TButton *btnAbout;
    TMainMenu *mnuMain;
    TMenuItem *File1;
    TMenuItem *mnu_Exit;
    TMenuItem *N3;
    TMenuItem *mnu_Check;
    TMenuItem *mnu_Import;
    TMenuItem *mnu_Update;
    TMenuItem *Help1;
    TMenuItem *About1;
    TMenuItem *mnu_Register;
    TMenuItem *Help2;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *mnu_OnTop;
    void __fastcall mnuOnTopClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnCheckClick(TObject *Sender);
    void __fastcall mnuRegisterClick(TObject *Sender);
    void __fastcall mnuAboutClick(TObject *Sender);
    void __fastcall mnuHelpClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall WinRollRoller(TObject *Sender, TRollerMode mode);
    void __fastcall btnUpdateClick(TObject *Sender);
    void __fastcall btnImportClick(TObject *Sender);
    void __fastcall btnAboutClick(TObject *Sender);
    void __fastcall mnu_ExitClick(TObject *Sender);
private:	// User declarations
    void    GetSWText();

public:		// User declarations
    __fastcall          TfrmMain(TComponent* Owner);
	Variant 			swApp, swModelDoc, swSelMgr, swNote;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
