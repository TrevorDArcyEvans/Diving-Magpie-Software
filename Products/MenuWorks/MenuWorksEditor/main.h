//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "Regi1632.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#define MENU_WORKS_TITLE		    "MenuWorks Editor v2.1"

// title used for software security
// have to update for v3.x releases etc
#define MENU_WORKS_TITLE_CODE       "MenuWorks v2.x"
//---------------------------------------------------------------------------
#ifdef	MAIN
#define GLOBAL
#else
#define GLOBAL  extern
#endif
//---------------------------------------------------------------------------
#define NUM_WRITE_BUTTONS   12

#define NUM_PROG            10
#define NUM_MENU            10
#define NUM_HINT            10

#ifdef	MAIN
char    *btnWriteName[NUM_WRITE_BUTTONS] =
    {
    "btnWrite0",
    "btnWrite1",
    "btnWrite2",
    "btnWrite3",
    "btnWrite4",
    "btnWrite5",
    "btnWrite6",
    "btnWrite7",
    "btnWrite8",
    "btnWrite9",
    "btnWriteAll",
    "btnMainWrite",
    };

char    *btnProgName[NUM_PROG] =
    {
    "edtProg0",
    "edtProg1",
    "edtProg2",
    "edtProg3",
    "edtProg4",
    "edtProg5",
    "edtProg6",
    "edtProg7",
    "edtProg8",
    "edtProg9",
    };

char    *btnMenuName[NUM_MENU] =
    {
    "edtMenu0",
    "edtMenu1",
    "edtMenu2",
    "edtMenu3",
    "edtMenu4",
    "edtMenu5",
    "edtMenu6",
    "edtMenu7",
    "edtMenu8",
    "edtMenu9",
    };

char    *btnHintName[NUM_HINT] =
    {
    "edtHint0",
    "edtHint1",
    "edtHint2",
    "edtHint3",
    "edtHint4",
    "edtHint5",
    "edtHint6",
    "edtHint7",
    "edtHint8",
    "edtHint9",
    };

char    *btnProgNumRegName[NUM_PROG] =
    {
    "Program0",
    "Program1",
    "Program2",
    "Program3",
    "Program4",
    "Program5",
    "Program6",
    "Program7",
    "Program8",
    "Program9",
    };

char    *btnMenuRegName[NUM_MENU] =
    {
    "edtMenu0",
    "edtMenu1",
    "edtMenu2",
    "edtMenu3",
    "edtMenu4",
    "edtMenu5",
    "edtMenu6",
    "edtMenu7",
    "edtMenu8",
    "edtMenu9",
    };

char    *btnHintRegName[NUM_HINT] =
    {
    "edtHint0",
    "edtHint1",
    "edtHint2",
    "edtHint3",
    "edtHint4",
    "edtHint5",
    "edtHint6",
    "edtHint7",
    "edtHint8",
    "edtHint9",
    };

#else
extern char    *btnWriteName[NUM_WRITE_BUTTONS];
extern char    *btnProgName[NUM_PROG];
extern char    *btnMenuName[NUM_MENU];
extern char    *btnHintName[NUM_HINT];

extern char    *btnProgNumRegName[NUM_PROG];
extern char    *btnMenuRegName[NUM_MENU];
extern char    *btnHintRegName[NUM_HINT];
#endif

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *btnWriteAll;
    TButton *btnReadAll;
    TPageControl *pctlMenuWorks;
    TTabSheet *tshMain;
    TLabel *lblMain;
    TEdit *edtMain;
    TButton *btnMainRead;
    TButton *btnMainWrite;
    TTabSheet *tshProg0;
    TLabel *lblProg0;
    TLabel *lblMenu0;
    TLabel *lblHint0;
    TEdit *edtProg0;
    TEdit *edtMenu0;
    TButton *btnBrowse0;
    TEdit *edtHint0;
    TButton *btnRead0;
    TButton *btnWrite0;
    TRegistry1632 *regMenuWorks;
    TOpenDialog *dlgOpen;
    TTabSheet *tshProg1;
    TTabSheet *tshProg2;
    TTabSheet *tshProg3;
    TTabSheet *tshProg4;
    TTabSheet *tshProg5;
    TTabSheet *tshProg6;
    TTabSheet *tshProg7;
    TTabSheet *tshProg8;
    TTabSheet *tshProg9;
    TLabel *lblProg1;
    TEdit *edtProg1;
    TButton *btnBrowse1;
    TEdit *edtMenu1;
    TLabel *lblMenu1;
    TLabel *lblHint1;
    TEdit *edtHint1;
    TButton *btnRead1;
    TButton *btnWrite1;
    TLabel *lblProg2;
    TEdit *edtProg2;
    TButton *btnBrowse2;
    TEdit *edtMenu2;
    TLabel *lblMenu2;
    TLabel *lblHint2;
    TEdit *edtHint2;
    TButton *btnRead2;
    TButton *btnWrite2;
    TLabel *lblProg3;
    TEdit *edtProg3;
    TButton *btnBrowse3;
    TEdit *edtMenu3;
    TLabel *lblMenu3;
    TLabel *lblHint3;
    TEdit *edtHint3;
    TButton *btnRead3;
    TButton *btnWrite3;
    TLabel *lblProg4;
    TEdit *edtProg4;
    TButton *btnBrowse4;
    TEdit *edtMenu4;
    TLabel *lblMenu4;
    TLabel *lblHint4;
    TEdit *edtHint4;
    TButton *btnRead4;
    TButton *btnWrite4;
    TLabel *lblProg5;
    TEdit *edtProg5;
    TButton *btnBrowse5;
    TEdit *edtMenu5;
    TLabel *lblMenu5;
    TLabel *lblHint5;
    TEdit *edtHint5;
    TButton *btnRead5;
    TButton *btnWrite5;
    TLabel *lblProg6;
    TEdit *edtProg6;
    TButton *btnBrowse6;
    TEdit *edtMenu6;
    TLabel *lblMenu6;
    TLabel *lblHint6;
    TEdit *edtHint6;
    TButton *btnRead6;
    TButton *btnWrite6;
    TLabel *lblProg7;
    TEdit *edtProg7;
    TButton *btnBrowse7;
    TEdit *edtMenu7;
    TLabel *lblMenu7;
    TLabel *lblHint7;
    TEdit *edtHint7;
    TButton *btnRead7;
    TButton *btnWrite7;
    TLabel *lblProg8;
    TEdit *edtProg8;
    TButton *btnBrowse8;
    TEdit *edtMenu8;
    TLabel *lblMenu8;
    TLabel *lblHint8;
    TEdit *edtHint8;
    TButton *btnRead8;
    TButton *btnWrite8;
    TLabel *lblProg9;
    TEdit *edtProg9;
    TButton *btnBrowse9;
    TEdit *edtMenu9;
    TLabel *lblMenu9;
    TLabel *lblHint9;
    TEdit *edtHint9;
    TButton *btnRead9;
    TButton *btnWrite9;
    TStatusBar *stbMenuWorks;
    TMainMenu *mnuMain;
    TMenuItem *mnuFile;
    TMenuItem *mnuExit;
    TMenuItem *Help1;
    TMenuItem *About1;
    TMenuItem *Contents1;
    void __fastcall FormCreate(TObject *Sender);

    
    void __fastcall btnRead0Click(TObject *Sender);
    void __fastcall btnMainReadClick(TObject *Sender);
    void __fastcall btnRead1Click(TObject *Sender);
    void __fastcall btnRead2Click(TObject *Sender);
    void __fastcall btnRead3Click(TObject *Sender);
    void __fastcall btnRead4Click(TObject *Sender);
    void __fastcall btnRead5Click(TObject *Sender);
    void __fastcall btnRead6Click(TObject *Sender);
    void __fastcall btnRead7Click(TObject *Sender);
    void __fastcall btnRead8Click(TObject *Sender);
    void __fastcall btnRead9Click(TObject *Sender);
    void __fastcall btnReadAllClick(TObject *Sender);
    void __fastcall btnMainWriteClick(TObject *Sender);
    void __fastcall btnWrite0Click(TObject *Sender);
    void __fastcall btnWrite1Click(TObject *Sender);
    void __fastcall btnWrite2Click(TObject *Sender);
    void __fastcall btnWrite3Click(TObject *Sender);
    void __fastcall btnWrite4Click(TObject *Sender);
    void __fastcall btnWrite5Click(TObject *Sender);
    void __fastcall btnWrite6Click(TObject *Sender);
    void __fastcall btnWrite7Click(TObject *Sender);
    void __fastcall btnWrite8Click(TObject *Sender);
    void __fastcall btnWrite9Click(TObject *Sender);
    void __fastcall btnWriteAllClick(TObject *Sender);
    void __fastcall btnBrowse0Click(TObject *Sender);
    void __fastcall btnBrowse1Click(TObject *Sender);
    void __fastcall btnBrowse2Click(TObject *Sender);
    void __fastcall btnBrowse3Click(TObject *Sender);
    void __fastcall btnBrowse4Click(TObject *Sender);
    void __fastcall btnBrowse5Click(TObject *Sender);
    void __fastcall btnBrowse6Click(TObject *Sender);
    void __fastcall btnBrowse7Click(TObject *Sender);
    void __fastcall btnBrowse8Click(TObject *Sender);
    void __fastcall btnBrowse9Click(TObject *Sender);
    void __fastcall mnuExitClick(TObject *Sender);
    
    void __fastcall About1Click(TObject *Sender);
    void __fastcall Contents1Click(TObject *Sender);
private:	// User declarations
    bool	bRegistered;

    void    EnableMainMenu(void);
    
    void    EnableWriteButtons(void);
    void    EnableProgramFields(void);
    void    EnableMenuFields(void);
    void    EnableHintFields(void);

    void    ReadMainMenu(void);

    void    ReadProgram(int Index);
    void    ReadMenu(int Index);
    void    ReadHint(int Index);

    void    WriteMainMenu(void);

    void    WriteProgram(int Index);
    void    WriteMenu(int Index);
    void    WriteHint(int Index);

    void    WriteAllPrograms(void);
    void    WriteAllMenus(void);
    void    WriteAllHints(void);

    void    BrowseProgram(int Index);

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

