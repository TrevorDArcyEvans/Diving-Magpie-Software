;----------------------------------------------------------------------
; stpcpy.asm - user-callable entry point to _stpcpy() function.
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
        Entry@ stpcpy, _stpcpy, _RTLENTRYF, 8
        end
