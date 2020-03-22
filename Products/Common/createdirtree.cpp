
#include "stdafx.h"

#include "SString.hpp"
#include "Shlwapi.h"

#include "CreateDirTree.h"

//--------------------------------------------------------------------
// CreateDirTree
// make a directory and all directories above the specified dir ie create
// a directory tree
//
// parameters
//      DirTree
//          string containing fully qualified path to directory tree to
//          create
//          without trailing back slash
//
//      lpSecurityAttributes
//          see MSDN help on CreateDirectory()
//
// returns
//      true
//          if all directories successfully created
//
//      false
//          if all directories not successfully created
//
//          if any of the directories above the specified directory
//          (DirTree) already exists.  This is a due to the return
//          code from the Windows API function CreateDirectory()
//
// note
//      requires   shlwapi.lib   to be linked into the project and relies
//      on Version 4.71 and later of Shlwapi.dll ie Internet Explorer 4.0
//      - see MSDN help on PathIsRoot()
bool    CreateDirTree
(
    CString                     DirTree,
    LPSECURITY_ATTRIBUTES       lpSecurityAttributes
)
{
    // transfer to SString for extra features
    SString                     sTreeStr = DirTree;

    // current directory to create
    SString                     sCurrentDir;

    BOOL                        bRet = true;

    // initialise the extraction of each node of the dir tree
    SElementExtractor           Ext = sTreeStr.ExtractStart (_T("\\"));

    while (Ext.Active())
        {
        // get next node
        SString         sDirNode = sTreeStr.ExtractNext(Ext);

        sCurrentDir += sDirNode + _T("\\");

        // don't try and make the root dir, otherwise
        // CreateDirectory() will return false!
        if (!PathIsRoot(sCurrentDir))
            {
            bRet &= CreateDirectory(sCurrentDir, lpSecurityAttributes);
            }
        }//while

    return bRet;
}//CreateDirTree
//--------------------------------------------------------------------
#ifdef TEST
int main(int argc, char* argv[])
{
    CreateDirTree(_T("c:\\temp2\\vtemp"));

    return 0;
}
#endif
//--------------------------------------------------------------------
