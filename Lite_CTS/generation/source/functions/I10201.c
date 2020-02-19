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

CT_Result I10201_PaintOperation_by_HUONE (CT_File *AnsFile)               
{
    VGPath  path;
    VGPaint paint;
    VGImage pattern;

    VGubyte commands[5]  =  {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[8]    =  {0.0f,0.0f, 32.0f,0.0f, 32.0f,32.0f, 0.0f,32.0f };

    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */                                              
    VGfloat fillColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};/* green color */
    VGuint  data[8];

    VGint i;
    
    for (i=0; i<8; i++) {
        data[i] = 0xFF0000FF;/* red color */
    }
        
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    pattern = vgCreateImage(VG_sRGBA_8888, 8, 1, VG_IMAGE_QUALITY_BETTER);
    if ( pattern == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyPaint(paint);
        return CT_ERROR;
    }

    vgImageSubData(pattern, data, 4*8, VG_sRGBA_8888, 0, 0, 8, 1);

    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    
    vgAppendPathData(path, 5, commands, coords);

    vgSetPaint(paint, VG_FILL_PATH);
    vgSetParameterfv(paint, VG_PAINT_COLOR, 4, fillColor);
    vgPaintPattern(paint, pattern);
    vgSetParameteri( paint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
    vgSetParameteri( paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_REPEAT );  
    
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgDrawPath(path, VG_FILL_PATH);

    vgDestroyPath(path);
    vgDestroyImage(pattern);
    vgDestroyPaint(paint);

    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}



