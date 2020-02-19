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

CT_Result K20102_ColorTransform_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    VGint i, j, k;
    VGImage gradient;
    VGPaint fill[2];
    VGuint gradient_data[256];
    VGfloat backgound[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    VGfloat fillColor1[4] = {0.9f, 0.8f, 0.7f, 0.6f};
    VGfloat fillColor2[4] = {0.6f, 0.7f, 0.8f, 0.9f};
    VGImageMode modes[] = {VG_DRAW_IMAGE_NORMAL, VG_DRAW_IMAGE_MULTIPLY, VG_DRAW_IMAGE_STENCIL};
    VGfloat transformations[7][8] =
        {
            {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.25f},
            {3.0f, 3.0f, 3.0f, 3.0f, -1.0f, -1.0f, -1.0f, -0.35f},
            {0.0f, 1.0f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.4f, 0.0f, 0.0f},
            {1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.4f, 0.0f},
            {1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.4f}
        };

    k = 0;
    for (i = 0; i < 16; i++)
    {
        VGint alpha = 64 + (i * 191) / 15;

        for (j = 0; j < 16; j++)
        {
            VGint color = (j * 255) / 15;
            gradient_data[k++] = alpha | (color * 0x01010100);
        }
    }

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    gradient = vgCreateImage(VG_sRGBA_8888, 16, 16, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageSubData(gradient, gradient_data, 64, VG_sRGBA_8888, 0, 0, 16, 16);

    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_IMAGE_MODE, modes[subtest]);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    /* Background setup */
    vgSetfv(VG_CLEAR_COLOR, 4, backgound);
    vgClear(0, 0, 64, 64);

    /* Fill setup */
    fill[0] = vgCreatePaint();
    vgSetParameteri(fill[0], VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(fill[0], VG_PAINT_COLOR, 4, fillColor1);
    fill[1] = vgCreatePaint();
    vgSetParameteri(fill[1], VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(fill[1], VG_PAINT_COLOR, 4, fillColor2);
    
    /* Draw image over each region */
    k = 0;
    for (i = 0; i < 4; i++)
    {
        vgSetPaint(fill[k / 8], VG_FILL_PATH);
        for (j = 0; j < 4; j++)
        {
            int type = k & 7;
            if (!type)
            {
                vgSeti(VG_COLOR_TRANSFORM, VG_FALSE);
            }
            else
            {
                vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
                vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, &transformations[type - 1][0]);
            }
            vgDrawImage(gradient);
            vgTranslate(16, 0);
            k++;
        }        
        vgTranslate(-64, 16);
    }

    vgDestroyImage(gradient);
    vgDestroyPaint(fill[0]);
    vgDestroyPaint(fill[1]);

    if (vgGetError() == VG_NO_ERROR)
    {
        DISPLAY_SUBTEST_BUFFER(subtest);
        return CT_NO_ERROR;
    }
    else
    {
        return CT_ERROR;
    }
}

