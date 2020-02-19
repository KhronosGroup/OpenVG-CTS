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

CT_Result B10103_RenderingQualityPath_by_HYBRID(CT_File *AnsFile)
{
    VGPaint fill;
    VGPath small_box;

    static const VGubyte sqrCmds[5] = {VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH};
    
    VGfloat small_coords[5];

    static const VGfloat transparent_white[4] = {1, 1, 1, 0.8f};
    static const VGfloat black[4]  = {0, 0, 0, 1};

    /* Test the position of the nonantialiased sampling point */

    /*  Exceptionally use the identity transform to make sure that we get the coordinates specified. */
    vgLoadIdentity();

    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, transparent_white);
    vgSetPaint(fill, VG_FILL_PATH);

    small_box = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO|VG_PATH_CAPABILITY_MODIFY);

    {
        VGfloat temp[5] = {0, 0, 4, 4, 0};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i] = temp[i];
        }
    }

    vgAppendPathData(small_box, 5, sqrCmds, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the left edge */

    {
        VGfloat temp[5] = {0.001f, 4, 4.001f, 8, 0.001f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {0.1f, 8, 4.1f, 12, 0.1f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the middle point */

    {
        VGfloat temp[5] = {0.499f, 16, 4.499f, 20, 0.499f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {0.5f, 20, 4.5f, 24, 0.5f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {0.5001f, 24, 4.5001f, 28, 0.5001f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {0.51f, 28, 4.51f, 32, 0.51f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the right edge */

    {
        VGfloat temp[5] = {0.99f, 36, 4.9f, 40, 0.9f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {0.99f, 40, 4.99f, 44, 0.99f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {1.001f, 44, 5.001f, 48, 1.001f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near 0.75f */

    {
        VGfloat temp[5] = {0.75f, 52, 4.75f, 56, 0.75f};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the left edge */

    {
        VGfloat temp[5] = {4, 0.001f, 8, 4.001f, 4};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {8, 0.1f, 12, 4.1f, 8};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the middle point */

    {
        VGfloat temp[5] = {16, 0.499f, 20, 4.499f, 16};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {20, 0.5f, 24, 4.5f, 20};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {24, 0.5001f, 28, 4.5001f, 24};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {28, 0.51f, 32, 4.51f, 28};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near the right edge */

    {
        VGfloat temp[5] = {36, 0.9f, 40, 4.9f, 36};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {40, 0.99f, 44, 4.99f, 40};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    {
        VGfloat temp[5] = {44, 1.001f, 48, 5.001f, 44};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    /* Near 0.75f */

    {
        VGfloat temp[5] = {52, 0.75f, 56, 4.75f, 52};
        int i;
        for (i = 0; i < 5; i++)
        {
            small_coords[i+0] = temp[i];
        }
    }

    vgModifyPathCoords(small_box, 0, 4, small_coords);
    vgDrawPath(small_box, VG_FILL_PATH);

    vgDestroyPaint(fill);
    vgDestroyPath(small_box);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

