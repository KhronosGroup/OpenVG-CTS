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
 * H30201_ImageError_by_NVIDIA
 *
 * Tests the error conditions of the image API functions. The test
 * performs a number of API calls with both valid and invalid input,
 * and checks that the results and error codes are as expected. The
 * resulting DAT file contains a single value for each test case,
 * telling how many failures were detected.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result H30201_ImageError_by_NVIDIA(CT_File *AnsFile)
{
    VGfloat     results[8];
    VGImage     vgImage;
    VGMaskLayer vgMaskLayer;
    VGImage     vgTempImage;
    VGErrorCode vgError;
    VGint       maxImageWidth   = vgGeti(VG_MAX_IMAGE_WIDTH);
    VGint       maxImagePixels  = vgGeti(VG_MAX_IMAGE_PIXELS);
    VGint       maxImageBytes   = vgGeti(VG_MAX_IMAGE_BYTES);
    int         i;

    /* Clear the results. */

    for (i = 0; i < (int)(sizeof(results) / sizeof(results[0])); i++)
        results[i] = 0.0f;

    /* Create the temporary objects. */

    vgImage = vgCreateImage(VG_A_8, 32, 32, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgMaskLayer = vgCreateMaskLayer(32, 32);

    /* 0. Init
     * Check that the initialization succeeded. */

    results[0] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[0] += (vgImage == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 1. vgCreateImage()
     * Check that exceeding VG_MAX_IMAGE_PIXELS produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgTempImage = vgCreateImage(VG_A_8,
        maxImageWidth, maxImagePixels / maxImageWidth + 1,
        VG_IMAGE_QUALITY_NONANTIALIASED);

    vgError = vgGetError();
    results[1] += (vgError != VG_ILLEGAL_ARGUMENT_ERROR &&
                   vgError != VG_OUT_OF_MEMORY_ERROR) ? 1.0f : 0.0f;
    results[1] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 2. vgCreateImage()
     * Check that exceeding VG_MAX_IMAGE_BYTES produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgTempImage = vgCreateImage(VG_sRGBA_8888,
        maxImageWidth, maxImageBytes / 4 / maxImageWidth + 1,
        VG_IMAGE_QUALITY_NONANTIALIASED);

    vgError = vgGetError();
    results[2] += (vgError != VG_ILLEGAL_ARGUMENT_ERROR &&
                   vgError != VG_OUT_OF_MEMORY_ERROR) ? 1.0f : 0.0f;
    results[2] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 3. vgCreateImage()
     * Check that an invalid allowedQuality produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgTempImage = vgCreateImage(VG_A_8, 1, 1, 0);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    results[3] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    vgTempImage = vgCreateImage(VG_A_8, 1, 1, 1 << 3);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    results[3] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 4. vgDestroyImage()
     * Check that specifying a VGMaskLayer object produces VG_BAD_HANDLE_ERROR. */

    vgDestroyImage(vgMaskLayer);
    results[4] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    /* 5. vgChildImage()
     * Check that specifying a VGMaskLayer object produces VG_BAD_HANDLE_ERROR. */

    vgTempImage = vgChildImage(vgMaskLayer, 0, 0, 1, 1);
    results[5] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    results[5] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 6. vgChildImage()
     * Check that an invalid rectangle produces VG_ILLEGAL_ARGUMENT_ERROR. */
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
            vgTempImage = vgChildImage(vgImage, rects[i][0], rects[i][1], rects[i][2], rects[i][3]);
            results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
            results[6] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;
        }
    }

    /* 7. vgChildImage()
     * Check that specifying a destroyed parent image produces VG_BAD_HANDLE_ERROR. */
    {
        VGImage vgParent;
        VGImage vgChild;

        vgParent = vgCreateImage(VG_A_8, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
        results[7] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        results[7] += (vgParent == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

        vgChild = vgChildImage(vgParent, 0, 0, 1, 1);
        results[7] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        results[7] += (vgChild == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

        vgDestroyImage(vgParent);
        results[7] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgTempImage = vgChildImage(vgParent, 0, 0, 1, 1);
        results[7] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
        results[7] += (vgTempImage != VG_INVALID_HANDLE) ? 1.0f : 0.0f;

        vgDestroyImage(vgChild);
        results[7] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* Clean up and save the results. */

    if (vgImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgImage);
    if (vgMaskLayer != VG_INVALID_HANDLE)
        vgDestroyMaskLayer(vgMaskLayer);
    return SaveValueFile(sizeof(results) / sizeof(results[0]), results, AnsFile);
}

