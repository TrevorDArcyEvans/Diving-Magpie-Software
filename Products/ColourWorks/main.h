//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"

#include <utilcls.h>
#include "Placemnt.hpp"

#include <assert.h>
#include <set>

#include <atlbase.h>
#include "DMS_Comm_TLB.h"
//---------------------------------------------------------------------------
const String    COLORWORKS_WORKS_TITLE      = "ColorWorks v1.0";
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *btnApply;
    TCSpinEdit *sedTolerance;
    TLabel *Label1;
    TFormStorage *FormStorage;
    void __fastcall btnApplyClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);

private:	// User declarations
    CComPtr <IDMS_Common>       m_DMS_Comm;
    std::set <COLORREF>         m_Colours;

    double rand(double num);

    bool IsTooClose
    (
        double          Red_1,
        double          Green_1,
        double          Blue_1,
        double          Red_2,
        double          Green_2,
        double          Blue_2,
        double          Tolerance
    );

    bool IsNotClose
    (
        double          Red_1,
        double          Green_1,
        double          Blue_1,
        double          Red_2,
        double          Green_2,
        double          Blue_2,
        double          Tolerance
    );

    bool GetNewColour
    (
        std::set <COLORREF>         ColourSet,
        double&                     NewRed,
        double&                     NewGreen,
        double&                     NewBlue,
        double                      Tolerance,
        double                      MaxColourValue,
        int                         Attempts
    );

    void GetSolidWorksColorTable(std::set <COLORREF>& ColourSet);
    bool ChangePartColor(
        Variant                     PartDoc     ,
        std::set <COLORREF>&        ColourSet   ,
        double                      Tolerance   );

    void TraverseComponent(
        int                         level       ,
        Variant                     Component   ,
        std::set <COLORREF>&        ColourSet   ,
        double                      Tolerance   );

    void __fastcall WndProc(Messages::TMessage &Message);


public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

