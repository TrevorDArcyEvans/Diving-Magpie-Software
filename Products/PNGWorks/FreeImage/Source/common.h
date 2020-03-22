// ==========================================================
// Common functions
//
// Design and implementation by Floris van den Berg
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

#ifndef COMMON_H
#define COMMON_H

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h> 
#endif

#ifndef _INC_MEMORY
#include <memory.h>
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

// FreeImage bitmap header ----------------------------------

typedef struct tagFREEIMAGEHEADER {
	BYTE transparency_count;
	BYTE transparent_table[256];
	BYTE filler[3];
} FREEIMAGEHEADER;

// Conversion macros ----------------------------------------

#define GREY(r,g,b) (BYTE)(((WORD)r*77 + (WORD)g*150 + (WORD)b*29) >> 8)	// .299R + .587G + .114B
// #define GREY(r,g,b) (BYTE)(((WORD)r*169 + (WORD)g*256 + (WORD)b*87) >> 9)	// .33R + 0.5G + .17B
#define RGB555(r, g, b) ((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))
#define RGB565(r, g, b) ((r >> 3) | ((g >> 2) << 5) | ((b >> 3) << 11))

// message function pointer ---------------------------------

extern FreeImage_OutputMessageFunction FreeImage_OutputMessage;

// Default IO functions (not exported)-----------------------

inline unsigned
_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fread(buffer, size, count, (FILE *)handle);
}

inline unsigned
_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fwrite(buffer, size, count, (FILE *)handle);
}

inline int
_SeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE *)handle, offset, origin);
}

inline long
_TellProc(fi_handle handle) {
	return ftell((FILE *)handle);
}

inline void
SetDefaultIO(FreeImageIO *io) {
	io->read_proc  = _ReadProc;
	io->seek_proc  = _SeekProc;
	io->tell_proc  = _TellProc;
	io->write_proc = _WriteProc;
}

// check for the availability of MMX ------------------------

BOOL CheckMMXTechnology();

// internal calculations ------------------------------------

inline double
pi() {
	return 3.14159265358979323846264338327950;
}

inline int
round(double x) {
	return (int)floor(x + 0.5);
}

inline unsigned char
HINIBBLE (unsigned char byte) {
	return byte & 240;
}

inline unsigned char
LOWNIBBLE (unsigned char byte) {
	return byte & 15;
}

inline int
CalculateLine(int width, int bitdepth) {
	return ((width * bitdepth) + 7) / 8;
}

inline int
CalculatePitch(int line) {
	return line + 3 & ~3;
}

inline int
CalculateUsedColors(int bitcount) {
	int c = 1 << bitcount;

	return ((c <= 256) && (c > 1)) ? c : 0;
}

#endif // !COMMON_H