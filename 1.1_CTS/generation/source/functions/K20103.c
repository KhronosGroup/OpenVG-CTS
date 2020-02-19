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

CT_Result K20103_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGfloat coords[] = {0.0f, 0.0f, 16.0f, 32.0f, -16.0f};
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_HLINE_TO_REL,
                          VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_CLOSE_PATH};
    VGPath rect;
    VGPaint fill;
    VGfloat backgound[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    static VGfloat rampStops[10] =
        {0.01f, 0.9f, 0.106f, 0.133f, 0.25f,
         0.95f, 0.1f, 0.9f,   0.8f,   0.90f};

    static VGfloat gradient[4] = {1.5f, 1.5f, 14.5f, 30.5f};

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    /* Rect setup */
    rect = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                        1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(rect, 5, commands, coords);

    /* Fill setup */
    fill = vgCreatePaint();
    vgSetParameteri(fill, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    vgSetParameterfv(fill, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgSetParameterfv(fill, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
    vgSetPaint(fill, VG_FILL_PATH);

    /* Background setup */
    vgSetfv(VG_CLEAR_COLOR, 4, backgound);
    vgClear(0, 0, 64, 64);

    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    
    /* Draw path over each region */
    {
        vgSeti(VG_COLOR_TRANSFORM, VG_FALSE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Identity color transformation */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Inverse color transformation */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Scale + bias color transformation */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {-2.0f, 4.0f, 4.0f, 4.0f, 1.0f, -1.0f, -1.0f, -1.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Set red channel */
    vgTranslate(-48, 32);
    {
        VGfloat values[] = {0.0f, 1.0f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, 0.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Set green channel */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.4f, 0.0f, 0.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Set blue channel */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.4f, 0.0f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    /* Set alpha channel */
    vgTranslate(16, 0);
    {
        VGfloat values[] = {1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.75f};
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    }
    vgDrawPath(rect, VG_FILL_PATH);

    vgDestroyPaint(fill);
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

