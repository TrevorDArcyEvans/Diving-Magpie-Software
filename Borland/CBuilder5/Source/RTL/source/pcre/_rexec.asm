;----------------------------------------------------------------------
; _rexec.asm -  jump stubs for the for the PCRE functions
;----------------------------------------------------------------------

; $Copyright: 1998$
; $Revision:   9.0  $

include rules.asi
include entry.inc

  Entry@ regexec,_pcre_regexec               , _RTLENTRY, 0

end
