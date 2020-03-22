/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Apr 02 16:29:32 2005
 */
/* Compiler settings for C:\Wombat\Products\DMS_Common\DMS_Comm.idl:
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

#ifndef __DMS_Comm_h__
#define __DMS_Comm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_Common_FWD_DEFINED__
#define __IDMS_Common_FWD_DEFINED__
typedef interface IDMS_Common IDMS_Common;
#endif 	/* __IDMS_Common_FWD_DEFINED__ */


#ifndef __DMS_Common_FWD_DEFINED__
#define __DMS_Common_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_Common DMS_Common;
#else
typedef struct DMS_Common DMS_Common;
#endif /* __cplusplus */

#endif 	/* __DMS_Common_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DMS_Comm_LIBRARY_DEFINED__
#define __DMS_Comm_LIBRARY_DEFINED__

/* library DMS_Comm */
/* [custom][custom][helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_DMS_Comm,0xFC99C7B2,0x4A88,0x11D4,0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifndef __IDMS_Common_INTERFACE_DEFINED__
#define __IDMS_Common_INTERFACE_DEFINED__

/* interface IDMS_Common */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_Common,0xFC99C7B3,0x4A88,0x11D4,0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC99C7B3-4A88-11D4-8A03-0020AFCC5695")
    IDMS_Common : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall About( void) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Icon( 
            /* [in] */ long Param1) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_ProductName( 
            /* [in] */ BSTR sProductName) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_ProductName( 
            /* [retval][out] */ BSTR __RPC_FAR *sProductName) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_ProductCode( 
            /* [in] */ BSTR sProductCode) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_ProductCode( 
            /* [retval][out] */ BSTR __RPC_FAR *sProductCode) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_AuthCode( 
            /* [in] */ BSTR Param1) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_IsRegistered( 
            /* [retval][out] */ int __RPC_FAR *bIsRegistered) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Register( void) = 0;
        
        virtual /* [id] */ HRESULT __stdcall IsSolidWorksFile( 
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ int __RPC_FAR *bIsSolidWorksFile) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Commercial( 
            /* [retval][out] */ int __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Commercial( 
            /* [in] */ int Value) = 0;
        
        virtual /* [id] */ HRESULT __stdcall IsSolidWorksRunning( 
            /* [retval][out] */ int __RPC_FAR *bIsSolidWorksRunning) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetMachineID( 
            /* [retval][out] */ BSTR __RPC_FAR *sMachineID) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_IniFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_IniFileName( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_SolidWorks( 
            /* [in] */ IDispatch __RPC_FAR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_CommonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_Common __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_Common __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_Common __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *About )( 
            IDMS_Common __RPC_FAR * This);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Icon )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ long Param1);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_ProductName )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ BSTR sProductName);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_ProductName )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *sProductName);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_ProductCode )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ BSTR sProductCode);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_ProductCode )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *sProductCode);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_AuthCode )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ BSTR Param1);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_IsRegistered )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *bIsRegistered);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Register )( 
            IDMS_Common __RPC_FAR * This);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *IsSolidWorksFile )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ int __RPC_FAR *bIsSolidWorksFile);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Commercial )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Commercial )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ int Value);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *IsSolidWorksRunning )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *bIsSolidWorksRunning);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *GetMachineID )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *sMachineID);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_IniFileName )( 
            IDMS_Common __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_IniFileName )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_SolidWorks )( 
            IDMS_Common __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Value);
        
        END_INTERFACE
    } IDMS_CommonVtbl;

    interface IDMS_Common
    {
        CONST_VTBL struct IDMS_CommonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_Common_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_Common_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_Common_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_Common_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_Common_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_Common_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_Common_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_Common_About(This)	\
    (This)->lpVtbl -> About(This)

#define IDMS_Common_put_Icon(This,Param1)	\
    (This)->lpVtbl -> put_Icon(This,Param1)

#define IDMS_Common_put_ProductName(This,sProductName)	\
    (This)->lpVtbl -> put_ProductName(This,sProductName)

#define IDMS_Common_get_ProductName(This,sProductName)	\
    (This)->lpVtbl -> get_ProductName(This,sProductName)

#define IDMS_Common_put_ProductCode(This,sProductCode)	\
    (This)->lpVtbl -> put_ProductCode(This,sProductCode)

#define IDMS_Common_get_ProductCode(This,sProductCode)	\
    (This)->lpVtbl -> get_ProductCode(This,sProductCode)

#define IDMS_Common_put_AuthCode(This,Param1)	\
    (This)->lpVtbl -> put_AuthCode(This,Param1)

#define IDMS_Common_get_IsRegistered(This,bIsRegistered)	\
    (This)->lpVtbl -> get_IsRegistered(This,bIsRegistered)

#define IDMS_Common_Register(This)	\
    (This)->lpVtbl -> Register(This)

#define IDMS_Common_IsSolidWorksFile(This,sFileName,bIsSolidWorksFile)	\
    (This)->lpVtbl -> IsSolidWorksFile(This,sFileName,bIsSolidWorksFile)

#define IDMS_Common_get_Commercial(This,Value)	\
    (This)->lpVtbl -> get_Commercial(This,Value)

#define IDMS_Common_put_Commercial(This,Value)	\
    (This)->lpVtbl -> put_Commercial(This,Value)

#define IDMS_Common_IsSolidWorksRunning(This,bIsSolidWorksRunning)	\
    (This)->lpVtbl -> IsSolidWorksRunning(This,bIsSolidWorksRunning)

#define IDMS_Common_GetMachineID(This,sMachineID)	\
    (This)->lpVtbl -> GetMachineID(This,sMachineID)

#define IDMS_Common_get_IniFileName(This,Value)	\
    (This)->lpVtbl -> get_IniFileName(This,Value)

#define IDMS_Common_put_IniFileName(This,Value)	\
    (This)->lpVtbl -> put_IniFileName(This,Value)

#define IDMS_Common_put_SolidWorks(This,Value)	\
    (This)->lpVtbl -> put_SolidWorks(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IDMS_Common_About_Proxy( 
    IDMS_Common __RPC_FAR * This);


void __RPC_STUB IDMS_Common_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_Icon_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ long Param1);


void __RPC_STUB IDMS_Common_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_ProductName_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ BSTR sProductName);


void __RPC_STUB IDMS_Common_put_ProductName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_Common_get_ProductName_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *sProductName);


void __RPC_STUB IDMS_Common_get_ProductName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_ProductCode_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ BSTR sProductCode);


void __RPC_STUB IDMS_Common_put_ProductCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_Common_get_ProductCode_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *sProductCode);


void __RPC_STUB IDMS_Common_get_ProductCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_AuthCode_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ BSTR Param1);


void __RPC_STUB IDMS_Common_put_AuthCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_Common_get_IsRegistered_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *bIsRegistered);


void __RPC_STUB IDMS_Common_get_IsRegistered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_Common_Register_Proxy( 
    IDMS_Common __RPC_FAR * This);


void __RPC_STUB IDMS_Common_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_Common_IsSolidWorksFile_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ BSTR sFileName,
    /* [retval][out] */ int __RPC_FAR *bIsSolidWorksFile);


void __RPC_STUB IDMS_Common_IsSolidWorksFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_Common_get_Commercial_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Value);


void __RPC_STUB IDMS_Common_get_Commercial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_Commercial_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ int Value);


void __RPC_STUB IDMS_Common_put_Commercial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_Common_IsSolidWorksRunning_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *bIsSolidWorksRunning);


void __RPC_STUB IDMS_Common_IsSolidWorksRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_Common_GetMachineID_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *sMachineID);


void __RPC_STUB IDMS_Common_GetMachineID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_Common_get_IniFileName_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_Common_get_IniFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_IniFileName_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_Common_put_IniFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_Common_put_SolidWorks_Proxy( 
    IDMS_Common __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Value);


void __RPC_STUB IDMS_Common_put_SolidWorks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_Common_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DMS_Common,0xFC99C7B5,0x4A88,0x11D4,0x8A,0x03,0x00,0x20,0xAF,0xCC,0x56,0x95);

#ifdef __cplusplus

class DECLSPEC_UUID("FC99C7B5-4A88-11D4-8A03-0020AFCC5695")
DMS_Common;
#endif
#endif /* __DMS_Comm_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
