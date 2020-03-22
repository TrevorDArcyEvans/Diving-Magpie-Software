//---------------------------------------------------------------------------
#ifndef previewH
#define previewH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "scrb4.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "XVIEW3DLib_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------

class TPreviewForm : public TScrForm
{
__published:      // IDE-managed Components
    TImage *imgLogoPreview;
    void __fastcall FormShow(TObject *Sender);
private:          // User declarations
public:           // User declarations
        __fastcall TPreviewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPreviewForm *PreviewForm;
//---------------------------------------------------------------------------
#endif


