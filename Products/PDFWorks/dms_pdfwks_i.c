/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Nov 05 15:14:43 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_PDFWorks\DMS_PDFWks.idl:
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

const IID LIBID_DMS_PDFWks = {0xB147E1AA,0x33C6,0x11D4,{0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const CLSID CLSID_DMS_PDFWorks = {0xB147E1AD,0x33C6,0x11D4,{0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const IID IID_IDMS_PDFWorks = {0xB147E1AB,0x33C6,0x11D4,{0x89,0xE8,0x00,0x20,0xAF,0xCC,0x56,0x95}};


#ifdef __cplusplus
}
#endif

