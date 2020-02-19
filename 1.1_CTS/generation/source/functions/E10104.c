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
#include "../static/hybrid/surf.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result E10104_ScissoringOperation_by_HYBRID(CT_File *AnsFile)
{
    VGPaint fill;
    VGPath path;
    VGImage surf;
    VGfloat bgCol[4]		= {0.5f, 0.5f, 0.5f, 1.0f};
    VGfloat color1[4]		= {0.671f, 0.106f, 0.133f, 1.0f};
    VGfloat color2[4]		= {0.6347f, 0.6561f, 0.6057f, 1.0f};
    VGfloat color3[4]		= {0.0000f, 0.6908f, 0.8595f, 1.0f};
    VGfloat xform[9]		= {0, 0, 0, 0, 0, 0, 0, 0, 0};
    VGint scissor1[8]		= {11, 11, 8, 8, 1, 1, 14, 14};
    VGubyte cmds[4]			= {VG_MOVE_TO, VG_QUAD_TO, VG_CUBIC_TO, VG_CLOSE_PATH};
    VGfloat coords[12]		= {5.f, -5.f, 0.f, 9.f, 10.f, 23.f, 22.f, 22.f, 12.5f, 12.5f, 22.f, 9.f};

	/*  Test scissoring by calling vgClear, vgDrawPath, vgDrawImage,
	 *  vgSetPixels, vgWritePixels and vgCopyPixels, with two overlapping
	 *  scissoring rects limiting the drawing area. Lines are drawn one pixel
	 *  outside the clipping rectangle borders to help debugging.
	 */

	/* Setup */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Filling paint */
    fill = vgCreatePaint();

    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, color3);
    vgSetPaint(fill, VG_FILL_PATH);

	/*  The initial transform */
    vgGetMatrix(xform);

    vgLoadIdentity();

    vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgSeti(VG_SCISSORING, VG_TRUE);

	bgCol[0] = 0.906f;
	bgCol[1] = 0.914f;
	bgCol[2] = 0.761f;
	bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0,0,WINDSIZEX,WINDSIZEY);

	/*  vgDrawPath  */
    vgLoadIdentity();
    vgTranslate(22,0);

	scissor1[0] = 33;
	scissor1[1] = 11;
	scissor1[2] = 8;
	scissor1[3] = 8;
	scissor1[4] = 23;
	scissor1[5] = 1;
	scissor1[6] = 14;
	scissor1[7] = 14;

    vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_SCISSORING, VG_FALSE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgLoadMatrix(xform);

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path, 4, cmds, coords);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgTranslate(18.f, -3.f);

    vgDrawPath(path, VG_FILL_PATH);

	/* vgDrawImage */
    vgLoadIdentity();
	vgTranslate(43, 0);

	scissor1[0] = 54;
	scissor1[1] = 11;
	scissor1[2] = 8;
	scissor1[3] = 8;
	scissor1[4] = 44;
	scissor1[5] = 1;
	scissor1[6] = 14;
	scissor1[7] = 14;

    vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_SCISSORING, VG_FALSE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);

    surf = vgCreateImage(VG_sRGBA_8888, surf_width, surf_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(surf, surf_data, surf_stride, VG_sRGBA_8888, 0, 0, surf_width, surf_height);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(55,2);
    vgRotate(45);
    vgTranslate(-11, -11);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgDrawImage(surf);

	/* vgSetPixels */

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgTranslate(0, 32);

	scissor1[0] = 11;
	scissor1[1] = 43;
	scissor1[2] = 8;
	scissor1[3] = 8;
	scissor1[4] = 1;
	scissor1[5] = 33;
	scissor1[6] = 14;
	scissor1[7] = 14;

    vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_SCISSORING, VG_FALSE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgSetPixels( -5, 20, surf, 0, 0, surf_width, surf_height);

	/* vgWritePixels */

    vgTranslate(22,0);

	scissor1[0] = 33;
	scissor1[1] = 43;
	scissor1[2] = 8;
	scissor1[3] = 8;
	scissor1[4] = 23;
	scissor1[5] = 33;
	scissor1[6] = 14;
	scissor1[7] = 14;

    vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_SCISSORING, VG_FALSE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgWritePixels( surf_data, surf_stride, VG_sRGBA_8888, 15, 20, surf_width, surf_height);

	/* vgCopyPixels */

    vgTranslate(21,0);

	scissor1[0] = 54;
	scissor1[1] = 43;
	scissor1[2] = 8;
	scissor1[3] = 8;
	scissor1[4] = 44;
	scissor1[5] = 33;
	scissor1[6] = 14;
	scissor1[7] = 14;

	vgSetiv(VG_SCISSOR_RECTS, 8, scissor1);
    vgSeti(VG_SCISSORING, VG_FALSE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgCopyPixels( 41, 32, 10, 35, surf_width, surf_height);
    vgDestroyPaint(fill);
    vgDestroyPath(path);
    vgDestroyImage(surf);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

