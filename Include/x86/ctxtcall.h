//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Thu Jun 24 18:48:27 2004
 */
/* Compiler settings for .\ctxtcall.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __ctxtcall_h__
#define __ctxtcall_h__

/* Forward Declarations */ 

#ifndef __IContextCallback_FWD_DEFINED__
#define __IContextCallback_FWD_DEFINED__
typedef interface IContextCallback IContextCallback;
#endif 	/* __IContextCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "objidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ctxtcall_0000 */
/* [local] */ 

//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
typedef struct tagComCallData
    {
    DWORD dwDispid;
    DWORD dwReserved;
    void __RPC_FAR *pUserDefined;
    }	ComCallData;



extern RPC_IF_HANDLE __MIDL_itf_ctxtcall_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ctxtcall_0000_v0_0_s_ifspec;

#ifndef __IContextCallback_INTERFACE_DEFINED__
#define __IContextCallback_INTERFACE_DEFINED__

/* interface IContextCallback */
/* [unique][uuid][object][local] */ 

typedef /* [ref] */ HRESULT ( __stdcall __RPC_FAR *PFNCONTEXTCALL )( 
    ComCallData __RPC_FAR *pParam);


EXTERN_C const IID IID_IContextCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000001da-0000-0000-C000-000000000046")
    IContextCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ContextCallback( 
            /* [in] */ PFNCONTEXTCALL pfnCallback,
            /* [in] */ ComCallData __RPC_FAR *pParam,
            /* [in] */ REFIID riid,
            /* [in] */ int iMethod,
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IContextCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IContextCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IContextCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IContextCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ContextCallback )( 
            IContextCallback __RPC_FAR * This,
            /* [in] */ PFNCONTEXTCALL pfnCallback,
            /* [in] */ ComCallData __RPC_FAR *pParam,
            /* [in] */ REFIID riid,
            /* [in] */ int iMethod,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        END_INTERFACE
    } IContextCallbackVtbl;

    interface IContextCallback
    {
        CONST_VTBL struct IContextCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IContextCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IContextCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IContextCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IContextCallback_ContextCallback(This,pfnCallback,pParam,riid,iMethod,pUnk)	\
    (This)->lpVtbl -> ContextCallback(This,pfnCallback,pParam,riid,iMethod,pUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IContextCallback_ContextCallback_Proxy( 
    IContextCallback __RPC_FAR * This,
    /* [in] */ PFNCONTEXTCALL pfnCallback,
    /* [in] */ ComCallData __RPC_FAR *pParam,
    /* [in] */ REFIID riid,
    /* [in] */ int iMethod,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IContextCallback_ContextCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IContextCallback_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


