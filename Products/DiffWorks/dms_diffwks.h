/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 21 11:34:41 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_DiffWks\DMS_DiffWks.idl:
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

#ifndef __DMS_DiffWks_h__
#define __DMS_DiffWks_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_DiffWorks_FWD_DEFINED__
#define __IDMS_DiffWorks_FWD_DEFINED__
typedef interface IDMS_DiffWorks IDMS_DiffWorks;
#endif 	/* __IDMS_DiffWorks_FWD_DEFINED__ */


#ifndef __DMS_DiffWorks_FWD_DEFINED__
#define __DMS_DiffWorks_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_DiffWorks DMS_DiffWorks;
#else
typedef struct DMS_DiffWorks DMS_DiffWorks;
#endif /* __cplusplus */

#endif 	/* __DMS_DiffWorks_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DMS_DiffWks_LIBRARY_DEFINED__
#define __DMS_DiffWks_LIBRARY_DEFINED__

/* library DMS_DiffWks */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_DMS_DiffWks,0x29A450B8,0xD6AE,0x11D4,0x8E,0x9C,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifndef __IDMS_DiffWorks_INTERFACE_DEFINED__
#define __IDMS_DiffWorks_INTERFACE_DEFINED__

/* interface IDMS_DiffWorks */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_DiffWorks,0x29A450B9,0xD6AE,0x11D4,0x8E,0x9C,0x00,0x20,0xAF,0xCC,0x56,0x95);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29A450B9-D6AE-11D4-8E9C-0020AFCC5695")
    IDMS_DiffWorks : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT __stdcall put_Icon( 
            /* [in] */ long hIcon) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetCompareInfo( 
            /* [out] */ BSTR __RPC_FAR *OriginalName,
            /* [out] */ BSTR __RPC_FAR *ChangedName,
            /* [out] */ BSTR __RPC_FAR *DisplayName,
            /* [out] */ double __RPC_FAR *Transparency,
            /* [out] */ long __RPC_FAR *Colour) = 0;
        
        virtual /* [id] */ HRESULT __stdcall ShowCompareResults( 
            /* [in] */ BSTR OriginalName,
            /* [in] */ BSTR ChangedName,
            /* [in] */ double OriginalMass,
            /* [in] */ double ChangedMass,
            /* [in] */ double OriginalVolume,
            /* [in] */ double ChangedVolume,
            /* [in] */ double OriginalArea,
            /* [in] */ double ChangedArea) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_DiffWorksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_DiffWorks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_DiffWorks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Icon )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ long hIcon);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *GetCompareInfo )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *OriginalName,
            /* [out] */ BSTR __RPC_FAR *ChangedName,
            /* [out] */ BSTR __RPC_FAR *DisplayName,
            /* [out] */ double __RPC_FAR *Transparency,
            /* [out] */ long __RPC_FAR *Colour);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *ShowCompareResults )( 
            IDMS_DiffWorks __RPC_FAR * This,
            /* [in] */ BSTR OriginalName,
            /* [in] */ BSTR ChangedName,
            /* [in] */ double OriginalMass,
            /* [in] */ double ChangedMass,
            /* [in] */ double OriginalVolume,
            /* [in] */ double ChangedVolume,
            /* [in] */ double OriginalArea,
            /* [in] */ double ChangedArea);
        
        END_INTERFACE
    } IDMS_DiffWorksVtbl;

    interface IDMS_DiffWorks
    {
        CONST_VTBL struct IDMS_DiffWorksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_DiffWorks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_DiffWorks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_DiffWorks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_DiffWorks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_DiffWorks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_DiffWorks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_DiffWorks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_DiffWorks_put_Icon(This,hIcon)	\
    (This)->lpVtbl -> put_Icon(This,hIcon)

#define IDMS_DiffWorks_GetCompareInfo(This,OriginalName,ChangedName,DisplayName,Transparency,Colour)	\
    (This)->lpVtbl -> GetCompareInfo(This,OriginalName,ChangedName,DisplayName,Transparency,Colour)

#define IDMS_DiffWorks_ShowCompareResults(This,OriginalName,ChangedName,OriginalMass,ChangedMass,OriginalVolume,ChangedVolume,OriginalArea,ChangedArea)	\
    (This)->lpVtbl -> ShowCompareResults(This,OriginalName,ChangedName,OriginalMass,ChangedMass,OriginalVolume,ChangedVolume,OriginalArea,ChangedArea)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT __stdcall IDMS_DiffWorks_put_Icon_Proxy( 
    IDMS_DiffWorks __RPC_FAR * This,
    /* [in] */ long hIcon);


void __RPC_STUB IDMS_DiffWorks_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_DiffWorks_GetCompareInfo_Proxy( 
    IDMS_DiffWorks __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *OriginalName,
    /* [out] */ BSTR __RPC_FAR *ChangedName,
    /* [out] */ BSTR __RPC_FAR *DisplayName,
    /* [out] */ double __RPC_FAR *Transparency,
    /* [out] */ long __RPC_FAR *Colour);


void __RPC_STUB IDMS_DiffWorks_GetCompareInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_DiffWorks_ShowCompareResults_Proxy( 
    IDMS_DiffWorks __RPC_FAR * This,
    /* [in] */ BSTR OriginalName,
    /* [in] */ BSTR ChangedName,
    /* [in] */ double OriginalMass,
    /* [in] */ double ChangedMass,
    /* [in] */ double OriginalVolume,
    /* [in] */ double ChangedVolume,
    /* [in] */ double OriginalArea,
    /* [in] */ double ChangedArea);


void __RPC_STUB IDMS_DiffWorks_ShowCompareResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_DiffWorks_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DMS_DiffWorks,0x29A450BB,0xD6AE,0x11D4,0x8E,0x9C,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifdef __cplusplus

class DECLSPEC_UUID("29A450BB-D6AE-11D4-8E9C-0020AFCC5695")
DMS_DiffWorks;
#endif
#endif /* __DMS_DiffWks_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
