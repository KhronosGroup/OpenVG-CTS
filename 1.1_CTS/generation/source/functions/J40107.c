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
 * J40107_ImageFilter_by_NVIDIA
 *
 * Tests vgColorMatrix() in extreme cases. The test draws
 * each pixel of the result independently by selecting an
 * arbitrary input color, and executing vgColorMatrix()
 * with an arbitrary transformation matrix. The biases of
 * the matrix are selected so that the resulting image
 * forms a 2D rainbow gradient.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result J40107_ImageFilter_by_NVIDIA(CT_File *AnsFile)
{
    VGImage vgDstImage;
    VGImage vgSrcImage;
    int     x, y;
    int     i, j;

    /* Create the images. */

    vgDstImage = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgSrcImage = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Clear the background to opaque white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Loop over the result pixels. */

    for (y = 0; y < WINDSIZEY; y++)
        for (x = 0; x < WINDSIZEX; x++)
        {
            int     hue = (x * 16 + y * 4) * 256 / WINDSIZEX;
            VGfloat bright = (VGfloat)y / (VGfloat)WINDSIZEY;
            VGfloat scale = EXP((bright - 0.5f) * 8.0f);
            VGfloat input[4];
            VGfloat target[4];
            VGfloat matrix[20];

            /* Select an arbitrary input color. */

            for (i = 0; i < 4; i++)
            {
                int value = ((x + 7) * (y + 7) * (i + 7)) & 255;
                if (i == 3)
                    value = value / 3 + 170;
                input[i] = (VGfloat)value / 255.0f;
            }

            /* Select the target (expected) color based on the hue and brightness. */

            for (i = 0; i < 4; i++)
            {
                static const VGint grayCodes[16] =
                {
                    0x0000, 0x0001, 0x0011, 0x0010,
                    0x0110, 0x0111, 0x0101, 0x0100,
                    0x1100, 0x1101, 0x1111, 0x1110,
                    0x1010, 0x1011, 0x1001, 0x1000
                };
                int lerpA = (grayCodes[(hue >> 8) & 15] >> (i * 4)) & 1;
                int lerpB = (grayCodes[((hue >> 8) + 1) & 15] >> (i * 4)) & 1;
                int lerpC = lerpA * (256 - (hue & 255)) + lerpB * (hue & 255);
                target[i] = (VGfloat)lerpC * bright / 256.0f;
            }
            target[3] = (target[3] + 2.0f) / 3.0f;

            /* Select the matrix coefficients to yield the target color. */

            for (i = 0; i < 4; i++)
            {
                static const VGfloat coefSets[][4] =
                {
                    { 1.0f,  0.0f,  0.0f,  0.0f },
                    { 1.0f,  1.0f,  0.0f,  0.0f },
                    { 0.0f,  0.0f,  1.0f, -1.0f },
                    { 0.2f, -0.4f,  0.6f, -0.8f }
                };

                int setIdx = ((x + y * WINDSIZEX) >> (i * 2)) & 3;

                matrix[i + 16] = target[i];
                for (j = 0; j < 4; j++)
                {
                    VGfloat coef = coefSets[setIdx][(i - j) & 3] * scale;
                    matrix[i + j * 4] = coef;
                    matrix[i + 16] -= coef * input[j];
                }
            }

            /* Set the source color. */

            vgSetfv(VG_CLEAR_COLOR, 4, input);
            vgClearImage(vgSrcImage, 0, 0, 1, 1);

            /* Perform the color transformation. */

            vgColorMatrix(vgDstImage, vgSrcImage, matrix);

            /* Copy the resulting pixels to the screen. */

            vgSetPixels(x, y, vgDstImage, 0, 0, 1, 1);
        }

    /* Clean up and save the result. */

    if (vgDstImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgDstImage);
    if (vgSrcImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgSrcImage);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();
    return CT_NO_ERROR;
}

