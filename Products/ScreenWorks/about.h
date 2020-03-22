//---------------------------------------------------------------------------
#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "scrb4.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------

class TAboutForm : public TScrDialog
{
__published:      // IDE-managed Components
    TLabel *lblWebSolidPartners;
    TImage *imgLogoScreenWorks;
    TLabel *Label2;
    TLabel *Label3;
    TImage *imgLogoSolidPartners;
    TLabel *lblBannerSolidPartners;
    TButton *btnOk;
    TLabel *lblBannerVar;
    TImage *imgLogoVar;
    TLabel *lblWebVar;
    TImage *imgLogoActify;
    TLabel *lblBannerActify;
    TLabel *lblWebActify;
        void __fastcall lblWebSolidPartnersClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:          // User declarations
public:           // User declarations
        __fastcall TAboutForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutForm *AboutForm;
//---------------------------------------------------------------------------
#endif


