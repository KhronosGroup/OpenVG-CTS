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

CT_Result G40102_PathDashing_by_HYBRID(CT_File *AnsFile)
{
    VGPaint paint;
    VGPath path;
    VGfloat bgColor[4];
    VGfloat col[4];
    VGubyte commands[1];
    VGshort coords[1];
    VGfloat dashes[2];
    VGfloat dashes_zero1[4];

    /* Try out negative and positive dash phases. */

    bgColor[0] = 1.0000f;
    bgColor[1] = 1.0000f;
    bgColor[2] = 1.0000f;
    bgColor[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    /* Paint used for all strokes */
    paint = vgCreatePaint();
    vgSetPaint(paint, VG_STROKE_PATH);
    col[0] = 1.0000f;
    col[1] = 0.0000f;
    col[2] = 0.0000f;
    col[3] = 1;
    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, col);

    vgSetf(VG_STROKE_LINE_WIDTH, 6);

    commands[0] = VG_HLINE_TO_REL;
    coords[0] = WINDSIZEX;

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_16,
        1.0f, 0.0f, 1, 1, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path, 1, commands, coords);


    /* "Normal" positive phase, normal dashes.
     * This is the bottom line, the following lines will be above in order.
     */
    dashes[0] = 0.25 * WINDSIZEX;
    dashes[1] = 0.25 * WINDSIZEX;

    vgSetfv(VG_STROKE_DASH_PATTERN, 2, dashes);
    vgSetf(VG_STROKE_DASH_PHASE, 0.33f * WINDSIZEX);

    vgTranslate(5, 7);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgDrawPath(path, VG_STROKE_PATH);

    /* Zero length "off" dash and negative phase. */
    dashes_zero1[0] = 0.05f * WINDSIZEX;
    dashes_zero1[1] = 0;
    dashes_zero1[2] = 0.20f * WINDSIZEX;
    dashes_zero1[3] = 0.25f * WINDSIZEX;
    vgSetfv(VG_STROKE_DASH_PATTERN, 4, dashes_zero1);
    vgSetf(VG_STROKE_DASH_PHASE, -0.33f * WINDSIZEX);

    vgTranslate(0, 12);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgDrawPath(path, VG_STROKE_PATH);

    dashes_zero1[0] = 0.25f * WINDSIZEX;
    dashes_zero1[1] = 0.12f * WINDSIZEX;
    dashes_zero1[2] = 0;
    dashes_zero1[3] = 0.13f * WINDSIZEX;

    vgSetfv(VG_STROKE_DASH_PATTERN, 4, dashes_zero1);
    vgSetf(VG_STROKE_DASH_PHASE, -12.345f * WINDSIZEX);

    vgTranslate(0, 12);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgDrawPath(path, VG_STROKE_PATH);

    vgTranslate(0, 12);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSetf(VG_STROKE_DASH_PHASE, 34.567f * WINDSIZEX);
    vgDrawPath(path, VG_STROKE_PATH);

    vgTranslate(0, 12);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgSetf(VG_STROKE_DASH_PHASE, -0.1234f * WINDSIZEX);
    vgDrawPath(path, VG_STROKE_PATH);

    vgDestroyPaint(paint);
    vgDestroyPath(path);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

