//---------------------------------------------------------------------------
#ifndef errorsH
#define errorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmError : public TForm
{
__published:	// IDE-managed Components
    TMemo *memError;
    TButton *btnOK;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmError(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmError *frmError;
//---------------------------------------------------------------------------
#endif
