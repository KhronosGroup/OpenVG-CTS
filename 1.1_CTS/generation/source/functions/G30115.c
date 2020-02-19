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

CT_Result G30115_PathStroking_by_ATI (CT_File *AnsFile)
{
    VGPaint fillpaint;
    VGPaint strokepaint;
 VGPath path191;
 VGubyte  path191cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path191coord[]={ /* 4 coordinates */
    -5.000000e+001f,  -3.000000e+000f,  -5.000000e+001f,   3.000000e+000f};

 VGPath path192;
 VGubyte  path192cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path192coord[]={ /* 4 coordinates */
    -3.500000e+001f,  -3.000000e+000f,  -3.500000e+001f,   3.000000e+000f};

 VGPath path193;
 VGubyte  path193cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path193coord[]={ /* 6 coordinates */
     0.000000e+000f,  -5.000000e-001f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   5.000000e-001f};

 VGPath path194;
 VGubyte  path194cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path194coord[]={ /* 6 coordinates */
     0.000000e+000f,  -1.000000e+000f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   1.000000e+000f};

 VGPath path195;
 VGubyte  path195cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path195coord[]={ /* 6 coordinates */
     0.000000e+000f,  -2.000000e+000f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   2.000000e+000f};

 VGPath path196;
 VGubyte  path196cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path196coord[]={ /* 6 coordinates */
     0.000000e+000f,  -4.000000e+000f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   4.000000e+000f};

 VGPath path197;
 VGubyte  path197cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path197coord[]={ /* 6 coordinates */
     0.000000e+000f,  -8.000000e+000f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   8.000000e+000f};

 VGPath path198;
 VGubyte  path198cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path198coord[]={ /* 6 coordinates */
     0.000000e+000f,  -1.600000e+001f,  -2.000000e+001f,   0.000000e+000f,   0.000000e+000f,   1.600000e+001f};

    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color  */                      

    path191=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path191,sizeof(path191cmd)/sizeof(VGubyte),path191cmd,path191coord);
    path192=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path192,sizeof(path192cmd)/sizeof(VGubyte),path192cmd,path192coord);
    path193=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path193,sizeof(path193cmd)/sizeof(VGubyte),path193cmd,path193coord);
    path194=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path194,sizeof(path194cmd)/sizeof(VGubyte),path194cmd,path194coord);
    path195=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path195,sizeof(path195cmd)/sizeof(VGubyte),path195cmd,path195coord);
    path196=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path196,sizeof(path196cmd)/sizeof(VGubyte),path196cmd,path196coord);
    path197=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path197,sizeof(path197cmd)/sizeof(VGubyte),path197cmd,path197coord);
    path198=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path198,sizeof(path198cmd)/sizeof(VGubyte),path198cmd,path198coord);

    if ( path191 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path192 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path193 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path194 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path195 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path196 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path197 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path198 == VG_INVALID_HANDLE )
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

  matrix[0]=   1.100000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   1.500000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=   6.000000e+001f; matrix[7]=   3.200000e+001f; matrix[8]=   1.000000e+000f;

  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
  vgSetColor(strokepaint,0xFFFFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,0.5000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path191,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FF00FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,0.5000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path192,VG_STROKE_PATH);

  vgSetColor(strokepaint,0xFF0000FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path193,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x000000FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path194,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FF00FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_SQUARE);
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path195,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_SQUARE);
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path196,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_SQUARE);
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path197,VG_STROKE_PATH);

  vgSetColor(strokepaint,0xFF0000FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,25.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path198,VG_STROKE_PATH);

    vgDestroyPath(path191);
    vgDestroyPath(path192);
    vgDestroyPath(path193);
    vgDestroyPath(path194);
    vgDestroyPath(path195);
    vgDestroyPath(path196);
    vgDestroyPath(path197);
    vgDestroyPath(path198);
    
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


