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
 * H30204_ImageChildren_by_NVIDIA
 *
 * Tests that vgDrawImage() and vgGetParent() work as
 * expected on child images, when their ancestors or
 * siblings are modified or destroyed.
 *
 * The test creates four images, organized according to the
 * following diagram:
 *
 *     vgGrandParent
 *           |
 *       vgParent
 *          / \
 *         /   \
 *   vgChildA vgChildB
 *
 * The test performs a number of operations on the images,
 * and draws a single row of results after each operation.
 *
 * The row is divided vertically into three subrows, each
 * drawn with a different image quality. The subrows contain
 * the following items, from left to right:
 *
 * A. The image returned by vgGetParent(vgChildA)
 * B. vgChildA
 * C. vgChildB
 * D. vgGetParent(vgChildA) minified by a factor of two
 * E. vgChildA minified by a factor of two
 * F. vgChildB minified by a factor of two
 *
 * The operations (and their corresponding rows from top to
 * bottom) are as follows:
 *
 * 1. Fill the images with constant colors.
 * 2. Fill vgChildA with black.
 * 3. Destroy vgParent.
 * 4. Destroy vgGrandParent.
 * 5. Fill vgChildB with red.
 * 6. Destroy vgChildB.
 */

#include "../main.h"
#include "../util/util.h"

static void fillImage(VGImage vgImage, VGuint rgba)
{
    VGfloat color[4];
    color[0] = (VGfloat)(rgba >> 24) / 255.0f;
    color[1] = (VGfloat)((rgba >> 16) & 0xff) / 255.0f;
    color[2] = (VGfloat)((rgba >> 8) & 0xff) / 255.0f;
    color[3] = (VGfloat)(rgba & 0xff) / 255.0f;

    vgSetfv(VG_CLEAR_COLOR, 4, color);
    vgClearImage(vgImage, 0, 0,
        vgGetParameteri(vgImage, VG_IMAGE_WIDTH),
        vgGetParameteri(vgImage, VG_IMAGE_HEIGHT));
}

static void drawImage(VGImage vgImage)
{
    if (vgImage != VG_INVALID_HANDLE)
        vgDrawImage(vgImage);
}

static void drawImages(VGImage vgParent, VGImage vgChildA, VGImage vgChildB)
{
    static const VGImageQuality qualities[] =
    {
        VG_IMAGE_QUALITY_NONANTIALIASED,
        VG_IMAGE_QUALITY_FASTER,
        VG_IMAGE_QUALITY_BETTER
    };

    int i;

    /* Draw a row of images for each image quality. */

    for (i = 0; i < (int)(sizeof(qualities) / sizeof(qualities[0])); i++)
    {
        vgSeti(VG_IMAGE_QUALITY, qualities[i]);

        /* Draw the images without scaling. */

        drawImage(vgParent);
        vgTranslate(18.0f, 0.0f);
        drawImage(vgChildA);
        vgTranslate(12.0f, 0.0f);
        drawImage(vgChildB);
        vgTranslate(12.0f, 0.0f);

        /* Draw the images minified by a factor of two.
         * Two copies of the minified images are drawn on top
         * of each other in order to avoid gaps. */

        vgScale(0.5f, 0.5f);
        drawImage(vgParent);
        vgTranslate(0.0f, 2.0f);
        drawImage(vgParent);
        vgTranslate(18.0f, -2.0f);
        drawImage(vgChildA);
        vgTranslate(0.0f, 2.0f);
        drawImage(vgChildA);
        vgTranslate(12.0f, -2.0f);
        drawImage(vgChildB);
        vgTranslate(0.0f, 2.0f);
        drawImage(vgChildB);
        vgTranslate(12.0f, -2.0f);

        /* Revert the scaling and proceed to the next row. */

        vgScale(2.0f, 2.0f);
        vgTranslate(-63.0f, -2.0f);
    }

    /* Add a vertical gap of 4 pixels between the cases. */

    vgTranslate(0.0f, -4.0f);
}

CT_Result H30204_ImageChildren_by_NVIDIA(CT_File *AnsFile)
{
    VGImage vgGrandParent;
    VGImage vgParent;
    VGImage vgChildA;
    VGImage vgChildB;

    /* Create the images. */

    vgGrandParent = vgCreateImage(VG_sRGBA_8888, 16, 2,
        VG_IMAGE_QUALITY_NONANTIALIASED | VG_IMAGE_QUALITY_FASTER | VG_IMAGE_QUALITY_BETTER);

    vgParent = vgChildImage(vgGrandParent, 0, 0, 14, 2);
    vgChildA = vgChildImage(vgParent, 2, 0, 10, 2);
    vgChildB = vgChildImage(vgParent, 4, 0, 10, 2);

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgTranslate(1.0f, (VGfloat)WINDSIZEY - 6.0f);

    /* 1st row
     * Fill the grandparent with blue, the left-hand child with red, and
     * the right-hand child with green. Since the children overlap, a large
     * portion of the left-hand child is also filled with green. */

    fillImage(vgGrandParent, 0x0000ffff);
    fillImage(vgChildA, 0xff0000ff);
    fillImage(vgChildB, 0x00ff00ff);
    drawImages(vgGetParent(vgChildA), vgChildA, vgChildB);

    /* 2nd row
     * Fill the left-hand child with black. The parent and
     * the right-hand child should reflect the change as well. */

    fillImage(vgChildA, 0x000000ff);
    drawImages(vgGetParent(vgChildA), vgChildA, vgChildB);

    /* 3rd row
     * Destroy the parent image. vgGetParent() should now return the
     * grandparent. */

    vgDestroyImage(vgParent);
    drawImages(vgGetParent(vgChildA), vgChildA, vgChildB);

    /* 4th row
     * Destroy the grandparent as well. vgGetParent() should now
     * return the left-hand child. */

    vgDestroyImage(vgGrandParent);
    drawImages(vgGetParent(vgChildA), vgChildA, vgChildB);

    /* 5th row
     * Fill the right-hand child with red. The left-hand child should
     * reflect the change, even though the images have no common
     * ancestors. */

    fillImage(vgChildB, 0xff0000ff);
    drawImages(vgGetParent(vgChildA), vgChildA, vgChildB);

    /* 6th row
     * Destroy the right-handle child image. The left-hand child should
     * stay unchanged. */

    vgDestroyImage(vgChildB);
    drawImages(vgGetParent(vgChildA), vgChildA, VG_INVALID_HANDLE);

    /* Clean up and save the result. */

    if (vgChildA != VG_INVALID_HANDLE)
        vgDestroyImage(vgChildA);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

