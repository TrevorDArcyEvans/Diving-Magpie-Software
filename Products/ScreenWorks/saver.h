//---------------------------------------------------------------------------
#ifndef saverH
#define saverH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "scrb4.h"
#include <ExtCtrls.hpp>
#include "XVIEW3DLib_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TSaverForm : public TScrForm
{
__published:      // IDE-managed Components
    TXView *actXView;
    TTimer *tmrSaver;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall tmrSaverTimer(TObject *Sender);
private:          // User declarations
    TStringList     *g_strsFileList;

    void __fastcall LoadSWFile(String   strFileName);
    void __fastcall ProcessDirectory(bool bDoSubfolders, String strFileSpec);

public:           // User declarations
        __fastcall TSaverForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSaverForm *SaverForm;
//---------------------------------------------------------------------------
#endif


