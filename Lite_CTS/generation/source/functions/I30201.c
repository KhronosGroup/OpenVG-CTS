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

CT_Result I30201_PaintGradient_by_HYBRID(CT_File *AnsFile)
{
    VGPaint paint;
    VGPath path;
    VGfloat bgCol[4];
    VGfloat rampStops[10];
    VGfloat gradient[4];
    VGint i;

    /* Test linear gradient when gradient is larger than the area it's being drawn to */

    /*  Render the scene with no antialiasing */
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    /* Clear the drawing surface */
    {
        VGfloat temp[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        for (i = 0; i < 4; i++)
        {
            bgCol[i] = temp[i];
        }
    }
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgLoadIdentity();

    /* Create a paint for the fill */
    paint = vgCreatePaint();
    {
        VGfloat temp[10] = {0,0,0,0,1, 1,1,1,1,1};
        for (i = 0; i < 10; i++)
        {
            rampStops[i] = temp[i];
        }
    }

    {
        VGfloat temp[4] = {-2560, 0, 2560, 0};
        for (i = 0; i < 4; i++)
        {
            gradient[i] = temp[i];
        }
    }
    
    vgSetParameteri(paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD);
    vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    vgSetParameterfv(paint, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgSetParameterfv(paint, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
    vgSetPaint(paint, VG_FILL_PATH);

    /* Create the path of the box */
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 4, 4, VG_PATH_CAPABILITY_ALL);
    DrawRect_by_HYBRID(path,  0, 0, 64, 32);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
    vgScale(0.0125f, 0.0125f);
    vgTranslate(2560, 0);
    vgDrawPath(path, VG_FILL_PATH);

    /* Set another spread mode */
    vgSetParameteri(paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REPEAT);

    /* Create the path of the box */
    {
        VGfloat temp[10] = {0,1,1,1,1, 1,0,0,1,1};
        for (i = 0; i < 10; i++)
        {
            rampStops[i] = temp[i];
        }
    }
    vgSetParameterfv(paint, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgDestroyPath(path);
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 4, 4, VG_PATH_CAPABILITY_ALL);
    DrawRect_by_HYBRID(path,  0, 32, 64, 32);
    vgDrawPath(path, VG_FILL_PATH);

    vgDestroyPaint(paint);
    vgDestroyPath(path);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

