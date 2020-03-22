/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Aug 12 11:31:50 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_WinError\DMS_WinError.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DMS_WinError_h__
#define __DMS_WinError_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_WinErrorMsg_FWD_DEFINED__
#define __IDMS_WinErrorMsg_FWD_DEFINED__
typedef interface IDMS_WinErrorMsg IDMS_WinErrorMsg;
#endif 	/* __IDMS_WinErrorMsg_FWD_DEFINED__ */


#ifndef __DMS_WinErrorMsg_FWD_DEFINED__
#define __DMS_WinErrorMsg_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_WinErrorMsg DMS_WinErrorMsg;
#else
typedef struct DMS_WinErrorMsg DMS_WinErrorMsg;
#endif /* __cplusplus */

#endif 	/* __DMS_WinErrorMsg_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDMS_WinErrorMsg_INTERFACE_DEFINED__
#define __IDMS_WinErrorMsg_INTERFACE_DEFINED__

/* interface IDMS_WinErrorMsg */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDMS_WinErrorMsg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E5F7DEF-702F-11D4-8E3C-0020AFCC5695")
    IDMS_WinErrorMsg : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetErrorString( 
            int nErrorCode,
            BSTR __RPC_FAR *sErrorString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_WinErrorMsgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_WinErrorMsg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_WinErrorMsg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_WinErrorMsg __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorString )( 
            IDMS_WinErrorMsg __RPC_FAR * This,
            int nErrorCode,
            BSTR __RPC_FAR *sErrorString);
        
        END_INTERFACE
    } IDMS_WinErrorMsgVtbl;

    interface IDMS_WinErrorMsg
    {
        CONST_VTBL struct IDMS_WinErrorMsgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_WinErrorMsg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_WinErrorMsg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_WinErrorMsg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_WinErrorMsg_GetErrorString(This,nErrorCode,sErrorString)	\
    (This)->lpVtbl -> GetErrorString(This,nErrorCode,sErrorString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_WinErrorMsg_GetErrorString_Proxy( 
    IDMS_WinErrorMsg __RPC_FAR * This,
    int nErrorCode,
    BSTR __RPC_FAR *sErrorString);


void __RPC_STUB IDMS_WinErrorMsg_GetErrorString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_WinErrorMsg_INTERFACE_DEFINED__ */



#ifndef __DMS_WINERRORLib_LIBRARY_DEFINED__
#define __DMS_WINERRORLib_LIBRARY_DEFINED__

/* library DMS_WINERRORLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DMS_WINERRORLib;

EXTERN_C const CLSID CLSID_DMS_WinErrorMsg;

#ifdef __cplusplus

class DECLSPEC_UUID("0E5F7DF0-702F-11D4-8E3C-0020AFCC5695")
DMS_WinErrorMsg;
#endif
#endif /* __DMS_WINERRORLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
