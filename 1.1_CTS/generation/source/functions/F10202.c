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

CT_Result F10202_MaskingOperation_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPaint fill;
    VGImage maskImg;
    VGPath box;
    VGfloat bgCol[4]		= {1.f, 1.f, 1.f, 1.f};
    VGfloat alpha1[4]		= {0, 0, 0, 1};
    VGfloat alpha0[4]		= {0, 0, 0, 0};
    VGfloat alpha025[4]		= {0, 0, 0, 0.25f};
    VGfloat alpha05[4]		= {0, 0, 0, 0.5f};
    VGfloat color1[4]		= {0.f, 0.f, 0.f, 0.f};
    VGfloat color2[4]		= {0.f, 0.f, 0.f, 1.f};
    VGubyte maskData[256];

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
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

    stroke = vgCreatePaint();

    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, color2);
    vgSetPaint(fill, VG_FILL_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH, 6);
    vgSeti(VG_MASKING, VG_TRUE);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgLoadIdentity();

    maskImg = vgCreateImage(VG_A_8, 16, 16, VG_IMAGE_QUALITY_NONANTIALIASED);

	/* Alpha 0.f */
	{ 
		int i;
	    for (i = 0; i < (sizeof(maskData)/sizeof(VGubyte)); i++)
	    {
	        maskData[i] = (VGubyte)0;
	    }
	}

    vgImageSubData(maskImg, maskData, 16, VG_A_8, 0, 0, 16, 16);

	/* Rectangle for filling the test areas. */
    box = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);

	/* Rectangle to cover completely 16x16 pixel area. */
    DrawRect_by_HYBRID(box, 0, 0, 16, 16);

	/* Four sample gradient from clear mask to fill mask */
	/* alpha 0 */
    vgMask(maskImg, VG_CLEAR_MASK, 0, 8, 16, 16);
    vgTranslate(0, 8);
    vgDrawPath(box, VG_FILL_PATH);

	/* Alpha 0.333f */
    vgMask(maskImg, VG_SET_MASK, 16, 8, 16, 16);
    vgTranslate(16,0);
    vgDrawPath(box, VG_FILL_PATH);

	/* Alpha 0.666f */
	{
		int i;
		for (i = 0; i < (sizeof(maskData)/sizeof(VGubyte)); i++)
		{
			maskData[i] = (VGubyte)255;
		}
	}

    vgImageSubData(maskImg, maskData, 16, VG_A_8, 0, 0, 16, 16);
    vgMask(maskImg, VG_SET_MASK, 32, 8, 16, 16);
    vgTranslate(16,0);
    vgDrawPath(box, VG_FILL_PATH);

	/* Alpha 1 */
    vgMask(maskImg, VG_FILL_MASK, 48, 8, 16, 16);
    vgTranslate(16,0);
    vgDrawPath(box, VG_FILL_PATH);

	/* One rectangle set mask */
    vgSetfv(VG_CLEAR_COLOR, 4, alpha0);
    vgClearImage(maskImg, 0, 0, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, alpha1);
    vgClearImage(maskImg, 5, 5, 6, 6);

    vgMask(maskImg, VG_SET_MASK, 0, 40, 16, 16);
    vgTranslate(-48, 32);
    vgDrawPath(box, VG_FILL_PATH);

	/* Union two overlapping rectangles */
    vgSetfv(VG_CLEAR_COLOR, 4, alpha025);
	vgClearImage(maskImg, 5, 5, 6, 6);
    vgMask(maskImg, VG_CLEAR_MASK, 16, 40, 16, 16);
    vgMask(maskImg, VG_UNION_MASK, 15, 39, 16, 16);
    vgMask(maskImg, VG_UNION_MASK, 18, 42, 16, 16);

    vgTranslate(16, 0);
    vgDrawPath(box, VG_FILL_PATH);

	/* Intersect two overlapping rects */
    vgSetfv(VG_CLEAR_COLOR, 4, alpha05);
    vgClearImage(maskImg, 5, 5, 6, 6);
    vgMask(maskImg, VG_FILL_MASK, 32, 40, 16, 16);
    vgMask(maskImg, VG_INTERSECT_MASK, 31, 39, 16, 16);
    vgMask(maskImg, VG_INTERSECT_MASK, 34, 42, 16, 16);

    vgTranslate(16, 0);
    vgDrawPath(box, VG_FILL_PATH);

	/* Subtract two overlapping rects */
    vgMask(maskImg, VG_CLEAR_MASK, 48, 40, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, alpha1);
    vgClearImage(maskImg, 5, 5, 6, 6);
    vgMask(maskImg, VG_SET_MASK, 47, 39, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, alpha025);
    vgClearImage(maskImg, 5, 5, 6, 6);
    vgMask(maskImg, VG_SUBTRACT_MASK, 50, 42, 16, 16);

    vgTranslate(16, 0);
    vgDrawPath(box, VG_FILL_PATH);

    vgDestroyImage(maskImg);
    vgDestroyPaint(stroke);
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

