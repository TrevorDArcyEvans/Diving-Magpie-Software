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
# $Revision:   9.8  $                                                                #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =           \
    assert.obj   \
    assertf.obj  \
    bsearch.obj  \
    borutil.obj  \
    castmptr.obj \
    checks.obj   \
    ddvt.obj     \
    delayhlp.obj \
    ermsghlp.obj \
    errno.obj    \
    errormsg.obj \
    getstrm.obj  \
    lsearch.obj  \
    match.obj    \
    platform.obj \
    pureerr.obj  \
    qsort.obj    \
    regexp.obj   \
    swab.obj     \
    version.obj  \
    seterrmd.obj \
    um.obj


!if $d(DLL)
    RES  = version.res

    IMPOBJS =            \
            ddvt.obj     \
            pureerr.obj
!else
    MISC = $(LIBDIR)\gp.obj
!endif


MISC = $(MISC) $(LIBDIR)\obsolete.lib

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################
$(LIBDIR)\obsolete.lib : obsolete.obj
    $(TLIB) $(LIBDIR)\$&+$**
    if exist $(LIBDIR)\$&.bak del $(LIBDIR)\$&.bak

$(LIBDIR)\gp.obj : gp.obj
    copy $** $(LIBDIR)\$.
