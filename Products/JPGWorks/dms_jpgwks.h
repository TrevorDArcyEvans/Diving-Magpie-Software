/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 22 21:10:47 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_JPGWks\DMS_JPGWks.idl:
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

#ifndef __DMS_JPGWks_h__
#define __DMS_JPGWks_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_JPGWorks_FWD_DEFINED__
#define __IDMS_JPGWorks_FWD_DEFINED__
typedef interface IDMS_JPGWorks IDMS_JPGWorks;
#endif 	/* __IDMS_JPGWorks_FWD_DEFINED__ */


#ifndef __DMS_JPGWorks_FWD_DEFINED__
#define __DMS_JPGWorks_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_JPGWorks DMS_JPGWorks;
#else
typedef struct DMS_JPGWorks DMS_JPGWorks;
#endif /* __cplusplus */

#endif 	/* __DMS_JPGWorks_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DMS_JPGWks_LIBRARY_DEFINED__
#define __DMS_JPGWks_LIBRARY_DEFINED__

/* library DMS_JPGWks */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_DMS_JPGWks,0x49F6D445,0xD82F,0x11D4,0x8E,0x9E,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifndef __IDMS_JPGWorks_INTERFACE_DEFINED__
#define __IDMS_JPGWorks_INTERFACE_DEFINED__

/* interface IDMS_JPGWorks */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_JPGWorks,0x49F6D446,0xD82F,0x11D4,0x8E,0x9E,0x00,0x20,0xAF,0xCC,0x56,0x95);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49F6D446-D82F-11D4-8E9E-0020AFCC5695")
    IDMS_JPGWorks : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall SaveAsJPEG( 
            /* [in] */ BSTR FileName,
            /* [in] */ long Handle) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Configure( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_JPGWorksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_JPGWorks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_JPGWorks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *SaveAsJPEG )( 
            IDMS_JPGWorks __RPC_FAR * This,
            /* [in] */ BSTR FileName,
            /* [in] */ long Handle);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Configure )( 
            IDMS_JPGWorks __RPC_FAR * This);
        
        END_INTERFACE
    } IDMS_JPGWorksVtbl;

    interface IDMS_JPGWorks
    {
        CONST_VTBL struct IDMS_JPGWorksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_JPGWorks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_JPGWorks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_JPGWorks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_JPGWorks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_JPGWorks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_JPGWorks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_JPGWorks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_JPGWorks_SaveAsJPEG(This,FileName,Handle)	\
    (This)->lpVtbl -> SaveAsJPEG(This,FileName,Handle)

#define IDMS_JPGWorks_Configure(This)	\
    (This)->lpVtbl -> Configure(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IDMS_JPGWorks_SaveAsJPEG_Proxy( 
    IDMS_JPGWorks __RPC_FAR * This,
    /* [in] */ BSTR FileName,
    /* [in] */ long Handle);


void __RPC_STUB IDMS_JPGWorks_SaveAsJPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_JPGWorks_Configure_Proxy( 
    IDMS_JPGWorks __RPC_FAR * This);


void __RPC_STUB IDMS_JPGWorks_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_JPGWorks_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DMS_JPGWorks,0x49F6D448,0xD82F,0x11D4,0x8E,0x9E,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifdef __cplusplus

class DECLSPEC_UUID("49F6D448-D82F-11D4-8E9E-0020AFCC5695")
DMS_JPGWorks;
#endif
#endif /* __DMS_JPGWks_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
