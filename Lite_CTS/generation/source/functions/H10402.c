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
#include "../util/st.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif


CT_Result H10402_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage img;
    VGfloat white[4];
    VGuint img_data[16];
    VGuint img_data2[16];
    VGint i;

	/* get OpenVG tie-break rule before changing the states */
	LOAD_TIE_BREAK_RULE_MATRIX();

    /* Try out the vgDrawImage drawing sampling position. */

    white[0] = 1;
    white[1] = 1;
    white[2] = 1;
    white[3] = 1;

    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

    img = vgCreateImage(VG_sRGBA_8888, 16, 16, VG_IMAGE_QUALITY_NONANTIALIASED);


    /* Solid bars */
    {
        VGuint temp[4] = {0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F};
        for (i = 0; i < 4; i++)
        {
            img_data[i] = temp[i];
        }
    }
    vgImageSubData(img, img_data, 0, VG_sRGBA_8888, 0, 0, 4, 4);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0, 0);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0.125f, 4);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0.375f, 12);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
	vgTranslate(0.5-0.0625f, 16);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0.625f, 20);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0.875f, 28);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(1.00f, 32);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(1.125f, 36);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(0, 0);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(4, 0.125f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 0.375f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
	vgTranslate(16, 0.5-0.0625f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(20, 0.625f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(28, 0.875f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(32, 1.00f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(36, 1.125f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);


    /* Vertical striped bars */
    {
        VGuint temp[4] = {0xFF00007F, 0x0000FF7F, 0xFF00007F, 0x0000FF7F};
        for (i = 0; i < 4; i++)
        {
            img_data[i] = temp[i];
        }
    }
    vgImageSubData(img, img_data, 0, VG_sRGBA_8888, 0, 0, 4, 4);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0.125f, 4);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0.375f, 12);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0.5f-0.0625f, 16);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0.625f, 20);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0.875f, 28);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(1.00f, 32);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(1.125f, 36);
    vgDrawImage(img);
    vgTranslate(4, 0);
    vgDrawImage(img);


    /* Horizontal striped bars */
    {
        VGuint temp[4] = {0xFF00007F, 0xFF00007F, 0xFF00007F, 0xFF00007F};
        for (i = 0; i < 4; i++)
        {
            img_data[i] = temp[i];
        }
    }
    {
        VGuint temp[4] = {0x0000FF7F, 0x0000FF7F, 0x0000FF7F, 0x0000FF7F};
        for (i = 0; i < 4; i++)
        {
            img_data2[i] = temp[i];
        }
    }
    vgImageSubData(img, img_data, 0, VG_sRGBA_8888, 0, 0, 4, 1);
    vgImageSubData(img, img_data2, 0, VG_sRGBA_8888, 0, 1, 4, 1);
    vgImageSubData(img, img_data, 0, VG_sRGBA_8888, 0, 2, 4, 1);
    vgImageSubData(img, img_data2, 0, VG_sRGBA_8888, 0, 3, 4, 1);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(0, 0);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(4, 0.125f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(12, 0.375f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(16, 0.5f-0.0625f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(20, 0.625f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(28, 0.875f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(32, 1.00f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    LOAD_TIE_BREAK_RULE_MATRIX();
    vgTranslate(12, 12);
    vgTranslate(36, 1.125f);
    vgDrawImage(img);
    vgTranslate(0, 4);
    vgDrawImage(img);

    vgDestroyImage(img);

    if (vgGetError() == VG_NO_ERROR) {
		FLIP_FRAME_BUFFER();
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

