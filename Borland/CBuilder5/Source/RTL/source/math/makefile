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
# $Revision:   9.8  $                                                      #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
OBJS =               \
        8087.obj     \
        _chgsgn.obj  \
        _cpysgn.obj  \
        _efcvt.obj   \
        _finite.obj  \
        _finitel.obj \
        _fpcls.obj   \
        _ftoul.obj   \
        _gcvt.obj    \
        _isnan.obj   \
        _isnanl.obj  \
        _logb.obj    \
        _ltoa1.obj   \
        _matherl.obj \
        _matherr.obj \
        _naftr.obj   \
        _naftrl.obj  \
        _pow10.obj   \
        _scalb.obj   \
        _scalbl.obj  \
        abs.obj      \
        acosasin.obj \
        acossinl.obj \
        atan.obj     \
        atan2.obj    \
        atan2l.obj   \
        atanl.obj    \
        atof.obj     \
        atoi64.obj   \
        atol.obj     \
        atold.obj    \
        bcd1.obj     \
        bcd2.obj     \
        ceil.obj     \
        ceill.obj    \
        clear87.obj  \
        cos.obj      \
        cosh.obj     \
        coshl.obj    \
        cosl.obj     \
#       cplx1.obj    \  # old Borland C++ complex class
#       cplx2.obj    \  # old Borland C++ complex class
        crotl.obj    \
        crotr.obj    \
        ctrl87.obj   \
        cvtentry.obj \
        cvtentyw.obj \
        cvtfak.obj   \
        cvtfakw.obj  \
        deflt87.obj  \
        div.obj      \
        efcvt.obj    \
        exp.obj      \
        expl.obj     \
        expld.obj    \
        f87atan.obj  \
        f87exp.obj   \
        f87log.obj   \
        f87sine.obj  \
        fabs.obj     \
        fabsl.obj    \
        fbstp.obj    \
        fildq.obj    \
        fistq.obj    \
        floor.obj    \
        floorl.obj   \
        fmod.obj     \
        fmodl.obj    \
        fpreset.obj  \
        frexp.obj    \
        frexpl.obj   \
        ftol.obj     \
        fuildq.obj   \
        fuistq.obj   \
        fxam.obj     \
        gcvt.obj     \
        hugeval.obj  \
        hypot.obj    \
        hypotl.obj   \
        i64toa.obj   \
        i64tow.obj   \
        initcvt.obj  \
        int64toa.obj \
        int64tow.obj \
        labs.obj     \
        ldexp.obj    \
        ldexpl.obj   \
        ldtrunc.obj  \
        log.obj      \
        log10.obj    \
        log10l.obj   \
        logl.obj     \
        longtoa.obj  \
        longtow.obj  \
        lrotl.obj    \
        lrotr.obj    \
        ltoa1.obj    \
        ltow1.obj    \
        matherr.obj  \
        matherrl.obj \
        mathptr.obj  \
        mathptr2.obj \
        mathwhy.obj  \
        modf.obj     \
        modfl.obj    \
        poly.obj     \
        polyl.obj    \
        pow.obj      \
        pow10d.obj   \
        pow10l.obj   \
        powl.obj     \
        qdiv10.obj   \
        qmul10.obj   \
        rand.obj     \
        realcvt.obj  \
        realcvtw.obj \
        rotl.obj     \
        rotr.obj     \
        round.obj    \
        scantod.obj  \
        scanwtod.obj \
        sin.obj      \
        sinh.obj     \
        sinhl.obj    \
        sinl.obj     \
        sqrt.obj     \
        sqrtl.obj    \
        stat87.obj   \
        strtod.obj   \
        strtol.obj   \
        strtoul.obj  \
        tan.obj      \
        tanh.obj     \
        tanhl.obj    \
        tanl.obj     \
        wcstod.obj   \
        wcstol.obj   \
        wcstoul.obj  \
        wtof.obj     \
        wtoi64.obj   \
        wtol.obj     \
        wtold.obj    \
        xcvt.obj     \
        xcvtw.obj




AUXOBJS =            \
        _ll.obj      \
        fdiv32.obj   \
        fastmath.obj

!if $d(DLL)
IMPOBJS =            \
        xinitcvt.obj
!endif

!if $d(DLL)
    IMPOBJS = $(AUXOBJS) $(IMPOBJS)
    OBJS    = $(AUXOBJS) $(OBJS)
!else
    OBJS    = $(AUXOBJS) $(OBJS)
!endif

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

cvtentyw.obj: cvtentry.asm
cvtfakw.obj : cvtfak.c
i64tow.obj  : i64toa.c
int64tow.obj: int64toa.c
longtow.obj : longtoa.c
ltow1.obj   : ltoa1.c
realcvtw.obj: realcvt.c
scanwtod.obj: scantod.c
wcstod.obj  : strtod.c
wcstol.obj  : strtol.c
wcstoul.obj : strtoul.c
wtof.obj    : atof.c
wtoi64.obj  : atoi64.c
wtol.obj    : atol.c
wtold.obj   : atold.c
xcvtw.obj   : xcvt.c
