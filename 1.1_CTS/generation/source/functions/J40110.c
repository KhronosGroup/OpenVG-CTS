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
 * J40110_ImageFilter_by_NVIDIA
 *
 * Tests vgLookup() and vgLookupSingle() by decoding an
 * image whose pixels have been permuted randomly on each
 * scanline.
 *
 * For each scanline, the test selects four random
 * permutations of the integers 0-255, used as the color
 * channels of the source image. The test then
 * initializes the lookup tables based on a known image
 * so that the lookup yields the desired color for each
 * pixel.
 *
 * The lookup format is selected based on the two lowest
 * bits of the scanline index (from bottom to top):
 *
 * 00: sRGBA
 * 01: lRGBA
 * 10: sRGBA_PRE
 * 11: lRGBA_PRE
 *
 * The lookup function and source channel are selected
 * based on the highest bits of the scanline index:
 *
 * (y / 4) % 5 == 0 -> vgLookupSingle(VG_RED)
 * (y / 4) % 5 == 1 -> vgLookupSingle(VG_GREEN)
 * (y / 4) % 5 == 2 -> vgLookupSingle(VG_BLUE)
 * (y / 4) % 5 == 3 -> vgLookupSingle(VG_ALPHA)
 * (y / 4) % 5 == 4 -> vgLookup()
 */

#include "../main.h"
#include "../util/util.h"
#include "../static/hybrid/pukki_64x64.h"

CT_Result J40110_ImageFilter_by_NVIDIA(CT_File *AnsFile)
{
    int         width = pukki_64x64_width;
    int         height = pukki_64x64_height;
    VGuint*     pixels;
    VGuint*     intLUT;
    VGubyte*    byteLUT[4];
    VGubyte*    permut[4];
    VGImage     vgTargetImage;
    VGImage     vgDstImage;
    VGImage     vgSrcImage;
    int         i, j, k;

    /* Allocate the lookup tables. */
    {
        VGubyte* ptr;

        pixels = (VGuint*)MALLOC(width * sizeof(VGuint) + 256 * (sizeof(VGuint) + 8 * sizeof(VGubyte)));
        if (!pixels)
            return CT_ERROR;

        intLUT = pixels + width;
        ptr = (VGubyte*)(intLUT + 256);
        for (i = 0; i < 4; i++)
        {
            byteLUT[i] = ptr;
            permut[i] = ptr + 256;
            ptr += 512;
        }
    }

    /* Create the images. */

    vgTargetImage = vgCreateImage(VG_sRGBA_8888, width, height, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgDstImage = vgCreateImage(VG_sRGBA_8888, width, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSrcImage = vgCreateImage(VG_sRGBA_8888, width, 1, VG_IMAGE_QUALITY_NONANTIALIASED);

    vgImageSubData(vgTargetImage, pukki_64x64_data, pukki_64x64_stride, VG_sRGBA_8888, 0, 0, width, height);

    /* Clear the background to opaque white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Loop over the scanlines from bottom to top */

    for (i = 0; i < height; i++)
    {
        static const VGImageChannel channels[] =
        {
            VG_RED,     /* vgLookupSingle() */
            VG_GREEN,   /* vgLookupSingle() */
            VG_BLUE,    /* vgLookupSingle() */
            VG_ALPHA,   /* vgLookupSingle() */
            0           /* vgLookup() */
        };

        VGboolean outputLinear = ((i & 1) != 0);
        VGboolean outputPremult = ((i & 2) != 0);
        int chanIdx = (i / 4) % (int)(sizeof(channels) / sizeof(channels[0]));

        /* Clear the lookup and permutation tables. */

        for (j = 0; j < 256; j++)
        {
            intLUT[j] = 0xffffffff;
            for (k = 0; k < 4; k++)
            {
                byteLUT[k][j] = (VGubyte)0xff;
                permut[k][j] = (VGubyte)j;
            }
        }

        /* Randomize the permutation tables. */

        for (j = 255; j >= 0; j--)
            for (k = 0; k < 4; k++)
            {
                int idx;
                VGubyte tmp;

                /* Generate a pseudo-random swap index. */
                {
                    VGuint a = 0x9e3779b9u + (VGuint)i;
                    VGuint b = 0x9e3779b9u + (VGuint)j;
                    VGuint c = 0x9e3779b9u + (VGuint)k;
                    a -= b; a -= c; a ^= (c>>13);
                    b -= c; b -= a; b ^= (a<<8);
                    c -= a; c -= b; c ^= (b>>13);
                    a -= b; a -= c; a ^= (c>>12);
                    b -= c; b -= a; b ^= (a<<16);
                    c -= a; c -= b; c ^= (b>>5);
                    a -= b; a -= c; a ^= (c>>3);
                    b -= c; b -= a; b ^= (a<<10);
                    c -= a; c -= b; c ^= (b>>15);
                    idx = (int)(c >> 1) % (j + 1);
                }

                /* Swap the current/selected indices. */

                tmp = permut[k][idx];
                permut[k][idx] = permut[k][j];
                permut[k][j] = tmp;
            }

        /* Use the permutation tables as the input RGBA values. */

        for (j = 0; j < width; j++)
        {
            pixels[j] = 0;
            for (k = 0; k < 4; k++)
                pixels[j] |= permut[k][j] << (24 - k * 8);
        }
        vgImageSubData(vgSrcImage, pixels, 0, VG_sRGBA_8888, 0, 0, width, 1);

        /* Query the pixel data of the target image in the output format,
         * and initialize the lookup tables to produce the same data. */
        {
            VGImageFormat dataFormat = (outputLinear) ?
                ((outputPremult) ? VG_lRGBA_8888_PRE : VG_lRGBA_8888) :
                ((outputPremult) ? VG_sRGBA_8888_PRE : VG_sRGBA_8888);
            vgGetImageSubData(vgTargetImage, pixels, 0, dataFormat, 0, i, width, 1);

            for (j = 0; j < width; j++)
            {
                VGuint rgba = pixels[j];
                if ((rgba & 0xff) == 0)
                    rgba = 0;

                if (chanIdx < 4)
                    intLUT[permut[chanIdx][j]] = rgba;
                else
                    for (k = 0; k < 4; k++)
                        byteLUT[k][permut[k][j]] = (VGubyte)(rgba >> (24 - k * 8));
            }
        }

        /* Perform the lookup. */

        if (chanIdx < 4)
            vgLookupSingle(vgDstImage, vgSrcImage, intLUT, channels[chanIdx],
                outputLinear, outputPremult);
        else
            vgLookup(vgDstImage, vgSrcImage, byteLUT[0], byteLUT[1], byteLUT[2], byteLUT[3],
                outputLinear, outputPremult);

        /* Write the pixels to the result. */

        vgSetPixels(0, i, vgDstImage, 0, 0, width, 1);
    }

    /* Clean up and save the result. */

    FREE(pixels);
    if (vgTargetImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgTargetImage);
    if (vgDstImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImage);
    if (vgSrcImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();
    return CT_NO_ERROR;
}

