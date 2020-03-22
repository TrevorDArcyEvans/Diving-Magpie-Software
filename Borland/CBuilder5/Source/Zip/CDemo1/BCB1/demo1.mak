# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = Demo1.exe
OBJFILES = Demo1.obj Main.obj AddFiles.obj ExtractFiles.obj Message.obj SFX.obj \
   Rename.obj
RESFILES = Demo1.res ZipMsgUS.res
RESDEPEN = $(RESFILES) Main.dfm AddFiles.dfm ExtractFiles.dfm Message.dfm SFX.dfm \
   Rename.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -Hc -w -d -k- -r -vi -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -I$(BCB)\projects\zipbuilder;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids \
   -H=$(BCB)\lib\vcl.csm 
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
   -U$(BCB)\projects\zipbuilder;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\newcomps\grids \
   -I$(BCB)\projects\zipbuilder;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids \
   -$L- -$D- -JPHNV -M
RFLAGS = -i$(BCB)\projects\zipbuilder;$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\newcomps\grids \
   -32 -v 
LFLAGS = -L$(BCB)\projects\zipbuilder;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\newcomps\grids \
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
    $(BCB)\BIN\brcc32 $(RFLAGS) <$
#-----------------------------------------------------------------------------
