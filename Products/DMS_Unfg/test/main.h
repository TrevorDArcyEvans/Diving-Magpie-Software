//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "DMS_Unfg_TLB.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TEdit *edtFileName;
    TButton *btnBrowse;
    TButton *btnUnfrag;
    TButton *btnPreview;
    TButton *btnGeometry;
    TOpenDialog *OpenDialog;
    TEdit *edtCode;
    TButton *btnCode;
    void __fastcall btnBrowseClick(TObject *Sender);
    void __fastcall btnCodeClick(TObject *Sender);
    void __fastcall btnUnfragClick(TObject *Sender);
    void __fastcall btnPreviewClick(TObject *Sender);
    void __fastcall btnGeometryClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
    TCOMIDMS_Unfrag     DMS_Unfrag;

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
