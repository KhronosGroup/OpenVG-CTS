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
 * J40109_ImageFilter_by_NVIDIA
 *
 * Tests that all combinations of filter output settings
 * work as expected.
 *
 * The test consists of 15 subtests, one for each
 * destination image format as follows:
 *
 * 0000: VG_sRGBX_8888
 * 0001: VG_lRGBX_8888
 * 0002: VG_sRGBA_8888
 * 0003: VG_lRGBA_8888
 * 0004: VG_sRGBA_8888_PRE
 * 0005: VG_lRGBA_8888_PRE
 * 0006: VG_sRGB_565
 * 0007: VG_sRGBA_5551
 * 0008: VG_sRGBA_4444
 * 0009: VG_sL_8
 * 0010: VG_lL_8
 * 0011: VG_BW_1
 * 0012: VG_A_8
 * 0013: VG_A_1
 * 0014: VG_A_4
 *
 * Each subtest draws a 20x16 grid of filtered images.
 * The source and destination are parent images of size 4x3,
 * and the format of the source image is always sRGBA_8888.
 *
 * The channel mask is selected based on the three highest
 * bits of the row index (from top to bottom):
 *
 * 000: VG_RED | VG_GREEN | VG_BLUE | VG_ALPHA | (1 << 4)
 * 001: VG_RED | VG_GREEN | VG_ALPHA
 * 010: VG_RED | VG_GREEN
 * 011: VG_ALPHA
 * 100: 0
 *
 * The filter format is selected based on the two lowest
 * bits of the row index:
 *
 * 00: sRGBA
 * 01: lRGBA
 * 10: sRGBA_PRE
 * 11: lRGBA_PRE
 *
 * The column index (from left to right) determines the
 * filter operations as follows:
 *
 * 1st:         vgColorMatrix() that scales the color channels
 * 2nd:         vgColorMatrix() that scales the alpha channel
 * 3rd:         vgConvolve() that retains all channels
 * 4th:         vgConvolve() that scales all channels
 * 5th:         vgSeparableConvolve() that retains all channels
 * 6th:         vgSeparableConvolve() that scales all channels
 * 7th:         vgGaussianBlur() with negligible deviation
 * 8th:         vgGaussianBlur() with visible deviation
 * 9th-12th:    vgLookup() with each output format
 * 13th-16th:   vgLookupSingle() with each output format
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40109_ImageFilter_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGImageFormat imageFormats[] =
    {
        VG_sRGBX_8888,
        VG_lRGBX_8888,
        VG_sRGBA_8888,
        VG_lRGBA_8888,
        VG_sRGBA_8888_PRE,
        VG_lRGBA_8888_PRE,
        VG_sRGB_565,
        VG_sRGBA_5551,
        VG_sRGBA_4444,
        VG_sL_8,
        VG_lL_8,
        VG_BW_1,
        VG_A_8,
        VG_A_1,
        VG_A_4
    };

    int         imageWidth = 4;
    int         imageHeight = 3;
    VGuint*     intLUT;
    VGubyte*    byteScaleLUT;
    VGubyte*    byteIdentLUT;
    VGImage     vgDstImage;
    VGImage     vgSrcImage;
    int         i, j;

    /* Allocate the lookup tables. */

    intLUT = (VGuint*)MALLOC(256 * (sizeof(VGuint) + 2 * sizeof(VGubyte)));
    if (!intLUT)
        return CT_ERROR;

    byteScaleLUT = (VGubyte*)(intLUT + 256);
    byteIdentLUT = byteScaleLUT + 256;

    /* Initialize the lookup tables. */

    for (i = 0; i < 256; i++)
    {
        intLUT[i] = 0x01010100 * i + 0x00000001 * (255 - i * 2 / 3);
        byteScaleLUT[i] = (VGubyte)(i * 2 / 3);
        byteIdentLUT[i] = (VGubyte)i;
    }

    /* Create the source and destination images. */

    vgDstImage = vgCreateImage(imageFormats[subtest],
        imageWidth, imageHeight, VG_IMAGE_QUALITY_NONANTIALIASED);

    vgSrcImage = vgCreateImage(VG_sRGBA_8888,
        imageWidth, imageHeight, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Clear the background to opaque black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Loop over the rows from top to bottom */

    for (i = 0; i < 20; i++)
    {
        /* Row % 4: filter format. */

        vgSeti(VG_FILTER_FORMAT_LINEAR, ((i & 1) != 0));
        vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, ((i & 2) != 0));

        /* Row / 4: channel mask. */
        {
            static const VGint channelMasks[] =
            {
                VG_RED | VG_GREEN | VG_BLUE | VG_ALPHA | (1 << 4),
                VG_RED | VG_GREEN | VG_ALPHA,
                VG_RED | VG_GREEN,
                VG_ALPHA,
                0
            };
            vgSeti(VG_FILTER_CHANNEL_MASK, channelMasks[i / 4]);
        }

        /* Loop over the columns from left to right. */

        for (j = 0; j < 16; j++)
        {
            VGshort kernel = 1;

            /* Clear the images and set the tile fill color. */
            {
                static const VGuint srcPixels[] =
                {
                    0xff8000ff, 0x80ff80ff, 0x0080ffff, 0x000080ff,
                    0xff8000d0, 0x80ff80d0, 0x0080ffd0, 0x000080d0,
                    0xff8000a0, 0x80ff80a0, 0x0080ffa0, 0x000080a0
                };

                VGfloat dstColor[] = { 0.5f, 0.5f, 0.5f, 0.75f };
                VGfloat tileFillColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

                vgSetfv(VG_CLEAR_COLOR, 4, dstColor);
                vgClearImage(vgDstImage, 0, 0, imageWidth, imageHeight);
                vgImageSubData(vgSrcImage, srcPixels, imageWidth * sizeof(VGuint),
                    VG_sRGBA_8888, 0, 0, imageWidth, imageHeight);
                vgSetfv(VG_TILE_FILL_COLOR, 4, tileFillColor);
            }

            /* Run a filter depending on the column. */

            switch (j)
            {
            /* 1st column: vgColorMatrix() that scales the color channels. */
            case 0:
                {
                    static const VGfloat colorMatrix[] =
                    {
                        2.0f / 3.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 2.0f / 3.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 2.0f / 3.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 0.0f, 0.0f
                    };
                    vgColorMatrix(vgDstImage, vgSrcImage, colorMatrix);
                }
                break;

            /* 2nd column: vgColorMatrix() that scales the alpha channel. */
            case 1:
                {
                    static const VGfloat colorMatrix[] =
                    {
                        1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 2.0f / 3.0f,
                        0.0f, 0.0f, 0.0f, 0.0f
                    };
                    vgColorMatrix(vgDstImage, vgSrcImage, colorMatrix);
                }
                break;

            /* 3rd column: vgConvolve() that retains all channels. */
            case 2:
                vgConvolve(vgDstImage, vgSrcImage, 1, 1, 0, 0,
                    &kernel, 1.0f, 0.0f, VG_TILE_FILL);
                break;

            /* 4th column: vgConvolve() that scales all channels. */
            case 3:
                vgConvolve(vgDstImage, vgSrcImage, 1, 1, 0, 0,
                    &kernel, 2.0f / 3.0f, 0.0f, VG_TILE_FILL);
                break;

            /* 5th column: vgSeparableConvolve() that retains all channels. */
            case 4:
                vgSeparableConvolve(vgDstImage, vgSrcImage, 1, 1, 0, 0,
                    &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
                break;

            /* 6th column: vgSeparableConvolve() that scales all channels. */
            case 5:
                vgSeparableConvolve(vgDstImage, vgSrcImage, 1, 1, 0, 0,
                    &kernel, &kernel, 2.0f / 3.0f, 0.0f, VG_TILE_FILL);
                break;

            /* 7th column: vgGaussianBlur() with negligible deviation. */
            case 6:
                vgGaussianBlur(vgDstImage, vgSrcImage, 0.1f, 0.1f,
                    VG_TILE_PAD);
                break;

            /* 8th column: vgGaussianBlur() with visible deviation. */
            case 7:
                vgGaussianBlur(vgDstImage, vgSrcImage, 1.5f, 1.5f,
                    VG_TILE_PAD);
                break;

            /* 9th-12th column: vgLookup() with each output format. */
            case 8:
            case 9:
            case 10:
            case 11:
                vgLookup(vgDstImage, vgSrcImage,
                    byteIdentLUT, byteIdentLUT, byteIdentLUT, byteScaleLUT,
                    ((j & 1) != 0), ((j & 2) != 0));
                break;

            /* 13th-16th column: vgLookupSingle() with each output format. */
            case 12:
            case 13:
            case 14:
            case 15:
                vgLookupSingle(vgDstImage, vgSrcImage, intLUT, VG_GREEN,
                    ((j & 1) != 0), ((j & 2) != 0));
                break;
            }

            /* Copy the pixels to the screen. */

            vgSetPixels(j * imageWidth, WINDSIZEY - (i + 1) * imageHeight,
                vgDstImage, 0, 0, imageWidth, imageHeight);
        }
    }

    /* Clean up and save the result. */

    FREE(intLUT);
    if (vgDstImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImage);
    if (vgSrcImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

