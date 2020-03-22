/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 05 21:41:07 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_XML_XSL\XML_XSL.idl:
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

const IID IID_IDMS_XML2XSL = {0x730AD102,0x51D3,0x11D4,{0x8A,0x10,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const IID LIBID_XML_XSLLib = {0x730AD0F6,0x51D3,0x11D4,{0x8A,0x10,0x00,0x20,0xAF,0xCC,0x56,0x95}};


const CLSID CLSID_DMS_XML2XSL = {0x730AD103,0x51D3,0x11D4,{0x8A,0x10,0x00,0x20,0xAF,0xCC,0x56,0x95}};


#ifdef __cplusplus
}
#endif

