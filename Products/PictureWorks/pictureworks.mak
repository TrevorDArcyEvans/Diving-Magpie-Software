# Microsoft Developer Studio Generated NMAKE File, Based on PictureWorks.dsp
!IF "$(CFG)" == ""
CFG=PICTUREWORKS - WIN32 RELEASEUNICODE
!MESSAGE No configuration specified. Defaulting to PICTUREWORKS - WIN32 RELEASEUNICODE.
!ENDIF 

!IF "$(CFG)" != "PictureWorks - Win32 ReleaseUNICODE" && "$(CFG)" != "PictureWorks - Win32 ReleaseMBCS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PictureWorks.mak" CFG="PICTUREWORKS - WIN32 RELEASEUNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PictureWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PictureWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "PictureWorks - Win32 ReleaseUNICODE"

OUTDIR=.\ReleaseUNICODE
INTDIR=.\ReleaseUNICODE
# Begin Custom Macros
OutDir=.\ReleaseUNICODE
# End Custom Macros

ALL : "$(OUTDIR)\PictureWorksNT.dll" "$(OUTDIR)\PictureWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\PictureWorks.obj"
	-@erase "$(INTDIR)\PictureWorks.pch"
	-@erase "$(INTDIR)\PictureWorks.res"
	-@erase "$(INTDIR)\PictureWorks.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PictureWorks.bsc"
	-@erase "$(OUTDIR)\PictureWorksNT.dll"
	-@erase "$(OUTDIR)\PictureWorksNT.exp"
	-@erase "$(OUTDIR)\PictureWorksNT.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PictureWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\PictureWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PictureWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\PictureWorks.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\PictureWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\PictureWorksNT.pdb" /machine:I386 /def:".\PictureWorks.def" /out:"$(OUTDIR)\PictureWorksNT.dll" /implib:"$(OUTDIR)\PictureWorksNT.lib" 
DEF_FILE= \
	".\PictureWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\PictureWorks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\PictureWorks.res"

"$(OUTDIR)\PictureWorksNT.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PictureWorks - Win32 ReleaseMBCS"

OUTDIR=.\ReleaseMBCS
INTDIR=.\ReleaseMBCS
# Begin Custom Macros
OutDir=.\ReleaseMBCS
# End Custom Macros

ALL : "$(OUTDIR)\PictureWorks95.dll" "$(OUTDIR)\PictureWorks.bsc"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\CcItem.obj"
	-@erase "$(INTDIR)\CcItem.sbr"
	-@erase "$(INTDIR)\ExampleApp.obj"
	-@erase "$(INTDIR)\ExampleApp.sbr"
	-@erase "$(INTDIR)\HandleEvents.obj"
	-@erase "$(INTDIR)\HandleEvents.sbr"
	-@erase "$(INTDIR)\PictureWorks.obj"
	-@erase "$(INTDIR)\PictureWorks.pch"
	-@erase "$(INTDIR)\PictureWorks.res"
	-@erase "$(INTDIR)\PictureWorks.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PictureWorks.bsc"
	-@erase "$(OUTDIR)\PictureWorks95.dll"
	-@erase "$(OUTDIR)\PictureWorks95.exp"
	-@erase "$(OUTDIR)\PictureWorks95.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PictureWorks.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)\PictureWorks.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PictureWorks.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\CcItem.sbr" \
	"$(INTDIR)\ExampleApp.sbr" \
	"$(INTDIR)\HandleEvents.sbr" \
	"$(INTDIR)\PictureWorks.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\PictureWorks.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\PictureWorks95.pdb" /machine:I386 /def:".\PictureWorks.def" /out:"$(OUTDIR)\PictureWorks95.dll" /implib:"$(OUTDIR)\PictureWorks95.lib" 
DEF_FILE= \
	".\PictureWorks.def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\CcItem.obj" \
	"$(INTDIR)\ExampleApp.obj" \
	"$(INTDIR)\HandleEvents.obj" \
	"$(INTDIR)\PictureWorks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\PictureWorks.res"

"$(OUTDIR)\PictureWorks95.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("PictureWorks.dep")
!INCLUDE "PictureWorks.dep"
!ELSE 
!MESSAGE Warning: cannot find "PictureWorks.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PictureWorks - Win32 ReleaseUNICODE" || "$(CFG)" == "PictureWorks - Win32 ReleaseMBCS"
SOURCE=.\About.cpp

"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PictureWorks.pch"


SOURCE=.\CcItem.cpp

"$(INTDIR)\CcItem.obj"	"$(INTDIR)\CcItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PictureWorks.pch"


SOURCE=.\ExampleApp.cpp

"$(INTDIR)\ExampleApp.obj"	"$(INTDIR)\ExampleApp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PictureWorks.pch"


SOURCE=.\HandleEvents.cpp

"$(INTDIR)\HandleEvents.obj"	"$(INTDIR)\HandleEvents.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PictureWorks.pch"


SOURCE=.\PictureWorks.cpp

"$(INTDIR)\PictureWorks.obj"	"$(INTDIR)\PictureWorks.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PictureWorks.pch"


SOURCE=.\PictureWorks.rc

"$(INTDIR)\PictureWorks.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "PictureWorks - Win32 ReleaseUNICODE"

CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PictureWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\PictureWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PictureWorks - Win32 ReleaseMBCS"

CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PictureWorks.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\PictureWorks.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

