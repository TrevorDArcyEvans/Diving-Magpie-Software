# Microsoft Developer Studio Generated NMAKE File, Based on MenuWorks.dsp
!IF "$(CFG)" == ""
CFG=MenuWorks - Win32 ReleaseUNICODE
!MESSAGE No configuration specified. Defaulting to MenuWorks - Win32 ReleaseUNICODE.
!ENDIF 

!IF "$(CFG)" != "MenuWorks - Win32 ReleaseMBCS" && "$(CFG)" != "MenuWorks - Win32 ReleaseUNICODE"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MenuWorks.mak" CFG="MenuWorks - Win32 ReleaseUNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MenuWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MenuWorks - Win32 ReleaseMBCS"

OUTDIR=.\ReleaseMBCS
INTDIR=.\ReleaseMBCS
# Begin Custom Macros
OutDir=.\ReleaseMBCS
# End Custom Macros

ALL : "$(OUTDIR)\MenuWorks95.dll" "$(OUTDIR)\MenuWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\init.sbr"
	-@erase "$(INTDIR)\MenuWorks.obj"
	-@erase "$(INTDIR)\MenuWorks.pch"
	-@erase "$(INTDIR)\MenuWorks.res"
	-@erase "$(INTDIR)\MenuWorks.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\MenuWorks.bsc"
	-@erase "$(OUTDIR)\MenuWorks95.dll"
	-@erase "$(OUTDIR)\MenuWorks95.exp"
	-@erase "$(OUTDIR)\MenuWorks95.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /D "_PSEUDO_DEBUG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MenuWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\MenuWorks.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\init.sbr" \
	"$(INTDIR)\MenuWorks.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\MenuWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MenuWorks95.pdb" /machine:I386 /def:".\MenuWorks.def" /out:"$(OUTDIR)\MenuWorks95.dll" /implib:"$(OUTDIR)\MenuWorks95.lib" /pdbtype:sept 
DEF_FILE= \
	".\MenuWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\MenuWorks.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\MenuWorks.res"

"$(OUTDIR)\MenuWorks95.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MenuWorks - Win32 ReleaseUNICODE"

OUTDIR=.\ReleaseUNICODE
INTDIR=.\ReleaseUNICODE
# Begin Custom Macros
OutDir=.\ReleaseUNICODE
# End Custom Macros

ALL : "$(OUTDIR)\MenuWorksNT.dll" "$(OUTDIR)\MenuWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\init.sbr"
	-@erase "$(INTDIR)\MenuWorks.obj"
	-@erase "$(INTDIR)\MenuWorks.pch"
	-@erase "$(INTDIR)\MenuWorks.res"
	-@erase "$(INTDIR)\MenuWorks.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\MenuWorks.bsc"
	-@erase "$(OUTDIR)\MenuWorksNT.dll"
	-@erase "$(OUTDIR)\MenuWorksNT.exp"
	-@erase "$(OUTDIR)\MenuWorksNT.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /D "_PSEUDO_DEBUG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MenuWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\MenuWorks.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\init.sbr" \
	"$(INTDIR)\MenuWorks.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\MenuWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MenuWorksNT.pdb" /machine:I386 /def:".\MenuWorks.def" /out:"$(OUTDIR)\MenuWorksNT.dll" /implib:"$(OUTDIR)\MenuWorksNT.lib" 
DEF_FILE= \
	".\MenuWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\MenuWorks.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\MenuWorks.res"

"$(OUTDIR)\MenuWorksNT.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MenuWorks.dep")
!INCLUDE "MenuWorks.dep"
!ELSE 
!MESSAGE Warning: cannot find "MenuWorks.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MenuWorks - Win32 ReleaseMBCS" || "$(CFG)" == "MenuWorks - Win32 ReleaseUNICODE"
SOURCE=.\About.cpp

"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\CcItem.cpp

"$(INTDIR)\CcItem.obj"	"$(INTDIR)\CcItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\crc_32.cpp

"$(INTDIR)\crc_32.obj"	"$(INTDIR)\crc_32.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\ExampleApp.cpp

"$(INTDIR)\ExampleApp.obj"	"$(INTDIR)\ExampleApp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\HandleEvents.cpp

"$(INTDIR)\HandleEvents.obj"	"$(INTDIR)\HandleEvents.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\init.cpp

"$(INTDIR)\init.obj"	"$(INTDIR)\init.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\MenuWorks.cpp

"$(INTDIR)\MenuWorks.obj"	"$(INTDIR)\MenuWorks.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\MenuWorks.rc

"$(INTDIR)\MenuWorks.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Register.cpp

"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MenuWorks - Win32 ReleaseMBCS"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /D "_PSEUDO_DEBUG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MenuWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MenuWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MenuWorks - Win32 ReleaseUNICODE"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /D "_PSEUDO_DEBUG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MenuWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MenuWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\utils.cpp

"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"


SOURCE=.\WinUtil.cpp

"$(INTDIR)\WinUtil.obj"	"$(INTDIR)\WinUtil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MenuWorks.pch"



!ENDIF 

