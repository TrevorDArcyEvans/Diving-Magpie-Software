# ---------------------------------------------------------------------------
VERSION = BCB.03
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = OrbWorks.exe
OBJFILES = obj\OrbWorks.obj obj\main.obj obj\about.obj obj\init.obj obj\process.obj \
  obj\swOle.obj obj\enum.obj obj\orb.obj obj\CodeGen.obj obj\crc_32.obj \
  obj\utils.obj
RESFILES = OrbWorks.res
RESDEPEN = $(RESFILES) main.dfm about.dfm CodeGen.dfm
LIBFILES =
LIBRARIES = bcbsmp35.lib vcldbx35.lib vcldb35.lib vclx35.lib vcl35.lib
SPARELIBS = vcl35.lib vclx35.lib vcldb35.lib vcldbx35.lib bcbsmp35.lib
PACKAGES = vclx35.bpi VCL35.bpi vcldb35.bpi vcldbx35.bpi bcbsmp35.bpi dclocx35.bpi \
  Qrpt35.bpi teeui35.bpi teedb35.bpi tee35.bpi ibsmp35.bpi NMFast35.bpi \
  inetdb35.bpi inet35.bpi
PATHASM = .;
PATHCPP = .;
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
DEFFILE =
# ---------------------------------------------------------------------------
CFLAG1 = -Od -Hc -w -Ve -r- -k -y -v -vi- -c -b- -w-par -w-inl -Vx
CFLAG2 = -I..\stkworks;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source \
  -H=v:\vcl.csm
CFLAG3 = -5
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
  -N2obj -N0obj \
  -U..\stkworks;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(RELEASELIBPATH) \
  -I..\stkworks;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source -H -W -$Y \
  -$W -$R -$Q -$O- -JPHNV -M
RFLAGS = -i..\stkworks;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source
AFLAGS = /i..\stkworks /i$(BCB)\include /i$(BCB)\include\vcl /i$(BCB)\include\source /mx \
  /w2 /zi /dUSEPACKAGES
LFLAGS = -L..\stkworks;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(RELEASELIBPATH) -aa \
  -Tpe -x -w -v
IFLAGS =
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
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

[Version Info Keys]
FileVersion=1.0.0.0

[HistoryLists\hlIncludePath]
Count=2
Item0=..\stkworks;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source
Item1=$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source

[HistoryLists\hlLibraryPath]
Count=4
Item0=..\stkworks;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source
Item1=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source
Item2=..\stkworks;$(BCB)\bin;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source
Item3=$(BCB)\bin;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source

[HistoryLists\hlConditionals]
Count=1
Item0=USEPACKAGES

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
