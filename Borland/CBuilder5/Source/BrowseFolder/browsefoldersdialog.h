//===========================================================================
// Copyright © 1998 Thin Air Enterprises and Robert Dunn
// BrowseFoldersDialog.H
//===========================================================================
#ifndef BrowseFoldersDialogH
#define BrowseFoldersDialogH

#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <shlobj.h>
//---------------------------------------------------------------------------
typedef enum tagTBrowseFoldersRoot {
	bfrRecycleBin, bfrControlPanel, bfrDesktop, bfrDesktopDir, bfrDrives,
	bfrFonts, bfrNetHood, bfrNetwork, bfrPersonal, bfrPrinters, bfrPrograms,
	bfrRecent, bfrSendTo, bfrStartMenu, bfrStartUp, bfrTemplates
	} TBrowseFoldersRoot;

typedef enum tagTBrowseFoldersFlag {
	bffBrowseForComputer, bffBrowseForPrinter, bffDontGoBelowDomain,
	bffReturnsAncestors, bffReturnOnlyDirs, bffStatusText
	} TBrowseFoldersFlag;

typedef Set<TBrowseFoldersFlag, bffBrowseForComputer, bffStatusText>
	TBrowseFoldersFlags;

class PACKAGE TBrowseFoldersDialog : public TCommonDialog
{
protected:
	LPMALLOC g_pMalloc;				// IMalloc interface
	LPITEMIDLIST pidlPrograms;  	// PIDL for Programs folder
	LPITEMIDLIST pidlBrowseLast;	// PIDL last returned from browse
	LPSTR lpBuffer;					// buffer for display name?
	BROWSEINFO bi;					// BROWSEINFO structure
	AnsiString path;				// path for folder
	TBrowseFoldersRoot root;		// root for browse
	TBrowseFoldersFlags flags;	// flags for browse
	AnsiString title;				// message to display in browse dlg
	AnsiString displayName;			// display name

	static int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam,
		LPARAM lpData);				// callback for browse dialog

	AnsiString __fastcall GetDisplayName(void);
	void __fastcall SetFolder(AnsiString folder);
	bool __fastcall Allocate(void);
	void __fastcall Deallocate(void);
	bool __fastcall DoBrowse(void);

public:
#pragma warn -hid
	__fastcall TBrowseFoldersDialog(TComponent* Owner);
	__fastcall ~TBrowseFoldersDialog();
#pragma warn +hid
//	bool __fastcall Browse(void);
	virtual bool __fastcall Execute(void);

__published:
	__property AnsiString Folder = { read = path, write = SetFolder };
	__property AnsiString DisplayName = { read = displayName };
	__property TBrowseFoldersRoot Root = { read = root, write = root,
		default = bfrDesktop };
	__property TBrowseFoldersFlags Options = { read = flags, write = flags,
		default = TBrowseFoldersFlag(bffReturnOnlyDirs) };
	__property AnsiString Title = { read = title, write = title };
};
//---------------------------------------------------------------------------
#endif
//===========================================================================
// end of BrowseFoldersDialog.H
//===========================================================================

