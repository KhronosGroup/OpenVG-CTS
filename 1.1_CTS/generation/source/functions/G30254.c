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

CT_Result G30254_PathStroking_by_ATI (CT_File *AnsFile)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path316;
 VGubyte  path316cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path316coord[]={ /* 8 coordinates */
     3.3125e+00f,   4.4375e+00f,   3.3125e+00f,   4.4375e+00f,   3.0000e+00f,   3.6250e+00f,
     2.5000e+00f,   2.5625e+00f};

 VGPath path317;
 VGubyte  path317cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path317coord[]={ /* 4 coordinates */
     3.3125e+00f,   4.4375e+00f,   2.5000e+00f,   2.5625e+00f};

 VGPath path318;
 VGubyte  path318cmd[]={ /* 3 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   , VG_CUBIC_TO_ABS   };
 VGfloat path318coord[]={ /* 14 coordinates */
     9.500e-01f,   6.000e-01f,   9.500e-01f,   6.000e-01f,   9.280e-01f,   5.460e-01f,
     8.910e-01f,   4.650e-01f,   8.910e-01f,   4.650e-01f,   8.910e-01f,   4.650e-01f,
     8.910e-01f,   4.650e-01f};

 VGPath path319;
 VGubyte  path319cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path319coord[]={ /* 4 coordinates */
     9.500e-01f,   6.000e-01f,   8.910e-01f,   4.650e-01f};

 VGPath path320;
 VGubyte  path320cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path320coord[]={ /* 8 coordinates */
     8.910e-01f,   4.650e-01f,   8.910e-01f,   4.650e-01f,   8.910e-01f,   4.650e-01f,
     8.910e-01f,   4.650e-01f};



    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/* clear color */                 

    path316=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path316,sizeof(path316cmd)/sizeof(VGubyte),path316cmd,path316coord);
    path317=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path317,sizeof(path317cmd)/sizeof(VGubyte),path317cmd,path317coord);
    path318=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path318,sizeof(path318cmd)/sizeof(VGubyte),path318cmd,path318coord);
    path319=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path319,sizeof(path319cmd)/sizeof(VGubyte),path319cmd,path319coord);
    path320=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path320,sizeof(path320cmd)/sizeof(VGubyte),path320cmd,path320coord);
 
    if ( path316 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path317 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path318 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path319 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path320 == VG_INVALID_HANDLE )
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

  matrix[0]=   3.500000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   3.500000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=   2.000000e+001f; matrix[7]=   3.500000e+001f; matrix[8]=   1.000000e+000f;
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
    vgSetColor(strokepaint,0x0000FFB3);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,13.3000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
    vgDrawPath(path316,VG_STROKE_PATH);

    vgSetColor(strokepaint,0x00FF00B3);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,0.2500f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
    vgDrawPath(path317,VG_STROKE_PATH);

  matrix[0]=   5.000000e+001f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   5.000000e+001f; matrix[5]=   0.000000e+000f;
  matrix[6]=  -1.500000e+001f; matrix[7]=  -5.000000e+000f; matrix[8]=   1.000000e+000f;
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(&matrix[0]);
    vgSetColor(strokepaint,0x0000FFB3);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
    vgDrawPath(path318,VG_STROKE_PATH);

    vgSetColor(strokepaint,0x00FF00B3);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,0.0188f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
    vgDrawPath(path319,VG_STROKE_PATH);

  matrix[0]=   5.000000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   5.000000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=  -1.500000e+001f; matrix[7]=  -5.000000e+000f; matrix[8]=   1.000000e+000f;
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadMatrix(&matrix[0]);
    vgSetColor(strokepaint,0x0000FFB3);
    vgSetPaint(strokepaint, VG_STROKE_PATH);
    vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
    vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
    vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
    vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
    vgDrawPath(path320,VG_STROKE_PATH);

    vgDestroyPath(path316);
    vgDestroyPath(path317);
    vgDestroyPath(path318);
    vgDestroyPath(path319);
    vgDestroyPath(path320);

    
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

