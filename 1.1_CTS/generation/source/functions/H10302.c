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

CT_Result H10302_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage img;
    VGfloat bgCol[4]	= {0.906f, 0.914f, 0.761f, 1.0f};
    VGfloat red[4]		= {1.f, 0.f, 0.f, 1.f};
    VGfloat green[4]	= {0.f, 1.f, 0.f, 1.f};
    VGfloat blue[4]		= {0.f, 0.f, 1.f, 1.f};
    VGfloat white[4]	= {1.f, 1.f, 1.f, 1.f};
    VGfloat black[4]	= {0.f, 0.f, 0.f, 1.f};

	/*  Copies images to check what happens when: a) Image is copied
	 *  in-place, b) Image destination or source coordinates are below zero,
	 *  c) Image destination or source rectangle exceeds the image width or
	 *  height and d) what happens if destination or source region is
	 *  outside the image completely.  
	 *  NOTE: Designed for 256 X 256 surface
	*/


	/* Background clear */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Setup matrix mode */
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
	
	/* Disable antialiasing */
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

	/* Use VG_sRGBA_8888 to avoid format conversions */
    img = vgCreateImage(VG_sRGBA_8888, 128, 128, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClearImage(img, 0, 0, 32, 32);
    vgSetfv(VG_CLEAR_COLOR, 4, red);
    vgClearImage(img, 0, 0, 14, 14);
    vgSetfv(VG_CLEAR_COLOR, 4, green);
    vgClearImage(img, 16, 0, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, blue);
    vgClearImage(img, 0, 16, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClearImage(img, 18, 18, 16, 16);


	/* Test copying in-place. */
    vgCopyImage(img, 1, 1, img, 1, 1, 30, 30, VG_FALSE);
    vgDrawImage(img);

/*  Source or destination coordinates below zero:
 */
    vgTranslate(32, 0);
    vgCopyImage(img, 0, 16, img, -2, -2, 16, 16, VG_FALSE);
    vgCopyImage(img, 16, -2, img, 16, 16, 16, 16, VG_FALSE);
    vgDrawImage(img);

/*  Source or destination rectangle exceeds width or height
 */
    vgTranslate(-32, 32);

/*  Reset image
 */
    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClearImage(img, 0, 0, 32, 32);
    vgSetfv(VG_CLEAR_COLOR, 4, red);
    vgClearImage(img, 0, 0, 14, 14);
    vgSetfv(VG_CLEAR_COLOR, 4, green);
    vgClearImage(img, 16, 0, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, blue);
    vgClearImage(img, 0, 16, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClearImage(img, 18, 18, 16, 16);

    vgCopyImage(img, 0, 0, img, 0, 18, 16, 16, VG_FALSE);
    vgCopyImage(img, 18, 16, img, 16, 0, 16, 16, VG_FALSE);
    vgDrawImage(img);

/*  Copying to outside image and from outside image completely
 */
    vgTranslate(32, 0);

/*  Reset image
 */
    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClearImage(img, 0, 0, 32, 32);
    vgSetfv(VG_CLEAR_COLOR, 4, red);
    vgClearImage(img, 0, 0, 14, 14);
    vgSetfv(VG_CLEAR_COLOR, 4, green);
    vgClearImage(img, 16, 0, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, blue);
    vgClearImage(img, 0, 16, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClearImage(img, 18, 18, 16, 16);

    vgCopyImage(img, -12, -12, img, 0, 18, 7, 7, VG_FALSE);
    vgCopyImage(img, 46, 16, img, 16, 0, 16, 16, VG_FALSE);
    vgDrawImage(img);

    vgDestroyImage(img);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

