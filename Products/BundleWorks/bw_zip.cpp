// pre-compiled headers
#include "stdafx.h"

/*
 A very simplistic example of how to load the zip dll and make a call into it.
 Note that none of the command line options are implemented in this example.

 */

#define API

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <direct.h>

#include "BW_Zip.h"
#include "zipver.h"

#include <commctrl.h>
#include <winver.h>

#define ZIP_DLL_NAME    _T("ZIP32.DLL\0")

#define DLL_WARNING             _T("Cannot find %s.")\
            _T(" The Dll must be in the application directory, the path, ")\
            _T("the Windows directory or the Windows System directory.")

#define DLL_VERSION_WARNING     _T("%s has the wrong version number.")\
            _T(" Insure that you have the correct dll's installed, and that ")\
            _T("an older dll is not in your path or Windows System directory.")


/* type definitions *********************************************************/

typedef int (WINAPI * _DLL_ZIP)(ZCL);
typedef int (WINAPI * _ZIP_USER_FUNCTIONS)(LPZIPUSERFUNCTIONS);
typedef BOOL (WINAPI * ZIPSETOPTIONS)(ZPOPT);

/* file global variables ****************************************************/

HANDLE                  hZUF = (HANDLE ) NULL;
ZPOPT                   ZpOpt;

/* local function prototypes ************************************************/

void                FreeUpMemory(void);

/****************************************************************************/

void FreeUpMemory(void)
{
if (hZUF)
   {
   GlobalUnlock(hZUF);
   GlobalFree(hZUF);
   }
}

/****************************************************************************/

/* Password entry routine - see password.c in the wiz directory for how
   this is actually implemented in Wiz. If you have an encrypted file,
   this will probably give you great pain. Note that none of the
   parameters are being used here, and this will give you warnings.
 */
int WINAPI          BunWks_ZipPassword(
                        char            *p      ,
                        int             n       ,
                        const char      *m      ,
                        const char      *name   )
{
(void ) p;
(void ) n;
(void ) m;
(void ) name;

return 1;
}

/****************************************************************************/

/* Dummy "print" routine that simply outputs what is sent from the dll */
int WINAPI          BunWks_ZipPrint(
                        char far        *buf    ,
                        unsigned long   size    )
{
#if 0
MessageBox((HWND ) NULL, ::CString(buf), _T("Message!"), MB_OK);
#endif
return (unsigned int) size;
}

/****************************************************************************/

/* Dummy "comment" routine. See comment.c in the wiz directory for how
   this is actually implemented in Wiz. This will probably cause you
   great pain if you ever actually make a call into it.
 */
char far * WINAPI   BunWks_ZipComment(
                        char far        *szBuf  )
{
szBuf[0] = '\0';
return szBuf;
}

/****************************************************************************/

int                 BunWks_ZipFile(
                        char            *pcZipFileName  ,
                        char            *pcFileToAdd    ,
                        BOOL            bSaveDirInfo    )
{
_DLL_ZIP                lpfnZpArchive;
_ZIP_USER_FUNCTIONS     lpfnZpInit;
ZIPSETOPTIONS           lpfnZpSetOptions;
HINSTANCE               hZipDll;

HANDLE                  hFileList;
ZCL                     ZpZCL;
LPZIPUSERFUNCTIONS      lpZipUserFunctions;



LPSTR           szFileList;
char            **index, *sz;
int             retcode, i, cc;
DWORD           dwVerInfoSize;
DWORD           dwVerHnd;
TCHAR           szFullPath[PATH_MAX];

TCHAR           *ptr;

HANDLE          hMem = NULL;         /* handle to mem alloc'ed */

hZUF = GlobalAlloc(GPTR, (DWORD ) sizeof(ZIPUSERFUNCTIONS));
if (!hZUF)
   {
   return 0;
   }
lpZipUserFunctions = (LPZIPUSERFUNCTIONS ) GlobalLock(hZUF);

if (!lpZipUserFunctions)
   {
   GlobalFree(hZUF);
   return 0;
   }

lpZipUserFunctions->print       = BunWks_ZipPrint;
lpZipUserFunctions->password    = BunWks_ZipPassword;
lpZipUserFunctions->comment     = BunWks_ZipComment;

/* Let's go find the dll */
if (SearchPath(
        NULL,               /* address of search path               */
        ZIP_DLL_NAME,       /* address of filename                  */
        NULL,               /* address of extension                 */
        PATH_MAX,           /* size, in characters, of buffer       */
        szFullPath,         /* address of buffer for found filename */
        &ptr                /* address of pointer to file component */
        ) == 0)
    {
    TCHAR       str[256];
    _stprintf(str, DLL_WARNING, ZIP_DLL_NAME);
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    FreeUpMemory();
    return 0;
    }

/* Now we'll check the zip dll version information */
dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);

if (dwVerInfoSize)
   {
   BOOL         fRet, fRetName;
   LPSTR        lpstrVffInfo; /* Pointer to block to hold info */
   LPTSTR        lszVer = NULL;
   LPTSTR        lszVerName = NULL;
   UINT         cchVer = 0;

   /* Get a block big enough to hold the version information */
   hMem          = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
   lpstrVffInfo  = (char *) GlobalLock(hMem);

   /* Get the version information */
   GetFileVersionInfo(szFullPath, 0L, dwVerInfoSize, lpstrVffInfo);
   fRet = VerQueryValue(lpstrVffInfo,
              TEXT("\\StringFileInfo\\040904E4\\FileVersion"),
               (LPVOID *) &lszVer,
               &cchVer);
   fRetName = VerQueryValue(lpstrVffInfo,
               TEXT("\\StringFileInfo\\040904E4\\CompanyName"),
              (LPVOID *) &lszVerName,
              &cchVer);

    if (!fRet || !fRetName ||
        (_tcsicmp(lszVer    , _T(ZIP_DLL_VERSION)) != 0) ||
        (_tcsicmp(lszVerName, _T(COMPANY_NAME   )) != 0) )
        {
        AfxMessageBox(_T("VerQueryValue"));

        TCHAR        str[256];
        _stprintf(str, DLL_VERSION_WARNING, ZIP_DLL_NAME);
        MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
        FreeUpMemory();
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        return 0;
        }
    /* free memory */
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    }
else
    {
    TCHAR       str[256];
    _stprintf(str, DLL_VERSION_WARNING, ZIP_DLL_NAME);
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    FreeUpMemory();
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    return 0;
    }
/* Okay, now we know that the dll exists, and has the proper version
 * information in it. We can go ahead and load it.
 */
hZipDll = LoadLibrary(ZIP_DLL_NAME);

if (hZipDll != NULL)
    {
    (_DLL_ZIP ) lpfnZpArchive = (_DLL_ZIP ) GetProcAddress(hZipDll, "ZpArchive");
    (ZIPSETOPTIONS ) lpfnZpSetOptions = (ZIPSETOPTIONS ) GetProcAddress(hZipDll, "ZpSetOptions");
    if (!lpfnZpArchive || !lpfnZpSetOptions)
        {
        TCHAR       str[256];
        _stprintf(str, _T("Could not get entry point to %s"), ZIP_DLL_NAME);
        MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
        FreeUpMemory();
        return 0;
        }
    }
else
    {
    TCHAR       str[256];
    _stprintf(str, _T("Could not load %s"), ZIP_DLL_NAME);
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    FreeUpMemory();
    return 0;
    }

(_ZIP_USER_FUNCTIONS) lpfnZpInit = (_ZIP_USER_FUNCTIONS)GetProcAddress(hZipDll, "ZpInit");
if (!lpfnZpInit)
    {
    TCHAR       str[256];
    _stprintf(str, _T("%s"), _T("Cannot get address of ZpInit in Zip dll. Terminating..."));
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    FreeLibrary(hZipDll);
    FreeUpMemory();
    return 0;
    }

if (!(*lpfnZpInit ) (lpZipUserFunctions))
    {
    TCHAR        str[256];
    _stprintf(str, _T("%s"), _T("Application functions not set up properly. Terminating..."));
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    FreeLibrary(hZipDll);
    FreeUpMemory();
    return 0;
    }

/* Here is where the action starts */
ZpOpt.fSuffix           = FALSE;        /* include suffixes (not yet implemented) */
ZpOpt.fEncrypt          = FALSE;        /* true if encryption wanted */
ZpOpt.fSystem           = FALSE;        /* true to include system/hidden files */
ZpOpt.fVolume           = FALSE;        /* true if storing volume label */
ZpOpt.fExtra            = FALSE;        /* true if including extra attributes */
ZpOpt.fNoDirEntries     = FALSE;        /* true if ignoring directory entries */
ZpOpt.fUpdate           = FALSE;        /* true if excluding files earlier than a
                                            specified date */
ZpOpt.fVerbose          = FALSE;        /* true if full messages wanted */
ZpOpt.fQuiet            = FALSE;        /* true if minimum messages wanted */
ZpOpt.fCRLF_LF          = FALSE;        /* true if translate CR/LF to LF */
ZpOpt.fLF_CRLF          = FALSE;        /* true if translate LF to CR/LF */

ZpOpt.fJunkDir          = !bSaveDirInfo;/* true if junking directory names */
ZpOpt.fRecurse          = FALSE;        /* true if recursing into subdirectories */
ZpOpt.fGrow             = FALSE;        /* true if allow appending to zip file */
ZpOpt.fForce            = FALSE;        /* true if making entries using DOS names */
ZpOpt.fMove             = FALSE;        /* true if deleting files added or updated */
ZpOpt.fUpdate           = FALSE;        /* true if updating zip file--overwrite only
                                            if newer */
ZpOpt.fFreshen          = FALSE;        /* true if freshening zip file--overwrite only */
ZpOpt.fJunkSFX          = FALSE;        /* true if junking sfx prefix*/
ZpOpt.fLatestTime       = FALSE;        /* true if setting zip file time to time of
                                            latest file in archive */
ZpOpt.fComment          = FALSE;        /* true if putting comment in zip file */
ZpOpt.fOffsets          = FALSE;        /* true if updating archive offsets for sfx
                                            files */
ZpOpt.fDeleteEntries    = FALSE;        /* true if deleting files from archive */
ZpOpt.fDate[0]          = '\0';         /* Not using, set to 0 length */
getcwd(ZpOpt.szRootDir, MAX_PATH);      /* Set directory to current directory */

ZpZCL.argc              = 1;            /* number of files to archive - adjust for the
                                            actual number of file names to be added */

ZpZCL.lpszZipFN         = pcZipFileName;/* archive to be created/updated */

/* Copy over the appropriate portions of argv, basically stripping out argv[0]
   (name of the executable) and argv[1] (name of the archive file)
 */
hFileList = GlobalAlloc(GPTR, 0x10000L);
if (hFileList)
    {
    szFileList = (char far *) GlobalLock(hFileList);
    }

index   = (char **) szFileList;
cc      = (sizeof(char *) * ZpZCL.argc);
sz      = szFileList + cc;

for (i = 0; i < ZpZCL.argc; i++)
    {
    cc = strlen(pcFileToAdd);
    strcpy(sz, pcFileToAdd);
    index[i] = sz;
    sz += (cc + 1);
    }
ZpZCL.FNV = (char **) szFileList;  /* list of files to archive */

/* Set the options */
(*lpfnZpSetOptions ) (ZpOpt);

/* Go zip 'em up */
retcode = (*lpfnZpArchive ) (ZpZCL);
if (retcode != 0)
    {
    TCHAR        str[256];
    _stprintf(str, _T("%s"), _T("Error in archiving"));
    MessageBox((HWND ) NULL, str, _T("Fatal Error!"), MB_ICONSTOP | MB_OK);
    }

GlobalUnlock(hFileList);
GlobalFree(hFileList);
FreeUpMemory();
FreeLibrary(hZipDll);

return 1;
}

/****************************************************************************/
