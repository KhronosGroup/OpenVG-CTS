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
 * F20103_Masking_by_NVIDIA
 *
 * Tests vgMask() on different image formats, as the channel from which
 * the function obtains the mask coverage values depends on the format.
 *
 * The resulting image consists of a 4x4 grid of image formats.
 * The images are such that using the correct mask channel yields
 * a checkerboard pattern, while using an incorrect channel yields
 * a horizontal gradient.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result F20103_Masking_by_NVIDIA(CT_File *AnsFile)
{
    static const struct
    {
        VGImageFormat   vgFormat;
        VGuint          maskUnit;
    } imageFormats[] =
    {
        { VG_sRGBX_8888,        0x01000000u },
        { VG_lRGBX_8888,        0x01000000u },
        { VG_sRGBA_8888,        0x00000001u },
        { VG_lRGBA_8888,        0x00000001u },
        { VG_sRGBA_8888_PRE,    0x00000001u },
        { VG_lRGBA_8888_PRE,    0x00000001u },
        { VG_sRGB_565,          0x01000000u },
        { VG_sRGBA_5551,        0x00000001u },
        { VG_sRGBA_4444,        0x00000001u },
        { VG_sL_8,              0x01010100u },
        { VG_lL_8,              0x01010100u },
        { VG_BW_1,              0x01010100u },
        { VG_A_8,               0x00000001u },
        { VG_A_1,               0x00000001u },
        { VG_A_4,               0x00000001u }
    };

    int imgW = 16;
    int imgH = 16;
    VGuint* buffer;
    int i;

    /* Set the surface mask to one. */

    vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, 64, 64);

    /* Allocate the pixel buffer. */

    buffer = MALLOC(imgW * imgH * sizeof(VGuint));
    if (!buffer)
        return CT_ERROR;

    /* Draw a grid of images into the surface mask. */

    for (i = 0; i < (int)(sizeof(imageFormats) / sizeof(imageFormats[0])); i++)
    {
        VGuint maskUnit = imageFormats[i].maskUnit;
        VGImage vgImage;
        int x, y, idx;

        /* Generate image pixel data. */
        
        idx = 0;
        for (y = 0; y < imgH; y++)
            for (x = 0; x < imgW; x++)
            {
                int maskValue = ((y * 2 >= imgH) == (x *2 >= imgW)) ? 0xff : 0x00;
                int nonMaskValue = x * 255 / (imgW - 1);
                buffer[idx] = maskUnit * maskValue + (0x01010101 - maskUnit) * nonMaskValue;
                idx++;
            }

        /* Create the image. */

        vgImage = vgCreateImage(imageFormats[i].vgFormat, imgW, imgH,
            VG_IMAGE_QUALITY_NONANTIALIASED);
        vgImageSubData(vgImage, buffer, imgW * sizeof(VGuint),
            VG_sRGBA_8888, 0, 0, imgW, imgH);

        /* Draw the image to the mask. */
        {
            int numPerRow = WINDSIZEX / imgW;
            vgMask(vgImage, VG_SET_MASK,
                (i % numPerRow) * imgW, (i / numPerRow) * imgH, imgW, imgH);
        }

        /* Clean up. */

        vgDestroyImage(vgImage);
    }

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

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

    FREE(buffer);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

