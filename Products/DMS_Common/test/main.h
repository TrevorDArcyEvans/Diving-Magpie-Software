//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *btnAbout;
    TButton *btnRegister;
    TCheckBox *cboCommercial;
    TCheckBox *cboIcon;
    TEdit *edtProductName;
    TEdit *edtProductCode;
    TButton *btnMachineID;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *edtMachineID;
    TEdit *edtIniFileName;
    TLabel *Label4;
    void __fastcall btnAboutClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnRegisterClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnMachineIDClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
