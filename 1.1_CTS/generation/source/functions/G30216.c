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

CT_Result G30216_PathStroking_by_ATI (CT_File *AnsFile)
{
    VGPath path;
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGubyte  path39cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   , VG_CUBIC_TO_ABS   };
 VGfloat path39coord[]={ /* 14 coordinates */
     9.500000e+000f,   6.000000e+000f,   9.500000e+000f,   6.000000e+000f,   9.280000e+000f,   5.460000e+000f,
     8.910000e+000f,   4.650000e+000f,   8.910000e+000f,   4.650000e+000f,   8.910000e+000f,   4.650000e+000f,
     8.910000e+000f,   4.650000e+000f};

 VGubyte  path40cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   , VG_CUBIC_TO_ABS   };
 VGfloat path40coord[]={ /* 14 coordinates */
     9.500000e+000f,   6.000000e+000f,   9.500000e+000f,   6.000000e+000f,   9.280000e+000f,   5.460000e+000f,
     8.910000e+000f,   4.650000e+000f,   8.910000e+000f,   4.650000e+000f,   8.910000e+000f,   4.650000e+000f,
     8.910000e+000f,   4.650000e+000f};

 VGubyte  path41cmd[]={ /* 5 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_SQUAD_TO_ABS   ,
   VG_SQUAD_TO_ABS   , VG_LINE_TO_ABS    };
 VGfloat path41coord[]={ /* 10 coordinates */
     0.000000e+000f,   0.000000e+000f,   0.000000e+000f,  -1.800000e+001f,   6.000000e+000f,  -8.000000e+000f,
     2.000000e+001f,  -1.800000e+001f,   2.000000e+001f,   0.000000e+000f};

 VGubyte  path42cmd[]={ /* 5 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_SQUAD_TO_ABS   ,
   VG_SQUAD_TO_ABS   , VG_LINE_TO_ABS    };
 VGfloat path42coord[]={ /* 10 coordinates */
     0.000000e+000f,   0.000000e+000f,   0.000000e+000f,  -1.800000e+001f,   6.000000e+000f,  -8.000000e+000f,
     2.000000e+001f,  -1.800000e+001f,   2.000000e+001f,   0.000000e+000f};

 
    VGfloat matrix[] = {
        2.000000e+000f, 0.000000e+000f, 0.000000e+000f,
        0.000000e+000f, 2.000000e+000f, 0.000000e+000f,
        1.300000e+001f, 4.000000e+001f, 1.000000e+000f};

    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color     */                   
    VGint dataType = VG_PATH_DATATYPE_F;

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, dataType, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    fillpaint = vgCreatePaint();
    if ( fillpaint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    vgSetParameteri(fillpaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(fillpaint, VG_PAINT_COLOR, 4, defaultColor);
    strokepaint = vgCreatePaint();
    if ( strokepaint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyPaint(fillpaint);
        return CT_ERROR;
    }
    vgSetParameteri(strokepaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(strokepaint, VG_PAINT_COLOR, 4, defaultColor);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);

    vgSetfv(VG_CLEAR_COLOR, 4, defaultColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    vgAppendPathData(path,sizeof(path39cmd)/sizeof(VGubyte),path39cmd,path39coord);
    
    vgSetColor(strokepaint,0x0000FFFF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,24.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path40cmd)/sizeof(VGubyte),path40cmd,path40coord);

    vgSetColor(strokepaint,0x00FF00FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path41cmd)/sizeof(VGubyte),path41cmd,path41coord);

    matrix[0]=   2.000000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
    matrix[3]=   0.000000e+000f; matrix[4]=   1.500000e+000f; matrix[5]=   0.000000e+000f;
    matrix[6]=   1.300000e+001f; matrix[7]=   3.500000e+001f; matrix[8]=   1.000000e+000f;

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);
    vgSetColor(strokepaint,0x0000FFFF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,5.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path42cmd)/sizeof(VGubyte),path42cmd,path42coord);

    vgSetColor(strokepaint,0x00FF00FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgDestroyPath(path);
    vgDestroyPaint(fillpaint);
    vgDestroyPaint(strokepaint);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

