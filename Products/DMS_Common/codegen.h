//---------------------------------------------------------------------------
#ifndef CodeGenH
#define CodeGenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Regi1632.hpp"
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
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations

public:		// User declarations
    String      m_sProductName,
                m_sProductCode,
                m_sAuthCode;
    bool        m_bIsRegistered;

    __fastcall TfrmCodeGen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCodeGen *frmCodeGen;
//---------------------------------------------------------------------------
#endif
