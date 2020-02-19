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
 * G70104_PointAlongPath_by_NVIDIA
 *
 * Ensures that vgPointAlongPath() returns the correct
 * results for a number of difficult paths, and that the
 * length computations are consistent with dashing.
 *
 * The test consists of 6 subtests, each operating on
 * distinct path data. The subtests loop over a number
 * of subpaths and distance steps. On each iteration,
 * they render a red circle at the point corresponding
 * to the distance through dashing. They also call
 * vgPointAlongPath() to compute the position and
 * tangent at the point, and render a black line
 * pointing to the direction of the tangent.
 *
 * The subtests are organized as follows:
 *
 * 0000: Two cubics.
 * 0001: Degenerate line -> cubic -> degenerate line.
 * 0002: Move -> cubic -> move.
 * 0003: Two cubics with one control point equal to an end point.
 * 0004: Three cubics with both control points equal to an end point.
 * 0005: Degenerate line, quad, cubic, and arc.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70104_PointAlongPath_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    VGfloat         lengthTolerance = 1.0f; /* pixels */
    VGPaint         vgPaint;
    VGPath          vgMotionPath = VG_INVALID_HANDLE;
    VGPath          vgPointerPath;
    const VGint*    ranges = NULL;
    int             i, j;

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_FILL_PATH | VG_STROKE_PATH);

    /* Create the motion path. */

    switch (subtest)
    {
        /* Subtest 0: Two cubics.
         * DATATYPE_F, scale = 1.0f, bias = 0.0f */
    case 0:
        {
            static const VGubyte motionCmd[] =
            { VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, VG_CUBIC_TO_ABS };

            static const VGfloat motionVal[] =
            {
                10.0f, 10.0f,
                10.0f, 35.0f, 20.0f, 50.0f, 30.0f, 50.0f,
                40.0f, 50.0f, 50.0f, 35.0f, 50.0f, 10.0f
            };

            static const VGint rangeVal[] =
            { 
                1, 1, 4, /* 1st cubic */
                2, 1, 4, /* 2nd cubic */
                1, 2, 6, /* 1st cubic -> 2nd cubic */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;

        /* Subtest 1: Degenerate line -> cubic -> degenerate line.
         * DATATYPE_F, scale = -2.0f, bias = 10.0f */
    case 1:
        {
            static const VGubyte motionCmd[] =
            { VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_CUBIC_TO_REL, VG_LINE_TO_REL };

            static const VGfloat motionVal[] =
            {
                0.0f, 0.0f,
                5.0f, 5.0f,
                5.0f, -20.0f, -15.0f, -20.0f, -15.0f, 5.0f,
                5.0f, 5.0f,
            };

            static const VGint rangeVal[] =
            {
                1, 1, 2, /* 1st line */
                1, 3, 6, /* 1st line -> cubic -> 2nd line */
                3, 1, 2, /* 2nd line */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                -2.0f, 10.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;

        /* Subtest 2: Move -> cubic -> move.
         * DATATYPE_S_8, scale = -2.0f, bias = 10.0f */
    case 2:
        {
            static const VGubyte motionCmd[] =
            { VG_MOVE_TO_ABS, VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_MOVE_TO_ABS };

            static const VGbyte motionVal[] =
            {
                -11, -11,
                0, 0,
                5, -20, -15, -20, -15, 5,
                -11, -11,
            };

            static const VGint rangeVal[] =
            {
                1, 1, 1, /* 1st move */
                1, 3, 6, /* 1st move -> cubic -> 2nd move */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_8,
                -2.0f, 10.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;

        /* Subtest 3: Two cubics with one control point equal to an end point.
         * DATATYPE_S_16, scale = -2.0f, bias = 10.0f */
    case 3:
        {
            static const VGubyte motionCmd[] =
            { VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_CUBIC_TO_REL };

            static const VGshort motionVal[] =
            {
                0, 0,
                5, 5, 5, -15, -5, -15,
                -5, 5, -5, 25, -5, 25
            };

            static const VGint rangeVal[] =
            {
                1, 1, 4, /* 1st cubic */
                2, 1, 4, /* 2nd cubic */
                1, 2, 6, /* 1st cubic -> 2nd cubic */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_16,
                -2.0f, 10.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;

        /* Subtest 4: Three cubics with both control points equal to an end point.
         * DATATYPE_S_32, scale = -1.0f, bias = 10.0f */
    case 4:
        {
            static const VGubyte motionCmd[] =
            {
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL
            };

            static const VGint motionVal[] =
            {
                5, 0, 10, 10, 10, 10, 0, -30,
                -15, 0, 10, 10, 0, -30, 0, -30,
                -35, 0, 0, -30, 0, -30, 0, -30
            };

            static const VGint rangeVal[] =
            {
                1, 1, 4, /* 1st cubic */
                3, 1, 4, /* 2nd cubic */
                5, 1, 4, /* 3rd cubic */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
                -1.0f, 10.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;

        /* Subtest 5: Degenerate line, quad, cubic, and arc.
         * DATATYPE_S_32, scale = 1.0f, bias = 0.0f */
    case 5:
        {
            static const VGubyte motionCmd[] =
            {
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_QUAD_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_CUBIC_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_SCCWARC_TO_REL
            };

            static const VGint motionVal[] =
            {
                15, 31, 0, 2, 0, 0,
                25, 31, 0, 2, 0, 0, 0, 0,
                35, 31, 0, 2, 0, 0, 0, 0, 0, 0,
                45, 31, 0, 2, 10, 10, 0, 0, 0
            };

            static const VGint rangeVal[] =
            {
                2, 1, 2, /* line */
                5, 1, 2, /* quad */
                8, 1, 2, /* cubic */
                11, 1, 2, /* arc */
                -1
            };

            vgMotionPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
                1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            vgAppendPathData(vgMotionPath, sizeof(motionCmd), motionCmd, motionVal);
            ranges = rangeVal;
        }
        break;
    }

    /* Create the pointer path. */
    {
        static const VGubyte pointerCmd[] =
        { VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat pointerVal[] =
        { 0.0f, 1.0f, 8.0f, 1.0f, 8.0f, -1.0f, 0.0f, -1.0f };

        vgPointerPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        vgAppendPathData(vgPointerPath, sizeof(pointerCmd), pointerCmd, pointerVal);
    }

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
    vgSetf(VG_STROKE_LINE_WIDTH, 6.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);
    vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_FALSE);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Loop over the ranges. */

    for (i = 0; ranges[i] != -1; i += 3)
    {
        int     startSeg = ranges[i + 0];
        int     numSegs  = ranges[i + 1];
        int     numSteps = ranges[i + 2];
        VGfloat startLen = (startSeg) ? vgPathLength(vgMotionPath, 0, startSeg) : 0.0f;
        VGfloat length   = vgPathLength(vgMotionPath, startSeg, numSegs);
        VGfloat stepSize;

        if (length > 0.0f && numSteps > 2)
            stepSize = length / (numSteps - 2);
        else
            stepSize = 1.0f;

        /* Loop over steps. */

        for (j = 0; j < numSteps; j++)
        {
            VGfloat distance = (j - 0.5f) * stepSize;
            vgLoadIdentity();

            /* Draw the position (red) through dashing. */
            {
                VGfloat dashPat[2];
                dashPat[0] = 0.0f;
                dashPat[1] = 1024.0f;
                vgSetfv(VG_STROKE_DASH_PATTERN, 2, dashPat);
                vgSetf(VG_STROKE_DASH_PHASE, -(startLen + MIN(MAX(distance, lengthTolerance), length - lengthTolerance)));
                vgSetColor(vgPaint, 0xff0000ff);
                vgDrawPath(vgMotionPath, VG_STROKE_PATH);
            }

            /* Draw the pointer (black) using vgPointAlongPath(). */
            {
                VGfloat posX, posY, tanX, tanY;
                VGfloat xform[9];
                vgPointAlongPath(vgMotionPath, startSeg, numSegs, distance, &posX, &posY, &tanX, &tanY);

                xform[0] = tanX;
                xform[1] = tanY;
                xform[2] = 0.0f;
                xform[3] = -tanY;
                xform[4] = tanX;
                xform[5] = 0.0f;
                xform[6] = posX;
                xform[7] = posY;
                xform[8] = 1.0f;
                vgMultMatrix(xform);
                vgSetColor(vgPaint, 0x000000ff);
                vgDrawPath(vgPointerPath, VG_FILL_PATH);
            }
        }
    }

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgMotionPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgMotionPath);
    if (vgPointerPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPointerPath);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

