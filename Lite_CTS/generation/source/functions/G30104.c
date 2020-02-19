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

CT_Result G30104_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPaint paint;
    VGPath degLine;
    VGPath degLineRel;
    VGfloat color[4]				= {0.4f, 0.3f, 1.0f, 1.0f};
    VGfloat pathCol[4]				= {1.0f, 1.0f, 1.0f, 1.0f};
    VGubyte degLineCmds[2]			= {VG_MOVE_TO, VG_LINE_TO};
    VGfloat degLineCoords[4]		= {0.01f, 0.00f, 0.01f, 0.00f};
    VGubyte degLineRelCmds[2]		= {VG_MOVE_TO, VG_LINE_TO|VG_RELATIVE};
    VGfloat degLineRelCoords[4]		= {0.01f, 0.00f, 0.00f, 0.00f};
    VGint i;

	/* Test that zero-length line caps and joins with coincident vertices work. */

    vgSetfv(VG_CLEAR_COLOR, 4, color);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    paint = vgCreatePaint();

    vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, pathCol);
    vgSetPaint(paint, VG_STROKE_PATH);

    for (i = 0; i < 4; i++)
    {
	    degLineCoords[i] = degLineCoords[i] * WINDSIZEX;
    }

	/* Absolute coordinates. */
    degLine = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
						   1.0f, 0.0f, 2, 4, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(degLine, 2, degLineCmds, degLineCoords);
	vgSetf(VG_STROKE_LINE_WIDTH, 26.0f);

	/* Round cap (Drawing starts from left lower corner */
    vgTranslate((VGint)(WINDSIZEX/4), (VGint)(WINDSIZEY/4));
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgDrawPath(degLine, VG_STROKE_PATH);

	/* Square cap */
    vgTranslate((VGint)(WINDSIZEX/2), 0);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgDrawPath(degLine, VG_STROKE_PATH);

	/* Butt cap (should draw nothing). */
    vgTranslate(-(VGint)(WINDSIZEX/4), 0);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgDrawPath(degLine, VG_STROKE_PATH);

    vgLoadIdentity();

	/* Next row, use relative line to, draw with same three caps. */
    degLineRel = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 2, 4, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(degLineRel, 2, degLineRelCmds, degLineRelCoords);

    vgTranslate((VGint)(WINDSIZEX/4), (VGint)(3*(WINDSIZEY/4)));
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSetf(VG_STROKE_LINE_WIDTH, 26.0f);
    vgDrawPath(degLineRel, VG_STROKE_PATH);

    vgTranslate((VGint)(WINDSIZEX/2), 0);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgDrawPath(degLineRel, VG_STROKE_PATH);

    vgTranslate(-(VGint)(WINDSIZEX/4), 0);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgDrawPath(degLineRel, VG_STROKE_PATH);

    vgDestroyPaint(paint);
    vgDestroyPath(degLine);
    vgDestroyPath(degLineRel);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}
