/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 05 21:41:07 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_XML_XSL\XML_XSL.idl:
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

#ifndef __XML_XSL_h__
#define __XML_XSL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_XML2XSL_FWD_DEFINED__
#define __IDMS_XML2XSL_FWD_DEFINED__
typedef interface IDMS_XML2XSL IDMS_XML2XSL;
#endif 	/* __IDMS_XML2XSL_FWD_DEFINED__ */


#ifndef __DMS_XML2XSL_FWD_DEFINED__
#define __DMS_XML2XSL_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_XML2XSL DMS_XML2XSL;
#else
typedef struct DMS_XML2XSL DMS_XML2XSL;
#endif /* __cplusplus */

#endif 	/* __DMS_XML2XSL_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDMS_XML2XSL_INTERFACE_DEFINED__
#define __IDMS_XML2XSL_INTERFACE_DEFINED__

/* interface IDMS_XML2XSL */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDMS_XML2XSL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("730AD102-51D3-11D4-8A10-0020AFCC5695")
    IDMS_XML2XSL : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XML_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XML_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XSL_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XSL_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Output_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Output_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Apply_XSL_XML( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_XML2XSLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_XML2XSL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_XML2XSL __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_XML_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_XML_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_XSL_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_XSL_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Output_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Output_FileName )( 
            IDMS_XML2XSL __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply_XSL_XML )( 
            IDMS_XML2XSL __RPC_FAR * This);
        
        END_INTERFACE
    } IDMS_XML2XSLVtbl;

    interface IDMS_XML2XSL
    {
        CONST_VTBL struct IDMS_XML2XSLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_XML2XSL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_XML2XSL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_XML2XSL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_XML2XSL_get_XML_FileName(This,pVal)	\
    (This)->lpVtbl -> get_XML_FileName(This,pVal)

#define IDMS_XML2XSL_put_XML_FileName(This,newVal)	\
    (This)->lpVtbl -> put_XML_FileName(This,newVal)

#define IDMS_XML2XSL_get_XSL_FileName(This,pVal)	\
    (This)->lpVtbl -> get_XSL_FileName(This,pVal)

#define IDMS_XML2XSL_put_XSL_FileName(This,newVal)	\
    (This)->lpVtbl -> put_XSL_FileName(This,newVal)

#define IDMS_XML2XSL_get_Output_FileName(This,pVal)	\
    (This)->lpVtbl -> get_Output_FileName(This,pVal)

#define IDMS_XML2XSL_put_Output_FileName(This,newVal)	\
    (This)->lpVtbl -> put_Output_FileName(This,newVal)

#define IDMS_XML2XSL_Apply_XSL_XML(This)	\
    (This)->lpVtbl -> Apply_XSL_XML(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_get_XML_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDMS_XML2XSL_get_XML_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_put_XML_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDMS_XML2XSL_put_XML_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_get_XSL_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDMS_XML2XSL_get_XSL_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_put_XSL_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDMS_XML2XSL_put_XSL_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_get_Output_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDMS_XML2XSL_get_Output_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_put_Output_FileName_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDMS_XML2XSL_put_Output_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_XML2XSL_Apply_XSL_XML_Proxy( 
    IDMS_XML2XSL __RPC_FAR * This);


void __RPC_STUB IDMS_XML2XSL_Apply_XSL_XML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_XML2XSL_INTERFACE_DEFINED__ */



#ifndef __XML_XSLLib_LIBRARY_DEFINED__
#define __XML_XSLLib_LIBRARY_DEFINED__

/* library XML_XSLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_XML_XSLLib;

EXTERN_C const CLSID CLSID_DMS_XML2XSL;

#ifdef __cplusplus

class DECLSPEC_UUID("730AD103-51D3-11D4-8A10-0020AFCC5695")
DMS_XML2XSL;
#endif
#endif /* __XML_XSLLib_LIBRARY_DEFINED__ */

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
