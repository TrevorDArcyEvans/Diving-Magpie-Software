#############################################################################
#									    #
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
#  $Revision:   9.3  $                                                               #
#                                                                           #
#############################################################################

#############################################################################
# Build the object module lists.                                            #
#############################################################################

OBJS =                \
       pcre.obj       \
       pcreposix.obj  \
       maketables.obj \
       study.obj      \
       _pcomp.obj     \
       _pexec.obj     \
       _pmktbl.obj    \
       _pstudy.obj    \
       _pver.obj      \
       _rcomp.obj     \
       _rerror.obj    \
       _rexec.obj     \
       _rfree.obj

REDEF=                                   \
       .pcre_compile=_pcre_compile       \
       .pcre_exec=_pcre_exec             \
       .pcre_version=_pcre_version       \
       .pcre_study=_pcre_study           \
       .pcre_maketables=_pcre_maketables \
       .regerror=_pcre_regerror          \
       .regcomp=_pcre_regcomp            \
       .regexec=_pcre_regexec            \
       .regfree=_pcre_regfree


#############################################################################
# Configure the environment apprpriately.                                   #
#############################################################################
TASMCFG = 1        # Force tasm.cfg creation

!include rules.mak

XTRAFLAGS = $(XTRAFLAGS) $(REDEF:.=-D)


#
# The following rule is only used to update the chartables.c file when a new
# version of the PCRE library is checked into the RTL.
#
update:
  bcc32 -edeftbl.exe -odeftbl.obj deftables.c
  deftbl.exe > chartables.c
  del deftbl.*

