//---------------------------------------------------------------------------
#ifndef UnZipDLLH
#define UnZipDLLH
// UnzDLL.h   - C++ Builder translation of file "wizunzip.h" by Eric W. Engler
/* Header file for UNZDLL - put this into the "include" statement of any
   other unit that wants to access the UNZDLL. */

/* I changed this to use dynamic loading of the DLL in order to allow
   the user program to control when to load and unload the DLLs.
   Thanks to these people for sending me dynamic loading code:
     Ewart Nijburg, Nijsoft@Compuserve.com
     P.A. Gillioz,  pag.aria@rhone.ch
*/

//---------------------------------------------------------------------------
namespace UnzipDLL {
#include "CallBack.h"

#include <vcl\Windows.hpp>
#include <vcl\System.hpp>

//-- type declarations -------------------------------------------------------
#pragma option -a1

/* These records are very critical.  Any changes in the order of items, the
   size of items, or modifying the number of items, may have disasterous
   results.  You have been warned! */
struct UnZipParms1 {
	HWND	 fHandle;
	void  *fCaller;   // "this" reference of the ZipBuilder class.
                     /* This is passed back to us in the callback function
                        so we can direct the info to the proper form instance
                        - thanks to Dennis Passmore for this idea. */
	long   fVersion;  // version of DLL we expect to see.
	CallBack::ZFunctionPtrType ZCallbackFunc;     // typedef in ZIPDLL.cpp
	DWord  fTraceEnabled;
	unsigned short fWantedCodePage;

   //============== Begin UnZip Flag section ==============
	unsigned short fPromptToOverwrite;  // Not used yet. (changed v1.5 in ush)
	char	*pZipPassword;			 // Password pointer. (changed v1.3)
	DWord  fTest;               // If true, test zipfile.
	DWord  fComments;           // Show zip comment.
	DWord  fConvert;            // If true, do ASCII/EBCDIC or EOL translation.
	DWord  fQuiet;              // DLL be quiet!
	DWord  fVerboseEnabled;     // Verbose flag.
	DWord  fUpdate;             // "update" (extract only newer files & brand new files).
	DWord  fFreshen;            // "freshen" (extract only newer files that already exist).
	DWord  fDirectories;        // If true, recreate dir structure.
	DWord  fOverwrite;          // If true, overwrite existing (no asking).

	//Count of filespecs to extract - don't forget to set this!
	long   fArgc;

	//ptr to zipfile name
	char  *pZipFN;
	long   fSeven;               // Pass a 7 here to validate struct size.

   // Array of filenames contained in the ZIP archive
	char  *pFileNames[FilesMax + 1];
};

struct UnzFileData {
	char	  *fFileSpec;			// Replaces PZipFN
	char	  *fFileAltName;
	char	  *fPassword;
	long		fNotUsed[15];
};

struct UnzExFileData {
	char	  *fFileSpec;
	long		fNotUsed[3];
};

struct UnZipParms2 {
	HWND								fHandle;
	void							  *fCaller;
	long								fVersion;
	CallBack::ZFunctionPtrType ZCallbackFunc;
	DWord								fTraceEnabled;
	unsigned short					fWantedCodePage;
	unsigned short					fPromptToOverwrite;
	char							  *pZipPassword;
	DWord								fTest;
	DWord								fComments;
	DWord								fConvert;
	DWord								fQuiet;
	DWord								fVerboseEnabled;
	DWord								fUpdate;
	DWord								fFreshen;
	DWord								fDirectories;
	DWord								fOverwrite;
	long								fArgc;
	char							  *pZipFN;
	struct UnzFileData		  *fUFDS;
	struct UnzExFileData		  *fXUDFS;
	DWord								fUseOutStream;		// NEW Use Memory stream as output.
	void							  *fOutStream;			// NEW Pointer to the start of streaam data.
	unsigned long					fOutStreamSize;	// NEW Size of the output data.
	DWord								fUseInStream;		// NEW Use memory stream as input.
	void							  *fInStream;			// NEW Pointer to the start of the input stream data.
	unsigned long					fInStreamSize;		// NEW Size of the input data.
	unsigned long					fPwdReqCount;		// NEW PasswordRequestCount, How many times a password will be asked per file
	long								fNotUsed[9];
	long								fSeven;
};
#pragma option -a.


typedef UnZipParms1 *pUnZipParms1;
typedef int __stdcall (*GetUnzExecAddress)( pUnZipParms1 );
typedef int __stdcall (*GetUnzVersionAddress)( void );

//-- var, const, procedure ---------------------------------------------------
extern GetUnzExecAddress		UnzDllExec;
extern GetUnzVersionAddress	GetUnzDllVersion;
extern HINSTANCE					UnzDllHandle;

}	/* namespace UnzipDLL */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
	using namespace UnzipDLL;
#endif
#endif
