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

CT_Result G30119_PathStroking_by_ATI (CT_File *AnsFile)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path258;
 VGubyte  path258cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path258coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+001f,   4.000000e+001f,   1.998000e+001f};

 VGPath path259;
 VGubyte  path259cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path259coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+001f,   4.000000e+001f,   1.999000e+001f};

 VGPath path260;
 VGubyte  path260cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path260coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+001f,   4.000000e+001f,   2.000000e+001f};

 VGPath path261;
 VGubyte  path261cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path261coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+001f,   4.000000e+001f,   2.001000e+001f};

 VGPath path262;
 VGubyte  path262cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path262coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+001f,   4.000000e+001f,   2.002000e+001f};

    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color */                       

    path258=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path258,sizeof(path258cmd)/sizeof(VGubyte),path258cmd,path258coord);
    path259=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path259,sizeof(path259cmd)/sizeof(VGubyte),path259cmd,path259coord);
    path260=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path260,sizeof(path260cmd)/sizeof(VGubyte),path260cmd,path260coord);
    path261=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path261,sizeof(path261cmd)/sizeof(VGubyte),path261cmd,path261coord);
    path262=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path262,sizeof(path262cmd)/sizeof(VGubyte),path262cmd,path262coord);

    if ( path258 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path259 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path260 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path261 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path262 == VG_INVALID_HANDLE )
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

  matrix[0]=   1.000000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   1.000000e+000f; matrix[5]=   0.000000e+000f;
  matrix[6]=   1.000000e+001f; matrix[7]=   1.000000e+001f; matrix[8]=   1.000000e+000f;
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
  vgSetColor(strokepaint,0x0000FFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,12.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
  vgDrawPath(path258,VG_STROKE_PATH);

  vgDrawPath(path259,VG_STROKE_PATH);

  vgDrawPath(path260,VG_STROKE_PATH);

  vgDrawPath(path261,VG_STROKE_PATH);

  vgDrawPath(path262,VG_STROKE_PATH);

    vgDestroyPath(path258);
    vgDestroyPath(path259);
    vgDestroyPath(path260);
    vgDestroyPath(path261);
    vgDestroyPath(path262);
    
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

