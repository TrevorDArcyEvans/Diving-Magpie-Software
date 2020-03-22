//---------------------------------------------------------------------------

#ifndef ConfigureH
#define ConfigureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include "Placemnt.hpp"
#include "mwajpeg.hpp"
//---------------------------------------------------------------------------
class TfrmConfigure : public TForm
{
__published:	// IDE-managed Components
    TImage *SWImage;
    TCheckBox *chkSpecifySize;
    TCheckBox *chkProgressive;
    TCSpinEdit *sedWidth;
    TCSpinEdit *sedHeight;
    TButton *btnOK;
    TButton *btnCancel;
    TLabel *Label1;
    TLabel *Label2;
    TFormStorage *FormStorage;
    TFormPlacement *FormPlacement;
    TJPEGFileCompressor *JPEGFileCompressor;
    TCSpinEdit *sedQuality;
    TLabel *Label3;
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chkSpecifySizeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmConfigure(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfigure *frmConfigure;
//---------------------------------------------------------------------------
#endif
