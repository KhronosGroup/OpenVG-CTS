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

CT_Result K20105_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGImage image;
    VGuint image_data[1024];
    VGfloat coords[] = {0.0f, 0.0f, 16.0f, 32.0f, -16.0f};
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_HLINE_TO_REL,
                          VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_CLOSE_PATH};
    VGPath rect;
    VGPaint gradientFill;
    VGPaint solidFill;
    VGfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    VGfloat fillColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    VGint i, j, k;
    
    static VGfloat rampStops[10] =
        {0.1f, 1.0f,  1.0f,  0.5f, 1.0f,
         0.9f, 0.25f, 0.25f, 0.5f, 1.0f};
         
    static VGfloat gradient[4] = {1.5f, 1.5f, 14.5f, 30.5f};


    k = 0;
    for (i = 0; i < 32; i++)
    {
        VGint alpha = 64 + (i * 191) / 31;

        for (j = 0; j < 16; j++)
        {
            VGint red = ((j - 8) * 511) / 15;
            VGint green = ((j - 24) * 511) / 15;
            if (red < 0)
                red = 0;
            if (green < 0)
                green = 0;

            image_data[k++] =
                red   * 0x01000000 +
                green * 0x00010000 +
                255   * 0x00000100 +
                alpha * 0x00000001;
        }
    }
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    image = vgCreateImage(VG_sRGBA_8888, 16, 32, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageSubData(image, image_data, 64, VG_sRGBA_8888, 0, 0, 16, 32);

    /* Rect setup */
    rect = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(rect, 5, commands, coords);

    /* Fill setup */
    solidFill = vgCreatePaint();
    vgSetParameteri(solidFill, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(solidFill, VG_PAINT_COLOR, 4, fillColor);
    vgSetPaint(solidFill, VG_FILL_PATH);

    /* Background setup */
    white[0] = 1;
    white[1] = 1;
    white[2] = 1;
    white[3] = 1;
    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClear(0, 0, 64, 64);

    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    /* Setup color transformation */
    {
        VGfloat values[] = {127.0f, -127.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }

    /* No image */
    vgDrawPath(rect, VG_FILL_PATH);

    /* VG_DRAW_IMAGE_MULTIPLY */
    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_MULTIPLY);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(16, 0);
    vgDrawImage(image);

    /* VG_DRAW_IMAGE_NORMAL */
    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(16, 0);
    vgDrawImage(image);

    /* VG_DRAW_IMAGE_STENCIL */
    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(16, 0);
    vgDrawImage(image);

    /* Gradient fill setup */
    gradientFill = vgCreatePaint();
    vgSetParameteri(gradientFill, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    vgSetParameterfv(gradientFill, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgSetParameterfv(gradientFill, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
    vgSetPaint(gradientFill, VG_FILL_PATH);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgTranslate(0, 32);
    vgDrawPath(rect, VG_FILL_PATH);

    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_MULTIPLY);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(-32, 32);
    vgDrawImage(image);

    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(16, 0);
    vgDrawImage(image);

    vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgTranslate(16, 0);
    vgDrawImage(image);

    vgDestroyImage(image);
    vgDestroyPaint(solidFill);
    vgDestroyPaint(gradientFill);
    vgDestroyPath(rect);

    if (vgGetError() == VG_NO_ERROR)
    {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else
    {
        return CT_ERROR;
    }
}

