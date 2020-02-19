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
 * F20107_Masking_by_NVIDIA
 *
 * Tests different mask operation corner cases. The test
 * consists of 24 subtests as follows:
 *
 * 0000: vgMask(), VG_CLEAR_MASK
 * 0001: vgMask(), VG_FILL_MASK
 * 0002: vgMask(), VG_SET_MASK
 * 0003: vgMask(), VG_UNION_MASK
 * 0004: vgMask(), VG_INTERSECT_MASK
 * 0005: vgMask(), VG_SUBTRACT_MASK
 * 0006: vgFillMaskLayer(), VG_CLEAR_MASK
 * 0007: vgFillMaskLayer(), VG_FILL_MASK
 * 0008: vgFillMaskLayer(), VG_SET_MASK
 * 0009: vgFillMaskLayer(), VG_UNION_MASK
 * 0010: vgFillMaskLayer(), VG_INTERSECT_MASK
 * 0011: vgFillMaskLayer(), VG_SUBTRACT_MASK
 * 0012: vgCopyMask(), VG_CLEAR_MASK
 * 0013: vgCopyMask(), VG_FILL_MASK
 * 0014: vgCopyMask(), VG_SET_MASK
 * 0015: vgCopyMask(), VG_UNION_MASK
 * 0016: vgCopyMask(), VG_INTERSECT_MASK
 * 0017: vgCopyMask(), VG_SUBTRACT_MASK
 * 0018: vgRenderToMask(), VG_CLEAR_MASK
 * 0019: vgRenderToMask(), VG_FILL_MASK
 * 0020: vgRenderToMask(), VG_SET_MASK
 * 0021: vgRenderToMask(), VG_UNION_MASK
 * 0022: vgRenderToMask(), VG_INTERSECT_MASK
 * 0023: vgRenderToMask(), VG_SUBTRACT_MASK
 *
 * Each subtest renders a 8x8 grid. The horizontal position of
 * each grid item defines the source mask type, while the vertical
 * position defines the destination mask type. The mask type
 * defines the size and initial contents of the masks.
 *
 * Twelve test cases are executed for each grid item. The test cases
 * perform an operation that uses the two mask layers as its input, and
 * writes the (binary) result into the surface mask. The results of the
 * test cases are combined together through additive blending.
 */

#include "../main.h"
#include "../util/util.h"

typedef struct CTMaskLayer_t
{
    VGint       width;      /* Width of the mask layer in pixels. */
    VGint       height;     /* Height of the mask layer in pixels. */
    VGMaskLayer vgHandle;   /* The corresponding VGMaskLayer object. */
} CTMaskLayer;

typedef struct CTMaskCase_t
{
    VGuint      color;      /* RGBA color value used for blending the result. */
    VGint       dx;         /* Operation destination X. */
    VGint       dy;         /* Operation destination Y. */
    VGint       sx;         /* Operation source X. */
    VGint       sy;         /* Operation source Y. */
    VGint       width;      /* Operation width. */
    VGint       height;     /* Operation height. */
} CTMaskCase;

static void setMatrixForRect(int x, int y, int w, int h)
{
    vgLoadIdentity();
    vgTranslate((VGfloat)x, (VGfloat)y);
    vgScale((VGfloat)w, (VGfloat)h);
}

static CTMaskLayer createMaskLayer(int i)
{
    static const struct
    {
        VGint   width;      /* Width of the mask layer in pixels. */
        VGint   height;     /* Height of the mask layer in pixels. */
        VGint   boxX;       /* X coordinate of the box filled with 1.0. */
        VGint   boxY;       /* Y coordinate of the box. */
        VGint   boxW;       /* Width of the box. */
        VGint   boxH;       /* Height of the box. */
    } types[] =
    {
        /* w   h  bx  by  bw  bh */
        { 7,  7,  0,  0,  7,  7 },  /* entirely 1.0 */
        { 7,  7,  0,  0,  0,  0 },  /* entirely 0.0 */
        { 7,  7,  2,  2,  4,  4 },  /* box of 1.0 at the center */
        { 7,  7,  0,  0,  4,  4 },  /* box of 1.0 at the origin */
        { 10, 5,  0,  0,  10, 5 },  /* entirely 1.0 */
        { 10, 5,  2,  2,  4,  3 },  /* box of 1.0 */
        { 5,  10, 2,  2,  0,  0 },  /* entirely 0.0 */
        { 5,  10, 2,  2,  3,  4 }   /* box of 1.0 */
    };

    CTMaskLayer res;
    res.width = types[i].width;
    res.height = types[i].height;
    res.vgHandle = vgCreateMaskLayer(res.width, res.height);

    if (res.vgHandle != VG_INVALID_HANDLE)
    {
        if (types[i].boxX > 0 ||
            types[i].boxY > 0 ||
            types[i].boxW < res.width ||
            types[i].boxH < res.height)
        {
            vgFillMaskLayer(res.vgHandle, 0, 0, res.width, res.height, 0.0f);
            if (types[i].boxW > 0 && types[i].boxH > 0)
                vgFillMaskLayer(res.vgHandle,
                    types[i].boxX, types[i].boxY,
                    types[i].boxW, types[i].boxH, 1.0f);
        }
    }
    return res;
}

static void runMaskCase(
    int                 x,
    int                 y,
    const CTMaskLayer*  dst,
    const CTMaskLayer*  src,
    VGMaskOperation     maskOp,
    int                 maskFunc,
    CTMaskCase          maskCase,
    VGPath              vgRectPath)
{
    /* Intersect the rectangle with mask layer bounds. */
    {
        int x0a = 0;
        int y0a = 0;
        int x1a = maskCase.width;
        int y1a = maskCase.height;

        int x0b = -maskCase.dx;
        int y0b = -maskCase.dy;
        int x1b = dst->width - maskCase.dx;
        int y1b = dst->height - maskCase.dy;

        int x0c = -maskCase.sx;
        int y0c = -maskCase.sy;
        int x1c = src->width - maskCase.sx;
        int y1c = src->height - maskCase.sy;

        int x0  = (x0a > x0b && x0a > x0c) ? x0a : (x0b > x0c) ? x0b : x0c;
        int y0  = (y0a > y0b && y0a > y0c) ? y0a : (y0b > y0c) ? y0b : y0c;
        int x1  = (x1a < x1b && x1a < x1c) ? x1a : (x1b < x1c) ? x1b : x1c;
        int y1  = (y1a < y1b && y1a < y1c) ? y1a : (y1b < y1c) ? y1b : y1c;

        maskCase.dx += x0;
        maskCase.dy += y0;
        maskCase.sx += x0;
        maskCase.sy += y0;
        maskCase.width = x1 - x0;
        maskCase.height = y1 - y0;
    }

    /* Call the specified function. */

    switch (maskFunc)
    {
    case 0: /* vgMask() */
        vgMask(dst->vgHandle, VG_SET_MASK, x, y, dst->width, dst->height);
        vgMask(src->vgHandle, maskOp,
            x + maskCase.dx, y + maskCase.dy, maskCase.width, maskCase.height);
        break;

    case 1: /* vgFillMaskLayer() */
        vgFillMaskLayer(dst->vgHandle,
            maskCase.dx, maskCase.dy, maskCase.width, maskCase.height,
            (maskOp == VG_CLEAR_MASK) ? 0.0f : 1.0f);
        vgMask(dst->vgHandle, VG_SET_MASK, x, y, dst->width, dst->height);
        break;

    case 2: /* vgCopyMask() */
        vgMask(src->vgHandle, VG_SET_MASK, 0, 0, src->width, src->height);
        vgCopyMask(dst->vgHandle, maskCase.dx, maskCase.dy,
            maskCase.sx, maskCase.sy, maskCase.width, maskCase.height);
        vgMask(dst->vgHandle, VG_SET_MASK, x, y, dst->width, dst->height);
        break;

    case 3: /* vgRenderToMask() */
        vgMask(dst->vgHandle, VG_SET_MASK, x, y, dst->width, dst->height);
        setMatrixForRect(x + maskCase.dx, y + maskCase.dy, maskCase.width, maskCase.height);
        vgRenderToMask(vgRectPath, VG_FILL_PATH, maskOp);
        break;
    }
}

CT_Result F20107_Masking_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGMaskOperation maskOps[] =
    {
        VG_CLEAR_MASK,
        VG_FILL_MASK,
        VG_SET_MASK,
        VG_UNION_MASK,
        VG_INTERSECT_MASK,
        VG_SUBTRACT_MASK
    };

    int             numItems    = 8;
    int             itemSize    = 7;
    int             itemPad     = 1;
    VGMaskOperation maskOp      = maskOps[subtest % 6];
    int             maskFunc    = subtest / 6;
    VGPath          vgRectPath;
    VGPaint         vgPaint;
    int             i, j, k;

    /* Create a 1x1 rectangle path. */
    {
        static const VGubyte rectCmd[] =
        { VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH };

        static const VGfloat rectVal[] =
        { 1.0f, 1.0f, 0.0f };

        vgRectPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        vgAppendPathData(vgRectPath, sizeof(rectCmd), rectCmd, rectVal);
    }

    /* Create a paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Clear the background to semi-transparent gray. */
    {
        VGfloat clearColor[] = { 0.5f, 0.5f, 0.5f, 0.75f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup the rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Loop over destination and source mask types. */

    for (i = 0; i < numItems; i++)
        for (j = 0; j < numItems; j++)
        {
            static const CTMaskCase maskCaseSet[] =
            {
                /* color      dx  dy  sx  sy  w   h */
                { 0x920000ff, 0,  0,  0,  0,  10, 10 },
                { 0x009200ff, 1,  1,  0,  0,  10, 10 },
                { 0x000092ff, 0,  0,  1,  1,  10, 10 },
                { 0x490000ff, 2,  3,  0,  0,  10, 10 },
                { 0x004900ff, 0,  0,  2,  3,  10, 10 },
                { 0x000049ff, 1,  1,  0,  0,  2,  3 },
                { 0x240000ff, 0,  0,  1,  1,  2,  3 },
                { 0x002400ff, 3,  2,  0,  0,  3,  2 },
                { 0x000024ff, 0,  0,  3,  2,  3,  2 }
            };

            int x = j * (itemSize + itemPad);
            int y = i * (itemSize + itemPad);

            /* Clear the item background to solid black. */

            vgSeti(VG_MASKING, VG_FALSE);
            vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
            vgSetColor(vgPaint, 0x000000ff);
            setMatrixForRect(x, y, itemSize, itemSize);
            vgDrawPath(vgRectPath, VG_FILL_PATH);

            /* Loop over the cases. */

            for (k = 0; k < (int)(sizeof(maskCaseSet) / sizeof(maskCaseSet[0])); k++)
            {
               /* Create the mask layers. */

                CTMaskLayer dst = createMaskLayer(i);
                CTMaskLayer src = createMaskLayer(j);

                if (dst.vgHandle != VG_INVALID_HANDLE && src.vgHandle != VG_INVALID_HANDLE)
                {
                    /* Clear the mask layer. */

                    vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, WINDSIZEX, WINDSIZEY);

                    /* Run the case. */

                    runMaskCase(x, y, &dst, &src, maskOp, maskFunc, maskCaseSet[k], vgRectPath);

                    /* Draw case specific color through the mask with additive blending. */

                    vgSeti(VG_MASKING, VG_TRUE);
                    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
                    vgSetColor(vgPaint, maskCaseSet[k].color);
                    setMatrixForRect(x, y, itemSize, itemSize);
                    vgDrawPath(vgRectPath, VG_FILL_PATH);
                }

                /* Clean up. */

                if (dst.vgHandle != VG_INVALID_HANDLE)
                    vgDestroyMaskLayer(dst.vgHandle);
                if (src.vgHandle != VG_INVALID_HANDLE)
                    vgDestroyMaskLayer(src.vgHandle);
            }
        }

    /* Clean up and save the result. */

    if (vgRectPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgRectPath);
    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

