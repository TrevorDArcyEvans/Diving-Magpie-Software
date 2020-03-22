/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Dec 26 20:53:06 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_PSWks\DMS_PSWks.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __DMS_PSWks_h__
#define __DMS_PSWks_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_PSWorks_FWD_DEFINED__
#define __IDMS_PSWorks_FWD_DEFINED__
typedef interface IDMS_PSWorks IDMS_PSWorks;
#endif 	/* __IDMS_PSWorks_FWD_DEFINED__ */


#ifndef __DMS_PSWorks_FWD_DEFINED__
#define __DMS_PSWorks_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_PSWorks DMS_PSWorks;
#else
typedef struct DMS_PSWorks DMS_PSWorks;
#endif /* __cplusplus */

#endif 	/* __DMS_PSWorks_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDMS_PSWorks_INTERFACE_DEFINED__
#define __IDMS_PSWorks_INTERFACE_DEFINED__

/* interface IDMS_PSWorks */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDMS_PSWorks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CAFC120B-DB67-11D4-8EA3-0020AFCC5695")
    IDMS_PSWorks : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExtractConfig( 
            /* [in] */ BSTR sSW_FileName,
            /* [in] */ BSTR sConfigBodyName,
            /* [in] */ BSTR sParasolid_FileName,
            /* [retval][out] */ int __RPC_FAR *nRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConfigList( 
            /* [in] */ BSTR sSW_FileName,
            /* [retval][out] */ BSTR __RPC_FAR *sConfigList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_PSWorksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_PSWorks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_PSWorks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExtractConfig )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ BSTR sSW_FileName,
            /* [in] */ BSTR sConfigBodyName,
            /* [in] */ BSTR sParasolid_FileName,
            /* [retval][out] */ int __RPC_FAR *nRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigList )( 
            IDMS_PSWorks __RPC_FAR * This,
            /* [in] */ BSTR sSW_FileName,
            /* [retval][out] */ BSTR __RPC_FAR *sConfigList);
        
        END_INTERFACE
    } IDMS_PSWorksVtbl;

    interface IDMS_PSWorks
    {
        CONST_VTBL struct IDMS_PSWorksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_PSWorks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_PSWorks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_PSWorks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_PSWorks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_PSWorks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_PSWorks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_PSWorks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_PSWorks_ExtractConfig(This,sSW_FileName,sConfigBodyName,sParasolid_FileName,nRetVal)	\
    (This)->lpVtbl -> ExtractConfig(This,sSW_FileName,sConfigBodyName,sParasolid_FileName,nRetVal)

#define IDMS_PSWorks_GetConfigList(This,sSW_FileName,sConfigList)	\
    (This)->lpVtbl -> GetConfigList(This,sSW_FileName,sConfigList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDMS_PSWorks_ExtractConfig_Proxy( 
    IDMS_PSWorks __RPC_FAR * This,
    /* [in] */ BSTR sSW_FileName,
    /* [in] */ BSTR sConfigBodyName,
    /* [in] */ BSTR sParasolid_FileName,
    /* [retval][out] */ int __RPC_FAR *nRetVal);


void __RPC_STUB IDMS_PSWorks_ExtractConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDMS_PSWorks_GetConfigList_Proxy( 
    IDMS_PSWorks __RPC_FAR * This,
    /* [in] */ BSTR sSW_FileName,
    /* [retval][out] */ BSTR __RPC_FAR *sConfigList);


void __RPC_STUB IDMS_PSWorks_GetConfigList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_PSWorks_INTERFACE_DEFINED__ */



#ifndef __DMS_PSWKSLib_LIBRARY_DEFINED__
#define __DMS_PSWKSLib_LIBRARY_DEFINED__

/* library DMS_PSWKSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DMS_PSWKSLib;

EXTERN_C const CLSID CLSID_DMS_PSWorks;

#ifdef __cplusplus

class DECLSPEC_UUID("CAFC120C-DB67-11D4-8EA3-0020AFCC5695")
DMS_PSWorks;
#endif
#endif /* __DMS_PSWKSLib_LIBRARY_DEFINED__ */

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
