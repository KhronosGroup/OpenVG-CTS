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

CT_Result G30127_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPath	obtuse;
    VGPath	right;
    VGPath	acute;
    VGPath	veryAcute;
    VGfloat bgCol[4]		= {1.000f, 1.000f, 1.000f, 1.0f};
    VGfloat color[4]		= {1.000f, 0.000f, 0.000f, 1.0f};
    VGubyte joinCmds[3]		= {VG_MOVE_TO, VG_LINE_TO_REL, VG_LINE_TO_REL};
    VGfloat coords[6];
    VGint	i;

	/* Test that the miter limits work in basic cases as expected. */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    stroke = vgCreatePaint();

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color);
    vgSetPaint(stroke, VG_STROKE_PATH);

    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSetf(VG_STROKE_LINE_WIDTH, 10.f);

	/* Angle 135 */
    obtuse = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    {
        VGfloat temp[6] = {0.1f, 0, 0, 0.25f, 0.2f, 0.2f};
        for (i = 0; i < 6; i++)
        {
            coords[i] = temp[i] * WINDSIZEX;
        }
    }
    vgAppendPathData(obtuse, 3, joinCmds, coords);

	/* Angle 90 */
    right = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    {
        VGfloat temp[2] = {0.2f, 0.0f};
        for (i = 0; i < 2; i++)
        {
            coords[i + 4] = temp[i] * WINDSIZEX;
        }
    }
    vgAppendPathData(right, 3, joinCmds, coords);

	/* Angle 45 */
    acute = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    {
        VGfloat temp[2] = {0.2f, -0.2f};
        for (i = 0; i < 2; i++)
        {
            coords[i + 4] = temp[i] * WINDSIZEX;
        }
    }
    vgAppendPathData(acute, 3, joinCmds, coords);

	/* Angle appr. 1.468f */
    veryAcute = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    {
		VGfloat temp[2] = {0.06f, -0.8f};
        for (i = 0; i < 2; i++)
        {
            coords[i + 4] = temp[i] * WINDSIZEX;
        }
		coords[3] = 0.8f * WINDSIZEX;
    }
    vgAppendPathData(veryAcute, 3, joinCmds, coords);

	/* Miter limit 2.615f */

    vgSetf(VG_STROKE_MITER_LIMIT, 2.615f);

	vgTranslate(0, (VGint)(WINDSIZEY/10));
    vgDrawPath(obtuse, VG_STROKE_PATH);
    vgTranslate((VGint)(0.35f * WINDSIZEX), 0);
	vgDrawPath(right, VG_STROKE_PATH);
	vgTranslate((VGint)(0.3f * WINDSIZEX), 0);
	vgDrawPath(veryAcute, VG_STROKE_PATH);
	vgLoadIdentity();
    vgTranslate(0, (VGint)(0.6f * WINDSIZEY));
    vgDrawPath(acute, VG_STROKE_PATH);

    vgDestroyPaint(stroke);
    vgDestroyPath(obtuse);
    vgDestroyPath(right);
    vgDestroyPath(acute);
    vgDestroyPath(veryAcute);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}
