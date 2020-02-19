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
 * G70108_Dashing_by_NVIDIA
 *
 * Tests the various dash settings on a path containing all
 * segment types.
 *
 * The test consists of four subtests, each defining the dash
 * pattern and dash phase reset as follows:
 *
 * 0000: Pattern of zero length.
 * 0001: Reset, simple pattern.
 * 0002: Reset, odd pattern with zeros and negative values.
 * 0003: No reset, long pattern with large values.
 *
 * Each subtest creates four copies of the same path with
 * varying data types, scales, and biases. It renders each
 * copy three times with different dash phase settings,
 * and composites the images into the color channels of the
 * resulting image through additive blending.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70108_Dashing_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    static const VGubyte pathCmd[] =
    {
        VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_REL, VG_HLINE_TO_ABS,
        VG_VLINE_TO_ABS, VG_HLINE_TO_REL, VG_VLINE_TO_REL, VG_HLINE_TO_REL,
        VG_CLOSE_PATH,

        VG_MOVE_TO_REL, VG_QUAD_TO_ABS, VG_QUAD_TO_REL, VG_SQUAD_TO_ABS,
        VG_SQUAD_TO_REL, VG_CLOSE_PATH,

        VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, VG_CUBIC_TO_REL, VG_SCUBIC_TO_ABS,
        VG_SCUBIC_TO_REL, VG_CLOSE_PATH,

        VG_MOVE_TO_ABS, VG_SCCWARC_TO_ABS, VG_SCWARC_TO_REL, VG_LCWARC_TO_ABS,
        VG_LCCWARC_TO_REL, VG_CLOSE_PATH,

        VG_MOVE_TO_ABS, VG_CLOSE_PATH | VG_RELATIVE, VG_MOVE_TO_REL, VG_MOVE_TO_REL,
        VG_LINE_TO_REL, VG_MOVE_TO_REL, VG_LINE_TO_REL, VG_CLOSE_PATH,
        VG_CLOSE_PATH,

        VG_MOVE_TO_ABS, VG_CUBIC_TO_REL, VG_CUBIC_TO_REL, VG_CUBIC_TO_REL,
        VG_QUAD_TO_REL, VG_QUAD_TO_REL
    };

    static const VGfloat pathVal[] =
    {
        2.0f, 2.0f,
        10.0f, 2.0f,
        0.0f, 4.0f,
        6.0f,
        10.0f,
        4.0f,
        4.0f,
        -8.0f,

        16.0f, 0.0f,
        26.0f, 2.0f, 18.0f, 8.0f,
        -8.0f, 6.0f, 0.0f, 6.0f,
        18.0f, 8.0f,
        0.0f, -6.0f,

        30.0f, 2.0f,
        36.0f, 2.0f, 36.0f, 8.0f, 30.0f, 8.0f,
        -6.0f, 0.0f, -6.0f, 6.0f, 0.0f, 6.0f,
        36.0f, 8.0f, 30.0f, 8.0f,
        -6.0f, -6.0f, 0.0f, -6.0f,

        42.0f, 2.0f,
        3.0f, 2.0f, 0.0f, 42.0f, 8.0f,
        3.0f, 2.0f, 0.0f, 0.0f, 6.0f,
        3.0f, 2.0f, 0.0f, 42.0f, 8.0f,
        3.0f, 2.0f, 0.0f, 0.0f, -6.0f,

        50.0f, 4.0f,
        0.0f, 2.0f,
        0.0f, 2.0f,
        0.0f, 0.0f,
        0.0f, 4.0f,
        0.0f, 0.0f,

        54.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 0.0f,
        0.0f, 0.0f, -4.0f, 6.0f, -4.0f, 6.0f,
        4.0f, 6.0f, 4.0f, 6.0f, 4.0f, 6.0f,
        0.0f, 0.0f, -8.0f, 0.0f,
        0.0f, -6.0f, 0.0f, -6.0f
    };

    static const struct
    {
        VGPathDatatype  datatype;
        VGfloat         scale;
        VGfloat         bias;
    } pathParams[] =
    {
        { VG_PATH_DATATYPE_F,       1.0f,   0.0f    },
        { VG_PATH_DATATYPE_S_32,    0.01f, -100.0f  },
        { VG_PATH_DATATYPE_S_16,    0.1f,  -10.0f   },
        { VG_PATH_DATATYPE_S_8,    -0.5f,   10.0f   }
    };

    int     numCmd      = sizeof(pathCmd) / sizeof(pathCmd[0]);
    int     numVal      = sizeof(pathVal) / sizeof(pathVal[0]);
    int     numPaths    = sizeof(pathParams) / sizeof(pathParams[0]);
    VGPaint vgPaint;
    VGPath  vgPaths[sizeof(pathParams) / sizeof(pathParams[0])];
    int     i, j;

    /* Create the paint. */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetPaint(vgPaint, VG_STROKE_PATH);

    /* Create the paths. */

    for (i = 0; i < numPaths; i++)
    {
        const void* dataPtr = NULL;
        VGfloat     valF[sizeof(pathVal) / sizeof(pathVal[0])];
        VGint       valS32[sizeof(pathVal) / sizeof(pathVal[0])];
        VGshort     valS16[sizeof(pathVal) / sizeof(pathVal[0])];
        VGbyte      valS8[sizeof(pathVal) / sizeof(pathVal[0])];

        switch (pathParams[i].datatype)
        {
        case VG_PATH_DATATYPE_F:    dataPtr = valF; break;
        case VG_PATH_DATATYPE_S_32: dataPtr = valS32; break;
        case VG_PATH_DATATYPE_S_16: dataPtr = valS16; break;
        case VG_PATH_DATATYPE_S_8:  dataPtr = valS8; break;
        }

        for (j = 0; j < numVal; j++)
        {
            valF[j]   = (pathVal[j] - pathParams[i].bias) / pathParams[i].scale;
            valS32[j] = (VGint)(valF[j] + ((valF[j] >= 0.0f) ? 0.5f : -0.5f));
            valS16[j] = (VGshort)valS32[j];
            valS8[j]  = (VGbyte)valS32[j];
        }

        vgPaths[i] = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            pathParams[i].datatype, pathParams[i].scale, pathParams[i].bias,
            numCmd, numVal, VG_PATH_CAPABILITY_ALL);
        vgAppendPathData(vgPaths[i], numCmd, pathCmd, dataPtr);
    }

    /* Clear the background to solid black. */
    {
        VGfloat clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
    vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSetf(VG_STROKE_MITER_LIMIT, 4.0f);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Set the dash pattern depending on the subtest. */

    switch (subtest)
    {
    case 0: /* Pattern of zero length. */
        {
            static const VGfloat pattern[] =
            {
                0.0f, 0.0f
            };
            vgSetfv(VG_STROKE_DASH_PATTERN, 2, pattern);
            vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_TRUE);
        }
        break;

    case 1: /* Reset, simple pattern. */
        {
            static const VGfloat pattern[] =
            {
                2.0f, 4.0f
            };
            vgSetfv(VG_STROKE_DASH_PATTERN, 2, pattern);
            vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_TRUE);
        }
        break;

    case 2: /* Reset, odd pattern with zeros and negative values. */
        {
            static const VGfloat pattern[] =
            {
                0.0f, 4.0f, -1.0f, 4.0f,
                2.0f, -123456789.0f, 100.0f
            };
            vgSetfv(VG_STROKE_DASH_PATTERN, 7, pattern);
            vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_TRUE);
        }
        break;

    case 3: /* No reset, long pattern with large values. */
        {
            static const VGfloat pattern[] =
            {
                8.0f, 16.0f, 8.0f, 16.0f,
                8.0f, 16.0f, 8.0f, 16.0f,
                8.0f, 16.0f, 8.0f, 16.0f,
                8.0f, 16.0f, 2940.0f, 0.0f
            };
            vgSetfv(VG_STROKE_DASH_PATTERN, 16, pattern);
            vgSeti(VG_STROKE_DASH_PHASE_RESET, VG_FALSE);
        }
        break;
    }

    /* Loop over dash phases. */

    for (i = 0; i < 3; i++)
    {
        static const struct
        {
            VGuint  color;
            VGfloat phase;
        } cases[] =
        {
            { 0xff0000ff, 0.0f          },
            { 0x00ff00ff, 12345.6789f   },
            { 0x0000ffff, -23456.789f   }
        };

        vgSetColor(vgPaint, cases[i].color);
        vgSetf(VG_STROKE_DASH_PHASE, cases[i].phase);
        vgLoadIdentity();

        /* Draw each path, from bottom to top. */

        for (j = 0; j < numPaths; j++)
        {
            vgDrawPath(vgPaths[j], VG_STROKE_PATH);
            vgTranslate(0.0f, 16.0f);
        }
    }

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    for (i = 0; i < numPaths; i++)
        if (vgPaths[i] != VG_INVALID_HANDLE)
            vgDestroyPath(vgPaths[i]);

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

