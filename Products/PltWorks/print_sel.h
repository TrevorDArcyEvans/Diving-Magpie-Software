//---------------------------------------------------------------------------
#ifndef print_selH
#define print_selH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmPrinters : public TForm
{
__published:	// IDE-managed Components
    TComboBox *ddlPrinters;
    TButton *btnOK;
    TButton *btnCancel;
    TLabel *Label1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmPrinters(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrinters *frmPrinters;
//---------------------------------------------------------------------------
#endif
