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

CT_Result G30204_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPath path;
    VGPaint stroke;
    VGPath points;
    VGPath control;
    VGubyte cmds[3];
    VGfloat bgCol[4];
    VGfloat pointCol[4];
    VGfloat color1[4];
    VGfloat color2[4];
    VGfloat coords[12];
    VGubyte pointCmds[12];
    VGubyte controlCmds[2];
    VGfloat controlCoords[8];
    VGint i;

    /* Test smoothness of cubics while the join that is supposed be smooth becomes tighter. */

    cmds[0] = VG_MOVE_TO_ABS;
    cmds[1] = VG_CUBIC_TO_ABS;

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);

    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_BEVEL);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);

    bgCol[0] = 1.000f;
    bgCol[1] = 1.000f;
    bgCol[2] = 1.000f;
    bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    pointCol[0] = 0;
    pointCol[1] = 0;
    pointCol[2] = 0;
    pointCol[3] = 1;

    stroke = vgCreatePaint();
    /* Red */
    color1[0] = 1.000f;
    color1[1] = 0.000f;
    color1[2] = 0.000f;
    color1[3] = 1.0f;

    /* Blue */
    color2[0] = 0.0000f;
    color2[1] = 1.0000f;
    color2[2] = 1.0000f;
    color2[3] = 1.0f;

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    /* Basic path */
    vgDestroyPath(path);
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO | VG_PATH_CAPABILITY_MODIFY);
    {
        VGubyte temp[3] = {VG_MOVE_TO, VG_CUBIC_TO, VG_SCUBIC_TO};
        for (i = 0; i < 3; i++)
        {
            cmds[i] = temp[i];
        }
    }
    {
        VGfloat temp[12] = {0.1f, 0.1f, 0, 0.2f, 0.2f, 0.35f, 0.3f, 0.4f, 0.35f, 0.1f, 0.1f, 0.1f};
        for (i = 0; i < 12; i++)
        {
            coords[i] = temp[i] * WINDSIZEX * 2;
        }
    }

    vgAppendPathData(path, 3, cmds, coords);

    /* Point path (Used to render the control points) */
    points = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);
    {
        VGubyte temp[12] = {VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO, VG_CLOSE_PATH};
        for (i = 0; i < 12; i++)
        {
            pointCmds[i] = temp[i];
        }
    }
    vgAppendPathData(points, 12, pointCmds, coords);

    /* Control curve (Hand calculated "smooth" curve) */
    control = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);
    {
        VGubyte temp[2] = {VG_MOVE_TO, VG_CUBIC_TO};
        for (i = 0; i < 2; i++)
        {
            controlCmds[i] = temp[i];
        }
    }
    {
        VGfloat temp[8] = {0.3f, 0.4f, 0.4f, 0.45f, 0.35f, 0.1f, 0.1f, 0.1f};
        for (i = 0; i < 8; i++)
        {
            controlCoords[i] = temp[i] * WINDSIZEX * 2;
        }
    }
    vgAppendPathData(control, 2, controlCmds, controlCoords);

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, pointCol);
    vgSetf(VG_STROKE_LINE_WIDTH, 4);
    vgDrawPath(points, VG_STROKE_PATH);

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);
    vgSetf(VG_STROKE_LINE_WIDTH, 8);
    vgDrawPath(control, VG_STROKE_PATH);

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetf(VG_STROKE_LINE_WIDTH, 4);
    vgDrawPath(path, VG_STROKE_PATH);

    vgDestroyPath(path);
    vgDestroyPaint(stroke);
    vgDestroyPath(points);
    vgDestroyPath(control);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

