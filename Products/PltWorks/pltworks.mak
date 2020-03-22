# ---------------------------------------------------------------------------
VERSION = BCB.04.04
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = pltworks.exe
OBJFILES = obj\pltworks.obj obj\main.obj obj\about.obj obj\CodeGen.obj obj\crc_32.obj \
  obj\utils.obj obj\enum.obj obj\print_sel.obj obj\errors.obj obj\swutils.obj \
  obj\PrintMap.obj obj\print_file.obj obj\FirstDraw.obj obj\print_setup.obj \
  obj\open_file.obj obj\print_draw.obj
RESFILES = PltWorks.res
RESDEPEN = $(RESFILES) main.dfm about.dfm CodeGen.dfm print_sel.dfm errors.dfm PrintMap.dfm
LIBFILES =
LIBRARIES = rxctl4.lib dclusr40.lib bcbsmp40.lib vcldbx40.lib vcldb40.lib vclx40.lib \
  vcl40.lib
SPARELIBS = vcl40.lib vclx40.lib vcldb40.lib vcldbx40.lib bcbsmp40.lib dclusr40.lib \
  rxctl4.lib
PACKAGES = vclx40.bpi vcl40.bpi vcldb40.bpi vcldbx40.bpi bcbsmp40.bpi dclocx40.bpi \
  qrpt40.bpi teeui40.bpi teedb40.bpi tee40.bpi ibsmp40.bpi nmfast40.bpi \
  inetdb40.bpi inet40.bpi
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
CFLAG1 = -I$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;..\..\..\rx\units \
  -Od -Hc -H=v:\vcl40.csm -w -Ve -VF -r- -a8 -5 -k -y -v -vi- \
  -D$(SYSDEFINES);$(USERDEFINES) -c -b- -w-par -w-inl -Vx -tWM
CFLAG2 =
CFLAG3 =
PFLAGS = -U$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib;..\..\..\rx\units;$(RELEASELIBPATH) \
  -I$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;..\..\..\rx\units \
  -N2obj -N0obj \
  -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -$YD \
  -$W -$O- -v -JPHNV -M -JPHNE
RFLAGS = -i$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;..\..\..\rx\units
AFLAGS = /i$(BCB)\source\fledit /i$(BCB)\include /i$(BCB)\include\vcl \
  /i$(BCB)\include\source /i\rx\units /mx /w2 /zi /dUSEPACKAGES
LFLAGS = -L$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib;..\..\..\rx\units;$(RELEASELIBPATH) \
  -aa -Tpe -x -w -v
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
Count=10
Item0=$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;\rx\units
Item1=$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;..\..\..\SldWorks\samples\appcomm
Item2=$(BCB)\source\fledit;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;C:\SldWorks\samples\appcomm
Item3=$(BCB)\source\fledit;..\;..;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source
Item4=..;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source
Item5=..;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;$(BCB)\include\mfc
Item6=..\;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source;$(BCB)\include\mfc
Item7=$(BCB)\include;$(BCB)\include\vcl;$(BCB)\include\source
Item8=..\stkworks;$(BCB)\source\thdtimer;$(BCB)\source\opengl;$(BCB)\bin;$(BCB)\source\fnpnumericedit;$(BCB)\source\spinfloat;$(BCB)\source\floatedit;$(BCB)\examples\controls;$(BCB)\include;$(BCB)\include\vcl
Item9=$(BCB)\source\thdtimer;$(BCB)\source\opengl;$(BCB)\bin;$(BCB)\source\fnpnumericedit;$(BCB)\source\spinfloat;$(BCB)\source\floatedit;$(BCB)\examples\controls;$(BCB)\include;$(BCB)\include\vcl

[HistoryLists\hlLibraryPath]
Count=10
Item0=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib;\rx\units
Item1=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib
Item2=..\;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib
Item3=..;$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source;$(BCB)\Projects\Lib
Item4=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\source
Item5=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\lib\sourceItem1=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\sourceItem1=$(BCB)\lib;$(BCB)\lib\obj;$(BCB)\sourceItem1=..\stkworks;$(BCB)\source\thdtimer;$(BCB)\source\opengl;$(BCB)\bin;$(BCB)\source\fnpnumericedit;$(BCB)\source\spinfloat;$(BCB)\source\floatedit;$(BCB)\examples\controls;$(BCB)\lib;$(BCB)\lib\obj
Item6=
Item7=
Item8=
Item9=$(BCB)\source\thdtimer;$(BCB)\source\opengl;$(BCB)\bin;$(BCB)\source\fnpnumericedit;$(BCB)\source\spinfloat;$(BCB)\source\floatedit;$(BCB)\examples\controls;$(BCB)\lib;$(BCB)\lib\obj

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
RemoteHost=
RemotePath=
RemoteDebug=0

[Compiler]
InMemoryExe=0
ShowInfoMsgs=1

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
