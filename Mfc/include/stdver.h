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
//-----------------------------------------------------------------------------
//	stdver.h
//
// All rights reserved.
//
//  Purpose:
//		define the version string for display.
//
//  Revision History:
//
//	[]		09-Jul-1993 [dans]		Created
//
//-----------------------------------------------------------------------------
#if !defined(_stdver_h)
#define _stdver_h 1

//
// defines for version string
//
#if (rmm <= 9)
#define rmmpad "0"
#else
#define rmmpad
#endif

#if (rup <= 9)
#define ruppad "000"
#elif (rup <= 99)
#define ruppad "00"
#elif (rup <= 999)
#define ruppad "0"
#else
#define ruppad
#endif

#if ( rup == 0 )
#define SZVER1(a,b) 				#a "." rmmpad #b
#define SZVER2(a,b) 				SZVER1(a, b)
#define SZVER						SZVER2(rmj,rmm)
#else
#define SZVER1(a,b,c)				#a "." rmmpad #b "." ruppad #c
#define SZVER2(a,b,c)				SZVER1(a, b, c)
#define SZVER						SZVER2(rmj,rmm,rup)
#endif

#define FULLSZVER1(a,b,c)			#a "." rmmpad #b "." ruppad #c
#define FULLSZVER2(a,b,c)			FULLSZVER1(a, b, c)
#define FULLSZVER					FULLSZVER2(rmj,rmm,rup)

#endif
