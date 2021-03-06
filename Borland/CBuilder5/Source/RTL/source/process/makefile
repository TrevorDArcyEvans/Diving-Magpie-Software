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
# $Revision:   9.4  $                                                                #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
    cwait.obj    \
    getpid.obj   \
    abort.obj    \
    patexit.obj  \
    atexit.obj   \
    execl.obj    \
    wexecl.obj   \
    execle.obj   \
    wexecle.obj  \
    execlp.obj   \
    wexeclp.obj  \
    execlpe.obj  \
    wexeclpe.obj \
    execv.obj    \
    wexecv.obj   \
    execve.obj   \
    wexecve.obj  \
    execvp.obj   \
    wexecvp.obj  \
    execvpe.obj  \
    wexecvpe.obj \
    exit.obj     \
    getenv.obj   \
    wgetenv.obj  \
    lonedll.obj  \
    initwild.obj \
    exparg.obj   \
    wexparg.obj  \
    putenv.obj   \
    wputenv.obj  \
    initargv.obj \
    saptr.obj    \
    wsaptr.obj   \
    setargv.obj  \
    hsargv.obj   \
    whsargv.obj  \
    wsetargv.obj \
    spawnl.obj   \
    wspawnl.obj  \
    spawnle.obj  \
    wspawnle.obj \
    spawnlp.obj  \
    wspawnlp.obj \
    spawnlpe.obj \
    wspwnlpe.obj \
    spawnv.obj   \
    wspawnv.obj  \
    spawnve.obj  \
    wspawnve.obj \
    spawnvp.obj  \
    wspawnvp.obj \
    spawnvpe.obj \
    wspwnvpe.obj \
    srchenv.obj  \
    wsrchenv.obj \
    srchpath.obj \
    wsrchpth.obj \
    srchstr.obj  \
    wsrchstr.obj \
    wait.obj     \
    wild.obj     \
    wwild.obj    \
    wildptr.obj  \
    wwildptr.obj \
    setargv0.obj \
    wsetarg0.obj \
    setjmp.obj   \
    loadprog.obj \
    wloadprg.obj \
    setenv.obj   \
    wsetenv.obj  \
    setenvp.obj  \
    wsetenvp.obj \
    signal.obj   \
    sleep.obj    \
    system.obj   \
    wsystem.obj  \
    _cwait.obj   \
    _getpid.obj


!if $d(DLL)
    IMPOBJS =    \
    setargv2.obj \
    wildptr.obj  \
    wwildptr.obj \
    wsetarg2.obj \
    xsetenvp.obj \
    wxsetenp.obj

!else
    MISC =               \
    $(LIBDIR)\wildargs.obj

!endif

MISC=$(MISC) setjmpnx.obj

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################
setjmpnx.obj : setjmp.asm
    $(ASM) -DNOXX $?, $(OBJDIR)\$&

$(LIBDIR)\wildargs.obj : wildargs.obj
    copy $** $(LIBDIR)\$.

wsetenv.obj  : setenv.c
wsetenvp.obj : setenvp.c
wloadprg.obj : loadprog.c
wsystem.obj  : system.c

wgetenv.obj  : getenv.c
wputenv.obj  : putenv.c
wsrchenv.obj : srchenv.c
wsrchpth.obj : srchpath.c
wsrchstr.obj : srchstr.c
wspawnl.obj  : spawnl.c
wspawnle.obj : spawnle.c
wspawnlp.obj : spawnlp.c
wspwnlpe.obj : spawnlpe.c
wspawnv.obj  : spawnv.c
wspawnve.obj : spawnve.c
wspawnvp.obj : spawnvp.c
wspwnvpe.obj : spawnvpe.c
wexecl.obj   : execl.c
wexecle.obj  : execle.c
wexeclp.obj  : execlp.c
wexeclpe.obj : execlpe.c
wexecv.obj   : execv.c
wexecve.obj  : execve.c
wexecvp.obj  : execvp.c
wexecvpe.obj : execvpe.c
wsaptr.obj   : saptr.c
whsargv.obj  : hsargv.c
wsetargv.obj : setargv.c
wsetarg0.obj : setargv0.c
wsetarg2.obj : setargv2.c
wwild.obj    : wild.c
wwildptr.obj : wildptr.c
wexparg.obj  : exparg.c
