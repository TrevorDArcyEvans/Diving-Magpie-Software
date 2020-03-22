/* IMPORTANT!!!  "Install" is designed for Win95 Registry keys.  It
 * should work on Win98, but it will likely require some tweaks for WinNT.
 * YOU HAVE BEEN WARNED! */
//---------------------------------------------------------------------------
#ifndef InstallH
#define InstallH

//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Registry.hpp>

#include <shlobj.h>
#include "ZIPBuilder.h"

//---------------------------------------------------------------------------
class TInstForm : public TForm {
	__published:	// IDE-managed Components
		TGroupBox	 *GroupBox1;
		TCheckBox	 *AssocCB;
		TCheckBox	 *SendToCB;
		TCheckBox	 *StartMenuCB;
		TCheckBox	 *DesktopCB;
		TCheckBox	 *RegistryCB;
		TCheckBox	 *KillCB;
		TButton		 *InstBut;
		TButton		 *UnInstBut;
		TButton		 *CancelBut;
		TLabel		 *Label1;
		TLabel		 *Label3;
		TLabel		 *ProgramNameLabel;
		TLabel		 *Label2;
		TRadioButton *StartMenuRB;
		TRadioButton *ProgramRB;

		void __fastcall FormCreate( TObject *Sender );
		void __fastcall FormActivate( TObject *Sender );
		void __fastcall InstButClick( TObject *Sender );
		void __fastcall UnInstButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		void __fastcall StartMenuCBClick( TObject *Sender );

	public:			// User declarations
		__fastcall TInstForm( TComponent *Owner );

		void __fastcall MakeAssociation( String Ext, String PgmToLinkTo );
		void __fastcall RemoveAssociation( String Ext );
		void __fastcall RegDeleteKey( HKEY RKey, String KeyPath );
		void __fastcall SetValInReg( HKEY RKey, String KeyPath, String ValName, String NewVal );
		HRESULT __fastcall MakeLink( String PgmPath, String PgmArgs, String LinkPath, String Descr );
		long __fastcall GetSpecialFolder( int aFolder, String &Location );
};

//---------------------------------------------------------------------------
extern PACKAGE TInstForm *InstForm;
extern String WinDir, EXEName, EXETitle;
extern void WINAPI KillMySelf2( DWORD dwExitCode, bool fRemoveDir );

#endif

