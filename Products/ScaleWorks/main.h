//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>

#include <atlbase.h>
#include "DMS_Comm_TLB.h"

#include <utilcls.h>
#include "RXSpin.hpp"
#include "Placemnt.hpp"
#include "RxGrdCpt.hpp"
//---------------------------------------------------------------------------
const String    SCALEWORKS_WORKS_TITLE      = "ScaleWorks v1.0";
//---------------------------------------------------------------------------
class TfrmScaleWorks : public TForm
{
__published:	// IDE-managed Components
    TListView *lvSketches;
    TPopupMenu *PopupMenu;
    TMenuItem *Change;
    TButton *btnApply;
    TButton *btnRefresh;
    TLabel *Label2;
    TRxSpinEdit *sedScaleModelX;
    TCheckBox *cboScaleModelEnable;
    TRxSpinEdit *sedScaleModelY;
    TRxSpinEdit *sedScaleModelZ;
    TCheckBox *cboScaleUniform;
    TComboBox *ddlScaleType;
    TLabel *Label1;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TFormPlacement *FormPlacement;
    TMainMenu *MainMenu;
    TMenuItem *mnuFile;
    TMenuItem *mnuExit;
    TMenuItem *N1;
    TMenuItem *mnuApply;
    TMenuItem *mnuRefresh;
    TMenuItem *mnuEdit;
    TMenuItem *mnuChange;
    TMenuItem *mnuHelp;
    TMenuItem *mnuAbout;
    TMenuItem *mnuContents;
    TStatusBar *StatusBar;
    void __fastcall ChangeClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnApplyClick(TObject *Sender);
    void __fastcall lvSketchesSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall btnRefreshClick(TObject *Sender);
    void __fastcall cboScaleModelEnableClick(TObject *Sender);
    void __fastcall cboScaleUniformClick(TObject *Sender);
    void __fastcall mnuExitClick(TObject *Sender);
    void __fastcall mnuContentsClick(TObject *Sender);
    void __fastcall mnuAboutClick(TObject *Sender);
private:	// User declarations
    CComPtr <IDMS_Common>   m_DMS_Comm;

public:		// User declarations
    __fastcall TfrmScaleWorks(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmScaleWorks *frmScaleWorks;
//---------------------------------------------------------------------------
#endif
