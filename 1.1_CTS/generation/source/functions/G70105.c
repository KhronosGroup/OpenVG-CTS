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
 * G70105_PathBounds_by_NVIDIA
 *
 * Ensures that vgPathBounds() and vgTransformedPathBounds()
 * return correct and consistent results for a number of paths.
 *
 * The test consists of 4 subtests, organized as follows:
 *
 * 0000: Cubic.
 * 0001: Arc.
 * 0002: Nearly symmetrical cubic.
 * 0003: Very thin arc.
 *
 * The subtests sweep through the columns of the resulting image,
 * rendering each column separately. The coordinates of the path
 * are adjusted on the fly, so that an X coordinate in the
 * resulting image corresponds to the horizontal position, and
 * also to the adjustment phase.
 *
 * On each column, a subtest does three things. First, it calls
 * vgPathTransformedBounds() with an arbitrary transformation matrix.
 * It compares the rectangle to the one produced by vgTransformPath()
 * -> vgPathBounds() to ensure that the former one is never smaller
 * than the latter one.
 *
 * Second, it renders a stroked rectangle corresponding to the
 * values returned by vgPathBounds() for the original path. The
 * color of the rectangle is determined by the consistency check
 * described above: red = good, cyan = bad.
 *
 * Third, it draws the original path with a black stroke.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70105_PathBounds_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    int     numSteps  = 64;
    VGfloat tolerance = 0.1f;
    VGPaint vgPaint;
    int     i;

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_STROKE_PATH);

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
    vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSetf(VG_STROKE_MITER_LIMIT, 4.0f);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Loop over animation steps. */

    for (i = 0; i < numSteps; i++)
    {
        VGfloat     phase = i / (numSteps - 1.0f);
        VGPath      vgCurvePath = VG_INVALID_HANDLE;
        VGPath      vgXformPath;
        VGPath      vgBoundPath;
        VGboolean   xformOk;

        /* Create the curve path. */

        switch (subtest)
        {
            /* Subtest 0: Cubic.
             * DATATYPE_S_16, scale = 0.1f, bias = 10.0f */
        case 0:

            {
                static const VGubyte curveCmd[] =
                { VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS };

                VGshort curveVal[] =
                {
                    -410, -320,
                    -410, 240, 210, 240, 210, -220
                };

                curveVal[1] = (VGshort)(-320.0f + phase * 200.0f);
                curveVal[5] = (VGshort)(240.0f - phase * 400.0f);

                vgCurvePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_16,
                    0.1f, 10.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
                vgAppendPathData(vgCurvePath, sizeof(curveCmd), curveCmd, curveVal);
            }
            break;

            /* Subtest 1: Arc.
             * DATATYPE_S_8, scale = -0.5f, bias = 0.0f */
        case 1:
            {
                static const VGubyte curveCmd[] =
                { VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS };

                VGbyte curveVal[] =
                {
                    62, 44,
                    -62, -84, 0, -62, 24
                };

                curveVal[0] = (VGbyte)(62.0f - phase * 40.0f);
                curveVal[1] = (VGbyte)(44.0f - phase * 40.0f);
                curveVal[6] = (VGbyte)(24.0f - phase * 60.0f);

                vgCurvePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_8,
                    -0.5f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
                vgAppendPathData(vgCurvePath, sizeof(curveCmd), curveCmd, curveVal);
            }
            break;

            /* Subtest 2: Nearly symmetrical cubic.
             * DATATYPE_F, scale = 1.0f, bias = 0.0f */
        case 2:
            {
                static const VGubyte curveCmd[] =
                { VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS };

                VGfloat curveVal[] =
                {
                    -31.0f, -22.0f,
                    -31.0f, 34.0f, 31.0f, 34.0f, 31.0f, -22.0f
                };

                curveVal[3] = 34.00001f - phase * 0.00005f;

                vgCurvePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                    1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
                vgAppendPathData(vgCurvePath, sizeof(curveCmd), curveCmd, curveVal);
            }
            break;

            /* Subtest 3: Very thin arc.
             * DATATYPE_F, scale = 1.0f, bias = 0.0f */
        case 3:
            {
                static const VGubyte curveCmd[] =
                { VG_MOVE_TO_ABS, VG_SCWARC_TO_REL, VG_LINE_TO_ABS };

                VGfloat curveVal[] =
                {
                    -31.0f, -22.0f,
                    1.0f, 42.0f, 0.0f, 2.0f, 0.0f,
                    31.0f, -22.0f
                };

                curveVal[2] = 0.000010f - phase * 0.000009f;
                curveVal[5] = curveVal[2] * 2.0f;

                vgCurvePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                    1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
                vgAppendPathData(vgCurvePath, sizeof(curveCmd), curveCmd, curveVal);
            }
            break;
        }

        /* Create the bound path. */
        {
            static const VGubyte boundCmd[] =
            { VG_MOVE_TO_ABS, VG_HLINE_TO_REL, VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_CLOSE_PATH };

            VGfloat minX, minY, width, height;
            VGfloat boundVal[5];

            vgPathBounds(vgCurvePath, &minX, &minY, &width, &height);
            boundVal[0] = minX;
            boundVal[1] = minY;
            boundVal[2] = width;
            boundVal[3] = height;
            boundVal[4] = -width;

            vgBoundPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgBoundPath, sizeof(boundCmd), boundCmd, boundVal);
        }

        /* Setup an arbitrary transformation. */

        vgLoadIdentity();
        vgTranslate(1.23f * i - 2.34f, 3.45f - 5.67f * i);
        vgRotate(6.78f * i);
        vgScale(7.89f * i - 8.90f, 0.12f - 9.01f * i);

        /* Transform the curve. */

        vgXformPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        vgTransformPath(vgXformPath, vgCurvePath);

        /* Check that vgPathBounds and vgPathTransformedBounds produce consistent results. */
        {
            VGfloat pbMinX, pbMinY, pbWidth, pbHeight;
            VGfloat tbMinX, tbMinY, tbWidth, tbHeight;
        
            vgPathBounds(vgXformPath, &pbMinX, &pbMinY, &pbWidth, &pbHeight);
            vgPathTransformedBounds(vgCurvePath, &tbMinX, &tbMinY, &tbWidth, &tbHeight);

            xformOk = (
                tbMinX <= pbMinX + tolerance &&
                tbMinY <= pbMinY + tolerance &&
                tbMinX + tbWidth >= pbMinX + pbWidth - tolerance &&
                tbMinY + tbHeight >= pbMinY + pbHeight - tolerance);

            if (subtest == 3)
                xformOk = VG_TRUE;
        }

        /* Set scissor for the column corresponding to the step. */
        {
            VGint scissor[] = { 0, 0, 1, 64 };
            scissor[0] = i;
            vgSeti(VG_SCISSORING, VG_TRUE);
            vgSetiv(VG_SCISSOR_RECTS, 4, scissor);
        }

        /* Draw the bounds (red or cyan) and the curve (black). */

        vgLoadIdentity();
        vgTranslate(32.0f, 32.0f);
        vgSetColor(vgPaint, (xformOk) ? 0xff0000ff : 0x00ffffff);
        vgDrawPath(vgBoundPath, VG_STROKE_PATH);
        vgSetColor(vgPaint, 0x000000ff);
        vgDrawPath(vgCurvePath, VG_STROKE_PATH);

        /* Clean up. */

        vgDestroyPath(vgCurvePath);
        vgDestroyPath(vgXformPath);
        vgDestroyPath(vgBoundPath);
    }

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

