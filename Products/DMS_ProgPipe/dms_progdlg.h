//---------------------------------------------------------------------------

#ifndef ProgDlgH
#define ProgDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmProgDlg : public TForm
{
__published:	// IDE-managed Components
    TProgressBar *pbProgBar;
    TImage *imgIcon;
    TLabel *lblText;
    TLabel *lblPercent;
    TLabel *lblMessage;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmProgDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProgDlg *frmProgDlg;
//---------------------------------------------------------------------------
#endif
