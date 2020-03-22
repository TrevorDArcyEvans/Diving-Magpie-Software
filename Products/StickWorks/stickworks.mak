# Microsoft Developer Studio Generated NMAKE File, Based on StickWorks.dsp
!IF "$(CFG)" == ""
CFG=STICKWORKS - WIN32 RELEASEUNICODE
!MESSAGE No configuration specified. Defaulting to STICKWORKS - WIN32 RELEASEUNICODE.
!ENDIF 

!IF "$(CFG)" != "StickWorks - Win32 ReleaseUNICODE" && "$(CFG)" != "StickWorks - Win32 ReleaseMBCS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StickWorks.mak" CFG="StickWorks - Win32 ReleaseUNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StickWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StickWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "StickWorks - Win32 ReleaseUNICODE"

OUTDIR=.\ReleaseUNICODE
INTDIR=.\ReleaseUNICODE
# Begin Custom Macros
OutDir=.\ReleaseUNICODE
# End Custom Macros

ALL : "$(OUTDIR)\StkWksNT.dll" "$(OUTDIR)\StickWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\Configure.obj"
	-@erase "$(INTDIR)\Configure.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\JoyPanel.obj"
	-@erase "$(INTDIR)\JoyPanel.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StickWorks.obj"
	-@erase "$(INTDIR)\StickWorks.pch"
	-@erase "$(INTDIR)\StickWorks.res"
	-@erase "$(INTDIR)\StickWorks.sbr"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\timer.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\StickWorks.bsc"
	-@erase "$(OUTDIR)\StkWksNT.dll"
	-@erase "$(OUTDIR)\StkWksNT.exp"
	-@erase "$(OUTDIR)\StkWksNT.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StickWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\StickWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StickWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\Configure.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\JoyPanel.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StickWorks.sbr" \
	"$(INTDIR)\timer.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\StickWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\StkWksNT.pdb" /machine:I386 /def:".\StickWorks.def" /out:"$(OUTDIR)\StkWksNT.dll" /implib:"$(OUTDIR)\StkWksNT.lib" 
DEF_FILE= \
	".\StickWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\Configure.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\JoyPanel.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StickWorks.obj" \
	"$(INTDIR)\timer.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\StickWorks.res"

"$(OUTDIR)\StkWksNT.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StickWorks - Win32 ReleaseMBCS"

OUTDIR=.\ReleaseMBCS
INTDIR=.\ReleaseMBCS
# Begin Custom Macros
OutDir=.\ReleaseMBCS
# End Custom Macros

ALL : "$(OUTDIR)\StkWks95.dll" "$(OUTDIR)\StickWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\Configure.obj"
	-@erase "$(INTDIR)\Configure.sbr"
	-@erase "$(INTDIR)\crc_32.obj"
	-@erase "$(INTDIR)\crc_32.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\JoyPanel.obj"
	-@erase "$(INTDIR)\JoyPanel.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StickWorks.obj"
	-@erase "$(INTDIR)\StickWorks.pch"
	-@erase "$(INTDIR)\StickWorks.res"
	-@erase "$(INTDIR)\StickWorks.sbr"
	-@erase "$(INTDIR)\timer.obj"
	-@erase "$(INTDIR)\timer.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinUtil.obj"
	-@erase "$(INTDIR)\WinUtil.sbr"
	-@erase "$(OUTDIR)\StickWorks.bsc"
	-@erase "$(OUTDIR)\StkWks95.dll"
	-@erase "$(OUTDIR)\StkWks95.exp"
	-@erase "$(OUTDIR)\StkWks95.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StickWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\StickWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\StickWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\Configure.sbr" \
	"$(INTDIR)\crc_32.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\JoyPanel.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StickWorks.sbr" \
	"$(INTDIR)\timer.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\WinUtil.sbr"

"$(OUTDIR)\StickWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\StkWks95.pdb" /machine:I386 /def:".\StickWorks.def" /out:"$(OUTDIR)\StkWks95.dll" /implib:"$(OUTDIR)\StkWks95.lib" 
DEF_FILE= \
	".\StickWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\Configure.obj" \
	"$(INTDIR)\crc_32.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\JoyPanel.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StickWorks.obj" \
	"$(INTDIR)\timer.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\WinUtil.obj" \
	"$(INTDIR)\StickWorks.res"

"$(OUTDIR)\StkWks95.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("StickWorks.dep")
!INCLUDE "StickWorks.dep"
!ELSE 
!MESSAGE Warning: cannot find "StickWorks.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "StickWorks - Win32 ReleaseUNICODE" || "$(CFG)" == "StickWorks - Win32 ReleaseMBCS"
SOURCE=.\About.cpp

"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\CcItem.cpp

"$(INTDIR)\CcItem.obj"	"$(INTDIR)\CcItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\Configure.cpp

"$(INTDIR)\Configure.obj"	"$(INTDIR)\Configure.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\crc_32.cpp

"$(INTDIR)\crc_32.obj"	"$(INTDIR)\crc_32.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\ExampleApp.cpp

"$(INTDIR)\ExampleApp.obj"	"$(INTDIR)\ExampleApp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\HandleEvents.cpp

"$(INTDIR)\HandleEvents.obj"	"$(INTDIR)\HandleEvents.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\JoyPanel.cpp

"$(INTDIR)\JoyPanel.obj"	"$(INTDIR)\JoyPanel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\Register.cpp

"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "StickWorks - Win32 ReleaseUNICODE"

CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StickWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\StickWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "StickWorks - Win32 ReleaseMBCS"

CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\StickWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\StickWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StickWorks.cpp

"$(INTDIR)\StickWorks.obj"	"$(INTDIR)\StickWorks.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\StickWorks.rc

"$(INTDIR)\StickWorks.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\timer.cpp

"$(INTDIR)\timer.obj"	"$(INTDIR)\timer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\utils.cpp

"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"


SOURCE=.\WinUtil.cpp

"$(INTDIR)\WinUtil.obj"	"$(INTDIR)\WinUtil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\StickWorks.pch"



!ENDIF 

