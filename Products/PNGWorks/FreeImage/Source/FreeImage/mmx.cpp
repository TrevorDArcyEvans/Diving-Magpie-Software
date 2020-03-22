// ==========================================================
// MMX Support functions
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
// - Alexander Dymerets (sashad@te.net.ua)
//
// This handle is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#include "FreeImage.h"
#include "Common.h"

// ----------------------------------------------------------

#define EXCEPTION_EXECUTE_HANDLER       1

static int use_mmx = -1;

// ----------------------------------------------------------

void
FreeImage_EnableMMX() {
	use_mmx = -1;

	CheckMMXTechnology();
}

void
FreeImage_DisableMMX() {
	use_mmx = 1;
}

BOOL
CheckMMXTechnology() {
	// extracted from Intel MMX Application Notes.

	if (use_mmx == -1) {
		BOOL ret_val = TRUE;

		DWORD reg_edx;

		__try {
			_asm {
				// set up CPUID to return processor version and features
				// 0 = vendor string, 1 = version info, 2 = cache info
				// --> the features are returned in edx

				mov eax, 1
				__asm _emit 0fh
				__asm _emit 0a2h
				mov reg_edx, edx
	   		}

		} __except(EXCEPTION_EXECUTE_HANDLER) {
			ret_val = FALSE;
		}

		if (!ret_val) {
			// processor does not support CPUID

			use_mmx = 1;

			return FALSE;
		}

		if (reg_edx & 0x800000)	{
			 // bit 23 is set for MMX technology

		   __try { 
		   		// try executing the MMX instruction "emms"

			   _asm emms
		   } __except(EXCEPTION_EXECUTE_HANDLER) {
			   use_mmx = 1;
			   }
		} else {
			// processor supports CPUID but does not support MMX technology

			use_mmx = 1;

			return FALSE;
		}

		if (ret_val) {
			use_mmx = 0;
		} else {
			use_mmx = 1;
		}

		return ret_val;
	} else {
		return (use_mmx == 0) ? TRUE : FALSE;
	}
}
