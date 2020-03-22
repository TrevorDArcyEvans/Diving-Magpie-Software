//---------------------------------------------------------------------------

#ifndef GetInfoH
#define GetInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RXSlider.hpp"
#include "ToolEdit.hpp"
#include <Mask.hpp>
#include "RxCombos.hpp"
#include "Placemnt.hpp"
//---------------------------------------------------------------------------
class TfrmGetInfo : public TForm
{
__published:	// IDE-managed Components
    TFilenameEdit *fedOriginal;
    TFilenameEdit *fedChanged;
    TRxSlider *sldTransparency;
    TColorComboBox *ccbxColour;
    TButton *btnOK;
    TButton *btnCancel;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TFormStorage *FormStorageSelect;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmGetInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGetInfo *frmGetInfo;
//---------------------------------------------------------------------------
#endif
