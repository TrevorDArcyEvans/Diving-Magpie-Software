//---------------------------------------------------------------------------
#ifndef DirBrowseH
#define DirBrowseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include "zipbuilder.h"
//---------------------------------------------------------------------------
class TfrmUnzip : public TForm
{
__published:	// IDE-managed Components
    TDriveComboBox *DriveComboBox;
    TDirectoryListBox *DirListBox;
    TButton *btnOK;
    TButton *btnCancel;
    TZipBuilder *ZipBuilder;
    TListBox *lbxFileList;
    TCheckBox *chkOpen;
    TLabel *lblDir;
    void __fastcall DriveComboBoxChange(TObject *Sender);
    void __fastcall chkOpenClick(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    String      m_strZipFileName;
    String      m_strFileNameToOpen;
    bool        m_bDirStruct;
    __fastcall TfrmUnzip(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUnzip *frmUnzip;
//---------------------------------------------------------------------------
#endif
