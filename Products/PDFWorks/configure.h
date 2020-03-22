//---------------------------------------------------------------------------
#ifndef configureH
#define configureH
//---------------------------------------------------------------------------

#include "pdflib.h"

//---------------------------------------------------------------------------
const   int NUM_PAPER_SIZE = 13;

struct PAPER_TYPE
    {
    // height of paper in points
    float       nHeight;

    // width of paper in points
    float       nWidth;

    // true if a predefined Windows paper type
    bool        bSystem;

    // index of Windows paper
    // defined in WinGdi.h
    // only used if bSystem is true
    int         nWinPaper;
    };

// note that the ordering here is the same as in DMS_PDFWks.idl
const   PAPER_TYPE  Papers[NUM_PAPER_SIZE] =
    {
    { a0_height     , a0_width      , false , DMPAPER_USER      },
    { a1_height     , a1_width      , false , DMPAPER_USER      },
    { a2_height     , a2_width      , true  , DMPAPER_A2        },
    { a3_height     , a3_width      , true  , DMPAPER_A3        },
    { a4_height     , a4_width      , true  , DMPAPER_A4        },
    { a5_height     , a5_width      , true  , DMPAPER_A5        },
    { a6_height     , a6_width      , false , DMPAPER_USER      },
    { b5_height     , b5_width      , true  , DMPAPER_B5        },
    { letter_height , letter_width  , true  , DMPAPER_LETTER    },
    { legal_height  , legal_width   , true  , DMPAPER_LEGAL     },
    { ledger_height , ledger_width  , true  , DMPAPER_LEDGER    },
    { p11x17_height , p11x17_width  , true  , DMPAPER_TABLOID   },
    { 0             , 0             , false , DMPAPER_USER      },
    };

//---------------------------------------------------------------------------
#endif

