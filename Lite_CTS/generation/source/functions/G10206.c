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

CT_Result G10206_PathSegment_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPath spiral;
    VGPath loop;
    VGfloat bgCol[4];
    VGfloat color1[4];
    VGfloat xform[9];
    VGubyte startCmds[2];
    VGfloat startCoords[4];
    VGubyte spiralCmds[4];
    VGfloat spiralCoords[16];
    VGint i;

	/* Tests that cubic tesselation can keep up with different curvatures
	 * by rendering a spiral.
	 */

	bgCol[0] = 1.0f;
	bgCol[1] = 1.0f;
	bgCol[2] = 1.0f;
	bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    stroke = vgCreatePaint();
	color1[0] = 1.0f;
	color1[1] = 0.0f;
	color1[2] = 0.0f;
	color1[3] = 1.0f;

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);

    vgSetf(VG_STROKE_LINE_WIDTH, 1.5);

    {
        VGfloat temp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (i = 0; i < 9; i++)
        {
            xform[i] = temp[i];
        }
    }
    vgGetMatrix(xform);

	/* Create spiral */
    {
        VGubyte temp[2] = {VG_MOVE_TO, VG_LINE_TO_ABS};
        for (i = 0; i < 2; i++)
        {
            startCmds[i] = temp[i];
        }
    }
    {
        VGfloat temp[4] = {0.2f, 0.05f, 0.5f, 0.05f};
        for (i = 0; i < 4; i++)
        {
            startCoords[i] = temp[i] * WINDSIZEX;
        }
    }

    {
        VGubyte temp[4] = {VG_SCUBIC_TO_ABS, VG_SCUBIC_TO_ABS, VG_SCUBIC_TO_ABS, VG_SCUBIC_TO_ABS};
        for (i = 0; i < 4; i++)
        {
            spiralCmds[i] = temp[i];
        }
    }
    {
        VGfloat temp[16] = {0.91f, 0.29f, 0.91f, 0.5f, 0.72f, 0.89f, 0.5f, 0.89f, 0.14f, 0.73f, 0.14f, 0.5f, 0.34f, 0.17f, 0.5f, 0.17f};
        for (i = 0; i < 16; i++)
        {
            spiralCoords[i] = temp[i] * WINDSIZEX;
        }
    }

    spiral = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_TO);
    vgAppendPathData(spiral, 2, startCmds, startCoords);

    loop = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
    vgAppendPathData(loop, 4, spiralCmds, spiralCoords);

    vgLoadIdentity();
    vgTransformPath(spiral, loop);

    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.8f, 0.8f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.8f, 0.8f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.7f, 0.7f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.6f, 0.6f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.5f, 0.5f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.3f, 0.3f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.3f, 0.3f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);
    vgTranslate(0.5f * WINDSIZEX, 0.5f * WINDSIZEY);
    vgScale(0.3f, 0.3f);
    vgTranslate(-0.5f * WINDSIZEX, -0.5f * WINDSIZEY);
    vgTransformPath(spiral, loop);

    vgLoadMatrix(xform);

    vgDrawPath(spiral, VG_STROKE_PATH);

    vgDestroyPaint(stroke);
    vgDestroyPath(spiral);
    vgDestroyPath(loop);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}
