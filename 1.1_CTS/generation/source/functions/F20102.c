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
 * F20102_Masking_by_NVIDIA
 *
 * Tests the mask operations on semi-transparent masks. Each of the
 * six subtests covers a single mask operation as follows:
 *
 * 0000: VG_CLEAR_MASK
 * 0001: VG_FILL_MASK
 * 0002: VG_SET_MASK
 * 0003: VG_UNION_MASK
 * 0004: VG_INTERSECT_MASK
 * 0005: VG_SUBTRACT_MASK
 *
 * The test sets up two mask layers, containing a horizontal and a
 * vertical coverage gradient. The gradients are formed by filling a
 * 32x1 path that consists of tiny rectangles covering a portion of
 * each pixel. The covered portion increases with the X coordinate,
 * from fully uncovered to fully covered.
 *
 * The resulting 64x64 image is divided into four quadrants:
 *
 * Bottom left:
 * Contents of the horizontal gradient mask.
 *
 * Bottom right:
 * Contents of the vertical gradient mask.
 *
 * Top left:
 * Result of compositing the vertical gradient mask top of the horizontal
 * one, using vgMask() with the given mask operation.
 *
 * Top right:
 * Identical to the top left quadrant, but the composition is done by
 * rendering the path using vgRenderToMask().
 *
 * Since OpenVG implementations can freely choose the color space
 * in which the coverage values applied, the test compensates for
 * the differences by normalizing the resulting image. This is done
 * by determining the appropriate color-to-coverage mapping based
 * on the bottom left quadrant, and applying the same mapping to the
 * rest of the pixels.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20102_Masking_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    VGMaskOperation vgMaskOp = (VGMaskOperation)(VG_CLEAR_MASK + subtest);
    VGMaskLayer     vgHorizontalMask;
    VGMaskLayer     vgVerticalMask;
    VGMaskLayer     vgResultMask;
    VGPath          vgDitheredPath;
    int             i;

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Create the mask layers.
     * If no surface mask is present, just exit. */

    vgHorizontalMask = vgCreateMaskLayer(32, 32);
    if (vgHorizontalMask == VG_INVALID_HANDLE)
    {
        if (vgGetError() != VG_NO_ERROR)
            return CT_ERROR;
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }

    vgVerticalMask = vgCreateMaskLayer(32, 32);
    vgResultMask = vgCreateMaskLayer(WINDSIZEX, WINDSIZEY);

    /* Create a 32x1 horizontal dithered path.
     * The path covers the portion x/31 of each pixel rectangle. */

    vgDitheredPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
        1.0f / 4.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

    for (i = 1; i <= 33; i++)
    {
        static const VGubyte ditherPattern[] =
        {
            0,  8,  2,  10,
            12, 4,  14, 6,
            3,  11, 1,  9,
            15, 7,  13, 5
        };

        VGubyte cmd[20];
        VGint val[25];
        int j;

        for (j = 0; j < 16; j++)
        {
            int cmdIdx = 0;
            int valIdx = 0;
            int k;

            if (ditherPattern[j] * 2 >= i)
                continue;

            for (k = -2; k <= 2; k++)
            {
                cmd[cmdIdx++] = VG_MOVE_TO_ABS;
                val[valIdx++] = i * 4 + j % 4;
                val[valIdx++] = k * 4 + j / 4;

                cmd[cmdIdx++] = VG_HLINE_TO_REL;
                val[valIdx++] = 1;

                cmd[cmdIdx++] = VG_VLINE_TO_REL;
                val[valIdx++] = 1;

                cmd[cmdIdx++] = VG_HLINE_TO_REL;
                val[valIdx++] = -1;
            }

            vgAppendPathData(vgDitheredPath, cmdIdx, cmd, val);
        }
    }

    /* Setup the horizontal mask. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgRenderToMask(vgDitheredPath, VG_FILL_PATH, VG_SET_MASK);

    for (i = 0; i < 32; i++)
        vgCopyMask(vgHorizontalMask, 0, i, 0, 0, 32, 1);

    /* Setup the vertical mask. */

    vgRotate(90.0f);
    vgRenderToMask(vgDitheredPath, VG_FILL_PATH, VG_SET_MASK);

    for (i = 0; i < 32; i++)
        vgCopyMask(vgVerticalMask, i, 0, 0, 0, 1, 32);

    /* Bottom left quadrant:
     * Contents of the horizontal mask. */

    vgMask(vgHorizontalMask, VG_SET_MASK, 0, 0, 32, 32);
    vgCopyMask(vgResultMask, 0, 0, 0, 0, 32, 32);

    /* Bottom right quadrant:
     * Contents of the vertical mask. */

    vgMask(vgVerticalMask, VG_SET_MASK, 32, 0, 32, 32);
    vgCopyMask(vgResultMask, 32, 0, 32, 0, 32, 32);

    /* Top left quadrant:
     * Vertical mask composited on top of horizontal mask. */

    vgMask(vgHorizontalMask, VG_SET_MASK, 0, 32, 32, 32);
    vgMask(vgVerticalMask, vgMaskOp, 0, 32, 32, 32);
    vgCopyMask(vgResultMask, 0, 32, 0, 32, 32, 32);

    /* Top left quadrant:
     * Vertical dithered path composited on top of horizontal mask. */

    vgTranslate(32.0f, -32.0f);
    for (i = 0; i < 32; i++)
    {
        vgMask(vgHorizontalMask, VG_SET_MASK, 32, 32, 32, 32);
        vgRenderToMask(vgDitheredPath, VG_FILL_PATH, vgMaskOp);
        vgCopyMask(vgResultMask, i + 32, 32, i + 32, 32, 1, 32);
        vgTranslate(0.0f, -1.0f);
    }

    /* Use the result mask as the surface mask. */

    vgMask(vgResultMask, VG_SET_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

    /* Destroy the objects. */

    vgDestroyMaskLayer(vgHorizontalMask);
    vgDestroyMaskLayer(vgVerticalMask);
    vgDestroyMaskLayer(vgResultMask);
    vgDestroyPath(vgDitheredPath);

    /* Draw a solid white rectangle through the surface mask. */
    {
        static const VGubyte rectCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat rectVal[] =
        { (VGfloat)WINDSIZEX, (VGfloat)WINDSIZEY, 0.0f };

        VGPath vgPath;
        VGPaint vgPaint;

        /* Create a path covering the whole window. */

        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(rectCmd), rectCmd, rectVal);

        /* Create a solid white paint. */

        vgPaint = vgCreatePaint();
        vgSetColor(vgPaint, 0xffffffff);

        /* Draw the path through the mask. */

        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        vgLoadIdentity();
        vgSetPaint(vgPaint, VG_FILL_PATH);
        vgSeti(VG_MASKING, VG_TRUE);
        vgDrawPath(vgPath, VG_FILL_PATH);
        vgSeti(VG_MASKING, VG_FALSE);

        /* Clean up. */

        vgDestroyPath(vgPath);
        vgDestroyPaint(vgPaint);
    }

    /* Process the resulting pixels to account for implementation specific
     * differences in the colorspace in which coverage values are processed. */
    {
        int         numPixels = WINDSIZEX * WINDSIZEY;
        VGubyte*    pixels;
        VGubyte     mapping[256];

        pixels = MALLOC(numPixels * sizeof(VGubyte));
        if (!pixels)
            return CT_ERROR;

        /* Read the surface pixels. */

        vgReadPixels(pixels, WINDSIZEX * sizeof(VGubyte),
            VG_lL_8, 0, 0, WINDSIZEX, WINDSIZEY);

        /* Determine the color-to-coverage mapping function based on
         * the first scanline of the bottom left quadrant. */
        {
            int prevColor = 0;
            int prevCover = 0;
            mapping[0] = 0;

            for (i = 1; i < 32; i++)
            {
                int currColor = pixels[i];
                int currCover = (i * 0x21) >> 2;
                int diffColor = currColor - prevColor;
                int j;

                if (i == 31)
                    currColor = 255;
                if (currColor == 255)
                    currCover = 255;

                for (j = prevColor + 1; j <= currColor; j++)
                {
                    int tmp = (currCover - prevCover) * (j - prevColor);
                    mapping[j] = (VGubyte)(prevCover + (tmp + diffColor / 2) / diffColor);
                }

                if (currColor > prevColor)
                {
                    prevColor = currColor;
                    prevCover = currCover;
                }
            }
        }

        /* Lookup the coverage of each pixel using the mapping function. */

        for (i = 0; i < numPixels; i++)
            pixels[i] = mapping[pixels[i]];

        /* Draw the coverage values. */

        vgWritePixels(pixels, WINDSIZEX * sizeof(VGubyte),
            VG_lL_8, 0, 0, WINDSIZEX, WINDSIZEY);

        /* Clean up. */

        FREE(pixels);
    }

    /* Check for errors and save the image. */

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

