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
 * F20104_Masking_by_NVIDIA
 *
 * Tests vgRenderToMask() on different mask operations and rendering
 * quality settings. Each of the eighteen subtests covers a single
 * combination as follows:
 *
 * 0000: VG_CLEAR_MASK,     VG_RENDERING_QUALITY_NONANTIALIASED
 * 0001: VG_CLEAR_MASK,     VG_RENDERING_QUALITY_FASTER
 * 0002: VG_CLEAR_MASK,     VG_RENDERING_QUALITY_BETTER
 * 0003: VG_FILL_MASK,      VG_RENDERING_QUALITY_NONANTIALIASED
 * 0004: VG_FILL_MASK,      VG_RENDERING_QUALITY_FASTER
 * 0005: VG_FILL_MASK,      VG_RENDERING_QUALITY_BETTER
 * 0006: VG_SET_MASK,       VG_RENDERING_QUALITY_NONANTIALIASED
 * 0007: VG_SET_MASK,       VG_RENDERING_QUALITY_FASTER
 * 0008: VG_SET_MASK,       VG_RENDERING_QUALITY_BETTER
 * 0009: VG_UNION_MASK,     VG_RENDERING_QUALITY_NONANTIALIASED
 * 0010: VG_UNION_MASK,     VG_RENDERING_QUALITY_FASTER
 * 0011: VG_UNION_MASK,     VG_RENDERING_QUALITY_BETTER
 * 0012: VG_INTERSECT_MASK, VG_RENDERING_QUALITY_NONANTIALIASED
 * 0013: VG_INTERSECT_MASK, VG_RENDERING_QUALITY_FASTER
 * 0014: VG_INTERSECT_MASK, VG_RENDERING_QUALITY_BETTER
 * 0015: VG_SUBTRACT_MASK,  VG_RENDERING_QUALITY_NONANTIALIASED
 * 0016: VG_SUBTRACT_MASK,  VG_RENDERING_QUALITY_FASTER
 * 0017: VG_SUBTRACT_MASK,  VG_RENDERING_QUALITY_BETTER
 *
 * The resulting 64x64 image is divided into four quadrants.
 * In the bottom ones, the mask is initialized to zero,
 * while in the top ones, it is initialized to one. The left-hand
 * quadrants call vgRenderToMask() with VG_STROKE_PATH, while
 * the right-hand ones call it with VG_FILL_PATH | VG_STROKE_PATH.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20104_Masking_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    VGRenderingQuality vgRenderingQuality = (VGRenderingQuality)(VG_RENDERING_QUALITY_NONANTIALIASED + subtest % 3);
    VGMaskOperation vgMaskOperation = (VGMaskOperation)(VG_CLEAR_MASK + subtest / 3);
    VGMaskLayer vgMaskLayer;

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Create the mask layer.
     * If no surface mask is present, just exit. */

    vgMaskLayer = vgCreateMaskLayer(WINDSIZEX, WINDSIZEY);
    if (vgMaskLayer == VG_INVALID_HANDLE)
    {
        if (vgGetError() != VG_NO_ERROR)
            return CT_ERROR;
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }

    /* Render a path to each quadrant of the mask layer. */
    {
        static const VGubyte pathCmd[] =
        { VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_MOVE_TO_REL, VG_LINE_TO_REL };

        static const VGfloat pathVal[] =
        { 8.0f, 4.0f, 0.0f, 32.0f, 16.0f, 32.0f, 16.0f, 0.0f, 4.0f, 4.0f, -24.0f, 16.0f };

        static const VGint scissorRect[]  = { 0, 0, 32, 24 };

        VGPath vgPath;

        /* Create the path. */
        
        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);

        /* Setup the rendering state. */

        vgSeti(VG_RENDERING_QUALITY, vgRenderingQuality);
        vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
        vgSeti(VG_SCISSORING, VG_TRUE);
        vgSetiv(VG_SCISSOR_RECTS, 4, scissorRect);
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        vgLoadIdentity();

        /* Bottom left quadrant:
         * Background init to zero, VG_STROKE_PATH. */

        vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, 32, 32);
        vgRenderToMask(vgPath, VG_STROKE_PATH, vgMaskOperation);
        vgCopyMask(vgMaskLayer, 0, 0, 0, 0, 32, 32);

        /* Bottom right quadrant:
         * Background init to zero, VG_FILL_PATH | VG_STROKE_PATH.
         * Using the path as a mask is ok, since the it's ignored. */

        vgMask(vgPath, VG_CLEAR_MASK, 0, 0, 32, 32);
        vgRenderToMask(vgPath, VG_FILL_PATH | VG_STROKE_PATH, vgMaskOperation);
        vgCopyMask(vgMaskLayer, 32, 0, 0, 0, 32, 32);

        /* Top left quadrant:
         * Background init to one, VG_STROKE_PATH. */

        vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, 32, 32);
        vgRenderToMask(vgPath, VG_STROKE_PATH, vgMaskOperation);
        vgCopyMask(vgMaskLayer, 0, 32, 0, 0, 32, 32);

        /* Top right quadrant:
         * Background init to one, VG_FILL_PATH | VG_STROKE_PATH.
         * Using the path as a mask is ok, since the it's ignored. */

        vgMask(vgPath, VG_FILL_MASK, 0, 0, 32, 32);
        vgRenderToMask(vgPath, VG_FILL_PATH | VG_STROKE_PATH, vgMaskOperation);
        vgCopyMask(vgMaskLayer, 32, 32, 0, 0, 32, 32);

        /* Clean up. */

        vgSeti(VG_SCISSORING, VG_FALSE);
        vgDestroyPath(vgPath);
    }

    /* Copy the contents of the mask layer to the surface mask. */

    vgMask(vgMaskLayer, VG_SET_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

    /* Draw a solid white rectangle through the surface mask. */
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
        vgSetColor(vgPaint, 0xffffffff);

        /* Draw the path through the mask. */

        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
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

    /* Clean up and save the result. */

    vgDestroyMaskLayer(vgMaskLayer);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

