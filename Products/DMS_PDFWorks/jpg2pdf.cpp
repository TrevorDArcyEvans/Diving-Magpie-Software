#include <vcl.h>
#pragma hdrstop

#include "jpg2pdf.h"

/* ------------------------------------------------------------- */

HRESULT
jpeg_image(
    char                *jpgname,
    char                *pdfname,
    PDF_Setup           PDFSetup)
/*
generates a PDF disk file from a jpg disk file according to the passed in
configuration information

parameters:
    jpgname
        fully qualified path to jpg disk file
        I think it should include the .jpg extension
        should have at least read access to the file

    pdfname
        fully qualified path to pdf disk file
        must have at write access to create the file

    m_PDF_Setup
        structure containing PDF configuration information on how to generate
        the pdf file

returns:
    S_OK    if successful
    1       if could not open pdf file for writing
    2       if could not analyse jpg image
*/
{
    PDF             *p;
    int             image;
    float           Scale,
                    ScaleHeight,
                    ScaleWidth,
                    Xorigin,
                    Yorigin;

    int             rc = 1;     // return code for function

    // check for landscape mode
    if (PDFSetup.PageSetup.Landscape)
        {
        // OK to swap values over since PDFSetup passed by value
        long        tmp     = PDFSetup.PageSetup.PaperHeight;
        PDFSetup.PageSetup.PaperHeight  = PDFSetup.PageSetup.PaperWidth;
        PDFSetup.PageSetup.PaperWidth   = tmp;
        }

    PDF_boot();

    p = PDF_new();

    if (-1 == PDF_open_file(p, pdfname))
        {
        // TDE  error message from sample code - please leave in
        // printf("Couldn't open PDF file '%s'!\n", pdfname);
        rc = 1;
        goto CLEAN_UP;
        }

    PDF_set_info(p, "Keywords", ::String(PDFSetup.Info.InfoKeyWords   ).c_str());
    PDF_set_info(p, "Subject" , ::String(PDFSetup.Info.InfoSubject    ).c_str());
    PDF_set_info(p, "Title"   , ::String(PDFSetup.Info.InfoTitle      ).c_str());
    PDF_set_info(p, "Creator" , ::String(PDFSetup.Info.InfoCreator    ).c_str());
    PDF_set_info(p, "Author"  , ::String(PDFSetup.Info.InfoAuthor     ).c_str());


    if (-1 == (image = PDF_open_image_file(p, "jpeg", jpgname, "", 0)))
        {
        // TDE  error message from sample code - please leave in
        // fprintf(stderr, "Error: Couldn't analyze JPEG image %s.\n", jpgname);
        rc = 2;
        goto CLEAN_UP;
        }

    PDF_begin_page(p, PDFSetup.PageSetup.PaperWidth, PDFSetup.PageSetup.PaperHeight);

    // scaling factor to fit image between left & right margins
    ScaleWidth  = (float) (PDFSetup.PageSetup.PaperWidth
                            - PDFSetup.PageSetup.MarginLeft
                            - PDFSetup.PageSetup.MarginRight)
                        / PDF_get_image_width(p, image);

    // scaling factor to fit image between top & bottom margins
    ScaleHeight = (float) (PDFSetup.PageSetup.PaperHeight
                            - PDFSetup.PageSetup.MarginTop
                            - PDFSetup.PageSetup.MarginBottom)
                        / PDF_get_image_height(p, image);

    // scaling factor used will be lesser of these
    Scale = (ScaleWidth > ScaleHeight) ? ScaleHeight : ScaleWidth;

    // after all that hard work, see if the user wanted to scale to fit
    // note that ScaleWidth & ScaleHeight are required if the image is to
    // be centered
    if (!PDFSetup.PageSetup.ScaleToFit)
        {
        // use specified scale
        Scale       = PDFSetup.PageSetup.Scale;
        ScaleWidth  = PDFSetup.PageSetup.Scale;
        ScaleHeight = PDFSetup.PageSetup.Scale;
        }
    else
        {
        if (PDFSetup.PageSetup.KeepAspectRatio)
            {
            // use lesser scaling factor for both
            ScaleWidth  = Scale;
            ScaleHeight = Scale;
            }
        else
            {
            // do not change calculated scaling factors
            ScaleWidth  = ScaleWidth ;
            ScaleHeight = ScaleHeight;

            // rather, adjust coord scaling to stretch image to fit page
            if (PDFSetup.PageSetup.Landscape)
                {
                PDF_scale(p, ScaleWidth  / Scale, ScaleHeight / Scale);
                }
            else
                {
                PDF_scale(p, ScaleHeight / Scale, ScaleWidth  / Scale);
                }
            }
        }

    // calculate the coordinates of the bottom LH corner of the image
    if (PDFSetup.PageSetup.CentreOnPage)
        {
        Xorigin = (float) (PDFSetup.PageSetup.PaperWidth
                            + PDFSetup.PageSetup.MarginLeft
                            - PDFSetup.PageSetup.MarginRight
                            - PDF_get_image_width (p, image) * ScaleWidth) / 2.0;

        Yorigin = (float) (PDFSetup.PageSetup.PaperHeight
                            + PDFSetup.PageSetup.MarginBottom
                            - PDFSetup.PageSetup.MarginTop
                            - PDF_get_image_height(p, image) * ScaleHeight) / 2.0;
        }
    else
        {
        Xorigin = (float) PDFSetup.PageSetup.MarginLeft;

        Yorigin = (float) PDFSetup.PageSetup.PaperHeight
                            - PDFSetup.PageSetup.MarginTop
                            - PDF_get_image_height(p, image) * ScaleHeight;
        }


    PDF_place_image(p, image, Xorigin, Yorigin, Scale);


    PDF_end_page(p);

    // successfully completed pdf generation, so set return code
    rc = S_OK;

    CLEAN_UP :
        ;

    PDF_close(p);
    PDF_delete(p);

    PDF_shutdown();

    return rc;
}
/* ------------------------------------------------------------- */

#if 0
    /* ----------------- second image ------------------- */
    /* half size and rotate through 90 deg */
    scale = (float) 0.5;
    PDF_save(p);
    PDF_rotate(p, (float) 90.0);
    PDF_place_image(p, image, (float) 0.0, (float) (-1 * a4_width), scale);
    PDF_restore(p);

    /* ----------------- third image ------------------- */
    /* quarter size and rotate through 45 deg */
    scale = (float) 0.25;
    PDF_save(p);
    PDF_rotate(p, (float) 45.0);
    PDF_place_image(p, image, (float) 200.0, (float) 0.0, scale);
    PDF_restore(p);

#endif

/* ------------------------------------------------------------- */

