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
 * K20401_Blending_by_NVIDIA
 *
 * Tests the blending modes work as expected on different
 * source alpha formats, with and without a stencil.
 *
 * The test consists of 10 subtests, one for each blending
 * mode. The subtests are organized as follows:
 *
 * 0000: VG_BLEND_SRC
 * 0001: VG_BLEND_SRC_OVER
 * 0002: VG_BLEND_DST_OVER
 * 0003: VG_BLEND_SRC_IN
 * 0004: VG_BLEND_DST_IN
 * 0005: VG_BLEND_MULTIPLY
 * 0006: VG_BLEND_SCREEN
 * 0007: VG_BLEND_DARKEN
 * 0008: VG_BLEND_LIGHTEN
 * 0009: VG_BLEND_ADDITIVE
 *
 * Each subtest renders a 2x2 grid of test cases. Each test case
 * initializes its background to a horizontal color gradient with
 * a monotonically increasing alpha. It then draws a pattern paint
 * containing a similar vertical color gradient, combined with an
 * image of constant color. The image format, image mode, and
 * constant color are chosen depending on the test case:
 *
 * Bottom left:  VG_sRGBA_8888, multiply with an opaque white.
 * Bottom right: VG_sRGBA_8888, stencil through an opaque red.
 * Top left:     VG_sRGBA_8888, stencil through an opaque green.
 * Top right:    VG_sRGBA_8888_PRE, stencil through an opaque blue.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20401_Blending_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGBlendMode blendModes[] =
    {
        VG_BLEND_SRC,
        VG_BLEND_SRC_OVER,
        VG_BLEND_DST_OVER,
        VG_BLEND_SRC_IN,
        VG_BLEND_DST_IN,
        VG_BLEND_MULTIPLY,
        VG_BLEND_SCREEN,
        VG_BLEND_DARKEN,
        VG_BLEND_LIGHTEN,
        VG_BLEND_ADDITIVE
    };

    static const struct
    {
        VGImageFormat   imageFormat;
        VGImageMode     imageMode;
        VGfloat         imageColor[4];
    } testCases[] =
    {
        { VG_sRGBA_8888,        VG_DRAW_IMAGE_MULTIPLY, { 1.0f, 1.0f, 1.0f, 1.0f } },
        { VG_sRGBA_8888,        VG_DRAW_IMAGE_STENCIL,  { 1.0f, 0.0f, 0.0f, 1.0f } },
        { VG_sRGBA_8888,        VG_DRAW_IMAGE_STENCIL,  { 0.0f, 1.0f, 0.0f, 1.0f } },
        { VG_sRGBA_8888_PRE,    VG_DRAW_IMAGE_STENCIL,  { 0.0f, 0.0f, 1.0f, 1.0f } },
    };

    VGBlendMode     blendMode = blendModes[subtest];
    int             itemSize = 32;
    VGuint          gradient[32];
    int             i, j;

    /* Calculate the gradient colors. */

    for (i = 0; i < itemSize; i++)
    {
        VGfloat hue     = (VGfloat)i * 6.0f / (VGfloat)itemSize;
        int     hueIdx  = (int)hue;
        int     hueLerp = (int)((hue - (VGfloat)hueIdx) * 255);

        gradient[i] = 64 + i * 255 / (itemSize - 1);
        if (gradient[i] > 255)
            gradient[i] = 255;

        for (j = 0; j < 3; j++)
            gradient[i] += ((((hueIdx + 7 - j * 2) % 6 < 3) ? 255 - hueLerp : 0) +
                           (((hueIdx + 8 - j * 2) % 6 < 3) ? hueLerp : 0)) << (24 - j * 8);
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, blendMode);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    /* Loop over test cases. */

    for (i = 0; i < (int)(sizeof(testCases) / sizeof(testCases[0])); i++)
    {
        int x = (i & 1) * itemSize;
        int y = (i >> 1) * itemSize;
        VGImage vgConstantImage;
        VGImage vgGradientImage;
        VGPaint vgPatternPaint;

        /* Create the constant color image. */

        vgConstantImage = vgCreateImage(testCases[i].imageFormat, itemSize, itemSize, VG_IMAGE_QUALITY_NONANTIALIASED);
        vgSetfv(VG_CLEAR_COLOR, 4, testCases[i].imageColor);
        vgClearImage(vgConstantImage, 0, 0, itemSize, itemSize);

        /* Create the gradient image. */

        vgGradientImage = vgCreateImage(testCases[i].imageFormat, itemSize, itemSize, VG_IMAGE_QUALITY_NONANTIALIASED);
        vgImageSubData(vgGradientImage, gradient, 0, VG_lRGBA_8888, 0, 0, itemSize, itemSize);

        /* Create the pattern paint. */

        vgPatternPaint = vgCreatePaint();
        vgSetParameteri(vgPatternPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
        vgPaintPattern(vgPatternPaint, vgGradientImage);
        vgSetPaint(vgPatternPaint, VG_FILL_PATH);

        /* Draw the test case. */

        vgLoadIdentity();
        vgTranslate((VGfloat)(x + itemSize), (VGfloat)y);
        vgRotate(90.0f);
        vgWritePixels(gradient, 0, VG_lRGBA_8888, x, y, itemSize, itemSize);
        vgSeti(VG_IMAGE_MODE, testCases[i].imageMode);
        vgDrawImage(vgConstantImage);
    
        /* Clean up. */

        vgDestroyImage(vgGradientImage);
        vgDestroyImage(vgConstantImage);
        vgDestroyPaint(vgPatternPaint);
    }

    /* Clean up and save the result. */

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

