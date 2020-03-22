# Microsoft Developer Studio Project File - Name="VRMLWorks" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VRMLWorks - Win32 DebugMBCS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VRMLWorks.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VRMLWorks.mak" CFG="VRMLWorks - Win32 DebugMBCS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VRMLWorks - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VRMLWorks - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VRMLWorks - Win32 DebugUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VRMLWorks - Win32 DebugMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VRMLWorks - Win32 ReleaseUNICODE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VRMLWorks - Win32 ReleaseMBCS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VRMLWorks - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/VRMLWksNT.dll"

!ELSEIF  "$(CFG)" == "VRMLWorks - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/VRMLWksNT.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "VRMLWorks - Win32 DebugUNICODE"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugUNICODE"
# PROP BASE Intermediate_Dir "DebugUNICODE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUNICODE"
# PROP Intermediate_Dir "DebugUNICODE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/VRMLWksNT.dll" /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"DebugUNICODE/VRMLWksNT.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "VRMLWorks - Win32 DebugMBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMBCS"
# PROP BASE Intermediate_Dir "DebugMBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMBCS"
# PROP Intermediate_Dir "DebugMBCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/VRMLWksNT.dll" /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"DebugMBCS/VRMLWks95.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "VRMLWorks - Win32 ReleaseUNICODE"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUNICODE"
# PROP BASE Intermediate_Dir "ReleaseUNICODE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUNICODE"
# PROP Intermediate_Dir "ReleaseUNICODE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/VRMLWksNT.dll"
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseUNICODE/VRMLWksNT.dll"

!ELSEIF  "$(CFG)" == "VRMLWorks - Win32 ReleaseMBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMBCS"
# PROP BASE Intermediate_Dir "ReleaseMBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMBCS"
# PROP Intermediate_Dir "ReleaseMBCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\Common" /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/VRMLWksNT.dll"
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseMBCS/VRMLWks95.dll"

!ENDIF 

# Begin Target

# Name "VRMLWorks - Win32 Release"
# Name "VRMLWorks - Win32 Debug"
# Name "VRMLWorks - Win32 DebugUNICODE"
# Name "VRMLWorks - Win32 DebugMBCS"
# Name "VRMLWorks - Win32 ReleaseUNICODE"
# Name "VRMLWorks - Win32 ReleaseMBCS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CcItem.cpp
# End Source File
# Begin Source File

SOURCE=..\DMS_Common\DMS_Comm.idl
# ADD MTL /h "DMS_Comm.h"
# End Source File
# Begin Source File

SOURCE=..\DMS_ProgPipe\DMS_ProgPipe.idl
# ADD MTL /h "DMS_ProgPipe.h"
# End Source File
# Begin Source File

SOURCE=.\ExampleApp.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\SldWorks\samples\appcomm\sldworks_i.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VRMLWorks.cpp
# End Source File
# Begin Source File

SOURCE=.\VRMLWorks.def
# End Source File
# Begin Source File

SOURCE=.\VRMLWorks.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CcItem.h
# End Source File
# Begin Source File

SOURCE=.\ExampleApp.h
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.h
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

SOURCE=.\VRMLWorks.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\VRMLWorks.ico
# End Source File
# Begin Source File

SOURCE=.\res\VRMLWorks.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
