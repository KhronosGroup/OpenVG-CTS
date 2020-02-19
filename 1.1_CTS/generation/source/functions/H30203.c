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
 * H30203_ImageClamping_by_NVIDIA
 *
 * Tests that all image operations correctly clamp the
 * color values to the alpha value when using premultiplied
 * image formats.
 *
 * The test consists of 8 subtests, one for each premultiplied
 * image format. The subtests are organized as follows:
 *
 * 0000: VG_sRGBA_8888_PRE
 * 0001: VG_sARGB_8888_PRE
 * 0002: VG_sBGRA_8888_PRE
 * 0003: VG_sABGR_8888_PRE
 * 0004: VG_lRGBA_8888_PRE
 * 0005: VG_lARGB_8888_PRE
 * 0006: VG_lBGRA_8888_PRE
 * 0007: VG_lABGR_8888_PRE
 *
 * Each subtest renders a 10x6 grid of results. Each grid item
 * is further divided vertically into three color channels.
 * In each of the cases, an image containing a horizontal color
 * gradient and a constant alpha of 2/3 is drawn. The row index
 * determines the method that is used to set the pixels of the
 * image, and the column index determines the method that is
 * used to draw the image.
 *
 * The rows (image creation, from top to bottom) are as follows:
 * 1st-4th: Different means of setting a gradient from 0 to 255.
 * 5th-10th: Different means of setting a gradient from 0 to 170.
 *
 * The columns (image display, from left to right) are as follows:
 * 1st: Use vgWritePixels() to draw a gradient from 0 to 255.
 * 2nd: Use vgSetPixels() to draw the image.
 * 3rd: Use vgDrawImage() to draw the image.
 * 4th: Use vgFillPath() to draw the image through a pattern paint.
 * 5th: Read image pixels and force their alpha to 1.
 * 6th: Use vgLookupSingle() to force the alpha to 1.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result H30203_ImageClamping_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const struct
    {
        VGImageFormat   imageFormat;
        VGuint          channelOrder;
        VGboolean       isLinear;
    } formats[] =
    {
        { VG_sRGBA_8888_PRE,    0x0123, VG_FALSE },
        { VG_sARGB_8888_PRE,    0x3012, VG_FALSE },
        { VG_sBGRA_8888_PRE,    0x2103, VG_FALSE },
        { VG_sABGR_8888_PRE,    0x3210, VG_FALSE },
        { VG_lRGBA_8888_PRE,    0x0123, VG_TRUE },
        { VG_lARGB_8888_PRE,    0x3012, VG_TRUE },
        { VG_lBGRA_8888_PRE,    0x2103, VG_TRUE },
        { VG_lABGR_8888_PRE,    0x3210, VG_TRUE }
    };

    int             imageWidth   = 10;
    int             imageHeight  = 2;
    VGImageFormat   imageFormat  = formats[subtest].imageFormat;
    VGuint          channelOrder = formats[subtest].channelOrder;
    VGboolean       isLinear     = formats[subtest].isLinear;
    VGuint*         buffer;
    VGuint*         gradient[3];
    VGuint*         tempGradient;
    VGuint*         luminanceIntLUT;
    VGuint*         decreaseIntLUT;
    VGubyte*        identityByteLUT;
    VGubyte*        decreaseByteLUT;
    VGImage         vgMainImage;
    VGImage         vgTempImage;
    VGPath          vgPath;
    VGPaint         vgPaint;
    VGuint          alphaMask;
    int             i, j, k;

    /* Allocate the temporary buffers. */

    buffer = (VGuint*)MALLOC((imageWidth * 4 + 256 * 2) * sizeof(VGuint) +
                             256 * 2 * sizeof(VGubyte));

    if (!buffer)
        return CT_ERROR;

    for (i = 0; i < 3; i++)
        gradient[i] = buffer + imageWidth * i;
    tempGradient    = buffer + imageWidth * 3;
    luminanceIntLUT = tempGradient + imageWidth;
    decreaseIntLUT  = luminanceIntLUT + 256;
    identityByteLUT = (VGubyte*)(decreaseIntLUT + 256);
    decreaseByteLUT = identityByteLUT + 256;

    /* Create two images with the selected format. */

    vgMainImage = vgCreateImage(imageFormat, imageWidth, imageHeight,
        VG_IMAGE_QUALITY_NONANTIALIASED);

    vgTempImage = vgCreateImage(imageFormat, imageWidth, imageHeight,
        VG_IMAGE_QUALITY_NONANTIALIASED);

    /* Create a rectangular path of the same size as the image. */
    {
        static const VGubyte cmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        VGfloat val[3];

        val[0] = (VGfloat)imageWidth;
        val[1] = (VGfloat)imageHeight;
        val[2] = 0.0f;

        vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

        vgAppendPathData(vgPath, sizeof(cmd), cmd, val);
    }

    /* Create a pattern paint from the main image. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
    vgPaintPattern(vgPaint, vgMainImage);
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Setup the gradient. */

    for (i = 0; i < 3; i++)
        for (j = 0; j < imageWidth; j++)
        {
            VGuint color = 0;
            for (k = 0; k < 4; k++)
            {
                int chn = (channelOrder >> (k * 4)) & 3;
                int val = (chn == 3) ? 170 :
                          (chn == i) ? (j + 1) * 255 / imageWidth : 0;
                color += val << (k * 8);
            }
            gradient[i][j] = color;
        }

    /* Setup the lookup tables. */

    for (i = 0; i < 256; i++)
    {
        luminanceIntLUT[i] = i * 0x01010100 + 0xff;
        decreaseIntLUT[i] = i * 2 / 3;
        identityByteLUT[i] = (VGubyte)i;
        decreaseByteLUT[i] = (VGubyte)decreaseIntLUT[i];
    }

    /* Determine the alpha mask value. */

    alphaMask = 0;
    for (i = 0; i < 4; i++)
        if (((channelOrder >> (i * 4)) & 3) == 3)
            alphaMask = 0xff << (i * 8);

    /* Clear the background to transparent black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti(VG_FILTER_FORMAT_PREMULTIPLIED, VG_TRUE);
    vgSeti(VG_FILTER_FORMAT_LINEAR, isLinear);

    /* Loop over the rows */

    for (i = 0; i < 10; i++)
        for (j = 0; j < 3; j++)
        {
            static const VGImageChannel channels[] =
            { VG_RED, VG_GREEN, VG_BLUE };

            static const VGfloat colorMatrix[20] =
            {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.6667f,
                0.0f, 0.0f, 0.0f, 0.0f
            };

            VGshort kernel = 1;
            int y = WINDSIZEY - (i * 3 + j + 1) * imageHeight;

            /* Initialize both images to an opaque variant of the gradient. */

            for (k = 0; k < imageWidth; k++)
                tempGradient[k] = gradient[j][k] | alphaMask;
            vgImageSubData(vgTempImage, tempGradient, 0, imageFormat,
                0, 0, imageWidth, imageHeight);
            vgCopyImage(vgMainImage, 0, 0, vgTempImage,
                0, 0, imageWidth, imageHeight, VG_FALSE);

            /* Process the main image depending on the current row */

            switch (i)
            {
            /* 1st row
             * Use vgImageSubData() to set the gradient with alpha = 2/3. */
            case 0:
                vgImageSubData(vgMainImage, gradient[j], 0, imageFormat,
                    0, 0, imageWidth, imageHeight);
                break;

            /* 2nd row
             * Use vgClearImage() to set the gradient with alpha = 2/3. */
            case 1:
                for (k = 0; k < imageWidth; k++)
                {
                    VGfloat color[4];
                    int chn;
                    for (chn = 0; chn < 4; chn++)
                        color[(channelOrder >> (chn * 4)) & 3] =
                            ((gradient[j][k] >> (chn * 8)) & 0xff) / 255.0f;
                    for (chn = 0; chn < 3; chn++)
                        color[chn] /= color[3];

                    vgSetfv(VG_CLEAR_COLOR, 4, color);
                    vgClearImage(vgMainImage, k, 0, 1, imageHeight);
                }
                break;

            /* 3rd row
             * Use vgColorMatrix() on all channels to multiply the alpha
             * with 2/3. The color channels are not modified, but they should
             * get clamped to the new alpha. */
            case 2:
                vgSeti(VG_FILTER_CHANNEL_MASK,
                    VG_RED | VG_GREEN | VG_BLUE | VG_ALPHA);
                vgColorMatrix(vgMainImage, vgTempImage, colorMatrix);
                break;

            /* 4th row
             * Use vgLookup() on all channels to multiply the alpha with
             * 2/3. The color channels are not modified, but they should get
             * clamped to the new alpha. */
            case 3:
                vgSeti(VG_FILTER_CHANNEL_MASK,
                    VG_RED | VG_GREEN | VG_BLUE | VG_ALPHA);
                vgLookup(vgMainImage, vgTempImage,
                    identityByteLUT,
                    identityByteLUT,
                    identityByteLUT,
                    decreaseByteLUT,
                    isLinear, VG_TRUE);
                break;

            /* 5th row
             * Use vgColorMatrix() on the alpha channel to multiply it
             * with 2/3. The color channels should get scaled to match the
             * new alpha. */
            case 4:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgColorMatrix(vgMainImage, vgTempImage, colorMatrix);
                break;

            /* 6th row
             * Use vgConvolve() with an 1x1 kernel on the alpha channel to
             * multiply it with 2/3. The color channels should get scaled to
             * match the new alpha. */
            case 5:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgConvolve(vgMainImage, vgTempImage, 1, 1, 0, 0,
                    &kernel, 0.6667f, 0.0f, VG_TILE_FILL);
                break;

            /* 7th row
             * Use vgSeparableConvolve() with an 1x1 kernel on the alpha
             * channel to multiply it with 2/3. The color channels should
             * get scaled to match the new alpha. */
            case 6:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgSeparableConvolve(vgMainImage, vgTempImage, 1, 1, 0, 0,
                    &kernel, &kernel, 0.6667f, 0.0f, VG_TILE_FILL);
                break;

            /* 8th row
             * Use vgGaussianBlur() on the alpha channel. The horizontal
             * deviation is negligible, and the vertical deviation is
             * selected so that it results in the alpha values being
             * multiplied with 2/3. The color channels should get scaled
             * to match the new alpha. */
            case 7:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgGaussianBlur(vgMainImage, vgTempImage,
                    0.1f, 0.937003f, VG_TILE_FILL);
                break;

            /* 9th row
             * The vgLookup() on the alpha channel to multiply it with
             * 2/3. The color channels should get scaled to match the new
             * alpha. */
            case 8:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgLookup(vgMainImage, vgTempImage,
                    decreaseByteLUT,
                    decreaseByteLUT,
                    decreaseByteLUT,
                    decreaseByteLUT,
                    isLinear, VG_TRUE);
                break;

            /* 10th row.
             * Use vgLookupSingle() on the alpha channel to multiply it
             * with 2/3. The color channels should get scaled to match the
             * new alpha. */
            case 9:
                vgSeti(VG_FILTER_CHANNEL_MASK, VG_ALPHA);
                vgLookupSingle(vgMainImage, vgTempImage, decreaseIntLUT, VG_ALPHA, isLinear, VG_TRUE);
                break;
            }

            /* 1st column
             * Use vgWritePixels() to draw the original gradient with
             * alpha = 2/3. */

            vgWritePixels(gradient[j], 0, imageFormat, 0, y, imageWidth, imageHeight);

            /* 2nd column
             * Use vgSetPixels() to draw the image. */

            vgSetPixels(imageWidth, y, vgMainImage, 0, 0, imageWidth, imageHeight);

            /* 3rd column
             * Use vgDrawImage() to draw the image. */

            vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
            vgLoadIdentity();
            vgTranslate((VGfloat)(imageWidth * 2), (VGfloat)y);
            vgDrawImage(vgMainImage);

            /* 4th column
             * Use vgDrawPath() to draw the pattern paint. */

            vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
            vgLoadIdentity();
            vgTranslate((VGfloat)(imageWidth * 3), (VGfloat)y);
            vgDrawPath(vgPath, VG_FILL_PATH);

            /* 5th column
             * Read the image pixels, force their alpha to 1,
             * and draw the result using vgWritePixels(). */

            vgGetImageSubData(vgMainImage, tempGradient, 0, imageFormat, 0, 0, imageWidth, 1);
            for (k = 0; k < imageWidth; k++)
                tempGradient[k] |= alphaMask;
            vgWritePixels(tempGradient, 0, imageFormat, imageWidth * 4, y, imageWidth, imageHeight);

            /* 6th column
             * Use vgLookupSingle() to force the alpha to 1,
             * and draw the resulting image with vgSetPixels(). */

            vgSeti(VG_FILTER_CHANNEL_MASK, channels[j] | VG_ALPHA);
            vgLookupSingle(vgTempImage, vgMainImage, luminanceIntLUT, channels[j], isLinear, VG_TRUE);
            vgSetPixels(imageWidth * 5, y, vgTempImage, 0, 0, imageWidth, imageHeight);
        }

    /* Clean up and save the result. */

    FREE(buffer);
    if (vgMainImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgMainImage);
    if (vgTempImage != VG_INVALID_HANDLE)
        vgDestroyImage(vgTempImage);
    if (vgPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPath);
    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

