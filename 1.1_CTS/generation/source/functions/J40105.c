/*------------------------------------------------------------------------------
Copyright (c) 2008 The Khronos Group Inc.

All Rights Reserved.  This code is protected by copyright laws and contains
material proprietary to the Khronos Group, Inc.  This is UNPUBLISHED
PROPRIETARY SOURCE CODE that may not be disclosed in whole or in part to third
parties, and may not be reproduced, republished, distributed, transmitted,
displayed, broadcast or otherwise exploited in any manner without the express
prior written permission of Khronos Group.

The receipt or possession of this code does not convey any rights to reproduce,
disclose, or distribute its contents, or to manufacture, use, or sell anything
that it may describe, in whole or in part other than under the terms of the
Khronos Adopters Agreement or Khronos Conformance Test Source License Agreement
as executed between Khronos and the recipient.

For the avoidance of doubt, this code when provided: a) under the Khronos
Conformance Test Source License Agreement is for the sole purpose of creating
conformance tests for delivery to Khronos and does not provide for formally
testing products or use of Khronos trademarks on conformant products; b) under
the Khronos Adopters Agreement is for the sole purpose of formally
administering tests to products pursuant to the Khronos Conformance Process
Document.

Khronos, OpenKODE, OpenVG, OpenWF, glFX, OpenMAX and OpenSL ES are trademarks
of the Khronos Group Inc.  COLLADA is a trademark of Sony Computer
Entertainment Inc. used by permission by Khronos.  OpenGL and OpenML are
registered trademarks and the OpenGL ES logo is a trademark of Silicon Graphics
Inc. used by permission by Khronos. 

Use, duplication or disclosure by the Government is subject to restrictions as
set forth in subdivision (c)(1)(ii) of the Rights in Technical Data and
Computer Software clause at DFARS 252.227-7013, and/or in similar or successor
clauses in the FAR, DOD or NASA FAR Supplement. Unpublished rights reserved
under the Copyright Laws of the United States and other countries.
------------------------------------------------------------------------------*/

/*
 * J40105_ImageFilter_by_NVIDIA
 *
 * Tests vgConvolve(), vgSeparableConvolve() and
 * vgGaussianBlur() in extreme conditions.
 *
 * The test executes a single filter operation on a
 * 16x16 source image for each pixel of the result. The
 * contents of the source image and the filter parameters
 * are selected depending on the location of the pixel,
 * and color is copied from the filtered pixel at (0, 0).
 * The filter parameters are selected so that they yield
 * a horizontal grayscale gradient.
 *
 * The scanlines of the resulting image are organized into
 * groups of 8:
 *
 * Scanlines 0 - 7:
 * - Func:   vgConvolve()
 * - Kernel: 0 <= x <= 32
 * - Scale:  0 <= x <= 3.0f
 *
 * Scanlines 8 - 15:
 * - Func:   vgConvolve()
 * - Kernel: -64 <= x <= 64
 * - Scale:  -2.0f <= x <= 2.0f
 *
 * Scanlines 16 - 23:
 * - Func:   vgConvolve()
 * - Kernel: Very large values
 * - Scale:  Very large values
 *
 * Scanlines 24 - 31:
 * - Func:   vgSeparableConvolve()
 * - Kernel: 0 <= x <= 32
 * - Scale:  0 <= x <= 3.0f
 *
 * Scanlines 32 - 39:
 * - Func:   vgSeparableConvolve()
 * - Kernel: -64 <= x <= 64
 * - Scale:  -2.0f <= x <= 2.0f
 *
 * Scanlines 40 - 47:
 * - Func:   vgSeparableConvolve()
 * - Kernel: Very large values
 * - Scale:  Very large values
 *
 * Scanlines 48 - 55:
 * - Func:   vgGaussianBlur()
 * - Dev:    Varying, X and Y close to each other
 *
 * Scanlines 56 - 63:
 * - Func:   vgGaussianBlur()
 * - Dev:    Varying, X and Y very different
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40105_ImageFilter_by_NVIDIA(CT_File *AnsFile)
{
    static const struct
    {
        VGint           width;
        VGint           height;
        VGint           minCoef;
        VGint           maxCoef;
        VGfloat         scale;
        VGint           imageFactors[16];
    } rows[] =
    {
        /*  index   width   height  minCoef maxCoef scale   imageFactors */

        /*  0 */ {  1,      1,      0,      4,     1.0f,    { 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  1 */ {  7,      1,      0,      4,     2.0f,    { 16,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  2 */ {  1,      7,      0,      4,     3.0f,    { 16, 12,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  3 */ {  7,      7,      0,      4,     0.5f,    { 16, 16, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  4 */ {  3,      3,      0,     32,     0.1f,    { 16, 14, 12, 10,  8,  6,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  5 */ { 15,      7,      0,     32,     0.0f,    { 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1 } },
        /*  6 */ {  7,     15,      0,     32,     3.0e-2f, { 16, 16, 16, 16, 16, 16, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  7 */ { 15,     15,      0,     32,     8.0e-3f, { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 } },

        /*  8 */ { 15,      1,     -4,     4,      1.0f,    { 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /*  9 */ {  1,     15,     -4,     4,      2.0f,    { 16,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 10 */ { 15,     15,     -4,     4,     -1.0f,    { 16, 12,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 11 */ { 15,     15,     -4,     4,     -2.0f,    { 16, 16, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 12 */ { 15,     15,    -32,    32,      1.0e-2f, { 16, 14, 12, 10,  8,  6,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 13 */ { 15,     15,    -32,     0,     -1.0e-9f, { 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1 } },
        /* 14 */ { 15,     15,    -32,   -16,      1.0e-2f, { 16, 16, 16, 16, 16, 16, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 15 */ { 15,     15,    -64,    64,      1.0e-3f, { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 } },

        /* 16 */ { 15,     15,      0, 32767,      1.0e-6f, { 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 17 */ { 15,     15, -32768,     0,      1.0e-7f, { 16,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 18 */ { 15,     15, -32768, 32767,      1.0e-7f, { 16, 12,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 19 */ { 15,     15,     -1,     1,      1.0e3f,  {  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 20 */ { 15,     15,     -1,     1,     -1.0e3f,  {  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 21 */ { 15,     15, -32768, 32767,      2.0e-7f, {  4,  4,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 22 */ { 15,     15, -32768, 32767,     -1.0e-9f, { 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
        /* 23 */ { 15,     15, -32768, 32767,      1.0e-9f, { 11, 11, 11, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } }
    };

    static const VGint coefSets[][17] =
    {
        /*  0 */ { 0x000, -1 },
        /*  1 */ { 0x080, -1 },
        /*  2 */ { 0x100, -1 },
        /*  3 */ { 0x100, 0x000, -1 },
        /*  4 */ { 0x100, 0x080, 0x000, 0x080, -1 },
        /*  5 */ { 0x100, 0x100, 0x000, 0x000, -1 },
        /*  6 */ { 0x100, 0x000, 0x080, 0x080, -1 },
        /*  7 */ { 0x000, 0x100, 0x080, 0x080, -1 },
        /*  8 */ { 0x100, 0x100, 0x100, 0x000, -1 },
        /*  9 */ { 0x000, 0x000, 0x000, 0x100, -1 },
        /* 10 */ { 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
                   0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, -1 },
        /* 11 */ { 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
                   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, -1 }
    };

    static const VGfloat asymmetry[] =
    {
        /*  0 */    1.0e0f  / 1.8e0f,
        /*  1 */    1.0e0f  / 1.6e0f,
        /*  2 */    1.0e0f  / 1.4e0f,
        /*  3 */    1.0e0f  / 1.2e0f,
        /*  4 */    1.2e0f  / 1.0e0f,
        /*  5 */    1.4e0f  / 1.0e0f,
        /*  6 */    1.6e0f  / 1.0e0f,
        /*  7 */    1.8e0f  / 1.0e0f,

        /*  8 */    1.0e0f  / 1.0e4f,
        /*  9 */    1.0e0f  / 1.0e3f,
        /* 10 */    1.0e0f  / 1.0e2f,
        /* 11 */    1.0e0f  / 1.0e1f,
        /* 12 */    1.0e1f  / 1.0e0f,
        /* 13 */    1.0e2f  / 1.0e0f,
        /* 14 */    1.0e3f  / 1.0e0f,
        /* 15 */    1.0e4f  / 1.0e0f,
    };

    int         imageSize       = 16;
    int         numRows         = sizeof(rows) / sizeof(rows[0]);
    int         maxConvolve     = 7;
    int         maxSeparable    = 15;
    VGfloat     maxDeviation    = 16.0f;
    int         maxCoefs        = maxConvolve * maxConvolve;
    VGshort*    coefs;
    VGubyte*    pixels;
    VGImage     vgSrcImage;
    VGImage     vgDstImage;
    int         i, j, k;
    int         x, y;

    /* Allocate the coefficient and pixel arrays. */

    coefs = (VGshort*)MALLOC(maxCoefs * sizeof(VGshort) + imageSize * imageSize * sizeof(VGubyte));
    if (!coefs)
        return CT_ERROR;
    pixels = (VGubyte*)(coefs + maxCoefs);

    /* Create the source and destination images. */

    vgSrcImage = vgCreateImage(VG_sL_8, imageSize, imageSize, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgDstImage = vgCreateImage(VG_sRGBX_8888, imageSize, imageSize, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Clear the background to opaque white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the filtering state. */
    {
        VGfloat tileFillColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSeti(VG_FILTER_FORMAT_LINEAR, VG_FALSE);
        vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, VG_FALSE);
        vgSetfv(VG_TILE_FILL_COLOR, 4, tileFillColor);
    }

    /* Loop over rows from top to bottom */

    for (i = 0; i < 64; i++)
    {
        int filterType = i / numRows;
        int r = i % numRows;
        vgSeti(VG_FILTER_CHANNEL_MASK, VG_BLUE << filterType);

        /* Set the source pixel values according to the table. */
        {
            const VGint* factors = rows[r].imageFactors;
            j = 0;
            for (y = 0; y < imageSize; y++)
                for (x = 0; x < imageSize; x++)
                {
                    int value = factors[x] * factors[y];
                    pixels[j] = (VGubyte)((value > 255) ? 255 : value);
                    j++;
                }

            vgImageSubData(vgSrcImage, pixels, imageSize, VG_sL_8, 0, 0, imageSize, imageSize);
            vgClearImage(vgDstImage, 0, 0, imageSize, imageSize);
        }

        /* Loop over pixels horizontally. */

        for (j = 0; j < WINDSIZEX; j++)
        {
            VGfloat target = (VGfloat)j / (VGfloat)(WINDSIZEX - 1);

            /* vgConvolve() or vgSeparableConvolve(). */

            if (filterType == 0 || filterType == 1)
            {
                const VGint*    coefSet = coefSets[j % (int)(sizeof(coefSets) / sizeof(coefSets[0]))];
                int             maxSize = (filterType == 0) ? maxConvolve : maxSeparable;
                int             w = (rows[r].width < maxSize) ? rows[r].width : maxSize;
                int             h = (rows[r].height < maxSize) ? rows[r].height : maxSize;
                int             numCoefs = (filterType == 0) ? w * h : w + h;
                int             coefIdx = 0;
                VGfloat         bias = 0.0f;

                /* Set the filter coefficients (kernel). */

                for (k = 0; k < numCoefs; k++)
                {
                    VGint t = coefSet[coefIdx];
                    VGshort minCoef = rows[r].minCoef;
                    VGshort maxCoef = rows[r].maxCoef;

                    if (filterType == 1)
                    {
                        minCoef = ((minCoef < 0) ? -1 : 1) * sqrt(abs(minCoef));
                        maxCoef = ((maxCoef < 0) ? -1 : 1) * sqrt(abs(maxCoef));
                    }

                    coefs[k] = (VGshort)((minCoef * (256 - t) + maxCoef * t) >> 8);

                    coefIdx++;
                    if (coefSet[coefIdx] < 0)
                        coefIdx = 0;
                }

                /* Simulate the filter at (0, 0). */

                for (y = 0; y < h; y++)
                    for (x = 0; x < w; x++)
                    {
                        VGfloat coef;
                        if (filterType == 0)
                            coef = (VGfloat)coefs[(w - 1 - x) * h + (h - 1 - y)];
                        else
                            coef = (VGfloat)coefs[w - 1 - x] * (VGfloat)coefs[w + h - 1 - y];
                        bias += coef * (VGfloat)pixels[x + y * imageSize];
                    }

                /* Select the bias so that the filter yields the
                 * desired target color. */

                bias = target - bias * rows[r].scale / 255.0f;

                /* Run the filter. */

                if (filterType == 0)
                    vgConvolve(vgDstImage, vgSrcImage, w, h, 0, 0,
                        coefs, rows[r].scale, bias, VG_TILE_FILL);
                else
                    vgSeparableConvolve(vgDstImage, vgSrcImage, w, h, 0, 0,
                        coefs, coefs + w, rows[r].scale, bias, VG_TILE_FILL);
            }

            /* vgGaussianBlur(). */

            else if (filterType == 2)
            {
                VGfloat radius = 0.0f;
                VGfloat step = 9.0f; /* Half the size of the current interval. */
                VGfloat devX;
                VGfloat devY;

                /* Binary search for a pair of deviation values that
                 * yield the desired target color. */

                do
                {
                    VGfloat newRadius = radius + step;
                    int     range = ((int)newRadius + 1) * 4;
                    VGfloat denomX = 0.0f;
                    VGfloat denomY = 0.0f;
                    VGfloat numer = 0.0f;
                    VGfloat scaleX;
                    VGfloat scaleY;

                    /* Scale the horizontal/vertical deviations based on
                     * the asymmetry value (aspect ratio). */

                    if (asymmetry[r] >= 1.0f)
                    {
                        devX = newRadius;
                        devY = newRadius / asymmetry[r];
                    }
                    else
                    {
                        devX = newRadius * asymmetry[r];
                        devY = newRadius;
                    }

                    /* Clamp to the maximum, and precalculate the
                     * exponent coefficients. */

                    devX = (devX <= maxDeviation) ? devX : maxDeviation;
                    devY = (devY <= maxDeviation) ? devY : maxDeviation;
                    scaleX = -0.5f / (devX * devX);
                    scaleY = -0.5f / (devY * devY);

                    /* Calculate the sums of the filter coefficients. */

                    for (k = -range; k <= range; k++)
                    {
                        VGfloat sqr = (VGfloat)(k * k);
                        denomX += EXP(scaleX * sqr);
                        denomY += EXP(scaleY * sqr);
                    }

                    /* Simulate the filter at (0, 0). */

                    k = 0;
                    for (y = 0; y < imageSize; y++)
                        for (x = 0; x < imageSize; x++)
                        {
                            if (pixels[k])
                                numer += (VGfloat)pixels[k] *
                                    EXP(scaleX * (VGfloat)(x * x) + scaleY * (VGfloat)(y * y));
                            k++;
                        }

                    /* Still brighter that the target -> use the larger radius. */

                    if (numer > target * denomX * denomY * 255.0f)
                        radius = newRadius;

                    step *= 0.5f;
                }
                while (step >= 0.001f);

                /* Run the filter. */

                vgGaussianBlur(vgDstImage, vgSrcImage, devX, devY, VG_TILE_FILL);
            }

            /* Use the pixel at (0, 0) as the result. */

            vgSetPixels(j, WINDSIZEY - 1 - i, vgDstImage, 0, 0, 1, 1);
        }
    }

    /* Clean up and save the result. */

    FREE(coefs);
    if (vgSrcImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImage);
    if (vgDstImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();
    return CT_NO_ERROR;
}

