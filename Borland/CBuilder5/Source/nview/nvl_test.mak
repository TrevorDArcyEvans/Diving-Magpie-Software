# ---------------------------------------------------------------------------
VERSION = BCB.04.04
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = nvl_test.exe
OBJFILES = nvl_test.obj main.obj
RESFILES = nvl_test.res
RESDEPEN = $(RESFILES) main.dfm
LIBFILES = nviewlib.lib
LIBRARIES = vcldbx40.lib vcldb40.lib vclx40.lib vcl40.lib
SPARELIBS = vcl40.lib vclx40.lib vcldb40.lib vcldbx40.lib
PACKAGES = Vcl40.bpi Vclx40.bpi Qrpt40.bpi Vcldb40.bpi ibsmp40.bpi vcldbx40.bpi \
  TeeUI40.bpi teedb40.bpi tee40.bpi nmfast40.bpi OE.bpi bcbsmp40.bpi dclusr40.bpi \
  scrb4.bpi scrgl.bpi dclocx40.bpi traypkg.bpi XView3D.bpi ZipPack.bpi rxctl4.bpi \
  rxdb4.bpi
PATHASM = .;
PATHCPP = .;
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
SYSDEFINES = NO_STRICT
USERDEFINES =
DEFFILE =
# ---------------------------------------------------------------------------
CFLAG1 = -I$(BCB)\include;$(BCB)\include\vcl -Od -Hc -H=v:\vcl40.csm -w -Ve -r- -a4 -k \
  -y -v -vi- -D$(SYSDEFINES);$(USERDEFINES) -c -b- -w-par -w-inl -Vx -tWM
CFLAG2 =
CFLAG3 =
PFLAGS = -U$(BCB)\lib\obj;$(BCB)\lib;"G:\PROGRAMS\CBUILDER\PROJECTS\NVIEWLIB\";$(DEBUGLIBPATH) \
  -I$(BCB)\include;$(BCB)\include\vcl \
  -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -$YD \
  -$W -$O- -v -JPHNV -M -JPHNE
RFLAGS = -i$(BCB)\include;$(BCB)\include\vcl
AFLAGS = /i$(BCB)\include /i$(BCB)\include\vcl /mx /w2 /zd
LFLAGS = -L$(BCB)\lib\obj;$(BCB)\lib;"G:\PROGRAMS\CBUILDER\PROJECTS\NVIEWLIB\";$(DEBUGLIBPATH) \
  -aa -Tpe -x -v
IFLAGS =
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib nviewlib.lib
# ---------------------------------------------------------------------------
.autodepend

!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0
Locale=1033
CodePage=1252

[Debugging]
DebugSourceDirs=

[Parameters]
RunParams=
HostApplication=
RemoteHost=
RemotePath=
RemoteDebug=0

[Compiler]
InMemoryExe=0
ShowInfoMsgs=0

!endif

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
