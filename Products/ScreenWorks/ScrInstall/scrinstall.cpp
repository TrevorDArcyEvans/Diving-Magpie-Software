// ScrInstall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 


int main(int argc, char* argv[])
{
TCHAR       cWinDir[MAX_PATH], cSysDir[MAX_PATH], cToFileName[MAX_PATH];
BYTE        bScrHotsPath[MAX_PATH];

HKEY        hScrHots;

if (!GetWindowsDirectory(cWinDir, sizeof(cWinDir) / sizeof(TCHAR)))
    {
    return 0;
    }

if (!GetSystemDirectory(cSysDir, sizeof(cSysDir) / sizeof(TCHAR)))
    {
    return 0;
    }

// copy ScreenWorks ini file to Windows directory
_stprintf(cToFileName, "%s\\ScrWorks.ini", cWinDir);
if (!CopyFile("ScrWorks.ini", cToFileName, FALSE))
    {
    return 0;
    }

// copy ScreenWorks bmp file to System directory
_stprintf(cToFileName, "%s\\ScrWorks.bmp", cSysDir);
if (!CopyFile("ScrWorks.bmp", cToFileName, FALSE))
    {
    return 0;
    }


//[HKEY_CLASSES_ROOT\CLSID\{9CB48109-E0FC-11D0-8E0C-C52523886C3B}\InProcServer32]
//@="C:\\WINDOWS\\SCRHOTS.DLL"
_mbscpy(bScrHotsPath, (const unsigned char * ) cWinDir);
_mbscat(bScrHotsPath, (const unsigned char * ) "\\ScrHots.dll");

if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CLASSES_ROOT,
        "CLSID\\{9CB48109-E0FC-11D0-8E0C-C52523886C3B}\\InProcServer32",
        0, KEY_ALL_ACCESS, &hScrHots))
    {
    return 0;
    }

RegSetValueEx(hScrHots,
    NULL, 0,
    REG_SZ, bScrHotsPath, sizeof(bScrHotsPath) / sizeof(BYTE));
RegCloseKey(hScrHots);


// run the screen hotspot installation dialog
TCHAR            cCurrDir [MAX_PATH];

GetCurrentDirectory(MAX_PATH, cCurrDir);

SetCurrentDirectory(cWinDir);
system("rundll32 ScrHots.dll,RunInstallDialog");

SetCurrentDirectory(cCurrDir);

return 1;
}
