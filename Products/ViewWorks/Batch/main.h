//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "Regi1632.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "Dropper.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#ifdef    MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
#define VIEW_WORKS_TITLE                "ViewWorks v1.0"

// title used for software security
// have to update for v3.x releases etc
#define VIEW_WORKS_TITLE_CODE           "ViewWorks v1.x"
//---------------------------------------------------------------------------
#define VW_LOG_ERROR(ErrorMessage)   \
                stbViewWorks->SimpleText = ErrorMessage;
//---------------------------------------------------------------------------
class TfrmViewWorks : public TForm
{
__published:	// IDE-managed Components
    TBevel *Bevel1;
    TSpeedButton *sbtnExit;
    TSpeedButton *sbtnOpen;
    TSpeedButton *sbtnSave;
    TSpeedButton *sbtnRemove;
    TSpeedButton *sbtnAdd;
    TListBox *lbxList;
    TButton *btnAdd;
    TButton *btnRemove;
    TOpenDialog *dlgOpenFileName;
    TOpenDialog *dlgOpen;
    TRegistry1632 *regSettings;
    TSaveDialog *dlgSaveFileName;
    TMainMenu *mnuMain;
    TMenuItem *mnuFile;
    TMenuItem *mnuOpen;
    TMenuItem *mnuSave;
    TMenuItem *mnuSaveAs;
    TMenuItem *N4;
    TMenuItem *mnuExit;
    TMenuItem *mnuHelp;
    TMenuItem *mnuRegister;
    TMenuItem *N3;
    TMenuItem *mnuContents;
    TMenuItem *mnuAbout;
    TButton *btnConvert;
    TFileDropper *FileDropper;
    TStatusBar *stbViewWorks;
    TMenuItem *Add1;
    TMenuItem *mnuRemove;
    TMenuItem *mnuConvert;
    TMenuItem *N1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnRemoveClick(TObject *Sender);
    void __fastcall mnuExitClick(TObject *Sender);
    void __fastcall mnuOpenClick(TObject *Sender);
    void __fastcall mnuSaveClick(TObject *Sender);
    void __fastcall mnuSaveAsClick(TObject *Sender);
    void __fastcall mnuRegisterClick(TObject *Sender);
    void __fastcall mnuContentsClick(TObject *Sender);
    void __fastcall mnuAboutClick(TObject *Sender);
    void __fastcall FileDropperDrop(TObject *Sender, AnsiString Filename);
    void __fastcall btnConvertClick(TObject *Sender);
    void __fastcall lbxListKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);

private:	// User declarations
    AnsiString          CurrFileName;
    void __fastcall     VW_MakeViewFile(
                            char     *pcSWFileName);
    int __fastcall      VW_UnfragFile(
                            int     nTimeOut,
                            char    *pcFileName);


public:		// User declarations
    __fastcall TfrmViewWorks(TComponent* Owner);
    bool                bRegistered;
//---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmViewWorks *frmViewWorks;
//---------------------------------------------------------------------------
#endif
