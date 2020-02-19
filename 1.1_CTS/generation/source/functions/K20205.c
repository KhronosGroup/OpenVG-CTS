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
 * K20205_ColorTransform_by_NVIDIA
 *
 * Tests that possible color transformation special case
 * optimizations work as expected, by varying each set of
 * coefficients and biases while keeping the rest of the
 * parameters at their defaults.
 *
 * The resulting image consists of 64x64 grid of pixels.
 * Each pixel is rendered as a rectangular path filled
 * with a solid color. The magnitude of the color values
 * increases vertically, oversaturating very quickly.
 * The hue of the pixels is dependent on both coordinates.
 *
 * For each color channel of each pixel, the test chooses
 * whether to specify the coefficient and/or bias, or just
 * use the default values. This choice is dependent on the
 * position of the pixel so that all of the 256 different
 * combinations are covered 16 times.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20205_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGPath vgPixelPath;
    VGPaint vgPaint;
    int y, x;

    /* Create a 1x1 rectangle path covering a single pixel. */
    {
        static const VGubyte pixelCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat pixelVal[] =
        { 1.0f, 1.0f, 0.0f };

        vgPixelPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPixelPath, sizeof(pixelCmd), pixelCmd, pixelVal);
    }

    /* Create a solid color paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Clear the background to solid gray. */
    {
        VGfloat clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    for (y = 0; y < WINDSIZEY; y++)
    {
        VGfloat unitY  = (VGfloat)y / (VGfloat)(WINDSIZEY - 1);
        VGfloat bright = EXP(EXP(unitY * 1.75f) - 1.0f) * 0.5f;
        
        for (x = 0; x < WINDSIZEX; x++)
        {
            static const VGint grayCodes[16] =
            {
                0x0000, 0x0001, 0x0011, 0x0010,
                0x0110, 0x0111, 0x0101, 0x0100,
                0x1100, 0x1101, 0x1111, 0x1110,
                0x1010, 0x1011, 0x1001, 0x1000
            };

            VGfloat hue     = 16.0f + (VGfloat)x / 4.0f - (VGfloat)y / 16.0f;
            int     hueIdx  = (int)hue;
            VGfloat hueLerp = hue - (VGfloat)hueIdx;
            VGfloat paintColor[4];
            VGfloat colorTransform[8];
            int     i;

            /* Loop over color channels to determine the paint
             * and color transform for each separately. */

            for (i = 0; i < 4; i++)
            {
                VGfloat lerpA = (VGfloat)((grayCodes[hueIdx & 15] >> (i * 4)) & 1);
                VGfloat lerpB = (VGfloat)((grayCodes[(hueIdx + 1) & 15] >> (i * 4)) & 1);
                VGfloat target = lerpA * (1.0f - hueLerp) + lerpB * hueLerp;
                if (i == 3)
                    target = target * 0.5f + 0.5f;
                target *= bright;

                /* Pick a color transform mode depending on the
                 * current position, and setup the parameters
                 * so that the transformed color value is equal
                 * to 'target'. */

                switch (((x + y * WINDSIZEX) >> (i * 2)) & 3)
                {
                case 0: /* coef = 1, bias = 0 */
                    paintColor[i] = target;
                    colorTransform[i + 0] = 1.0f;
                    colorTransform[i + 4] = 0.0f;
                    break;

                case 1: /* coef = clamped, bias = 0 */
                    paintColor[i] = 1.0f - unitY * 0.5f;
                    colorTransform[i + 0] = target / paintColor[i];
                    colorTransform[i + 4] = 0.0f;
                    break;

                case 2: /* coef = 1, bias = clamped */
                    paintColor[i] = 1.0f - unitY * 0.5f;
                    colorTransform[i + 0] = 1.0f;
                    colorTransform[i + 4] = target - paintColor[i];
                    break;

                case 3: /* coef = nonclamped, bias = clamped */
                    {
                        VGfloat bias = unitY * 4.0f - 2.0f;
                        VGfloat clamped = (bias < -1.0f) ? -1.0f : (bias > 1.0f) ? 1.0f : bias;
                        paintColor[i] = unitY * 0.5f + 0.5f;
                        colorTransform[i + 0] = (target - clamped) / paintColor[i];
                        colorTransform[i + 4] = bias;
                    }
                    break;
                }
            }

            /* Draw the pixel. */

            vgSetParameterfv(vgPaint, VG_PAINT_COLOR, 4, paintColor);
            vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, colorTransform);
            vgLoadIdentity();
            vgTranslate((VGfloat)x, (VGfloat)y);
            vgDrawPath(vgPixelPath, VG_FILL_PATH);
        }
    }

    /* Clean up and save the result. */

    if (vgPixelPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPixelPath);
    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

