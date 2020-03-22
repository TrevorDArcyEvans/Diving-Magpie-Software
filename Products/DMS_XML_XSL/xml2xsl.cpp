// XML2XSL.cpp : Implementation of CXML2XSL
#include "stdafx.h"

#include "XML_XSL.h"
#include "XML2XSL.h"

#include "SHResult.hpp"
#include "LogEvent.h"


//#include "SLogError.h"
#define     STEST_HR(x)             (x)
#define     SASSERT_BOOL_COM(x)     (x)
#define     SASSERT(x)              (x)

#include "Shlwapi.h"

#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CXML2XSL

CXML2XSL::CXML2XSL()
{
    ObjectLock(this);
}
//------------------------------------------------------------------------
CXML2XSL::~CXML2XSL()
{
    ObjectLock(this);
}
//------------------------------------------------------------------------
HRESULT CXML2XSL::FinalConstruct()
{
    ObjectLock(this);

    return S_OK;
}
//------------------------------------------------------------------------
HRESULT CXML2XSL::FinalRelease()
{
    ObjectLock(this);

    return S_OK;
}
//------------------------------------------------------------------------
// CXML2XSL::get_XML_FileName
// fully qualified name to XML source file
// should include .xml extension
STDMETHODIMP CXML2XSL::get_XML_FileName(BSTR *pVal)
{
    try
        {
        ObjectLock(this);

        m_XML_FileName.CopyTo(pVal);

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::get_XML_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::get_XML_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::put_XML_FileName
// fully qualified name to XML source file
// should include .xml extension
STDMETHODIMP CXML2XSL::put_XML_FileName(BSTR newVal)
{
    try
        {
        ObjectLock(this);

        m_XML_FileName = newVal;

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::put_XML_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::put_XML_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::get_XSL_FileName
// fully qualified name to XSL source file
// should include .xsl extension
STDMETHODIMP CXML2XSL::get_XSL_FileName(BSTR *pVal)
{
    try
        {
        ObjectLock(this);

        m_XSL_FileName.CopyTo(pVal);

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::get_XSL_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::get_XSL_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::put_XSL_FileName
// fully qualified name to XSL source file
// should include .xsl extension
STDMETHODIMP CXML2XSL::put_XSL_FileName(BSTR newVal)
{
    try
        {
        ObjectLock(this);

        m_XSL_FileName = newVal;

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::put_XSL_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::put_XSL_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::get_Output_FileName
// fully qualified name to output file
// should include any arbitrary extension eg .htm,.html, .xml etc
STDMETHODIMP CXML2XSL::get_Output_FileName(BSTR *pVal)
{
    try
        {
        ObjectLock(this);

        m_Output_FileName.CopyTo(pVal);

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::get_Output_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::get_Output_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::put_Output_FileName
// fully qualified name to output file
// should include any arbitrary extension eg .htm,.html, .xml etc
STDMETHODIMP CXML2XSL::put_Output_FileName(BSTR newVal)
{
    try
        {
        ObjectLock(this);

        m_Output_FileName = newVal;

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::put_Output_FileName: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::put_Output_FileName"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::Apply_XSL_XML
// takes an XSL style sheet and applies it to an XML file containing data.
// The resultant (transformed) data is then written out to file.
//
// returns
//      S_OK
//          if successfully written output file
//
//      S_FALSE
//          if XML, XSL or output file names has not been set
//              or
//          could not load msxml.dll version 2
//              or
//          problems applying XSL style sheet - result is not well formed XML
//              or
//          problems writing output file
STDMETHODIMP CXML2XSL::Apply_XSL_XML()
{
    try
        {
        ObjectLock(this);

        // make sure we've specified all the file names first
        if (!m_XML_FileName     ||
            !m_XSL_FileName     ||
            !m_Output_FileName  )
            {
            return S_FALSE;
            }

        CComQIPtr<MSXML::IXMLDOMDocument>       pXML_File;
        CComQIPtr<MSXML::IXMLDOMDocument>       pXSL_File;
        CComQIPtr<MSXML::IXMLDOMDocument>       pOutput_File;

        // create our DOMs in MSXML.dll v2
        STEST_HR(pXML_File   .CoCreateInstance(MSXML::CLSID_DOMDocument));
        STEST_HR(pXSL_File   .CoCreateInstance(MSXML::CLSID_DOMDocument));
        STEST_HR(pOutput_File.CoCreateInstance(MSXML::CLSID_DOMDocument));

        // have to use variants with MSXML - ewwwww!
        VARIANT_BOOL                            bRetval;
        CComVariant                             pVarXML_FileName;
        CComVariant                             pVarXSL_FileName;
        CComVariant                             pVarOutput_FileName;
        CComVariant                             pVarOutput_Object(pOutput_File.p);

        STEST_HR(pVarXML_FileName    .ChangeType(VT_BSTR     ));
        STEST_HR(pVarXSL_FileName    .ChangeType(VT_BSTR     ));
        STEST_HR(pVarOutput_FileName .ChangeType(VT_BSTR     ));

        STEST_HR(pVarOutput_Object   .vt = VT_UNKNOWN         );

        m_XML_FileName      .CopyTo(&pVarXML_FileName   .bstrVal);
        m_XSL_FileName      .CopyTo(&pVarXSL_FileName   .bstrVal);
        m_Output_FileName   .CopyTo(&pVarOutput_FileName.bstrVal);

        // load XML & XSL files from disk
        STEST_HR(pXML_File->load(pVarXML_FileName, &bRetval));
        STEST_HR(pXSL_File->load(pVarXSL_FileName, &bRetval));

        // apply XSL transformation to XML data, storing result in our output file
        STEST_HR(pXML_File->transformNodeToObject(pXSL_File, pVarOutput_Object));

        pOutput_File = pVarOutput_Object.punkVal;
        SASSERT_BOOL_COM(pOutput_File != NULL);

        // write output file to disk
        STEST_HR(pOutput_File->save(pVarOutput_FileName));

        return S_OK;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::Apply_XSL_XML: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::Apply_XSL_XML"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
// CXML2XSL::Print
// prints output file to the default system printer using the Windows 
// Explorer Shell
//
// returns
//      S_OK
//          if successfully written output file
//
//      S_FALSE
//          if error finding file association with output file
//              or
//          error printing
//              or
//          output file has not been specified
//
// note
//      no check is made if output file actually exists, this will be done 
//      on the call to FindExecutable()
//
//      will log error to NT event log
//
//      read comments about call to WaitForSingleObject()
STDMETHODIMP CXML2XSL::Print()
{
    try
        {
        ObjectLock(this);

        USES_CONVERSION;

        // make sure we've specified the output file name first
        if (!m_Output_FileName)
            {
            return S_FALSE;
            }

        HINSTANCE                               hRetVal1 = 0, hRetVal2 = 0;
        TCHAR                                   sExeName[MAX_PATH];
        TCHAR                                   sFileDir[MAX_PATH];
        SHELLEXECUTEINFO                        seiExecInfo;
        DWORD                                   dwWaitRet = 0;

        // find out where output file is stored
        //
        // note that it probably won't work too well for paths/file names
        // with spaces as this probably uses simple string parsing - beware!
        _tcscpy(sFileDir, OLE2T(m_Output_FileName.m_str));
        PathRemoveFileSpec(sFileDir);

        hRetVal1 = FindExecutable(OLE2T(m_Output_FileName.m_str), sFileDir, sExeName);

        // setup info to pass to the Windows shell
        ZeroMemory(&seiExecInfo, sizeof(seiExecInfo));
        seiExecInfo.cbSize          = sizeof(seiExecInfo);
        seiExecInfo.fMask          |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_DDEWAIT;
        seiExecInfo.hwnd            = NULL;
        seiExecInfo.lpVerb          = _T("print");
        seiExecInfo.lpFile          = OLE2T(m_Output_FileName.m_str);
        seiExecInfo.lpParameters    = NULL;
        seiExecInfo.lpDirectory     = sFileDir;
        seiExecInfo.nShow           = SW_SHOW;
        seiExecInfo.hInstApp        = hRetVal2;

        // print out through the shell
        ShellExecuteEx(&seiExecInfo);

        // wait for the printing process to finish, typically for the user 
        // to press the OK button on any print confirmations
        //
        // note that this does not work because Internet Explorer spawns the
        // "print" process off as a separate process.
        // Thus, seiExecInfo.hProcess immediately becomes signalled.  This
        // has been left in because the printing process may be handled by
        // another program which does not do printing in a separate process
        // eg WordPad
        //
        // note also that this will work for "open" since the file is opened
        // in the process returned in seiExecInfo.hProcess  This may be useful
        // for doing a print preview...
        //
        // TDE      could also EnumWindows() or EnumChildWindows() to look
        // for a window with "Print" in it's titlebar and keep doing this 
        // until we can't find such a window.  However, there may be more
        // than one such window eg from another app which may also be
        // printing...
        dwWaitRet = WaitForSingleObject(seiExecInfo.hProcess, INFINITE);
        SASSERT(WAIT_OBJECT_0 == dwWaitRet);

        // check for errors
        if ((int ) hRetVal1 > 32 &&
            (int ) hRetVal2 > 32 )
            {
            // no errors, so return
            return S_OK;
            }

        // errors from FindExecutable()
        switch ((int ) hRetVal1)
            {
            case 0:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: The system is out of memory or resources."));
                break;

            case 31:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: There is no association for the specified file type."));
                break;

            case ERROR_FILE_NOT_FOUND:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: The specified file was not found."));
                break;

            case ERROR_PATH_NOT_FOUND:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: The specified path was not found."));
                break;

            case ERROR_BAD_FORMAT:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: The .exe file is invalid (non-Win32 .exe or error in .exe image)."));
                break;

            default :
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("FindExecutable: Unknown error from FindExecutable()"));
                break;
            }// switch FindExecutable()

        // errors from ShellExecute()
        switch ((int ) hRetVal2)
            {
            case 0:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The operating system is out of memory or resources."));
                break;

            // this is the same as SE_ERR_FNF
            case ERROR_FILE_NOT_FOUND:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The specified file was not found."));
                break;

            // this is the same as SE_ERR_PNF
            case ERROR_PATH_NOT_FOUND:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The specified path was not found."));
                break;

            case ERROR_BAD_FORMAT:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The .exe file is invalid (non-Win32® .exe or error in .exe image)."));
                break;

            case SE_ERR_ACCESSDENIED:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The operating system denied access to the specified file."));
                break;

            case SE_ERR_ASSOCINCOMPLETE:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The file name association is incomplete or invalid."));
                break;

            case SE_ERR_DDEBUSY:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The DDE transaction could not be completed because other DDE transactions were being processed."));
                break;

            case SE_ERR_DDEFAIL:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The DDE transaction failed."));
                break;

            case SE_ERR_DDETIMEOUT:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The DDE transaction could not be completed because the request timed out."));
                break;

            case SE_ERR_DLLNOTFOUND:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: The specified dynamic-link library was not found."));
                break;

            case SE_ERR_NOASSOC:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable."));
                break;

            case SE_ERR_OOM:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: There was not enough memory to complete the operation."));
                break;

            case SE_ERR_SHARE:
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: A sharing violation occurred."));
                break;

            default :
                LogEvent(_T ("Error in CXML2XSL::Print: %s"),
                    _T("ShellExecute: Unknown error from ShellExecute()"));
                break;
            }// switch ShellExecute()

        // must be an error if we got to here
        return S_FALSE;
        }
    catch (_com_error   &e)
        {
        LogEvent (_T ("Error in CXML2XSL::Print: %s"),e.ErrorMessage ());

        return E_UNEXPECTED;
        }
    catch (...)
        {
        LogEvent (_T ("Unknown error in CXML2XSL::Print"));

        return E_UNEXPECTED;
        }
}
//------------------------------------------------------------------------
