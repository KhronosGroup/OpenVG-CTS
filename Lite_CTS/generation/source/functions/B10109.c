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



VGubyte boxCommands[5] = {VG_MOVE_TO_ABS, VG_VLINE_TO_REL, VG_HLINE_TO_REL, VG_VLINE_TO_REL, VG_CLOSE_PATH } ;
VGfloat boxCoords[] =  {0.f, 0.f, WINDSIZEY,WINDSIZEX,-WINDSIZEY } ;


/* checks for consisten tie-breaking rule in NONANTIALIASING mode */

CT_Result B10109_RenderingQualityPath_by_ATI(CT_File *AnsFile, VGuint subtest)
{
    VGPath line;
    VGPaint fillPaint;

    VGubyte commands0[5] = {VG_MOVE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords0[] =   {18.5f,18.5f, 48.5f,48.5f, 19.0f};

    VGubyte commands1[4] = {VG_MOVE_TO_ABS, VG_QUAD_TO_ABS, VG_SQUAD_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords1[] = {0.0f,32.0f, 32.0f, 64.0f, 32.f, 32.f, 64.f, 32.f};

    VGubyte commands2[3] = {VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords2[] = {64.0f,0.0f, 0.0f,0.0f, 0.0f,64.0f, 64.0f,64.0f};

    VGubyte commands3[4] = {VG_MOVE_TO_ABS, VG_CUBIC_TO_ABS, VG_SCUBIC_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords3[] = {0.0f, 32.0f, 0.0f, 64.0, 32.0f, 64.0f, 32.0f, 32.0f, 64.0f, 0.0f, 64.0f, 32.0f};

    VGubyte commands4[4] = {VG_MOVE_TO_ABS, VG_LCWARC_TO_ABS, VG_SCWARC_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords4[] = {32.0f,   0.0f,
                        -32.0f, -32.0f, 0.0f, 64.0f, 32.0f,
                        -32.0f, -32.0f, 0.0f, 32.0f, 0.0f};

    VGubyte commands5[4] = {VG_MOVE_TO_ABS, VG_LCWARC_TO_ABS, VG_SCWARC_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords5[] = {56.0f,   24.0f,
                        32.0f, 24.0f, -90.0f, 56.0f, 40.0f,
                        32.0f, 24.0f, -90.0f, 56.0f, 24.0f};

    VGubyte commands6[20] = {VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH,
                            VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH,
                            VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH,
                            VG_MOVE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords6[20]   = {2.5f, 2.5f, 31.5f, 31.5f, 2.5f, 
                            31.5f, 2.5f, 61.5f, 31.5f, 31.5f,
                            31.5f, 31.5f, 61.5f, 61.5f, 31.5f,
                            2.5f, 31.5f, 31.5f, 61.5f, 2.5f};
    
    VGubyte commands7[5] = {VG_MOVE_TO_ABS, VG_VLINE_TO_ABS, VG_HLINE_TO_ABS, VG_VLINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords7[] =   {4.f,12.f,52.f,60.f,12.f};

    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.f};/* black color */                       
    VGfloat fillColor[] =        {0.0f, 0.0f, 1.0f, 0.5f};/* blue color */
    VGfloat fillColorInverse[] = {1.0f, 0.0f, 0.0f, 0.5f};/* red color */
    
    line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( line == VG_INVALID_HANDLE )
        return CT_ERROR;
    fillPaint = vgCreatePaint();
    if ( fillPaint == VG_INVALID_HANDLE ) {
        vgDestroyPath(line);
        return CT_ERROR;
    }

    vgSetParameterfv(fillPaint, VG_PAINT_COLOR, 4, fillColor);
    vgSetParameteri( fillPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);

    vgSeti(VG_FILL_RULE, VG_EVEN_ODD);

    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
        
    vgSetPaint(fillPaint, VG_FILL_PATH);


    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);

    switch (subtest)
    {
    case 0:
        vgAppendPathData(line, 5, commands0, coords0);
        break;
    case 1:
        vgAppendPathData(line, 4, commands1, coords1);
        break;
    case 2:
        vgAppendPathData(line, 3, commands2, coords2);
        break;
    case 3:
        vgAppendPathData(line, 4, commands3, coords3);
        break;
    case 4:
        vgAppendPathData(line, 4, commands4, coords4);
        break;
    case 5:
        vgAppendPathData(line, 4, commands5, coords5);
        break;
    case 6:
        vgAppendPathData(line, 20, commands6, coords6);
        break;
    case 7:
        vgAppendPathData(line, 4, commands5, coords5);
        vgAppendPathData(line, 5, commands7, coords7);
        break;
    }

    vgAppendPathData(line, 5, boxCommands, boxCoords);
        
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgDrawPath(line, VG_FILL_PATH);

    vgSetParameterfv(fillPaint, VG_PAINT_COLOR, 4, fillColorInverse);

    vgAppendPathData(line, 5, boxCommands, boxCoords);
        
    vgDrawPath(line, VG_FILL_PATH);
    vgClearPath(line, VG_PATH_CAPABILITY_ALL);

    vgDestroyPath(line);
    vgDestroyPaint(fillPaint);

    if ( vgGetError() == VG_NO_ERROR )
        return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}

