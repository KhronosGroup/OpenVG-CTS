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
 * J40106_ImageFilter_by_NVIDIA
 *
 * Tests different shift values on vgConvolve() and
 * vgSeparableConvolve() in conjunction with the tiling modes.
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
 * image is filtered multiple times with different X shifts.
 * Each scanline contains the result of a single filtering
 * operation, with the shift increasing from the bottom to
 * the top. In the bottom-right and top-right quadrants,
 * a vertical image is filtered similarly with a varying Y
 * shift.
 *
 * The bottom-left and bottom-right quadrants are drawn
 * using vgConvolve(), while the top-left and top-right
 * quadrants are drawn using vgSeparableConvolve().
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40106_ImageFilter_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGTilingMode tilingModes[] =
    {
        VG_TILE_FILL,
        VG_TILE_PAD,
        VG_TILE_REPEAT,
        VG_TILE_REFLECT
    };

    VGTilingMode    tilingMode = tilingModes[subtest];
    VGImage         vgDstImageX;
    VGImage         vgDstImageY;
    VGImage         vgSrcImageX;
    VGImage         vgSrcImageY;
    int             i;

    /* Create the images. */
    {
        VGImage vgParentX = vgCreateImage(VG_sRGBA_8888, 128, 2, VG_IMAGE_QUALITY_NONANTIALIASED);
        VGImage vgParentY = vgCreateImage(VG_sRGBA_8888, 2, 128, VG_IMAGE_QUALITY_NONANTIALIASED);

        vgDstImageX = vgChildImage(vgParentX, 8, 0, 32, 1);
        vgDstImageY = vgChildImage(vgParentY, 0, 8, 1, 32);
        vgSrcImageX = vgChildImage(vgParentX, 80, 0, 47, 1);
        vgSrcImageY = vgChildImage(vgParentY, 0, 80, 1, 47);

        vgDestroyImage(vgParentX);
        vgDestroyImage(vgParentY);
    }

    /* Initialize the source image pixels. */
    {
        VGfloat bgColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        VGfloat fgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        vgSetfv(VG_CLEAR_COLOR, 4, bgColor);
        vgClearImage(vgSrcImageX, 0, 0, 47, 1);
        vgClearImage(vgSrcImageY, 0, 0, 1, 47);

        vgSetfv(VG_CLEAR_COLOR, 4, fgColor);
        vgClearImage(vgSrcImageX, 19, 0, 1, 1);
        vgClearImage(vgSrcImageY, 0, 19, 1, 1);
    }

    /* Clear the background and set the tile fill color. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        VGfloat tileFillColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
        vgSetfv(VG_TILE_FILL_COLOR, 4, tileFillColor);
    }

    /* Loop over the shift counts. */

    for (i = 0; i < 32; i++)
    {
        static const VGshort blurKernel[] = { 1, 6, 15, 20, 15, 6, 1 };
        VGshort identKernel = 1;
        VGfloat scale = 1.0f / 20.0f;
        VGfloat bias = 1.0f - 64.0f / 20.0f;
        int shift = (i < 16) ? (-1 << (15 - i)) : (1 << (i - 16));

        /* Run vgConvolve() with horizontal/vertical shift. */

        vgConvolve(vgDstImageX, vgSrcImageX, 7, 1, shift, 0,
            blurKernel, scale, bias, tilingMode);

        vgConvolve(vgDstImageY, vgSrcImageY, 1, 7, 0, shift,
            blurKernel, scale, bias, tilingMode);

        /* Copy the resulting images to the screen. */

        vgSetPixels(0, i, vgDstImageX, 0, 0, 32, 1);
        vgSetPixels(32 + i, 0, vgDstImageY, 0, 0, 1, 32);

        /* Run vgSeparableConvolve() with horizontal/vertical shift. */

        vgSeparableConvolve(vgDstImageX, vgSrcImageX, 7, 1, shift, 0,
            blurKernel, &identKernel, scale, bias, tilingMode);

        vgSeparableConvolve(vgDstImageY, vgSrcImageY, 1, 7, 0, shift,
            &identKernel, blurKernel, scale, bias, tilingMode);

        /* Copy the resulting images to the screen. */

        vgSetPixels(0, 32 + i, vgDstImageX, 0, 0, 32, 1);
        vgSetPixels(32 + i, 32, vgDstImageY, 0, 0, 1, 32);
    }

    /* Clean up and save the result. */

    if (vgDstImageX != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImageX);
    if (vgDstImageY != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImageY);
    if (vgSrcImageX != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImageX);
    if (vgSrcImageY != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImageY);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

