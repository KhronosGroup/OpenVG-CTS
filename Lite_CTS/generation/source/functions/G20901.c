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

CT_Result G20901_PathOperation_by_HUONE (CT_File *AnsFile)               
{
    VGPath line, point;
    VGubyte lineCommands[5] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS,VG_CLOSE_PATH};
    VGfloat lineCoords[] =   {-16.0f,-16.0f, -16.0f,16.0f, 16.0f,16.0f, 16.0f,-16.0f};

    VGubyte pointCommands[5] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS,VG_CLOSE_PATH};
    VGfloat pointCoords[] = {0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f};
    VGfloat minX, minY, width, height;
    VGfloat values[12];
    
    /* line */
    line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( line == VG_INVALID_HANDLE )
        return CT_ERROR;

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgTranslate(32, 32);
    
    vgAppendPathData(line, 5, lineCommands, lineCoords);

    vgSetf(VG_STROKE_LINE_WIDTH, 16.0f);
    
    vgPathBounds(line, &minX, &minY, &width, &height);

    values[0] = minX;
    values[1] = minY;
    values[2] = width;
    values[3] = height;
    
    vgDestroyPath(line);

    /* point */
    point = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( point == VG_INVALID_HANDLE )
        return CT_ERROR;

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgTranslate(32, 32);
    
    vgAppendPathData(point, 5, pointCommands, pointCoords);

    vgSetf(VG_STROKE_LINE_WIDTH, 16.0f);
    
    vgPathBounds(point, &minX, &minY, &width, &height);

    values[4] = minX;
    values[5] = minY;
    values[6] = width;
    values[7] = height;
    
    vgClearPath(point, VG_PATH_CAPABILITY_ALL);
    
    vgSetf(VG_STROKE_LINE_WIDTH, 16.0f);

    /* path is empty */
    vgPathBounds(point, &minX, &minY, &width, &height);

    values[8] = minX;
    values[9] = minY;
    values[10] = width;
    values[11] = height;

    vgDestroyPath(point);
    
    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (12, values, AnsFile);
    else
        return CT_ERROR;
}


