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
// This is a part of the Microsoft Foundation Classes C++ library.
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module

extern int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow);

extern "C" int WINAPI
WCE_IF(wWinMain,_tWinMain)(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	// call shared/exported WinMain
	return AfxWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

/////////////////////////////////////////////////////////////////////////////
// initialize app state such that it points to this module's core state

BOOL AFXAPI AfxInitialize(BOOL bDLL, DWORD dwVersion)
{
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_bDLL = (BYTE)bDLL;
	ASSERT(dwVersion <= _MFC_VER);
	UNUSED(dwVersion);  // not used in release build
#ifdef _AFXDLL
	pModuleState->m_dwVersion = dwVersion;
#endif
#ifdef _MBCS
	// set correct multi-byte code-page for Win32 apps
	if (!bDLL)
		_setmbcp(_MB_CP_ANSI);
#endif //_MBCS
	return TRUE;
}

// force initialization early
#pragma warning(disable: 4074)
#pragma init_seg(lib)

#ifndef _AFXDLL
void AFX_CDECL _AfxTermAppState()
{
	// terminate local data and critical sections
	AfxTermLocalData(NULL, TRUE);
	AfxCriticalTerm();

	// release the reference to thread local storage data
	AfxTlsRelease();
}
#endif

#ifndef _AFXDLL
char _afxInitAppState = (char)(AfxInitialize(FALSE, _MFC_VER), atexit(&_AfxTermAppState));
#else
char _afxInitAppState = (char)(AfxInitialize(FALSE, _MFC_VER));
#endif

/////////////////////////////////////////////////////////////////////////////
