#if !defined(SXML_PRINT_INCLUDED_)
#define SXML_PRINT_INCLUDED_

#include "stdafx.h"

#include "XML_XSL.h"

#include "SRegistryAccess.hpp"
#include "SHResult.hpp"
#include "LogEvent.h"

#include <vector>

typedef std::vector <char> RemoveCharsVector;

class SXML_Print
{
private:
    // helper functions
    Initialise();

    // registry key name under [HKEY_LOCAL_MACHINE\SOFTWARE\Sigmex\] where
    // settings are held.  The following sub-keys should be present, under
    // [HKEY_LOCAL_MACHINE\SOFTWARE\Sigmex\"m_RegKey"]:
    //      name                type        member variable
    //      ------------------------------------------------
    //      "XSL FileName"      string      m_XSL_FileName
    //      "Output FileExt"    string      m_OutputFileExt
    //      "TimeOut"           DWORD       m_TimeOut
    CString                 m_RegKey;

    // fully qualified path to XSL file to apply to XML file
    CString                 m_XSL_FileName;

    // extension for output file *without* period
    CString                 m_OutputFileExt;

    // time to wait (seconds) before deleting temporary file
    // this is needed so the program associated with printing gets a chance
    // to initialise/start and then load the temporary file.
    // For example, something like Notepad may only need 5 secs but WinWord
    // may need 20 secs
    //
    // default value = 10 seconds
    int                     m_TimeOut;

    // list of characters to remove from the output file
    // this is an ugly hack because of extraneous characters being added in
    // some output files, in particular HTML files
    //
    // default value = none ie no characters
    RemoveCharsVector       m_RemoveChars;

public:
     SXML_Print();
    ~SXML_Print();

    SXML_Print
        (
            CString                     sRegKey
        );

    // helper functions
    CString get_RegKey() { return m_RegKey; }
    void    put_RegKey(CString sRegKey) { m_RegKey = sRegKey; }

    CString get_XSL_FileName() { return m_XSL_FileName; }
    void    put_XSL_FileName(CString sXSL_FileName) { m_XSL_FileName = sXSL_FileName; }

    int  get_TimeOut() { return m_TimeOut; }
    void put_TimeOut(int nTimeOut) { m_TimeOut = nTimeOut; }

    LoadSettings();

    // the main one!
    HRESULT Print
        (
            CString                     sXMLFileName
        );

    HRESULT AddRemoveChar
        (
            char                        cRemoveChar
        );
};
#endif

