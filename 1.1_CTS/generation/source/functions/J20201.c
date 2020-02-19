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

CT_Result J20201_FilterConvolve_by_HYBRID(CT_File *AnsFile, VGuint subtest)
{
    VGImage srcImg;
    VGImage dstImg;
    VGfloat bgCol[4];
    VGfloat red[4];
    VGfloat grey[4];
    VGfloat orange[4];
    VGfloat blue[4];
    VGfloat black[4];
    VGfloat white[4];
    VGshort identKernelX[3];
    VGshort identKernelY[3];

	/* Test separately behaviour of the each vgSeparableConvolve parameters. First
	 * shifts are used to translate the result image in resect to the
	 * source image. Next, kernel is used to achieve same results. Then
	 * bias and scale are tested separately for color channels and alpha
	 * channels. Both are also tested against gross under- and
	 * overflow. Finally each tiling mode is used.
	 */

	bgCol[0] = 0.906f;
	bgCol[1] = 0.914f;
	bgCol[2] = 0.761f;
	bgCol[3] = 1.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	red[0] = 0.6710f;
	red[1] = 0.1060f;
	red[2] = 0.1330f;
	red[3] = 1.0f;

	grey[0] = 0.6347f;
	grey[1] = 0.6561f;
	grey[2] = 0.6057f;
	grey[3] = 1.0f;

	orange[0] = 1.0000f;
	orange[1] = 0.8227f;
	orange[2] = 0.5057f;
	orange[3] = 1.0f;

	blue[0] = 0.0000f;
	blue[1] = 0.6908f;
	blue[2] = 0.8595f;
	blue[3] = 1.0f;

	black[0] = 0;
	black[1] = 0;
	black[2] = 0;
	black[3] = 1.0f;

	white[0] = 1;
	white[1] = 1;
	white[2] = 1;
	white[3] = 1.0f;

    vgSetfv(VG_TILE_FILL_COLOR, 4, blue);

	/* Affected channels to RGB instead of RGBA (Easier to check the results) */
    vgSeti(VG_FILTER_CHANNEL_MASK, 14);

	/* Setup images */
    srcImg = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED);
    dstImg = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED);

    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClearImage(srcImg, 0, 0, 32, 32);
    vgSetfv(VG_CLEAR_COLOR, 4, red);
    vgClearImage(srcImg, 2, 2, 28, 28);

    vgSetfv(VG_CLEAR_COLOR, 4, orange);
    vgClearImage(dstImg, 0, 0, 32, 32);

	/* Identity convolution */
	identKernelX[0] = 0;
	identKernelX[1] = 0;
	identKernelX[2] = 1;

	identKernelY[0] = 0;
	identKernelY[1] = 0;
	identKernelY[2] = 1;

    switch ( subtest )
    {
        case 0:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, 0, 0,
                identKernelX, identKernelY, 1.0f, 0, VG_TILE_FILL);
            break;
	    /* Test that results of Y shifting are as expected. */
        case 1:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, 0, 3, 
                identKernelX, identKernelY, 1, 0, VG_TILE_FILL);
            break;
	    /* Test that results of Y shifting are as expected. */
        case 2:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, 0, -3, 
                identKernelX, identKernelY, 1, 0, VG_TILE_FILL);
            break;
	    /* Test that results of X shifting are as expected. */
        case 3:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, 3, 0, 
                identKernelX, identKernelY, 1, 0, VG_TILE_FILL);
            break;
	    /* Test that results of X shifting are as expected. */
        case 4:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, -3, 0, 
                identKernelX, identKernelY, 1, 0, VG_TILE_FILL);
            break;
	    /* Combined shift */
        case 5:
            vgSeparableConvolve(dstImg, srcImg, 3, 3, 3, 3, 
                identKernelX, identKernelY, 1, 0, VG_TILE_FILL);
            break;
    }

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_IMAGE(dstImg);

        vgDestroyImage(dstImg);
        vgDestroyImage(srcImg);

        return CT_NO_ERROR;
    }
    else {
        vgDestroyImage(dstImg);
        vgDestroyImage(srcImg);

        return CT_ERROR;
    }
}

