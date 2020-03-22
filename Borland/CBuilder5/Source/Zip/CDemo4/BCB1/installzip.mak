# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = InstallZip.exe
OBJFILES = InstallZip.obj Main.obj Install.obj
RESFILES = InstallZip.res ZipMsgUS.res
RESDEPEN = $(RESFILES) Main.dfm Install.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -Hc -w -k- -r -vi -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -I$(BCB)\projects\zipbuilder;$(BCB)\newcomps\supertimer;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids \
   -H=$(BCB)\lib\vcl.csm 
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
   -U$(BCB)\projects\zipbuilder;$(BCB)\newcomps\supertimer;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\newcomps\grids \
   -I$(BCB)\projects\zipbuilder;$(BCB)\newcomps\supertimer;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids \
   -$L- -$D- -JPHNV -M     
RFLAGS = -i$(BCB)\projects\zipbuilder;$(BCB)\newcomps\supertimer;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids 
LFLAGS = -L$(BCB)\projects\zipbuilder;$(BCB)\newcomps\supertimer;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\newcomps\grids \
   -aa -Tpe -x -V4.0 
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

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
