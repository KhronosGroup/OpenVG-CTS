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
 * J40108_ImageFilter_by_NVIDIA
 *
 * Tests that all combinations of filter input settings
 * work as expected.
 *
 * The test consists of 15 subtests, one for each
 * source/destination image format as follows:
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
 * Each subtest draws a 16x16 grid of filtered images.
 * The source and destination images are non-overlapping
 * children of a common parent image. The two highest bits
 * of the row index (from top to bottom) determine the
 * dimensions of the images:
 *
 * 00: dst = (4, 4), src = (4, 4)
 * 01: dst = (4, 4), src = (6, 6)
 * 10: dst = (3, 3), src = (4, 4)
 * 11: dst = (4, 4), src = (3, 3)
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
 * 1st:         vgClearImage() with solid white
 * 2nd:         vgColorMatrix() that scales the color channels
 * 3rd-6th:     vgConvolve() with each tiling mode
 * 7th-10th:    vgSeparableConvolve() with each tiling mode
 * 11th-14th:   vgGaussianBlur() with each tiling mode
 * 15th:        vgLookup() that scales the color channels
 * 16th:        vgLookupSingle() that scales the color channels
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40108_ImageFilter_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
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

    int         itemSize = 4;
    VGuint*     intLUT;
    VGubyte*    byteScaleLUT;
    VGubyte*    byteIdentLUT;
    VGImage     vgParentImage;
    VGImage     vgChildImageA;
    VGImage     vgChildImageB;
    VGImage     vgChildImageC;
    VGImage     vgChildImageD;
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
        intLUT[i] = 0x00010000 * (i * 2 / 3) + 0x01000000 * ((255 - i) * 2 / 3) + 0x000000ff;
        byteScaleLUT[i] = (VGubyte)(i * 2 / 3);
        byteIdentLUT[i] = (VGubyte)i;
    }

    /* Create the images. */

    vgParentImage = vgCreateImage(imageFormats[subtest],
        9, 10, VG_IMAGE_QUALITY_NONANTIALIASED);

    vgChildImageA = vgChildImage(vgParentImage, 0, 0, 4, 4);
    vgChildImageB = vgChildImage(vgParentImage, 4, 0, 4, 4);
    vgChildImageC = vgChildImage(vgParentImage, 0, 4, 6, 6);
    vgChildImageD = vgChildImage(vgParentImage, 6, 4, 3, 3);

    /* Clear the background to opaque black. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Loop over the rows from top to bottom */

    for (i = 0; i < 16; i++)
    {
        VGImage vgDstImage = VG_INVALID_HANDLE;
        VGImage vgSrcImage = VG_INVALID_HANDLE;

        /* Row % 4: filter format. */

        vgSeti(VG_FILTER_FORMAT_LINEAR, ((i & 1) != 0));
        vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, ((i & 2) != 0));

        /* Row / 4: the orientation of the source and destination images. */

        switch (i / 4)
        {
        case 0: vgDstImage = vgChildImageA; vgSrcImage = vgChildImageB; break;
        case 1: vgDstImage = vgChildImageA; vgSrcImage = vgChildImageC; break;
        case 2: vgDstImage = vgChildImageD; vgSrcImage = vgChildImageB; break;
        case 3: vgDstImage = vgChildImageA; vgSrcImage = vgChildImageD; break;
        }

        /* Loop over the columns from left to right. */

        for (j = 0; j < 16; j++)
        {
            static const VGTilingMode tilingModes[] =
            {
                VG_TILE_FILL,
                VG_TILE_PAD,
                VG_TILE_REPEAT,
                VG_TILE_REFLECT
            };

            /* Clear the images and set the tile fill color. */
            {
                VGfloat dstColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                VGfloat srcColorA[] = { 1.0f, 0.0f, 0.0f, 0.75f };
                VGfloat srcColorB[] = { 0.0f, 1.0f, 0.0f, 0.75f };
                VGfloat tileFillColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };

                vgSetfv(VG_CLEAR_COLOR, 4, dstColor);
                vgClearImage(vgDstImage, 0, 0, itemSize, itemSize);
                vgSetfv(VG_CLEAR_COLOR, 4, srcColorA);
                vgClearImage(vgSrcImage, 0, 0, 6, 6);
                vgSetfv(VG_CLEAR_COLOR, 4, srcColorB);
                vgClearImage(vgSrcImage, 1, 1, 3, 3);
                vgSetfv(VG_TILE_FILL_COLOR, 4, tileFillColor);
            }

            /* Run a filter depending on the column. */

            switch (j)
            {
            /* 1st column: vgClearImage() with solid white. */
            case 0:
                break;

            /* 2nd column: vgColorMatrix() that scales the color channels. */
            case 1:
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

            /* 3rd-6th column: vgConvolve() with each tiling mode. */
            case 2:
            case 3:
            case 4:
            case 5:
                {
                    static const VGshort kernel[] =
                    {
                        1,  4,  6,  4,  1,
                        4, 16, 24, 16,  4,
                        6, 24, 36, 24,  6,
                        4, 16, 24, 16,  4,
                        1,  4,  6,  4,  1
                    };
                    vgConvolve(vgDstImage, vgSrcImage, 5, 5, 2, 2,
                        kernel, 1.0f / 256.0f, 0.0f, tilingModes[j - 2]);
                }
                break;

            /* 7th-10th column: vgSeparableConvolve() with each tiling mode. */
            case 6:
            case 7:
            case 8:
            case 9:
                {
                    static const VGshort kernel[] =
                    { 1,  4,  6,  4,  1 };
                    vgSeparableConvolve(vgDstImage, vgSrcImage, 5, 5, 2, 2,
                        kernel, kernel, 1.0f / 256.0f, 0.0f, tilingModes[j - 6]);
                }
                break;

            /* 11th-14th column: vgGaussianBlur() with each tiling mode. */
            case 10:
            case 11:
            case 12:
            case 13:
                vgGaussianBlur(vgDstImage, vgSrcImage, 1.0f, 1.0f,
                    tilingModes[j - 10]);
                break;

            /* 15th column: vgLookup() that scales the color channels. */
            case 14:
                vgLookup(vgDstImage, vgSrcImage,
                    byteScaleLUT, byteScaleLUT, byteScaleLUT, byteIdentLUT,
                    VG_FALSE, VG_FALSE);
                break;

            /* 16th column: vgLookupSingle() that scales the color channels. */
            case 15:
                vgLookupSingle(vgDstImage, vgSrcImage,
                    intLUT, VG_GREEN, VG_FALSE, VG_FALSE);
                break;
            }

            /* Copy the pixels to the screen. */

            vgSetPixels(j * itemSize, WINDSIZEY - (i + 1) * itemSize,
                vgDstImage, 0, 0, itemSize, itemSize);
        }
    }

    /* Clean up and save the result. */

    FREE(intLUT);
    if (vgParentImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgParentImage);
    if (vgChildImageA != VG_INVALID_HANDLE)
        vgDestroyImage(vgChildImageA);
    if (vgChildImageB != VG_INVALID_HANDLE)
        vgDestroyImage(vgChildImageB);
    if (vgChildImageC != VG_INVALID_HANDLE)
        vgDestroyImage(vgChildImageC);
    if (vgChildImageD != VG_INVALID_HANDLE)
        vgDestroyImage(vgChildImageD);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

