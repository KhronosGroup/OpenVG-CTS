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
 * H30205_ImageChildren_by_NVIDIA
 *
 * Tests that using a ridiculously long (2048) chain of
 * child images can be created successfully, and that
 * operating on the chain does not cause a stack overflow
 * within the implementation.
 *
 * From the memory footprint standpoint, the requirement
 * of being able to create 2048 child images is reasonable.
 * To store a bitmap font efficiently, an application
 * might pack all the glyphs into a single large image.
 * It would then proceed to create a child image for each
 * glyph, and add the image to a VGFont object. For CJK
 * fonts, the application may need to store thousands of
 * glyphs this way.
 *
 * There are two common cases in which an OpenVG
 * implementation may end up performing an unbounded
 * recursion: image destruction and mipmap invalidation.
 * An unbounded recursion is generally undesirable,
 * since some mobile platforms have a very limited stack.
 * The test tries to trigger both of the cases to ensure
 * that they do not lead to a crash.
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

CT_Result H30205_ImageChildren_by_NVIDIA(CT_File *AnsFile)
{
    int     numChildren = 2048;
    int     imageWidth  = 32;
    int     imageHeight = 32;
    VGImage vgParent;
    VGImage vgChild;
    int     i;

    /* Create the parent image. */

    vgParent = vgCreateImage(VG_sRGBX_8888, imageWidth, imageHeight,
        VG_IMAGE_QUALITY_BETTER);

    /* Construct a chain of child images. */

    vgChild = vgParent;
    for (i = 0; i < numChildren; i++)
    {
        VGImage image = vgChildImage(vgChild, 0, 0, imageWidth, imageHeight);
        if (image != VG_INVALID_HANDLE)
            vgChild = image;
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_BETTER);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();

    /* Bottom left
     * Fill vgChild with red and draw it. */

    fillImage(vgChild, 0xff0000ff);
    vgDrawImage(vgChild);

    /* Bottom right
     * Fill vgParent with green and draw vgChild. */

    vgTranslate((VGfloat)imageWidth, 0.0f);
    fillImage(vgParent, 0x00ff00ff);
    vgDrawImage(vgChild);

    /* Destroy all images except vgParent and vgChild. */
    {
        VGImage image = vgGetParent(vgChild);
        while (image != vgParent)
        {
            VGImage parent = vgGetParent(image);
            vgDestroyImage(image);
            image = parent;
        }
    }

    /* Top left
     * Fill vgParent with magenta and draw vgChild. */

    vgTranslate(-(VGfloat)imageWidth, (VGfloat)imageHeight);
    fillImage(vgParent, 0xff00ffff);
    vgDrawImage(vgChild);

    /* Top right
     * Fill vgParent with cyan, destroy it, and draw vgChild. */

    vgTranslate((VGfloat)imageWidth, 0.0f);
    fillImage(vgParent, 0x00ffffff);
    vgDestroyImage(vgParent);
    vgDrawImage(vgChild);

    /* Destroy vgChild. */

    vgDestroyImage(vgChild);

    /* Clean up and save the result. */

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_TEST_BUFFER();    
    return CT_NO_ERROR;
}

