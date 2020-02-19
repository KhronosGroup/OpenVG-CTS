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

CT_Result G30103_PathStroking_by_HUONE (CT_File *AnsFile)               
{
    VGPath  HPath, VPath;
    VGPaint strokePaint;
    VGubyte HCommands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS};
    VGubyte VCommands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS};

    VGfloat HCoords[] = {-24.0f,0.0f, 24.0f,0.0f};
    VGfloat VCoords[] = {0.0f,24.0f, 0.0f,-24.0f};                                            
    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 1.0f};/* black color */                       
    VGfloat strokeColor[] = {1.0f, 0.0f, 0.0f, 0.7f};/* red color */

    HPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( HPath == VG_INVALID_HANDLE )
        return CT_ERROR;
    VPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( VPath == VG_INVALID_HANDLE )
        return CT_ERROR;
    strokePaint = vgCreatePaint();
    if ( strokePaint == VG_INVALID_HANDLE )
        return CT_ERROR;
        
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgTranslate(32.0f, 32.0f);
    
    vgAppendPathData(HPath, 2, HCommands, HCoords);
    vgAppendPathData(VPath, 2, VCommands, VCoords);
    
    vgSetf(VG_STROKE_LINE_WIDTH, 16.0f);
    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    
    vgSetPaint(strokePaint, VG_STROKE_PATH);
    
    vgSetParameterfv(strokePaint, VG_PAINT_COLOR, 4, strokeColor);
    vgSetParameteri( strokePaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    
    vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
    vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);

    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgDrawPath(HPath, VG_STROKE_PATH);
    vgDrawPath(VPath, VG_STROKE_PATH);

    vgDestroyPath(HPath);
    vgDestroyPath(VPath);
    vgDestroyPaint(strokePaint);

    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}


