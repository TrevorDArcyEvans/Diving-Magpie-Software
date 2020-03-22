#ifndef MessageH
#define MessageH

//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>

#include "Main.h"

//---------------------------------------------------------------------------
class TMsgForm : public TForm {
	__published:	// IDE-managed Components
		TPanel		 *Panel2;
		TPanel		 *Panel1;
		TButton		 *DismissBut;
		TButton		 *CancelBut;
		TLabel		 *FileBeingZipped;
		TProgressBar *ProgressBar1;
		TRichEdit	 *RichEdit1;
		TStatusBar	 *StatusBar1;

		void __fastcall DismissButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall FormResize( TObject *Sender );

	public:			// User declarations
		TProgressBar *ProgressBar2;
		int			  FormInitialWidth;

		__fastcall TMsgForm( TComponent *Owner ) : TForm( Owner ) { }
};

//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;

#endif

