// Unfrag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "UnfragFile.h"
#include "utils.h"

//------------------------------------------------------------------------
#define UNFRAG_WORKS_TITLE                  "UnfragWorks Server v2.0"
#define UNFRAG_WORKS_TITLE_CODE             "UnfragWorks Server v2.x"
//------------------------------------------------------------------------
void GetCode
(
    char*                   sCode
);

void SecurityAlert
(
    char*                   sCode, 
    char*                   sMachID
);

void Usage();

bool IsSolidWorksFile
(
    char*                   sFileName
);
//------------------------------------------------------------------------
void GetCode
(
    char*                   sCode
)
{
    // read code from UWSV.ini
    GetPrivateProfileString(
        "CU_Security", 
        "code", 
        "default", 
        sCode, 
        MAX_PATH - 1, 
        "uwsv.ini");

    return;
}
//------------------------------------------------------------------------
void SecurityAlert
(
    char*                   sCode, 
    char*                   sMachID
)
{
    printf("UnfragWorks v2.x - commandline utility to unfragment files\n\n");
    printf("    Security code %s is incorrect for machine ID %s\n", sCode, sMachID);
}
//------------------------------------------------------------------------
void Usage()
{
    printf("    UnfragWorks v2.x - commandline utility to unfragment files\n\n");
    printf("    Usage:\n");
    printf("        UnfragWorks.exe [trevorde] [timeout] [filename]\n");
    printf("\n");
    printf("    where:\n");
    printf("        trevorde\n");
    printf("            required string for backwards compatibility\n");
    printf("        timeout\n");
    printf("            time in seconds to wait for file to become free\n");
    printf("        filename\n");
    printf("            fully qualified path to file\n");
    printf("            filenames with spaces must be enclosed in quotes\n");
    printf("\n");
    printf("    examples:\n");
    printf("        UnfragWorks.exe trevorde 1 c:\\Data\\53148425.sldasm\n");
    printf("        UnfragWorks.exe trevorde 5 \"c:\\Data\\Filename With a Space In It.sldasm\"\n");
}
//------------------------------------------------------------------------
bool IsSolidWorksFile
(
    char*                   sFileName
)
{
    // NOTE:  just checks file name and NOT file existence
    char        *sLower = _strlwr(sFileName);

    if ((strstr(sLower, ".prt"   ) != NULL)  ||
        (strstr(sLower, ".sldprt") != NULL)  ||
        (strstr(sLower, ".asm"   ) != NULL)  ||
        (strstr(sLower, ".sldasm") != NULL)  ||
        (strstr(sLower, ".drw"   ) != NULL)  ||
        (strstr(sLower, ".slddrw") != NULL)  )
        {
        return true;
        }
    else
        {
        return false;
        }
}
//---------------------------------------------------------------------------
/*
    argv[0] = program name
    argv[1] = "trevorde"
    argv[2] = timeout in seconds
    argv[3] = filename
*/
int main(int argc, char* argv[])
{
    // make sure that at least one file was specified on the commandline
    if (4 != argc)
        {
        Usage();

        return 0;
        }


    // first check authorisation code
    char            sMachID[MAX_PATH];
    char            sCode  [MAX_PATH];

    GetMachineID(sMachID);
    GetCode(sCode);

    if (false == CheckCode(sMachID, UNFRAG_WORKS_TITLE_CODE, sCode))
        {
        SecurityAlert(sCode, sMachID);

        return 0;
        }


    // try and unfrag file
    int             nTimeOut = atoi(argv[2]);
    char            *sFileName = argv[3];
    int             nBytesSaved = 0;

    // make sure the timeout is a valid conversion from the string
    nTimeOut = (0 >= nTimeOut) ? 1 : nTimeOut;

    if (IsSolidWorksFile(sFileName))
        {
        nBytesSaved = UnfragFile(nTimeOut, sFileName);
        }

    if (nBytesSaved > 0)
        {
        printf("Unfragged %s\nSaved %d bytes\n", sFileName, nBytesSaved);
        }

    return nBytesSaved;
}
//------------------------------------------------------------------------

