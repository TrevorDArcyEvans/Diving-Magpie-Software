// XGL_InflateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XGL_Inflate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/**********************
ZLib Defines
***********************/
#define ZLIB_VERSION "1.1.3"

#define inflateInit(strm) \
        inflateInit_((strm),                ZLIB_VERSION, sizeof(z_stream))

#define Z_NO_FLUSH      0
#define Z_PARTIAL_FLUSH 1 /* will be removed, use Z_SYNC_FLUSH instead */
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4
/* Allowed flush values; see deflate() below for details */

#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)
/* Return codes for the compression/decompression functions. Negative
 * values are errors, positive values are used for special but normal events.
 */

#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION  (-1)
/* compression levels */

#define Z_FILTERED            1
#define Z_HUFFMAN_ONLY        2
#define Z_DEFAULT_STRATEGY    0
/* compression strategy; see deflateInit2() below for details */

#define Z_BINARY   0
#define Z_ASCII    1
#define Z_UNKNOWN  2
/* Possible values of the data_type field */

#define Z_DEFLATED   8
/* The deflate compression method (the only one supported in this version) */

#define Z_NULL  0  /* for initializing zalloc, zfree, opaque */

typedef unsigned char  Byte;  /* 8 bits */
typedef unsigned int   uInt;  /* 16 bits or more */
typedef unsigned long  uLong; /* 32 bits or more */
typedef Byte  Bytef;
typedef char  charf;
typedef int   intf;
typedef uInt  uIntf;
typedef uLong uLongf;
typedef void	*voidpf;
typedef void    *voidp;

typedef voidpf (*alloc_func) (voidpf opaque, uInt items, uInt size);
typedef void   (*free_func)  (voidpf opaque, voidpf address);

typedef struct z_stream_s {
    Bytef    *next_in;  /* next input byte */
    uInt     avail_in;  /* number of bytes available at next_in */
    uLong    total_in;  /* total nb of input bytes read so far */

    Bytef    *next_out; /* next output byte should be put there */
    uInt     avail_out; /* remaining free space at next_out */
    uLong    total_out; /* total nb of bytes output so far */

    char     *msg;      /* last error message, NULL if no error */
    struct internal_state *state; /* not visible by applications */

    alloc_func zalloc;  /* used to allocate the internal state */
    free_func  zfree;   /* used to free the internal state */
    voidpf     opaque;  /* private data object passed to zalloc and zfree */

    int     data_type;  /* best guess about the data type: ascii or binary */
    uLong   adler;      /* adler32 value of the uncompressed data */
    uLong   reserved;   /* reserved for future use */
} z_stream;

int (__stdcall *inflateInit_) (z_stream *strm, const char *version, int stream_size);
int (__stdcall *inflate) (z_stream *strm, int flush);
int (__stdcall *inflateEnd) (z_stream *strm);


/************************
End ZLib Stuff
*************************/


//------------------------------------------------------------------------
// Inflate_Zlib_File
// uncompresses a zlib compressed file, typically a zgl file
//
// parameters
//      Input_FileName
//          fully qualifed name to compressed (zgl) file
//          including any file extension
//
//      Output_FileName
//          fully qualifed name to output (xgl) file
//          including any file extension
//
//      ErrorString
//          holds error message, if there was an error, see below
//
//          should be at least 2*MAX_PATH characters long since the 
//          file name is included in the error message
//
// returns
//      0
//          if successful
//
//      1
//          could not open .zgl file
//
//      2
//          could not load zlib.dll
//
//      3
//          error reading .zgl file
//
//      4
//          error creating .xgl file
//
//      5
//          error writing .xgl file
//
// notes
//      requires zlib.dll to be accessible along the usual dll load path
int
Inflate_Zlib_File
(
    const TCHAR*            Input_FileName,
    const TCHAR*            Output_FileName,
    TCHAR*                  ErrorString
)
{
    USES_CONVERSION;

    int                         nRetVal = 0;
    int                         done;
    char                        uncompressed[65536];
    DWORD                       len;
    int                         result;
    char                        Buf[BUFSIZ];
    DWORD                       NumWritten = 0;

    HANDLE                      ZGL_handle = INVALID_HANDLE_VALUE;
    HANDLE                      XGL_handle = INVALID_HANDLE_VALUE;
    HINSTANCE                   dllHandle = NULL;
    z_stream                    zStream;


    ZGL_handle = CreateFile(Input_FileName,
                    GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_SEQUENTIAL_SCAN,
                    NULL);

    XGL_handle = CreateFile(Output_FileName,
                    GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                    CREATE_ALWAYS,
                    FILE_FLAG_SEQUENTIAL_SCAN,
                    NULL);

    if (ZGL_handle == INVALID_HANDLE_VALUE  ||
        XGL_handle == INVALID_HANDLE_VALUE  )
        {
        if (ZGL_handle == INVALID_HANDLE_VALUE)
            {
            _stprintf(ErrorString, _T("Could not open input file %s."), Input_FileName);
            nRetVal = 1;
            }

        if (XGL_handle == INVALID_HANDLE_VALUE)
            {
            _stprintf(ErrorString, _T("Could not create output file %s"), Output_FileName);
            nRetVal = 4;
            }
        }
    else
        {
        dllHandle = LoadLibrary(_T("ZLib"));
        if (dllHandle == NULL)
            {
            _tcscpy(ErrorString, _T("Can't load zlib.dll"));
            nRetVal = 2;
            }
        else
            {
            //find the functions we'll need from the dll
            *((int*) &inflateInit_)     = (int) GetProcAddress(dllHandle, "inflateInit_");
            *((int*) &inflate)          = (int) GetProcAddress(dllHandle, "inflate"     );
            *((int*) &inflateEnd)       = (int) GetProcAddress(dllHandle, "inflateEnd"  );

            zStream.opaque      = Z_NULL;
            zStream.zalloc      = Z_NULL;
            zStream.zfree       = Z_NULL;
            zStream.avail_in    = 0;
            zStream.next_in     = Z_NULL;

            inflateInit(&zStream);

            do
                {
                if (ReadFile(ZGL_handle, Buf, sizeof(Buf), &len, NULL) == 0)
                    {
                    _stprintf(ErrorString, _T("Error reading input file %s."), Input_FileName);
                    done = 1;
                    nRetVal = 3;
                    }
                else
                    {
                    done = len < sizeof(Buf);
                    zStream.avail_in = len;
                    zStream.next_in = (unsigned char*) Buf;
                    while (1)
                        {
                        zStream.avail_out = sizeof(uncompressed);
                        zStream.next_out  = (unsigned char*) uncompressed;

                        result = inflate(&zStream, Z_NO_FLUSH);

                        if (zStream.avail_out != sizeof(uncompressed))
                            {
                            if (!WriteFile(XGL_handle,
                                    uncompressed,
                                    sizeof(uncompressed) - zStream.avail_out,
                                    &NumWritten,
                                    NULL))
                                {
                                _stprintf(ErrorString, _T("Error writing output file %s."), Output_FileName);
                                done = 1;
                                nRetVal = 5;
                                break;
                                }
                            }

                        if (result == Z_STREAM_END)
                            {
                            done = 1;
                            break;
                            }

                        if (zStream.avail_out != 0)
                            break;
                        }//while(1)
                    }//else
                } while (!done);
            FreeLibrary(dllHandle);
            }
        CloseHandle(ZGL_handle);
        CloseHandle(XGL_handle);
        }

    return nRetVal;
}
//------------------------------------------------------------------------
