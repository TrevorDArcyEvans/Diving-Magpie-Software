;----------------------------------------------------------------------
; fnsplit.asm - user-callable entry point to _fnsplit() function.
;----------------------------------------------------------------------

;
;       C/C++ Run Time Library - Version 10.0
; 
;       Copyright (c) 1991, 2000 by Inprise Corporation
;       All Rights Reserved.
; 

; $Revision:   9.0  $

        include rules.asi
	include entry.inc
        Entry@ fnsplit, _fnsplit, _RTLENTRYF, 20
        end
