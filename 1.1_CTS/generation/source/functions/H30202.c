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
 * H30202_ImageBlit_by_NVIDIA
 *
 * Tests the pixel blit functions on different image
 * formats, blit rectangle orientations, and child
 * images.
 *
 * The test consists of 21 subtest, each covering a
 * combination of a blit operation and an image layout.
 * Each subtest is further divided into 4x4 grid of
 * destination image formats.
 *
 * For each destination image format, the test
 * executes the subtest specific blit operation 25
 * times, with different source images and blit
 * rectangles. Most of the blit rectangles extend
 * beyond the image bounds, and the test expects
 * the implementation to clip them correctly.
 *
 * All blit operations except op A are identical in
 * that they copy a portion of the source image pixels
 * to the destination image. The operations are as follows:
 *
 * Op A: vgClear()
 * Op B: vgCopyImage()
 * Op C: vgGetImageSubData() -> vgImageSubData()
 * Op D: vgSetPixels() -> vgGetPixels()
 * Op E: vgGetImageSubData() -> vgWritePixels() -> vgGetPixels()
 * Op F: vgSetPixels() -> vgReadPixels() -> vgImageSubData()
 * Op G: vgSetPixels() -> vgCopyPixels() -> vgGetPixels()
 *
 * Image layouts:
 *
 * Layout A: Src and dst are separate parent images.
 * Layout B: Src and dst share a common parent image.
 *           Src spans the rectangle (0, 0, 16, 16).
 *           Dst spans the rectangle (16, 16, 32, 32).
 * Layout C: Src and dst share a common parent image.
 *           Src spans the rectangle (16, 16, 32, 32).
 *           Dst spans the rectangle (0, 0, 16, 16).
 *
 * The subtests are organized as follows:
 *
 * 0000: Op A, layout A
 * 0001: Op A, layout B
 * 0002: Op A, layout C
 * 0003: Op B, layout A
 * 0004: Op B, layout B
 * 0005: Op B, layout C
 * 0006: Op C, layout A
 * 0007: Op C, layout B
 * 0008: Op C, layout C
 * 0009: Op D, layout A
 * 0010: Op D, layout B
 * 0011: Op D, layout C
 * 0012: Op E, layout A
 * 0013: Op E, layout B
 * 0014: Op E, layout C
 * 0015: Op F, layout A
 * 0016: Op F, layout B
 * 0017: Op F, layout C
 * 0018: Op G, layout A
 * 0019: Op G, layout B
 * 0020: Op G, layout C
 */

#include "../main.h"
#include "../util/util.h"

/* Source and destination rectangle specifications
 * for a blit operation. */

typedef struct
{
    VGint   dx;
    VGint   dy;
    VGint   sx;
    VGint   sy;
    VGint   w;
    VGint   h;
    VGuint  color;  /* RGBA color for vgClear(). */
} CTBlitOp;

/* Intersects a blit operation with the given source X range. */

static void intersectSrcX(CTBlitOp* r, VGint x1, VGint x2)
{
    if (r->sx < x1)
    {
        int diff = x1 - r->sx;
        r->dx += diff;
        r->w -= diff;
        r->sx = x1;
    }
    if (r->w > x2 - r->sx)
        r->w = x2 - r->sx;
}

/* Intersects a blit operation with the given source Y range. */

static void intersectSrcY(CTBlitOp* r, VGint y1, VGint y2)
{
    if (r->sy < y1)
    {
        int diff = y1 - r->sy;
        r->dy += diff;
        r->h -= diff;
        r->sy = y1;
    }
    if (r->h > y2 - r->sy)
        r->h = y2 - r->sy;
}

/* Intersects a blit operation with the given destination X range. */

static void intersectDstX(CTBlitOp* r, VGint x1, VGint x2)
{
    if (r->dx < x1)
    {
        int diff = x1 - r->dx;
        r->sx += diff;
        r->w -= diff;
        r->dx = x1;
    }
    if (r->w > x2 - r->dx)
        r->w = x2 - r->dx;
}

/* Intersects a blit operation with the given destination Y range. */

static void intersectDstY(CTBlitOp* r, VGint y1, VGint y2)
{
    if (r->dy < y1)
    {
        int diff = y1 - r->dy;
        r->sy += diff;
        r->h -= diff;
        r->dy = y1;
    }
    if (r->h > y2 - r->dy)
        r->h = y2 - r->dy;
}

CT_Result H30202_ImageBlit_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const struct
    {
        VGImageFormat   vgFormat;
        VGint           bpp;
    } imageFormats[] =
    {
        { VG_sRGBX_8888,        32 },
        { VG_lRGBX_8888,        32 },
        { VG_sRGBA_8888,        32 },
        { VG_lRGBA_8888,        32 },
        { VG_sRGBA_8888_PRE,    32 },
        { VG_lRGBA_8888_PRE,    32 },
        { VG_sRGB_565,          16 },
        { VG_sRGBA_5551,        16 },
        { VG_sRGBA_4444,        16 },
        { VG_sL_8,              8 },
        { VG_lL_8,              8 },
        { VG_BW_1,              1 },
        { VG_A_8,               8 },
        { VG_A_1,               1 },
        { VG_A_4,               4 }
    };

    static const VGfloat bgColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    int     blitType    = subtest / 3;
    int     layout      = subtest % 3;
    int     imageW      = 16;
    int     imageH      = 16;
    int     numPerRow   = 4;
    int     numFormats  = sizeof(imageFormats) / sizeof(imageFormats[0]);
    VGuint* buffer;
    int     stride      = imageW * sizeof(VGuint);
    VGImage vgSrcImages[sizeof(imageFormats) / sizeof(imageFormats[0])];
    VGImage vgDstImages[sizeof(imageFormats) / sizeof(imageFormats[0])];
    int     i, j;

    /* Allocate the pixel buffer. */

    buffer = MALLOC(imageH * stride);
    if (!buffer)
        return CT_ERROR;

    /* Create the images. */

    for (i = 0; i < numFormats; i++)
        if (layout == 0)
        {
            vgSrcImages[i] = vgCreateImage(imageFormats[i].vgFormat,
                imageW, imageH, VG_IMAGE_QUALITY_NONANTIALIASED);
            vgDstImages[i] = vgCreateImage(imageFormats[i].vgFormat,
                imageW, imageH, VG_IMAGE_QUALITY_NONANTIALIASED);
        }
        else
        {
            VGImage vgParent = vgCreateImage(imageFormats[i].vgFormat,
                imageW * 2, imageH * 2, VG_IMAGE_QUALITY_NONANTIALIASED);
            VGImage vgChildA = vgChildImage(vgParent, 0, 0, imageW, imageH);
            VGImage vgChildB = vgChildImage(vgParent, imageW, imageH, imageW, imageH);

            vgSrcImages[i] = (layout == 1) ? vgChildA : vgChildB;
            vgDstImages[i] = (layout == 1) ? vgChildB : vgChildA;
            vgDestroyImage(vgParent);
        }

    /* Initialize the source image pixels. */

    for (i = 0; i < numFormats; i++)
    {
        int idx = 0;
        int x, y;
        for (y = 0; y < imageH; y++)
            for (x = 0; x < imageW; x++)
            {
                int xx = x * 255 / (imageW - 1);
                int yy = y * 255 / (imageH - 1);

                /* Modify the coordinates based on image index. */

                if ((i & 1) != 0)
                    xx = 255 - xx;
                if ((i & 2) != 0)
                    yy = 255 - yy;
                if ((i & 4) != 0)
                {
                    int t = xx;
                    xx = yy;
                    yy = t;
                }
                if ((i & 8) != 0)
                    xx ^= 128;

                /* Select a color for the pixel. */

                buffer[idx] =
                    0x01000000 * xx +
                    0x00010000 * yy +
                    0x00000100 * (255 - xx) +
                    0x00000001 * (255 - xx * 2 / 3);
                idx++;
            }

        /* Upload the pixels. */

        vgImageSubData(vgSrcImages[i], buffer, stride,
            VG_sRGBA_8888, 0, 0, imageW, imageH);
    }

    /* Process each destination image. */

    for (i = 0; i < numFormats; i++)
    {
        static const CTBlitOp ops[] =
        {
            /* dx          dy          sx          sy          w           h           color */
            { 0xffff8011, 0x00000000, 0xffff8011, 0x00000000, 0x00007fff, 0x00007fff, 0x00000000 },

            { 0xfffffff3, 0x00000000, 0x00000000, 0x00000000, 0x00000010, 0x00000010, 0x00007777 },
            { 0x0000000d, 0x00000000, 0x00000000, 0x00000000, 0x7fffffff, 0x00000010, 0x00007777 },
            { 0x00000000, 0xfffffff3, 0x00000000, 0x00000000, 0x00000010, 0x7fffffff, 0x00007777 },
            { 0x00000000, 0x0000000d, 0x00000000, 0x00000000, 0x7fffffff, 0x7fffffff, 0x00007777 },

            { 0xffff7ff3, 0xffff7ff3, 0xffff8000, 0xffff8000, 0x00008010, 0x00008010, 0x0000ffff },
            { 0x0000000d, 0xfffffff3, 0x00000000, 0x00000000, 0x00000003, 0x00000010, 0x0000ffff },
            { 0xfffffff3, 0x0000000d, 0x00000000, 0x00000000, 0x00000010, 0x00000003, 0x0000ffff },
            { 0x0000000d, 0x0000000d, 0x00000000, 0x00000000, 0x00000003, 0x00000003, 0x0000ffff },

            { 0xfffffff6, 0xfffffffd, 0xfffffff3, 0xfffffffa, 0x00000010, 0x00000010, 0x00770077 },
            { 0x0000000a, 0xfffffffd, 0x0000000d, 0xfffffffa, 0x7fffffff, 0x00000010, 0x00770077 },
            { 0xfffffffd, 0xfffffff6, 0xfffffffa, 0xfffffff3, 0x00000010, 0x00000010, 0x00770077 },
            { 0xfffffffd, 0x0000000a, 0xfffffffa, 0x0000000d, 0x00000010, 0x7fffffff, 0x00770077 },

            { 0xfffffff6, 0xfffffff6, 0xfffffff3, 0xfffffff3, 0x00000010, 0x00000010, 0x00ff00ff },
            { 0x0000000a, 0xfffffff6, 0x0000000d, 0xfffffff3, 0x00000003, 0x00000010, 0x00ff00ff },
            { 0xfffffff6, 0x0000000a, 0xfffffff3, 0x0000000d, 0x00000010, 0x00000003, 0x00ff00ff },
            { 0x0000000a, 0x0000000a, 0x0000000d, 0x0000000d, 0x00000003, 0x00000003, 0x00ff00ff },

            { 0x80000000, 0x80000001, 0x00000000, 0x80000001, 0x00007fff, 0x00007fff, 0xff0000ff },
            { 0x00000001, 0x80000000, 0x80000001, 0x80000000, 0x00007fff, 0x00007fff, 0xff0000ff },
            { 0x80000000, 0x80000001, 0x00000000, 0x80000001, 0x00000001, 0x00000001, 0xff0000ff },
            { 0x00000001, 0x80000000, 0x80000001, 0x80000000, 0x00000001, 0x00000001, 0xff0000ff },

            { 0x7fffffff, 0x7ffffffe, 0x00000000, 0x7ffffffe, 0x7fffffff, 0x7fffffff, 0xff0000ff },
            { 0x00000001, 0x7fffffff, 0x7ffffffe, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0xff0000ff },
            { 0x7fffffff, 0x7ffffffe, 0x00000000, 0x7ffffffe, 0x00000001, 0x00000001, 0xff0000ff },
            { 0x00000001, 0x7fffffff, 0x7ffffffe, 0x7fffffff, 0x00000001, 0x00000001, 0xff0000ff }
        };

        /* Clear the surface and the destination image to solid white. */

        vgSetfv(VG_CLEAR_COLOR, 4, bgColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
        vgClearImage(vgDstImages[i], 0, 0, imageW, imageH);

        for (j = 0; j < (int)(sizeof(ops) / sizeof(ops[0])); j++)
        {
            CTBlitOp        op          = ops[j];
            CTBlitOp        opDst;
            CTBlitOp        opSrc;
            CTBlitOp        opBoth;
            int             srcIdx      = j % numFormats;
            VGImage         vgDstImage  = vgDstImages[i];
            VGImage         vgSrcImage  = vgSrcImages[srcIdx];
            VGImageFormat   srcFormat   = imageFormats[srcIdx].vgFormat;
            int             srcBPP      = imageFormats[srcIdx].bpp;

            /* Less than 32 bits per pixel -> intersect the op X
             * coordinates with the images, to make sure that the
             * read/write pointers are aligned properly. */

            opDst = op;
            if (srcBPP < 32)
            {
                intersectDstX(&opDst, 0, imageW);
                intersectSrcX(&opDst, 0, imageW);
            }

            /* opDst = op to use for writing the destination. */

            intersectSrcX(&opDst, 0, imageW);
            intersectSrcY(&opDst, 0, imageH);

            /* opSrc = op to use for reading the source. */

            opSrc = opDst;
            intersectDstX(&opSrc, 0, imageW);
            intersectDstY(&opSrc, 0, imageH);

            /* opBoth = op to use for accessing intermediate storage. */

            opBoth = opSrc;
            intersectSrcX(&opBoth, 0, imageW);
            intersectSrcY(&opBoth, 0, imageH);

            /* Execute a blit operation. */

            switch (blitType)
            {
            /* vgClear(). */
            case 0:
                {
                    VGfloat color[4];
                    color[0] = (VGfloat)(op.color >> 24) / 255.0f;
                    color[1] = (VGfloat)((op.color >> 16) & 0xff) / 255.0f;
                    color[2] = (VGfloat)((op.color >> 8) & 0xff) / 255.0f;
                    color[3] = (VGfloat)(op.color & 0xff) / 255.0f;
                    vgSetfv(VG_CLEAR_COLOR, 4, color);
                    intersectSrcX(&op, 0, imageW);
                    intersectSrcY(&op, 0, imageH);
                    if (op.w > 0 && op.h > 0)
                        vgClearImage(vgDstImage, op.dx, op.dy, op.w, op.h);
                }
                break;

            /* vgCopyImage(). */
            case 1:
                vgCopyImage(
                    vgDstImage, op.dx, op.dy,
                    vgSrcImage, op.sx, op.sy,
                    op.w, op.h, VG_FALSE);
                break;

            /* vgGetImageSubData() -> vgImageSubData(). */
            case 2:
                if (opSrc.w > 0 && opSrc.h > 0)
                    vgGetImageSubData(vgSrcImage,
                        buffer + opSrc.dx + opSrc.dy * imageW, stride,
                        srcFormat, opSrc.sx, opSrc.sy, opSrc.w, opSrc.h);

                if (opDst.w > 0 && opDst.h > 0)
                    vgImageSubData(vgDstImage,
                        buffer + opDst.dx + opDst.dy * imageW, stride,
                        srcFormat, opDst.dx, opDst.dy, opDst.w, opDst.h);
                break;

            /* vgSetPixels() -> vgGetPixels(). */
            case 3:
                vgSetPixels(op.dx, op.dy, vgSrcImage, op.sx, op.sy, op.w, op.h);

                if (opDst.w > 0 && opDst.h > 0)
                    vgGetPixels(vgDstImage, opDst.dx, opDst.dy,
                        opDst.dx, opDst.dy, opDst.w, opDst.h);
                break;

            /* vgGetImageSubData() -> vgWritePixels() -> vgGetPixels(). */
            case 4:
                if (opSrc.w > 0 && opSrc.h > 0)
                    vgGetImageSubData(vgSrcImage,
                        buffer + opSrc.dx + opSrc.dy * imageW, stride,
                        srcFormat, opSrc.sx, opSrc.sy, opSrc.w, opSrc.h);

                if (opBoth.w > 0 && opBoth.h > 0)
                    vgWritePixels(buffer + opBoth.dx + opBoth.dy * imageW, stride,
                        srcFormat, opBoth.dx, opBoth.dy, opBoth.w, opBoth.h);

                if (opDst.w > 0 && opDst.h > 0)
                    vgGetPixels(vgDstImage, opDst.dx, opDst.dy,
                        opDst.dx, opDst.dy, opDst.w, opDst.h);
                break;

            /* vgSetPixels() -> vgReadPixels() -> vgImageSubData(). */
            case 5:
                vgSetPixels(op.dx, op.dy, vgSrcImage, op.sx, op.sy, op.w, op.h);

                if (opBoth.w > 0 && opBoth.h > 0)
                    vgReadPixels(buffer + opBoth.dx + opBoth.dy * imageW, stride,
                        srcFormat, opBoth.dx, opBoth.dy, opBoth.w, opBoth.h);

                if (opDst.w > 0 && opDst.h > 0)
                    vgImageSubData(vgDstImage,
                        buffer + opDst.dx + opDst.dy * imageW, stride,
                        srcFormat, opDst.dx, opDst.dy, opDst.w, opDst.h);
                break;
            
            /* vgSetPixels() -> vgCopyPixels() -> vgGetPixels(). */
            case 6:
                vgSetPixels(op.sx, op.sy, vgSrcImage, op.sx, op.sy, op.w, op.h);
                vgCopyPixels(op.dx, op.dy, op.sx, op.sy, op.w, op.h);

                if (opDst.w > 0 && opDst.h > 0)
                    vgGetPixels(vgDstImage, opDst.dx, opDst.dy,
                        opDst.dx, opDst.dy, opDst.w, opDst.h);
                break;
            }
        }
    }

    /* Draw the destination images. */

    vgSetfv(VG_CLEAR_COLOR, 4, bgColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    for (i = 0; i < numFormats; i++)
        vgSetPixels(
            (i % numPerRow) * imageW,
            (i / numPerRow) * imageH,
            vgDstImages[i], 0, 0, imageW, imageH);

    /* Destroy the images. */

    for (i = 0; i < numFormats; i++)
    {
        if (vgSrcImages[i] != VG_INVALID_HANDLE)
            vgDestroyImage(vgSrcImages[i]);
        if (vgDstImages[i] != VG_INVALID_HANDLE)
            vgDestroyImage(vgDstImages[i]);
    }

    /* Clean up and save the result. */

    FREE(buffer);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

