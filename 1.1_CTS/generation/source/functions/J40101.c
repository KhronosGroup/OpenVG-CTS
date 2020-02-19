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
 * J40101_ImageFilter_by_NVIDIA
 *
 * Tests the error conditions and special cases of
 * the image filter API functions. The test performs
 * a number of API calls with both valid and invalid
 * input, and checks that the results and error codes
 * are as expected. The resulting DAT file contains a
 * single value for each test case, telling how many
 * failures were detected.
 */

#include "../main.h"
#include "../util/util.h"

typedef union
{
    VGfloat f;
    VGuint u;
} CTFloatInt;

CT_Result J40101_ImageFilter_by_NVIDIA(CT_File *AnsFile)
{
    static const VGfloat colorMatrix[] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

    VGImage     vgImageA;
    VGImage     vgImageB;
    VGfloat     results[10];
    VGshort     kernel = 0;
    VGuint*     intLUT;
    VGubyte*    byteLUT;
    int         i;

    /* Allocate the lookup tables. */

    intLUT = (VGuint*)MALLOC(256 * (sizeof(VGuint) + sizeof(VGubyte)));
    if (!intLUT)
        return CT_ERROR;

    byteLUT = (VGubyte*)(intLUT + 256);

    /* Initialize the lookup tables. */

    for (i = 0; i < 256; i++)
    {
        intLUT[i] = 0x01010101 * i;
        byteLUT[i] = (VGubyte)i;
    }

    /* Clear the results. */

    for (i = 0; i < (int)(sizeof(results) / sizeof(results[0])); i++)
        results[i] = 0.0f;

    /* Create the temporary images. */

    vgImageA = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageB = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* 0. Init
     * Check that the initialization succeeded. */

    results[0] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[0] += (vgImageA == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    results[0] += (vgImageB == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 1. vgColorMatrix(), vgConvolve(), vgSeparableConvolve(),
     *    vgGaussianBlur(), vgLookup(), vgLookupSingle()
     * Check that invalid src/dst produces VG_BAD_HANDLE_ERROR. */

    vgColorMatrix(VG_INVALID_HANDLE, vgImageB, colorMatrix);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgColorMatrix(vgImageA, VG_INVALID_HANDLE, colorMatrix);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgConvolve(VG_INVALID_HANDLE, vgImageB, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgConvolve(vgImageA, VG_INVALID_HANDLE, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgSeparableConvolve(VG_INVALID_HANDLE, vgImageB, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgSeparableConvolve(vgImageA, VG_INVALID_HANDLE, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgGaussianBlur(VG_INVALID_HANDLE, vgImageB, 1.0f, 1.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgGaussianBlur(vgImageA, VG_INVALID_HANDLE, 1.0f, 1.0f, VG_TILE_FILL);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgLookup(VG_INVALID_HANDLE, vgImageB, byteLUT, byteLUT, byteLUT, byteLUT, VG_FALSE, VG_FALSE);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgLookup(vgImageA, VG_INVALID_HANDLE, byteLUT, byteLUT, byteLUT, byteLUT, VG_FALSE, VG_FALSE);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    vgLookupSingle(VG_INVALID_HANDLE, vgImageB, intLUT, VG_RED, VG_FALSE, VG_FALSE);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;
    vgLookupSingle(vgImageA, VG_INVALID_HANDLE, intLUT, VG_RED, VG_FALSE, VG_FALSE);
    results[1] += (vgGetError() != VG_BAD_HANDLE_ERROR) ? 1.0f : 0.0f;

    /* 2. vgColorMatrix(), vgConvolve(), vgSeparableConvolve(),
     *    vgGaussianBlur(), vgLookup(), vgLookupSingle()
     * Check that overlapping src/dst produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgColorMatrix(vgImageA, vgImageA, colorMatrix);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgConvolve(vgImageA, vgImageA, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSeparableConvolve(vgImageA, vgImageA, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgGaussianBlur(vgImageA, vgImageA, 1.0f, 1.0f, VG_TILE_FILL);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookup(vgImageA, vgImageA, byteLUT, byteLUT, byteLUT, byteLUT, VG_FALSE, VG_FALSE);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookupSingle(vgImageA, vgImageA, intLUT, VG_RED, VG_FALSE, VG_FALSE);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 3. vgColorMatrix(), vgConvolve(), vgSeparableConvolve(),
     *    vgLookup(), vgLookupSingle()
     * Check that NULL pointers produce VG_ILLEGAL_ARGUMENT_ERROR. */

    vgColorMatrix(vgImageA, vgImageB, NULL);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgConvolve(vgImageA, vgImageB, 1, 1, 0, 0, NULL, 1.0f, 0.0f, VG_TILE_FILL);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, NULL, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, NULL, 1.0f, 0.0f, VG_TILE_FILL);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookup(vgImageA, vgImageB, NULL, byteLUT, byteLUT, byteLUT, VG_FALSE, VG_FALSE);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgLookup(vgImageA, vgImageB, byteLUT, NULL, byteLUT, byteLUT, VG_FALSE, VG_FALSE);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgLookup(vgImageA, vgImageB, byteLUT, byteLUT, NULL, byteLUT, VG_FALSE, VG_FALSE);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgLookup(vgImageA, vgImageB, byteLUT, byteLUT, byteLUT, NULL, VG_FALSE, VG_FALSE);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookupSingle(vgImageA, vgImageB, NULL, VG_RED, VG_FALSE, VG_FALSE);
    results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 4. vgConvolve(), vgSeparableConvolve()
     * Check that non-positive kernel sizes produce VG_ILLEGAL_ARGUMENT_ERROR. */
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
        for (i = 0; i < (int)(sizeof(nonPositiveSizes) / sizeof(nonPositiveSizes[0])); i++)
        {
            int w = nonPositiveSizes[i][0];
            int h = nonPositiveSizes[i][1];

            vgConvolve(vgImageA, vgImageB, w, h, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
            results[4] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

            vgSeparableConvolve(vgImageA, vgImageB, w, h, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
            results[4] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }
    }

    /* 5. vgConvolve(), vgSeparableConvolve()
     * Check that too large kernel produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        VGint maxKern = vgGeti(VG_MAX_KERNEL_SIZE);
        VGint maxSep  = vgGeti(VG_MAX_SEPARABLE_KERNEL_SIZE);

        vgConvolve(vgImageA, vgImageB, maxKern + 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
        results[5] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        vgConvolve(vgImageA, vgImageB, 1, maxKern + 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
        results[5] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

        vgSeparableConvolve(vgImageA, vgImageB, maxSep + 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
        results[5] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        vgSeparableConvolve(vgImageA, vgImageB, 1, maxSep + 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL);
        results[5] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    }

    /* 6. vgConvolve(), vgSeparableConvolve(), vgGaussianBlur()
     * Check that invalid tiling mode produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        VGTilingMode tile = (VGTilingMode)0xdeadbeef;

        vgConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, tile);
        results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

        vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, tile);
        results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

        vgGaussianBlur(vgImageA, vgImageB, 1.0f, 1.0f, tile);
        results[6] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    }

    /* 7. vgGaussianBlur()
     * Check that non-positive deviation produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        static const VGuint nonPositiveDeviations[][2] =
        {
            { 0x00000000u, 0x42000000u },
            { 0x42000000u, 0x00000000u },
            { 0x00000000u, 0x00000000u },
            { 0xbf800000u, 0x42000000u },
            { 0x42000000u, 0xbf800000u },
            { 0xbf800000u, 0xbf800000u },
            { 0x80000000u, 0x42000000u },
            { 0x42000000u, 0x80000000u },
            { 0x80000000u, 0x80000000u },
            { 0xff7fffffu, 0x42000000u },
            { 0x42000000u, 0xff7fffffu },
            { 0xff7fffffu, 0xff7fffffu }
        };
        for (i = 0; i < (int)(sizeof(nonPositiveDeviations) / sizeof(nonPositiveDeviations[0])); i++)
        {
            CTFloatInt devX, devY;
            devX.u = nonPositiveDeviations[i][0];
            devY.u = nonPositiveDeviations[i][1];

            vgGaussianBlur(vgImageA, vgImageB, devX.f, devY.f, VG_TILE_FILL);
            results[7] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }
    }

    /* 8. vgGaussianBlur()
     * Check that max deviation does not produce an error,
     * but too large deviation produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        VGfloat maxDev = vgGetf(VG_MAX_GAUSSIAN_STD_DEVIATION);
        VGfloat largeDev = maxDev + 1.0f;

        vgGaussianBlur(vgImageA, vgImageB, maxDev, 1.0f, VG_TILE_FILL);
        results[8] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    
        vgGaussianBlur(vgImageA, vgImageB, 1.0f, maxDev, VG_TILE_FILL);
        results[8] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgGaussianBlur(vgImageA, vgImageB, maxDev, maxDev, VG_TILE_FILL);
        results[8] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        if (largeDev > maxDev)
        {
            vgGaussianBlur(vgImageA, vgImageB, largeDev, 1.0f, VG_TILE_FILL);
            results[8] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        
            vgGaussianBlur(vgImageA, vgImageB, 1.0f, largeDev, VG_TILE_FILL);
            results[8] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        }
    }

    /* 9. vgLookupSingle()
     * Check that invalid source channels produce VG_ILLEGAL_ARGUMENT_ERROR. */

    vgLookupSingle(vgImageA, vgImageB, intLUT, 0, VG_FALSE, VG_FALSE);
    results[9] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookupSingle(vgImageA, vgImageB, intLUT, VG_RED | VG_GREEN, VG_FALSE, VG_FALSE);
    results[9] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgLookupSingle(vgImageA, vgImageB, intLUT, 1 << 4, VG_FALSE, VG_FALSE);
    results[9] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* Clean up and save the results. */

    FREE(intLUT);
    if (vgImageA != VG_INVALID_HANDLE)
        vgDestroyImage(vgImageA);
    if (vgImageB != VG_INVALID_HANDLE)
        vgDestroyImage(vgImageB);
    return SaveValueFile(sizeof(results) / sizeof(results[0]), results, AnsFile);
}

