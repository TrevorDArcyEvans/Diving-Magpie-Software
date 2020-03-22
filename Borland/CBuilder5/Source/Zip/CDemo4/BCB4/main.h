// InstallZip - Demo4 of C-Builder Zip v1.51
/* This is a C-Builder example of how a small self-installing program
 * might be written. If it runs with an argument of /INSTALL, it automatically
 * brings up the install menu.  If it runs with an argument of /UNINSTALL
 * (such as when running from the Control Panel Uninstall option), it
 * does the uninstall and exits.  If the argument is anything else, then
 * it assumes it's a zip file and tries to open it.
 *
 * IMPORTANT!!!  "Install" is designed for Win95 Registry keys.  It
 * should work on Win98, but it will likely require some tweaks for WinNT.
 * YOU HAVE BEEN WARNED!
 */

//---------------------------------------------------------------------------
#ifndef MainH
#define MainH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

#include "Grids.hpp"
#include "SortGrid.hpp"

#include "ZIPBuilder.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm {
	__published:	// IDE-managed Components
		TPanel			*Panel1;
		TLabel			*Label1;
		TLabel			*Label2;
		TLabel			*ZipFName;
		TLabel			*Label4;
		TButton			*OpenBut;
		TButton			*CancelBut;
		TButton			*InstBut;
		TSortGrid		*SortGrid1;
		TOpenDialog		*OpenDialog1;
		TZipBuilder		*ZipDir1;

		void __fastcall FormActivate( TObject *Sender );
		void __fastcall FormCreate( TObject *Sender );
		void __fastcall OpenButClick( TObject *Sender );
		void __fastcall InstButClick( TObject *Sender );
		void __fastcall CancelButClick( TObject *Sender );
		

	public:			// User declarations
		__fastcall TMainForm( TComponent *Owner );

		bool			 AutoUnInstall;

		void __fastcall FillGrid( void );
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;

#endif

