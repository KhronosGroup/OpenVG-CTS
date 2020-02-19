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
#include "../static/hybrid/pukki_16x16.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result F10203_MaskingOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage maskImg, pukki_16x16;
    VGPath ellipse;
    VGfloat bgCol[4]		= {0.906f, 0.914f, 0.761f, 1.0f};
    VGfloat alpha1[4]		= {0, 0, 0, 1};
	VGPaint fill, stroke;
    VGfloat color1[4]		= {0.671f, 0.106f, 0.133f, 0.65f};
    VGfloat color2[4]		= {0.6347f, 0.6561f, 0.6057f, 1.0f};

	/* Test that mask clearing and filling use correct values. Test that
	 * setting a value between filled or cleared mask gives visually
	 * reasonable results. Test that all operations, setting, union,
	 * intersection and subtraction work as expected. Test that path
	 * stroking and filling and image drawing are affected by masking and
	 * the clearing and pixel transfer operations are not. Test that
	 * clipping of the destination and source rectangles in the masking
	 * calls behaves as expected.
	 */

	/* Background clear */
	stroke = vgCreatePaint();
    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    fill = vgCreatePaint();
	vgSetParameterfv(fill, VG_PAINT_COLOR, 4, color2);
    vgSetPaint(fill, VG_FILL_PATH);

	vgSetf(VG_STROKE_LINE_WIDTH, 1);
	vgSeti(VG_MASKING, VG_TRUE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);

    maskImg = vgCreateImage(VG_BW_1, 16, 16, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgClearImage(maskImg, 0, 0, 16, 16);

    pukki_16x16 = vgCreateImage(VG_BW_1, pukki_16x16_width, pukki_16x16_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(pukki_16x16, pukki_16x16_data, pukki_16x16_stride, VG_sRGBA_8888, 0, 0, pukki_16x16_width, pukki_16x16_height);

    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_BETTER);

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

	/* - Fill&Stroke affected */
	vgMask(pukki_16x16, VG_SET_MASK, 4, 8, 16, 16);

    ellipse = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_16, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    DrawEllipse_by_HYBRID(ellipse, 0, 0, 16, 7);

	vgLoadIdentity();
    vgTranslate(12, 16);
    vgRotate(-45);

    vgDrawPath(ellipse, VG_FILL_PATH|VG_STROKE_PATH);

	/* Draw Image affected */
    vgSetfv(VG_CLEAR_COLOR, 4, alpha1);
    vgClearImage(maskImg, 5, 5, 6, 6);
    vgMask(maskImg, VG_SET_MASK, 24, 8, 16, 16);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(24, 8);
    vgDrawImage(pukki_16x16);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	/* clear not affected. */
    vgMask(maskImg, VG_SET_MASK, 44, 8, 16, 16);
    vgClear(44, 8, 16, 16);

	/* vgSetPixels not affected */
    vgMask(maskImg, VG_SET_MASK, 4, 40, 16, 16);
    vgSetPixels( 4, 40, pukki_16x16, 0, 0, 16, 16);

	/* vgWritePixels not affected */
    vgMask(maskImg, VG_SET_MASK, 24, 40, 16, 16);
    vgWritePixels(pukki_16x16_data, pukki_16x16_stride, VG_sRGBA_8888, 24, 40, 16, 16);

	/* vgCopyPixels not affected */
    vgMask(maskImg, VG_SET_MASK, 44, 40, 16, 16);
    vgCopyPixels( 44, 40, 24, 40, 16, 16);

    vgDestroyPaint(stroke);
    vgDestroyPaint(fill);
    vgDestroyImage(maskImg);
    vgDestroyImage(pukki_16x16);
    vgDestroyPath(ellipse);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

