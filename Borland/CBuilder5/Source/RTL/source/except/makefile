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
# $Revision:   9.7  $                                                                #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
        xx.obj       \
        xxa.obj      \
        xx_xpf.obj   \
        xxtype.obj   \
        xxut.obj     \
        xxv.obj      \
        defhandl.obj \
        dtrcount.obj \
        except.obj   \
        lockdbg.obj  \
        setexc.obj   \
        ta.obj       \
        xmsg.obj

IMPOBJS =            \
        xxv.obj      \
	xxa.obj

!if $d(MAGIC)
IMPOBJS_P_ONLY =     \
        xx_xpf.obj

IMPOBJS_W_ONLY =     \
        xx_w.obj

!else
IMPOBJS = $(IMPOBJS) \
        xx_w.obj

!endif

MISC =  noxx.obj


#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation
!include rules.mak

#############################################################################
# Miscellaneous explicit rules.                                             #
#############################################################################

