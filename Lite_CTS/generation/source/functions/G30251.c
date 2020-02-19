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

CT_Result G30251_PathStroking_by_ATI (CT_File *AnsFile, VGuint subtest)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path250;
 VGubyte  path250cmd[]={ /* 23 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_REL    , VG_SCUBIC_TO_REL  ,
   VG_SCUBIC_TO_REL  , VG_SCUBIC_TO_REL  , VG_LINE_TO_REL    ,
   VG_LINE_TO_REL    , VG_CUBIC_TO_REL   , VG_CUBIC_TO_REL   ,
   VG_VLINE_TO_REL   , VG_SQUAD_TO_REL   , VG_SQUAD_TO_REL   ,
   VG_SQUAD_TO_REL   , VG_LINE_TO_REL    , VG_QUAD_TO_REL    ,
   VG_QUAD_TO_REL    , VG_HLINE_TO_REL   , VG_SCUBIC_TO_REL  ,
   VG_SQUAD_TO_REL   , VG_SCUBIC_TO_REL  , VG_QUAD_TO_REL    ,
   VG_CUBIC_TO_REL   , VG_QUAD_TO_REL    };
 VGfloat path250coord[]={ /* 74 coordinates */
     2.300000e+002f,  -1.500000e+001f,   0.000000e+000f,   1.500000e+001f,   1.000000e+001f,   9.000000e+000f,
     1.700000e+001f,  -1.500000e+001f,   1.500000e+001f,   1.900000e+001f,   2.300000e+001f,   1.500000e+001f,
     1.000000e+001f,   0.000000e+000f,   3.000000e+001f,   0.000000e+000f,   0.000000e+000f,  -1.500000e+001f,
     5.000000e+000f,   0.000000e+000f,   1.500000e+001f,   1.500000e+001f,   3.500000e+001f,   5.000000e+000f,
     4.000000e+001f,   0.000000e+000f,   5.000000e+001f,  -5.000000e+000f,  -7.000000e+001f,  -2.500000e+001f,
    -7.000000e+001f,  -2.500000e+001f,  -1.000000e+001f,  -1.000000e+001f,  -5.000000e+000f,  -1.000000e+001f,
     4.000000e+000f,  -1.000000e+001f,   8.000000e+000f,   0.000000e+000f,  -1.200000e+001f,   0.000000e+000f,
    -1.000000e+001f,  -1.000000e+001f,   2.000000e+001f,   1.000000e+001f,   4.000000e+000f,   1.500000e+001f,
     4.000000e+000f,   1.000000e+001f,   1.000000e+001f,   2.100000e+001f,   1.500000e+001f,   2.100000e+001f,
     1.500000e+001f,  -7.000000e+000f,   5.000000e+000f,  -9.000000e+000f,  -1.000000e+001f,  -1.100000e+001f,
    -1.000000e+001f,   0.000000e+000f,  -1.000000e+001f,   0.000000e+000f,  -5.000000e+000f,  -1.000000e+001f,
    -5.000000e+000f,  -1.000000e+001f,  -5.000000e+000f,  -1.000000e+001f,  -6.000000e+000f,  -3.000000e+000f,
    -6.000000e+000f,  -3.000000e+000f};

 VGPath path251;
 VGubyte  path251cmd[]={ /* 24 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    , VG_SCUBIC_TO_ABS  ,
   VG_SCUBIC_TO_ABS  , VG_SCUBIC_TO_ABS  , VG_LINE_TO_ABS    ,
   VG_LINE_TO_ABS    , VG_CUBIC_TO_ABS   , VG_CUBIC_TO_ABS   ,
   VG_VLINE_TO_ABS   , VG_SQUAD_TO_ABS   , VG_SQUAD_TO_ABS   ,
   VG_SQUAD_TO_ABS   , VG_LINE_TO_ABS    , VG_QUAD_TO_ABS    ,
   VG_QUAD_TO_ABS    , VG_HLINE_TO_ABS   , VG_SCUBIC_TO_ABS  ,
   VG_SQUAD_TO_ABS   , VG_SCUBIC_TO_ABS  , VG_QUAD_TO_ABS    ,
   VG_CUBIC_TO_ABS   , VG_QUAD_TO_ABS    , VG_CLOSE_PATH     };
 VGfloat path251coord[]={ /* 74 coordinates */
     2.300000e+002f,  -1.500000e+001f,   2.300000e+002f,   0.000000e+000f,   2.400000e+002f,   9.000000e+000f,
     2.470000e+002f,  -1.500000e+001f,   2.620000e+002f,   4.000000e+000f,   2.700000e+002f,   0.000000e+000f,
     2.830000e+002f,   0.000000e+000f,   3.000000e+002f,   0.000000e+000f,   3.000000e+002f,  -1.500000e+001f,
     3.050000e+002f,  -1.500000e+001f,   3.200000e+002f,   0.000000e+000f,   3.400000e+002f,  -1.000000e+001f,
     3.450000e+002f,  -1.500000e+001f,   3.950000e+002f,  -2.000000e+001f,   2.750000e+002f,  -4.000000e+001f,
     2.750000e+002f,  -4.000000e+001f,  -5.000000e+001f,   2.650000e+002f,  -5.500000e+001f,   2.550000e+002f,
    -5.100000e+001f,   2.450000e+002f,  -4.300000e+001f,   2.450000e+002f,  -5.500000e+001f,   2.450000e+002f,
    -6.500000e+001f,   2.350000e+002f,  -3.500000e+001f,   2.450000e+002f,  -3.100000e+001f,   2.500000e+002f,
    -3.100000e+001f,   2.600000e+002f,   2.700000e+002f,  -1.000000e+001f,   2.750000e+002f,  -1.000000e+001f,
     2.900000e+002f,  -1.700000e+001f,   2.950000e+002f,  -2.600000e+001f,   2.800000e+002f,  -2.800000e+001f,
     2.700000e+002f,  -2.800000e+001f,   2.700000e+002f,  -2.800000e+001f,   2.650000e+002f,  -3.800000e+001f,
     2.650000e+002f,  -3.800000e+001f,   2.650000e+002f,  -3.800000e+001f,   2.590000e+002f,  -4.100000e+001f,
     2.590000e+002f,  -4.100000e+001f};

    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color */                  

    path250=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path250,sizeof(path250cmd)/sizeof(VGubyte),path250cmd,path250coord);
    path251=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path251,sizeof(path251cmd)/sizeof(VGubyte),path251cmd,path251coord);


    if ( path250 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path251 == VG_INVALID_HANDLE )
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

  matrix[0]=   0.940000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   1.800000e+000f; matrix[5]=   0.000000e+000f;
  switch (subtest)
  {
  case 0:
    matrix[6]=  -2.1200000e+002f; matrix[7]=   5.500000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 1:
    matrix[6]=  -2.8000000e+002f; matrix[7]=   5.500000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 2:
    matrix[6]=  -2.1200000e+002f; matrix[7]=   11.500000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 3:
    matrix[6]=  -2.800000e+002f; matrix[7]=   11.500000e+001f; matrix[8]=   1.000000e+000f;
    break;
  }
  matrix[6] += 0.01f;
  matrix[7] += 0.17f;
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);

  vgSetColor(fillpaint,0x0000FFFF);
  vgSetPaint(fillpaint, VG_FILL_PATH);
  vgSeti(VG_FILL_RULE,VG_EVEN_ODD);
  vgSetColor(strokepaint,0x00000080);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,10.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path250,VG_FILL_PATH|VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FF00FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,5.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path251,VG_STROKE_PATH);

    vgDestroyPath(path250);
    vgDestroyPath(path251);
    
    vgDestroyPaint(fillpaint);
    vgDestroyPaint(strokepaint);

    if (vgGetError() == VG_NO_ERROR) {
        return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile); 
    }
    else {
        return CT_ERROR;
    }
}

