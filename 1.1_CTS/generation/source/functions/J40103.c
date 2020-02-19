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
 * J40103_ImageFilter_by_NVIDIA
 *
 * Tests vgConvolve() on various commonly used kernels.
 * The test consists of 4 subtests, each operating on a
 * different source image. The resulting image contains
 * a 4x4 grid of filtered results, one for each filter
 * kernel.
 */

#include "../main.h"
#include "../util/util.h"
#include "../static/hybrid/lines_64x64.h"
#include "../static/hybrid/pukki_16x16.h"
#include "../static/hybrid/mobile_man.h"

CT_Result J40103_ImageFilter_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const struct
    {
        VGint   width;
        VGint   height;
        VGint   shiftX;
        VGint   shiftY;
        VGfloat scale;
        VGfloat bias;
        VGshort coefs[49];
    } kernels[] =
    {
        /* 1st row, 1st column: 1x1 identity */
        { 1, 1, 0, 0, 1.0f, 0.0f, {
            1,
        }},

        /* 1st row, 2nd column: 3x3 binomial blur */
        { 3, 3, 1, 1, 1.0f / 16.0f, 0.0f, {
            1,  2,  1,
            2,  4,  2,
            1,  2,  1,
        }},

        /* 1st row, 3rd column: 5x5 binomial blur */
        { 5, 5, 2, 2, 1.0f / 256.0f, 0.0f, {
            1,  4,  6,  4,  1,
            4, 16, 24, 16,  4,
            6, 24, 36, 24,  6,
            4, 16, 24, 16,  4,
            1,  4,  6,  4,  1,
        }},

        /* 1st row, 4th column: 5x5 mean */
        { 5, 5, 2, 2, 1.0f / 25.0f, 0.0f, {
            1,  1,  1,  1,  1,
            1,  1,  1,  1,  1,
            1,  1,  1,  1,  1,
            1,  1,  1,  1,  1,
            1,  1,  1,  1,  1,
        }},

        /* 2nd row, 1st column: 7x7 diagonal motion blur */
        { 7, 7, 3, 3, 1.0f / 7.0f, 0.0f, {
            1,  0,  0,  0,  0,  0,  0,
            0,  1,  0,  0,  0,  0,  0,
            0,  0,  1,  0,  0,  0,  0,
            0,  0,  0,  1,  0,  0,  0,
            0,  0,  0,  0,  1,  0,  0,
            0,  0,  0,  0,  0,  1,  0,
            0,  0,  0,  0,  0,  0,  1,
        }},

        /* 2nd row, 2nd column: 3x3 sharpen (4-connected) */
        { 3, 3, 1, 1, 1.0f, 0.0f, {
            0, -1,  0,
           -1,  5, -1,
            0, -1,  0,
        }},

        /* 2nd row, 3rd column: 3x3 sharpen (8-connected) */
        { 3, 3, 1, 1, 1.0f, 0.0f, {
           -1, -1, -1,
           -1,  9, -1,
           -1, -1, -1,
        }},

        /* 2nd row, 4th column: 5x5 soft sharpen */
        { 5, 5, 1, 1, 1.0f / 8.0f, 0.0f, {
           -1, -1, -1, -1, -1,
           -1,  2,  2,  2, -1,
           -1,  2,  8,  2, -1,
           -1,  2,  2,  2, -1,
           -1, -1, -1, -1, -1,
        }},

        /* 3rd row, 1st column: 3x3 laplacian (4-connected) */
        { 3, 3, 1, 1, 1.0f / 4.0f, 0.5f, {
            0, -1,  0,
           -1,  4, -1,
            0, -1,  0,
        }},

        /* 3rd row, 2nd column: 3x3 laplacian (8-connected) */
        { 3, 3, 1, 1, 1.0f / 8.0f, 0.5f, {
           -1, -1, -1,
           -1,  8, -1,
           -1, -1, -1,
        }},

        /* 3rd row, 3rd column: 2x1 horizontal difference */
        { 2, 1, 0, 1, 1.0f, 0.5f, {
            1,
           -1,
        }},

        /* 3rd row, 4th column: 3x3 horizontal sobel */
        { 3, 3, 1, 1, 1.0f / 4.0f, 0.5f, {
            1,  2,  1,
            0,  0,  0,
           -1, -2, -1,
        }},

        /* 4th row, 1st column: 1x2 vertical difference */
        { 1, 2, 0, 1, 1.0f, 0.5f, {
            1, -1,
        }},

        /* 4th row, 2nd column: 3x3 vertical sobel */
        { 3, 3, 1, 1, 1.0f / 4.0f, 0.5f, {
            1,  0, -1,
            2,  0, -2,
            1,  0, -1,
        }},

        /* 4th row, 3rd column: 3x3 diagonal emboss */
        { 3, 3, 1, 1, 1.0f / 3.0f, 0.5f, {
            0, -1, -1,
            1,  0, -1,
            1,  1,  0,
        }},

        /* 4th row, 4th column: 5x5 diagonal emboss */
        { 5, 5, 2, 2, 1.0f / 10.0f, 0.5f, {
            0, -1, -1, -1, -1,
            1,  0, -1, -1, -1,
            1,  1,  0, -1, -1,
            1,  1,  1,  0, -1,
            1,  1,  1,  1,  0,
        }}
    };

    int     imageWidth  = 16;
    int     imageHeight = 16;
    int     numPerRow   = 4;
    VGImage vgSrcImage;
    VGImage vgDstImage;
    int     i;

    /* Create the images. */

    vgSrcImage = vgCreateImage(VG_sRGBA_8888, imageWidth, imageHeight, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgDstImage = vgCreateImage(VG_sRGBA_8888, imageWidth, imageHeight, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Initialize the source image depending on the subtest. */
    {
        VGImageFormat   format  = 0;
        const void*     data    = NULL;
        int             stride  = 0;

        switch (subtest)
        {
        case 0: format = VG_sRGBX_8888; data = pukki_16x16_data; stride = pukki_16x16_stride; break;
        case 1: format = VG_sRGBA_8888; data = pukki_16x16_data; stride = pukki_16x16_stride; break;
        case 2: format = VG_sRGBX_8888; data = lines_64x64_data; stride = lines_64x64_stride; break;
        case 3: format = VG_sRGBX_8888; data = mobile_man_data; stride = mobile_man_stride; break;
        }

        vgImageSubData(vgSrcImage, data, stride, format, 0, 0, imageWidth, imageHeight);
    }

    /* Clear the background to opaque white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the filtering state. */

    vgSeti(VG_FILTER_FORMAT_LINEAR, VG_TRUE); /* physically correct */
    vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, VG_FALSE); /* ignore alpha */
    vgSeti(VG_FILTER_CHANNEL_MASK, VG_RED | VG_GREEN | VG_BLUE); /* ignore alpha */

    /* Loop over the filter kernels. */

    for (i = 0; i < (int)(sizeof(kernels) / sizeof(kernels[0])); i++)
    {
        int x = (i % numPerRow) * imageWidth;
        int y = WINDSIZEY - (i / numPerRow + 1) * imageHeight;

        /* Copy the unmodified alpha. */

        vgCopyImage(vgDstImage, 0, 0, vgSrcImage, 0, 0, imageWidth, imageHeight, VG_FALSE);

        /* Perform the filtering. */

        vgConvolve(vgDstImage, vgSrcImage,
            kernels[i].width, kernels[i].height, kernels[i].shiftX, kernels[i].shiftY,
            kernels[i].coefs, kernels[i].scale, kernels[i].bias,
            VG_TILE_PAD);

        /* Copy the resulting pixels to the screen. */

        vgSetPixels(x, y, vgDstImage, 0, 0, imageWidth, imageHeight);
    }

    /* Clean up and save the result. */

    if (vgSrcImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImage);
    if (vgDstImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

