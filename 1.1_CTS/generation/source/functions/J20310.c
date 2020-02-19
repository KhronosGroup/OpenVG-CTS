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
#include "../static/hybrid/red_black_box_64x64.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result J20310_FilterConvolve_by_HYBRID(CT_File *AnsFile)
{
    VGImage combo_image;
    VGImage blurred;
    VGfloat col[4];

	/* This test case checks that the vgGaussianBlur works in the basic cases
	 * with tiling mode "reflect"
	 * Also: source and target are of same size and the standard deviations
	 * are equal on y- and x-axes. The image contains different kinds of features.
	 */

	col[0] = 0;
	col[1] = 0;
	col[2] = 0;
	col[3] = 1;
    vgSetfv(VG_CLEAR_COLOR, 4, col);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    combo_image = vgCreateImage(VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(combo_image, red_black_box_64x64_data, 256, VG_sRGBA_8888, 0, 0, 64, 64);

	/* Target image */
    blurred = vgCreateImage(VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER);

    vgGaussianBlur(blurred, combo_image, 1.0f, 1.0f, VG_TILE_REFLECT);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_IMAGE(blurred);

        vgDestroyImage(combo_image);
        vgDestroyImage(blurred);

        return CT_NO_ERROR;
    }
    else {
        vgDestroyImage(combo_image);
        vgDestroyImage(blurred);

        return CT_ERROR;
    }
}

