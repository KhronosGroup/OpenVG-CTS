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
 * K20202_ColorTransform_by_NVIDIA
 *
 * Tests the color transformation corner cases. The test renders
 * 64 columns of size 1x64 separately to compose the final image.
 * Each column is filled with a linear gradient that is transformed
 * so that the color values independently clamp to either 0.0 or
 * 1.0 on each pixel.
 *
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20202_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGPath vgColumnPath;
    VGPaint vgGradientPaint;
    int i;

    /* Create a 1x64 column rectangle path. */
    {
        static const VGubyte columnCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat columnVal[] =
        { 1.0f, 64.0f, 0.0f };

        vgColumnPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgColumnPath, sizeof(columnCmd), columnCmd, columnVal);
    }

    /* Create a vertical linear gradient paint. */
    {
        static const VGfloat coords[] =
        { 0.0f, 0.0f, 0.0f, 64.0f };

        vgGradientPaint = vgCreatePaint();
        vgSetParameteri(vgGradientPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
        vgSetParameterfv(vgGradientPaint, VG_PAINT_LINEAR_GRADIENT, 4, coords);
        vgSetPaint(vgGradientPaint, VG_FILL_PATH);
    }

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();

    /* Loop over the columns. */

    for (i = 0; i < 64; i++)
    {
        const VGfloat* stops;
        VGfloat values[8];
        int j;

        /* Select the gradient stop colors. */

        {
            static const VGfloat stopSet[][10] =
            {
                { 0.0f, 0.0f,  0.0f,  0.0f,  0.35f,     1.0f, 1.0f,  1.0f,  1.0f,  0.65f },
                { 0.0f, 0.0f,  0.0f,  0.0f,  0.65f,     1.0f, 1.0f,  1.0f,  1.0f,  0.35f },
                { 0.0f, 1.0f,  1.0f,  1.0f,  1.0f,      1.0f, 0.0f,  0.0f,  0.0f,  0.5f },
                { 0.0f, 1.0f,  1.0f,  1.0f,  0.4f,      1.0f, 0.0f,  0.0f,  0.0f,  1.0f },
                { 0.0f, 0.25f, 0.25f, 0.25f, 0.4f,      1.0f, 0.75f, 0.75f, 0.75f, 1.0f },
            };

            stops = stopSet[i % (sizeof(stopSet) / sizeof(stopSet[0]))];
        }

        /* Select the per-channel coefficients. */
        {
            static const VGfloat scaleSet[] =
            { 63.0f, 65.0f, 12345.0f, 123456.0f, 1234567.0f, 12345678.0f, 123456789.0f };

            VGfloat scale = scaleSet[i % (sizeof(scaleSet) / sizeof(scaleSet[0]))];
            for (j = 0; j < 4; j++)
                values[j] = scale / (stops[j + 6] - stops[j + 1]);
        }

        /* Select the bias so that the cutoff happens at the desired point. */

        for (j = 0; j < 4; j++)
        {
            VGfloat colorA  = stops[j + 1];
            VGfloat colorB  = stops[j + 6];
            VGfloat alphaA  = (j == 3) ? 1.0f : stops[4];
            VGfloat alphaB  = (j == 3) ? 1.0f : stops[9];
            VGfloat cutoff  = ((VGfloat)((i - 16) * 2 + 24 - j * 16) + 0.5f) / 64.0f;
            VGfloat colorC  = colorA * alphaA * (1.0f - cutoff) + colorB * alphaB * cutoff;
            VGfloat alphaC  = alphaA * (1.0f - cutoff) + alphaB * cutoff;
            VGfloat bias    = 0.5f - (colorC / alphaC) * values[j];
            VGfloat maxBias = 2147483647.0f;
            values[j + 4]   = (bias < -maxBias) ? -maxBias : (bias > maxBias) ? maxBias : bias;
        }

        /* Draw the column. */

        vgSetParameterfv(vgGradientPaint, VG_PAINT_COLOR_RAMP_STOPS, 10, stops);
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgDrawPath(vgColumnPath, VG_FILL_PATH);
        vgTranslate(1.0f, 0.0f);
    }

    /* Clean up and save the result. */

    if (vgColumnPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgColumnPath);
    if (vgGradientPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgGradientPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

