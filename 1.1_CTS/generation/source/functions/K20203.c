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
 * K20203_ColorTransform_by_NVIDIA
 *
 * Tests that the color transformation works as expected on
 * all relevant combinations of
 * path/image x image format x paint type x image mode.
 *
 * The test consists of 16 subtests, organized as follows:
 *
 * 0000: No image, solid color paint
 * 0001: No image, radial gradient paint
 * 0002: No image, patten paint VG_sRGBA_8888_PRE
 * 0003: No image, patten paint VG_lRGBA_8888
 * 0004: No image, patten paint VG_sL_8
 * 0005: No image, patten paint VG_A_8
 * 0006: VG_DRAW_IMAGE_NORMAL, solid color paint
 * 0007: VG_DRAW_IMAGE_NORMAL, radial gradient paint
 * 0008: VG_DRAW_IMAGE_NORMAL, patten paint VG_sRGBA_8888_PRE
 * 0009: VG_DRAW_IMAGE_NORMAL, patten paint VG_lRGBA_8888
 * 0010: VG_DRAW_IMAGE_NORMAL, patten paint VG_sL_8
 * 0011: VG_DRAW_IMAGE_NORMAL, patten paint VG_A_8
 * 0012: VG_DRAW_IMAGE_MULTIPLY, solid color paint
 * 0013: VG_DRAW_IMAGE_MULTIPLY, radial gradient paint
 * 0014: VG_DRAW_IMAGE_MULTIPLY, patten paint VG_sRGBA_8888_PRE
 * 0015: VG_DRAW_IMAGE_MULTIPLY, patten paint VG_lRGBA_8888
 * 0016: VG_DRAW_IMAGE_MULTIPLY, patten paint VG_sL_8
 * 0017: VG_DRAW_IMAGE_MULTIPLY, patten paint VG_A_8
 * 0018: VG_DRAW_IMAGE_STENCIL, solid color paint
 * 0019: VG_DRAW_IMAGE_STENCIL, radial gradient paint
 * 0020: VG_DRAW_IMAGE_STENCIL, patten paint VG_sRGBA_8888_PRE
 * 0021: VG_DRAW_IMAGE_STENCIL, patten paint VG_lRGBA_8888
 * 0022: VG_DRAW_IMAGE_STENCIL, patten paint VG_sL_8
 * 0023: VG_DRAW_IMAGE_STENCIL, patten paint VG_A_8
 *
 * Each subtest renders a 4x4 grid of image formats. The
 * elements of the grid contain a rectangular path or image,
 * filled or modulated with the paint defined by the subtest
 * index. The resulting colors are transformed with a constant
 * color transformation.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20203_ColorTransform_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGint imageModes[] =
    {
        0,
        VG_DRAW_IMAGE_NORMAL,
        VG_DRAW_IMAGE_MULTIPLY,
        VG_DRAW_IMAGE_STENCIL
    };

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

    int     itemW       = 16;
    int     itemH       = 16;
    int     numPerRow   = 4;
    int     paintType   = subtest % 6;
    VGint   imageMode   = imageModes[subtest / 6];
    VGPath  vgRectPath;
    VGPaint vgPaint;
    VGuint* buffer;
    int     i;

    /* Allocate the pixel buffer. */

    buffer = MALLOC(itemW * itemH * sizeof(VGuint));
    if (!buffer)
        return CT_ERROR;

    /* Initialize the pixel buffer contents. */
    {
        int x, y, idx = 0;
        for (y = 0; y < itemH; y++)
        {
            int yy = y * 255 / (itemH - 1);
            for (x = 0; x < itemW; x++)
            {
                int xx = x * 255 / (itemW - 1);
                buffer[idx] =
                    0x01000000 * xx +
                    0x00010000 * (255 - xx) +
                    0x00000100 * yy +
                    0x00000001 * (255 - yy / 3);
                idx++;
            }
        }
    }

    /* Create a rectangle path. */
    {
        static const VGubyte rectCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat rectVal[] =
        { 16.0f, 16.0f, 0.0f };

        vgRectPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgRectPath, sizeof(rectCmd), rectCmd, rectVal);
    }

    /* Create a paint. */

    vgPaint = vgCreatePaint();
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Set the paint type depending on the subtest. */
    {
        VGint patternFormat = 0;

        switch (paintType)
        {
        case 0:
            /* Solid color, transformed to semi-transparent purple. */
            {
                vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
                vgSetColor(vgPaint, 0xffb0a090);
            }
            break;

    
        case 1: 
            /* Linear gradient.
             * The transformed interior color is semi-transparent green.
             * The transformed exterior color is opaque red. */
            {
                static const VGfloat coords[] =
                { 8.0f, 8.0f, 8.0f, 8.0f, 10.0f };
                static const VGfloat stops[10] =
                { 0.0f, 0.25f, 0.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.75f, 0.0f, 1.0f };

                vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_RADIAL_GRADIENT);
                vgSetParameterfv(vgPaint, VG_PAINT_RADIAL_GRADIENT, 5, coords);
                vgSetParameterfv(vgPaint, VG_PAINT_COLOR_RAMP_STOPS, 10, stops);
            }
            break;

        case 2:
            patternFormat = VG_sRGBA_8888_PRE;
            break;

        case 3:
            patternFormat = VG_lRGBA_8888;
            break;

        case 4:
            patternFormat = VG_sL_8;
            break;

        case 5:
            patternFormat = VG_A_8;
            break;
        }

        /* Setup pattern paint if needed. */

        if (patternFormat)
        {
            VGImage vgImage = vgCreateImage(patternFormat, itemW, itemH,
                VG_IMAGE_QUALITY_NONANTIALIASED);
            vgImageSubData(vgImage, buffer, itemW * sizeof(VGuint),
                VG_sRGBA_8888, 0, 0, itemW, itemH);

            vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
            vgPaintPattern(vgPaint, vgImage);
            vgDestroyImage(vgImage);
        }
    }

    /* Clear the background to semi-transparent white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 0.75f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */
    {
        static const VGfloat colorTransform[] =
        { 2.0f, -2.0f, 0.5f, 0.9f, -0.5f, 1.0f, 0.25f, 0.21f };

        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
        vgSeti(VG_BLEND_MODE, (imageMode == VG_DRAW_IMAGE_STENCIL) ? VG_BLEND_SRC_OVER : VG_BLEND_SRC);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, colorTransform);

        vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
        vgLoadIdentity();
        vgTranslate((VGfloat)itemW, 0.0f);
        vgRotate(90.0f);

        if (!imageMode)
            vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        else
        {
            vgSeti(VG_IMAGE_MODE, imageMode);
            vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
        }
    }

    /* Loop over image formats. */

    for (i = 0; i < (int)(sizeof(imageFormats) / sizeof(imageFormats[0])); i++)
    {
        /* Setup the transformation matrix. */

        vgLoadIdentity();
        vgTranslate(
            (VGfloat)((i % numPerRow) * itemW),
            (VGfloat)((i / numPerRow) * itemH));

        /* Image disabled -> draw the path. */

        if (!imageMode)
            vgDrawPath(vgRectPath, VG_FILL_PATH);

        /* Image enabled -> create and draw it. */

        else
        {
            VGImage vgImage = vgCreateImage(imageFormats[i], itemW, itemH,
                VG_IMAGE_QUALITY_NONANTIALIASED);
            vgImageSubData(vgImage, buffer, itemW * sizeof(VGuint),
                VG_sRGBA_8888, 0, 0, itemW, itemH);
            vgDrawImage(vgImage);
            vgDestroyImage(vgImage);
        }
    }

    /* Clean up and save the result. */

    FREE(buffer);
    if (vgRectPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgRectPath);
    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

