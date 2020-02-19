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
 * F20101_Masking_by_NVIDIA
 *
 * Tests the error conditions of the masking API functions. The test
 * performs a number of API calls with both valid and invalid input,
 * and checks that the results and error codes are as expected. The
 * resulting DAT file contains a single value for each test case,
 * telling how many failures were detected.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20101_Masking_by_NVIDIA(CT_File *AnsFile)
{
    static const VGint nonPositiveSizes[][2] =
    {
        { 0, 32 },
        { 32, 0 },
        { 0, 0 },
        { -1, 32 },
        { 32, -1 },
        { -1, -1 },
        { (VGint)0x80000000u, 32 },
        { 32, (VGint)0x80000000u },
        { (VGint)0x80000000u, (VGint)0x80000000u }
    };

    VGfloat     results[18];
    VGPath      vgPath;
    VGImage     vgImage;
    VGPaint     vgPaint;
    VGboolean   hasSurfaceMask;
    VGMaskLayer vgMaskLayer = VG_INVALID_HANDLE;
    int         i, j;

    /* Clear the results. */

    for (i = 0; i < (int)(sizeof(results) / sizeof(results[0])); i++)
        results[i] = 0.0f;

    /* Create the temporary objects. */
    {
        static const VGubyte rectCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat rectVal[] =
        { 1.0f, 1.0f, 0.0f };

        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(rectCmd), rectCmd, rectVal);

        vgImage = vgCreateImage(VG_sRGBA_8888, 32, 32,
            VG_IMAGE_QUALITY_NONANTIALIASED);

        vgPaint = vgCreatePaint();
    }

    /* Make sure that the VGPaint handle is distinct from the other objects. */

    if (vgPaint == vgPath || vgPaint == vgImage)
    {
        VGPaint vgOldPaint = vgPaint;
        vgPaint = vgCreatePaint();
        vgDestroyPaint(vgOldPaint);
    }

    /* Check whether the surface mask is present. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        VGuint pixelRGBA;

        /* Clear with the background color. */

        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, 1, 1);

        /* Clear the mask. */

        vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, 1, 1);

        /* Fill the path using the default paint.
         * If the mask is present, this is a no-op. */

        vgSeti(VG_MASKING, VG_TRUE);
        vgDrawPath(vgPath, VG_FILL_PATH);
        vgSeti(VG_MASKING, VG_FALSE);

        /* Read the pixel.
         * If the mask is present, the result matches the clear color. */

        vgReadPixels(&pixelRGBA, 0, VG_sRGBA_8888, 0, 0, 1, 1);
        hasSurfaceMask = (pixelRGBA == 0xffffffff);
    }

    /* 0. Init
     * Check that the initialization succeeded. */

    results[0] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[0] += (vgPath == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    results[0] += (vgImage == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    results[0] += (vgPaint == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 1. vgMask()
     * Check that an invalid op produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgMask(vgImage, (VGMaskOperation)0xdeadbeefu, 0, 0, 32, 32);
    results[1] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 2. vgMask()
     * Check that non-positive width/height produces
     * VG_ILLEGAL_ARGUMENT_ERROR. */

    for (i = VG_CLEAR_MASK; i <= VG_SUBTRACT_MASK; i++)
        for (j = 0; j < (int)(sizeof(nonPositiveSizes) / sizeof(nonPositiveSizes[0])); j++)
        {
            vgMask(vgImage, (VGMaskOperation)i, 0, 0, nonPositiveSizes[j][0], nonPositiveSizes[j][1]);
            results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }

    /* 3. vgMask()
     * Check that an invalid handle produces VG_BAD_HANDLE_ERROR for
     * ops other than fill/clear. */

    for (i = VG_SET_MASK; i <= VG_SUBTRACT_MASK; i++)
    {
        vgMask(VG_INVALID_HANDLE, (VGMaskOperation)i, 0, 0, 32, 32);
        results[3] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

        vgMask(vgPaint, (VGMaskOperation)i, 0, 0, 32, 32);
        results[3] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    }

    /* 4. vgMask()
     * Check that an invalid handle does not produce an error
     * for fill/clear ops. */

    for (i = VG_CLEAR_MASK; i <= VG_FILL_MASK; i++)
    {
        vgMask(VG_INVALID_HANDLE, (VGMaskOperation)i, 0, 0, 32, 32);
        results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgMask(vgPaint, (VGMaskOperation)i, 0, 0, 32, 32);
        results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* 5. vgRenderToMask()
     * Check that an invalid handle produces VG_BAD_HANDLE_ERROR. */

    for (i = VG_FILL_PATH; i <= (VG_FILL_PATH | VG_STROKE_PATH); i++)
        for (j = VG_CLEAR_MASK; j <= VG_SUBTRACT_MASK; j++)
        {
            vgRenderToMask(VG_INVALID_HANDLE, (VGbitfield)i, (VGMaskOperation)j);
            results[5] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

            vgRenderToMask((VGPath)vgPaint, (VGbitfield)i, (VGMaskOperation)j);
            results[5] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
        }

    /* 6. vgRenderToMask()
     * Check that an invalid paintModes produces VG_ILLEGAL_ARGUMENT_ERROR. */

    for (i = VG_CLEAR_MASK; i <= VG_SUBTRACT_MASK; i++)
    {
        vgRenderToMask(vgPath, 0x00, (VGMaskOperation)i);
        results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    
        vgRenderToMask(vgPath, 0x05, (VGMaskOperation)i);
        results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    }

    /* 7. vgRenderToMask()
     * Check that an invalid op produces VG_ILLEGAL_ARGUMENT_ERROR. */

    for (i = VG_FILL_PATH; i <= (VG_FILL_PATH | VG_STROKE_PATH); i++)
    {
        vgRenderToMask(vgPath, (VGbitfield)i, (VGMaskOperation)0xdeadbeefu);
        results[7] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    }

    /* 8. vgCreateMaskLayer()
     * Check that VG_INVALID_HANDLE is returned if and only if the surface
     * mask is unavailable. */

    vgMaskLayer = vgCreateMaskLayer(32, 32);
    results[8] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[8] += ((vgMaskLayer != VG_INVALID_HANDLE) != hasSurfaceMask) ? 1.0f : 0.0f;
    results[8] += (vgMaskLayer == vgImage) ? 1.0f : 0.0f;

    /* 9. vgCreateMaskLayer()
     * Check that non-positive width/height produces
     * VG_ILLEGAL_ARGUMENT_ERROR. */

    for (i = 0; i < (int)(sizeof(nonPositiveSizes) / sizeof(nonPositiveSizes[0])); i++)
    {
        VGMaskLayer vgTmpMaskLayer = vgCreateMaskLayer(nonPositiveSizes[i][0], nonPositiveSizes[i][1]);
        results[9] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        results[9] += (vgTmpMaskLayer != VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    }

    /* 10. vgCreateMaskLayer()
     * Check that large width/height produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        VGMaskLayer vgTmpMaskLayer;
        VGint maxWidth = vgGeti(VG_MAX_IMAGE_WIDTH);
        VGint maxHeight = vgGeti(VG_MAX_IMAGE_HEIGHT);

        vgTmpMaskLayer = vgCreateMaskLayer(maxWidth + 1, 1);
        results[10] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        results[10] += (vgTmpMaskLayer != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

        vgTmpMaskLayer = vgCreateMaskLayer(1, maxHeight + 1);
        results[10] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        results[10] += (vgTmpMaskLayer != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

        if (vgGeti(VG_MAX_IMAGE_PIXELS) / maxWidth < maxHeight)
        {
            vgTmpMaskLayer = vgCreateMaskLayer(maxWidth, maxHeight);
            results[10] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
            results[10] += (vgTmpMaskLayer != VG_INVALID_HANDLE) ? 1.0f : 0.0f;
        }
    }

    /* 11. vgDestroyMaskLayer()
     * Check that an invalid handle produces VG_BAD_HANDLE_ERROR. */

    vgDestroyMaskLayer(VG_INVALID_HANDLE);
    results[11] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgDestroyMaskLayer((VGMaskLayer)vgPaint);
    results[11] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    /* 12. vgFillMaskLayer()
     * Check that an invalid handle produces VG_BAD_HANDLE_ERROR. */

    vgFillMaskLayer(VG_INVALID_HANDLE, 0, 0, 32, 32, 0.5f);
    results[12] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgFillMaskLayer((VGMaskLayer)vgPaint, 0, 0, 32, 32, 0.5f);
    results[12] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    /* 13. vgFillMaskLayer()
     * Check that a value below 0 or above 1 produces
     * VG_ILLEGAL_ARGUMENT_ERROR. */

    if (vgMaskLayer != VG_INVALID_HANDLE)
    {
        static const VGfloat values[] =
        {
            1.0019f, 1.5f, 2.0f, 1e8f, 1e10f, 1e38f,
            -0.0019f, -0.5f, -1.0f, -1e8f, -1e10f, -1e38f
        };
        for (i = 0; i < (int)(sizeof(values) / sizeof(values[0])); i++)
        {
            vgFillMaskLayer(vgMaskLayer, 0, 0, 32, 32, values[i]);
            results[13] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }
    }

    /* 14. vgFillMaskLayer()
     * Check that non-positive width/height produces
     * VG_ILLEGAL_ARGUMENT_ERROR. */


    if (vgMaskLayer != VG_INVALID_HANDLE)
        for (i = 0; i < (int)(sizeof(nonPositiveSizes) / sizeof(nonPositiveSizes[0])); i++)
        {
            vgFillMaskLayer(vgMaskLayer, 0, 0, nonPositiveSizes[i][0], nonPositiveSizes[i][1], 0.5f);
            results[14] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }

    /* 15. vgFillMaskLayer()
     * Check that the rectangle being out of bounds produces
     * VG_ILLEGAL_ARGUMENT_ERROR. */

    if (vgMaskLayer != VG_INVALID_HANDLE)
    {
        static const VGint rects[][4] =
        {
            { 0, 0, 33, 32 },
            { 0, 0, 32, 33 },
            { -1, 0, 32, 32 },
            { 0, -1, 32, 32 },
            { (VGint)0x80000000u, 0, 32, 32 },
            { 0, (VGint)0x80000000u, 32, 32 },
            { 0x7fffffff, 0, 32, 32 },
            { 0, 0x7fffffff, 32, 32 },
            { 0, 0, 0x7fffffff, 32 },
            { 0, 0, 32, 0x7fffffff },
            { 0x7fffffff, 0, 0x7fffffff, 32 },
            { 0, 0x7fffffff, 32, 0x7fffffff },
        };
        for (i = 0; i < (int)(sizeof(rects) / sizeof(rects[0])); i++)
        {
            vgFillMaskLayer(vgMaskLayer, rects[i][0], rects[i][1], rects[i][2], rects[i][3], 0.5f);
            results[15] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }
    }

    /* 16. vgCopyMask()
     * Check that an invalid handle produces VG_BAD_HANDLE_ERROR. */

    vgCopyMask(VG_INVALID_HANDLE, 0, 0, 0, 0, 32, 32);
    results[16] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgCopyMask((VGMaskLayer)vgPaint, 0, 0, 0, 0, 32, 32);
    results[16] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    /* 17. vgCopyMask()
     * Check that non-positive width/height produces VG_ILLEGAL_ARGUMENT_ERROR. */

    if (vgMaskLayer != VG_INVALID_HANDLE)
        for (i = 0; i < (int)(sizeof(nonPositiveSizes) / sizeof(nonPositiveSizes[0])); i++)
        {
            vgCopyMask(vgMaskLayer, 0, 0, 0, 0, nonPositiveSizes[i][0], nonPositiveSizes[i][1]);
            results[17] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }

    /* Clean up and save the results. */

    if (vgPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPath);
    if (vgImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgImage);
    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgMaskLayer != VG_INVALID_HANDLE)
        vgDestroyMaskLayer(vgMaskLayer);

    return SaveValueFile(sizeof(results) / sizeof(results[0]), results, AnsFile);
}

