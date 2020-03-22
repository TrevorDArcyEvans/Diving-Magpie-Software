#ifndef jpg2pdfH
#define jpg2pdfH

/* ------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "pdflib.h"
#include "DMS_PDFWorksImpl.H"

/* ------------------------------------------------------------- */

HRESULT
jpeg_image(
    char                *jpgname,
    char                *pdfname,
    PDF_Setup           PDFSetup);

/* ------------------------------------------------------------- */

#endif

