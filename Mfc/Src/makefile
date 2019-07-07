!if 0
Copyright (c) Microsoft Corporation.  All rights reserved.
!endif
!if 0
Use of this source code is subject to the terms of the Microsoft end-user
license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
If you did not accept the terms of the EULA, you are not authorized to use
this source code. For a copy of the EULA, please see the LICENSE.RTF on your
install media.
!endif
#############################################################################
# Makefile : Builds a Microsoft Foundation Class library for Windows CE
#
# This is a part of the Microsoft Foundation Classes C++ library.
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Microsoft Foundation Classes Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Microsoft Foundation Classes product.
#
#
# Definition of parameters for this makefile.  These can be environment variables 
# or arguments passed into nmake.  You also must customize wce.h, which
# includes the specification of your MFCCE and OLECE library names.
#
# Build type: (required)
#   OSVER      = { 200 | 201 | 210 | 211 | 212 | 300 | 400 |410 |420}  
#   CPU        = { x86em | mips | mipsii | mipsfp | mipsii_fp | mipsiv | mipsiv_fp | sh3 | sh4 | ppc | x86 | arm | armv4 | thumb | armv4t | mips16 | armv4i | cef }
#   LIBTYPE    = { mfcdll | helper | static | oledll | locdll | atldll }     
#
# Directories and file names:  (required)
#   INCLUDE    = semicolon-delimited include files path (for OS headers and MFC headers)
#   LIB        = semicolon-delimited libraries path (for OS libs and MFC libs)
#   OUTDIR     = name of output directory (e.g. d:\mfcce\build)
#   TARGNAME   = name of file minus path and extension (e.g. mfcce210)
#   DEFFILE    = name of def file used to export DLL functions (e.g. wceppc\mfcce210.def)
#
# MFC localization DLL: (required only when LIBTYPE=locdll)   
#   LANG       = three-letter language id (e.g. deu, jpn)
#   LANGID     = hexadecimal language id  (e.g. 0407 for deu, 0411 for jpn)
#   CP         = decimal code page id     (e.g. 932 for jpn) 
#   CPHEX      = hexadecimal code page id (e.g. 03A4 for jpn)
#      CP and CPHEX are used for Japanese builds only.
#
# Additional build flags: (optional)
#   CLEAN      = { (empty) | CLEANALL | CLEANPCH } (default=(empty))
#   DEBUG      = { 0 | 1 } debug build (default = 0)
#   BROWSE     = { 0 | 1 } output browse information file (*.sbr) (default = 0)
#   BUILDINFO  = { 0 | 1 } output build parameters (default = 0)
#   NO_PCH     = { 0 | 1 } don't use precompiled headers (default = 0)
#############################################################################


#############################################################################
# Additional definitions and defaults

# Default build settings
!ifndef CLEAN
CLEAN=
!endif
!ifndef DEBUG
DEBUG=0
!endif
!ifndef BROWSE
BROWSE=0
!endif
!ifndef BUILDINFO
BUILDINFO=0
!endif
!ifndef NO_PCH
NO_PCH=0
!endif

# Define output filename
PREOUTFILE=$(OUTDIR)\$(TARGNAME)
!if ("$(LIBTYPE)" == "static") || ("$(LIBTYPE)" == "helper")
OUTFILE=$(PREOUTFILE).lib
!else
OUTFILE=$(PREOUTFILE).dll
!endif

# Precompiled headers
!if ("$(NO_PCH)" == "1")
CREATE_PCH_FLAG=
USE_PCH_FLAG=
!else
CREATE_PCH_FLAG=/Yc"stdafx.h"
USE_PCH_FLAG=/Yu"stdafx.h"
!endif

# Set muting (for less verbose output)
!if "$(BUILDINFO)" == "1"
MUTE=
NOLOGO=
!else
MUTE=@
NOLOGO=/nologo
!endif
#############################################################################


#############################################################################
# Compose base flags for both resource compiler and C++ compiler

# Set base flags
BASE_FLAGS=/D _WIN32_WCE=$(OSVER) /D UNDER_CE=$(OSVER) /D "UNICODE" /D "_UNICODE"
BASE_FLAGS = $(BASE_FLAGS) $(BASE_CPP_FLAGS)  

# ATL flags
!if "$(LIBTYPE)" == "atldll" 
BASE_FLAGS=$(BASE_FLAGS) /D _WINGDI_ /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" 
!endif

# Set more base flags per debug mode
!if "$(DEBUG)" == "1"
BASE_FLAGS=$(BASE_FLAGS) /D "_DEBUG"
!else
BASE_FLAGS=$(BASE_FLAGS) /D "NDEBUG"
!endif
#############################################################################


#############################################################################
# Configure C++ compiler

# Choose C++ compiler per platform
!if     "$(CPU)" == "x86em"
CPP=$(MUTE)cl.exe
!elseif "$(CPU)" == "mips"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mipsii"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mipsfp"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mipsii_fp"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mips16"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mipsiv"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "mipsiv_fp"
CPP=$(MUTE)clmips.exe
!elseif "$(CPU)" == "sh3"
CPP=$(MUTE)clsh.exe
!elseif "$(CPU)" == "sh4"
CPP=$(MUTE)clsh.exe
!elseif "$(CPU)" == "ppc"
CPP=$(MUTE)clppc.exe
!elseif "$(CPU)" == "x86"
CPP=$(MUTE)cl.exe
!elseif "$(CPU)" == "arm"
CPP=$(MUTE)clarm.exe
!elseif "$(CPU)" == "armv4"
CPP=$(MUTE)clarm.exe
!elseif "$(CPU)" == "armv4i"
CPP=$(MUTE)clarm.exe
!elseif "$(CPU)" == "thumb"
CPP=$(MUTE)clthumb.exe
!elseif "$(CPU)" == "armv4t"
CPP=$(MUTE)clthumb.exe
!elseif "$(CPU)" == "cef"
CPP=$(MUTE)clcef.exe
!endif

# Set C++ compiler flags
!if "$(CPU)" == "cef"
CPP_FLAGS=$(NOLOGO) $(BASE_FLAGS) /c /W3 /WX /Zi /Gf /cef /Fo"$(OUTDIR)\\" \
          /Fp$(PREOUTFILE).pch /Fd"$(PREOUTFILE).pdb"
!if "$(DEBUG)" != "1"
CPP_FLAGS=$(CPP_FLAGS) /Gy /Oxs   
!endif
!elseif "$(CPU)" == "x86em"
CPP_FLAGS=$(NOLOGO) $(BASE_FLAGS) /c /W3 /WX /Zi /Zl /Gf /Gz /Fo"$(OUTDIR)\\" \
          /Fp$(PREOUTFILE).pch /Fd"$(PREOUTFILE).pdb"
!else
CPP_FLAGS=$(NOLOGO) $(BASE_FLAGS) /c /W3 /WX /Zi /Zl /Gf /Fo"$(OUTDIR)\\" \
          /Fp$(PREOUTFILE).pch /Fd"$(PREOUTFILE).pdb"
!endif
!if $(BUILDINFO) == 1 
CPP_FLAGS=$(CPP_FLAGS) /Bd
!endif
!if $(BROWSE) == 1 
CPP_FLAGS=$(CPP_FLAGS) /Fr"$(OUTDIR)\\"
!endif

# Set more C++ compilers flags per library type
!if     "$(LIBTYPE)" == "mfcdll"
CPP_FLAGS=$(CPP_FLAGS) /D "_AFX_CORE_IMPL" /D "_AFX_NET_IMPL" /D "_AFXDLL" /D "_WINDLL" 
!elseif "$(LIBTYPE)" == "helper"
CPP_FLAGS=$(CPP_FLAGS) /D "_AFX_CORE_IMPL" /D "_AFXDLL" /D "_WINDLL" 
!elseif "$(LIBTYPE)" == "static"
CPP_FLAGS=$(CPP_FLAGS) /D "_AFX_CORE_IMPL" /D "_AFX_NET_IMPL"                        
!elseif "$(LIBTYPE)" == "oledll"
CPP_FLAGS=$(CPP_FLAGS) /D "_AFX_OLE_IMPL"  /D "_AFXDLL" /D "_WINDLL" /D "_AFXEXT" 
!elseif "$(LIBTYPE)" == "locdll"
!elseif "$(LIBTYPE)" == "atldll"
CPP_FLAGS=$(CPP_FLAGS) /D "_USRDLL"
!endif # library types

# Set more C++ compiler flags per platform (both debug and release mode)
!if     "$(CPU)" == "x86em"
CPP_FLAGS=$(CPP_FLAGS) /D "_WIN32_WCE_EMULATION" /D "x86" /D "_X86_" /D "WIN32" /D "_WINDOWS" /D "STRICT" 
!elseif "$(CPU)" == "mips"
CPP_FLAGS=$(CPP_FLAGS) /D "_MIPS_" /D "MIPS" /QMRWCE 
!elseif "$(CPU)" == "mipsii"
CPP_FLAGS=$(CPP_FLAGS) /D "R4000" /D "_MIPS_" /D "MIPS" /D "MIPSII" /QMRWCE /QMmips2 /D _M_MRX000=4000 -QMFPE
!elseif "$(CPU)" == "mipsfp"
CPP_FLAGS=$(CPP_FLAGS) /D "_MIPS_" /D "MIPS" /QMR4300 
!elseif "$(CPU)" == "mipsii_fp"
CPP_FLAGS=$(CPP_FLAGS) /D "R4000" /D "_MIPS_" /D "MIPS" /D "MIPSII" /D "MIPSII_FP" -QMFPE- -QMmips2
!elseif "$(CPU)" == "mips16"
CPP_FLAGS=$(CPP_FLAGS) /D "R4000" /ase16 /D "_MIPS16_" /D "MIPS16" /D "MIPSII" /D "MIPS16SUPPORT" /D "_MIPS_" /D "MIPS" /QMFWCE 
!elseif "$(CPU)" == "mipsiv"
CPP_FLAGS=$(CPP_FLAGS) /Ob0 /D "R4000" /D "_MIPS_" /D "MIPS" /D "MIPSIV" /D "_MIPS64" -QMmips4 -QMn32 -QMFPE
!elseif "$(CPU)" == "mipsiv_fp"
CPP_FLAGS=$(CPP_FLAGS) /Ob0 /D "R4000" /D "_MIPS_" /D "MIPS" /D "MIPSIV" /D "MIPSIV_FP" /D "_MIPS64" -QMmips4 -QMn32 -QMFPE-
!elseif "$(CPU)" == "sh3"
CPP_FLAGS=$(CPP_FLAGS) /D "SH" /D "_SH3_" /D "SH3" /D "SHx" /Qsh3
!elseif "$(CPU)" == "sh4"
CPP_FLAGS=$(CPP_FLAGS) /D "SH" /D "_SH4_" /D "SH4" /D "SHx" /Qsh4
!elseif "$(CPU)" == "ppc"
CPP_FLAGS=$(CPP_FLAGS) /D "_PPC_" /D "PPC" 
!elseif "$(CPU)" == "x86"
CPP_FLAGS=$(CPP_FLAGS) /D "_WIN32_WCE_CEPC" /D "x86" /D "_X86_"
!elseif "$(CPU)" == "arm"
CPP_FLAGS=$(CPP_FLAGS) /D "_ARM_" /D "ARM" /QMWCE 
!elseif "$(CPU)" == "armv4"
CPP_FLAGS=$(CPP_FLAGS) /Ob0 /D "_ARM_" /D "ARM" /D "ARMV4" /QMWCE 
!elseif "$(CPU)" == "thumb"
CPP_FLAGS=$(CPP_FLAGS) /D "_ARM_" /D "ARM" /QMWCE /QRarch4t /QRinterwork-return
!elseif "$(CPU)" == "armv4i"
CPP_FLAGS=$(CPP_FLAGS) /Ob0 /D "_ARM_" /D "ARM" /D "ARMV4I" /QMWCE /QRarch4t /QRinterwork-return -DTHUMBSUPPORT
!elseif "$(CPU)" == "armv4t"
CPP_FLAGS=$(CPP_FLAGS) /Ob0 /D "ARMV4T" /D "_ARM_" /D "_THUMB_" /D "ARM" /QMWCE /QRarch4t /QRinterwork-return
!endif # platforms

# Set compiler optimization flags according the debug mode
!if "$(CPU)" != "cef"
!if "$(DEBUG)" == "1"
CPP_FLAGS=$(CPP_FLAGS) /Od 
!else
CPP_FLAGS=$(CPP_FLAGS) /Gy /Oxs 
!endif
!endif

# For WinCE 2.0x, choose the CRT library to link in for ATL
!if ($(OSVER) < 201) && ("$(LIBTYPE)" == "atldll")
!if "$(DEBUG)" == "1"
CPP_FLAGS=$(CPP_FLAGS) /MLd
!else
CPP_FLAGS=$(CPP_FLAGS) /ML
!endif
!else
!if "$(DEBUG)" == "1"
CPP_FLAGS=$(CPP_FLAGS) /MTd
!else
CPP_FLAGS=$(CPP_FLAGS) /MT
!endif
!endif
#############################################################################


#############################################################################
# Configure linker

# Define linker flags per library type
!if ("$(LIBTYPE)" == "helper") || ("$(LIBTYPE)" == "static") # static library

!if "$(CPU)" == "cef"
LINK=$(MUTE)linkcef.exe -lib
!else
LINK=$(MUTE)link.exe -lib
!endif

LINK_FLAGS=$(NOLOGO) /out:$(OUTFILE) 

!else # dynamic library

!if "$(CPU)" == "cef"
LINK=$(MUTE)linkcef.exe
!else
LINK=$(MUTE)link.exe
!endif

LINK_FLAGS=$(NOLOGO) /out:$(OUTFILE) /def:$(DEFFILE) /pdb:$(PREOUTFILE).pdb     \
           /map:$(PREOUTFILE).map /savebaserelocations:$(PREOUTFILE).rel \
           /implib:$(PREOUTFILE).lib                     \
           /debug /dll /incremental:no /opt:noref /IGNORE:4108                  \
           /base:0x00100000 /nodefaultlib:LIBCMT.LIB /nodefaultlib:OLDNAMES.LIB

# Set more linker flags per platform
!if     "$(CPU)" == "x86em"
LINK_FLAGS=$(LINK_FLAGS) /machine:I386
!elseif "$(CPU)" == "mips" || "$(CPU)" == "mipsfp" || "$(CPU)" == "mipsii" || "$(CPU)" == "mipsii_fp"
LINK_FLAGS=$(LINK_FLAGS) /machine:MIPS  
!elseif "$(CPU)" == "mipsiv" || "$(CPU)" == "mipsiv_fp"
LINK_FLAGS=$(LINK_FLAGS) /machine:MIPSFPU  
!elseif "$(CPU)" == "mips16"
LINK_FLAGS=$(LINK_FLAGS) /machine:MIPS16
!elseif "$(CPU)" == "sh3"
LINK_FLAGS=$(LINK_FLAGS) /machine:SH3 /align:4096
!elseif "$(CPU)" == "sh4"
LINK_FLAGS=$(LINK_FLAGS) /machine:SH4  /align:4096
!elseif "$(CPU)" == "ppc"
LINK_FLAGS=$(LINK_FLAGS) /machine:PPC   
!elseif "$(CPU)" == "x86"
LINK_FLAGS=$(LINK_FLAGS) /machine:I386
!elseif "$(CPU)" == "arm"
LINK_FLAGS=$(LINK_FLAGS) /machine:ARM  /align:4096 /ARMPADCODE
!elseif "$(CPU)" == "armv4"
LINK_FLAGS=$(LINK_FLAGS) /machine:ARM  /align:4096 /ARMPADCODE
!elseif "$(CPU)" == "thumb" || "$(CPU)" == "armv4i" || "$(CPU)" == "armv4t"
LINK_FLAGS=$(LINK_FLAGS) /machine:THUMB /align:4096 /ARMPADCODE
!elseif "$(CPU)" == "cef"
# LINK_FLAGS=$(LINK_FLAGS) /machine:CEF /fixed:no /opt:noicf /nodefaultlib \
#                         msvccef.lib corelibc.lib coredll.lib 

LINK_FLAGS=$(LINK_FLAGS) /machine:CEF /fixed:no /opt:noicf /nodefaultlib:msvccee.lib \
			  msvccef.lib

!endif # platforms

# Specify entry point for locdll
!if "$(LIBTYPE)" == "locdll"
LINK_FLAGS=$(LINK_FLAGS) /noentry 
!endif

# Choose additional libraries for atldll
!if "$(LIBTYPE)" == "atldll"
LINK_FLAGS=$(LINK_FLAGS) /IGNORE:4197 coredll.lib
!if $(OSVER) < 201
!if "$(DEBUG)" == "1"
LINK_FLAGS=$(LINK_FLAGS) libcmtd.lib
!else
LINK_FLAGS=$(LINK_FLAGS) libcmt.lib
!endif # debug
!endif # < 201
!endif # atldll

# Choose subsystem per os version
!if "$(CPU)" == "x86em"  
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windows /windowsce:emulation
!elseif $(OSVER) == 200
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce
!elseif $(OSVER) == 201
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,2.01
!elseif $(OSVER) == 210
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,2.10
!elseif $(OSVER) == 211
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,2.11
!elseif $(OSVER) == 212
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,2.12
!elseif $(OSVER) == 300
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,3.00
!elseif $(OSVER) == 400
LINK_FLAGS=$(LINK_FLAGS) /subsystem:windowsce,4.00
!endif

!endif # static/dynamic library
#############################################################################


#############################################################################
# Configure additional build tools

# Choose resource compiler, midl compilers, and browse file generator
RSC=$(MUTE)rc.exe 
MIDL=$(MUTE)midl.exe
BSCMAKE=$(MUTE)bscmake.exe

RC_FILE=
RES_FILE=
IDL_FILE=
TLB_FILE=
MIDL_FLAGS=$(NOLOGO) $(BASE_FLAGS) /out $(OUTDIR) /mktyplib203 /win32 /o NUL
!if "$(DEBUG)" == "1"
MIDL_FLAGS=$(MIDL_FLAGS) /D "_DEBUG" 
!else
MIDL_FLAGS=$(MIDL_FLAGS) /D "NDEBUG" 
!endif

# Determine name of resource files per library type
!if     "$(LIBTYPE)" == "mfcdll"
RC_FILE=mfcdll.rc
RES_FILE=$(OUTDIR)\mfcdll.res
!elseif "$(LIBTYPE)" == "helper"
!elseif "$(LIBTYPE)" == "static"
!elseif "$(LIBTYPE)" == "oledll"
RC_FILE=mfcole.rc
RES_FILE=$(OUTDIR)\mfcole.res
!elseif "$(LIBTYPE)" == "locdll"
RC_FILE=mfcintl.rc
RES_FILE=$(OUTDIR)\mfcintl.res
!elseif "$(LIBTYPE)" == "atldll"
RC_FILE=atl.rc
RES_FILE=$(OUTDIR)\atl.res
IDL_FILE=atl.idl
TLB_FILE=$(OUTDIR)\atl.tlb
INCLUDE=$(OUTDIR);$(INCLUDE) 
MIDL_FLAGS=$(MIDL_FLAGS) /iid atl_i.c /h atl.h
!endif

# Define code page
!ifndef CP
# Default to "Windows, Multilingual" codepage (ANSI)
CP=1252
CPHEX=04E4
!endif

# Create resource flags
!if "$(LIBTYPE)" == "locdll"
RSC_FLAGS=$(BASE_FLAGS) /r /DLANG=$(LANG) /DLANGCODE=\"$(LANGID)$(CPHEX)\" \
   /l$(LANGID) /DLANGID=0x$(LANGID) /c$(CP) /DCODEPAGE=$(CP)
!else
RSC_FLAGS=$(BASE_FLAGS) /l 0x409 
!endif
!if "$(RES_FILE)" != ""
RSC_FLAGS=$(RSC_FLAGS) /fo$(RES_FILE)
!endif
#############################################################################


#############################################################################
# Configure library dependencies per library type

!if "$(LIBTYPE)" == "mfcdll" || "$(LIBTYPE)" == "static"
OBJ_FILES="$(OUTDIR)\stdafx.obj" \
!if "$(CPU)" == "mips" && "$(OSVER)" == "201"
# Workaround for AlderFE implementation of longjmp for MIPS (for MFC exception handling)
	"$(OUTDIR)\longjmp.obj"    \
!endif
	"$(OUTDIR)\afxabort.obj" \
	"$(OUTDIR)\afxasert.obj" \
	"$(OUTDIR)\afxcrit.obj"  \
	"$(OUTDIR)\afxdbcs.obj"  \
	"$(OUTDIR)\afxinl1.obj"  \
	"$(OUTDIR)\afxinl2.obj"  \
	"$(OUTDIR)\afxinl3.obj"  \
	"$(OUTDIR)\afxmem.obj"   \
	"$(OUTDIR)\afxstate.obj" \
	"$(OUTDIR)\afxtls.obj"   \
	"$(OUTDIR)\afxtrace.obj" \
	"$(OUTDIR)\appcore.obj"  \
	"$(OUTDIR)\appdlg.obj"   \
	"$(OUTDIR)\appgray.obj"  \
	"$(OUTDIR)\apphelp.obj"  \
	"$(OUTDIR)\apphelpx.obj" \
	"$(OUTDIR)\appinit.obj"  \
!if "$(LIBTYPE)" == "static"
	"$(OUTDIR)\appmodul.obj" \
!endif
	"$(OUTDIR)\appprnt.obj"  \
	"$(OUTDIR)\appterm.obj"  \
	"$(OUTDIR)\appui.obj"    \
	"$(OUTDIR)\appui1.obj"   \
	"$(OUTDIR)\appui2.obj"   \
	"$(OUTDIR)\appui3.obj"   \
	"$(OUTDIR)\arccore.obj"  \
	"$(OUTDIR)\arcex.obj"    \
	"$(OUTDIR)\arcobj.obj"   \
	"$(OUTDIR)\arcstrm.obj"  \
	"$(OUTDIR)\array_b.obj"  \
	"$(OUTDIR)\array_d.obj"  \
	"$(OUTDIR)\array_o.obj"  \
	"$(OUTDIR)\array_p.obj"  \
	"$(OUTDIR)\array_s.obj"  \
	"$(OUTDIR)\array_u.obj"  \
	"$(OUTDIR)\array_w.obj"  \
	"$(OUTDIR)\auxdata.obj"  \
	"$(OUTDIR)\barcool.obj"  \
	"$(OUTDIR)\barcore.obj"  \
	"$(OUTDIR)\bardlg.obj"   \
	"$(OUTDIR)\bardock.obj"  \
	"$(OUTDIR)\barstat.obj"  \
	"$(OUTDIR)\bartool.obj"  \
	"$(OUTDIR)\ccdata.obj"   \
	"$(OUTDIR)\cmdtarg.obj"  \
	"$(OUTDIR)\dlgclr.obj"   \
	"$(OUTDIR)\dlgcomm.obj"  \
	"$(OUTDIR)\dlgcore.obj"  \
	"$(OUTDIR)\dlgdata.obj"  \
	"$(OUTDIR)\dlgfile.obj"  \
	"$(OUTDIR)\dlgfloat.obj" \
	"$(OUTDIR)\dlgfr.obj"    \
	"$(OUTDIR)\dlgprop.obj"  \
	"$(OUTDIR)\dlgtempl.obj" \
!if "$(LIBTYPE)" == "static"
	"$(OUTDIR)\dllmodul.obj" \
!else
	"$(OUTDIR)\dllinit.obj"  \
!endif
	"$(OUTDIR)\doccore.obj"  \
	"$(OUTDIR)\dockcont.obj" \
	"$(OUTDIR)\dockstat.obj" \
	"$(OUTDIR)\docmgr.obj"   \
	"$(OUTDIR)\docsingl.obj" \
	"$(OUTDIR)\doctempl.obj" \
	"$(OUTDIR)\dumpcont.obj" \
	"$(OUTDIR)\dumpflt.obj"  \
	"$(OUTDIR)\dumpinit.obj" \
	"$(OUTDIR)\dumpout.obj"  \
	"$(OUTDIR)\except.obj"   \
	"$(OUTDIR)\filecore.obj" \
	"$(OUTDIR)\filelist.obj" \
	"$(OUTDIR)\filemem.obj"  \
	"$(OUTDIR)\filest.obj"   \
	"$(OUTDIR)\filetxt.obj"  \
	"$(OUTDIR)\filex.obj"    \
	"$(OUTDIR)\inet.obj"     \
	"$(OUTDIR)\list_o.obj"   \
	"$(OUTDIR)\list_p.obj"   \
	"$(OUTDIR)\list_s.obj"   \
	"$(OUTDIR)\map_pp.obj"   \
	"$(OUTDIR)\map_pw.obj"   \
	"$(OUTDIR)\map_so.obj"   \
	"$(OUTDIR)\map_sp.obj"   \
	"$(OUTDIR)\map_ss.obj"   \
	"$(OUTDIR)\map_wo.obj"   \
	"$(OUTDIR)\map_wp.obj"   \
	"$(OUTDIR)\mtcore.obj"   \
	"$(OUTDIR)\mtex.obj"     \
	"$(OUTDIR)\objcore.obj"  \
	"$(OUTDIR)\olelock.obj"  \
	"$(OUTDIR)\plex.obj"     \
	"$(OUTDIR)\sockcore.obj" \
	"$(OUTDIR)\strcore.obj"  \
	"$(OUTDIR)\strex.obj"    \
	"$(OUTDIR)\thrdcore.obj" \
	"$(OUTDIR)\timecore.obj" \
	"$(OUTDIR)\tooltip.obj"  \
	"$(OUTDIR)\trckrect.obj" \
	"$(OUTDIR)\validadd.obj" \
	"$(OUTDIR)\viewcmn.obj"  \
	"$(OUTDIR)\viewcore.obj" \
	"$(OUTDIR)\viewedit.obj" \
	"$(OUTDIR)\viewform.obj" \
	"$(OUTDIR)\viewprnt.obj" \
	"$(OUTDIR)\viewscrl.obj" \
	"$(OUTDIR)\winbtn.obj"   \
	"$(OUTDIR)\wincore.obj"  \
	"$(OUTDIR)\winctrl1.obj" \
	"$(OUTDIR)\winctrl2.obj" \
	"$(OUTDIR)\winctrl6.obj" \
	"$(OUTDIR)\winfrm.obj"   \
	"$(OUTDIR)\winfrmx.obj"  \
	"$(OUTDIR)\wingdi.obj"   \
	"$(OUTDIR)\wingdix.obj"  \
	"$(OUTDIR)\winhand.obj"  \
	"$(OUTDIR)\winmain.obj"  \
	"$(OUTDIR)\winmenu.obj"  \
	"$(OUTDIR)\winocc.obj"   \
	"$(OUTDIR)\winsplit.obj" \
	"$(OUTDIR)\winstr.obj"   \
	"$(OUTDIR)\winutil.obj"  \
	"$(OUTDIR)\wcealt.obj"   \
	"$(OUTDIR)\wcebar.obj"   \
	"$(OUTDIR)\wcedoclt.obj"   \
	"$(OUTDIR)\wcedoctm.obj"   \
	"$(OUTDIR)\wcedb.obj"    \
	"$(OUTDIR)\wcedlgfr.obj" \
	"$(OUTDIR)\wcedlgpr.obj" \
	"$(OUTDIR)\wcedlgsm.obj" \
	"$(OUTDIR)\wcedll.obj"   \
	"$(OUTDIR)\wceimpl.obj"   \
	"$(OUTDIR)\wcesock.obj"  \
	"$(OUTDIR)\wcethunk.obj" \
	"$(OUTDIR)\wcetime.obj"  

!elseif "$(LIBTYPE)" == "helper"
OBJ_FILES="$(OUTDIR)\stdafx.obj" \
	"$(OUTDIR)\appmodul.obj" \
	"$(OUTDIR)\dllmodul.obj" \
	"$(OUTDIR)\oleexp.obj"   \
	"$(OUTDIR)\wcedll.obj"

!elseif "$(LIBTYPE)" == "oledll"
OBJ_FILES="$(OUTDIR)\stdafx.obj" \
	"$(OUTDIR)\ctlconn.obj"  \
	"$(OUTDIR)\ctlcore.obj"  \
	"$(OUTDIR)\ctldata.obj"  \
	"$(OUTDIR)\ctlevent.obj" \
	"$(OUTDIR)\ctlfont.obj"  \
	"$(OUTDIR)\ctlframe.obj" \
	"$(OUTDIR)\ctlinl.obj"   \
	"$(OUTDIR)\ctlinplc.obj" \
	"$(OUTDIR)\ctlmodul.obj" \
	"$(OUTDIR)\ctlnownd.obj" \
	"$(OUTDIR)\ctlobj.obj"   \
	"$(OUTDIR)\ctlpbag.obj"  \
	"$(OUTDIR)\ctlppg.obj"   \
	"$(OUTDIR)\ctlprop.obj"  \
	"$(OUTDIR)\ctlpropx.obj" \
	"$(OUTDIR)\ctlpset.obj"  \
	"$(OUTDIR)\ctlpstg.obj"  \
	"$(OUTDIR)\ctlpstm.obj"  \
	"$(OUTDIR)\ctlquick.obj" \
	"$(OUTDIR)\ctlrefl.obj"  \
	"$(OUTDIR)\ctlreg.obj"   \
	"$(OUTDIR)\ctltrack.obj" \
	"$(OUTDIR)\ctlview.obj"  \
	"$(OUTDIR)\dllole.obj"   \
	"$(OUTDIR)\occcont.obj"  \
	"$(OUTDIR)\occddx.obj"   \
	"$(OUTDIR)\occddxf.obj"  \
	"$(OUTDIR)\occdlg.obj"   \
	"$(OUTDIR)\occevent.obj" \
	"$(OUTDIR)\occlock.obj"  \
	"$(OUTDIR)\occmgr.obj"   \
	"$(OUTDIR)\occsite.obj"  \
	"$(OUTDIR)\olecall.obj"  \
	"$(OUTDIR)\olecnvrt.obj" \
	"$(OUTDIR)\oleconn.obj"  \
	"$(OUTDIR)\oledata.obj"  \
	"$(OUTDIR)\oledisp1.obj" \
	"$(OUTDIR)\oledisp2.obj" \
	"$(OUTDIR)\oledll.obj"   \
	"$(OUTDIR)\oledobj2.obj" \
	"$(OUTDIR)\oleenum.obj"  \
	"$(OUTDIR)\olefact.obj"  \
	"$(OUTDIR)\oleinit.obj"  \
	"$(OUTDIR)\olemisc.obj"  \
	"$(OUTDIR)\olepset.obj"  \
	"$(OUTDIR)\olereg.obj"   \
	"$(OUTDIR)\olestrm.obj"  \
	"$(OUTDIR)\oletyplb.obj" \
	"$(OUTDIR)\oleunk.obj"   \
	"$(OUTDIR)\olevar.obj"   \
	"$(OUTDIR)\oleverb.obj"  \
	"$(OUTDIR)\winctrl5.obj" \
	"$(OUTDIR)\wcedll.obj"   \
	"$(OUTDIR)\wcefont.obj"  \
	"$(OUTDIR)\wceole.obj"   \
	"$(OUTDIR)\wceoleth.obj"

!elseif "$(LIBTYPE)" == "locdll"
OBJ_FILES=	

!elseif "$(LIBTYPE)" == "atldll"
OBJ_FILES="$(OUTDIR)\stdafx.obj" \
	"$(OUTDIR)\atl.obj"      \
	"$(OUTDIR)\regobj.obj"
!endif # library types

SBR_FILES = $(OBJ_FILES:.obj=.sbr)
#############################################################################


#############################################################################
# Configure nmake build rules

# Primary build target
ALL : $(CLEAN) $(OUTDIR) $(OUTFILE) 

# PCH-clean build (1)
CLEANPCH:
        -@if exist $(OUTDIR)    del /q $(OUTDIR)\*.pch 2> nul

# Clean build (2)
CLEANALL :
	-@if exist $(OUTDIR)    delnode /q $(OUTDIR) 2> nul

# Creating the output directory
$(OUTDIR) :
	-@if not exist $(OUTDIR) mkdir $(OUTDIR)

# Building a library 
$(OUTFILE) : $(RES_FILE) $(OBJ_FILES)
	-@ECHO === Linking...
	-$(LINK) 	$(LINK_FLAGS) 	$(RES_FILE) 	$(OBJ_FILES)

!if "$(BROWSEFILE)" == "1"
	-$(BSCMAKE) $(NOLOGO) -n -o $(PREOUTFILE).bsc @<<
	$(SBR_FILES: =^
)
<<
!endif

# Compiling type library
!if "$(TLB_FILE)" != ""
$(TLB_FILE) : $(IDL_FILE)
	-$(MIDL) $(MIDL_FLAGS) $(IDL_FILE)
!endif

# Compiling resource file
!if "$(RES_FILE)" != ""
$(RES_FILE) : $(TLB_FILE) $(RC_FILE) 
	-$(RSC) $(RSC_FLAGS) $(RC_FILE) 
!endif 

# Compiling stdafx.cpp
$(OUTDIR)\stdafx.obj :
	-@del $(OUTFILE) 2>nul
	$(CPP) $(CPP_FLAGS) $(CREATE_PCH_FLAG) stdafx.cpp 

# Compiling C files
.c{$(OUTDIR)/}.obj::    
	-$(CPP) @<< 
	$(CPP_FLAGS) $<
<<

# Compiling C++ files
.cpp{$(OUTDIR)/}.obj::
	-$(CPP) @<<
	$(CPP_FLAGS) $(USE_PCH_FLAG) $< 
<<

!if "$(CPU)" == "mips" && "$(OSVER)" == "201"
# Workaround for AlderFE implementation of longjmp for MIPS (for MFC exception handling)
# Compiling longjmp.s
$(OUTDIR)\longjmp.obj :
	-@del $(OUTFILE) 2>nul
	$(CPP) $(CPP_FLAGS) longjmp.s 
!endif

#############################################################################
