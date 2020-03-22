//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <atlbase.h>
#include "bi_ctrls.hpp"
#include "WinRoll.hpp"
#include "Placemnt.hpp"

#include "DMS_Comm_TLB.h"
//---------------------------------------------------------------------------
const String LOUPE_WORKS_TITLE          = "LoupeWorks v1.0";
const String LOUPE_WORKS_TITLE_CODE     = "LoupeWorks v1.x";
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TBI_Loupe *BI_Loupe;
    TWinRoller *WinRoller;
    TFormPlacement *FormPlacement;
    void __fastcall FormCreate(TObject *Sender);

private:	// User declarations
    CComPtr <IDMS_Common>       m_DMS_Comm;

    void __fastcall WndProc(Messages::TMessage &Message);

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

