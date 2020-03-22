//---------------------------------------------------------------------------

#ifndef configureH
#define configureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include "Placemnt.hpp"
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TfrmConfigure : public TForm
{
__published:	// IDE-managed Components
    TCheckBox *chkBoundBox;
    TCheckBox *chkDateTime;
    TCheckBox *chkFileSize;
    TCheckBox *chkFileName;
    TCheckBox *chkCentreOfMass;
    TCheckBox *chkVolume;
    TCheckBox *chkArea;
    TCheckBox *chkMass;
    TCheckBox *chkMassMoment;
    TCheckBox *chkBitmap;
    TRadioButton *rdoIncDirectory;
    TRadioButton *rdoFileNameOnly;
    TCheckBox *chkMassProps;
    TButton *btnCancel;
    TButton *btnOK;
    TFormStorage *FormStorage;
    TFilenameEdit *fedXSL_FileName;
    TLabel *Label2;
    TCheckBox *chkFileInfo;
    TCheckBox *chkSummInfo;
    TCheckBox *chkCustomProps;
    TCheckBox *chkBitmapSize;
    TCSpinEdit *sedHeight;
    TCSpinEdit *sedWidth;
    TLabel *Label1;
    TLabel *Label3;
    void __fastcall chkFileInfoClick(TObject *Sender);
    void __fastcall chkMassPropsClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall chkFileNameClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall chkBitmapClick(TObject *Sender);
    void __fastcall chkBitmapSizeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmConfigure(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfigure *frmConfigure;
//---------------------------------------------------------------------------
#endif
