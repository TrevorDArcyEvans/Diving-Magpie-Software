/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Apr 02 16:29:32 2005
 */
/* Compiler settings for C:\Wombat\Products\DMS_StkWks\DMS_StkWks.idl:
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

#ifndef __DMS_StkWks_h__
#define __DMS_StkWks_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_StickWorks_FWD_DEFINED__
#define __IDMS_StickWorks_FWD_DEFINED__
typedef interface IDMS_StickWorks IDMS_StickWorks;
#endif 	/* __IDMS_StickWorks_FWD_DEFINED__ */


#ifndef __DMS_StickWorks_FWD_DEFINED__
#define __DMS_StickWorks_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_StickWorks DMS_StickWorks;
#else
typedef struct DMS_StickWorks DMS_StickWorks;
#endif /* __cplusplus */

#endif 	/* __DMS_StickWorks_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DMS_StkWks_LIBRARY_DEFINED__
#define __DMS_StkWks_LIBRARY_DEFINED__

/* library DMS_StkWks */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_DMS_StkWks,0x52357E4C,0x4AAB,0x11D4,0x8A,0x05,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifndef __IDMS_StickWorks_INTERFACE_DEFINED__
#define __IDMS_StickWorks_INTERFACE_DEFINED__

/* interface IDMS_StickWorks */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_StickWorks,0x52357E4D,0x4AAB,0x11D4,0x8A,0x05,0x00,0x20,0xAF,0xCC,0x56,0x95);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52357E4D-4AAB-11D4-8A05-0020AFCC5695")
    IDMS_StickWorks : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall Configure( void) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Name( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Icon( 
            /* [in] */ long Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_StickWorksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_StickWorks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_StickWorks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Configure )( 
            IDMS_StickWorks __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Name )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Name )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Icon )( 
            IDMS_StickWorks __RPC_FAR * This,
            /* [in] */ long Value);
        
        END_INTERFACE
    } IDMS_StickWorksVtbl;

    interface IDMS_StickWorks
    {
        CONST_VTBL struct IDMS_StickWorksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_StickWorks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_StickWorks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_StickWorks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_StickWorks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_StickWorks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_StickWorks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_StickWorks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_StickWorks_Configure(This)	\
    (This)->lpVtbl -> Configure(This)

#define IDMS_StickWorks_get_Name(This,Value)	\
    (This)->lpVtbl -> get_Name(This,Value)

#define IDMS_StickWorks_put_Name(This,Value)	\
    (This)->lpVtbl -> put_Name(This,Value)

#define IDMS_StickWorks_put_Icon(This,Value)	\
    (This)->lpVtbl -> put_Icon(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IDMS_StickWorks_Configure_Proxy( 
    IDMS_StickWorks __RPC_FAR * This);


void __RPC_STUB IDMS_StickWorks_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_StickWorks_get_Name_Proxy( 
    IDMS_StickWorks __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_StickWorks_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_StickWorks_put_Name_Proxy( 
    IDMS_StickWorks __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_StickWorks_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_StickWorks_put_Icon_Proxy( 
    IDMS_StickWorks __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_StickWorks_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_StickWorks_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DMS_StickWorks,0x52357E4F,0x4AAB,0x11D4,0x8A,0x05,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifdef __cplusplus

class DECLSPEC_UUID("52357E4F-4AAB-11D4-8A05-0020AFCC5695")
DMS_StickWorks;
#endif
#endif /* __DMS_StkWks_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
