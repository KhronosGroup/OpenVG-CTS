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
#include "../static/hybrid/mipmap_yoda.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result H10403_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage mipmapyoda;

    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    mipmapyoda = vgCreateImage(VG_sRGBA_8888, 64, 64,
		VG_IMAGE_QUALITY_NONANTIALIASED | VG_IMAGE_QUALITY_FASTER | VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(mipmapyoda, mipmap_yoda_data, 256, VG_sRGBA_8888, 0, 0, 64, 64);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);

	/* Draw the mipmap on the bottom row */
    vgLoadIdentity();
    vgTranslate(0, 0);
    vgScale(0.5f, 0.5f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(32, 0);
    vgScale(0.25f, 0.25f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(48, 0);
    vgScale(0.125f, 0.125f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(56, 0);
    vgScale(0.0625f, 0.0625f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(60, 0);
    vgScale(0.03125f, 0.03125f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(62, 0);
    vgScale(0.015625f, 0.015625f);
    vgDrawImage(mipmapyoda);

	/*	draw the mipmaps on the top row,
	 *	this time with not-so-convenient scales
	 */
    vgLoadIdentity();
    vgTranslate(0, 32);
    vgScale(0.48f, 0.48f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(32, 32);
    vgScale(0.225f, 0.225f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(48, 32);
    vgScale(0.115f, 0.115f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(56, 32);
    vgScale(0.0525f, 0.0525f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(60, 32);
    vgScale(0.03025f, 0.03025f);
    vgDrawImage(mipmapyoda);

    vgLoadIdentity();
    vgTranslate(62, 32);
    vgScale(0.01562f, 0.01562f);
    vgDrawImage(mipmapyoda);

    vgDestroyImage(mipmapyoda);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

