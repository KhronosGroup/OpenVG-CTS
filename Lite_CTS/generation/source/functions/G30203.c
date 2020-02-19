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

CT_Result G30203_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPath path;
    VGPaint stroke;
    VGPath points;
    VGubyte cmds[2];
    VGfloat bgCol[4];
    VGfloat color1[4];
    VGfloat coords1[8];
    VGfloat coords2[8];
    VGfloat coords3[8];
    VGfloat coords4[8];
    VGfloat color2[4];
    VGubyte pntCmds[8];
    VGint i;

    bgCol[0] = 1.000f;
    bgCol[1] = 1.000f;
    bgCol[2] = 1.000f;
    bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

/*  Setup
 */
/* UN_USED: SetFlag(DRVLIB_STOP_ON_OPENVG_ERROR)
 */
    {
        VGubyte temp[2] = {VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS};
        for (i = 0; i < 2; i++)
        {
            cmds[i] = temp[i];
        }
    }
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);

    vgSetf(VG_STROKE_LINE_WIDTH, 10);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_BEVEL);

    stroke = vgCreatePaint();

    color1[0] = 1.000f;
    color1[1] = 0.000f;
    color1[2] = 0.000f;
    color1[3] = 1.0f;
    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    /* Control points form a square with 3rd point above the 1st and 2nd above 4th. */

    {
        VGfloat temp[8] = {0, 0, 0.5f, 0.5f, 0, 0.5f, 0.5f, 0};
        for (i = 0; i < 8; i++)
        {
            coords1[i] = temp[i] * WINDSIZEX;
        }
    }
    vgAppendPathData(path, 2, cmds, coords1);
    vgDrawPath(path, VG_STROKE_PATH);

    /* In one line, intermediate points right of the 4th point. */

    vgTranslate(0.5f * WINDSIZEX, 0);
    {
        VGfloat temp[8] = {0, 0.25f, 0.5f, 0.25f, 0.4f, 0.25f, 0.3f, 0.25f};
        for (i = 0; i < 8; i++)
        {
            coords2[i] = temp[i] * WINDSIZEX;
        }
    }
    vgModifyPathCoords(path, 0, 2, coords2);
    vgDrawPath(path, VG_STROKE_PATH);

    /* In one line, 2nd point right of 4th and 3rd left of 1st. */
    vgTranslate(-0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    {
        VGfloat temp[8] = {0.2f, 0.25f, 0.5f, 0.25f, 0, 0.25f, 0.3f, 0.25f};
        for (i = 0; i < 8; i++)
        {
            coords3[i] = temp[i] * WINDSIZEX;
        }
    }
    vgModifyPathCoords(path, 0, 2, coords3);
    vgDrawPath(path, VG_STROKE_PATH);

    /* In one line, intermediate points in one line. */
    vgTranslate(0.5f * WINDSIZEX, 0);
    {
        VGfloat temp[8] = {0.2f, 0.25f, 0.5f, 0.25f, 0.4f, 0.25f, 0.3f, 0.25f};
        for (i = 0; i < 8; i++)
        {
            coords4[i] = temp[i] * WINDSIZEX;
        }
    }
    vgModifyPathCoords(path, 0, 2, coords4);
    vgDrawPath(path, VG_STROKE_PATH);

    /* Debug points (Draw the control points) */
    vgSetf(VG_STROKE_LINE_WIDTH, 5);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);

    color2[0] = 0;
    color2[1] = 0;
    color2[2] = 0;
    color2[3] = 1.0f;
    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);

    {
        VGubyte temp[8] = {VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH};
        for (i = 0; i < 8; i++)
        {
            pntCmds[i] = temp[i];
        }
    }
    points = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);

    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgAppendPathData(points, 8, pntCmds, coords1);
    vgDrawPath(points, VG_STROKE_PATH);

    vgTranslate(0.5f * WINDSIZEX, 0);
    vgModifyPathCoords(points, 0, 8, coords2);
    vgDrawPath(points, VG_STROKE_PATH);

    vgTranslate(-0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgModifyPathCoords(points, 0, 8, coords3);
    vgDrawPath(points, VG_STROKE_PATH);

    vgTranslate(0.5f * WINDSIZEX, 0);
    vgModifyPathCoords(points, 0, 8, coords4);
    vgDrawPath(points, VG_STROKE_PATH);

    vgDestroyPath(path);
    vgDestroyPaint(stroke);
    vgDestroyPath(points);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

