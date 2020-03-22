//---------------------------------------------------------------------------
#ifndef PrintMapH
#define PrintMapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include "FlEdit.hpp"
//---------------------------------------------------------------------------
#define     NUM_PAPER_SIZES     13
#define     SCALE_INCR_DECR     0.1

#ifdef	MAIN
char    *ddlPrinterName[NUM_PAPER_SIZES] =
    {
    "ddlA_Landscape",
    "ddlA_Portrait",
    "ddlB_Landscape",
    "ddlC_Landscape",
    "ddlD_Landscape",
    "ddlE_Landscape",
    "ddlA4_Landscape",
    "ddlA4_Portrait",
    "ddlA3_Landscape",
    "ddlA2_Landscape",
    "ddlA1_Landscape",
    "ddlA0_Landscape",
    "ddlOther",
    };

char    *cboScaleName[NUM_PAPER_SIZES] =
    {
    "cboA_Landscape",
    "cboA_Portrait",
    "cboB_Landscape",
    "cboC_Landscape",
    "cboD_Landscape",
    "cboE_Landscape",
    "cboA4_Landscape",
    "cboA4_Portrait",
    "cboA3_Landscape",
    "cboA2_Landscape",
    "cboA1_Landscape",
    "cboA0_Landscape",
    "cboOther",
    };

char    *fleScaleName[NUM_PAPER_SIZES] =
    {
    "fleA_Landscape",
    "fleA_Portrait",
    "fleB_Landscape",
    "fleC_Landscape",
    "fleD_Landscape",
    "fleE_Landscape",
    "fleA4_Landscape",
    "fleA4_Portrait",
    "fleA3_Landscape",
    "fleA2_Landscape",
    "fleA1_Landscape",
    "fleA0_Landscape",
    "fleOther",
    };

char    *udbScaleName[NUM_PAPER_SIZES] =
    {
    "udbA_Landscape",
    "udbA_Portrait",
    "udbB_Landscape",
    "udbC_Landscape",
    "udbD_Landscape",
    "udbE_Landscape",
    "udbA4_Landscape",
    "udbA4_Portrait",
    "udbA3_Landscape",
    "udbA2_Landscape",
    "udbA1_Landscape",
    "udbA0_Landscape",
    "udbOther",
    };

char    *PaperSizeName[NUM_PAPER_SIZES] =
    {
    "A_Landscape",
    "A_Portrait",
    "B_Landscape",
    "C_Landscape",
    "D_Landscape",
    "E_Landscape",
    "A4_Landscape",
    "A4_Portrait",
    "A3_Landscape",
    "A2_Landscape",
    "A1_Landscape",
    "A0_Landscape",
    "Other",
    };
#else
extern char    *ddlPrinterName  [NUM_PAPER_SIZES];
extern char    *cboScaleName    [NUM_PAPER_SIZES];
extern char    *fleScaleName    [NUM_PAPER_SIZES];
extern char    *udbScaleName    [NUM_PAPER_SIZES];
extern char    *PaperSizeName   [NUM_PAPER_SIZES];
#endif
//---------------------------------------------------------------------------
class TfrmPrintMap : public TForm
{
__published:	// IDE-managed Components
    TComboBox *ddlA_Landscape;
    TComboBox *ddlA_Portrait;
    TComboBox *ddlB_Landscape;
    TComboBox *ddlC_Landscape;
    TComboBox *ddlD_Landscape;
    TComboBox *ddlE_Landscape;
    TComboBox *ddlA4_Landscape;
    TComboBox *ddlA4_Portrait;
    TComboBox *ddlA3_Landscape;
    TComboBox *ddlA2_Landscape;
    TComboBox *ddlA1_Landscape;
    TComboBox *ddlA0_Landscape;
    TComboBox *ddlOther;
    TButton *btnOK;
    TButton *btnCancel;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TCheckBox *cboA_Landscape;
    TCheckBox *cboA_Portrait;
    TCheckBox *cboB_Landscape;
    TCheckBox *cboC_Landscape;
    TCheckBox *cboD_Landscape;
    TCheckBox *cboE_Landscape;
    TCheckBox *cboA4_Landscape;
    TCheckBox *cboA4_Portrait;
    TCheckBox *cboA3_Landscape;
    TCheckBox *cboA2_Landscape;
    TCheckBox *cboA1_Landscape;
    TCheckBox *cboA0_Landscape;
    TCheckBox *cboOther;
    TFloatEdit *fleA_Landscape;
    TCSpinButton *udbA_Landscape;
    TFloatEdit *fleA_Portrait;
    TCSpinButton *udbA_Portrait;
    TFloatEdit *fleB_Landscape;
    TCSpinButton *udbB_Landscape;
    TFloatEdit *fleC_Landscape;
    TCSpinButton *udbC_Landscape;
    TFloatEdit *fleD_Landscape;
    TCSpinButton *udbD_Landscape;
    TFloatEdit *fleE_Landscape;
    TCSpinButton *udbE_Landscape;
    TFloatEdit *fleA4_Landscape;
    TCSpinButton *udbA4_Landscape;
    TFloatEdit *fleA4_Portrait;
    TCSpinButton *udbA4_Portrait;
    TFloatEdit *fleA3_Landscape;
    TCSpinButton *udbA3_Landscape;
    TFloatEdit *fleA2_Landscape;
    TCSpinButton *udbA2_Landscape;
    TFloatEdit *fleA1_Landscape;
    TCSpinButton *udbA1_Landscape;
    TFloatEdit *fleA0_Landscape;
    TCSpinButton *udbA0_Landscape;
    TFloatEdit *fleOther;
    TCSpinButton *udbOther;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall udbA_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA_PortraitDownClick(TObject *Sender);
    void __fastcall udbA_PortraitUpClick(TObject *Sender);
    void __fastcall udbB_LandscapeDownClick(TObject *Sender);
    void __fastcall udbB_LandscapeUpClick(TObject *Sender);
    void __fastcall udbC_LandscapeDownClick(TObject *Sender);
    void __fastcall udbC_LandscapeUpClick(TObject *Sender);
    void __fastcall udbD_LandscapeDownClick(TObject *Sender);
    void __fastcall udbD_LandscapeUpClick(TObject *Sender);
    void __fastcall udbE_LandscapeDownClick(TObject *Sender);
    void __fastcall udbE_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA4_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA4_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA4_PortraitDownClick(TObject *Sender);
    void __fastcall udbA4_PortraitUpClick(TObject *Sender);
    void __fastcall udbA3_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA3_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA2_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA2_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA1_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA1_LandscapeUpClick(TObject *Sender);
    void __fastcall udbA0_LandscapeDownClick(TObject *Sender);
    void __fastcall udbA0_LandscapeUpClick(TObject *Sender);
    void __fastcall udbOtherDownClick(TObject *Sender);
    void __fastcall udbOtherUpClick(TObject *Sender);
    void __fastcall cboA_LandscapeClick(TObject *Sender);
    void __fastcall cboA_PortraitClick(TObject *Sender);
    void __fastcall cboB_LandscapeClick(TObject *Sender);
    void __fastcall cboC_LandscapeClick(TObject *Sender);
    void __fastcall cboD_LandscapeClick(TObject *Sender);
    void __fastcall cboE_LandscapeClick(TObject *Sender);
    void __fastcall cboA4_LandscapeClick(TObject *Sender);
    void __fastcall cboA4_PortraitClick(TObject *Sender);
    void __fastcall cboA3_LandscapeClick(TObject *Sender);
    void __fastcall cboA2_LandscapeClick(TObject *Sender);
    void __fastcall cboA1_LandscapeClick(TObject *Sender);
    void __fastcall cboA0_LandscapeClick(TObject *Sender);
    void __fastcall cboOtherClick(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
    void    IncrementScale      (int  nIndex);
    void    DecrementScale      (int  nIndex);
    void    SetScaleUpDownState (int  nIndex);
    void    LoadRegistrySettings(void);
    void    SaveRegistrySettings(void);

public:		// User declarations
    __fastcall TfrmPrintMap(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrintMap *frmPrintMap;
//---------------------------------------------------------------------------
#endif
