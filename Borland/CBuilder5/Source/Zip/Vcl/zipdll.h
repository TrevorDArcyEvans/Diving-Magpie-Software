#ifndef ZipDLLH
#define ZipDLLH
// ZIPDLL.H   - C++ Builder translation of file "wizzip.h" by Eric W. Engler
/* Header file for ZIPDLL - put this into the "include" statement of any
   other unit that wants to access the DLL. */

//---------------------------------------------------------------------------
#include "CallBack.h"

#include <vcl\Windows.hpp>
#include <vcl\System.hpp>

namespace ZipDLL {
//-- type declarations -------------------------------------------------------

/* This record is very critical.  Any changes in the order of items, the
  size of items, or modifying the number of items, may have disasterous
  results.  You have been warned! */
#pragma option -a1
struct ZipParms1 {
	HWND	 fHandle;
	void  *fCaller; /* "this" reference of the ZipBuilder class.
                      This is passed back to us in the callback function
                      so we can direct the info to the proper form instance
                      - thanks to Dennis Passmore for this idea.            */
	long   fVersion;
	CallBack::ZFunctionPtrType ZCallbackFunc;
	DWord  fTraceEnabled;

   //============== Begin Zip Flag section ==============
	char	*pZipPassword;		// password pointer (changed v1.3)
	char	*pSuffix;			// Enum of file extensions; files with this extensions will be stored. v1.6
	DWord  fEncrypt;        // Encrypt files to be added?
	DWord  fSystem;			// Add hidden system files.
	DWord  fVolume;

   // Include extra file attributes (read-only, unix timestamps, etc)
	DWord  fExtra;

   // Do not add directory names to .ZIP archive
   // see also: fJunkDir
	DWord  fNoDirEntries;

   // Only add files newer a specified date
   // See the "Date" array below if you set this to TRUE
	DWord  fUseDate;

   // Give a little more information to the user via message boxes
	DWord  fVerboseEnabled;

   // Quiet operation - the DLL won't issue any messages at all.
   // BCB program MUST handle ALL errors via it's callback function.
	DWord  fQuiet;

   // Compression level (0 - 9; 9=max, 0=none)
   // All of these levels are variations of deflate.
   // I strongly recommend you use one of 3 values here:
	// 		0 = no compression, just store file
   //      3 = "fast" compression
   //      9 = "best" compression
	long   fLevel;

	DWord  fComprSpecial;		// Not use any more (v1.6)
	DWord  fCRLF_LF;				// translate text file end-of-lines

   // junk the directory names
   /* If true, this says not to save dirnames as separate entries,
      in addition to being save with filenames. */
   // see also: fNoDirEntries
	DWord  fJunkDir;
	//	DWord  fRecurse;		         // Recurse into subdirectories
	unsigned short fRecurse;			// Recurse into subdirectories
	unsigned short fNoRecurseFiles;	// Do not recurse if filespec is a file.
	DWord  fGrow;        				// Allow appending to a zip file

   /* Convert filenames to DOS 8x3 names - for compatibility
      with PKUNZIP v2.04g, which doesn't understand long filenames */
	DWord  fForce;

   // Delete orig files that were added or updated in zip file
   // This is a variation of Add
	DWord  fMove;
	DWord  fDeleteEntries;   // Delete specified files from zip file

   // Update zip -- if true, rezip changed, and add new files in fspec
   // This is a variation of Add
	DWord  fUpdate;

   // Freshen zip -- if true, rezip all changed files in fspec
   // This is a variation of Add
	DWord  fFreshen;

   // junk the SFX prefix on the self-extracing .EXE archives
	DWord  fJunkSFX;

   // Set zip file time to time of newest file in it
	DWord  fLatestTime;
   // ============== End Zip Flag section ==============

   // Cutoff Date for Add-by-date; add files newer than this day
   // This is only used if the "fDate" option is TRUE
   // format = MMDDYY plus two trailing nulls
	char   fDate[8];

   // Count of files to add or delete - don't forget to set this!
	long   fArgc;
	char  *pZipFN;       // Ptr to name of zip file.
	long   fSeven;        // Pass a 7 here to validate struct size.

	// Array of filenames contained in the ZIP archive
	char  *pFileNames[FilesMax + 1]; // :=4097
};

struct FileData {
	char	  *fFileSpec;			// Replaces pZipFN
	char	  *fFileComment;		// * NEW z->comment and z->com
	char	  *fFileAltName;		// * NEW
	char	  *fPassword;			// * Override
	DWord		fEncrypt;			// * Override
	DWord		fRecurse;			// * Override
	DWord		fNoRecurseFile;	// * Override
	DWord		fDateUsed;			// * Override
	char		fDate[8];			// * Override
	long		fNotUsed[16];		// * NEW
};

struct ExcludedFileSpec {
	char	  *fFileSpec;
};


struct ZipParms2 {
	HWND								fHandle;
	void							  *fCaller;
	long								fVersion;
	CallBack::ZFunctionPtrType ZCallbackFunc;
	DWord								fTraceEnabled;
	char							  *pZipPassword;		// password pointer (changed v1.3)
	char							  *pSuffix;
	DWord								fEncrypt;			// General encrypt, if not superseded by FileData.fEncrypt
	DWord								fSystem;
	DWord								fVolume;
	DWord								fExtra;
	DWord								fNoDirEntries;
	DWord								fUseDate;			// General DateUsed, if not superseded by FileData.fDateUsed
	DWord								fVerboseEnabled;
	DWord								fQuiet;
	int								fLevel;
	DWord								fComprSpecial;		// Not used any more. (v1.6) now fSuffix takes care of this.
	DWord								fCRLF_LF;
	DWord								fJunkDir;
	unsigned short int			fRecurse;
	unsigned short int			fNoRecurseFiles;
	DWord								fGrow;
	DWord								fForce;
	DWord								fMove;
	DWord								fDeleteEntries;
	DWord								fUpdate;
	DWord								fFreshen;
	DWord								fJunkSFX;
	DWord								fLatestTime;
	char								fDate[8];			// General Date, if not superseded by FileData.fDate
	long								fArgc;				// Changed, Number of FileData structures.
	char							  *pZipFN;				// Ptr to name of zip file.
	// After this point the structure is different from the ZipParms structure.
	char							  *fTempPath;			// NEW b option
	char							  *fArchComment;		// NEW zcomment and zcomlen
	short int						fArchiveFilesOnly;// NEW when != 0 only zip when archive bit set
	short int						fResetArchiveBit;	// NEW when != 0 reset the archive bit after a successfull zip
	struct FileData			  *fFDS;					// NEW (Actually an array of FileData's)
	BOOL								fForceWin;			// * NEW
	int								fTotExFileSpecs;	// NEW Number of ExcludedFileSpec structures.
	struct ExcludedFileSpec	  *fExFiles;			// NEW Array of file specs to exclude from zipping.
	long								fNotUsed[14];		// * NEW
	int								fSeven;				// End of structure (eg. 7)
};
#pragma option -a.

typedef ZipParms1 *PZipParms1;
typedef int __stdcall (*GetZipExecAddress)( PZipParms1 );
typedef int __stdcall (*GetZipVersionAddress)( void ) ;

// Note: Freshen, Update, and Move are only variations of Add.
enum ZipOpt { ZipAdd, ZipDelete };

//-- var, const, procedure ---------------------------------------------------
/* Main call to execute a ZIP add or Delete.  This call returns the
 * number of files that were sucessfully operated on. 					*/
extern GetZipExecAddress		ZipDllExec;
extern GetZipVersionAddress	GetZipDllVersion;
extern HINSTANCE					ZipDllHandle;

}	/* namespace ZipDLL */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
	using namespace ZipDLL;
#endif
#endif
