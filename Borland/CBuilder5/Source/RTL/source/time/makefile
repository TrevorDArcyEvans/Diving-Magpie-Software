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
# $Revision:   9.1  $                                                                #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
        ctime.obj    \
        wctime.obj   \
        difftime.obj \
        gmtime.obj   \
        mktime.obj   \
        timecvt.obj  \
        timedata.obj \
        wtimedat.obj \
        timefunc.obj \
	tzdata.obj   \
        tzset.obj    \
        _tzset.obj   \
        wtzset.obj   \
        clock.obj    \
        dosgdate.obj \
        dossdate.obj \
        ftime.obj    \
        getdate.obj  \
        setdate.obj  \
        statcvt.obj  \
        stime.obj    \
        strdate.obj  \
        systime.obj  \
        wstrdate.obj \
        time.obj

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

wctime.obj   : ctime.c
wtimedat.obj : timedata.c
wtzset.obj   : tzset.c
wstrdate.obj : strdate.c

