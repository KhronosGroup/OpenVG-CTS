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
 * J40102_ImageFilter_by_NVIDIA
 *
 * Tests the quality of vgGaussianBlur() by sweeping
 * through different deviation values.
 *
 * The test consists of 4 subtests, one for each tiling
 * mode as follows:
 *
 * 0000: VG_TILE_FILL
 * 0001: VG_TILE_PAD
 * 0002: VG_TILE_REPEAT
 * 0003: VG_TILE_REFLECT
 *
 * Each subtest is further divided into four quadrants.
 * In the bottom-left and top-left quadrants, a horizontal
 * 32x1 image is filtered multiple times with different X
 * deviations. Each scanline contains the result of a single
 * filtering operation, with the deviation increasing from
 * the bottom to the top. In the bottom-right and top-right
 * quadrants, a vertical image is filtered similarly with a
 * varying Y deviation.
 *
 * Different filter format settings (VG_FILTER_FORMAT_LINEAR
 * and VG_FILTER_FORMAT_PREMULTIPLIED) are used for each
 * quadrant:
 *
 * Bottom-left:  sRGBA
 * Bottom-right: sRGBA_PRE
 * Top-left:     lRGBA
 * Top-right:    lRGBA_PRE
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40102_ImageFilter_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGTilingMode tilingModes[] =
    {
        VG_TILE_FILL,
        VG_TILE_PAD,
        VG_TILE_REPEAT,
        VG_TILE_REFLECT
    };

    VGuint          pixels[32];
    int             itemSize = sizeof(pixels) / sizeof(pixels[0]);
    VGTilingMode    tilingMode = tilingModes[subtest];
    VGImage         vgSrcImageH;
    VGImage         vgDstImageH;
    VGImage         vgSrcImageV;
    VGImage         vgDstImageV;
    int             i, j;

    /* Create the images. */

    vgSrcImageH = vgCreateImage(VG_sRGBA_8888, itemSize, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgDstImageH = vgCreateImage(VG_sRGBA_8888, itemSize, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSrcImageV = vgCreateImage(VG_sRGBA_8888, 1, itemSize, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgDstImageV = vgCreateImage(VG_sRGBA_8888, 1, itemSize, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Initialize the source image pixels. */

    for (i = 0; i < 4; i++)
        pixels[i] = 0xff0000ff;
    for (i = 4; i < 16; i++)
        pixels[i] = 0x00ff00ff;
    for (i = 16; i < 28; i++)
        pixels[i] = 0x0000ffff;
    for (i = 28; i < 32; i++)
        pixels[i] = 0xff000040;

    vgImageSubData(vgSrcImageH, pixels, 0, VG_sRGBA_8888, 0, 0, itemSize, itemSize);
    vgImageSubData(vgSrcImageV, pixels, sizeof(VGuint), VG_sRGBA_8888, 0, 0, itemSize, itemSize);

    /* Use semi-transparent magenta as the tile fill color. */
    {
        VGfloat tileFillColor[] = { 1.0f, 0.0f, 1.0f, 0.5f };
        vgSetfv(VG_TILE_FILL_COLOR, 4, tileFillColor);
    }

    /* Clear the background to opaque white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Loop over the two rows. */

    for (i = 0; i < 2; i++)
    {
        int y = i  * itemSize;
        vgSeti(VG_FILTER_FORMAT_LINEAR, (i == 0) ? VG_FALSE : VG_TRUE);

        /* Loop over the deviation values. */

        for (j = 0; j < itemSize; j++)
        {
            VGfloat dev = POW((VGfloat)j / (VGfloat)(itemSize - 1), 2.0f) * 15.8f + 0.1f;

            /* Left-hand column: horizontal blur. */

            vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, VG_FALSE);
            vgGaussianBlur(vgDstImageH, vgSrcImageH, dev, 1.0f, tilingMode);
            vgSetPixels(0, y + j, vgDstImageH, 0, 0, itemSize, 1);

            /* Right-hand column: vertical blur. */

            vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, VG_TRUE);
            vgGaussianBlur(vgDstImageV, vgSrcImageV, 1.0f, dev, tilingMode);
            vgSetPixels(itemSize + j, y, vgDstImageV, 0, 0, 1, itemSize);
        }
    }

    /* Clean up and save the result. */

    if (vgSrcImageH != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImageH);
    if (vgDstImageH != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImageH);
    if (vgSrcImageV != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImageV);
    if (vgDstImageV != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImageV);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

