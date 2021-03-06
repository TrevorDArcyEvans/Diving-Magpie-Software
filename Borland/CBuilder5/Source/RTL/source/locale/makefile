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
# $Revision:   9.1  $                                                       #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
	bigctype.obj \
	cconv.obj    \
	convt.obj    \
        clower.obj   \
        ctype.obj    \
        cupper.obj   \
        getinfo.obj  \
        getinfo1.obj \
        getinfo2.obj \
        getinfo3.obj \
        is.obj       \
        wis.obj      \
        isctype.obj  \
        iswctype.obj \
        locale.obj   \
        clocale.obj  \
        initcat.obj  \
	lconv.obj    \
	lstrcoll.obj \
	lwcscoll.obj \
        lstricol.obj \
        lwcsicol.obj \
        lstrncol.obj \
        lwcsncol.obj \
        lstrnico.obj \
        lwcsnico.obj \
        lstrlwr.obj  \
        lwcslwr.obj  \
        lstrupr.obj  \
        lwcsupr.obj  \
        lstrxfrm.obj \
        lwcsxfrm.obj \
        ltolower.obj \
        ltowlwr.obj  \
        ltoupper.obj \
        ltowupr.obj  \
        mbyte1.obj   \
        setlocal.obj \
        wsetlocl.obj \
        lsetlocl.obj \
	lwsetlcl.obj \
	strcoll.obj  \
        wcscoll.obj  \
        stricoll.obj \
        wcsicoll.obj \
        strncoll.obj \
        wcsncoll.obj \
        strnicol.obj \
        wcsnicol.obj \
        strftime.obj \
        wcsftime.obj \
        strlwr.obj   \
        wcslwr.obj   \
        strupr.obj   \
        wcsupr.obj   \
        strxfrm.obj  \
        wcsxfrm.obj  \
        tolower.obj  \
        towlower.obj \
        toupper.obj  \
        towupper.obj

#!if $d(MT)
#    OBJS = $(OBJS)     \
#           locales.obj
#!endif

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

CC = $(CC) -U_MBCS

toupper.obj : towupper.c
tolower.obj : towlower.c
strupr.obj  : wcsupr.c
strlwr.obj  : wcslwr.c
wis.obj     : is.c
wsetlocl.obj: setlocal.c
wcscoll.obj : strcoll.c
wcsicoll.obj: stricoll.c
wcsncoll.obj: strncoll.c
wcsnicol.obj: strnicol.c
lwcscoll.obj: lstrcoll.c
wcsxfrm.obj : strxfrm.c

