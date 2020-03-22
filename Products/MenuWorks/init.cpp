// pre-compiled headers
#include "stdafx.h"


#include "MenuWorks.h"
#include "SldWorks.h"
#include "About.h"
#include "ExampleApp.h"
#include "init.h"
#include "register.h"
#include "WinUtil.h"
#include "utils.h"

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------
void    MW_Init(void)
{

    g_bRegistered = false;
    g_nMaxMenus = MENU_WORKS_MIN_MENUS;

    #define     MENU_WORKS_DEFAULT_MENU_NAME    "&MenuWorks"

	_tcscpy(g_MainMenuName, _T(MENU_WORKS_DEFAULT_MENU_NAME));


    _TCHAR   CodeUStr[_MAX_PATH];
    char    CodeStr [_MAX_PATH];

    GetPrivateProfileString(
            MENU_WORKS_INI_FILE_SECTION,
            MENU_WORKS_INI_FILE_KEY,
            _T("SolidPartners"), // points to default string
            CodeUStr, // points to destination buffer
            _MAX_PATH,        // size of destination buffer
            MENU_WORKS_INI_FILE_NAME);

    wu_strcpy(CodeStr, ::CString(CodeUStr));

    char    MachineID[_MAX_PATH];
    strcpy(MachineID, GetMachineID());

    if (CheckCode(MachineID, (char *) MENU_WORKS_TITLE_CODE, CodeStr) == true)
        {
        // disable menu item
        g_bRegistered = true;

        g_nMaxMenus = MENU_WORKS_MAX_MENUS;

        // main menu item name
        GetPrivateProfileString(
            MENU_WORKS_MAIN, MENU_WORKS_MAIN_TITLE,
            _T(MENU_WORKS_DEFAULT_MENU_NAME), g_MainMenuName, sizeof(g_MainMenuName),
            MENU_WORKS_INI_FILE_NAME);
        }

    // initialise all the menu strings
    for (int i = 0; i < g_nMaxMenus; i++)
        {
        _TCHAR    MenuSectionName[512];
        _stprintf(MenuSectionName, _T("CU_Program%d"), i);

        // program name
        GetPrivateProfileString(
            MenuSectionName, _T("Prog_Name"),
            _T("\0"), MenuItem[i].ProgName, sizeof(MenuItem[i].ProgName),
            MENU_WORKS_INI_FILE_NAME);

        // menu text
        GetPrivateProfileString(
            MenuSectionName, _T("Menu_Text"),
            _T("\0"), MenuItem[i].MenuText, sizeof(MenuItem[i].MenuText),
            MENU_WORKS_INI_FILE_NAME);

        if (true == g_bRegistered)
            {
            // hint text
            GetPrivateProfileString(
                MenuSectionName, _T("Hint_Text"),
                _T("\0"), MenuItem[i].HintText, sizeof(MenuItem[i].HintText),
                MENU_WORKS_INI_FILE_NAME);
            }
        }

    if (false == g_bRegistered)
        {
        MW_About();
        }
}
//-----------------------------------------------------
