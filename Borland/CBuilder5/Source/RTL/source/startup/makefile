#############################################################################
# The make process relies on the creation of DLL and library response file  #
# creation.  To control the location of object modules the following should #
# be defined:                                                               #
#                                                                           #
#     IMPOBJS - A list of object modules that should appear in the DLL      #
#               import library.                                             #
#                                                                           #
#        OBJS - If a DLL is build, this is a list of the object modules     #
#               that are linked into the DLL.  If building a library, this  #
#               is the list of object modules that goes into the library.   #
#                                                                           #
# The building of miscellaneous object modules and libraries is controlled  #
# by the list of files in the MISC variable.                                #
#                                                                           #
# $Revision:   9.11  $	                                                    #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =                   \
            dllmain.obj  \
            libmain.obj  \
            rawdll.obj   \
            globals.obj  \
            initexit.obj \
            startup.obj  \
            wstartup.obj \
            startupd.obj \
            wstrtupd.obj \
            dllx.obj

!if $d(DLL)
    IMPOBJS =            \
        dllmain.obj \
        libmain.obj	\
        rawdll.obj

    MISC =                         \
            $(LIBDIR)\c0d32x.obj

!endif

    MISC =  $(MISC)                \
            $(LIBDIR)\c0d32.obj    \
            $(LIBDIR)\c0w32.obj    \
            $(LIBDIR)\c0x32.obj    \
            $(LIBDIR)\c0d32w.obj   \
            $(LIBDIR)\c0w32w.obj   \
            $(LIBDIR)\c0x32w.obj   \
            $(LIBDIR)\c0s32.obj


!if $d(MAGIC)
    MISC =  $(MISC)                \
            $(LIBDIR)\c0pkg32.obj
!endif


!if $d(DLL)
# if building the RTLDLL, add in dllstub.obj & rtldll.obj for the RTLDLL to
# find and use for itself.

    OBJS  =                      \
            dllstub.obj          \
            rtldll.obj           \
            $(OBJS)

# then add dlllock.obj to the import library so that the target DLL links with
# this one instead.

    IMPOBJS = $(IMPOBJS)           \
            dlllock.obj

!else
    OBJS    = $(OBJS)              \
            dllstub.obj

!endif

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation
TASM_CASE_SENSITIVE = 1

!include rules.mak

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################
#
# Here we compile the startup code to the LIBDIR directly so that the
# dependancies are invoked and all the files are built only the first time.
#
$(LIBDIR)\c0x32.obj : c0nt.asm     c0nt.asm
  $(ASM) $(ASMFLAGS) c0nt.asm,$<;

$(LIBDIR)\c0x32w.obj : wc0nt.asm   c0nt.asm
  $(ASM) $(ASMFLAGS) wc0nt.asm,$<;

$(LIBDIR)\c0w32.obj : c0ntw.asm    c0nt.asm
  $(ASM) $(ASMFLAGS) c0ntw.asm,$<;

$(LIBDIR)\c0w32w.obj : wc0ntw.asm  c0nt.asm
  $(ASM) $(ASMFLAGS) wc0ntw.asm,$<;

$(LIBDIR)\c0d32.obj : c0ntd.asm    c0nt.asm
  $(ASM) $(ASMFLAGS) c0ntd.asm,$<;

$(LIBDIR)\c0d32w.obj : wc0ntd.asm  c0nt.asm
  $(ASM) $(ASMFLAGS) wc0ntd.asm,$<;

$(LIBDIR)\c0d32x.obj: c0ntdx.asm   c0nt.asm
  $(ASM) $(ASMFLAGS) c0ntdx.asm,$<;

$(LIBDIR)\c0pkg32.obj: c0ntpkg.asm c0nt.asm
  $(ASM) $(ASMFLAGS) c0ntpkg.asm,$<;

$(LIBDIR)\c0s32.obj : c0ntds.asm   c0nt.asm
  $(ASM) $(ASMFLAGS) c0ntds.asm,$<;


wstartup.obj : startup.c

wstrtupd.obj : startupd.c
