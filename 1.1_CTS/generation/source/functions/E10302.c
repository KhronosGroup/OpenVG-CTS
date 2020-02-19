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
#include "../static/hybrid/mobile_man.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result  E10302_ScissoringOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage mobile_man;
	
	/* 32 scissoring rectangles which cover the whole screen */
    VGint scissor_rect[128] = {
		/* The first 16 are tightly packed, except for the 8 highest ones which have the topmost pixel missing */
		0,  0, 8,16,   8,  0, 8,16,
		16, 0, 8,16,   24, 0, 8,16,
		32, 0, 8,16,   40, 0, 8,16,
		48, 0, 8,16,   56, 0, 8,16,
		0,  16,8,15,   8,  16,8,15,
		16, 16,8,15,   24, 16,8,15,
		32, 16,8,15,   40, 16,8,15,
		48, 16,8,15,   56, 16,8,15,

		/* The last 16 have one pixel wide cap between them */
		0,  32,7,15,   8,  32,7,15,
		16, 32,7,15,   24, 32,7,15,
		32, 32,7,15,   40, 32,7,15,
		48, 32,7,15,   56, 32,7,15,
		0,  48,7,15,   8,  48,7,15,
		16, 48,7,15,   24, 48,7,15,
		32, 48,7,15,   40, 48,7,15,
		48, 48,7,15,   56, 48,7,15 };

	VGfloat clearColor[4] = { 1.f, 1.f, 1.f, 1.f };

	/* Tests scissoring in a case where the whole sceen is covered with
	 * the maximum number of scissoring rectangles
	 */

	/* Clear the drawing surface */

	vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Generate the image with no antialiasing and turn scissoring on */

    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_SCISSORING, VG_TRUE);
    vgSetiv(VG_SCISSOR_RECTS, 128, scissor_rect);

    mobile_man = vgCreateImage(VG_sRGBA_8888, mobile_man_width, mobile_man_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(mobile_man, mobile_man_data, mobile_man_stride, VG_sRGBA_8888, 0, 0, mobile_man_width, mobile_man_height);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgDrawImage(mobile_man);

	vgDestroyImage(mobile_man);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

