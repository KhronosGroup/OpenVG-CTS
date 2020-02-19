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

CT_Result G20503_PathOperation_by_HYBRID(CT_File *AnsFile, VGuint subtest)
{
    VGPaint stroke;
    VGPath target;
    VGPath lines;
    VGPath quad;
    VGPath cubic;
    VGPath arcs;
    VGfloat bgCol[4];
    VGfloat color1[4];
    VGfloat color2[4];
    VGfloat xform[9];
    VGubyte lineCmds[6];
    VGfloat lineCoords[8];
    VGubyte quadCmds[3];
    VGfloat quadCoords[10];
    VGubyte cubicCmds[3];
    VGfloat cubicCoords[14];
    VGfloat arcCoords[5];
    VGubyte sccCmd[1];
    VGubyte scCmd[1];
    VGubyte lccCmd[1];
    VGubyte lcCmd[1];
    VGubyte moveCmd[1];
    VGfloat moveCoords[2];
    VGint i;

    /* Test that lines, quadrics, cubics and arcs are rotated correctly by
    * vgTransformPath.
    */


    bgCol[0] = 1.0f;
    bgCol[1] = 1.0f;
    bgCol[2] = 1.0f;
    bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    stroke = vgCreatePaint();
    /* Red */
    color1[0] = 1.0f;
    color1[1] = 0.0f;
    color1[2] = 0.0f;
    color1[3] = 1.0f;

    /* Orange */
    color2[0] = 1.0000f;
    color2[1] = 1.0f;
    color2[2] = 0.0f;
    color2[3] = 1.0f;
    vgSetPaint(stroke, VG_STROKE_PATH);

    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);

    {
        VGfloat temp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (i = 0; i < 9; i++)
        {
            xform[i] = temp[i];
        }
    }
    vgGetMatrix(xform);


    /* Transform target path */
    target = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_TRANSFORM_TO);

    switch (subtest)
    {
    case 0:
        /* Line path */
        {
            VGubyte temp[6] = {VG_MOVE_TO_ABS, VG_VLINE_TO_REL, VG_MOVE_TO_ABS, VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_VLINE_TO_REL};
            for (i = 0; i < 6; i++)
            {
                lineCmds[i] = temp[i];
            }
        }
        {
            VGfloat temp[8] = {0.5f, 0.8f, -0.6f, 0.28f, 0.6f, -0.4f, 0.44f, 0.4f};
            for (i = 0; i < 8; i++)
            {
                lineCoords[i] = temp[i] * WINDSIZEX;
            }
        }

        lines = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
        vgAppendPathData(lines, 6, lineCmds, lineCoords);

        vgLoadIdentity();
        vgTranslate(0.25f * WINDSIZEX, 0.25f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgTransformPath(target, lines);

        vgLoadMatrix(xform);
        vgTranslate(0.25f * WINDSIZEX, 0.25f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgSetf(VG_STROKE_LINE_WIDTH, 7);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
        vgDrawPath(lines, VG_STROKE_PATH);

        vgLoadMatrix(xform);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);
        vgSetf(VG_STROKE_LINE_WIDTH, 3);
        vgDrawPath(target, VG_STROKE_PATH);
        vgDestroyPath(lines);
        break;
    case 1:
        /* Quadric path */
        {
            VGubyte temp[3] = {VG_MOVE_TO_ABS, VG_QUAD_TO_ABS, VG_QUAD_TO_ABS};
            for (i = 0; i < 3; i++)
            {
                quadCmds[i] = temp[i];
            }
        }
        {
            VGfloat temp[10] = {0.36f, 0.8f, 0.8f, 0.7f, 0.5f, 0.5f, 0.8f, 0.3f, 0.36f, 0.2f};
            for (i = 0; i < 10; i++)
            {
                quadCoords[i] = temp[i] * WINDSIZEX;
            }
        }
        quad = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
        vgAppendPathData(quad, 3, quadCmds, quadCoords);

        vgLoadIdentity();
        vgTranslate(0.25f * WINDSIZEX, 0.25f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgClearPath(target, VG_PATH_CAPABILITY_TRANSFORM_TO);
        vgTransformPath(target, quad);

        vgLoadMatrix(xform);
        vgTranslate(0.25f * WINDSIZEX, 0.25f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);

        vgSetf(VG_STROKE_LINE_WIDTH, 7);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
        vgDrawPath(quad, VG_STROKE_PATH);

        vgLoadMatrix(xform);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);
        vgSetf(VG_STROKE_LINE_WIDTH, 3);
        vgDrawPath(target, VG_STROKE_PATH);
        vgDestroyPath(quad);
        break;
    case 2:
        /* Cubic path */
        {
            VGubyte temp[3] = {VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, VG_CUBIC_TO_ABS};
            for (i = 0; i < 3; i++)
            {
                cubicCmds[i] = temp[i];
            }
        }
        {
            VGfloat temp[14] = {0.2f, 0.74f, 0.8f, 0.8f, 0, 0.2f, 0.5f, 0.2f, 1.0f, 0.2f, 0.2f, 0.8f, 0.8f, 0.74f};
            for (i = 0; i < 14; i++)
            {
                cubicCoords[i] = temp[i] * WINDSIZEX;
            }
        }

        cubic = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
        vgAppendPathData(cubic, 3, cubicCmds, cubicCoords);

        vgLoadIdentity();
        vgTranslate(0.5f * WINDSIZEX, 0.8f * WINDSIZEY);
        vgRotate(210);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgClearPath(target, VG_PATH_CAPABILITY_TRANSFORM_TO);
        vgTransformPath(target, cubic);

        vgLoadMatrix(xform);
        vgTranslate(0.5f * WINDSIZEX, 0.8f * WINDSIZEY);
        vgRotate(210);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgSetf(VG_STROKE_LINE_WIDTH, 7);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
        vgDrawPath(cubic, VG_STROKE_PATH);

        vgLoadMatrix(xform);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);
        vgSetf(VG_STROKE_LINE_WIDTH, 3);
        vgDrawPath(target, VG_STROKE_PATH);
        vgDestroyPath(cubic);
        break;
    case 3:
        /* Arc path */
        {
            VGfloat temp[5] = {0.35f, 0.15f, 29, 0.3f, 0.4f};
            for (i = 0; i < 5; i++)
            {
                arcCoords[i] = temp[i] * WINDSIZEX;
            }
            arcCoords[2] = 29;
        }

        {
            VGubyte temp[1] = {VG_SCCWARC_TO_ABS};
            for (i = 0; i < 1; i++)
            {
                sccCmd[i] = temp[i];
            }
        }
        {
            VGubyte temp[1] = {VG_SCWARC_TO_ABS};
            for (i = 0; i < 1; i++)
            {
                scCmd[i] = temp[i];
            }
        }
        {
            VGubyte temp[1] = {VG_LCCWARC_TO_ABS};
            for (i = 0; i < 1; i++)
            {
                lccCmd[i] = temp[i];
            }
        }
        {
            VGubyte temp[1] = {VG_LCWARC_TO_ABS};
            for (i = 0; i < 1; i++)
            {
                lcCmd[i] = temp[i];
            }
        }

        {
            VGubyte temp[1] = {VG_MOVE_TO_ABS};
            for (i = 0; i < 1; i++)
            {
                moveCmd[i] = temp[i];
            }
        }
        {
            VGfloat temp[2] = {0.7f, 0.6f};
            for (i = 0; i < 2; i++)
            {
                moveCoords[i] = temp[i] * WINDSIZEX;
            }
        }

        arcs = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
        vgAppendPathData(arcs, 1, moveCmd, moveCoords);
        vgAppendPathData(arcs, 1, sccCmd, arcCoords);
        vgAppendPathData(arcs, 1, moveCmd, moveCoords);
        vgAppendPathData(arcs, 1, scCmd, arcCoords);
        vgAppendPathData(arcs, 1, moveCmd, moveCoords);
        vgAppendPathData(arcs, 1, lccCmd, arcCoords);
        vgAppendPathData(arcs, 1, moveCmd, moveCoords);
        vgAppendPathData(arcs, 1, lcCmd, arcCoords);

        vgLoadIdentity();
        vgTranslate(0.35f * WINDSIZEX, 0.2f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);
        vgClearPath(target, VG_PATH_CAPABILITY_TRANSFORM_TO);
        vgTransformPath(target, arcs);

        vgLoadMatrix(xform);
        vgTranslate(0.35f * WINDSIZEX, 0.2f * WINDSIZEY);
        vgRotate(30);
        vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEY);

        vgSetf(VG_STROKE_LINE_WIDTH, 7);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
        vgDrawPath(arcs, VG_STROKE_PATH);

        vgLoadMatrix(xform);
        vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color2);
        vgSetf(VG_STROKE_LINE_WIDTH, 3);
        vgDrawPath(target, VG_STROKE_PATH);
        vgDestroyPath(arcs);
        break;
    }
    vgDestroyPaint(stroke);
    vgDestroyPath(target);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_SUBTEST_BUFFER(subtest);    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}
