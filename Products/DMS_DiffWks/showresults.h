//---------------------------------------------------------------------------

#ifndef ShowResultsH
#define ShowResultsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Placemnt.hpp"
//---------------------------------------------------------------------------
class TfrmShowResults : public TForm
{
__published:	// IDE-managed Components
    TMemo *memResults;
    TButton *btnOK;
    TFormStorage *FormStorageResults;
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmShowResults(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmShowResults *frmShowResults;
//---------------------------------------------------------------------------
#endif
