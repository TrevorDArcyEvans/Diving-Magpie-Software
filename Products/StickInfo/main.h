//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <mmsystem.h>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TMemo *memJoystick;
    TButton *btnCheck;
    TLabel *lblHASZ;
    TLabel *lblHASR;
    TLabel *lblHASU;
    TLabel *lblHASV;
    TLabel *lblHASPOV;
    TLabel *lblHASPOV4DIR;
    TLabel *lblHASPOVCTS;
    TButton *btnReset;
    TButton *btnEmail;
    TMemo *memComments;
    TButton *btnWeb;
    void __fastcall btnCheckClick(TObject *Sender);
    void __fastcall btnResetClick(TObject *Sender);
    void __fastcall btnEmailClick(TObject *Sender);
    void __fastcall btnWebClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
