/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Dec 12 20:47:54 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_CustProps\DMS_CustProps.idl:
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

#ifndef __DMS_CustProps_h__
#define __DMS_CustProps_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_CustomProperties_FWD_DEFINED__
#define __IDMS_CustomProperties_FWD_DEFINED__
typedef interface IDMS_CustomProperties IDMS_CustomProperties;
#endif 	/* __IDMS_CustomProperties_FWD_DEFINED__ */


#ifndef __DMS_CustomProperties_FWD_DEFINED__
#define __DMS_CustomProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_CustomProperties DMS_CustomProperties;
#else
typedef struct DMS_CustomProperties DMS_CustomProperties;
#endif /* __cplusplus */

#endif 	/* __DMS_CustomProperties_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDMS_CustomProperties_INTERFACE_DEFINED__
#define __IDMS_CustomProperties_INTERFACE_DEFINED__

/* interface IDMS_CustomProperties */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDMS_CustomProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA621304-D053-11D4-8E94-0020AFCC5695")
    IDMS_CustomProperties : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddCustomInfo3( 
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [in] */ long FieldType,
            /* [in] */ BSTR FieldValue,
            /* [retval][out] */ BOOL __RPC_FAR *RetVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CustomInfo2( 
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CustomInfo2( 
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteCustomInfo2( 
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BOOL __RPC_FAR *RetVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCustomInfoCount2( 
            /* [in] */ BSTR Configuration,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCustomInfoNames2( 
            /* [in] */ BSTR Configuration,
            /* [retval][out] */ BSTR __RPC_FAR *__RPC_FAR *RetVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCustomInfoType3( 
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ long __RPC_FAR *Type) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SummaryInfo( 
            /* [in] */ long FieldID,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SummaryInfo( 
            /* [in] */ long FieldID,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadFile( 
            /* [in] */ BSTR FileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_CustomPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_CustomProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_CustomProperties __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCustomInfo3 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [in] */ long FieldType,
            /* [in] */ BSTR FieldValue,
            /* [retval][out] */ BOOL __RPC_FAR *RetVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CustomInfo2 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CustomInfo2 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCustomInfo2 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BOOL __RPC_FAR *RetVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCustomInfoCount2 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCustomInfoNames2 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [retval][out] */ BSTR __RPC_FAR *__RPC_FAR *RetVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCustomInfoType3 )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR Configuration,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ long __RPC_FAR *Type);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SummaryInfo )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ long FieldID,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SummaryInfo )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ long FieldID,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFile )( 
            IDMS_CustomProperties __RPC_FAR * This,
            /* [in] */ BSTR FileName);
        
        END_INTERFACE
    } IDMS_CustomPropertiesVtbl;

    interface IDMS_CustomProperties
    {
        CONST_VTBL struct IDMS_CustomPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_CustomProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_CustomProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_CustomProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_CustomProperties_AddCustomInfo3(This,Configuration,FieldName,FieldType,FieldValue,RetVal)	\
    (This)->lpVtbl -> AddCustomInfo3(This,Configuration,FieldName,FieldType,FieldValue,RetVal)

#define IDMS_CustomProperties_get_CustomInfo2(This,Configuration,FieldName,pVal)	\
    (This)->lpVtbl -> get_CustomInfo2(This,Configuration,FieldName,pVal)

#define IDMS_CustomProperties_put_CustomInfo2(This,Configuration,FieldName,newVal)	\
    (This)->lpVtbl -> put_CustomInfo2(This,Configuration,FieldName,newVal)

#define IDMS_CustomProperties_DeleteCustomInfo2(This,Configuration,FieldName,RetVal)	\
    (This)->lpVtbl -> DeleteCustomInfo2(This,Configuration,FieldName,RetVal)

#define IDMS_CustomProperties_GetCustomInfoCount2(This,Configuration,Count)	\
    (This)->lpVtbl -> GetCustomInfoCount2(This,Configuration,Count)

#define IDMS_CustomProperties_GetCustomInfoNames2(This,Configuration,RetVal)	\
    (This)->lpVtbl -> GetCustomInfoNames2(This,Configuration,RetVal)

#define IDMS_CustomProperties_GetCustomInfoType3(This,Configuration,FieldName,Type)	\
    (This)->lpVtbl -> GetCustomInfoType3(This,Configuration,FieldName,Type)

#define IDMS_CustomProperties_get_SummaryInfo(This,FieldID,pVal)	\
    (This)->lpVtbl -> get_SummaryInfo(This,FieldID,pVal)

#define IDMS_CustomProperties_put_SummaryInfo(This,FieldID,newVal)	\
    (This)->lpVtbl -> put_SummaryInfo(This,FieldID,newVal)

#define IDMS_CustomProperties_LoadFile(This,FileName)	\
    (This)->lpVtbl -> LoadFile(This,FileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_AddCustomInfo3_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [in] */ BSTR FieldName,
    /* [in] */ long FieldType,
    /* [in] */ BSTR FieldValue,
    /* [retval][out] */ BOOL __RPC_FAR *RetVal);


void __RPC_STUB IDMS_CustomProperties_AddCustomInfo3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_get_CustomInfo2_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [in] */ BSTR FieldName,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDMS_CustomProperties_get_CustomInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_put_CustomInfo2_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [in] */ BSTR FieldName,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDMS_CustomProperties_put_CustomInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_DeleteCustomInfo2_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [in] */ BSTR FieldName,
    /* [retval][out] */ BOOL __RPC_FAR *RetVal);


void __RPC_STUB IDMS_CustomProperties_DeleteCustomInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_GetCustomInfoCount2_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IDMS_CustomProperties_GetCustomInfoCount2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_GetCustomInfoNames2_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [retval][out] */ BSTR __RPC_FAR *__RPC_FAR *RetVal);


void __RPC_STUB IDMS_CustomProperties_GetCustomInfoNames2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_GetCustomInfoType3_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR Configuration,
    /* [in] */ BSTR FieldName,
    /* [retval][out] */ long __RPC_FAR *Type);


void __RPC_STUB IDMS_CustomProperties_GetCustomInfoType3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_get_SummaryInfo_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ long FieldID,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDMS_CustomProperties_get_SummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_put_SummaryInfo_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ long FieldID,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDMS_CustomProperties_put_SummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDMS_CustomProperties_LoadFile_Proxy( 
    IDMS_CustomProperties __RPC_FAR * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB IDMS_CustomProperties_LoadFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_CustomProperties_INTERFACE_DEFINED__ */



#ifndef __DMS_CUSTPROPSLib_LIBRARY_DEFINED__
#define __DMS_CUSTPROPSLib_LIBRARY_DEFINED__

/* library DMS_CUSTPROPSLib */
/* [helpstring][version][uuid] */ 


enum swCustomInfoType_e
    {	swCustomInfoUnknown	= 0,
	swCustomInfoText	= 30,
	swCustomInfoDate	= 64,
	swCustomInfoNumber	= 3,
	swCustomInfoYesOrNo	= 11
    };

EXTERN_C const IID LIBID_DMS_CUSTPROPSLib;

EXTERN_C const CLSID CLSID_DMS_CustomProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("CA621305-D053-11D4-8E94-0020AFCC5695")
DMS_CustomProperties;
#endif
#endif /* __DMS_CUSTPROPSLib_LIBRARY_DEFINED__ */

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
