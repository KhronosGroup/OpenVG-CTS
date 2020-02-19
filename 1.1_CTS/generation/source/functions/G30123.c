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

CT_Result G30123_PathStroking_by_HYBRID(CT_File *AnsFile)
{
    VGPaint paint;
    VGPath	degLineJoin;
    VGfloat color[4]				= {0.0f, 0.0f, 1.0f, 1.0f};
    VGfloat pathCol[4]				= {1.0f, 1.0f, 1.0f, 1.0f};
    VGubyte degLineJoinCmds[4]		= {VG_MOVE_TO, VG_LINE_TO, VG_LINE_TO, VG_LINE_TO};
    VGfloat degLineJoinCoords[8]	= {0.01f, 0.01f, 0.18f, 0.4f, 0.18f, 0.4f, 0.4f, 0.06f};
    VGint i;

	/* Test that zero-length line joins with coincident vertices work. */

    vgSetfv(VG_CLEAR_COLOR, 4, color);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    paint = vgCreatePaint();

    vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, pathCol);
    vgSetPaint(paint, VG_STROKE_PATH);

	/* Line with a join and the join having two coincident vertices,
	   i.e., absolute move to the same point as previous. */

    /* Scale the coordinates */
	for (i = 0; i < 8; i++)
    {
	    degLineJoinCoords[i] = degLineJoinCoords[i] * WINDSIZEX;
    }

    degLineJoin = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 4, 8, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(degLineJoin, 4, degLineJoinCmds, degLineJoinCoords);

    vgTranslate((VGint)(WINDSIZEX*0.3f), (VGint)(WINDSIZEY*0.3f));

	/* With miter join, make sure that the miter limit is big enough. */
    vgSetf(VG_STROKE_MITER_LIMIT, 1000.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSetf(VG_STROKE_LINE_WIDTH, 12.0f);
	vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgDrawPath(degLineJoin, VG_STROKE_PATH);

    vgDestroyPaint(paint);
    vgDestroyPath(degLineJoin);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }

}

