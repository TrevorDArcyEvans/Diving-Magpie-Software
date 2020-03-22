# Microsoft Developer Studio Generated NMAKE File, Based on UnfragWorks.dsp
!IF "$(CFG)" == ""
CFG=UnfragWorks - Win32 ReleaseUNICODE
!MESSAGE No configuration specified. Defaulting to UnfragWorks - Win32 ReleaseUNICODE.
!ENDIF 

!IF "$(CFG)" != "UnfragWorks - Win32 ReleaseUNICODE" && "$(CFG)" != "UnfragWorks - Win32 ReleaseMBCS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UnfragWorks.mak" CFG="UnfragWorks - Win32 ReleaseUNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UnfragWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnfragWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "UnfragWorks - Win32 ReleaseUNICODE"

OUTDIR=.\ReleaseUNICODE
INTDIR=.\ReleaseUNICODE
# Begin Custom Macros
OutDir=.\ReleaseUNICODE
# End Custom Macros

ALL : "$(OUTDIR)\UnfragWorksNT.dll" "$(OUTDIR)\UnfragWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UnfragWorks.obj"
	-@erase "$(INTDIR)\UnfragWorks.pch"
	-@erase "$(INTDIR)\UnfragWorks.res"
	-@erase "$(INTDIR)\UnfragWorks.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\UnfragWorks.bsc"
	-@erase "$(OUTDIR)\UnfragWorksNT.dll"
	-@erase "$(OUTDIR)\UnfragWorksNT.exp"
	-@erase "$(OUTDIR)\UnfragWorksNT.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UnfragWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\UnfragWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UnfragWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UnfragWorks.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\UnfragWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\UnfragWorksNT.pdb" /machine:I386 /def:".\UnfragWorks.def" /out:"$(OUTDIR)\UnfragWorksNT.dll" /implib:"$(OUTDIR)\UnfragWorksNT.lib" 
DEF_FILE= \
	".\UnfragWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UnfragWorks.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\UnfragWorks.res"

"$(OUTDIR)\UnfragWorksNT.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "UnfragWorks - Win32 ReleaseMBCS"

OUTDIR=.\ReleaseMBCS
INTDIR=.\ReleaseMBCS
# Begin Custom Macros
OutDir=.\ReleaseMBCS
# End Custom Macros

ALL : "$(OUTDIR)\UnfragWorks95.dll" "$(OUTDIR)\UnfragWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UnfragWorks.obj"
	-@erase "$(INTDIR)\UnfragWorks.pch"
	-@erase "$(INTDIR)\UnfragWorks.res"
	-@erase "$(INTDIR)\UnfragWorks.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\UnfragWorks.bsc"
	-@erase "$(OUTDIR)\UnfragWorks95.dll"
	-@erase "$(OUTDIR)\UnfragWorks95.exp"
	-@erase "$(OUTDIR)\UnfragWorks95.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UnfragWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\UnfragWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UnfragWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UnfragWorks.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\UnfragWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\UnfragWorks95.pdb" /machine:I386 /def:".\UnfragWorks.def" /out:"$(OUTDIR)\UnfragWorks95.dll" /implib:"$(OUTDIR)\UnfragWorks95.lib" 
DEF_FILE= \
	".\UnfragWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UnfragWorks.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\UnfragWorks.res"

"$(OUTDIR)\UnfragWorks95.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("UnfragWorks.dep")
!INCLUDE "UnfragWorks.dep"
!ELSE 
!MESSAGE Warning: cannot find "UnfragWorks.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "UnfragWorks - Win32 ReleaseUNICODE" || "$(CFG)" == "UnfragWorks - Win32 ReleaseMBCS"
SOURCE=.\About.cpp

"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\CcItem.cpp

"$(INTDIR)\CcItem.obj"	"$(INTDIR)\CcItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\crc_32.cpp

"$(INTDIR)\crc_32.obj"	"$(INTDIR)\crc_32.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\Debug.cpp

"$(INTDIR)\Debug.obj"	"$(INTDIR)\Debug.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\ExampleApp.cpp

"$(INTDIR)\ExampleApp.obj"	"$(INTDIR)\ExampleApp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\HandleEvents.cpp

"$(INTDIR)\HandleEvents.obj"	"$(INTDIR)\HandleEvents.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\Register.cpp

"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "UnfragWorks - Win32 ReleaseUNICODE"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UnfragWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\UnfragWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "UnfragWorks - Win32 ReleaseMBCS"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UnfragWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\UnfragWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UnfragWorks.cpp

"$(INTDIR)\UnfragWorks.obj"	"$(INTDIR)\UnfragWorks.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\UnfragWorks.rc

"$(INTDIR)\UnfragWorks.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\utils.cpp

"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"


SOURCE=.\WinUtil.cpp

"$(INTDIR)\WinUtil.obj"	"$(INTDIR)\WinUtil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UnfragWorks.pch"



!ENDIF 

