#############################################################################
#                                                                           #
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
# $Revision:   9.15  $                                                       #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
        alloca.obj   \
        chkstk.obj   \
        memchk.obj   \
        stkavail.obj \
        calloc.obj   \
        del.obj      \
        delarray.obj \
        new.obj      \
        newarray.obj \
	setnew.obj   \
        vapp.obj     \
        vappv.obj    \
        vdel.obj     \
        vdelldtc.obj \
        vnewldtc.obj \
        vnwvldtc.obj \
        _alloca.obj  \
        _stkavl.obj  \
        initstk.obj  \
        virtmem.obj  \
        hrdir_b.obj  \
        hrdir_bh.obj \
        hrdir_g.obj  \
        hrdir_mf.obj \
        hrdir_r.obj  \
        hrdir_s.obj  \
        hrdir_us.obj \
        nothrow.obj

!if $d(MAGIC) && !$d(DLL)
OBJS = $(OBJS)	     \
        pheap.obj

!else
OBJS = $(OBJS)	     \
        heap.obj     \
        heapchk.obj  \
        heapchkf.obj \
        heapchkn.obj \
        heapfill.obj \
        heapmin.obj  \
        heapset.obj  \
        heapwalk.obj \
        oheapchk.obj \
        oheapwlk.obj \
	realloc.obj


!endif

!if $d(DLL)
IMPOBJS =            \
        chkstk.obj   \
        vdel.obj     \
        vdelldtc.obj \
        vnewldtc.obj \
        vnwvldtc.obj \
        initstk.obj  \
        nothrow.obj


!endif

MISC =	             \
        setnewnx.obj


!if !$d(MAGIC) && !$d(DLL)
MISC = $(MISC)       \
        $(LIBDIR)\usebormm.lib
!endif

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

#
# These C++ file must be compiled to generate PUBDEFs since the new & delete
# operators will be smashed into their __org_xxx names by PUBDUP.EXE
# The -V?- switch will prevent COMDEFs and cause PUBDEFs to be generated
#
XTRAFLAGS=-V?-

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################
setnewnx.obj : setnew.cpp
    $(CC) -o$(OBJDIR)\$& -DNOXX $?


!if !$d(MAGIC) && !$d(DLL)

#
# Rule for creating usebormm.lib
#
# NOTE: Don't use the $(TLIB) macro since that includes the /0 switch that
#       will remove the pragma comment (lib, "") entries.
#

$(LIBDIR)\usebormm.lib: usebormm.obj
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    tlib /C $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

!endif

