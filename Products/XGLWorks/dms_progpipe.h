/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Dec 24 22:00:56 2000
 */
/* Compiler settings for C:\Wombat\Pro\DMS_ProgPipe\DMS_ProgPipe.idl:
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

#ifndef __DMS_ProgPipe_h__
#define __DMS_ProgPipe_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDMS_ProgPipe_FWD_DEFINED__
#define __IDMS_ProgPipe_FWD_DEFINED__
typedef interface IDMS_ProgPipe IDMS_ProgPipe;
#endif 	/* __IDMS_ProgPipe_FWD_DEFINED__ */


#ifndef __DMS_ProgPipe_FWD_DEFINED__
#define __DMS_ProgPipe_FWD_DEFINED__

#ifdef __cplusplus
typedef class DMS_ProgPipe DMS_ProgPipe;
#else
typedef struct DMS_ProgPipe DMS_ProgPipe;
#endif /* __cplusplus */

#endif 	/* __DMS_ProgPipe_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ProgPipe_LIBRARY_DEFINED__
#define __ProgPipe_LIBRARY_DEFINED__

/* library ProgPipe */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_ProgPipe,0x66DDC6D0,0xAA5D,0x11D4,0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C);

#ifndef __IDMS_ProgPipe_INTERFACE_DEFINED__
#define __IDMS_ProgPipe_INTERFACE_DEFINED__

/* interface IDMS_ProgPipe */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


DEFINE_GUID(IID_IDMS_ProgPipe,0x66DDC6D1,0xAA5D,0x11D4,0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66DDC6D1-AA5D-11D4-83E2-00104BB2580C")
    IDMS_ProgPipe : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall Show( void) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Hide( void) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Step( void) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_TotalSteps( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_TotalSteps( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Title( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Text( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Text( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_CurrentStep( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_CurrentStep( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Icon( 
            /* [retval][out] */ long __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Icon( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT __stdcall Reset( void) = 0;
        
        virtual /* [id][propget] */ HRESULT __stdcall get_Message( 
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [id][propput] */ HRESULT __stdcall put_Message( 
            /* [in] */ BSTR Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMS_ProgPipeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Show )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Hide )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Step )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_TotalSteps )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_TotalSteps )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Title )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Title )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Text )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Text )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_CurrentStep )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_CurrentStep )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Icon )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Icon )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( __stdcall __RPC_FAR *Reset )( 
            IDMS_ProgPipe __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( __stdcall __RPC_FAR *get_Message )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [id][propput] */ HRESULT ( __stdcall __RPC_FAR *put_Message )( 
            IDMS_ProgPipe __RPC_FAR * This,
            /* [in] */ BSTR Value);
        
        END_INTERFACE
    } IDMS_ProgPipeVtbl;

    interface IDMS_ProgPipe
    {
        CONST_VTBL struct IDMS_ProgPipeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMS_ProgPipe_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMS_ProgPipe_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMS_ProgPipe_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMS_ProgPipe_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDMS_ProgPipe_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDMS_ProgPipe_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDMS_ProgPipe_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDMS_ProgPipe_Show(This)	\
    (This)->lpVtbl -> Show(This)

#define IDMS_ProgPipe_Hide(This)	\
    (This)->lpVtbl -> Hide(This)

#define IDMS_ProgPipe_Step(This)	\
    (This)->lpVtbl -> Step(This)

#define IDMS_ProgPipe_get_TotalSteps(This,Value)	\
    (This)->lpVtbl -> get_TotalSteps(This,Value)

#define IDMS_ProgPipe_put_TotalSteps(This,Value)	\
    (This)->lpVtbl -> put_TotalSteps(This,Value)

#define IDMS_ProgPipe_get_Title(This,Value)	\
    (This)->lpVtbl -> get_Title(This,Value)

#define IDMS_ProgPipe_put_Title(This,Value)	\
    (This)->lpVtbl -> put_Title(This,Value)

#define IDMS_ProgPipe_get_Text(This,Value)	\
    (This)->lpVtbl -> get_Text(This,Value)

#define IDMS_ProgPipe_put_Text(This,Value)	\
    (This)->lpVtbl -> put_Text(This,Value)

#define IDMS_ProgPipe_get_CurrentStep(This,Value)	\
    (This)->lpVtbl -> get_CurrentStep(This,Value)

#define IDMS_ProgPipe_put_CurrentStep(This,Value)	\
    (This)->lpVtbl -> put_CurrentStep(This,Value)

#define IDMS_ProgPipe_get_Icon(This,Value)	\
    (This)->lpVtbl -> get_Icon(This,Value)

#define IDMS_ProgPipe_put_Icon(This,Value)	\
    (This)->lpVtbl -> put_Icon(This,Value)

#define IDMS_ProgPipe_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IDMS_ProgPipe_get_Message(This,Value)	\
    (This)->lpVtbl -> get_Message(This,Value)

#define IDMS_ProgPipe_put_Message(This,Value)	\
    (This)->lpVtbl -> put_Message(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IDMS_ProgPipe_Show_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This);


void __RPC_STUB IDMS_ProgPipe_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_ProgPipe_Hide_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This);


void __RPC_STUB IDMS_ProgPipe_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_ProgPipe_Step_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This);


void __RPC_STUB IDMS_ProgPipe_Step_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_TotalSteps_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_TotalSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_TotalSteps_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_ProgPipe_put_TotalSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_Title_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_Title_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_ProgPipe_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_Text_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_Text_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_ProgPipe_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_CurrentStep_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_CurrentStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_CurrentStep_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_ProgPipe_put_CurrentStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_Icon_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_Icon_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IDMS_ProgPipe_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IDMS_ProgPipe_Reset_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This);


void __RPC_STUB IDMS_ProgPipe_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT __stdcall IDMS_ProgPipe_get_Message_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDMS_ProgPipe_get_Message_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT __stdcall IDMS_ProgPipe_put_Message_Proxy( 
    IDMS_ProgPipe __RPC_FAR * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IDMS_ProgPipe_put_Message_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMS_ProgPipe_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DMS_ProgPipe,0x66DDC6D3,0xAA5D,0x11D4,0x83,0xE2,0x00,0x10,0x4B,0xB2,0x58,0x0C);

#ifdef __cplusplus

class DECLSPEC_UUID("66DDC6D3-AA5D-11D4-83E2-00104BB2580C")
DMS_ProgPipe;
#endif
#endif /* __ProgPipe_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
