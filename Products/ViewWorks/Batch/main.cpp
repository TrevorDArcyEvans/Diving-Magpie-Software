//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Windows.h>
#include <ObjBase.h>
#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#define        MAIN    1

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "main.h"
#include "SWutils.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Regi1632"
#pragma link "Dropper"
#pragma resource "*.dfm"
TfrmViewWorks *frmViewWorks;
//---------------------------------------------------------------------------
__fastcall TfrmViewWorks::TfrmViewWorks(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::FormCreate(TObject *Sender)
{
char            MachineID[MAX_PATH];
AnsiString      CodeStr;

Application->Title = VIEW_WORKS_TITLE;
frmViewWorks->Caption = Application->Title;

bRegistered = false;

// initialise CurrFileName to hold list of files
CurrFileName = '\0';

strcpy(MachineID, GetMachineID());
CodeStr = regSettings->ReadString("Security", "code");

if (CheckCode(MachineID, VIEW_WORKS_TITLE_CODE, CodeStr.c_str()) == true)
    {
    // security passed, enable options
    mnuRegister->Enabled = false;
    bRegistered = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::btnAddClick(TObject *Sender)
{
if (dlgOpen->Execute() == true)
    {
    int i = 0;
    for (i = 0; i < dlgOpen->Files->Count; i++)
        {
        if (true == IsSolidWorksFile(dlgOpen->Files->Strings[i]))
            {
            lbxList->Items->Add(dlgOpen->Files->Strings[i]);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::btnRemoveClick(TObject *Sender)
{
int i = 0, Curr = 0;

TStringList    *Items;

if (lbxList->SelCount >= 1)
    {
    Items = new TStringList();
    Items->AddStrings(lbxList->Items);

    for (i = 0; i < lbxList->Items->Count; i++)
        {
        if (lbxList->Selected[i] == true)
            {
            Items->Delete(i - Curr);
            Curr++;
            }
        }
    lbxList->Items->Clear();
    lbxList->Items->AddStrings(Items);
    delete Items;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuOpenClick(TObject *Sender)
{
if (dlgOpenFileName->Execute() == true)
    {
    CurrFileName = dlgOpenFileName->FileName;

    // update app & form titles with filename
    Application->Title = ::String(VIEW_WORKS_TITLE) + ::String(" - ") + ::String(CurrFileName);
    frmViewWorks->Caption = Application->Title;

    // TO DO:   manually catch exceptions on trying to load strings from file
    //          this is done by the default RTL handler at the moment
    lbxList->Items->LoadFromFile(CurrFileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuSaveClick(TObject *Sender)
{
// if no filename, then get one
if (true == CurrFileName.IsEmpty()  ||
    0 == CurrFileName.AnsiCompare(""))
    {
    mnuSaveAsClick(Sender);
    }
else
    {
    // update app & form titles with filename
    Application->Title = ::String(VIEW_WORKS_TITLE) + ::String(" - ") + ::String(CurrFileName);
    frmViewWorks->Caption = Application->Title;

    // if a valid file name and some files to save
    if (lbxList->Items->Count >= 1)
        {
        lbxList->Items->SaveToFile(CurrFileName);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuSaveAsClick(TObject *Sender)
{
// get a valid file name and save the file
if (dlgSaveFileName->Execute() == true)
    {
    CurrFileName = dlgSaveFileName->FileName;
    mnuSaveClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuRegisterClick(TObject *Sender)
{
frmCodeGen->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuContentsClick(TObject *Sender)
{
WinExec(
    AnsiString::AnsiString(
        AnsiString::AnsiString("winhlp32 ") +
        Application->HelpFile).c_str(),
        SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::mnuAboutClick(TObject *Sender)
{
frmAbout->Caption                     = VIEW_WORKS_TITLE;
frmAbout->lblProductName->Caption     = "Product Name:   " + ::String(VIEW_WORKS_TITLE);
frmAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::FileDropperDrop(TObject *Sender,
      AnsiString Filename)
{
if (true == IsSolidWorksFile(Filename))
    {
    lbxList->Items->Add(Filename);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::btnConvertClick(TObject *Sender)
{
// maximum number of conversions for the unregistered version
#define        MAX_DOC            5

if (0 == lbxList->Items->Count)
    {
    return;
    }

// for each file in the list
int     i = 0;
for (i = 0; i < lbxList->Items->Count; i++)
    {
    if (i > MAX_DOC && bRegistered == false) break;

    if (true == IsSolidWorksFile(lbxList->Items->Strings[i]))
        {
        String      astrModFileName     = lbxList->Items->Strings[i],
                    astrTempModFileName = astrModFileName;


        int         nStartExtn = astrTempModFileName.Length() - 5;
        astrTempModFileName[nStartExtn + 0] = 'v';
        astrTempModFileName[nStartExtn + 1] = 'e';
        astrTempModFileName[nStartExtn + 2] = 'w';

        // overwrite existing files - a safe bet ;-)
        if (0 != CopyFile(astrModFileName.c_str(), astrTempModFileName.c_str(), FALSE))
            {
            VW_MakeViewFile (astrTempModFileName.c_str());
            VW_UnfragFile   (1, astrTempModFileName.c_str());
            }
        }
    }

String      strTemp = ::String("Finished - converted ") +
                        ::String(i) +
                        ::String(" files");
Application->MessageBox(strTemp.c_str(), Application->Title.c_str(), MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall     TfrmViewWorks::VW_MakeViewFile(
                            char     *pcSWFileName)
{
// save time stamp of file
HANDLE          hFile = NULL;
FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
BOOL            bRetVal = FALSE;

if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcSWFileName,
                GENERIC_READ, 0, NULL,
                OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }


IStorage*       pRoot;
IStorage*       pContents;

if (S_OK == StgOpenStorage(::WideString(pcSWFileName).c_bstr(), NULL,
                STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                NULL, 0, &pRoot))
    {
    pRoot->DestroyElement(::WideString("Header"     ).c_bstr());
    pRoot->DestroyElement(::WideString("ThirdPty"   ).c_bstr());
    pRoot->DestroyElement(::WideString("Embedding 1").c_bstr());

    // ugly hack to remove the "SummaryInformation" and
    // "DocumentSummaryInformation" elements
    // I think these element names are in Unicode :-(
    IEnumSTATSTG*   pEnum;
    IMalloc*        pMalloc;
    STATSTG         statstg;

    CoGetMalloc(MEMCTX_TASK, &pMalloc);
    pRoot->EnumElements(0, NULL, 0, &pEnum);

    while (pEnum->Next(1, &statstg, NULL) == NOERROR)
        {
        if (statstg.type == STGTY_STREAM)
            {
            if (NULL != strstr(::String(statstg.pwcsName).c_str(), "SummaryInformation"))
                {
                pRoot->DestroyElement(statstg.pwcsName);
                }
            }
        pMalloc->Free(statstg.pwcsName);
        }
    pMalloc->Release();
    pEnum->Release();

    if (S_OK == pRoot->OpenStorage(::WideString("Contents"), NULL,
        STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &pContents))
        {
        if (NULL != pContents)
            {
            pContents->DestroyElement(::WideString("Config-0"           ).c_bstr());
            pContents->DestroyElement(::WideString("CMgr"               ).c_bstr());
            pContents->DestroyElement(::WideString("OleItems"           ).c_bstr());
            pContents->DestroyElement(::WideString("Config-33"          ).c_bstr());
            pContents->DestroyElement(::WideString("Definition"         ).c_bstr());
            pContents->DestroyElement(::WideString("Config-33-Body__Zip").c_bstr());

            pContents->Release();
            }
        }

    pRoot->Release();
    }


// restore time stamp of file
if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcSWFileName,
                GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
    {
    bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
    CloseHandle(hFile);
    }

return;
}
//---------------------------------------------------------------------------
int __fastcall      TfrmViewWorks::VW_UnfragFile(
                            int     nTimeOut,
                            char    *pcFileName)
{
BSTR    bstrFileName = ::WideString(pcFileName).c_bstr();

HANDLE          hFile = NULL;
FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
BOOL            bRetVal = FALSE;

if (S_OK == StgIsStorageFile(bstrFileName))
    {
    TCHAR   pcPathName      [_MAX_PATH],
            pcTempFileName  [_MAX_PATH];

    // get a temporary file name
    GetTempPath(_MAX_PATH, pcPathName);
    GetTempFileName(pcPathName, "tde", 0, pcTempFileName);

    // open file for reading
    IStorage* pIn;

    HRESULT hr;

    int nCount = 0;

    // loop forever
    for(;;)
        {
        hr = ::StgOpenStorage(bstrFileName, NULL,
                        STGM_DIRECT | STGM_READ | STGM_SHARE_DENY_WRITE,
                        NULL, 0, &pIn);

        // until file becomes free or we timeout
        if (hr != S_OK && nCount < nTimeOut)
            {
            Sleep(1000);
            nCount++;
            }
        else
            {
            break;
            }
        }
    if (FAILED(hr)) { _tremove(pcTempFileName); return 0; }

    IStorage* pOut;

    hr = ::StgCreateDocfile(::WideString(pcTempFileName).c_bstr(),
                STGM_DIRECT | STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
                0, &pOut);
    if (FAILED(hr)) { pIn->Release(); return 0; }

    hr = pIn->CopyTo(0, NULL, NULL, pOut);
    if (FAILED(hr)) { pIn->Release(); pOut->Release(); return 0; }

    pIn ->Release();
    pOut->Release();

    struct stat     sTempFileName, sFileName;

    if (0 != _tstat(pcTempFileName, &sTempFileName)) { _tremove(pcTempFileName); }
    if (0 != _stat (pcFileName    , &sFileName    )) { _tremove(pcTempFileName); }

    if (sTempFileName.st_size < sFileName.st_size)
        {
        HANDLE          hFile = NULL;
        FILETIME        ftCreationTime, ftLastAccessTime, ftLastWriteTime;
        BOOL            bRetVal = FALSE;

        if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                        GENERIC_READ, 0, NULL,
                        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL)))
            {
            bRetVal = GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
            CloseHandle(hFile);
            }

        remove(pcFileName);
        rename(pcTempFileName, pcFileName);

        if (INVALID_HANDLE_VALUE != (hFile = CreateFile(pcFileName,
                        GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
            {
            bRetVal = SetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
            CloseHandle(hFile);
            }
        }
    else
        {
        _tremove(pcTempFileName);
        }

    return 1;
    }

return 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewWorks::lbxListKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
// insert key
if (45 == Key)
    {
    btnAddClick(Sender);
    }

// delete key
if (46 == Key)
    {
    btnRemoveClick(Sender);
    }
}
//---------------------------------------------------------------------------

