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

CT_Result G30106_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPath	path;
    VGfloat bgCol[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
    VGfloat color1[4]	= {1.0f, 0.0f, 0.0f, 1.0f};
    VGubyte cmds1[8]	= {VG_MOVE_TO, VG_CLOSE_PATH, VG_MOVE_TO_REL, VG_HLINE_TO_REL, VG_MOVE_TO_REL, VG_VLINE_TO_REL, VG_MOVE_TO_REL, VG_LINE_TO_REL};
    VGbyte	coords1[12]	= {5, 5, 18, 0, 0, 18, 0, 0, 18, 0, 0, 0};
    VGubyte cmds2[8]	= {VG_MOVE_TO, VG_QUAD_TO_REL, VG_MOVE_TO_REL, VG_SQUAD_TO_REL, VG_MOVE_TO_REL, VG_CUBIC_TO_REL, VG_MOVE_TO_REL, VG_SCUBIC_TO_REL};
    VGbyte	coords2[24]	= {5, 23, 0, 0, 0, 0, 18, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0};
    VGubyte cmds3[8]	= {VG_MOVE_TO, VG_SCCWARC_TO_REL, VG_MOVE_TO_REL, VG_SCWARC_TO_REL, VG_MOVE_TO_REL, VG_LCCWARC_TO_REL, VG_MOVE_TO_REL, VG_LCWARC_TO_REL};
    VGbyte	coords3[28]	= {5, 41, 10, 20, 30, 0, 0, 18, 0, 10, 20, 30, 0, 0, 18, 0, 10, 20, 30, 0, 0, 18, 0, 10, 20, 30, 0, 0};
    VGubyte cmds4[8]	= {VG_MOVE_TO, VG_LINE_TO, VG_MOVE_TO, VG_QUAD_TO, VG_MOVE_TO, VG_CUBIC_TO, VG_MOVE_TO, VG_SCWARC_TO};
    VGbyte	coords4[25]	= {5, 59, 5, 59, 23, 59, 23, 59, 23, 59, 41, 59, 41, 59, 41, 59, 41, 59, 59, 59, 10, 20, 30, 59, 59};

	/*  Test that degenerate subpaths are rendered correctly by creating one
	 *  path having each kind of segment as degenerate followed by
	 *  MOVE_TO. Also, cap is set to square to see that it is correctly
	 *  rendered.
	 */

	/* Disable antialiasing */
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0,0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgSetf(VG_STROKE_LINE_WIDTH, 6.0f);

    stroke = vgCreatePaint();
    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_8, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);

	/*  Bottom row: Close path and lines. */
    vgAppendPathData(path, 8, cmds1, coords1);

	/*  2nd row: Quadrics and cubics */
    vgAppendPathData(path, 8, cmds2, coords2);

	/*  3rd row: arcs */
    vgAppendPathData(path, 8, cmds3, coords3);

	/*  Some of them again with absolute versions. */
    vgAppendPathData(path, 8, cmds4, coords4);

    vgDrawPath(path, VG_STROKE_PATH);

    vgDestroyPaint(stroke);
    vgDestroyPath(path);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

