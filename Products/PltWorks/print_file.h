//---------------------------------------------------------------------------
#ifndef print_fileH
#define print_fileH
//---------------------------------------------------------------------------

// time in milliseconds to wait for SW to finish printing
#define        SW_PAUSE                     (10*1000)



// Visual Basic Reference
// Printer Object Constants


// Printer Color Mode
//              Constant                    Value   Description
#define         vbPRCMMonochrome            1       Monochrome output
#define         vbPRCMColor                 2       Color output


// Duplex Printing
//              Constant                    Value   Description
#define         vbPRDPSimplex               1       /* Single-sided printing                */
#define         vbPRDPHorizontal            2       /* Double-sided horizontal printing     */
#define         vbPRDPVertical              3       /* Double-sided vertical printing       */


// Printer Orientation
//              Constant                    Value   Description
#define         vbPRORPortrait              1       /* Documents print with the top at the narrow side of the paper     */
#define         vbPRORLandscape             2       /* Documents print with the top at the wide side of the paper       */


// Print Quality
//              Constant                    Value   Description
#define         vbPRPQDraft                 -1      /* Draft print quality      */
#define         vbPRPQLow                   -2      /* Low print quality        */
#define         vbPRPQMedium                -3      /* Medium print quality     */
#define         vbPRPQHigh                  -4      /* High print quality       */


// PaperBin Property
//              Constant                    Value   Description
#define         vbPRBNUpper                 1       /* Use paper from the upper bin                                             */
#define         vbPRBNLower                 2       /* Use paper from the lower bin                                             */
#define         vbPRBNMiddle                3       /* Use paper from the middle bin                                            */
#define         vbPRBNManual                4       /* Wait for manual insertion of each sheet of paper                         */
#define         vbPRBNEnvelope              5       /* Use envelopes from the envelope feeder                                   */
#define         vbPRBNEnvManual             6       /* Use envelopes from the envelope feeder, but wait for manual insertion    */
#define         vbPRBNAuto                  7       /* (Default) Use paper from the current default bin                         */
#define         vbPRBNTractor               8       /* Use paper fed from the tractor feeder                                    */
#define         vbPRBNSmallFmt              9       /* Use paper from the small paper feeder                                    */
#define         vbPRBNLargeFmt              10      /* Use paper from the large paper bin                                       */
#define         vbPRBNLargeCapacity         11      /* Use paper from the large capacity feeder                                 */
#define         vbPRBNCassette              14      /* Use paper from the attached cassette cartridge                           */


// PaperSize Property
//              Constant                    Value   Description
#define         vbPRPSLetter                1       /* Letter, 8 1/2 x 11 in                    */
#define         vbPRPSLetterSmall           2       /* +A611Letter Small, 8 1/2 x 11 in         */
#define         vbPRPSTabloid               3       /* Tabloid, 11 x 17 in                      */
#define         vbPRPSLedger                4       /* Ledger, 17 x 11 in                       */
#define         vbPRPSLegal                 5       /* Legal, 8 1/2 x 14 in                     */
#define         vbPRPSStatement             6       /* Statement, 5 1/2 x 8 1/2 in              */
#define         vbPRPSExecutive             7       /* Executive, 7 1/2 x 10 1/2 in             */
#define         vbPRPSA3                    8       /* A3, 297 x 420 mm                         */
#define         vbPRPSA4                    9       /* A4, 210 x 297 mm                         */
#define         vbPRPSA4Small               10      /* A4 Small, 210 x 297 mm                   */
#define         vbPRPSA5                    11      /* A5, 148 x 210 mm                         */
#define         vbPRPSB4                    12      /* B4, 250 x 354 mm                         */
#define         vbPRPSB5                    13      /* B5, 182 x 257 mm                         */
#define         vbPRPSFolio                 14      /* Folio, 8 1/2 x 13 in                     */
#define         vbPRPSQuarto                15      /* Quarto, 215 x 275 mm                     */
#define         vbPRPS1&H14                 16      /* 10 x 14 in                               */
#define         vbPRPS11x17                 17      /* 11 x 17 in                               */
#define         vbPRPSNote                  18      /* Note, 8 1/2 x 11 in                      */
#define         vbPRPSEnv9                  19      /* Envelope #9, 3 7/8 x 8 7/8 in            */
#define         vbPRPSEnv10                 20      /* Envelope #10, 4 1/8 x 9 1/2 in           */
#define         vbPRPSEnv11                 21      /* Envelope #11, 4 1/2 x 10 3/8 in          */
#define         vbPRPSEnv12                 22      /* Envelope #12, 4 1/2 x 11 in              */
#define         vbPRPSEnv14                 23      /* Envelope #14, 5 x 11 1/2 in              */
#define         vbPRPSCSheet                24      /* C size sheet                             */
#define         vbPRPSDSheet                25      /* D size sheet                             */
#define         vbPRPSESheet                26      /* E size sheet                             */
#define         vbPRPSEnvDL                 27      /* Envelope DL, 110 x 220 mm                */
#define         vbPRPSEnvC3                 29      /* Envelope C3, 324 x 458 mm                */
#define         vbPRPSEnvC4                 30      /* Envelope C4, 229 x 324 mm                */
#define         vbPRPSEnvC5                 28      /* Envelope C5, 162 x 229 mm                */
#define         vbPRPSEnvC6                 31      /* Envelope C6, 114 x 162 mm                */
#define         vbPRPSEnvC65                32      /* Envelope C65, 114 x 229 mm               */
#define         vbPRPSEnvB4                 33      /* Envelope B4, 250 x 353 mm                */
#define         vbPRPSEnvB5                 34      /* Envelope B5, 176 x 250 mm                */
#define         vbPRPSEnvB6                 35      /* Envelope B6, 176 x 125 mm                */
#define         vbPRPSEnvItaly              36      /* Envelope, 110 x 230 mm                   */
#define         vbPRPSEnvMonarch            37      /* Envelope Monarch, 3 7/8 x 7 1/2 in       */
#define         vbPRPSEnvPersonal           38      /* Envelope, 3 5/8 x 6 1/2 in               */
#define         vbPRPSFanfoldUS             39      /* U.S. Standard Fanfold, 14 7/8 x 11 in    */
#define         vbPRPSFanfoldStdGerman      40      /* German Standard Fanfold, 8 1/2 x 12 in   */
#define         vbPRPSFanfoldLglGerman      41      /* German Legal Fanfold, 8 1/2 x 13 in      */
#define         vbPRPSUser                  256     /* User-defined                             */


//---------------------------------------------------------------------------
#endif
