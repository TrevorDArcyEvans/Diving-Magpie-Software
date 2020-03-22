//---------------------------------------------------------------------------
#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include "scrb4.h"
#include "scrb4_controls.h"
#include "scrb4_values.h"
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include "browsefoldersdialog.h"
//---------------------------------------------------------------------------

class TConfigForm : public TScrDialog
{
__published:      // IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPageControl *PageControl;
    TTabSheet *tsGeneral;
    TTabSheet *tsOptions;
    TScrCheckBox *cbMute;
    TScrCheckBox *cbDisableActiveConfig;
    TLabel *tHotsInfo;
    TScrMonitor *monCorners;
    TScrCorners *corCorners;
    TScrTextHotServicesController *conHotsInfo;
    TScrEditIntegerMagnitudeController *conPasswordDelayMagnitude;
    TScrListBoxTwoUnitsController *conPasswordDelayUnits;
    TGroupBox *tDismissOptions;
    TLabel *tMouseSensitivity;
    TLabel *tPasswordDelay1;
    TLabel *tPasswordDelay2;
    TScrEdit *ePasswordDelay;
    TScrUpDown *udPasswordDelay;
    TScrComboBox *cbPasswordDelay;
    TScrComboBox *cbMouseSensitivity;
    TScrMonitor *ScrMonitor;
    TScrPreview *ScrPreview;
    TLabel *tBlobCaption;
    TScrEdit *edSW_DirName;
    TLabel *Label1;
    TButton *btnBrowse;
    TScrCheckBox *chkSubDir;
    TScrTrackBar *tbFileChange;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TScrTrackBar *tbTumbleSpeed;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TBrowseFoldersDialog *BrowseFoldersDialog;
    void __fastcall btnBrowseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:          // User declarations
public:           // User declarations
        __fastcall TConfigForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif


