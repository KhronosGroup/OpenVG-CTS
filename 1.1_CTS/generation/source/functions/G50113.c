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

CT_Result G50113_PathFilling_by_HYBRID(CT_File *AnsFile)
{
    VGPath  path;
    VGPaint stroke;
    VGPaint fill;
    VGfloat bgCol[4]        = {1.f, 1.f, 1.f, 1.f};
    VGfloat xformStore[9]   = {0.f, 0.f, 0.f, 
                               0.f, 0.f, 0.f, 
                               0.f, 0.f, 0.f};
    VGfloat color1[4]       = {1.f, 0.f, 0.f, 1.f};
    VGfloat color2[4]       = {0.f, 1.f, 0.f, 1.f};
    VGint   i;
    VGubyte cmds[6]         = {VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, 
                               VG_CUBIC_TO_ABS, VG_CUBIC_TO_ABS, 
                               VG_CUBIC_TO_ABS, VG_CLOSE_PATH};

    VGfloat coords[26]      = {0.25f,  0.25f,  0.45f, 
                               1.55f,  0.45f, -0.55f, 
                               0.25f,  0.75f,  1.55f, 
                               0.55f, -0.55f,  0.55f, 
                               0.75f,  0.75f,  0.55f, 
                              -0.55f,  0.55f,  1.55f, 
                               0.75f,  0.25f, -0.55f, 
                               0.45f,  1.55f,  0.45f, 
                               0.25f,  0.25f};

    /* Test that self-intersecting cubic beziers are filled correctly under the both fill-rules.
     * Test draws a square with loops on each side formed with cubics.
     */

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    for (i = 0; i < 26; i++)
    {
        coords[i] = coords[i] * WINDSIZEX * 1.66f;
    }

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_TRANSFORM_FROM);
    vgAppendPathData(path, 6, cmds, coords);

    vgGetMatrix(xformStore);

    vgSetf(VG_STROKE_LINE_WIDTH, 2);

    vgSeti(VG_FILL_RULE, VG_NON_ZERO);

    stroke = vgCreatePaint();
    vgSetParameterfv(stroke, VG_PAINT_COLOR, 4, color1);
    vgSetPaint(stroke, VG_STROKE_PATH);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, color2);
    vgSetPaint(fill, VG_FILL_PATH);

    vgTranslate(-(VGint)(WINDSIZEX/3), -(VGint)(WINDSIZEY/3));
    vgSeti(VG_FILL_RULE, VG_EVEN_ODD);
    vgDrawPath(path, VG_STROKE_PATH|VG_FILL_PATH);

    vgDestroyPath(path);
    vgDestroyPaint(stroke);
    vgDestroyPaint(fill);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}
