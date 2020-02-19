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

#define BOUNDARY_TEST_LIMIT 0.5

VGboolean BoundaryTestNonAA (VGuint* buf, VGfloat radius)
{
    VGuint curColor;
    VGfloat whiteValue;
    VGint i, j;
    VGint internalErrorCount = 0;
    VGint externalErrorCount = 0;
    VGfloat d2Origin;
    
    for (j = 0; j < WINDSIZEY; j ++)
    {
        for (i = 0; i < WINDSIZEX; i ++)
        {
            curColor = buf[i+j*WINDSIZEX];
            whiteValue = (VGfloat)(curColor&0xFF) * (VGfloat)((curColor&0xFF00)>>8)*(VGfloat)((curColor&0xFF0000)>>16)*(VGfloat)((curColor&0xFF000000)>>24) / 4228250625.f;
            d2Origin = ((VGfloat)i + 0.5f)*((VGfloat)i + 0.5f) + ((VGfloat)j + 0.5f)*((VGfloat)j + 0.5f);
            if (d2Origin >= (radius + BOUNDARY_TEST_LIMIT) * (radius + BOUNDARY_TEST_LIMIT) &&  whiteValue!= 0.0f)
                externalErrorCount ++;
            else if (d2Origin <= (radius - BOUNDARY_TEST_LIMIT) * (radius - BOUNDARY_TEST_LIMIT) && whiteValue < 1.0f)
                internalErrorCount ++;
        }
    }

    if (externalErrorCount || internalErrorCount)
        return VG_FALSE;
    else
        return VG_TRUE;
}

/* checks that all the pixels in the buffer with pixel-centers more than 0.5pixels
away from the fill boundary are filled exactly correct*/

CT_Result B10108_RenderingQualityPath_by_ATI(CT_File *AnsFile)
{
    VGPath line;
    VGPaint fillPaint;
    VGubyte lineCommands[3] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS};
    VGfloat lineCoords[] =   {-2.0f,-1.0f, 0.0f,0.0f, -1.0f, -2.0f};
    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */                       
    VGfloat fillColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/* white color */
    VGfloat testRadius = 60.0f;
    
    line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( line == VG_INVALID_HANDLE )
        return CT_ERROR;
    fillPaint = vgCreatePaint();
    if ( fillPaint == VG_INVALID_HANDLE ) {
        vgDestroyPath(line);
        return CT_ERROR;
    }

    vgSetf(VG_STROKE_LINE_WIDTH, 1.0f);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgScale(testRadius * 2, testRadius * 2);

    vgAppendPathData(line, 3, lineCommands, lineCoords);
        
    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        
    vgSetPaint(fillPaint, VG_STROKE_PATH);
        
    vgSetParameterfv(fillPaint, VG_PAINT_COLOR, 4, fillColor);
    vgSetParameteri( fillPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
        
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgDrawPath(line, VG_STROKE_PATH);

    vgDestroyPath(line);
    vgDestroyPaint(fillPaint);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

