/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 25 21:38:55 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_ProgPipe\DMS_ProgPipe.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_ProgPipe = {0x66DDC6D0,0xAA5D,0x11D4,{0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C}};


const IID IID_IDMS_ProgPipe = {0x66DDC6D1,0xAA5D,0x11D4,{0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C}};


const CLSID CLSID_DMS_ProgPipe = {0x66DDC6D3,0xAA5D,0x11D4,{0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C}};


#ifdef __cplusplus
}
#endif

