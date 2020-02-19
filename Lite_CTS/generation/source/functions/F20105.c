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

/*
 * F20105_Masking_by_NVIDIA
 *
 * Tests the effect of different rendering parameters on
 * vgRenderToMask(). Some of the parameters should have an effect on
 * the resulting image, while others should not.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20105_Masking_by_NVIDIA(CT_File *AnsFile)
{
    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Clear the surface mask.
     * Bottom half is cleared to zero, top half is cleared to one.
     * Since VG_SET_MASK is used in vgRenderToMask(), the initial
     * values should be ignored. */

    vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, WINDSIZEX, WINDSIZEY / 2);
    vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, WINDSIZEY / 2, WINDSIZEX, WINDSIZEY / 2);

    /* Render a path to the surface mask. */
    {
        static const VGubyte pathCmd[] =
        {
            VG_MOVE_TO_ABS, VG_QUAD_TO_REL, VG_QUAD_TO_REL,
            VG_MOVE_TO_ABS, VG_HLINE_TO_REL
        };

        static const VGfloat pathVal[] =
        {
            0.0f, 0.0f, 12.0f, 80.0f, 24.0f, 0.0f, 12.0f, 80.0f, 24.0f, 0.0f,
            0.0f, 48.0f, 48.0f
        };

        static const VGfloat colorTransform[] =
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

        static const VGfloat dashPattern[] =
        { 4.0f, 10.0f };

        VGPath vgPath;
        VGPaint vgPaint;

        /* Create the path. */
        
        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);

        /* Create a fully transparent paint.
         * The paint should be ignored by vgRenderToMask(). */

        vgPaint = vgCreatePaint();
        vgSetColor(vgPaint, 0x00000000);
        vgSetPaint(vgPaint, VG_STROKE_PATH);

        /* Setup the rendering state. */

        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
        vgSeti(VG_BLEND_MODE, VG_BLEND_MULTIPLY);               /* Ignored. */
        vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);                    /* Ignored. */
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, colorTransform);  /* Ignored. */
        vgSetf(VG_STROKE_LINE_WIDTH, 8.0f);                     /* Visible. */
        vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);              /* Visible. */
        vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);            /* Visible. */
        vgSetfv(VG_STROKE_DASH_PATTERN, 2, dashPattern);        /* Visible. */
        vgSetf(VG_STROKE_DASH_PHASE, -15.0f);                   /* Visible. */
        vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_TRUE);            /* Visible. */
        vgSeti(VG_MASKING, VG_TRUE);                            /* Ignored. */

        /* Setup the matrices. */

        vgSeti(VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER);
        vgLoadIdentity();
        vgScale(0.0f, 0.0f);                                    /* Ignored. */
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        vgLoadIdentity();
        vgTranslate(8.0f, 8.0f);                                /* Visible. */

        /* Stroke the path. */

        vgRenderToMask(vgPath, VG_STROKE_PATH, VG_SET_MASK);

        /* Clean up. */

        vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
        vgSeti(VG_COLOR_TRANSFORM, VG_FALSE);
        vgSeti(VG_MASKING, VG_FALSE);
        vgDestroyPath(vgPath);
        vgDestroyPaint(vgPaint);
    }

    /* Draw a solid cyan rectangle through the surface mask. */
    {
        static const VGubyte rectCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat rectVal[] =
        { (VGfloat)WINDSIZEX, (VGfloat)WINDSIZEY, 0.0f };

        VGPath vgPath;
        VGPaint vgPaint;

        /* Create a path covering the whole window. */

        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(rectCmd), rectCmd, rectVal);

        /* Create a solid white paint. */

        vgPaint = vgCreatePaint();
        vgSetColor(vgPaint, 0x00ffffff);

        /* Draw the path through the mask.
         * Additive blending is used to ensure that vgRenderToMask() did not
         * modify the contents of the color buffer. */

        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
        vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        vgLoadIdentity();
        vgSetPaint(vgPaint, VG_FILL_PATH);
        vgSeti(VG_MASKING, VG_TRUE);
        vgDrawPath(vgPath, VG_FILL_PATH);
        vgSeti(VG_MASKING, VG_FALSE);

        /* Clean up. */

        vgDestroyPath(vgPath);
        vgDestroyPaint(vgPaint);
    }

    /* Save the result. */

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

