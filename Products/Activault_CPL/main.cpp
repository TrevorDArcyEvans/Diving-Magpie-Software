//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\registry.hpp>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "zipbuilder"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
TRegistry   *AppReg = NULL;

// assume running on W95 - conservative
bool    bIsNT = false;

OSVERSIONINFO       osv;
osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
if (GetVersionEx(&osv))
    {
    String      WindowsPlatform;
    // note: szCSDVersion =  service pack  release
    String  ServiceRelease = osv.szCSDVersion;

    switch (osv.dwPlatformId)
        {
        case    VER_PLATFORM_WIN32s: //Win32s on Windows 3.1.
                    WindowsPlatform = "Microsoft® Windows 3.1(TM)";
                    bIsNT = false;
                    break;

        case    VER_PLATFORM_WIN32_WINDOWS: //WIN32 on 95 or 98
                    //determine if Win95 or Win98
                    if (osv.dwMinorVersion == 0)
                        {
                        WindowsPlatform = "Microsoft® Windows 95(TM) " + ServiceRelease;
                        }
                    else
                        {
                        WindowsPlatform = "Microsoft® Windows 98(TM) " + ServiceRelease;
                        }
                    bIsNT = false;
                    break;

        case    VER_PLATFORM_WIN32_NT: //Win32 on Windows NT.
                    WindowsPlatform = "Microsoft® Windows NT(TM) "  + ServiceRelease;
                    bIsNT = true;

                    break;

        default:
                    bIsNT = false;
                    MessageBox(NULL, "Failed to get correct Operating System.",
                        Application->Title.c_str(), MB_OK);
        } //end switch
    } //end if

if (true == bIsNT)
    {
    m_bSvrRunningFile = false;
    m_bSvrRunningDB   = false;
    }
else
    {
    MessageBox(NULL, "This program requires Windows NT.",
        Application->Title.c_str(), MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
    Application->Terminate();
    }



// get DB file name
//      [HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBC.INI\ActivaultVM]
//      "DBQ"="C:\\Program Files\\Activault\\Database\\AgileVM.mdb"
lblDBName->Caption = "";

AppReg = new TRegistry;
AppReg->RootKey = HKEY_LOCAL_MACHINE;
if (AppReg->OpenKey("SOFTWARE\\ODBC\\ODBC.INI\\ActivaultVM", false) == true)
    {
    try
        {
        lblDBName->Caption = AppReg->ReadString("DBQ");
        }
    catch(...)
        {
        }
    }
delete AppReg;


// get DB file size
lblDBSize->Caption = "";
bool        bDBServiceRunningOnEntry = true;
if (1 == AV_ServiceRunning(AV_DATABASE_MGR))
    {
    AV_ServiceStop(AV_DATABASE_MGR);
    }
else
    {
    bDBServiceRunningOnEntry = false;
    }

DWORD       dwSize;
HANDLE      hFile;

hFile = CreateFile(lblDBName->Caption.c_str(),
            0,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

if (INVALID_HANDLE_VALUE == hFile)
    {
    lblDBSize->Caption = "Error: could not open Activault database";
    return;
    }

dwSize = GetFileSize(hFile, NULL) ;
// If we failed ...
if (dwSize == 0xFFFFFFFF)
    {
    // Obtain the error code.
    lblDBSize->Caption = "Error: " + ::String(GetLastError());
    } // End of error handler
else
    {
    String      strTempStr;
    lblDBSize->Caption = strTempStr.FormatFloat(AV_STR_FORMAT, dwSize) + " bytes";
    }

CloseHandle(hFile);
if (true == bDBServiceRunningOnEntry)
    {
    if (false == AV_ServiceStart(AV_DATABASE_MGR))
        {
        // ugly hack to restart service if we couldn't start
        // it the first time around
        #define     AV_TIMEOUT      1000

        Sleep(AV_TIMEOUT);
        AV_ServiceStart(AV_DATABASE_MGR);
        }
    }

// get vault directories
//      [HKEY_LOCAL_MACHINE\SOFTWARE\SolidPartners\Activault\FileServer]
//      "StorDirs"="C:\\Program Files\\Activault\\ActivaultFileMgr\\Files;c:\temp"
String      strStorDirs;
AppReg = new TRegistry;
AppReg->RootKey = HKEY_LOCAL_MACHINE;
if (AppReg->OpenKey("SOFTWARE\\SolidPartners\\Activault\\FileServer", false) == true)
    {
    cboVaultDir->Items->Clear();
    try
        {
        strStorDirs = AppReg->ReadString("StorDirs");
        }
    catch(...)
        {
        }
    }
delete AppReg;

// put each storage dir into ddl box
char    *p = (char *) strStorDirs.c_str();
char    TempStr[MAX_PATH];
int     i = 0;

TempStr[0] = '\0';

while (*p != '\0')
    {
    while(*p != ';' && *p != '\0')
        {
        TempStr[i++] = *p;
        p++;
        }
    TempStr[i] = '\0';
    cboVaultDir->Items->Insert(cboVaultDir->Items->Count, TempStr);
    if (*p == '\0')
        {
        break;
        }
    p++;
    i = 0;
    }



cboVaultDir->Items->Clear();

int     nDelimiterPos = strStorDirs.AnsiPos(';');

if (0 == nDelimiterPos && strStorDirs.Length() > 0)
    {
    cboVaultDir->Items->Add(strStorDirs);
    }
else
    {
    while (nDelimiterPos > 0)
        {
        cboVaultDir->Items->Add(strStorDirs.SubString(0, nDelimiterPos - 1));

        strStorDirs = strStorDirs.SubString(nDelimiterPos + 1,
                        strStorDirs.Length() - nDelimiterPos + 1);
        nDelimiterPos = strStorDirs.AnsiPos(';');
        }
    if (strStorDirs.Length() > 0)
        {
        cboVaultDir->Items->Add(strStorDirs);
        }
    }


// get Preview directories
//  [HKEY_LOCAL_MACHINE\SOFTWARE\SolidPartners\Activault\FileServer\Previews]
//
//  [HKEY_LOCAL_MACHINE\SOFTWARE\SolidPartners\Activault\FileServer\Previews\bmp]
//  @="RSDeriveBMP.RSDeriveBMPMaker.1"
//  "Path"="C:\\Program Files\\SolidPartners\\Activault\\Data\\Previews\\bmp"
//  "Width"="400"
//
//  [HKEY_LOCAL_MACHINE\SOFTWARE\SolidPartners\Activault\FileServer\Previews\jpeg]
//  @="RSDeriveBMP.RSDeriveBMPMaker.1"
//  "Path"="C:\\Program Files\\SolidPartners\\Activault\\Data\\Previews\\jpeg"
//  "Width"="400"
AppReg = new TRegistry;
AppReg->RootKey = HKEY_LOCAL_MACHINE;
TStringList     *strPreviewDirs = new TStringList;
String          strPreviewPath;
const String    strPreviewKey = "SOFTWARE\\SolidPartners\\Activault\\FileServer\\Previews";
if (AppReg->OpenKey(strPreviewKey, false) == true)
    {
    try
        {
        AppReg->GetKeyNames(strPreviewDirs);
        AppReg->CloseKey();

        for (int i = 0; i < strPreviewDirs->Count; i++)
            {
            AppReg->OpenKey(strPreviewKey + "\\" + strPreviewDirs->Strings[i], false);
            strPreviewPath = AppReg->ReadString("Path");
            cboVaultDir->Items->Add(strPreviewPath);
            AppReg->CloseKey();
            }
        }
    catch(...)
        {
        }
    }
delete strPreviewDirs;
delete AppReg;


cboVaultDir->ItemIndex = 0;
cboVaultDirChange(Sender);


// get file server status
m_bSvrRunningFile = AV_ServiceRunning(AV_FILE_MGR);
lblSvrStatFile->Caption = (true == m_bSvrRunningFile) ? AV_STR_STARTED : AV_STR_STOPPED;

// get DB server status
m_bSvrRunningDB = AV_ServiceRunning(AV_DATABASE_MGR);
lblSvrStatDB->Caption = (true == m_bSvrRunningDB) ? AV_STR_STARTED : AV_STR_STOPPED;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSvrFileClick(TObject *Sender)
{
if (true == m_bSvrRunningFile)
    {
    m_bSvrRunningFile = !AV_ServiceStop(AV_FILE_MGR);
    }
else
    {
    m_bSvrRunningFile = AV_ServiceStart(AV_FILE_MGR);
    }

lblSvrStatFile->Caption = (true == m_bSvrRunningFile) ? AV_STR_STARTED : AV_STR_STOPPED;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSvrDBClick(TObject *Sender)
{
if (true == m_bSvrRunningDB)
    {
    m_bSvrRunningDB = !AV_ServiceStop(AV_DATABASE_MGR);
    }
else
    {
    m_bSvrRunningDB = AV_ServiceStart(AV_DATABASE_MGR);
    }

lblSvrStatDB->Caption = (true == m_bSvrRunningDB) ? AV_STR_STARTED : AV_STR_STOPPED;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cboVaultDirChange(TObject *Sender)
{
int     nSize       = 0,
        nFileCount  = 0;

AV_StorageDirScan(cboVaultDir->Items->Strings[cboVaultDir->ItemIndex].c_str(),
    &nSize, &nFileCount);
lblVaultsize->Caption  = lblVaultsize-> Caption.FormatFloat(AV_STR_FORMAT, nSize) + " bytes";
lblVaultCount->Caption = lblVaultCount->Caption.FormatFloat(AV_STR_FORMAT, nFileCount);
}
//---------------------------------------------------------------------------
int TfrmMain::AV_ServiceRunning(char *pcServiceName)
// returns:
//      1   if named service is running
//      0   if the service is not running
//     -1   if there was a problem
{
int                 nRetval = -1;
SC_HANDLE           schService;
SC_HANDLE           schSCManager;
SERVICE_STATUS      ServiceStatus;

schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
if (schSCManager)
    {
    schService = OpenService(schSCManager, pcServiceName, SERVICE_ALL_ACCESS);
    if (schService)
        {
        if (!QueryServiceStatus(schService, &ServiceStatus))
            {
            nRetval = -1;
            }
        else
            {
            if (SERVICE_RUNNING == ServiceStatus.dwCurrentState)
                {
                nRetval = 1;
                }

            if (SERVICE_STOPPED     == ServiceStatus.dwCurrentState)
                {
                nRetval = 0;
                }
            }
        CloseServiceHandle(schService);
        }
    CloseServiceHandle(schSCManager);
    }

return nRetval;
}
//---------------------------------------------------------------------------
int TfrmMain::AV_ServiceStart    (char *pcServiceName)
// returns:
//      1   if started service successfully
//      0   if could not start service
{
SC_HANDLE           schService;
SC_HANDLE           schSCManager;

int                 nRetVal = 0;

schSCManager = OpenSCManager(
                    NULL,                   // machine (NULL == local)
                    NULL,                   // database (NULL == default)
                    SC_MANAGER_ALL_ACCESS   // access required
                    );
if (schSCManager)
    {
    schService = OpenService(schSCManager, pcServiceName, SERVICE_ALL_ACCESS);

    if (schService)
        {
        // try to start the service
        if (StartService(schService, 0, NULL))
            {
            nRetVal = 1;
            }
        CloseServiceHandle(schService);
        }
    CloseServiceHandle(schSCManager);
    }

return nRetVal;
}
//---------------------------------------------------------------------------
int TfrmMain::AV_ServiceStop     (char *pcServiceName)
// returns:
//      1   if stopped service successfully
//      0   if could not stop service
{
SC_HANDLE           schService;
SC_HANDLE           schSCManager;

SERVICE_STATUS      ssStatus;       // current status of the service

int                 nRetVal = 0;

schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
if (schSCManager)
    {
    schService = OpenService(schSCManager, pcServiceName, SERVICE_ALL_ACCESS);
    if (schService)
        {
        // try to stop the service
        if (ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
            {
            nRetVal = 1;
            }
        CloseServiceHandle(schService);
        }
    CloseServiceHandle(schSCManager);
    }

return nRetVal;
}
//---------------------------------------------------------------------------
int TfrmMain::AV_StorageDirScan(char *pcDirName, int *Size, int *FileCount)
{
String      strFileSpec = ::String(pcDirName) + ::String("\\*.*");

WIN32_FIND_DATA         fd;
HANDLE hFind = FindFirstFile(strFileSpec.c_str(), &fd);

if (hFind != INVALID_HANDLE_VALUE)
    {
    *Size      = 0;
    *FileCount = 0;

    do
        {
        if (!(fd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
            FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM |
            FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_TEMPORARY)))
            {
            *Size += fd.nFileSizeLow;
            (*FileCount)++;
            }
        } while (FindNextFile(hFind, &fd));
    FindClose(hFind);
    }

return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormKeyDown(TObject *Sender, WORD &Key,
                    TShiftState Shift)
{
if (VK_ESCAPE == Key)
    {
    Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBackupClick(TObject *Sender)
{
    String              sBackupDir;
    String              sBackupFileName;
    String              sFileExt;
    String              sTempStr;
    String              sMsg;
    int                 i = 0;

    sBackupDir = ExtractFileDir(lblDBName->Caption) + "\\Backup";
    sFileExt   = ExtractFileExt(lblDBName->Caption);

    if (false == CreateDir(sBackupDir))
        {
        sMsg = "Could not create backup directory\n    " + sBackupDir;
        MessageBox(NULL, sMsg.c_str(), "Activault", MB_OK);
        return;
        }

    sBackupFileName = sBackupDir + "\\" + ExtractFileName(lblDBName->Caption);

    // remove extension
    sBackupFileName.SetLength(sBackupFileName.Length() - sFileExt.Length());

    do
        {
        sTempStr = sBackupFileName + ::String(i) + ".zip";
        i++;
        } while(FileExists(sTempStr));
    sBackupFileName = sTempStr;

    TCursor         Save_Cursor = Screen->Cursor;
    Screen->Cursor = crHourGlass;    // Show hourglass cursor

    try
        {
        ZipBuilder->Load_Zip_Dll();

        ZipBuilder->FSpecArgs->Add(lblDBName->Caption);
        ZipBuilder->ZipFileName = sBackupFileName;
        ZipBuilder->Add();

        ZipBuilder->Unload_Zip_Dll();
        }
    __finally
        {
        Screen->Cursor = Save_Cursor; // always restore the cursor
        }

    sMsg = "Database backed up to:\n    " + sBackupFileName;
    MessageBox(NULL, sMsg.c_str(), "Activault", MB_OK);
}
//---------------------------------------------------------------------------

