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

#include "../main.h"
#include "../util/util.h"

#define HALFWINX (WINDSIZEX>>1)
#define HALFWINY (WINDSIZEY>>1)

/*========================================================================
  Type Definitions
========================================================================*/

typedef struct {
    VGPath  path;
    VGPaint paint;
} JoinStyleInfo;

/*========================================================================
  Prototypes
=======================================================================*/

static void DrawPath(JoinStyleInfo *gJs);

/*========================================================================
  Functions
========================================================================*/

static void DrawPath(JoinStyleInfo *gJs)
{
    vgSetf(VG_STROKE_LINE_WIDTH, 30.f);
    vgSetPaint(gJs->paint, VG_STROKE_PATH);
    vgDrawPath(gJs->path, VG_STROKE_PATH);
}

static void joinstyle_init(JoinStyleInfo *gJs)
{
    const VGfloat clearColor[4] = {0.f, 0.f, 0.f, 1.f};
    
    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgSetf(VG_STROKE_MITER_LIMIT, 100.f);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
    
    gJs->paint = vgCreatePaint();
    vgSetParameteri(gJs->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);

    gJs->path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
        1., 0., 10, 10, VG_PATH_CAPABILITY_ALL);
}

static void joinstyle_deinit(JoinStyleInfo *gJs)
{
    vgDestroyPath(gJs->path);
    vgDestroyPaint(gJs->paint);
}

CT_Result G60101_JoinStyles_by_NVIDIA(CT_File *AnsFile, VGuint subtest)
{
    JoinStyleInfo gJs;

    static const int joinStyle[3] = {VG_JOIN_MITER, VG_JOIN_ROUND, VG_JOIN_BEVEL};
    static const VGuint color[3] = {0x0000ffff, 0xff0000ff, 0x00ff00ff};

    VGubyte segments[] = {
        VG_LINE_TO_ABS,
        VG_HLINE_TO_ABS,
        VG_VLINE_TO_ABS,
        VG_QUAD_TO_ABS,
        VG_CUBIC_TO_ABS,
        VG_SQUAD_TO_ABS,
        VG_SCUBIC_TO_ABS,
        VG_SCCWARC_TO_ABS,
        VG_SCWARC_TO_ABS,
        VG_LCCWARC_TO_ABS,
        VG_LCWARC_TO_ABS,
    };
    static const int dataCount[] = {2, 1, 1, 4, 6, 2, 4, 5, 5, 5, 5};
    static const VGfloat dataL[][20] = {
        {120.f, 190.f},
        {120.f},
        {190.f},
        {90.f, 100.f, 120.f, 190.f},
        {90.f, 130.f, 30.f, 160.f, 120.f, 190.f},
        {120.f, 190.f},
        {30.f, 160.f, 120.f, 190.f},
        {40.f, 40.f, 0.f, 120.f, 190.f},
        {40.f, 40.f, 0.f, 120.f, 190.f},
        {40.f, 40.f, 0.f, 120.f, 190.f},
        {40.f, 40.f, 0.f, 120.f, 190.f},
        {40.f, 40.f, 0.f, 120.f, 190.f}
    };
    static const VGfloat dataR[][20] = {
        {210.f, 100.f},
        {210.f},
        {100.f},
        {150.f, 100.f, 210.f, 100.f},
        {150.f, 130.f, 210.f, 160.f, 210.f, 100.f},
        {210.f, 100.f},
        {210.f, 160.f, 210.f, 100.f},
        {40.f, 40.f, 0.f, 210.f, 100.f},
        {40.f, 40.f, 0.f, 210.f, 100.f},
        {40.f, 40.f, 0.f, 210.f, 100.f},
        {40.f, 40.f, 0.f, 210.f, 100.f},
        {40.f, 40.f, 0.f, 210.f, 100.f}
    };
    
    VGubyte pathSegmentData[10] = {
        VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS
    };
    VGfloat pathCoordData[30] = {30.f, 100.f, 120.f, 190.f, 210.f, 100.f};

    int style;
    int left;
    int right;
    int i, p;

    joinstyle_init(&gJs);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    right = subtest % 11;
    left  = subtest / 11;
    
    p = 2;
    pathSegmentData[1] = segments[left];
    pathSegmentData[2] = segments[right];
    for (i = 0; i < dataCount[left]; i++) {
        pathCoordData[p++] = dataL[left][i];
    }
    for (i = 0; i < dataCount[right]; i++) {
        pathCoordData[p++] = dataR[right][i];
    }

    vgClearPath(gJs.path, VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(gJs.path, 3, pathSegmentData, pathCoordData);

    for (style = 0; style < 3; style++)
    {
        vgSeti( VG_STROKE_JOIN_STYLE, joinStyle[style] );
        vgSetColor( gJs.paint, color[style] );
        vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
        vgLoadIdentity();
        switch (left)
        {
            case 0:
                vgTranslate( HALFWINX-dataL[left][0], HALFWINY-dataL[left][1] );
                break;
            case 1:
                vgTranslate( HALFWINX-dataL[left][0], HALFWINY-pathCoordData[1] );
                break;
            case 2:
                vgTranslate( HALFWINX-pathCoordData[0], HALFWINY-dataL[left][0] );
                break;
            case 3:
                vgTranslate( HALFWINX-dataL[left][2], HALFWINY-dataL[left][3] );
                break;
            case 4:
                vgTranslate( HALFWINX-dataL[left][4], HALFWINY-dataL[left][5] );
                break;
            case 5:
                vgTranslate( HALFWINX-dataL[left][0], HALFWINY-dataL[left][1] );
                break;
            case 6:
                vgTranslate( HALFWINX-dataL[left][2], HALFWINY-dataL[left][3] );
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                vgTranslate( HALFWINX-dataL[left][3], HALFWINY-dataL[left][4] );
                break;
        }

        DrawPath(&gJs);
    }

    joinstyle_deinit(&gJs);

    return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile);
}
