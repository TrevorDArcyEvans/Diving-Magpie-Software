//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "zipbuilder.h"
//---------------------------------------------------------------------------
#define AV_FILE_MGR         "ActivaultFileMgr"
#define AV_DATABASE_MGR     "ActivaultServer"

#define AV_STR_STARTED      "started"
#define AV_STR_STOPPED      "stopped"
#define AV_STR_FORMAT       "#,##0"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *Server;
    TLabel *Label2;
    TLabel *Label3;
    TGroupBox *Database;
    TLabel *lblSvrStatFile;
    TLabel *lblSvrStatDB;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *lblDBName;
    TLabel *lblDBSize;
    TGroupBox *Vault;
    TLabel *label12;
    TLabel *label13;
    TLabel *lblVaultsize;
    TLabel *label11;
    TLabel *lblVaultCount;
    TButton *btnSvrFile;
    TButton *btnSvrDB;
    TComboBox *cboVaultDir;
    TZipBuilder *ZipBuilder;
    TButton *btnBackup;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSvrFileClick(TObject *Sender);
    void __fastcall btnSvrDBClick(TObject *Sender);
    void __fastcall cboVaultDirChange(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall btnBackupClick(TObject *Sender);

private:	// User declarations
    bool    m_bSvrRunningFile,
            m_bSvrRunningDB;

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
    int AV_ServiceRunning   (char *pcServiceName);
    int AV_ServiceStart     (char *pcServiceName);
    int AV_ServiceStop      (char *pcServiceName);
    int AV_StorageDirScan(char *pcDirName, int *Size, int *FileCount);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
