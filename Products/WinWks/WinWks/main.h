//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>

#include <utilcls.h>
#include <Comobj.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#define WW_HELP_FILE            "WinWks.hlp"
#define WINDOW_WORKS_TITLE      "WindowWorks v1.0"
//---------------------------------------------------------------------------
#define WW_CATCH_OLE_ERROR      \
catch(EOleException& e) \
    {   \
    MessageBox(NULL,    \
        ::String(   \
            ::String("OLE Error:  ") +  \
            e.Message +     \
            ::String("(") + \
            ::String(e.ErrorCode) +     \
            ::String(")")       \
            ).c_str(),      \
        WINDOW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);      \
    }   \
\
catch(EOleSysError& e)  \
    {   \
    MessageBox(NULL,    \
        ::String(   \
            ::String("OLE Error:  ") +  \
            e.Message +     \
            ::String("(") +     \
            ::String(e.ErrorCode) +     \
            ::String(")")       \
            ).c_str(),      \
        WINDOW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);      \
    }   \
\
catch(EOleError& e)     \
    {   \
    MessageBox(NULL,    \
        ::String(   \
            ::String("OLE Error:  ") +      \
            e.Message       \
            ).c_str(),      \
        WINDOW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);      \
    }   \
\
catch(...)      \
    {   \
    MessageBox(NULL,    \
    ::String(("OLE Error:  unknown error")).c_str(),    \
    WINDOW_WORKS_TITLE, MB_OK | MB_DEFBUTTON1 | MB_ICONERROR);  \
    }

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TCheckListBox *clbFileList;
    TButton *btnOK;
    TButton *btnCancel;
    TButton *btnHelp;
    TLabel *Label1;
    TImage *icoGripper;
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall btnHelpClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
extern "C"  bool WINAPI __declspec(dllexport) WW_CloseAll(void);
#endif
