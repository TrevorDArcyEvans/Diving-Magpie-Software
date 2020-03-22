// DMS_PSWorks.cpp : Implementation of CDMS_PSWorks
#include "stdafx.h"
#include "DMS_PSWks.h"
#include "DMS_PSWorks.h"

#include "SLogError.h"

#include <pkzip/implode.h>

/////////////////////////////////////////////////////////////////////////////
// CDMS_PSWorks


CDMS_PSWorks::CDMS_PSWorks()
{
    ObjectLock(this);
}
//------------------------------------------------------------------------
CDMS_PSWorks::~CDMS_PSWorks()
{
    ObjectLock(this);
}
//------------------------------------------------------------------------
HRESULT CDMS_PSWorks::FinalConstruct()
{
    ObjectLock(this);
    return S_OK;
}
//------------------------------------------------------------------------
HRESULT CDMS_PSWorks::FinalRelease  ()
{
    ObjectLock(this);
    return S_OK;
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
typedef struct
{
   FILE                 *InFile;
   FILE                 *OutFile;
   DWORD                dwCrc;
} IOFILEBLOCK, *PIOFILEBLOCK;
//-------------------------------------------------------------------------
UINT ProcessInBuffer(PCHAR buffer, UINT *iSize, void *pParam)
{
    PIOFILEBLOCK        pFileIOBlock;
    UINT                iRead;

    pFileIOBlock = (PIOFILEBLOCK) pParam;
    iRead = fread( buffer, 1, *iSize, pFileIOBlock->InFile );   // Read data from disk
    if (iRead > 0)
        {
        pFileIOBlock->dwCrc = crc32(buffer, &iRead, &pFileIOBlock->dwCrc);
        }
    return iRead;
}
//-------------------------------------------------------------------------
void ProcessOutBuffer(PCHAR buffer, UINT *iSize, void *pParam)
{
    PIOFILEBLOCK        pFileIOBlock;
    UINT                iWrite;

    pFileIOBlock = (PIOFILEBLOCK) pParam;
    iWrite = fwrite( buffer, 1, *iSize, pFileIOBlock->OutFile );   // Write the data to disk
    if (iWrite > 0)
        {
        pFileIOBlock->dwCrc = crc32(buffer, &iWrite, &pFileIOBlock->dwCrc);
        }
    return;
}
//-------------------------------------------------------------------------
// CDMS_PSWorks::ExtractConfig
//
// parameters
//      sSW_FileName
//          fully qualified path to SolidWorks file,
//          including any file extension
//
//          should be a part file, assembly and drawings do not contain
//          Parasolids info
//
//      sConfigBodyName
//          name of IStream under "Contents" storage to dump
//          this will be soemthing like:
//              Config-0-Body
//              Config-1-Body
//              Config-5-Body
//
//      sParasolid_FileName
//          fully qualified path to Parasolids file to which to dump the
//          specified configuration, including any file extension
//
//      [out] nRetVal
//          return code from the PkZip explode() routine:
//
//          0
//              CMP_NO_ERROR
//          1
//              CMP_INVALID_DICTSIZE
//          2
//              CMP_INVALID_MODE
//          3
//              CMP_BAD_DATA
//          4
//              CMP_ABORT
//
// returns
//      S_OK
//          normally
//
//      E_FAIL
//          some COM error, probably sConfigBodyName not found
//
//      E_UNEXPECTED
//          some C++ exception
//
// notes
//      any existing Parasolids file will be overwritten
STDMETHODIMP CDMS_PSWorks::ExtractConfig
(
    BSTR                sSW_FileName,
    BSTR                sConfigBodyName,
    BSTR                sParasolid_FileName,
    int*                nRetVal
)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    ObjectLock(this);

    HRESULT                 hr = S_OK;
    byte*                   pData = NULL;
    PCHAR                   pScratchPad = NULL;


    TCHAR                   sTempPath    [MAX_PATH];
    TCHAR                   sTempFileName[MAX_PATH];

    // work out where the temporary files are
    GetTempPath(sizeof(sTempPath) / sizeof(TCHAR), sTempPath);

    // form the output file name
    GetTempFileName(sTempPath, _T("PS_Extract_Parasolid"), 0, sTempFileName);

    // remove temp file created by GetTempFileName()
    DeleteFile(sTempFileName);

    try
        {
        USES_CONVERSION;

        CComPtr <IStorage>          pStgRoot;
        CComPtr <IStorage>          pStgContents;
        CComPtr <IStream >          pStmParasolids;
        STATSTG                     StatStg;
        ULONG                       Size = 0;
        ULONG                       BytesRead = 0;

        CFile                       TempFile(sTempFileName,
                                        CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

        char*                       PS_Header = 
                                        "**ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz**************************\n"
                                        "**PARASOLID !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~0123456789**************************\n"
                                        "**PART1;\n"
                                        "MC=x86;\n"
                                        "MC_MODEL=x86 Family 6 Model 5 Stepping 2, GenuineIntel;\n"
                                        "MC_ID=unknown;\n"
                                        "OS=Windows_NT;\n"
                                        "OS_RELEASE=unknown;\n"
                                        "FRU=;\n"
                                        "APPL=;\n"
                                        "SITE=;\n"
                                        "USER=unknown;\n"
                                        "FORMAT=binary;\n"
                                        "GUISE=transmit;\n"
                                        "KEY=cup;\n"
                                        "FILE=;\n"
                                        "DATE=;\n"
                                        "**PART2;\n"
                                        "SCH=;\n"
                                        "USFLD_SIZE=0;\n"
                                        "**PART3;\n"
                                        "**END_OF_HEADER*****************************************************************\n";

        IOFILEBLOCK                 FileInfoParam;


        // open SW file
        STEST_HR(::StgOpenStorage(sSW_FileName,
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                        NULL, 0, &pStgRoot));

        STEST_HR(pStgRoot->OpenStorage(CComBSTR(_T("Contents")),
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
                        NULL, 0, &pStgContents));

        //STEST_HR(pStgContents->OpenStream(CComBSTR(_T("DisplayLists__Zip")),
        STEST_HR(pStgContents->OpenStream(CComBSTR(sConfigBodyName),
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
                        0, &pStmParasolids));

        STEST_HR(pStmParasolids->Stat(&StatStg, STATFLAG_DEFAULT));

        Size = StatStg.cbSize.LowPart;
        SASSERT(0 == StatStg.cbSize.HighPart);

        pData = new byte [Size];
        SASSERT(NULL != pData);

        // read in Parasolid info
        STEST_HR(pStmParasolids->Read(pData, Size, &BytesRead));
        SASSERT(Size == BytesRead);

        // write out to our temporary file
        TempFile.Write(pData, Size);
        TempFile.Close();



        // start preprocess
        FileInfoParam.dwCrc     = ~((DWORD)0);  // Pre-condition CRC
        FileInfoParam.InFile    = NULL;
        FileInfoParam.OutFile   = NULL;

        FileInfoParam.InFile    = _tfopen(sTempFileName, _T("r+b"));
        FileInfoParam.OutFile   = _tfopen(OLE2T(sParasolid_FileName), _T("w+b"));

        // first 4 bytes are not Parasolids data, so skip these
        fseek(FileInfoParam.InFile, 4L, SEEK_SET);

        fwrite(PS_Header, sizeof(char), strlen(PS_Header), FileInfoParam.OutFile);
        // end preprocess


        // allocate the memory block for the scratch pad
        pScratchPad = (PCHAR ) new char[EXP_BUFFER_SIZE];
        SASSERT(NULL != pScratchPad);

        // decompress and write out to target file
        *nRetVal = explode(ProcessInBuffer, ProcessOutBuffer,
                        pScratchPad, &FileInfoParam);


        // start postprocess
        fclose(FileInfoParam.InFile );
        fclose(FileInfoParam.OutFile);
        // end postprocess
        }
    catch (_com_error& e)
        {
        hr = E_FAIL;
        LogEvent(_T("COM Error in CDMS_PSWorks::ExtractConfig: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        LogEvent(_T("C++ Error in CDMS_PSWorks::ExtractConfig"));
        }

    // cleanup after ourselves
    DeleteFile(sTempFileName);

    delete [] pScratchPad;
    delete [] pData;

    return hr;
}
//------------------------------------------------------------------------
// CDMS_PSWorks::GetConfigList
//
// parameters
//      sSW_FileName
//          fully qualified path to SolidWorks file,
//          including any file extension
//
//      [out] sConfigList
//          receives a comma separated list of the Config-n-Body names
//          the list will be something like:
//              "Config-0-Body,Config-1-Body,Config-7-Body,Config-5-Body"
//
// returns
//      S_OK
//          normally
//
//      E_FAIL
//          some COM error
//
//      E_UNEXPECTED
//          some C++ exception
STDMETHODIMP CDMS_PSWorks::GetConfigList
(
    BSTR                sSW_FileName,
    BSTR*               sConfigList
)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    ObjectLock(this);

    HRESULT                 hr = S_OK;

    try
        {
        USES_CONVERSION;

        CComPtr <IStorage>          pStgRoot;
        CComPtr <IStorage>          pStgContents;
        CComPtr <IEnumSTATSTG>      pEnum;
        CComPtr <IStream >          pStmParasolids;
        STATSTG                     StatStg;
        CComBSTR                    sTempStr;
        CString                     ConfigBodyName;
        bool                        bFirstTime = true;


        // open SW file
        STEST_HR(::StgOpenStorage(sSW_FileName,
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                        NULL, 0, &pStgRoot));

        STEST_HR(pStgRoot->OpenStorage(CComBSTR(_T("Contents")),
                        NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
                        NULL, 0, &pStgContents));

        STEST_HR(pStgContents->EnumElements(0, NULL, 0, &pEnum));

        while (NOERROR == pEnum->Next(1, &StatStg, NULL))
            {
            if (STGTY_STREAM == StatStg.type)
                {
                ConfigBodyName = StatStg.pwcsName;
                if (-1 != ConfigBodyName.Find(_T("-Body")))
                    {
                    if (true == bFirstTime)
                        {
                        // don't put a comma at the end of the string the 
                        // first time through since there are no configs yet
                        bFirstTime = false;
                         }
                    else
                        {
                        sTempStr.Append(_T(","));
                        }
                    sTempStr.Append(ConfigBodyName);
                    }
                }
            CoTaskMemFree(StatStg.pwcsName);
            }

        sTempStr.CopyTo(sConfigList);
        }
    catch (_com_error& e)
        {
        hr = E_FAIL;
        LogEvent(_T("COM Error in CDMS_PSWorks::GetConfigList: %s"), e.ErrorMessage());
        }
    catch (...)
        {
        hr = E_UNEXPECTED;
        LogEvent(_T("C++ Error in CDMS_PSWorks::GetConfigList"));
        }

    return hr;
}
//------------------------------------------------------------------------
