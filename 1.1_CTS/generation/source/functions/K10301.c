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

CT_Result K10301_BlendingStencil_by_HYBRID(CT_File *AnsFile, VGuint subtest)
{
    VGImage gradient;
    VGuint gradient_data[1024];
    VGfloat white[4];
    VGfloat black[4];
    VGfloat grey[4];
    VGint i, j, k;

	k = 0;
	for (i = 0; i < 32; i++)
	{
		VGint alpha = ((i < 4)? 0 : (i * 255) / 31);

		for (j = 0; j < 32; j++)
		{
			VGint color = (j * 255) / 31;
			gradient_data[k++] = alpha | (color * 0x01010100);
		}
	}

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);

	/* Background setup */
	white[0] = 1;
	white[1] = 1;
	white[2] = 1;
	white[3] = 1;

	black[0] = 0;
	black[1] = 0;
	black[2] = 0;
	black[3] = 0;

	grey[0] = 0.5f;
	grey[1] = 0.5f;
	grey[2] = 0.5f;
	grey[3] = 0.5f;

	/* Draw image over each region */
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC + subtest);
    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    vgSetfv(VG_CLEAR_COLOR, 4, grey);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    gradient = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageSubData(gradient, gradient_data, 128, VG_sRGBA_8888, 0, 0, 32, 32);

	/* Setup background */
    vgSetPixels(0, 0, gradient, 0, 0, 32, 32);
    vgSetPixels(32, 0, gradient, 0, 0, 32, 32);
    vgSetPixels(0, 32, gradient, 0, 0, 32, 32);
    vgSetPixels(32, 32, gradient, 0, 0, 32, 32);

	/* Draw the image in four orientations */
    vgLoadIdentity();
    vgDrawImage(gradient);

    vgLoadIdentity();
    vgTranslate(32, 32);
    vgRotate(-90);
    vgDrawImage(gradient);

    vgLoadIdentity();
    vgTranslate(32, 64);
    vgRotate(-180);
    vgDrawImage(gradient);

    vgLoadIdentity();
    vgTranslate(64, 32);
    vgRotate(-270);
    vgDrawImage(gradient);

    vgDestroyImage(gradient);
	
    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

