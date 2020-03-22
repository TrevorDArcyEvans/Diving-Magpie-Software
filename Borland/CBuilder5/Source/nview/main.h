//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
class TFRM_Main : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TButton *BTN_Open;
	TScrollBox *ScrollBox1;
	TImage *Image1;
	TLabel *Label1;
	TButton *BTN_Exit;
	TPopupMenu *PopupMenu1;
	TMenuItem *MNU_About;
    TButton *Button1;
	void __fastcall BTN_OpenClick(TObject *Sender);
	void __fastcall BTN_ExitClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MNU_AboutClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
protected:
    void __fastcall WMSysCommand(TMessage& Message);
    BEGIN_MESSAGE_MAP
      MESSAGE_HANDLER(WM_SYSCOMMAND, TMessage, WMSysCommand)
    END_MESSAGE_MAP(TComponent)
public:		// User declarations
	__fastcall TFRM_Main(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFRM_Main *FRM_Main;

//---------------------------------------------------------------------------
#endif
