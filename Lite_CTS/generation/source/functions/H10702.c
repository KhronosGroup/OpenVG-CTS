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

CT_Result H10702_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage dst;
    VGfloat bgCol[4]	= {0.906f, 0.914f, 0.761f, 1.0f};
    VGfloat red[4]		= {1.0f, 0.0f, 0.0f, 1.0f};
    VGfloat green[4]	= {0.0f, 1.0f, 0.0f, 1.0f};
    VGfloat blue[4]		= {0.0f, 0.0f, 1.0f, 1.0f};
    VGfloat white[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
    VGfloat black[4]	= {0.0f, 0.0f, 0.0f, 1.0f};

	/* Test that vgGetPixels can copy in place, can handle clipping the
	/* source and destination rectangles when source or destination
	/* rectangle either starts or ends outside the surface. 
	 */

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Make a source image */
    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClear(0, 0, 32, 32);
    vgSetfv(VG_CLEAR_COLOR, 4, red);
    vgClear(0, 0, 14, 14);
    vgSetfv(VG_CLEAR_COLOR, 4, green);
    vgClear(16, 0, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, blue);
    vgClear(0, 16, 16, 16);
    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClear(18, 18, 14, 14);

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);

	/* Disable antialiasing */
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

	/* Create destination image */
    dst = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgClearImage(dst, 0, 0, 32, 32);

	/* Test copying in place. */
    vgGetPixels(dst, 1, 1, 1, 1, 30, 30);
    vgSetPixels(1, 1, dst, 1, 1, 30, 30);

	/* Source or destination coordinates below zero: */
    vgClearImage(dst, 0, 0, 32, 32);
    vgGetPixels(dst, 0, 16, -2, -2, 18, 18);
    vgGetPixels(dst, 16, -5, 16, 16, 16, 16);
    vgSetPixels(32, 0, dst, 0, 0, 32, 32);

	/* Source or destination rectangle over width/height */
    vgClearImage(dst, 0, 0, 32, 32);
    vgGetPixels(dst, 0, 16, 14, 0, 18, 18);
    vgClear(64, 0, 16, 16);
    vgGetPixels(dst, 0, 0, 48, 0, 32, 16);
    vgSetPixels(0, 32, dst, 0, 0, 32, 32);

	/* Try copying pixels completely from outside the surface */
    vgClearImage(dst, 0, 0, 32, 32);
    vgClear(64, 32, 32, 32);
    vgGetPixels(dst, 0, 0, 64, 32, 32, 32);
    vgSetPixels(32, 32, dst, 0, 0, 32, 32);

    vgDestroyImage(dst);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

