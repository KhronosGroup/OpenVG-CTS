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

/* checks the number of distinct alpha levels drawable by the implementation meets the minimum requirment */
/* This test depends on the resolution of the alpha channel, different depths requires different criterias*/

CT_Result B10105_RenderingQualityPath_by_ATI(CT_File *AnsFile)
{
    VGPath line;
    VGPaint fillPaint;
    VGubyte lineCommands[6] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat lineCoords[] =   {0.0f,1.0f, 0.0f,64.0f, 65.0f,64.0f, 65.0f, 0.0f, 64.0f, 0.0f};
    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */                       
    VGfloat fillColor[] = {1.0f, 0.0f, 0.0f, 1.0f};/* red color */
    VGuint curColor = 0, nextColor;
    VGint i=0;
    VGfloat levelCount = 1.f;
    VGubyte *buf;

    line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( line == VG_INVALID_HANDLE )
        return CT_ERROR;
    fillPaint = vgCreatePaint();
    if ( fillPaint == VG_INVALID_HANDLE ) {
        vgDestroyPath(line);
        return CT_ERROR;
    }
    buf = MALLOC(4*64*sizeof(VGint));
    if (!buf)
        return CT_ERROR;

        vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
        vgLoadIdentity();

        vgAppendPathData(line, 6, lineCommands, lineCoords);
        
        vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        
        vgSetPaint(fillPaint, VG_FILL_PATH);
        
        vgSetParameterfv(fillPaint, VG_PAINT_COLOR, 4, fillColor);
        vgSetParameteri( fillPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
                  
        vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
        vgClear(0, 0, WINDSIZEX, WINDSIZEY);
        vgDrawPath(line, VG_FILL_PATH);
        vgReadPixels((void *)buf, WINDSIZEX, VG_lRGBA_8888, 0, 0, WINDSIZEX, 1);

        for (i = 0; i < 64 * 4; i += 4)
        {
            nextColor = (VGuint)buf[i]+(VGuint)buf[i+1]+(VGuint)buf[i+2]+(VGuint)buf[i+3];
            if (curColor < nextColor)
            {
                curColor = nextColor;
                levelCount+=1.f;
            }
        }

        FREE(buf);
        vgDestroyPath(line);
        vgDestroyPaint(fillPaint);

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile(1, &levelCount, AnsFile);
    else
        return CT_ERROR;
}

