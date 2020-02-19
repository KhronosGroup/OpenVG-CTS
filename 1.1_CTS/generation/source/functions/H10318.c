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
#include "../static/hybrid/gradient.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result H10318_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage src;
    VGImage dst;   
    VGfloat bgCol[4] = {0.906f, 0.914f, 0.761f, 1.0f};

    /* Copies an image of a certain type to destinations with all possible 
       image formats (including only the basic types specified with OpenVG) */

    /* Clear background */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, 256, 256);

    /* Create the destination image */
    dst = vgCreateImage(VG_lL_8, gradient_width, gradient_height*13, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_BETTER);

    /* Create the source image for every image format and copy it to the destination */

    /* Dst format VG_sRGBA_8888 */
    src = vgCreateImage(VG_sRGBA_8888, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_sRGBA_8888, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 0, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sRGBX_8888 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sRGBX_8888, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_sRGBX_8888, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 18, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sRGBA_8888_PRE */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sRGBA_8888_PRE, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_sRGBA_8888_PRE, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 36, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sRGB_565 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sRGB_565, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_565, gradient_stride_565, VG_sRGB_565, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 54, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sRGBA_5551 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sRGBA_5551, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_5551, gradient_stride_5551, VG_sRGBA_5551, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 72, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sRGBA_4444 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sRGBA_4444, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_4444, gradient_stride_4444, VG_sRGBA_4444, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 90, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_sL_8 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_sL_8, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_8, gradient_stride_8, VG_sL_8, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 108, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_lRGBA_8888 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_lRGBA_8888, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_lRGBA_8888, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 126, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_lRGBX_8888 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_lRGBX_8888, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_lRGBX_8888, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 144, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_lRGBA_8888_PRE */
    vgDestroyImage(src);
    src = vgCreateImage(VG_lRGBA_8888_PRE, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data, gradient_stride, VG_lRGBA_8888_PRE, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 162, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_lL_8 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_lL_8, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_8, gradient_stride_8, VG_lL_8, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 180, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_A_8 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_A_8, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_8, gradient_stride_8, VG_A_8, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 198, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    /* Dst format VG_A_4 */
    vgDestroyImage(src);
    src = vgCreateImage(VG_A_4, gradient_width, gradient_height, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(src, gradient_data_4, gradient_stride_4, VG_A_4, 0, 0, gradient_width, gradient_height);
    vgCopyImage(dst, 0, 216, src, 0, 0, gradient_width, gradient_height, VG_FALSE);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_IMAGE(dst);
        
        vgDestroyImage(dst);
        vgDestroyImage(src);

        return CT_NO_ERROR;
    }
    else {
        vgDestroyImage(dst);
        vgDestroyImage(src);

        return CT_ERROR;
    }
}

