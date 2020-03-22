//---------------------------------------------------------------------------
#ifndef SWutilsH
#define SWutilsH
#define        swDocNONE                    0
#define        swDocPART                    1
#define        swDocASSEMBLY                2
#define        swDocDrawing                 3

#define        swGenericError               0x1
#define        swFileNotFoundError          0x2
#define        swIdMatchError               0x4
#define        swReadOnlyWarn               0x8
#define        swSharingViolationWarn       0x10
#define        swDrawingANSIUpdateWarn      0x20
#define        swSheetScaleUpdateWarn       0x40
#define        swNeedsRegenWarn             0x80
#define        swBasePartNotLoadedWarn      0x100


#define        swDwgPaperAsize              0
#define        swDwgPaperAsizeVertical      1
#define        swDwgPaperBsize              2
#define        swDwgPaperCsize              3
#define        swDwgPaperDsize              4
#define        swDwgPaperEsize              5
#define        swDwgPaperA4size             6
#define        swDwgPaperA4sizeVertical     7
#define        swDwgPaperA3size             8
#define        swDwgPaperA2size             9
#define        swDwgPaperA1size             10
#define        swDwgPaperA0size             11
#define        swDwgPapersUserDefined       12


#define        swPrintPaperSize	            0
#define        swPrintOrientation	        1
//---------------------------------------------------------------------------
#define        swDocNONE                    0
#define        swDocPART                    1
#define        swDocASSEMBLY                2
#define        swDocDrawing                 3

#define        swGenericError               0x1
#define        swFileNotFoundError          0x2
#define        swIdMatchError               0x4
#define        swReadOnlyWarn               0x8
#define        swSharingViolationWarn       0x10
#define        swDrawingANSIUpdateWarn      0x20
#define        swSheetScaleUpdateWarn       0x40
#define        swNeedsRegenWarn             0x80
#define        swBasePartNotLoadedWarn      0x100


#define        swDwgPaperAsize              0
#define        swDwgPaperAsizeVertical      1
#define        swDwgPaperBsize              2
#define        swDwgPaperCsize              3
#define        swDwgPaperDsize              4
#define        swDwgPaperEsize              5
#define        swDwgPaperA4size             6
#define        swDwgPaperA4sizeVertical     7
#define        swDwgPaperA3size             8
#define        swDwgPaperA2size             9
#define        swDwgPaperA1size             10
#define        swDwgPaperA0size             11
#define        swDwgPapersUserDefined       12


#define        swPrintPaperSize	            0
#define        swPrintOrientation	        1
//---------------------------------------------------------------------------
bool    IsSolidWorksFile(String  strFileName);
long    GetType(String  strFileName);
//---------------------------------------------------------------------------

#endif
