# Microsoft Developer Studio Project File - Name="MenuWorks" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MenuWorks - Win32 DebugUNICODE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MenuWorks.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MenuWorks.mak" CFG="MenuWorks - Win32 DebugUNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MenuWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuWorks - Win32 DebugUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MenuWorks - Win32 ReleaseMBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ReleaseMBCS"
# PROP BASE Intermediate_Dir "ReleaseMBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ReleaseMBCS"
# PROP Intermediate_Dir "ReleaseMBCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /D "_PSEUDO_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:no /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "MenuWorks - Win32 ReleaseUNICODE"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ReleaseUNICODE"
# PROP BASE Intermediate_Dir "ReleaseUNICODE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ReleaseUNICODE"
# PROP Intermediate_Dir "ReleaseUNICODE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_EXTDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /D "_PSEUDO_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"ReleaseMBCS/MenuWorks95.dll" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:no /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "MenuWorks - Win32 DebugUNICODE"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MenuWorks___Win32_DebugUNICODE"
# PROP BASE Intermediate_Dir "MenuWorks___Win32_DebugUNICODE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUNICODE"
# PROP Intermediate_Dir "DebugUNICODE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /D "_PSEUDO_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /ZI /Od /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /D "_PSEUDO_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:no /machine:I386 /out:"ReleaseUNICODE/MenuWorksNT.dll"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "MenuWorks - Win32 ReleaseMBCS"
# Name "MenuWorks - Win32 ReleaseUNICODE"
# Name "MenuWorks - Win32 DebugUNICODE"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\CcItem.cpp
# End Source File
# Begin Source File

SOURCE=.\crc_32.cpp
# End Source File
# Begin Source File

SOURCE=.\ExampleApp.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\init.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuWorks.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuWorks.def
# End Source File
# Begin Source File

SOURCE=.\MenuWorks.rc
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\utils.cpp
# End Source File
# Begin Source File

SOURCE=.\WinUtil.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\CcItem.h
# End Source File
# Begin Source File

SOURCE=.\crc_32.h
# End Source File
# Begin Source File

SOURCE=.\ExampleApp.h
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.h
# End Source File
# Begin Source File

SOURCE=.\init.h
# End Source File
# Begin Source File

SOURCE=.\MenuWorks.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SldWorks.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# Begin Source File

SOURCE=.\WinUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MenuWorks.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
