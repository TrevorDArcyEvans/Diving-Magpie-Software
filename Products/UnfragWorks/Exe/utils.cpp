//---------------------------------------------------------------------------
#include "stdafx.h"

#include "crc_32.h"
#include "utils.h"
//---------------------------------------------------------------------------
void GetMachineID
(
    char*                   sMachID
)
/* ------------------------------------------------
returns unique machine ID, in a character string,
from hard disk serial number
------------------------------------------------ */
{
    unsigned long           CRC32;
    long                    CharCnt;

    // determine machine ID hard disk serial number:
    DWORD                   dwVolumeSerialNumber = 0;

    GetVolumeInformation(
        _T("C:\\"),        // address of root directory of the file system
        NULL,     // address of name of the volume
        NULL,         // length of lpVolumeNameBuffer
        &dwVolumeSerialNumber,  // address of volume serial number
        NULL,   // address of system's maximum filename length
        NULL,     // address of file system flags
        NULL, // address of name of file system
        NULL    // length of lpFileSystemNameBuffer
        );
 
    sprintf(sMachID, "%d", dwVolumeSerialNumber);

    // calculate 32 bit CRC value
    crc32string(&CRC32, &CharCnt, sMachID);

    sprintf(sMachID, "%x", CRC32);

    return;
}
//---------------------------------------------------------------------------
unsigned long   CalculateCode
(
    char*                   Machine_ID ,
    char*                   Prod       
)
/* ------------------------------------------------
returns security code based on machine ID and product

NOTE:   1) case of Machine_ID is very important
------------------------------------------------ */
{
    unsigned long                   CRC32;
    long                            CharCnt;
    char                            TempStr[MAX_PATH];

    // get machine ID
    strcpy(TempStr, Machine_ID);

    // add product name
    strcat(TempStr, Prod);

    // calculate 32 bit CRC value
    crc32string(&CRC32,&CharCnt, TempStr);

    return CRC32;
}
//---------------------------------------------------------------------------
bool            CheckCode
(
    char*                   Machine_ID ,
    char*                   Prod       ,
    char*                   Code       
)
/* ------------------------------------------------
checks for valid security code based on machine ID and product

NOTE:   1) case of Machine_ID is very important
------------------------------------------------ */
{
    char            TempStr[MAX_PATH];

    sprintf(TempStr, "%x", CalculateCode(Machine_ID, Prod));

    if (strcmp(TempStr, Code) == 0)
        {
        return true;
        }
    else
        {
        return false;
        }
}
//---------------------------------------------------------------------------
