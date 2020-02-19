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

CT_Result G50108_PathFilling_by_ATI (CT_File *AnsFile)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path189;
 VGubyte  path189cmd[]={ /* 31 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_CLOSE_PATH     ,
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_CLOSE_PATH     , VG_MOVE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_CLOSE_PATH     , VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_CLOSE_PATH     ,
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_CLOSE_PATH     , VG_MOVE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_CLOSE_PATH     };
 VGfloat path189coord[]={ /* 50 coordinates */
     0.000000e+000f,   0.000000e+000f,   6.000000e+001f,   2.000000e+001f,   2.000000e+001f,  -2.000000e+001f,
     2.000000e+001f,   2.000000e+001f,   6.000000e+001f,  -2.000000e+001f,   4.500000e+001f,   1.700000e+001f,
     4.500000e+001f,  -1.700000e+001f,   9.000000e+001f,  -1.700000e+001f,   9.000000e+001f,   1.700000e+001f,
     5.000000e+001f,  -1.300000e+001f,   5.000000e+001f,   1.300000e+001f,   8.500000e+001f,   1.300000e+001f,
     8.500000e+001f,  -1.300000e+001f,   5.500000e+001f,   9.000000e+000f,   5.500000e+001f,  -9.000000e+000f,
     8.000000e+001f,  -9.000000e+000f,   8.000000e+001f,   9.000000e+000f,   6.000000e+001f,   5.000000e+000f,
     6.000000e+001f,  -5.000000e+000f,   7.500000e+001f,  -5.000000e+000f,   7.500000e+001f,   5.000000e+000f,
     6.500000e+001f,   2.000000e+000f,   6.500000e+001f,  -2.000000e+000f,   7.000000e+001f,  -2.000000e+000f,
     7.000000e+001f,   2.000000e+000f};

 VGPath path190;
 VGubyte  path190cmd[]={ /* 31 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_CLOSE_PATH     ,
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_CLOSE_PATH     , VG_MOVE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_CLOSE_PATH     , VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_CLOSE_PATH     ,
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_CLOSE_PATH     , VG_MOVE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    ,
   VG_CLOSE_PATH     };
 VGfloat path190coord[]={ /* 50 coordinates */
     0.000000e+000f,   0.000000e+000f,   6.000000e+001f,   2.000000e+001f,   2.000000e+001f,  -2.000000e+001f,
     2.000000e+001f,   2.000000e+001f,   6.000000e+001f,  -2.000000e+001f,   4.500000e+001f,   1.700000e+001f,
     4.500000e+001f,  -1.700000e+001f,   9.000000e+001f,  -1.700000e+001f,   9.000000e+001f,   1.700000e+001f,
     5.000000e+001f,  -1.300000e+001f,   5.000000e+001f,   1.300000e+001f,   8.500000e+001f,   1.300000e+001f,
     8.500000e+001f,  -1.300000e+001f,   5.500000e+001f,   9.000000e+000f,   5.500000e+001f,  -9.000000e+000f,
     8.000000e+001f,  -9.000000e+000f,   8.000000e+001f,   9.000000e+000f,   6.000000e+001f,   5.000000e+000f,
     6.000000e+001f,  -5.000000e+000f,   7.500000e+001f,  -5.000000e+000f,   7.500000e+001f,   5.000000e+000f,
     6.500000e+001f,   2.000000e+000f,   6.500000e+001f,  -2.000000e+000f,   7.000000e+001f,  -2.000000e+000f,
     7.000000e+001f,   2.000000e+000f};


    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/* clear color */                 

    path189=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path189,sizeof(path189cmd)/sizeof(VGubyte),path189cmd,path189coord);
    path190=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path190,sizeof(path190cmd)/sizeof(VGubyte),path190cmd,path190coord);

    if ( path189 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path190 == VG_INVALID_HANDLE )
        return CT_ERROR;

    fillpaint = vgCreatePaint();
    if ( fillpaint == VG_INVALID_HANDLE )
        return CT_ERROR;
    vgSetParameteri(fillpaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(fillpaint, VG_PAINT_COLOR, 4, defaultColor);
    strokepaint = vgCreatePaint();
    if ( strokepaint == VG_INVALID_HANDLE )
        return CT_ERROR;
    vgSetParameteri(strokepaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    vgSetParameterfv(strokepaint, VG_PAINT_COLOR, 4, defaultColor);

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(matrix);

    vgSetfv(VG_CLEAR_COLOR, 4, defaultColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

  matrix[0]=   0.690000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   0.690000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=   0.050000e+001f; matrix[7]=   4.800000e+001f; matrix[8]=   1.000000e+000f;

  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
  vgSetColor(fillpaint,0xFF0000FF);
  vgSetPaint(fillpaint, VG_FILL_PATH);
  vgSeti(VG_FILL_RULE,VG_NON_ZERO);
  vgDrawPath(path189,VG_FILL_PATH);

  matrix[0]=   0.690000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   0.690000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=   0.050000e+001f; matrix[7]=   1.700000e+001f; matrix[8]=   1.000000e+000f;

  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
  vgSetColor(fillpaint,0x0000FFFF);
  vgSetPaint(fillpaint, VG_FILL_PATH);
  vgSeti(VG_FILL_RULE,VG_EVEN_ODD);
  vgDrawPath(path190,VG_FILL_PATH);

    vgDestroyPath(path189);
    vgDestroyPath(path190);

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

