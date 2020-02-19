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
 * K20204_ColorTransform_by_NVIDIA
 *
 * Tests that possible color transformation special case
 * optimizations work as expected, by varying a single coefficient
 * or bias at a time while keeping the rest of the parameters at
 * their defaults.
 *
 * The resulting image consists of a 4x4 grid of image formats.
 * Each element is divided into 4 slices vertically, each
 * corresponding to a single color channel. The slices are
 * further divided into two. The bottom one is drawn by varying
 * coefficient associated with the color channel, while the top
 * one is drawn by varying the bias.
 *
 * Each 1x2 column of the slices is rendered independently using
 * vgDrawImage(). The contents of the image are initialized to the
 * sRGBA_NONPRE color of 0x80808080. The color transformation
 * parameters are selected so that the columns form a smooth color
 * ramp from 0.167 to 1.5. The color values exceeding 1.0 at the
 * right-hand side should be clamped by the implementation.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20204_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    static const struct
    {
        VGImageFormat   vgFormat;
        VGuint          depths;
    } formats[] =
    {
        { VG_sRGBX_8888,        0x8880 },
        { VG_lRGBX_8888,        0x8880 },
        { VG_sRGBA_8888,        0x8888 },
        { VG_lRGBA_8888,        0x8888 },
        { VG_sRGBA_8888_PRE,    0x8888 },
        { VG_lRGBA_8888_PRE,    0x8888 },
        { VG_sRGB_565,          0x5650 },
        { VG_sRGBA_5551,        0x5551 },
        { VG_sRGBA_4444,        0x4444 },
        { VG_sL_8,              0x8880 },
        { VG_lL_8,              0x8880 },
        { VG_BW_1,              0x1110 },
        { VG_A_8,               0x0008 },
        { VG_A_1,               0x0001 },
        { VG_A_4,               0x0004 }
    };

    int itemW       = 16;
    int itemH       = 16;
    int numPerRow   = 4;
    int i, j, k;

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

    /* Loop over image formats. */

    for (i = 0; i < (int)(sizeof(formats) / sizeof(formats[0])); i++)
    {
        VGImage vgImage;
        
        /* Create the image. */
        {
            VGuint color = 0x80808080;
            vgImage = vgCreateImage(formats[i].vgFormat, 1, 2, VG_IMAGE_QUALITY_NONANTIALIASED);
            vgImageSubData(vgImage, &color, 0, VG_sRGBA_8888, 0, 0, 1, 2);
        }

        /* Loop over intensities. */

        for (j = 0; j < itemW; j++)
        {
            VGfloat values[] = { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };
            VGfloat target = (VGfloat)(j + 1) * 1.5f / (VGfloat)itemW;

            /* Setup the transformation matrix. */

            vgLoadIdentity();
            vgTranslate(
                (VGfloat)((i % numPerRow) * itemW + j),
                (VGfloat)((i / numPerRow) * itemH));

            /* Loop over channels. */

            for (k = 0; k < 4; k++)
            {
                int depth = (formats[i].depths >> (12 - k * 4)) & 0xf;
                VGfloat value = (depth >= 2) ? 0.5f : 1.0f;

                /* Modulate the color to reach the target. */

                values[k] = target / value;
                vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
                values[k] = 1.0f;
                vgDrawImage(vgImage);
                vgTranslate(0.0f, 2.0f);

                /* Bias the color to reach the target. */

                values[k + 4] = target - value;
                vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
                values[k + 4] = 0.0f;
                vgDrawImage(vgImage);
                vgTranslate(0.0f, 2.0f);
            }
        }

        /* Clean up. */

        vgDestroyImage(vgImage);
    }

    /* Save the result. */

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

