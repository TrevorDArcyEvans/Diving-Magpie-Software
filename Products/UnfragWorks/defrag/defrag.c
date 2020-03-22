//====================================================================
//
// Defrag.c
//
// Copyright (C) 1997 Mark Russinovich
//
// This program demonstrates the use of NT 4.0 FAT and NTFS cluster
// movement File System Control functions.
//
//====================================================================
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "defrag.h"

//--------------------------------------------------------------------
//                         D E F I N E S
//--------------------------------------------------------------------

//
// Interval at which output is paused (in lines)
//
#define PAUSEINTERVAL    24

//
// Size of the buffer we read file mapping information into.
// The buffer is big enough to hold the 16 bytes that 
// come back at the head of the buffer (the number of entries 
// and the starting virtual cluster), as well as 512 pairs
// of [virtual cluster, logical cluster] pairs.
//
#define    FILEMAPSIZE        (512+2)

//
// Size of the bitmap buffer we pass in. Its large enough to
// hold information for the 16-byte header that's returned
// plus the indicated number of bytes, each of which has 8 bits 
// (imagine that!)
//
#define BITMAPBYTES        4096
#define BITMAPSIZE        (BITMAPBYTES+2*sizeof(ULONGLONG))

//
// Invalid longlong number
//
#define LLINVALID        ((ULONGLONG) -1)

//--------------------------------------------------------------------
//                        G L O B A L S
//--------------------------------------------------------------------

//
// Handle for the raw volume that was opened
//
HANDLE       VolumeHandle;

//
// Buffer to read file mapping information into
//
ULONGLONG    FileMap[ FILEMAPSIZE ];

//
// Buffer thats passed to bitmap function
//
BYTE         BitMap[ BITMAPSIZE ];

//
// Bit shifting array for efficient processing of the bitmap
//
BYTE         BitShift[] = { 1, 2, 4, 8, 16, 32, 64, 128 };


//--------------------------------------------------------------------
//                      F U N C T I O N S
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//
// PrintNtError
//
// Translates an NTDLL error code into its text equivalent. This
// only deals with ones commonly returned by defragmenting FS Control
// commands.
//--------------------------------------------------------------------
void PrintNtError(NTSTATUS Status)
{
    switch (Status)
        {
        case STATUS_SUCCESS:
            printf("STATUS_SUCCESS\n\n");
            break;

        case STATUS_INVALID_PARAMETER:
            printf("STATUS_INVALID_PARAMETER\n\n");
            break;

        case STATUS_BUFFER_TOO_SMALL:
            printf("STATUS_BUFFER_TOO_SMALL\n\n");
            break;

        case STATUS_ALREADY_COMMITTED:
            printf("STATUS_ALREADY_COMMITTED\n\n");
            break;

        case STATUS_INVALID_DEVICE_REQUEST:
            printf("STATUS_INVALID_DEVICE_REQUEST\n\n");
            break;

        default:
            printf("0x%08x\n\n", Status );
            break;
        }
}


//--------------------------------------------------------------------
//
// PrintWin32Error
// 
// Translates a Win32 error into a text equivalent
//
//--------------------------------------------------------------------
void PrintWin32Error( DWORD ErrorCode )
{
    LPVOID lpMsgBuf;
 
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL, ErrorCode, 
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR) &lpMsgBuf, 0, NULL);
    printf("%s\n", lpMsgBuf);
    LocalFree( lpMsgBuf );
}


//--------------------------------------------------------------------
//
// PrintHelp
//
//--------------------------------------------------------------------
void PrintHelp()
{
    printf("\nCommands:\n\n");
    printf("Dump bitmap free clusters:\n");
    printf("     b [offset]\n");
    printf("Enumerate clusters of file:\n");
    printf("     n [filename]\n");
    printf("Move clusters:\n");
    printf("     m [file] [off] [tgt] [numclust]\n");
    printf("Quit:\n");
    printf("     q\n");
    printf("\n");
}

//--------------------------------------------------------------------
//
// PauseOutput
//
// After n lines have printed, stop and wait for the user to continue.
// 'q' causes the function to return false.
//
//--------------------------------------------------------------------
BOOL PauseOutput(DWORD Count)
{
    char    key;

    if (!(Count % PAUSEINTERVAL))
        {
        printf("more ('q' to quit): "); 
        fflush(stdout);
        key = getch();
        printf("\n");
        if (key == 'q')
            {
            printf("\nEnumeration aborted.\n\n");
            return FALSE;
            }
        }
    return TRUE;
}


//--------------------------------------------------------------------
//
// OpenVolume
//
// Open the volume for defragging, a flag that is new for NT 4.0.
//
//--------------------------------------------------------------------
DWORD OpenVolume( int DriveId ) 
{
    static char            volumeName[] = "\\\\.\\A:";

    //
    // open the volume
    //
    volumeName[4] = DriveId + 'A'; 
    VolumeHandle = CreateFile( volumeName, GENERIC_READ, 
                    FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
                    0, 0 );
    if (VolumeHandle == INVALID_HANDLE_VALUE)
        {
        return GetLastError();
        }

    return ERROR_SUCCESS;
}


//--------------------------------------------------------------------
//
// DumpBitmap
//
// Start at the offset specified (if any) and dumps all the free
// clusters on the volume to the end of the volume or until
// the user stops the dump with a 'q'.
//
//--------------------------------------------------------------------
void DumpBitmap( char *argument )
{
    DWORD                    status;
    PBITMAP_DESCRIPTOR       bitMappings;
    ULONGLONG                cluster;
    ULONGLONG                numFree;
    ULONGLONG                startLcn;
    ULONGLONG                nextLcn;
    ULONGLONG                lastLcn;
    IO_STATUS_BLOCK          ioStatus;
    ULONGLONG                i;
    int                      lines;

    //
    // Start scanning at the cluster offset the user specifies
    //
    bitMappings = (PBITMAP_DESCRIPTOR) BitMap;
    cluster = 0;
    nextLcn = 0;
    lines = 0;
    lastLcn = LLINVALID;
    sscanf(argument, " %I64d ", &nextLcn);
    while (!(status = NtFsControlFile( VolumeHandle, NULL, NULL, 0, &ioStatus,
                        FSCTL_GET_VOLUME_BITMAP,
                        &nextLcn, sizeof( cluster ),
                        bitMappings, BITMAPSIZE )) ||
             status == STATUS_BUFFER_OVERFLOW ||
             status == STATUS_PENDING )
        {
        // 
        // If the operation is pending, wait for it to finish
        //
        if( status == STATUS_PENDING )
            {
            WaitForSingleObject( VolumeHandle, INFINITE );

            //
            // Get the status from the status block
            //
            if (ioStatus.Status != STATUS_SUCCESS && 
                ioStatus.Status != STATUS_BUFFER_OVERFLOW )
                {
                printf("\nGet Volume Bitmap: ");
                PrintNtError( ioStatus.Status );
                return;
                }
            }

        //
        // Print the range we're starting at
        //
        if (!lines)
            {
            printf("\nFree clusters starting at offset: %I64d\n", 
                        bitMappings->StartLcn );
            }

        //
        // Scan through the returned bitmap info, looking for empty clusters
        //
        startLcn = bitMappings->StartLcn;
        numFree = 0;
        cluster = LLINVALID;
        for (i = 0; i < min( bitMappings->ClustersToEndOfVol, 8*BITMAPBYTES); i++ )
            {
            if (!(bitMappings->Map[ i/8 ] & BitShift[ i % 8 ]))
                {
                //
                // Cluster is free
                //
                if (cluster == LLINVALID )
                    {
                    cluster = startLcn + i;
                    numFree = 1;
                    }
                else
                    {
                    numFree++;
                    }
                }
            else
                {
                //
                // Cluster is not free
                //
                if (cluster != LLINVALID )
                    {
                    if (lastLcn == cluster )
                        {
                        lastLcn = LLINVALID;
                        }
                    else
                        {
                        //
                        // See if we should continue
                        //
                        if (!PauseOutput( ++lines ))
                            {
                            return;
                            }

                        printf("   LCN: %I64d LEN: %I64d\n", cluster, numFree );
                        numFree = 0;
                        lastLcn = cluster;
                        cluster = LLINVALID;
                        }
                    } 
                }
            }

        //
        // See if we should continue
        //
        if (!PauseOutput( ++lines ))
            {
            return;
            }

        //
        // Print any remaining
        //
        if (cluster != LLINVALID && lastLcn != cluster )
            {
            printf("   LCN: %I64d LEN: %I64d\n", cluster, numFree );
            numFree = 0;
            cluster = LLINVALID;
            }

        //
        // End of volume?
        //
        if (status != STATUS_BUFFER_OVERFLOW)
            {
            printf("End of volume.\n\n");
            return;
            }

        //
        // Move to the next block
        //
        nextLcn = bitMappings->StartLcn + i;
        }

    //
    // We only get here when there's an error
    //
    printf("\nGet Volume Bitmap: ");
    PrintNtError(status);
}


//--------------------------------------------------------------------
//
// DumpFile
//
// Dumps the clusters belonging to the specified file until the
// end of the file or the user stops the dump.
//
//--------------------------------------------------------------------
void DumpFile(int drive, char *argument)
{
    DWORD                       status;
    int                         i;
    HANDLE                      sourceFile;
    char                        fileName[MAX_PATH];
    IO_STATUS_BLOCK             ioStatus;
    ULONGLONG                   startVcn;
    PGET_RETRIEVAL_DESCRIPTOR   fileMappings;
    int                         lines = 0;

    //
    // Make the name into a real pathname
    //
    if (strlen( argument ) > 1 && argument[0] != '\\' &&
        argument[0] != 'A'+drive &&
        argument[0] != 'a'+drive ) 
        sprintf(fileName, "%C:\\%s", drive+'A', argument );
    else if (strlen( argument ) > 1 && argument[0] == '\\')
        sprintf(fileName, "%C:%s", drive+'A', argument );
    else
        strcpy(fileName, argument );

    printf("\nClusters for file: %s\n", fileName );

    //
    // Open the file
    //
    sourceFile = CreateFile( fileName, GENERIC_READ, 
                    FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
                    FILE_FLAG_NO_BUFFERING, 0 );
    if (sourceFile == INVALID_HANDLE_VALUE )
        {
        printf("Failed to open file: ");
        PrintWin32Error( GetLastError() );
        return;
        }

    //
    // Start dumping the mapping information. Go until we hit the end of the
    // file.
    //
    startVcn = 0;
    fileMappings = (PGET_RETRIEVAL_DESCRIPTOR) FileMap;
    while (!(status = NtFsControlFile( sourceFile, NULL, NULL, 0, &ioStatus,
                        FSCTL_GET_RETRIEVAL_POINTERS,
                        &startVcn, sizeof( startVcn ),
                        fileMappings, FILEMAPSIZE * sizeof(LARGE_INTEGER) ) ) ||
             status == STATUS_BUFFER_OVERFLOW ||
             status == STATUS_PENDING )
        {
        // 
        // If the operation is pending, wait for it to finish
        //
        if (status == STATUS_PENDING)
            {
            WaitForSingleObject(sourceFile, INFINITE);

            //
            // Get the status from the status block
            //
            if (ioStatus.Status != STATUS_SUCCESS && 
                ioStatus.Status != STATUS_BUFFER_OVERFLOW )
                {
                printf("Enumerate file clusters: ");
                PrintNtError( ioStatus.Status );
                return;
                }
            }

        //
        // Loop through the buffer of number/cluster pairs, printing them
        // out.
        //
        startVcn = fileMappings->StartVcn;
        for (i = 0; i < (ULONGLONG) fileMappings->NumberOfPairs; i++)
            {
            //
            // See if we should continue
            //
            if (!PauseOutput(++lines))
                {
                return;
                }

            //
            // On NT 4.0, a compressed virtual run (0-filled) is 
            // identified with a cluster offset of -1
            //
            if (fileMappings->Pair[i].Lcn == LLINVALID )
                {
                printf("   VCN: %I64d VIRTUAL LEN: %I64d\n",
                            startVcn, fileMappings->Pair[i].Vcn - startVcn );
                }
            else
                {
                printf("   VCN: %I64d LCN: %I64d LEN: %I64d\n",
                            startVcn, fileMappings->Pair[i].Lcn,
                            fileMappings->Pair[i].Vcn - startVcn);
                }
            startVcn = fileMappings->Pair[i].Vcn;
            }

        //
        // If the buffer wasn't overflowed, then we're done
        //
        if (!status)
            break;
        }
    CloseHandle( sourceFile );

    //
    // Print any error code
    //
    printf("Enumerate file clusters: ");
    PrintNtError( status );
}

//--------------------------------------------------------------------
//
// MoveClusterUsage
//
// Prints the syntax of the demonstration program's move file command.
//
//--------------------------------------------------------------------
void MoveClusterUsage()
{
    printf("\nMove File's syntax is:\n   m [filename] [fileoffset] [target] [numclusters]\n\n");
    printf("Example:\n   m c:\\foo\\bar 5 3455 10\n");
    printf("   c:\\foo\\bar       File to move\n");
    printf("   5                Start offset (in clusters) of the cluster in file to move\n");
    printf("   3455             Target cluster on drive\n");
    printf("   10               Number of clusters to move\n");
    printf("\n   This would direct 10 clusters, starting at offset 5 clusters\n"
        "   in the file, to be moved to logical cluster 3455 on the volume.\n\n");
    return;
}

//--------------------------------------------------------------------
//
// MoveCluster
//
// This uses the FSCT_MOVE_FILE interface to move the clusters of a
// file specified by the user as arguments. MoveFile requires a 
// file handle, an offset within the file, the number of sectors of
// the file to move, and the target cluster on the drive to move the
// clusters to.
//
//--------------------------------------------------------------------
void MoveCluster(int drive, char *argument)
{
    DWORD                       status;
    IO_STATUS_BLOCK             ioStatus;
    char                        *argptr;
    HANDLE                      sourceFile;
    char                        fileName[MAX_PATH];
    LARGE_INTEGER               startVcn, targetLcn;
    DWORD                       numClusters;
    MOVEFILE_DESCRIPTOR         moveFile;

    //
    // First, we have to extract the file name
    //
    argptr = argument;
    while (*argptr && *argptr != ' ' )
        argptr++;

    if (!*argptr )
        {
        MoveClusterUsage();
        return; 
        }

    //
    // Make the name into a real pathname
    //
    *argptr = 0;
    if (strlen( argument ) > 1 && argument[0] != '\\' &&
        argument[0] != 'A'+drive &&
        argument[0] != 'a'+drive ) 
        sprintf(fileName, "%C:\\%s", drive+'A', argument );
    else if( strlen( argument ) > 1 && argument[0] == '\\')
        sprintf(fileName, "%C:%s", drive+'A', argument );
    else
        strcpy(fileName, argument );

    // 
    // Get numeric parameters
    //
    argument = argptr+1;
    if (sscanf(argument, " %I64d %I64d %d ", &startVcn, &targetLcn, &numClusters ) != 3)
        {
        MoveClusterUsage();
        return;
        }

    //
    // Tell user what we're going to try
    //
    printf("\nMoving file %s:\n", fileName );
    printf("   Start Offset: %I64d\n", startVcn );
    printf("   Number of Clusters: %d\n", numClusters );
    printf("   Target Cluster: %I64d\n", targetLcn );

    //
    // Open the file
    //
    sourceFile = CreateFile(fileName, GENERIC_READ, 
                    FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                    FILE_FLAG_NO_BUFFERING, 0 );
    if (sourceFile == INVALID_HANDLE_VALUE )
        {
        printf("Failed to open file: ");
        PrintWin32Error(GetLastError());
        return;
        }

    //
    // Setup movefile descriptor and make the call
    //
    moveFile.FileHandle = sourceFile;
    moveFile.StartVcn = startVcn;
    moveFile.TargetLcn = targetLcn;
    moveFile.NumVcns = numClusters;

    status = NtFsControlFile(VolumeHandle, NULL, NULL, 0, &ioStatus,
                        FSCTL_MOVE_FILE,
                        &moveFile, sizeof( moveFile ),
                        NULL, 0 );

    // 
    // If the operation is pending, wait for it to finish
    //
    if (status == STATUS_PENDING )
        {
        WaitForSingleObject( sourceFile, INFINITE );
        status = ioStatus.Status;
        }

    //
    // Print status
    //
    printf("Move cluster status: ");
    PrintNtError(status);
}

//--------------------------------------------------------------------
//
// ExtractCommand
//
// Given a command line, searches for 1 character command, and then
// returns a pointer to first non-whitespace following.
//
//--------------------------------------------------------------------
char ExtractCommand(char *command, char **argument)
{
    char    cmdChar;

    //
    // Look for the command character
    //
    while (*command && *command == ' ')
        command++;

    if (!*command)
        return (char) 0;

    cmdChar = *command;

    command++;

    //
    // Now look for argument
    //
    while (*command && *command == ' ' )
        command++;
    *argument = command;

    return cmdChar;
}


//--------------------------------------------------------------------
//
// main
//
// Process simple commands for enumerating the clusters of a file,
// reading the volume bitmap, and moving a cluster of a particular 
// file.
//
//--------------------------------------------------------------------
int main(int argc, char *argv[])
{
    DWORD                       status;
    int                         drive;
    char                        command[256];
    char                        *argument;
    char                        cmdChar;

    //
    // Get the drive to open off the command line
    //
    if (argc != 2)
        {
        printf("Usage: %s <drive letter>\n", argv[0] );
        exit(1);
        }

    printf("\nNT 4.0 Defragmentation Demonstration Program V1.0\n");
    printf("Copyright (C) 1997 Mark Russinovich\n");
    printf("http://www.ntinternals.com\n\n");

    if (argv[1][0] >= 'a' && argv[1][0] <= 'z' )
        {
        drive = argv[1][0] - 'a';
    } else if( argv[1][0] >= 'A' && argv[1][0] <= 'Z' )
        {
        drive = argv[1][0] - 'A';
    } else if( argv[1][0] == '/' )
        {
        printf("Usage: %s <drive letter>\n", argv[0] );
        exit(1);
    } else
        {
        printf("illegal drive: %c\n", argv[1][0] );
        exit(1);
    }

    //
    // Get the NtFsControlFile entry point
    //
    if (!(NtFsControlFile = (void *) GetProcAddress( GetModuleHandle("ntdll.dll"),
            "NtFsControlFile" )) )
        {
        printf("Could not find NtFsControlFile entry point in NTDLL.DLL\n");
        exit(1);
        }

    //
    // Open the volume
    //
    printf("Opening volume: %c\n", drive+'A' );
    status = OpenVolume(drive);
    printf("Open status: ");
    PrintWin32Error( status );
    if (status != ERROR_SUCCESS )
        {
        printf("Exiting.\n");
        exit(0);
        }

    //
    // Get commands 
    //
    printf("Enter commands ('?' for help):\n\n");
    while (1)
        {
        printf(": ");
        fflush(stdout );
        gets( command );

        cmdChar = ExtractCommand( command, &argument );

        switch (cmdChar)
            {

        //
        // Dump bitmap information
        //
        case 'b':
        case 'B':
            DumpBitmap( argument );
            break;

        //
        // Help
        //
        case '?':
        case 'H':
        case 'h':
            PrintHelp();
            break;

        //
        // Move Cluster
        //
        case 'm':
        case 'M':
            MoveCluster( drive, argument );
            break;

        //
        // Get cluster map for file specified by name
        //
        case 'N':
        case 'n':
            DumpFile( drive, argument );
            break;

        //
        // Quit
        //
        case 'Q':
        case 'q':
            printf("\nQuiting\n");
            exit(0);
            break;

        case 0:
            break;

        default:
            printf("\nInvalid command\n\n");
            break;
        }
    }

    return 0;
}
DEFRAG.C	7 of 13

