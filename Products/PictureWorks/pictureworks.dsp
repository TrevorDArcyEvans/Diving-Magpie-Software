# Microsoft Developer Studio Project File - Name="PictureWorks" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PICTUREWORKS - WIN32 RELEASEUNICODE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PictureWorks.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PictureWorks - Win32 ReleaseUNICODE"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUNICODE"
# PROP BASE Intermediate_Dir "ReleaseUNICODE"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUNICODE"
# PROP Intermediate_Dir "ReleaseUNICODE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseUNICODE/PictureWorksNT.dll"

!ELSEIF  "$(CFG)" == "PictureWorks - Win32 ReleaseMBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PictureWorks___Win32_ReleaseMBCS"
# PROP BASE Intermediate_Dir "PictureWorks___Win32_ReleaseMBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMBCS"
# PROP Intermediate_Dir "ReleaseMBCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "C:\SldWorks\Samples\AppComm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_EXTDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseUNICODE/PictureWorksNT.dll"
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseMBCS/PictureWorks95.dll"

!ENDIF 

# Begin Target

# Name "PictureWorks - Win32 ReleaseUNICODE"
# Name "PictureWorks - Win32 ReleaseMBCS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\CcItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ExampleApp.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureWorks.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureWorks.def
# End Source File
# Begin Source File

SOURCE=.\PictureWorks.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
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

SOURCE=.\ExampleApp.h
# End Source File
# Begin Source File

SOURCE=.\HandleEvents.h
# End Source File
# Begin Source File

SOURCE=.\PictureWorks.h
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PictureWorks.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
