#############################################################################
#
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
#############################################################################

#############################################################################
# Build the object module lists                                             #
#############################################################################
NOEHOBJS =       \
    setnewnx.obj \
    noxx.obj

MISC = noeh32.lib

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
!include rules.mak

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################

noeh32.lib : $(NOEHOBJS)
    makersp "-+%s &\n" &&|
            $?
|   >> $(LIBDIR)\noeh.rsp
    $(TLIB) $(LIBDIR)\$& @$(LIBDIR)\noeh.rsp, $(LIBDIR)\temp.lst
    if exist $(LIBDIR)\$&.bak del $(LIBDIR)\$&.bak
    del $(LIBDIR)\temp.lst
    del $(LIBDIR)\noeh.rsp

