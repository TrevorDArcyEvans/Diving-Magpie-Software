#include "stdafx.h"

#include "XML_XSL.h"

#include "SRegistryAccess.hpp"
#include "SHResult.hpp"
#include "LogEvent.h"
#include "SLogError.h"

#include "SXML_Print.h"
#include "RemoveAllCharactersInFile.h"
#include "SDelayedDeleteFile.h"

//------------------------------------------------------------------------
SXML_Print::SXML_Print()
{
    Initialise();
}//SXML_Print::SXML_Print
//------------------------------------------------------------------------
SXML_Print::SXML_Print
(
    CString                     sRegKey
)
{
    Initialise();

    m_RegKey        = sRegKey;
}//SXML_Print::SXML_Print
//------------------------------------------------------------------------
// SXML_Print::Initialise
// called by both constructors to set all member variables to blank
SXML_Print::Initialise()
{
    m_RegKey            = _T("");
    m_XSL_FileName      = _T("");
    m_OutputFileExt     = _T("");

    m_TimeOut           = 10;

    m_RemoveChars.clear();
}//SXML_Print::Initialise
//------------------------------------------------------------------------
SXML_Print::~SXML_Print()
{
}//SXML_Print::~SXML_Print
//------------------------------------------------------------------------
// SXML_Print::AddRemoveChar
// adds specified character to the end of the list of characters to remove
// from output file
//
// parameters
//      cRemoveChar
//          character to remove from output file
//          this can be any character in the extended ASCII character set
//          ASCII 0 -255 inclusive
//
// returns
//      S_OK
//          always returns S_OK!
HRESULT SXML_Print::AddRemoveChar
(
    char                        cRemoveChar
)
{
    m_RemoveChars.push_back(cRemoveChar);
    return S_OK;
}//SXML_Print::AddRemoveChar
//------------------------------------------------------------------------
// SXML_Print::LoadSettings
// queries registry keys for the XSL filename and the extension for the
// output file.  Registry key is specified by m_RegKey and string values
// are read out of the following sub-keys:
//
//      "XSL FileName"      --> m_XSL_FileName
//      "Output FileExt"    --> m_OutputFileExt
//      "TimeOut"           --> m_TimeOut
// 
// If m_RegKey = _T("CMIDS\\Archiver") then settings will be read out of the 
// following registry keys:
//
//      [HKEY_LOCAL_MACHINE\SOFTWARE\Sigmex\CMIDS\Archiver]
//      "XSL FileName"="c:\\Archiver.xsl"
//      "Output FileExt"="html"
SXML_Print::LoadSettings()
{
    // load XSL file name & output file extension out of the registry
    SRegistryAccess         RegAc(HKEY_LOCAL_MACHINE);

    m_XSL_FileName  = RegAc.ReadString(m_RegKey, _T("XSL FileName"  ));
    m_OutputFileExt = RegAc.ReadString(m_RegKey, _T("Output FileExt"));
    m_TimeOut       = RegAc.ReadInt   (m_RegKey, _T("TimeOut"       ), m_TimeOut);
}//SXML_Print::LoadSettings
//------------------------------------------------------------------------
// SXML_Print::Print
// will query the registry for an XSL file to apply to the specified XML file,
// apply the XSL file and print it out to the default system printer
//
// parameters
//      sXMLFileName
//          fully qualified name to XML file to print out
//
// returns
//      S_OK
//          if successfully printed out file
//      otherwise
//          return values from IDMS_XML2XSL::Print() in XML2XSL.cpp
//
// notes
//      caller should call CWaitCursor before calling this function as we
//      wait for the print program to initialise and start printing before
//      returning
HRESULT SXML_Print::Print
(
    CString                     sXMLFileName
)
{
    HRESULT                         hres = S_OK;
    CString                         sOutputFileName;

    try
        {
        TCHAR                           sTempPath    [MAX_PATH];
        TCHAR                           sTempFileName[MAX_PATH];

        // work out where the temporary files are
        GetTempPath(sizeof(sTempPath) / sizeof(TCHAR), sTempPath);

        // form the output file name
        GetTempFileName(sTempPath, _T("SXML_Print"), 0, sTempFileName);
        sOutputFileName  = sTempFileName;

        // remove temp file created by GetTempFileName()
        DeleteFile(sTempFileName);

        // remove existing extension
        int                     nDotPos = sOutputFileName.Find(_T("."));
        if (-1 != nDotPos)
            {
            sOutputFileName.Delete(nDotPos + 1, sOutputFileName.GetLength() - nDotPos - 1);
            }
        // then add our own extension
        sOutputFileName += m_OutputFileExt;

        // now apply the XSL transform
        CComPtr <IDMS_XML2XSL>          pXML_XSL;
        CComBSTR                        sXML_FileName    = sXMLFileName;
        CComBSTR                        sXSL_FileName    = m_XSL_FileName;
        CComBSTR                        sOutput_FileName = sOutputFileName;

        STEST_HR(pXML_XSL.CoCreateInstance(__uuidof(DMS_XML2XSL)));
        STEST_HR(pXML_XSL->put_XML_FileName   (sXML_FileName   ));
        STEST_HR(pXML_XSL->put_XSL_FileName   (sXSL_FileName   ));
        STEST_HR(pXML_XSL->put_Output_FileName(sOutput_FileName));
        STEST_HR(pXML_XSL->Apply_XSL_XML());

        // remove all extraneous characters from the output file
        // before we print out
        for (int i = 0; i < m_RemoveChars.size (); i++)
            {
            RemoveAllCharactersInFile(::CString(sOutput_FileName), m_RemoveChars[i]);
            }

        // finally print out - whew!
        STEST_HR(pXML_XSL->Print());

        hres = S_OK;
        }
    catch (_com_error& e)
        {
        LogEvent(_T ("Error in SXML_Print::Print: %s"), e.ErrorMessage());

        hres = E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent(_T ("Unknown error in SXML_Print::Print"));

        hres = E_UNEXPECTED;
        }//try

    // we have to wait for print program to initialise and print out
    // note that there is no *real* way of waiting as we don't know what to
    // wait on.  Thus, this is just a guess...
    //
    // We cleanup the temporary files we've created before returning
    // note that we do this in a separate thread so as not to block
    SDelayedDeleteFile::DelayedDeleteFile(sOutputFileName, m_TimeOut);

    return hres;
}//SXML_Print::Print
//------------------------------------------------------------------------
