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
 * G70103_Clipping_by_NVIDIA
 *
 * Tests that lines extending far beyond the viewport
 * boundaries do not suffer from clipping artifacts.
 *
 * The test consists of 9 subtests, each defining a single
 * center point. The subtests draw a number of stroked radial
 * line segments from and to the center point. Three line
 * segments of varying length are rendered for each angle,
 * and composited together into the color channels of the
 * resulting image through additive blending.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70103_Clipping_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGfloat center[][2] =
    {
        {  0.0f,  0.0f },
        { +1.0f,  0.0f },
        { +1.0f, +1.0f },
        {  0.0f, +1.0f },
        { -1.0f, +1.0f },
        { -1.0f,  0.0f },
        { -1.0f, -1.0f },
        {  0.0f, -1.0f },
        { +1.0f, -1.0f }
    };

    VGfloat distance  = 48.0f;
    VGfloat centerX   = center[subtest][0] * distance + 32.0f;
    VGfloat centerY   = center[subtest][1] * distance + 32.0f;
    int     numAngles = 32;
    VGPaint vgPaint;
    int     i, j;

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_STROKE_PATH);

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
    vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();

    /* Loop of radii. */

    for (i = 0; i < 3; i++)
    {
        static const struct
        {
            VGuint  color;
            VGfloat radius;
        } cases[] =
        {
            { 0x0000ffff, 4096.0f },
            { 0xff0000ff, 512.0f  },
            { 0x00ff00ff, 128.0f   }
        };

        /* Create the path. */

        VGPath vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        /* Append each radial line to the path. */

        for (j = 0; j < numAngles; j++)
        {
            static const VGubyte lineCmd[] =
            {  VG_MOVE_TO_ABS, VG_LINE_TO_ABS };

            VGfloat angle = j * 2.0f * PI / numAngles;
            VGfloat circX = COS(angle) * cases[i].radius + centerX;
            VGfloat circY = SIN(angle) * cases[i].radius + centerY;
            VGfloat lineVal[4];

            /* Even: center -> circumference. */

            if ((j & 1) == 0)
            {
                lineVal[0] = centerX;
                lineVal[1] = centerY;
                lineVal[2] = circX;
                lineVal[3] = circY;
            }

            /* Odd: circumference -> center. */

            else
            {
                lineVal[0] = circX;
                lineVal[1] = circY;
                lineVal[2] = centerX;
                lineVal[3] = centerY;
            }

            vgAppendPathData(vgPath, sizeof(lineCmd), lineCmd, lineVal);
        }

        /* Draw the path. */

        vgSetColor(vgPaint, cases[i].color);
        vgDrawPath(vgPath, VG_STROKE_PATH);

        /* Clean up. */

        vgDestroyPath(vgPath);
}

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

