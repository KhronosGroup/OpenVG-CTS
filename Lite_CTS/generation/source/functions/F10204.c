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

CT_Result F10204_MaskingOperation_by_HYBRID(CT_File *AnsFile)
{
	VGPaint fill;
	VGImage maskImg;
    VGPath box;
	VGfloat color[4]		= {0.f, 0.f, 0.f, 1.f};
    VGfloat bgCol[4]		= {0.906f, 0.914f, 0.761f, 1.0f};
    VGubyte maskData[256];
	
	/* Test that mask clearing and filling use correct values. Test that
	 * setting a value between filled or cleared mask gives visually
	 * reasonable results. Test that all operations, setting, union,
	 * intersection and subtraction work as expected.
	 */

	/* Background clear */
    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, color);
    vgSetPaint(fill, VG_FILL_PATH);

	vgSeti(VG_MASKING, VG_TRUE);
	vgLoadIdentity();

    box = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);

	/* Rectangle to cover completely 16x16 pixel area. */

    DrawRect_by_HYBRID(box, 0, 0, 16, 16);

    maskImg = vgCreateImage(VG_BW_1, 16, 16, VG_IMAGE_QUALITY_NONANTIALIASED);
	{ 
		int i;
	    for (i = 0; i < (sizeof(maskData)/sizeof(VGubyte)); i++)
	    {
	        maskData[i] = (VGubyte)255;
	    }
	}

	vgClearImage(maskImg, 0, 0, 16, 16);
	vgImageSubData(maskImg, maskData, 16, VG_A_8, 5, 5, 6, 6);

	/* Stop bleeding */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

	/* Mask rectangle clipping: */

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
	vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

    vgMask(maskImg, VG_FILL_MASK, 0, 0, 256, 256);

	/* X below zero */
    vgMask(maskImg, VG_SET_MASK, -5, 24, 16, 16);
	
    vgLoadIdentity();
    vgTranslate(0, 24);
    vgDrawPath(box, VG_FILL_PATH);

	/* Y below zero */
    vgMask(maskImg, VG_SET_MASK, 24, -5, 16, 16);

    vgLoadIdentity();
    vgTranslate(24, 0);
    vgDrawPath(box, VG_FILL_PATH);

	/* Rectangle exceeds surface width/height */
    vgMask(maskImg, VG_SET_MASK, 53, 24, 16, 16);

    vgLoadIdentity();
    vgTranslate(48, 24);
	vgDrawPath(box, VG_FILL_PATH);

    vgMask(maskImg, VG_SET_MASK, 24, 53, 16, 16);

    vgLoadIdentity();
    vgTranslate(24,	48);
    vgDrawPath(box, VG_FILL_PATH);

	/* Rectangle exceeds image width/height */
    vgMask(maskImg, VG_CLEAR_MASK, 16, 16, 32, 32);
    vgMask(maskImg, VG_SET_MASK, 16, 16, 32, 32);

    vgLoadIdentity();
    vgTranslate(16, 32);
    vgDrawPath(box, VG_FILL_PATH);

    vgMask(maskImg, VG_FILL_MASK, 16, 16, 32, 32);
    vgMask(maskImg, VG_SET_MASK, 16, 16, 32, 32);

    vgLoadIdentity();
    vgTranslate(32, 32);
    vgDrawPath(box, VG_FILL_PATH);

    vgDestroyImage(maskImg);
    vgDestroyPaint(fill);
    vgDestroyPath(box);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

