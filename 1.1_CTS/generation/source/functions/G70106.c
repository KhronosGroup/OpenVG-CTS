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
 * G70106_PathOps_by_NVIDIA
 *
 * Tests vgAppendPath(), vgModifyPathCoords(), vgInterpolatePath(),
 * and vgTransformPath() on different path segments, datatypes, scales,
 * and biases.
 *
 * The test consists of four subtests, each defining the path datatype,
 * and a set of scales and biases. Each subtest operates on path data
 * containing all segment types, and renders four rows from the bottom
 * to top as follows:
 *
 * Row 1: vgAppendPath(app, orig); vgDrawPath(app);
 * Row 2: vgModifyPathCoords(app); vgDrawPath(app);
 * Row 3: vgInterpolatePath(ipol, orig, app); vgDrawPath(ipol);
 * Row 4: vgTransformPath(xform, orig); vgDrawPath(xform);
 *
 * In each of the path operations listed above, the scales and/or biases
 * of the source and destination paths are different.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result G70106_PathOps_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
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
        2.0f, 2.0f, 0.0f, 42.0f, 6.0f,
        2.0f, 2.0f, 0.0f, 0.0f, 8.0f,
        2.0f, 2.0f, 0.0f, 42.0f, 8.0f,
        2.0f, 2.0f, 0.0f, 0.0f, -6.0f,

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
        { VG_PATH_DATATYPE_S_8,    -0.5f,   20.0f   }
    };

    int             numCmd      = sizeof(pathCmd) / sizeof(pathCmd[0]);
    int             numVal      = sizeof(pathVal) / sizeof(pathVal[0]);
    VGPathDatatype  datatype    = pathParams[subtest].datatype;
    VGfloat         scale       = pathParams[subtest].scale;
    VGfloat         bias        = pathParams[subtest].bias;
    const void*     dataPtr     = NULL;
    VGfloat         valF[sizeof(pathVal) / sizeof(pathVal[0])];
    VGint           valS32[sizeof(pathVal) / sizeof(pathVal[0])];
    VGshort         valS16[sizeof(pathVal) / sizeof(pathVal[0])];
    VGbyte          valS8[sizeof(pathVal) / sizeof(pathVal[0])];
    VGPaint         vgPaint;
    VGPath          vgOrigPath;
    VGPath          vgAppPath;
    VGPath          vgIpolPath;
    VGPath          vgXformPath;
    int             i;

    /* Create the fill paint (green). */

    vgPaint = vgCreatePaint();
    vgSetParameteri(vgPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetColor(vgPaint, 0x00ff00ff);
    vgSetPaint(vgPaint, VG_FILL_PATH);

    /* Create the original path. */
    {

        switch (datatype)
        {
        case VG_PATH_DATATYPE_F:    dataPtr = valF; break;
        case VG_PATH_DATATYPE_S_32: dataPtr = valS32; break;
        case VG_PATH_DATATYPE_S_16: dataPtr = valS16; break;
        case VG_PATH_DATATYPE_S_8:  dataPtr = valS8; break;
        }

        for (i = 0; i < numVal; i++)
        {
            valF[i]   = (pathVal[i] - pathParams[subtest].bias) / pathParams[subtest].scale;
            valS32[i] = (VGint)(valF[i] + ((valF[i] >= 0.0f) ? 0.5f : -0.5f));
            valS16[i] = (VGshort)valS32[i];
            valS8[i]  = (VGbyte)valS32[i];
        }

        vgOrigPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            datatype, scale, bias, numCmd, numVal, VG_PATH_CAPABILITY_ALL);
        vgAppendPathData(vgOrigPath, numCmd, pathCmd, dataPtr);
    }

    /* Create the other paths. */

    vgAppPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        datatype, scale, bias - 1.0f, numCmd, numVal, VG_PATH_CAPABILITY_ALL);

    vgIpolPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        datatype, scale / 2.0f, bias + 12.0f, numCmd, numVal, VG_PATH_CAPABILITY_ALL);

    vgXformPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        datatype, scale * 2.0f, bias - 10.0f, numCmd, numVal, VG_PATH_CAPABILITY_ALL);

    /* Clear the background to solid white. */
    {
        VGfloat clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    }

    /* Setup rendering state. */

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
    vgSetf(VG_STROKE_LINE_WIDTH, 2.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSetf(VG_STROKE_MITER_LIMIT, 4.0f);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

    /* Row 1: Append origPath to appPath, and draw it. */

    vgLoadIdentity();
    vgAppendPath(vgAppPath, vgOrigPath);
    vgDrawPath(vgAppPath, VG_FILL_PATH | VG_STROKE_PATH);

    /* Row 2: Modify appPath and draw it. */

    vgTranslate(2.0f, 18.0f);
    vgModifyPathCoords(vgAppPath, 0, numCmd, dataPtr);
    vgDrawPath(vgAppPath, VG_FILL_PATH | VG_STROKE_PATH);

    /* Row 3: Interpolate origPath and appPath to ipolPath, and draw it. */

    vgTranslate(-1.0f, 15.0f);
    vgInterpolatePath(vgIpolPath, vgOrigPath, vgAppPath, 0.5f);
    vgDrawPath(vgIpolPath, VG_FILL_PATH | VG_STROKE_PATH);

    /* Row 4: Mirror origPath vertically to xformPath, and draw it. */

    vgLoadIdentity();
    vgTranslate(0.0f, 64.0f);
    vgScale(1.0f, -1.0f);
    vgTransformPath(vgXformPath, vgOrigPath);
    vgLoadIdentity();
    vgDrawPath(vgXformPath, VG_FILL_PATH | VG_STROKE_PATH);

    /* Clean up and save the result. */

    if (vgPaint != VG_INVALID_HANDLE)
        vgDestroyPaint(vgPaint);
    if (vgOrigPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgOrigPath);
    if (vgAppPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgAppPath);
    if (vgIpolPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgIpolPath);
    if (vgXformPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgXformPath);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;
    DISPLAY_SUBTEST_BUFFER(subtest);
    return CT_NO_ERROR;
}

