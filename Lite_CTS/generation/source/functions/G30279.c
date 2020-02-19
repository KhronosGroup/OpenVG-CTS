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

CT_Result G30279_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPath	path1;
    VGfloat bgCol[4]	= {0.000f, 0.000f, 0.000f, 1.0f};
    VGfloat color1[4]	= {0.000f, 1.000f, 0.000f, 0.75f};
    VGubyte cmds[2]		= {VG_MOVE_TO_REL, VG_CUBIC_TO_REL};
    VGfloat coords1[8]	= {0.111f, 0.125f,	0.9f, 0.f, 0.9f, 0.f, 0.75f, 0.f};
	VGfloat coords2[6]	= {0.75f, 0, 0, 0, 0.75f, 0};
    VGint	i;

	/* Test that cubics are rendered correctly even if
	 * some of the points coincide with each other.
	 */

	vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    stroke = vgCreatePaint();

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    vgSetf(VG_STROKE_LINE_WIDTH, 6);

	/* Scale the coordinates */
	for (i = 0; i < 8; i++)
    {
		coords1[i] = coords1[i] * WINDSIZEX;
    }

	/* Lower line: All control points beyond end point on the same line. */
    path1 = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0,  VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);
    vgAppendPathData(path1, 2, cmds, coords1);

    vgDrawPath(path1, VG_STROKE_PATH);

    vgTranslate(0, (VGint)(WINDSIZEY/2));

	/* Scale the coordinates */
    for (i = 0; i < 6; i++)
    {
	    coords2[i] = coords2[i] * WINDSIZEX;
    }

	/* Upper line: First control point at the end point, second control at the start point. */
    vgModifyPathCoords(path1, 1, 1, coords2);
    vgDrawPath(path1, VG_STROKE_PATH);

    vgDestroyPaint(stroke);
    vgDestroyPath(path1);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

