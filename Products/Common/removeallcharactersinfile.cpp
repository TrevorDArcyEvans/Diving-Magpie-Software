#include "stdafx.h"
#include "RemoveAllCharactersInFile.h"

// RemoveAllCharactersInFile
// removes all occurrences of the specified character from a text file on disk.
//
// Since the character is *removed* rather than replaced, the resultant file
// should be smaller than the original
//
// parameters
//      sFileName
//          fully qualified path to text file
//
//      cChar
//          character to remove
//
// returns
//      int
//          number of characters removed from file
//       0
//          if no characters were removed
//      -1
//          if there were problems, typically a CFileException
//
// notes
//      original file is overwritten by new file - just in case it wasn't obvious
int RemoveAllCharactersInFile
(
    CString                 sFileName,
    char                    cChar
)
{
    char                    *pXML_Contents;
    int                     nRemoved;

    try
        {
        USES_CONVERSION;

        CStdioFile              fXML_OldFile(sFileName,
                                    CFile::modeRead |
                                    CFile::typeText );

        UINT                    nOldFileSize = fXML_OldFile.GetLength();

        pXML_Contents = new char[nOldFileSize];

        // update the filesize based on the actual number of bytes read in
        // CFile::GetLength() seems to slightly overestimate the file size...
        nOldFileSize = fXML_OldFile.Read(pXML_Contents, nOldFileSize);
        fXML_OldFile.Close();

        CString                 sXML_FileContents = pXML_Contents;
        TCHAR                   cToReplace = cChar;

        // note ugly conversion for Unicode/MBCS compatibility
        nRemoved = sXML_FileContents.Remove(*A2T(&cChar));

        // recalculate the file size based on how many characters were removed
        UINT                    nNewFileSize = nOldFileSize - nRemoved;

        // note ugly cast for Unicode/MBCS compatibility
        strncpy(pXML_Contents, T2A((TCHAR *) LPCTSTR(sXML_FileContents)), nNewFileSize);

        // create output file, overwriting original file
        CStdioFile              fXML_NewFile(sFileName,
                                    CFile::modeWrite    |
                                    CFile::modeCreate   |
                                    CFile::typeText     );

        fXML_NewFile.Write(pXML_Contents, nNewFileSize);
        fXML_NewFile.Close();
        }//try
    catch (CFileException e)
        {
        nRemoved = -1;
        }
    catch (...)
        {
        nRemoved = -1;
        }

    delete [] pXML_Contents;

    return nRemoved;
}//RemoveAllCharactersInFile
