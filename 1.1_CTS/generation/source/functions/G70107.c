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
 * G70107_PathTransform_by_NVIDIA
 *
 * Draws a 4x4 grid of ellipses with various transformation
 * matrices. The shape of each ellipse and the corresponding
 * transformation matrix should cancel each other out, resulting
 * in 16 circles with varying stroke width.
 */

#include "../main.h"
#include "../util/util.h"

static void ellipse(VGPath vgPath, VGfloat rx, VGfloat ry, VGfloat angle)
{
    static const VGubyte cmd[] =
    { VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL, VG_SCCWARC_TO_REL, VG_CLOSE_PATH };

    VGfloat val[12];
    VGfloat c = COSD(angle) * rx;
    VGfloat s = SIND(angle) * rx;

    val[0] = c;
    val[1] = s;
    val[2] = rx;
    val[3] = ry;
    val[4] = angle;
    val[5] = -2.0f * c;
    val[6] = -2.0f * s;
    val[7] = rx;
    val[8] = ry;
    val[9] = angle;
    val[10] = 2.0f * c;
    val[11] = 2.0f * s;

    vgClearPath(vgPath, VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(vgPath, sizeof(cmd), cmd, val);
    vgDrawPath(vgPath, VG_FILL_PATH | VG_STROKE_PATH);
}

CT_Result G70107_PathTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGPaint vgPaint;
    VGPath  vgPath;

    /* Create the fill paint (green). */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetColor(vgPaint, 0x00ff00ff);
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Create the path. */

    vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

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
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSetf(VG_STROKE_MITER_LIMIT, 4.0f);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* row 1, col 1: Identity transform. */

    vgLoadIdentity();
    vgTranslate(8.0f, 8.0f);
    ellipse(vgPath, 4.0f, 4.0f, 0.0f);

    /* row 1, col 2: 10^3 horizontal squeeze. */

    vgLoadIdentity();
    vgTranslate(24.0f, 8.0f);
    vgScale(1.0e-3f, 1.0f);
    ellipse(vgPath, 4.0e3f, 4.0f, 0.0f);

    /* row 1, col 3: 10^6 horizontal squeeze. */

    vgLoadIdentity();
    vgTranslate(40.0f, 8.0f);
    vgScale(1.0e-6f, 1.0f);
    ellipse(vgPath, 4.0e6f, 4.0f, 0.0f);

    /* row 1, col 4: 10^9 horizontal squeeze. */

    vgLoadIdentity();
    vgTranslate(56.0f, 8.0f);
    vgScale(1.0e-9f, 1.0f);
    ellipse(vgPath, 4.0e9f, 4.0f, 0.0f);

    /* row 2, col 1: 10^3 vertical squeeze. */

    vgLoadIdentity();
    vgTranslate(8.0f, 24.0f);
    vgScale(1.0f, 1.0e-3f);
    ellipse(vgPath, 4.0f, 4.0e3f, 0.0f);

    /* row 2, col 2: Shear 0. */

    vgLoadIdentity();
    vgTranslate(24.0f, 24.0f);
    vgShear(0.0f, 0.0f);
    ellipse(vgPath, 4.0f, 4.0f, 0.0f);

    /* row 2, col 3: Horizontal shear -1. */

    vgLoadIdentity();
    vgTranslate(40.0f, 24.0f);
    vgScale(0.61804f, 0.61804f);
    vgShear(-1.0f, 0.0f);
    ellipse(vgPath, 10.47213f, 4.0f, 31.717f);

    /* row 2, col 4: Horizontal shear 10. */

    vgLoadIdentity();
    vgTranslate(56.0f, 24.0f);
    vgScale(0.0990195f, 0.0990195f);
    vgShear(10.0f, 0.0f);
    ellipse(vgPath, 407.961f, 4.0f, 174.345f);

    /* row 3, col 1: 10^6 vertical squeeze. */

    vgLoadIdentity();
    vgTranslate(8.0f, 40.0f);
    vgScale(1.0f, 1.0e-6f);
    ellipse(vgPath, 4.0f, 4.0e6f, 0.0f);

    /* row 3, col 2: Vertical shear -1. */

    vgLoadIdentity();
    vgTranslate(24.0f, 40.0f);
    vgScale(0.61804f, 0.61804f);
    vgShear(0.0f, -1.0f);
    ellipse(vgPath, 10.47213f, 4.0f, 58.283f);

    /* row 3, col 3: Projective matrix with W = -0.1. */
    {
        static const VGfloat matrix[] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            40.0f, 40.0f, -0.1f
        };

        vgLoadMatrix(matrix);
        ellipse(vgPath, 4.0f, 4.0f, 0.0f);
    }

    /* row 3, col 4: Projective matrix with W = X. */
    {
        static const VGfloat matrix[] =
        {
            1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            56.0f, 40.0f, 0.0f
        };

        vgLoadMatrix(matrix);
        ellipse(vgPath, 4.0f, 4.0f, 0.0f);
    }

    /* row 4, col 1: 10^9 vertical squeeze. */

    vgLoadIdentity();
    vgTranslate(8.0f, 56.0f);
    vgScale(1.0f, 1.0e-9f);
    ellipse(vgPath, 4.0f, 4.0e9f, 0.0f);

    /* row 4, col 2: Horizontal shear 10. */

    vgLoadIdentity();
    vgTranslate(24.0f, 56.0f);
    vgScale(0.0990195f, 0.0990195f);
    vgShear(0.0f, 10.0f);
    ellipse(vgPath, 407.961f, 4.0f, -84.345f);

    /* row 4, col 3: Projective matrix with W = Y. */
    {
        static const VGfloat matrix[] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 1.0f,
            40.0f, 56.0f, 0.0f
        };

        vgLoadMatrix(matrix);
        ellipse(vgPath, 4.0f, 4.0f, 0.0f);
    }

    /* row 4, col 4: Rotation with large negative angle. */

    vgLoadIdentity();
    vgRotate(-123456.789f);
    vgTranslate(73.5372f, 29.3987f);
    ellipse(vgPath, 4.0f, 4.0f, 0.0f);

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPath);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();
    return CT_NO_ERROR;
}

