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
#include "../static/hybrid/pukki_64x64.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result H10329_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage pukki_src;
    VGImage pukki_dst;
	VGfloat bgCol[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    pukki_src = vgCreateImage(VG_sRGBA_8888, pukki_64x64_width, pukki_64x64_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(pukki_src, pukki_64x64_data, pukki_64x64_stride, VG_sRGBA_8888, 0, 0, pukki_64x64_width, pukki_64x64_height);

	/*  Clear the drawing surface */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();

/*  ------------------------------------------------------------------
 *
 *  Source and destination are different images
 *
 *  ------------------------------------------------------------------ */

	/* Copy two portions of the original image to the destination and draw it */
    pukki_dst = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgCopyImage(pukki_dst, 0, 16, pukki_src, 16, 16, 64, 64, VG_FALSE);
    vgCopyImage(pukki_dst, 16, 16, pukki_src, 26, 26, 32, 32, VG_FALSE);
    vgDrawImage(pukki_dst);

	/* Copy a non-symmetrical part of the image to the destination */
    vgDestroyImage(pukki_dst);
    pukki_dst = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgCopyImage(pukki_dst, 0, 0, pukki_src, 30, 25, 64, 64, VG_FALSE);
    vgTranslate(0, 32);
    vgDrawImage(pukki_dst);

	/*  Copy multiple parts of the source to the destination overlappig each other in the destination */
    vgDestroyImage(pukki_dst);
    pukki_dst = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgCopyImage(pukki_dst, 0, 0, pukki_src, 16, 16, 8, 35, VG_FALSE);
    vgCopyImage(pukki_dst, 0, 16, pukki_src, 16, 32, 40, 16, VG_FALSE);
    vgCopyImage(pukki_dst, 16, 16, pukki_src, 32, 32, 26, 26, VG_FALSE);
    vgCopyImage(pukki_dst, 18, 0, pukki_src, 34, 16, 26, 26, VG_FALSE);
    vgCopyImage(pukki_dst, 5, 18, pukki_src, 21, 34, 5, 5, VG_FALSE);
    vgLoadIdentity();
    vgTranslate(32, 32);
    vgDrawImage(pukki_dst);

	/* Copy the whole image */
    vgDestroyImage(pukki_dst);
    pukki_dst = vgCreateImage(VG_sRGBA_8888, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgCopyImage(pukki_dst, 0, 0, pukki_src, 0, 0, 64, 64, VG_FALSE);
    vgLoadIdentity();
    vgTranslate(32, 0);
    vgDrawImage(pukki_dst);

    vgDestroyImage(pukki_src);
    vgDestroyImage(pukki_dst);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

