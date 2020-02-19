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
 * G70101_Arcs_by_NVIDIA
 *
 * Tests that elliptical arc segments are rendered correctly
 * with different transformation matrices, and that
 * vgTransformPath() and vgModifyPathCoords() work as expected
 * on them.
 *
 * The test consists of 12 subtests, organized as follows:
 *
 * 0000: Transform 0, method 0
 * 0001: Transform 0, method 1
 * 0002: Transform 0, method 2
 * 0003: Transform 1, method 0
 * 0004: Transform 1, method 1
 * 0005: Transform 1, method 2
 * 0006: Transform 2, method 0
 * 0007: Transform 2, method 1
 * 0008: Transform 2, method 2
 * 0009: Transform 3, method 0
 * 0010: Transform 3, method 1
 * 0011: Transform 3, method 2
 *
 * Each subtest renders a path containing arc segments three
 * times. The three images are composited into the color channels
 * of the resulting image using additive blending. The path
 * datatype, scale, and bias vary between the renderings,
 * but the three images should be equal nevertheless.
 *
 * Transformation matrices:
 *
 * Transform 0: Identity.
 * Transform 1: Mirror horizontally.
 * Transform 2: Mirror vertically.
 * Transform 3: Rotate 180 degrees.
 *
 * Transformation methods:
 *
 * Method 0: Transform using vgDrawPath()
 * Method 1: Transform using vgTransformPath() and draw with
 *           identity transform
 * Method 2: Same as method 1, but override the path coordinates
 *           after the transformation.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70101_Arcs_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    int     xformMethod = subtest % 3;
    int     xformType   = subtest / 3;
    VGPaint vgPaint;
    int     i, j;

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_FILL_PATH | VG_STROKE_PATH);

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
    vgSetf(VG_FILL_RULE, VG_NON_ZERO);
    vgSetf(VG_STROKE_LINE_WIDTH, 1.0f);
    vgSetf(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
    vgSetf(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Loop over cases. */

    for (i = 0; i < 3; i++)
    {
        static const struct
        {
            VGuint  fillColor;
            VGuint  strokeColor;
            VGfloat srcCoef;
            VGfloat srcBias;
            VGfloat dstCoef;
            VGfloat dstBias;
        } cases[3] =
        {
            { 0x800000ff, 0xff0000ff,  1.0f,   0.0f,   1.0f,   0.0f  },
            { 0x008000ff, 0x00ff00ff,  2.0f,  -1.0f,   1.23f, -4.56f },
            { 0x000080ff, 0x0000ffff, -1.23f,  4.56f, -2.0f,   1.0f  },
        };

        static const VGubyte pathCmd[] =
        { 
            VG_MOVE_TO_ABS, VG_SCCWARC_TO_ABS,
            VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS,
            VG_MOVE_TO_ABS, VG_LCCWARC_TO_REL,
            VG_MOVE_TO_ABS, VG_LCWARC_TO_ABS,
            VG_MOVE_TO_ABS, VG_LCCWARC_TO_ABS,
            VG_MOVE_TO_ABS, VG_SCWARC_TO_REL,
            VG_MOVE_TO_ABS, VG_SCCWARC_TO_ABS,
            VG_MOVE_TO_ABS, VG_LCWARC_TO_ABS
        };

        static const VGfloat pathVal[] =
        {
            5.5f,  8.5f,   14.0f,  10.0f, 40.0f, 21.5f, 24.5f,
            7.5f,  6.5f,  -14.0f,  10.0f, 40.0f, 23.5f, 22.5f,
            37.5f, 8.5f,   14.0f, -10.0f, 40.0f, 16.0f, 16.0f,
            39.5f, 6.5f,  -14.0f, -10.0f, 40.0f, 55.5f, 22.5f,
            5.5f,  40.5f,  14.0f,  10.0f, 40.0f, 21.5f, 56.5f,
            7.5f,  38.5f, -14.0f,  10.0f, 40.0f, 16.0f, 16.0f,
            37.5f, 40.5f,  14.0f, -10.0f, 40.0f, 53.5f, 56.5f,
            39.5f, 38.5f, -14.0f, -10.0f, 40.0f, 55.5f, 54.5f
        };

        int numCmd = sizeof(pathCmd) / sizeof(VGubyte);
        int numVal = sizeof(pathVal) / sizeof(VGfloat);
        VGPath vgSrcPath;
        VGPath vgDstPath;

        /* Create the paths. */

        vgSrcPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            cases[i].srcCoef, cases[i].srcBias, 100, 100, VG_PATH_CAPABILITY_ALL);
        vgDstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
            cases[i].dstCoef, cases[i].dstBias, 100, 100, VG_PATH_CAPABILITY_ALL);

        /* Append data to the source path. */
        {
            VGfloat scaledVal[sizeof(pathVal) / sizeof(VGfloat)];
            for (j = 0; j < numVal; j++)
                scaledVal[j] = (pathVal[j] - cases[i].srcBias) / cases[i].srcCoef;
            vgAppendPathData(vgSrcPath, numCmd, pathCmd, scaledVal);
        }

        /* Setup the transformation. */

        vgLoadIdentity();
        if ((xformType & 1) != 0)
        {
            vgTranslate(64.0f, 0.0f);
            vgScale(-1.0f, 1.0f);
        }
        if ((xformType & 2) != 0)
        {
            vgTranslate(0.0f, 64.0f);
            vgScale(1.0f, -1.0f);
        }

        /* Method 0: Copy using vgAppendPath() and draw. */

        if (xformMethod == 0)
            vgAppendPath(vgDstPath, vgSrcPath);

        /* Method 1: Transform using vgTransformPath()
         * and draw with an identity matrix. */

        else
        {
            vgTransformPath(vgDstPath, vgSrcPath);
            vgLoadIdentity();

            /* Method 2: Re-specify segment values
             * after transformation. */

            if (xformMethod == 2)
            {
                VGfloat xformVal[sizeof(pathVal) / sizeof(VGfloat)];
                for (j = 0; j < numVal; j++)
                    xformVal[j] = pathVal[j];

                if ((xformType & 1) != 0)
                    for (j = 0; j < numVal; j += 7)
                    {
                        xformVal[j + 0] = 64.0f - xformVal[j + 0];
                        xformVal[j + 4] = 180.0f - xformVal[j + 4];
                        xformVal[j + 5] = -xformVal[j + 5];
                        if (j != 14 && j != 35)
                            xformVal[j + 5] += 64.0f;
                    }

                if ((xformType & 2) != 0)
                    for (j = 0; j < numVal; j += 7)
                    {
                        xformVal[j + 1] = 64.0f - xformVal[j + 1];
                        xformVal[j + 4] = -xformVal[j + 4];
                        xformVal[j + 6] = -xformVal[j + 6];
                        if (j != 14 && j != 35)
                            xformVal[j + 6] += 64.0f;
                    }

                for (j = 0; j < numVal; j++)
                    xformVal[j] = (xformVal[j] - cases[i].dstBias) / cases[i].dstCoef;
                vgModifyPathCoords(vgDstPath, 0, numCmd, xformVal);
            }
        }

        /* Draw the destination path. */

        vgSetColor(vgPaint, cases[i].fillColor);
        vgDrawPath(vgDstPath, VG_FILL_PATH);
        vgSetColor(vgPaint, cases[i].strokeColor);
        vgDrawPath(vgDstPath, VG_STROKE_PATH);

        /* Clean up. */

        vgDestroyPath(vgSrcPath);
        vgDestroyPath(vgDstPath);
    }

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

