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
#include "../util/st.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result B10101_RenderingQualityPath_by_HYBRID(CT_File *AnsFile)
{
    VGPaint fill;
    VGPath lowLeft;
    VGPath lowRight;
    VGPath upLeft;
    VGPath upRight;

    static const VGfloat lowLeftCoords[5]   = {2.5f, 2.5f, 31.5f, 31.5f, 2.5f};
    static const VGfloat lowRightCoords[5]  = {31.5f, 2.5f, 61.5f, 31.5f, 31.5f};
    static const VGfloat upRightCoords[5]   = {31.5f, 31.5f, 61.5f, 61.5f, 31.5f};
    static const VGfloat upLeftCoords[5]    = {2.5f, 31.5f, 31.5f, 61.5f, 2.5f};
    
    static const VGubyte sqrCmds[5] = {VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH};
    
    static const VGfloat transparent_white[4] = {1, 1, 1, 0.8f};
    static const VGfloat black[4]  = {0, 0, 0, 1};

    /* Test the position of the nonantialiased sampling point */

    /*  Exceptionally use the identity transform to make sure that we get the coordinates specified. */
    //vgLoadIdentity();
	LOAD_TIE_BREAK_RULE_MATRIX();

    vgSetfv(VG_CLEAR_COLOR, 4, black);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, transparent_white);
    vgSetPaint(fill, VG_FILL_PATH);

    /*  Make four rectangles that fill the screen. We should get even grey as result. */

    lowLeft = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(lowLeft, 5, sqrCmds, lowLeftCoords);

    lowRight = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(lowRight, 5, sqrCmds, lowRightCoords);

    upLeft = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(upLeft, 5, sqrCmds, upLeftCoords);

    upRight = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(upRight, 5, sqrCmds, upRightCoords);

    vgDrawPath(lowLeft, VG_FILL_PATH);
    vgDrawPath(lowRight, VG_FILL_PATH);
    vgDrawPath(upLeft, VG_FILL_PATH);
    vgDrawPath(upRight, VG_FILL_PATH);

    vgDestroyPaint(fill);
    vgDestroyPath(lowLeft);
    vgDestroyPath(lowRight);
    vgDestroyPath(upLeft);
    vgDestroyPath(upRight);

    if (vgGetError() == VG_NO_ERROR) {
		FLIP_FRAME_BUFFER();
        DISPLAY_TEST_BUFFER();   
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

