/*
 Example header file
*/
#ifndef _BUNWKS_ZIP_H
#define _BUNWKS_ZIP_H

#include <windows.h>
#include <assert.h>    /* required for all Windows applications */
#include <stdlib.h>
#include <stdio.h>
#include <commdlg.h>
#include <dlgs.h>
#include <windowsx.h>

#include "api.h"
#include "structs.h"

/* Defines */
#ifndef MSWIN
#define MSWIN
#endif

/* global functions ************************************* */

int WINAPI          BunWks_ZipPassword(
                        char            *p      ,
                        int             n       ,
                        const char      *m      ,
                        const char      *name   );

int WINAPI          BunWks_ZipPrint(
                        char far        *buf    ,
                        unsigned long   size    );

char far * WINAPI   BunWks_ZipComment(
                        char far        *szBuf  );

int                 BunWks_ZipFile(
                        char            *pcZipFileName  ,
                        char            *pcFileToAdd    ,
                        BOOL            bSaveDirInfo    );


/****************************************************************************/

#endif /* _BUNWKS_ZIP_H */

