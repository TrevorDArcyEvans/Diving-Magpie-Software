//===========================================================================
// Copyright © 1998 Thin Air Enterprises and Robert Dunn
// BrowseFoldersDialog.cpp
//===========================================================================
#include <vcl.h>
#pragma hdrstop

#include "BrowseFoldersDialog.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TBrowseFoldersDialog *)
{
	new TBrowseFoldersDialog(NULL);
}
//---------------------------------------------------------------------------
namespace Browsefoldersdialog
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TBrowseFoldersDialog)};
		RegisterComponents("Samples", classes, 0);
	}
}
//---------------------------------------------------------------------------
// constructor
//
__fastcall TBrowseFoldersDialog::TBrowseFoldersDialog(TComponent* Owner)
	: TCommonDialog(Owner), pidlBrowseLast(NULL)
{
	// set defaults
	path = "";
	root = bfrDesktop;
	flags.Clear();
	flags << bffReturnOnlyDirs;
}
//---------------------------------------------------------------------------
// destructor
//
__fastcall TBrowseFoldersDialog::~TBrowseFoldersDialog()
{
}
//---------------------------------------------------------------------------
// Execute() - set up and invoke the shell browse function
//
bool __fastcall TBrowseFoldersDialog::Execute(void)
{
	if (!Allocate()) return false;
	bool result = DoBrowse();
	Deallocate();
	return result;
}
//---------------------------------------------------------------------------
// Allocate() - allocate needed structures and fill in values
//
bool __fastcall TBrowseFoldersDialog::Allocate(void)
{
	// get the shell's allocator
	if (!SUCCEEDED(SHGetMalloc(&g_pMalloc))) return false;

	// Allocate a buffer to receive browse information.
	if ((lpBuffer = (LPSTR) g_pMalloc->Alloc(MAX_PATH)) == NULL) {
		g_pMalloc->Release();
		return false;
		}

	// since TCommonDialog does not contain a window handle, grab
	// the handle of the currently active window in this thread
	HWND hwnd = GetActiveWindow();

	// translate enum to flag
	int flag = CSIDL_DESKTOP;
	switch ((int) root) {
		case bfrRecycleBin:		flag = CSIDL_BITBUCKET;			break;
		case bfrControlPanel:	flag = CSIDL_CONTROLS;			break;
		case bfrDesktopDir:		flag = CSIDL_DESKTOPDIRECTORY;	break;
		case bfrDrives:			flag = CSIDL_DRIVES;			break;
		case bfrFonts:			flag = CSIDL_FONTS;				break;
		case bfrNetHood:		flag = CSIDL_NETHOOD;			break;
		case bfrNetwork:		flag = CSIDL_NETWORK;			break;
		case bfrPersonal:		flag = CSIDL_PERSONAL;			break;
		case bfrPrinters:		flag = CSIDL_PRINTERS;			break;
		case bfrPrograms:		flag = CSIDL_PROGRAMS;			break;
		case bfrRecent:			flag = CSIDL_RECENT;			break;
		case bfrSendTo:			flag = CSIDL_SENDTO;			break;
		case bfrStartMenu:		flag = CSIDL_STARTMENU;			break;
		case bfrStartUp:		flag = CSIDL_STARTUP;			break;
		case bfrTemplates:		flag = CSIDL_TEMPLATES;			break;
		}

	// Get the PIDL for the desktop folder.
	if (!SUCCEEDED(SHGetSpecialFolderLocation(
			hwnd, flag, &pidlPrograms))) {
		g_pMalloc->Free(lpBuffer);
		g_pMalloc->Release();
		return false;
		}

	// Fill in the BROWSEINFO structure.
	bi.hwndOwner = hwnd;
	bi.pidlRoot = pidlPrograms;
	bi.pszDisplayName = lpBuffer;
	if (title != "") bi.lpszTitle = title.c_str();
	bi.ulFlags =
		flags.Contains(bffBrowseForComputer) ? BIF_BROWSEFORPRINTER : 0 |
		flags.Contains(bffDontGoBelowDomain) ? BIF_DONTGOBELOWDOMAIN : 0 |
		flags.Contains(bffReturnsAncestors) ? BIF_RETURNFSANCESTORS : 0 |
		flags.Contains(bffReturnOnlyDirs) ? BIF_RETURNONLYFSDIRS : 0 |
		flags.Contains(bffStatusText) ? BIF_STATUSTEXT : 0;

	bi.lpfn = BrowseCallbackProc;	// callback used to set last selection
	bi.lParam = (long) this;		// for callback proc

	// return ok
	return true;
}
//---------------------------------------------------------------------------
// Deallocate() - free allocated structures
//
void __fastcall TBrowseFoldersDialog::Deallocate(void)
{
	if (pidlBrowseLast) g_pMalloc->Free(pidlBrowseLast);
	g_pMalloc->Free(pidlPrograms);
	g_pMalloc->Free(lpBuffer);
	g_pMalloc->Release();
}
//---------------------------------------------------------------------------
// DoBrowse() - invoke the shell browse function
//
bool __fastcall TBrowseFoldersDialog::DoBrowse(void)
{
	LPITEMIDLIST pidlBrowse;    // PIDL selected by user this time

	// Browse for a folder and return its PIDL.
	pidlBrowse = SHBrowseForFolder(&bi);
	if (pidlBrowse != NULL) {
		// Free the PIDL previously returned by SHBrowseForFolder.
		g_pMalloc->Free(pidlBrowseLast);
		// And set to current selection
		pidlBrowseLast = pidlBrowse;
		displayName = lpBuffer;
		SHGetPathFromIDList(pidlBrowseLast, lpBuffer);
		path = lpBuffer;
		return true;
		}
	return false;
}
//---------------------------------------------------------------------------
// callback proc used by shell browse
//
int __stdcall TBrowseFoldersDialog::BrowseCallbackProc(HWND hwnd, UINT uMsg,
	LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, true,
			(LPARAM) reinterpret_cast<TBrowseFoldersDialog *>
			(lpData)->path.c_str());
	return 0;
}
//---------------------------------------------------------------------------
// property setter function
//---------------------------------------------------------------------------
void __fastcall TBrowseFoldersDialog::SetFolder(AnsiString folder)
{
//	path = folder.Trim();
	path = folder.Trim();
}
//===========================================================================
// end of BrowseFoldersDialog.cpp
//===========================================================================


