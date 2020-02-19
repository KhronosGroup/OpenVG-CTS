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

#include "../main.h"
#include "../util/util.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result C10802_MatrixOperation_by_HYBRID(CT_File *AnsFile)
{
    VGPaint paint;
    VGPath dots;
    VGfloat color[4];
    VGfloat pathCol[4];
    VGubyte dotCmds[8];
    VGfloat dotCoords[16];
    VGint i;

/*  Probe transform accuracy by rotating back and forth and
 *  translating. All cases are expected to produce approximately same
 *  orientation.
 */

    {
        VGfloat temp[4] = {1.f, 1.f, 1.f, 1.f};
        for (i = 0; i < 4; i++)
        {
            color[i] = temp[i];
        }
    }
    vgSetfv(VG_CLEAR_COLOR, 4, color);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    paint = vgCreatePaint();
    {
        VGfloat temp[4] = {1.f, 0.f, 0.f, 1.f};
        for (i = 0; i < 4; i++)
        {
            pathCol[i] = temp[i];
        }
    }
    vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, pathCol);
    vgSetPaint(paint, VG_STROKE_PATH);

    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSetf(VG_STROKE_LINE_WIDTH, 11.0f);

/*  Path consists of four dots (degenerate lines with round caps) in a
 *  square formation. This will be drawn twice each time, once rotated to
 *  get the eight points.
 */
    {
        VGubyte temp[8] = {VG_MOVE_TO, VG_LINE_TO|VG_RELATIVE, VG_MOVE_TO, VG_LINE_TO|VG_RELATIVE, VG_MOVE_TO, VG_LINE_TO|VG_RELATIVE, VG_MOVE_TO, VG_LINE_TO|VG_RELATIVE};
        for (i = 0; i < 8; i++)
        {
            dotCmds[i] = temp[i];
        }
    }
    {
        VGfloat temp[16] = {0.0f, -0.4f, 0.0f, 0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.0f, 0.0f, -0.4f, 0.0f, 0.0f, 0.0f};
        for (i = 0; i < 16; i++)
        {
            dotCoords[i] = temp[i] * WINDSIZEX;
        }
    }
    dots = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 8, 16, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(dots, 8, dotCmds, dotCoords);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEX);

/*  Draw without translation for reference, this produces the largets
 *  dots in the background. Size decreases and color alternates between
 *  dark red and light brown after each draw.
 */
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(45.0f);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(-45.0f);

    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, color);
    vgSetf(VG_STROKE_LINE_WIDTH, 8.0f);

/*  Rotate 360 degrees in 10 degree increments. */
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);
    vgRotate(10);

    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(45.0f);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(-45.0f);

    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, pathCol);
    vgSetf(VG_STROKE_LINE_WIDTH, 5.0f);

/*  Rotate with a large multiple of 360 */
    vgRotate(360000);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(45.0f);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(-45.0f);

/*  Translate back and forth with the same values. These values should
 *  fit into floats.
 */
    vgTranslate(123013, 123005);
    vgTranslate(-123013, -123005);

    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, color);
    vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);

/*  Rotate once more with multiple of 360. */
    vgRotate(360000);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(45.0f);
    vgDrawPath(dots, VG_STROKE_PATH);
    vgRotate(-45.0f);

    vgDestroyPaint(paint);
    vgDestroyPath(dots);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

