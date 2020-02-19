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

CT_FileType G50107_PathFilling_by_HUONE (CT_File *AnsFile)              
{
    VGPath line1, line2;
    VGPaint paint1, paint2;
    VGubyte lineCommands1[9] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS,
                                VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGubyte lineCommands2[9] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS,
                                VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat lineCoords1[] =   {0.0f,64.0f, 64.0f,64.0f, 64.0f,0.0f, 48.0f,0.0f, 
                               48.0f,64.0f, 64.0f,64.0f, 64.0f,48.0f, 0.0f,48.0f};
    VGfloat lineCoords2[] =   {0.0f,64.0f, 0.0f,0.0f, 64.0f,0.0f, 64.0f,16.0f, 
                               0.0f,16.0f, 0.0f,0.0f, 16.0f,0.0f, 16.0f,64.0f};

    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */                                              
    VGfloat fillColor1[] = {1.0f, 0.0f, 0.0f, 1.0f};/* red color */
    VGfloat fillColor2[] = {0.0f, 1.0f, 0.0f, 1.0f};/* green color */
    

    line1  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( line1 == VG_INVALID_HANDLE )
        return CT_ERROR;
    line2  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( line2 == VG_INVALID_HANDLE )
        return CT_ERROR;
    paint1 = vgCreatePaint();
    if ( paint1 == VG_INVALID_HANDLE )
        return CT_ERROR;
    paint2 = vgCreatePaint();
    if ( paint2 == VG_INVALID_HANDLE )
        return CT_ERROR;
        
    vgAppendPathData(line1, 9, lineCommands1, lineCoords1);
    vgAppendPathData(line2, 9, lineCommands2, lineCoords2);
    
    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_FILL_RULE, VG_EVEN_ODD);
    vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
    
    vgSetParameterfv(paint1, VG_PAINT_COLOR, 4, fillColor1);
    vgSetParameterfv(paint2, VG_PAINT_COLOR, 4, fillColor2);
    vgSetParameteri( paint1, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameteri( paint2, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSetPaint(paint1, VG_FILL_PATH);
    vgDrawPath(line1, VG_FILL_PATH);

    vgSetPaint(paint2, VG_FILL_PATH);
    vgDrawPath(line2, VG_FILL_PATH);
        
    vgDestroyPath(line1);
    vgDestroyPath(line2);    
    vgDestroyPaint(paint1);
    vgDestroyPaint(paint2);
    
    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}


