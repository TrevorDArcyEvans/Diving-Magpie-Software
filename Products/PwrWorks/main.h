//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *btnRead;
    TButton *btnWrite;
    TCheckBox *chkEnableMCD;
    TCheckBox *chkEnableDwgChanges;
    TCheckBox *chkEnableEmail;
    TMainMenu *mnuMain;
    TMenuItem *File1;
    TMenuItem *mnuExit;
    TMenuItem *Help1;
    TMenuItem *mnuAbout;
    TMenuItem *mnuContents;
    TCheckBox *chkTips;
    TComboBox *ddlApps;
    TButton *btnRemove;
    void __fastcall mnuExitClick(TObject *Sender);
    void __fastcall mnuAboutClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall mnuContentsClick(TObject *Sender);
    void __fastcall btnReadClick(TObject *Sender);
    void __fastcall btnWriteClick(TObject *Sender);
    
    void __fastcall btnRemoveClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
