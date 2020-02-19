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
#include "../static/hybrid/checker.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

/*---------------------------------------------------------------------
 * Test the behaviour of a pattern image.
 * VG_PAINT_PATTERN_TILING_MODE = VG_TILE_FILL.
 *-------------------------------------------------------------------*/
CT_Result I40102_PaintPatternImage_by_HYBRID(CT_File *AnsFile)
{
    VGImage checker;
    VGPaint paint;
    VGPath	path;
    VGfloat fill_color[4]	= {0.0f, 0.0f, 0.0f, 1.0f};
	VGfloat clear_color[4]	= {1.0f, 1.0f, 1.0f, 1.0f};

	/* Tests pattern fill with rotations, scale and translations on the pattern image */ 

	/* Generate an image with no antialiasing */
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

	/* Clear the drawing surface */
	vgSetfv(VG_CLEAR_COLOR, 4, clear_color);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    checker = vgCreateImage(VG_sRGBA_8888, checker_width, checker_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(checker, checker_data, checker_stride, VG_sRGBA_8888, 0, 0, checker_width, checker_height);

	/* Create the paint and set parameters for the pattern fill */
    paint = vgCreatePaint();
    vgSetPaint(paint, VG_FILL_PATH);
    vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
    vgSetParameteri(paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_FILL);
    vgPaintPattern(paint, checker);

	/* Set the tile fill color */
    vgSetfv(VG_TILE_FILL_COLOR, 4, fill_color);

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32, 1, 0, 4, 8, VG_PATH_CAPABILITY_ALL);
    DrawRect_by_HYBRID(path, 0, 0, 64, 64);

	/* Set the indentity matrix and draw the path */
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);

	/*---------------------------------------------------------------------
	 * Rotate by 45 degrees and translate by small amounts.
	 *-------------------------------------------------------------------*/
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
    vgLoadIdentity();
    vgRotate(45);
	vgTranslate(30, -56);

	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgDrawPath(path, VG_FILL_PATH);

	/*---------------------------------------------------------------------
	 * Cleanup
	 *-------------------------------------------------------------------*/
    vgDestroyImage(checker);
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

