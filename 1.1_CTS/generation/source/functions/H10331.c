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

static const VGImageFormat image_format_table[] =
{
  VG_sRGBX_8888                               ,
  VG_sRGBA_8888                               ,
  VG_sRGBA_8888_PRE                           ,
  VG_sRGB_565                                 ,
  VG_sRGBA_5551                               ,
  VG_sRGBA_4444                               ,
  /* Bugzilla Bug 4110 - Subtest 6 of H10331 should be moved out as separate test case */
  /* VG_sL_8                                     ,*/
  VG_lRGBX_8888                               ,
  VG_lRGBA_8888                               ,
  VG_lRGBA_8888_PRE                           ,
  VG_lL_8                                     ,
  VG_BW_1                                     ,
  VG_sXRGB_8888                               ,
  VG_sARGB_8888                               ,
  VG_sARGB_8888_PRE                           ,
  VG_sARGB_1555                               ,
  VG_sARGB_4444                               ,
  VG_lXRGB_8888                               ,
  VG_lARGB_8888                               ,
  VG_lARGB_8888_PRE                           ,
  VG_sBGRX_8888                               ,
  VG_sBGRA_8888                               ,
  VG_sBGRA_8888_PRE                           ,
  VG_sBGR_565                                 ,
  VG_sBGRA_5551                               ,
  VG_sBGRA_4444                               ,
  VG_lBGRX_8888                               ,
  VG_lBGRA_8888                               ,
  VG_lBGRA_8888_PRE                           ,
  VG_sXBGR_8888                               ,
  VG_sABGR_8888                               ,
  VG_sABGR_8888_PRE                           ,
  VG_sABGR_1555                               ,
  VG_sABGR_4444                               ,
  VG_lXBGR_8888                               ,
  VG_lABGR_8888                               ,
  VG_lABGR_8888_PRE                           ,
  VG_A_8                                      ,
  VG_A_1                                      ,
  VG_A_4                                      
};

CT_Result H10331_ImageConversion_by_ATI(CT_File *AnsFile, VGuint subtest)
{
    VGImage image_src;
    VGImage image_dst;
    VGImageFormat src_format = VG_sRGBA_8888;
    VGImageFormat dst_format;
    VGfloat bgCol[4] = {1.0f, 1.0f, 1.0f, 1.0f};


    /*  Clear the drawing surface */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();

    dst_format = image_format_table[subtest];

    image_src = vgCreateImage(src_format, pukki_64x64_width, pukki_64x64_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(image_src, pukki_64x64_data, pukki_64x64_stride, src_format, 0, 0, pukki_64x64_width, pukki_64x64_height);
    image_dst = vgCreateImage(dst_format, pukki_64x64_width, pukki_64x64_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    
    vgCopyImage(image_dst, 0, 0, image_src, 0, 0, pukki_64x64_width, pukki_64x64_height, VG_FALSE);

    if (vgGetError() == VG_NO_ERROR) {
        SAVE_SUBTEST_IMAGE(subtest, image_dst);
        vgDestroyImage(image_dst);
        vgDestroyImage(image_src);
        return CT_NO_ERROR;
    }
    else {
        vgDestroyImage(image_dst);
        vgDestroyImage(image_src);
        return CT_ERROR;
    }
}

