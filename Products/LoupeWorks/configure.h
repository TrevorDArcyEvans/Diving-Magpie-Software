//---------------------------------------------------------------------------

#ifndef configureH
#define configureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include "RXSpin.hpp"
#include "Placemnt.hpp"
//---------------------------------------------------------------------------
class TfrmConfigure : public TForm
{
__published:	// IDE-managed Components
    TRxSpinEdit *sedZoom;
    TLabel *Label1;
    TButton *bnOK;
    TButton *btnCancel;
    TFormStorage *FormStorage;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall bnOKClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmConfigure(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfigure *frmConfigure;
//---------------------------------------------------------------------------
#endif
