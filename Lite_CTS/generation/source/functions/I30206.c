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

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result I30206_PaintGradient_by_HYBRID(CT_File *AnsFile)
{
    VGPaint stroke;
    VGPaint fill;
    VGPath rect;
    VGfloat bgCol[4]		= {0.906f, 0.914f, 0.761f, 1.0f};
    VGfloat rampStops[10]	= {0.333f, 0.671f, 0.106f, 0.133f, 1.0f, 0.666f, 0.6347f, 0.6561f, 0.6057f, 1.0f};
    VGfloat gradient[4]		= {10, 10, 10, 10};
    VGubyte rectCmds[5]		= {VG_MOVE_TO, VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_VLINE_TO_REL, VG_CLOSE_PATH};
    VGfloat rectCoords[5]	= {4.0f, 4.0f, 24.0f, 24.0f, -24.0f};
    VGint i;

	/* Tests the same things as linear_gradient but with gradient values
	 * on the same spot
	 */

    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Disable antialiasing */
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);	

	/* Stroke */
    stroke = vgCreatePaint();
    vgSetParameteri(stroke, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    vgSetParameterfv(stroke, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgSetParameterfv(stroke, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
    vgSetPaint(stroke, VG_STROKE_PATH);

	/* Filling  */
    fill = vgCreatePaint();
    vgSetParameteri(fill, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    vgSetParameterfv(fill, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);
    vgSetParameterfv(fill, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
    vgSetPaint(fill, VG_FILL_PATH);

    rect = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);

    vgAppendPathData(rect, 5, rectCmds, rectCoords);

	/* VG_COLOR_RAMP_SPREAD_PAD */
    vgDrawPath(rect, VG_FILL_PATH);

	/* Change the gradient scale to show the effects of the following better. */
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);

    vgTranslate(0.25f * WINDSIZEX, 0.25f * WINDSIZEX);
    vgScale(0.25f, 0.25f);
    vgTranslate(-0.25f * WINDSIZEX, -0.25f * WINDSIZEX);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	/* VG_COLOR_RAMP_SPREAD_REPEAT */
    vgTranslate(0.5f * WINDSIZEX, 0);
    vgSetParameteri(fill, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REPEAT);
    vgDrawPath(rect, VG_FILL_PATH);

	/* VG_COLOR_RAMP_SPREAD_REFLECT */
    vgTranslate(-WINDSIZEX >> 1, WINDSIZEX >> 1);
    vgSetParameteri(fill, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REFLECT);
    vgDrawPath(rect, VG_FILL_PATH);

	/* Stroking */
    vgSetf(VG_STROKE_LINE_WIDTH, 2);

	/* Fill the rectangle with blending to see that the gradients are in sync. */
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
    vgLoadIdentity();
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    {
        VGfloat temp[10] = {0.333f, 0.671f, 0.106f, 0.133f, 0.5f, 0.666f, 0.6347f, 0.6561f, 0.6057f, 0.5f};
        for (i = 0; i < 10; i++)
        {
            rampStops[i] = temp[i];
        }
    }
    vgSetParameterfv(fill, VG_PAINT_COLOR_RAMP_STOPS, 10, rampStops);

    vgTranslate(WINDSIZEX >> 1, 0);
    vgDrawPath(rect, VG_STROKE_PATH|VG_FILL_PATH);

    vgDestroyPaint(stroke);
    vgDestroyPaint(fill);
    vgDestroyPath(rect);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

