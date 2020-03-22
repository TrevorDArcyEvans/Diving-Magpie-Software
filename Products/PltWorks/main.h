//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>

#include <utilcls.h>

#include <Comobj.hpp>
#include <vcl\Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <Regi1632.hpp>
#include "Dropper.hpp"
#include "MRUList.hpp"
#include <memory>     //for STL auto_ptr
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <except.h> //for xmsg
#include <cstring.h>

#include <printers.hpp>

#include <process.h>
#include <dos.h>
//---------------------------------------------------------------------------
#ifdef    MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
GLOBAL    bool        g_bSW_Running;
//---------------------------------------------------------------------------
#define PLT_WORKS_TITLE             "PlotWorks v3.0"

// title used for software security
// have to update for v3.x releases etc
#define PLT_WORKS_TITLE_CODE        "PlotWorks v3.x"

// maximum number of prints for the unregistered version
#define        MAX_DOC            5
//---------------------------------------------------------------------------
#define PW_LOG_ERROR(ErrorMessage)   \
                stbPltWorks->SimpleText = ErrorMessage;                 \
                frmError->memError->Lines->Add(stbPltWorks->SimpleText)
//---------------------------------------------------------------------------
#define PW_CATCH_OLE_ERROR      \
                                                                                                \
            catch(EOleException& e)                                                             \
                {                                                                               \
                PW_LOG_ERROR("OLE Error:  " + e.Message + "(" + e.ErrorCode + ")");             \
                }                                                                               \
                                                                                                \
            catch(EOleSysError& e)                                                              \
                {                                                                               \
                PW_LOG_ERROR("OLE Error:  " + e.Message + "(" + e.ErrorCode + ")");             \
                }                                                                               \
                                                                                                \
            catch(EOleError& e)                                                                 \
                {                                                                               \
                PW_LOG_ERROR("OLE Error:  " + e.Message);                                       \
                }                                                                               \
                                                                                                \
            catch(...)                                                                          \
                {                                                                               \
                PW_LOG_ERROR("OLE Error:  unknown error");                                      \
                }
//---------------------------------------------------------------------------
class TfrmPltWorks : public TForm
{
__published:    // IDE-managed Components
    TButton *btnAdd;
    TOpenDialog *dlgOpen;
    TListBox *lbxList;
    TButton *btnRemove;
    TButton *btnPrint;
    TRadioButton *rdoHiddenVisible;
    TRadioButton *rdoHiddenGrayed;
    TRadioButton *rdoHiddenRemoved;
    TRadioButton *rdoShaded;
    TStatusBar *stbPltWorks;
    TPrintDialog *dlgPrintDialog;
    TPrinterSetupDialog *dlgPrinterSetupDialog;
    TMainMenu *mnuMain;
    TMenuItem *mnuHelp;
    TMenuItem *mnuAbout;
    TMenuItem *mnuContents;
    TCheckBox *chkIsometric;
    TLabel *lblPrtAssy;
    TCheckBox *chkZoomFit;
    TCheckBox *chkPreview;
    TMenuItem *mnuFile;
    TMenuItem *mnuExit;
    TMenuItem *N1;
    TMenuItem *mnuSelPrint;
    TMenuItem *mnuPrintSetup;
    TMenuItem *N2;
    TMenuItem *mnuOpen;
    TMenuItem *mnuSave;
    TMenuItem *mnuSaveAs;
    TMenuItem *mnuPrint;
    TOpenDialog *dlgOpenFileName;
    TSaveDialog *dlgSaveFileName;
    TSpeedButton *sbtnAdd;
    TBevel *Bevel1;
    TSpeedButton *sbtnRemove;
    TSpeedButton *sbtnSelPrint;
    TSpeedButton *sbtnPrintSetup;
    TSpeedButton *sbtnPrint;
    TSpeedButton *sbtnExit;
    TSpeedButton *sbtnSave;
    TSpeedButton *sbtnOpen;
    TMenuItem *mnuRegister;
    TMenuItem *N3;
    TRegistry1632 *regSettings;
    TMenuItem *N4;
    TMenuItem *mnuViewLog;
    TFileDropper *FileDropper;
    TBitBtn *btnUp;
    TBitBtn *btnDown;
    TMenuItem *mnuMapPrinters;
    TSpeedButton *sbtnMapPrint;
    TMRUManager *MRUFileList;
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnRemoveClick(TObject *Sender);

    void __fastcall btnPrintClick(TObject *Sender);

    void __fastcall mnuSelPrintClick(TObject *Sender);
    void __fastcall mnuPrintSetupClick(TObject *Sender);
    void __fastcall mnuExitClick(TObject *Sender);

    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);

    void __fastcall mnuSaveClick(TObject *Sender);

    void __fastcall mnuSaveAsClick(TObject *Sender);
    void __fastcall mnuOpenClick(TObject *Sender);


    void __fastcall mnuAboutClick(TObject *Sender);
    void __fastcall mnuContentsClick(TObject *Sender);

    void __fastcall mnuRegisterClick(TObject *Sender);
    void __fastcall mnuViewLogClick(TObject *Sender);
    void __fastcall FileDropperDrop(TObject *Sender, AnsiString Filename);
    void __fastcall btnUpClick(TObject *Sender);
    void __fastcall btnDownClick(TObject *Sender);
    void __fastcall mnuMapPrintersClick(TObject *Sender);
    void __fastcall MRUFileListClick(TObject *Sender,
          const AnsiString RecentName, const AnsiString Caption,
          int UserData);

private:    // User declarations

public:        // User declarations
    __fastcall TfrmPltWorks(TComponent* Owner);

    AnsiString      m_FileName;

    bool            m_bRegistered, m_bPrinted,
                    m_bDirty;

    int             m_nCurrentPrinter;
    TPrinter        *m_Printer;

    void            UpdateFileName(
                        String      AFileName);

    void            PrintFiles();

    void            PrintDrawingFile(
                        Variant     swApp,
                        Variant     swDrawingDoc);

    void            GotoFirstDrawing(
                        Variant     swDrawingDoc);

    void            SetupPrinter(
                        Variant     swApp,
                        Variant     swDrawingDoc,
                        Variant     swSheet,
                        double      *nPrintScale);

    void            OpenFile(
                        Variant     swApp,
                        String      FileName,
                        bool        *bFileLoadedOK,
                        bool        *bErrorsPrinting);
};
//---------------------------------------------------------------------------
extern TfrmPltWorks *frmPltWorks;
//---------------------------------------------------------------------------
#endif

