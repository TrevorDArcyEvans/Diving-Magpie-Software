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
# $Revision:   9.12  $                                                                #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################
MISC =                         \
        $(LIBDIR)\import32.lib \
        $(LIBDIR)\ole2w32.lib

MISC =  $(MISC)                \
        $(LIBDIR)\ws2_32.lib        # WinSock 2.0 (some names conflict with
                                    # WinSock 1.x, therefore this must be
                                    # seperate from import32.lib)

MISC =  $(MISC)                \
        $(LIBDIR)\inet.lib          # Internet APIs (WININET, MSCONF, WEBPOST,
                                    # URLMON, HLINK)

MISC =  $(MISC)                \
        $(LIBDIR)\wininet.lib       # Internet APIs (WININET for MS compat.)

MISC =  $(MISC)                \
        $(LIBDIR)\dxextra.lib       # Used for DirectX.  Contains the pre-
                                    # defined DINPUT.H stuff: c_dfDIMouse &
                                    # c_dfDIKeyboard

MISC =  $(MISC)                \
        $(LIBDIR)\uuid.lib          # Used to hold some of the common GUIDS
                                    # generated by the new INETSDK headers.
                                    # Many of these headers attempt to do
                                    # a #pragma comment (lib, uuid.lib) so
                                    # instead of always removing those
                                    # uuid.lib references, we simply place
                                    # those GUIDS in that lib file.


MISC =  $(MISC)                \
        $(LIBDIR)\dummy.fil         # dummy target to force all the .defs to
                                    # be built

#############################################################################
# Configure the environment appropriately.                                  #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation
TASM_CASE_SENSITIVE = 1
!include rules.mak

#############################################################################
# MISC explicit rules.                                                      #
#############################################################################

CONLIBS =                   \
        advapi32.def        \
        dlcapi.def          \
        kernel32.def        \
        inetmib1.def        \
        lz32.def            \
        mgmtapi.def         \
        mpr.def             \
        netapi32.def        \
        nddeapi.def         \
        rasapi32.def        \
        rpcrt4.def          \
        vdmdbg.def          \
        version.def         \
        win32spl.def        \
        wsock32.def         \
        winspool.def

WIN95LIBS =                 \
        imm32.def           \
        mapi32.def          \
        tapi32.def          \
        pkpd32.def          \
        url.def             \
        snmpapi.def

NT40LIBS =                  \
        wintrust.def        \
        vfw32.def           \
        sporder.def         \
        setupapi.def        \
        rassapi.def         \
        rasdlg.def          \
        pdh.def             \
        lsapi32.def         \
        loadperf.def        \
        imagehlp.def        \
        cap.def

GUILIBS =                   \
        comctl32.def        \
        comdlg32.def        \
        ctl3d32.def         \
        gdi32.def           \
        glu32.def           \
        msacm32.def         \
        opengl32.def        \
        shell32nt4.def      \
        shfolder.def        \
        user32.def          \
        winmm.def

DIRECTXLIBS =               \
        ddraw.def           \
        dplayx.def          \
        dsound.def          \
        dinput.def          \
        dsetup.def          \
        d3drm.def

TH32LIB =                   \
        th32.def

INETLIBS =                  \
        hlink.def           \
        msconf.def          \
        urlmon.def          \
        webpost.def         \
        wininet.def

WININET =                   \
        wininet.def


DIRECTXEXTRALIB =           \
        dxiface.obj                 # Note: This is source code (initialized data)

RPCEXTRALIB =               \
        rpcdce4.def

WS2_32LIB =                 \
        ws2_32.def


MSWSOCKLIB =                \
        mswsock.def


OLEPRO32LIB =               \
        olepro32.def

OLE2LIBS =                  \
        ole32.def           \
        oleaut32.def        \
        oledlg.def          \
        $(OLEPRO32LIB)

OLE1LIBS =                  \
        olecli32.def        \
        olesvr32.def


MSEXTRALIB =                \
        mfcuia32.def        \
        svrapi.def          \
        penwin32.def        \
        winstrm.def         \
        thunk32.def         \
        $(OLE1LIBS)

UUIDLIB =                   \
        uuid.obj                 # stub that contains only _GUID_NULL


# These were new from the NT5 / Win98 Platform SDK
NT50LIBS =                  \
        aclcls.def          \
        activeds.def        \
        adptif.def          \
        bdnapi.def          \
        bhmon.def           \
        bhsupp.def          \
        clusapi.def         \
        crypt32.def         \
        dacdll.def          \
        dapi.def            \
        dflayout.def        \
        dtccfg.def          \
        edbbcli.def         \
        filter.def          \
        fmistr32.def        \
        friendly.def        \
        gtrtst32.def        \
        gwperf.def          \
        hexedit.def         \
        icmui.def           \
        ihvlink.def         \
        measure.def         \
        mprapi.def          \
        mqrt.def            \
        mscms.def           \
        mscomstf.def        \
        msdetstf.def        \
        msi.def             \
        msimg32.def         \
        msinsstf.def        \
        msjava.def          \
        msrating.def        \
        msshlstf.def        \
        msuilstf.def        \
        mtx.def             \
        mtxdm.def           \
        mtxoci.def          \
        nal.def             \
        nmapi.def           \
        ntmsapi.def         \
        ntquery.def         \
        ntwdblib.def        \
        odbc32.def          \
        oleacc.def          \
        opends60.def        \
        parser.def          \
        quartz.def          \
        resutils.def        \
        rtm.def             \
        rtutils.def         \
        rulecls.def         \
        scarddlg.def        \
        shlwapi.def         \
        slbs.def            \
        smsapi.def          \
#
        snacli.def          \
#
        snanls.def          \
        svcsrvl.def         \
        trnsdt.def          \
        wappc32.def         \
        wcpic32.def         \
        wincsv32.def        \
        winscard.def        \
        wldap32.def         \
        wsnmp32.def         \
        xolehlp.def         \
        wow32.def           \
        rpcns4.def          \
        wst.def             \



# These are additional modules from the WIN2K.RC2 Platform SDK
WIN2KLIBS =                 \
        aclui.def           \
        comsvcs.def         \
        dbghelp.def         \
        dhcpcsvc.def        \
        dsprop.def          \
        framedyd.def        \
        framedyn.def        \
        gpedit.def          \
        icm32.def           \
        iphlpapi.def        \
        iprop.def           \
        ksproxy.def         \
        mobsync.def         \
        ntdsapi.def         \
        ntdsbcli.def        \
        psapi.def           \
        qosname.def         \
        riched20.def        \
        secur32.def         \
        sens.def            \
        sensapi.def         \
        sfc.def             \
        shell32.def         \
        sti.def             \
        traffic.def         \
        userenv.def         \
        winfax.def          \
        wtsapi32.def


#
# List of the def files that should only be built and not added into any
# composite library.
#

DUMMY_BUILD_LIST =          \
        msvfw32.def         \
        $(DIRECTXLIBS)      \
        $(MSEXTRALIB)       \
        $(MSWSOCKLIB)       \
        $(RPCEXTRALIB)      \
        $(TH32LIB)          \
        $(NT50LIBS)         \
        $(WIN2KLIBS)


#
# dummy.fil is a dummy rule designed to make sure that the .def->.fst
# file dependents are properly built.  We don't add them to any libs,
# but as part of the .fst process they get added into individually named
# libs and placed into the LIB\PSDK dir (the .def.fst: rule in RULES.MAK
# does this for us.)
#
# Note: Several individual lib files are then also back copied into the
#       main LIB dir.
#
$(LIBDIR)\dummy.fil    : $(DUMMY_BUILD_LIST:.def=.fst)
    copy $(PSDKDIR)\oleaut32.lib            $(LIBDIR)
    copy $(PSDKDIR)\$(MSWSOCKLIB:.def=.lib) $(LIBDIR)
    echo ** Made DUMMY_BUILD_LIST current


$(LIBDIR)\import32.lib : $(NT40LIBS:.def=.fst)  $(CONLIBS:.def=.fst)     \
                         $(GUILIBS:.def=.fst)                            \
                         $(WIN95LIBS:.def=.fst) $(OLE2LIBS:.def=.fst)    \
                         uuid.obj inetguid.obj dxguid.obj mltmstub.obj

    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\ole2w32.lib : $(OLE2LIBS:.def=.fst)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\ws2_32.lib : $(WS2_32LIB:.def=.fst)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\inet.lib : $(INETLIBS:.def=.fst)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\wininet.lib : $(WININET:.def=.fst)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\dxextra.lib : $(DIRECTXEXTRALIB)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak

$(LIBDIR)\uuid.lib : $(UUIDLIB)
    makersp "-+!s &\n" &&|
        $?
|   > $&.rsp
    $(TLIB) $< @$&.rsp, temp.lst
    del *.rsp
    del temp.lst
    if exist $*.bak del $*.bak
