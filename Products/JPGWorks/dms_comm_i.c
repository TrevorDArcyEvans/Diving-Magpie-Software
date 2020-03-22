/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 22 21:10:48 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_Common\DMS_Comm.idl:
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

const IID LIBID_DMS_Comm = {0xFC99C7B2,0x4A88,0x11D4,{0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const IID IID_IDMS_Common = {0xFC99C7B3,0x4A88,0x11D4,{0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const CLSID CLSID_DMS_Common = {0xFC99C7B5,0x4A88,0x11D4,{0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95}};


#ifdef __cplusplus
}
#endif

