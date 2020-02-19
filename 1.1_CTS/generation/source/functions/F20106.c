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
 * F20106_Masking_by_NVIDIA
 *
 * Tests that intermixing masked and non-masked rendering with mask
 * updates works as expected. The test renders a number of colored
 * circles to the surface mask and to the color buffer, with and
 * without masking. It also maintains two auxiliary mask layers, and
 * occassionally copies pixels between them and the surface mask.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20106_Masking_by_NVIDIA(CT_File *AnsFile)
{
    static const VGubyte circleCmd[] =
    { VG_MOVE_TO_ABS, VG_LCCWARC_TO_ABS, VG_LCCWARC_TO_ABS, VG_CLOSE_PATH };

    static const VGfloat circleVal[] =
    { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    VGMaskLayer vgMaskLayerA;
    VGMaskLayer vgMaskLayerB;
    VGPath vgCirclePath;
    VGPaint vgPaint;
    int i, j;

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Create the mask layers.
     * If no surface mask is present, just exit. */

    vgMaskLayerA = vgCreateMaskLayer(64, 64);
    if (vgMaskLayerA == VG_INVALID_HANDLE)
    {
        if (vgGetError() != VG_NO_ERROR)
            return CT_ERROR;
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }

    vgMaskLayerB = vgCreateMaskLayer(64, 64);

    /* Create the circle path. */
    
    vgCirclePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
        1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

    vgAppendPathData(vgCirclePath, sizeof(circleCmd), circleCmd, circleVal);

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetPaint(vgPaint, VG_FILL_PATH);
    
    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgSetf(VG_STROKE_LINE_WIDTH, 0.125f);

    /* Initialize vgMaskLayerA and the surface mask.
     * vgMaskLayerA ends up getting filled with zeros.
     * The surface mask ends up with the following values:
     * 1.0f within rect(0, 0, 48, 16)
     * 1.0f within rect(0, 0, 16, 32)
     * 0.0f elsewhere */

    vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, 64, 64);
    vgFillMaskLayer(vgMaskLayerA, 0, 0, 64, 64, 1.0f);
    vgMask(vgMaskLayerA, VG_SET_MASK, -16, -16, 0x7fffffff, 0x7fffffff);
    vgFillMaskLayer(vgMaskLayerA, 0, 0, 64, 64, 0.0f);
    vgMask(vgMaskLayerA, VG_SET_MASK, 16, 16, 0x7fffffff, 0x7fffffff);

    /* Iterate through a 4x4 grid of 16x16 elements. */
    
    for (i = 8; i <= 56; i += 16)
        for (j = 8; j <= 56; j += 16)
        {
            vgLoadIdentity();
            vgTranslate((VGfloat)i, (VGfloat)j);
            vgScale(8.0f, 8.0f);

            /* Draw a cyan circle at the center. */

            vgSeti(VG_MASKING, VG_FALSE);
            vgSetColor(vgPaint, 0x00ffffff);
            vgDrawPath(vgCirclePath, VG_FILL_PATH | VG_STROKE_PATH);

            /* Draw a magenta circle through the (non-updated) mask,
             * translated slightly left from the center. */

            vgSeti(VG_MASKING, VG_TRUE);
            vgSetColor(vgPaint, 0xff00ffff);
            vgTranslate(-0.5f, 0.0f);
            vgDrawPath(vgCirclePath, VG_FILL_PATH | VG_STROKE_PATH);

            /* Union the cyan circle into the surface mask. */

            vgTranslate(0.5f, 0.0f);
            vgRenderToMask(vgCirclePath, VG_FILL_PATH, VG_UNION_MASK);

            /* Draw a yellow circle through the (updated) mask,
             * translated slightly right from the center. */

            vgSetColor(vgPaint, 0xffff00ff);
            vgTranslate(0.5f, 0.0f);
            vgDrawPath(vgCirclePath, VG_FILL_PATH | VG_STROKE_PATH);
        }

    /* Swap the mask layers:
     * vgMaskLayerB := surfaceMask
     * surfaceMask  := vgMaskLayerA */

    vgCopyMask(vgMaskLayerB, -0x10000000, -0x10000000, -0x10000000, -0x10000000, 0x7fffffff, 0x7fffffff);
    vgMask(vgMaskLayerA, VG_SET_MASK, 0, 0, 64, 64);

    /* Union two large circles into the surface mask. */

    vgLoadIdentity();
    vgTranslate(16.0f, 32.0f);
    vgScale(16.0f, 16.0f);
    vgRenderToMask(vgCirclePath, VG_FILL_PATH, VG_UNION_MASK);
    vgTranslate(2.0f, 0.0f);
    vgRenderToMask(vgCirclePath, VG_FILL_PATH, VG_UNION_MASK);

    /* Shuffle the mask layers a bit. The surface mask ends up
     * containing the intersection of the grid and the two circles. */

    vgCopyMask(vgMaskLayerA, 0, 0, 0, 0, 64, 64);
    vgMask(vgMaskLayerB, VG_SET_MASK, 0, 0, 64, 64);
    vgMask(vgMaskLayerA, VG_INTERSECT_MASK, 0, 0, 64, 64);

    /* Draw a transparent black circle through the mask, centered at (32, 32). */

    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_MASKING, VG_TRUE);
    vgSetColor(vgPaint, 0x00000000);
    vgLoadIdentity();
    vgTranslate(32.0f, 32.0f);
    vgScale(16.0f, 16.0f);
    vgDrawPath(vgCirclePath, VG_FILL_PATH);

    /* Clean up and save the result. */

    vgDestroyMaskLayer(vgMaskLayerA);
    vgDestroyMaskLayer(vgMaskLayerB);
    vgDestroyPath(vgCirclePath);
    vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

