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
 * H30206_ImageDithering_by_NVIDIA
 *
 * Tests that enabling dithering in vgCopyImage() produces
 * consistent results, if supported by the implementation.
 *
 * The test consists of 6 subtests, each operating on a
 * single destination image format. The subtests are organized
 * as follows:
 *
 * 0000: VG_sRGB_565
 * 0001: VG_sRGBA_5551
 * 0002: VG_sRGBA_4444
 * 0003: VG_BW_1
 * 0004: VG_A_1
 * 0005: VG_A_4
 *
 * Each subtest creates a source image with the same channels
 * and color format as the destination, but with more bits per
 * channel. For the formats containing color or luminance
 * channels, the test initializes the source image to a vertical
 * opaque green gradient. For the alpha formats, it uses an alpha
 * gradient instead.
 *
 * The test then calls vgCopyImage() twice, with dithering
 * disabled and enabled, to determine whether the implementation
 * supports dithering on the particular format. If the images
 * differ, the test uses vgGaussianBlur() with a large horizontal
 * deviation to average out the color values. If the images do
 * not differ, the test just outputs the original source image.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result H30206_ImageDithering_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const struct
    {
        VGImageFormat original;
        VGImageFormat dithered;
    } imageFormats[] =
    {
        { VG_sRGBX_8888,    VG_sRGB_565 },
        { VG_sRGBA_8888,    VG_sRGBA_5551 },
        { VG_sRGBA_8888,    VG_sRGBA_4444 },
        { VG_lL_8,          VG_BW_1 },
        { VG_A_8,           VG_A_1 },
        { VG_A_8,           VG_A_4 }
    };

    VGuint*     buffer;
    int         stride = WINDSIZEX * sizeof(VGuint);
    VGImage     vgOriginalImage;
    VGImage     vgTempImage;
    VGImage     vgRoundedImage;
    VGImage     vgDitheredImage;
    VGboolean   ditheringSupported;
    int         i;

    /* Allocate the pixel buffer. */

    buffer = MALLOC(WINDSIZEY * stride * 2);
    if (!buffer)
        return CT_ERROR;

    /* Initialize the pixel buffer. */
    {
        int idx = 0;
        int x, y;
        for (y = 0; y < WINDSIZEY; y++)
            for (x = 0; x < WINDSIZEX; x++)
            {
                int yy = y * 255 / (WINDSIZEY - 1);
                buffer[idx] = 0x000000ff +
                    0x01000000 * yy +
                    0x00010000 * (255 - (255 - yy) * (255 - yy) / 255) +
                    0x00000100 * (yy * yy / 255);
                idx++;
            }
    }

    /* Create the original image. */

    vgOriginalImage = vgCreateImage(imageFormats[subtest].original,
        WINDSIZEX, WINDSIZEY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageSubData(vgOriginalImage, buffer, stride,
        (imageFormats[subtest].original == VG_A_8) ? VG_sARGB_8888 : VG_sRGBA_8888,
        0, 0, WINDSIZEX, WINDSIZEY);

    /* Create the temporary image. */

    vgTempImage = vgCreateImage(imageFormats[subtest].original,
        WINDSIZEX, WINDSIZEY, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Create the rounded image. */

    vgRoundedImage = vgCreateImage(imageFormats[subtest].dithered,
        WINDSIZEX, WINDSIZEY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgCopyImage(vgRoundedImage, 0, 0, vgOriginalImage, 0, 0,
        WINDSIZEX, WINDSIZEY, VG_FALSE);

    /* Create the dithered image. */

    vgDitheredImage = vgCreateImage(imageFormats[subtest].dithered,
        WINDSIZEX, WINDSIZEY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgCopyImage(vgDitheredImage, 0, 0, vgOriginalImage, 0, 0,
        WINDSIZEX, WINDSIZEY, VG_TRUE);

    /* Compare the rounded and dithered images to determine
     * whether dithering is supported by the implementation. */
    {
        int numPixels = WINDSIZEX * WINDSIZEY;
        VGuint* roundedBuf = buffer;
        VGuint* ditheredBuf = buffer + numPixels;

        vgGetImageSubData(vgRoundedImage, roundedBuf, stride,
            VG_sRGBA_8888, 0, 0, WINDSIZEX, WINDSIZEY);
        vgGetImageSubData(vgDitheredImage, ditheredBuf, stride,
            VG_sRGBA_8888, 0, 0, WINDSIZEX, WINDSIZEY);

        ditheringSupported = VG_FALSE;
        for (i = 0; i < numPixels; i++)
            if (roundedBuf[i] != ditheredBuf[i])
            {
                ditheringSupported = VG_TRUE;
                break;
            }
    }

    /* Dithering is supported -> replace the original image
     * with a blurred version of the dithered image. */

    if (ditheringSupported)
    {
        vgSeti(VG_FILTER_FORMAT_LINEAR, VG_TRUE);
        vgGaussianBlur(vgTempImage, vgDitheredImage, 16.0f, 1.0e-8f, VG_TILE_REPEAT);
        for (i = 0; i < 7; i++)
        {
            vgGaussianBlur(vgOriginalImage, vgTempImage, 16.0f, 1.0e-8f, VG_TILE_REPEAT);
            vgGaussianBlur(vgTempImage, vgOriginalImage, 16.0f, 1.0e-8f, VG_TILE_REPEAT);
        }
        vgGaussianBlur(vgOriginalImage, vgTempImage, 1.0e-8f, 12.0f, VG_TILE_PAD);
    }

    /* Draw the original image. */

    vgSetPixels(0, 0, vgOriginalImage, 0, 0, WINDSIZEX, WINDSIZEY);

    /* Clean up and save the result. */

    FREE(buffer);
    if (vgOriginalImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgOriginalImage);
    if (vgTempImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgTempImage);
    if (vgRoundedImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgRoundedImage);
    if (vgDitheredImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDitheredImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

