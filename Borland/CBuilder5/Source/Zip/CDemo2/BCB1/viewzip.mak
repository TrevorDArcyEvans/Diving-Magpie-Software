# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = Viewzip.exe
OBJFILES = Viewzip.obj uViewZip.obj
RESFILES = ViewZip.res
RESDEPEN = $(RESFILES) uViewZip.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -Od -Hc -w -k -r- -y -v -vi- -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -I$(BCB)\projects\zipbuilder;$(BCB)\comp;$(BCB)\include;$(BCB)\include\vcl;c:\cpplib \
   -H=$(BCB)\lib\vcld.csm 
PFLAGS = -U$(BCB)\projects\zipbuilder;$(BCB)\comp;$(BCB)\lib\obj;$(BCB)\lib;c:\cpplib \
   -I$(BCB)\projects\zipbuilder;$(BCB)\comp;$(BCB)\include;$(BCB)\include\vcl;c:\cpplib \
   -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -v -$Y -$W \
   -$O- -$I- -JPHNV -M 
RFLAGS = -i$(BCB)\projects\zipbuilder;$(BCB)\comp;$(BCB)\include;$(BCB)\include\vcl;c:\cpplib 
LFLAGS = -L$(BCB)\projects\zipbuilder;$(BCB)\comp;$(BCB)\lib\obj;$(BCB)\lib;c:\cpplib \
   -aa -Tpe -x -v -V4.0 
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
