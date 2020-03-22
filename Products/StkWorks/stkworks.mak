# ---------------------------------------------------------------------------
VERSION = BCB.04.04
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = StkWorks.exe
OBJFILES = obj\StkWorks.obj obj\main.obj obj\process.obj obj\about.obj obj\swOle.obj \
  obj\enum.obj obj\init.obj obj\CodeGen.obj obj\crc_32.obj obj\utils.obj
RESFILES = stkworks.res
RESDEPEN = $(RESFILES) main.dfm about.dfm CodeGen.dfm
LIBFILES =
#LIBRARIES = bcbsmp35.lib vcldbx35.lib vcldb35.lib vclx35.lib vcl35.lib
LIBRARIES = dclusr40.lib bcbsmp40.lib vcldbx40.lib vcldb40.lib vclx40.lib vcl40.lib
SPARELIBS = vcl40.lib vclx40.lib vcldb40.lib vcldbx40.lib bcbsmp40.lib dclusr40.lib
PACKAGES = vcl40.bpi vcldb40.bpi vcldbx40.bpi bcbsmp40.bpi dclocx40.bpi qrpt40.bpi \
  teeui40.bpi teedb40.bpi tee40.bpi ibsmp40.bpi nmfast40.bpi inetdb40.bpi \
  inet40.bpi
PATHASM = .;
PATHCPP = .;
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
SYSDEFINES = NO_STRICT
USERDEFINES = $(SYSDEFINES);$(USERDEFINES)
DEFFILE =
# ---------------------------------------------------------------------------
CFLAG1 = -I$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source -Od -Hc \
  -H=v:\vcl40.csm -w -Ve -r- -a8 -d -k -y -v -vi- -D$(SYSDEFINES);$(USERDEFINES) \
  -c -b- -w-par -w-inl -Vx -tWM -tWM -tWM
CFLAG2 =
CFLAG3 =
PFLAGS = -U$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib;$(RELEASELIBPATH) \
  -I$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source -N2obj -N0obj \
  -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
  -D$(SYSDEFINES);$(USERDEFINES) -$YD -$W -$S -$R -$Q -$O- -JPHNV -M -JPHNE \
  -JPHNE -JPHNE
RFLAGS = -i$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source \
  -D$(SYSDEFINES);$(USERDEFINES)
AFLAGS = /i$(BCB)\include /i$(BCB)\include\vcl /i$(BCB)\include\source /d$(SYSDEFINES) \
  /d$(USERDEFINES) /mx /w2 /zi
LFLAGS = -L$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib;$(RELEASELIBPATH) \
  -aa -Tpe -x -w -v
IFLAGS =
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj sysinit.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
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

[HistoryLists\hlIncludePath]
Count=1
Item0=$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source

[HistoryLists\hlLibraryPath]
Count=2
Item0=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib
Item1=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source

[HistoryLists\hlConditionals]
Count=2
Item0=$(SYSDEFINES);$(USERDEFINES)
Item1=_RWSTD_MULTI_THREAD

[HistoryLists\hlUnitAliases]
Count=1
Item0=WinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE

[HistoryLists\hlIntOutputDir]
Count=1
Item0=obj

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
