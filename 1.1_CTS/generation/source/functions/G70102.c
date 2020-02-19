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
 * G70102_Stroking_by_NVIDIA
 *
 * Renders three stroking test images with every cap and
 * join style, and with two different transformations.
 *
 * The test consists of 18 subtests, organized as follows:
 *
 * 0000: Primitives, butt cap, untransformed
 * 0001: Primitives, butt cap, mirrored horizontally
 * 0002: Primitives, round cap, untransformed
 * 0003: Primitives, round cap, mirrored horizontally
 * 0004: Primitives, square cap, untransformed
 * 0005: Primitives, square cap, mirrored horizontally
 * 0006: Circles, butt cap, untransformed
 * 0007: Circles, butt cap, mirrored horizontally
 * 0008: Circles, round cap, untransformed
 * 0009: Circles, round cap, mirrored horizontally
 * 0010: Circles, square cap, untransformed
 * 0011: Circles, square cap, mirrored horizontally
 * 0012: Sharp joins, butt cap, untransformed
 * 0013: Sharp joins, butt cap, mirrored horizontally
 * 0014: Sharp joins, round cap, untransformed
 * 0015: Sharp joins, round cap, mirrored horizontally
 * 0016: Sharp joins, square cap, untransformed
 * 0017: Sharp joins, square cap, mirrored horizontally
 *
 * Each subtest draws the path with every join style, and
 * composites the images into the color channels of the
 * resulting image through additive blending.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70102_Stroking_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    int     xformType = subtest % 2;
    int     capType   = (subtest / 2) % 3;
    int     pathType  = subtest / 6;
    VGPaint vgPaint;
    VGPath  vgPath;
    int     i;

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
    {
        static const VGCapStyle capStyles[] = { VG_CAP_BUTT, VG_CAP_ROUND, VG_CAP_SQUARE };
        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
        vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
        vgSeti(VG_STROKE_CAP_STYLE, capStyles[capType]);
        vgSetf(VG_STROKE_MITER_LIMIT, 4.0f);
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

        vgLoadIdentity();
        if (xformType)
        {
            vgTranslate(64.0f, 0.0f);
            vgScale(-1.0f, 1.0f);
        }
    }

    /* Create the path. */

    vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
        1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

    switch (pathType)
    {
    case 0: /* Points, lines, quads, cubics. */
        {
            static const VGubyte pathCmd[] =
            { 
                VG_MOVE_TO_ABS, VG_MOVE_TO_ABS, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_CLOSE_PATH, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_QUAD_TO_REL,
                VG_MOVE_TO_ABS, VG_QUAD_TO_REL, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_QUAD_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_CUBIC_TO_REL
            };

            static const VGfloat pathVal[] =
            {
                5.0f, 4.0f, 8.0f, 7.0f, 0.0f, 0.0f,
                24.0f, 7.0f,
                3.0f, 18.0f, 5.0f, 9.0f, 5.0f, -9.0f,
                19.0f, 18.0f, 5.0f, 9.0f, 5.0f, -9.0f,
                3.0f, 34.0f, 5.0f, 21.0f, 10.0f, 0.0f,
                19.0f, 34.0f, 5.0f, 21.0f, 10.0f, 0.0f,
                3.0f, 50.0f, 0.0f, 14.0f, 11.0f, 14.0f, 11.0f, 0.0f,
                19.0f, 50.0f, 0.0f, 14.0f, 11.0f, 14.0f, 11.0f, 0.0f,
                35.0f, 3.0f, 21.0f, 9.0f,
                35.0f, 29.0f, 5.0f, -9.0f, 5.0f, 18.0f, 11.0f, 0.0f, 5.0f, 9.0f,
                45.0f, 34.0f, -22.0f, 14.0f, 22.0f, 14.0f, 0.0f, 0.0f,
                37.0f, 50.0f, 0.0f, 0.0f, 20.0f, 22.0f, 20.0f, 0.0f
            };

            vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);
            vgSetf(VG_STROKE_LINE_WIDTH, 4.0f);
        }
        break;

    case 1: /* Closed and unclosed circles. */
        {
            static const VGubyte pathCmd[] =
            { 
                VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL, VG_SCCWARC_TO_REL,
                VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL, VG_SCCWARC_TO_REL, VG_CLOSE_PATH,
                VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL, VG_SCCWARC_TO_REL,
                VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL, VG_SCCWARC_TO_REL, VG_CLOSE_PATH
            };

            static const VGfloat pathVal[] =
            {
                8.0f, 16.0f, 8.0f, 8.0f, 0.0f, 16.0f, 0.0f, 8.0f, 8.0f, 0.0f, -16.0f, 0.0f,
                40.0f, 16.0f, 8.0f, 8.0f, 0.0f, 16.0f, 0.0f, 8.0f, 8.0f, 0.0f, -16.0f, 0.0f,
                12.0f, 48.0f, 4.0f, 4.0f, 0.0f, 8.0f, 0.0f, 4.0f, 4.0f, 0.0f, -8.0f, 0.0f,
                44.0f, 48.0f, 4.0f, 4.0f, 0.0f, 8.0f, 0.0f, 4.0f, 4.0f, 0.0f, -8.0f, 0.0f
            };

            vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);
            vgSetf(VG_STROKE_LINE_WIDTH, 12.0f);
        }
        break;

    case 2: /* Sharp joins. */
        {
            static const VGubyte pathCmd[] =
            { 
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
                VG_MOVE_TO_ABS, VG_LINE_TO_REL, VG_LINE_TO_REL,
            };

            static const VGfloat pathVal[] =
            {
                4.0f,  4.0f, 0.0f, 4.0f, 3.0f,  -4.0f,
                8.0f,  4.0f, 0.0f, 4.0f, 2.0f,  -4.0f,
                12.0f, 4.0f, 0.0f, 4.0f, 1.0f,  -4.0f,
                16.0f, 4.0f, 0.0f, 4.0f, 0.9f,  -4.0f,
                20.0f, 4.0f, 0.0f, 4.0f, 0.8f,  -4.0f,
                24.0f, 4.0f, 0.0f, 4.0f, 0.7f,  -4.0f,
                28.0f, 4.0f, 0.0f, 4.0f, 0.6f,  -4.0f,
                32.0f, 4.0f, 0.0f, 4.0f, 0.5f,  -4.0f,
                36.0f, 4.0f, 0.0f, 4.0f, 0.4f,  -4.0f,
                40.0f, 4.0f, 0.0f, 4.0f, 0.3f,  -4.0f,
                44.0f, 4.0f, 0.0f, 4.0f, 0.2f,  -4.0f,
                48.0f, 4.0f, 0.0f, 4.0f, 0.1f,  -4.0f,
                52.0f, 4.0f, 0.0f, 4.0f, 0.09f, -4.0f,
                56.0f, 4.0f, 0.0f, 4.0f, 0.08f, -4.0f,
                60.0f, 4.0f, 0.0f, 4.0f, 0.07f, -4.0f,
            };

            vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);
            vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
            vgSetf(VG_STROKE_MITER_LIMIT, 10000.0f);
        }
        break;
    }

    /* Draw the path with each join style. */

    for (i = 0; i < 3; i++)
    {
        static const struct
        {
            VGuint      color;
            VGJoinStyle joinStyle;
        } cases[] =
        {
            { 0x0000ffff, VG_JOIN_MITER },
            { 0xff0000ff, VG_JOIN_ROUND },
            { 0x00ff00ff, VG_JOIN_BEVEL }
        };

        vgSetColor(vgPaint, cases[i].color);
        vgSeti(VG_STROKE_JOIN_STYLE, cases[i].joinStyle);
        vgDrawPath(vgPath, VG_STROKE_PATH);
    }

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPath);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

