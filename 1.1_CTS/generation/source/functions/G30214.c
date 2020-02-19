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

CT_Result G30214_PathStroking_by_ATI (CT_File *AnsFile)
{
    VGPath path;
    VGPaint fillpaint;
    VGPaint strokepaint;

    VGubyte  path19cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path19coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path20cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path20coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path21cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path21coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     2.000000e-001f,   5.200000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path22cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path22coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     2.000000e-001f,   5.200000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path23cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path23coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     4.000000e-001f,   5.400000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path24cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path24coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     4.000000e-001f,   5.400000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path25cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path25coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     1.000000e+000f,   6.000000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};

 VGubyte  path26cmd[]={ /* 4 segments */
   VG_MOVE_TO_ABS    , VG_QUAD_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    };
 VGfloat path26coord[]={ /* 14 coordinates */
    -3.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,  -1.000000e+000f,   6.000000e+000f,
     1.000000e+000f,   6.000000e+000f,   1.000000e+000f,   4.000000e+000f,   1.000000e+000f,   2.000000e+000f,
     1.000000e+000f,   2.000000e+000f};
 
    VGfloat matrix[] = {
        1.300000e+000f, 0.000000e+000f, 0.000000e+000f,
        0.000000e+000f, 1.300000e+000f, 0.000000e+000f,
        1.500000e+001f, 4.000000e+001f, 1.000000e+000f};

    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color    */                    
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

    vgAppendPathData(path,sizeof(path19cmd)/sizeof(VGubyte),path19cmd,path19coord);
    
    vgSetColor(strokepaint,0xFF0000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,24.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path20cmd)/sizeof(VGubyte),path20cmd,path20coord);

	
    vgSetColor(strokepaint,0x000000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path21cmd)/sizeof(VGubyte),path21cmd,path21coord);

    matrix[0]=   1.300000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
    matrix[3]=   0.000000e+000f; matrix[4]=   1.300000e+000f; matrix[5]=   0.000000e+000f;
    matrix[6]=   4.700000e+001f; matrix[7]=   4.000000e+001f; matrix[8]=   1.000000e+000f;
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);
    vgSetColor(strokepaint,0xFF0000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,24.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);


    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path22cmd)/sizeof(VGubyte),path22cmd,path22coord);

    vgSetColor(strokepaint,0x000000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path23cmd)/sizeof(VGubyte),path23cmd,path23coord);


    matrix[0]=   1.300000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
    matrix[3]=   0.000000e+000f; matrix[4]=   1.300000e+000f; matrix[5]=   0.000000e+000f;
    matrix[6]=   1.500000e+001f; matrix[7]=   0.800000e+001f; matrix[8]=   1.000000e+000f;
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);
    vgSetColor(strokepaint,0xFF0000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,24.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);


    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path24cmd)/sizeof(VGubyte),path24cmd,path24coord);

    vgSetColor(strokepaint,0x000000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path25cmd)/sizeof(VGubyte),path25cmd,path25coord);

    matrix[0]=   1.300000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
    matrix[3]=   0.000000e+000f; matrix[4]=   1.300000e+000f; matrix[5]=   0.000000e+000f;
    matrix[6]=   4.700000e+001f; matrix[7]=   0.800000e+001f; matrix[8]=   1.000000e+000f;
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);
    vgSetColor(strokepaint,0xFF0000FF);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,24.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);
    vgDrawPath(path,VG_STROKE_PATH);

    vgClearPath(path,VG_PATH_CAPABILITY_ALL);
    vgAppendPathData(path,sizeof(path26cmd)/sizeof(VGubyte),path26cmd,path26coord);

    vgSetColor(strokepaint,0x000000FF);
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

