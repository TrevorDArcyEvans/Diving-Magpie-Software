#ifndef CallBackH
#define CallBackH

#include <vcl\Windows.hpp>
#include <vcl\System.hpp>

//---------------------------------------------------------------------------
namespace CallBack {

// Maximum no. of files in a single ZIP file (do NOT change):
const int FilesMax = 4096;
const int PASSWORDLEN = 80;	// new V1.3

/* All the items in the CallBackStruct are passed to the BCB
 * program from the DLL.  Note that the "Caller" value returned
 * here is the same one specified earlier in ZipParms by the
 * BCB program. */
#pragma option -a1
struct ZCallBackStruct {
	HWND   Handle;
	void  *Caller;					// 'this' reference of the ZipBuilder class
	long   Version;				// version no. of DLL.
	DWord  IsOperationZip;		// true=zip, false=unzip
	long   ActionCode;
	long   ErrorCode;
	long   FileSize;
	char   FileNameOrMsg[512];
};
#pragma option -a.
typedef ZCallBackStruct *PZCallBackStruct;

/* Declare a function pointer type for the BCB/Delphi callback function, to
 * be called by the DLL to pass updated status info back to BCB/Delphi.
 * From V1.5 the callback is a static member function of the ZipBuilder class! */
typedef unsigned long __stdcall (*ZFunctionPtrType)(PZCallBackStruct ZCallbackRec);

}	/* EOF namespace CallBack */

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
	using namespace CallBack;
#endif

#endif
