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

CT_Result G30253_PathStroking_by_ATI (CT_File *AnsFile, VGuint subtest)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path278;
 VGubyte  path278cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path278coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path279;
 VGubyte  path279cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path279coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path280;
 VGubyte  path280cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path280coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path281;
 VGubyte  path281cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path281coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path282;
 VGubyte  path282cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path282coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path283;
 VGubyte  path283cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path283coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path284;
 VGubyte  path284cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path284coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path285;
 VGubyte  path285cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path285coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path286;
 VGubyte  path286cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path286coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path287;
 VGubyte  path287cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path287coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path288;
 VGubyte  path288cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path288coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path289;
 VGubyte  path289cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path289coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path290;
 VGubyte  path290cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path290coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path291;
 VGubyte  path291cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path291coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path292;
 VGubyte  path292cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path292coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};



    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color */                    

    path278=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path278,sizeof(path278cmd)/sizeof(VGubyte),path278cmd,path278coord);
    path279=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path279,sizeof(path279cmd)/sizeof(VGubyte),path279cmd,path279coord);
    path280=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path280,sizeof(path280cmd)/sizeof(VGubyte),path280cmd,path280coord);
    path281=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path281,sizeof(path281cmd)/sizeof(VGubyte),path281cmd,path281coord);
    path282=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path282,sizeof(path282cmd)/sizeof(VGubyte),path282cmd,path282coord);
    path283=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path283,sizeof(path283cmd)/sizeof(VGubyte),path283cmd,path283coord);
    path284=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path284,sizeof(path284cmd)/sizeof(VGubyte),path284cmd,path284coord);
    path285=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path285,sizeof(path285cmd)/sizeof(VGubyte),path285cmd,path285coord);
    path286=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path286,sizeof(path286cmd)/sizeof(VGubyte),path286cmd,path286coord);
    path287=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path287,sizeof(path287cmd)/sizeof(VGubyte),path287cmd,path287coord);
    path288=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path288,sizeof(path288cmd)/sizeof(VGubyte),path288cmd,path288coord);
    path289=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path289,sizeof(path289cmd)/sizeof(VGubyte),path289cmd,path289coord);
    path290=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path290,sizeof(path290cmd)/sizeof(VGubyte),path290cmd,path290coord);
    path291=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path291,sizeof(path291cmd)/sizeof(VGubyte),path291cmd,path291coord);
    path292=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path292,sizeof(path292cmd)/sizeof(VGubyte),path292cmd,path292coord);
 
    if ( path278 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path279 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path280 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path281 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path282 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path283 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path284 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path285 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path286 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path287 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path288 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path289 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path290 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path291 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path292 == VG_INVALID_HANDLE )
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

  matrix[0]=   6.200000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   6.200000e+000f; matrix[5]=   0.000000e+000f;
switch (subtest)
    {
    case 0:
        matrix[6]=   5.000000e+001f; matrix[7]=   0.000000e+001f; matrix[8]=   1.000000e+000f;
        break;
    case 1:
        matrix[6]=   1.000000e+001f; matrix[7]=   0.000000e+001f; matrix[8]=   1.000000e+000f;
        break;
    case 2:
        matrix[6]=   5.000000e+001f; matrix[7]=   6.400000e+001f; matrix[8]=   1.000000e+000f;
        break;
    case 3:
        matrix[6]=   1.000000e+001f; matrix[7]=   6.400000e+001f; matrix[8]=   1.000000e+000f;
        break;
    }
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,14.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path278,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,13.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path279,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,12.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path280,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,11.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path281,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,10.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path282,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,9.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path283,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,8.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path284,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,7.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path285,VG_STROKE_PATH);

vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,6.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path286,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,5.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path287,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,4.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path288,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path289,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,2.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path290,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path291,VG_STROKE_PATH);

  vgSetColor(strokepaint,0xFFFF00FF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,0.2000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path292,VG_STROKE_PATH);

    vgDestroyPath(path278);
    vgDestroyPath(path279);
    vgDestroyPath(path280);
    vgDestroyPath(path281);
    vgDestroyPath(path282);
    vgDestroyPath(path283);
    vgDestroyPath(path284);
    vgDestroyPath(path285);
    vgDestroyPath(path286);
    vgDestroyPath(path287);
    vgDestroyPath(path288);
    vgDestroyPath(path289);
    vgDestroyPath(path290);
    vgDestroyPath(path291);
    vgDestroyPath(path292);
    
    vgDestroyPaint(fillpaint);
    vgDestroyPaint(strokepaint);

    if (vgGetError() == VG_NO_ERROR) {
        return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile);  
    }
    else {
        return CT_ERROR;
    }
}

