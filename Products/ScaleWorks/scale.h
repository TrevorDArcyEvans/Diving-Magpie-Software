//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RXSpin.hpp"
//---------------------------------------------------------------------------
class TfrmScale : public TForm
{
__published:	// IDE-managed Components
    TRxSpinEdit *sedScale;
    TButton *btnOK;
    TButton *btnCancel;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmScale(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmScale *frmScale;
//---------------------------------------------------------------------------
#endif
