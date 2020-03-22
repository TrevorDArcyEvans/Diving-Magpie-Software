//---------------------------------------------------------------------------
#ifndef CodeGenH
#define CodeGenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmCodeGen : public TForm
{
__published:	// IDE-managed Components
    TEdit *edtMachineID;
    TEdit *edtCode;
    TButton *btnRegister;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall btnRegisterClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmCodeGen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCodeGen *frmCodeGen;
//---------------------------------------------------------------------------
#endif
