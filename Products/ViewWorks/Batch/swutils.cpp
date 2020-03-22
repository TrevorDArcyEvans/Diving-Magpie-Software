//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include "about.h"
#include "CodeGen.h"
#include "crc_32.h"
#include "main.h"
#include "SWutils.h"
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool IsSolidWorksFile(String  strFileName)
{
// NOTE:  just checks file name and NOT file existence
if ((strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".prt"   ) != NULL)  ||
    (strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".sldprt") != NULL)  ||
    (strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".asm"   ) != NULL)  ||
    (strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".sldasm") != NULL)  ||
    (strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".drw"   ) != NULL)  ||
    (strstr(::AnsiString(strFileName.LowerCase()).c_str(), ".slddrw") != NULL)  )
    {
    return true;
    }
else
    {
    return false;
    }
}
//---------------------------------------------------------------------------

