//---------------------------------------------------------------------------
#ifndef configureH
#define configureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Clipbrd.hpp>

#include "BmpToJpg.hpp"
#include "RXSpin.hpp"
#include "rxgif.hpp"
#include "pdflib.h"

#include "DMS_PDFWorksImpl.H"
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------

const   NUM_PAPER_SIZE = 12;

const   PDF_PAPER_HEIGHT[NUM_PAPER_SIZE] =
            {
            a0_height       ,
            a1_height       ,
            a2_height       ,
            a3_height       ,
            a4_height       ,
            a5_height       ,
            a6_height       ,
            b5_height       ,
            letter_height   ,
            legal_height    ,
            ledger_height   ,
            p11x17_height
            };

const   PDF_PAPER_WIDTH [NUM_PAPER_SIZE] =
            {
            a0_width        ,
            a1_width        ,
            a2_width        ,
            a3_width        ,
            a4_width        ,
            a5_width        ,
            a6_width        ,
            b5_width        ,
            letter_width    ,
            legal_width     ,
            ledger_width    ,
            p11x17_width
            };

//---------------------------------------------------------------------------
class TfrmConfig : public TForm
{
__published:	// IDE-managed Components
    TButton *btnOK;
    TButton *btnCancel;
    TPageControl *pcConfigure;
    TTabSheet *tsPageSetup;
    TTabSheet *tsImageSetup;
    TCheckBox *chkLandscape;
    TCheckBox *chkCentreOnPage;
    TGroupBox *gboMargins;
    TLabel *lblMarginTop;
    TRxSpinEdit *fedMarginTop;
    TLabel *lblMarginBottom;
    TRxSpinEdit *fedMarginBottom;
    TLabel *lblMarginLeft;
    TRxSpinEdit *fedMarginLeft;
    TLabel *lblMarginRight;
    TRxSpinEdit *fedMarginRight;
    TGroupBox *gboPaperSize;
    TComboBox *ddlPaperSize;
    TLabel *Label8;
    TRxSpinEdit *fedPageHeight;
    TLabel *Label7;
    TRxSpinEdit *fedPageWidth;
    TLabel *lblUnits01;
    TLabel *lblUnits02;
    TLabel *lblUnits03;
    TLabel *lblUnits04;
    TLabel *lblUnits05;
    TLabel *lblUnits06;
    TComboBox *ddlUnits;
    TLabel *Label11;
    TLabel *Label17;
    TTabSheet *tsInformation;
    TLabel *Label1;
    TEdit *edtAuthor;
    TLabel *Label6;
    TEdit *edtCreator;
    TLabel *Label9;
    TEdit *edtTitle;
    TLabel *Label10;
    TEdit *edtSubject;
    TLabel *Label18;
    TEdit *edtKeyWords;
    TRxSpinEdit *fedImageHeight;
    TRxSpinEdit *fedImageWidth;
    TRxSpinEdit *fedJPGQuality;
    TCheckBox *cbStretch;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TRadioGroup *rdogrpScaleGroup;
    TRadioButton *rdoScaleToFit;
    TCheckBox *chkKeepAspect;
    TRadioButton *rdoSpecifyScale;
    TRxSpinEdit *fedScale;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall chkScaleToFitClick(TObject *Sender);
    void __fastcall ddlPaperSizeChange(TObject *Sender);
    void __fastcall ddlUnitsChange(TObject *Sender);
    void __fastcall rdoScaleToFitClick(TObject *Sender);
    void __fastcall rdoSpecifyScaleClick(TObject *Sender);

private:	// User declarations
    // copy of passed in parameters - used for tracking previous state of ddlUnits
    PDF_Setup       m_PDFSetup;

    bool            m_bAmyuni;

public:		// User declarations
    __fastcall TfrmConfig(TComponent* Owner);
    void    SetPDFInfo(PDF_Setup     PDFSetup);
    void    GetPDFInfo(PDF_Setup    *PDFSetup);
    void    SetAmyuni (bool          bAmyuni);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
#endif
