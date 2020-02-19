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

CT_Result G30252_PathStroking_by_ATI (CT_File *AnsFile, VGuint subtest)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

 VGPath path263;
 VGubyte  path263cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path263coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path264;
 VGubyte  path264cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path264coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path265;
 VGubyte  path265cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path265coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path266;
 VGubyte  path266cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path266coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path267;
 VGubyte  path267cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path267coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path268;
 VGubyte  path268cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path268coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path269;
 VGubyte  path269cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path269coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path270;
 VGubyte  path270cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path270coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path271;
 VGubyte  path271cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path271coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path272;
 VGubyte  path272cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path272coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path273;
 VGubyte  path273cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path273coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path274;
 VGubyte  path274cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path274coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path275;
 VGubyte  path275cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path275coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path276;
 VGubyte  path276cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path276coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};

 VGPath path277;
 VGubyte  path277cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path277coord[]={ /* 8 coordinates */
     0.000000e+000f,   3.000000e+000f,   2.000000e+000f,   2.000000e+000f,   2.000000e+000f,  -2.000000e+000f,
     0.000000e+000f,  -3.000000e+000f};


    VGfloat matrix[9];
    VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color */

    path263=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path263,sizeof(path263cmd)/sizeof(VGubyte),path263cmd,path263coord);
    path264=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path264,sizeof(path264cmd)/sizeof(VGubyte),path264cmd,path264coord);
    path265=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path265,sizeof(path265cmd)/sizeof(VGubyte),path265cmd,path265coord);
    path266=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path266,sizeof(path266cmd)/sizeof(VGubyte),path266cmd,path266coord);
    path267=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path267,sizeof(path267cmd)/sizeof(VGubyte),path267cmd,path267coord);
    path268=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path268,sizeof(path268cmd)/sizeof(VGubyte),path268cmd,path268coord);
    path269=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path269,sizeof(path269cmd)/sizeof(VGubyte),path269cmd,path269coord);
    path270=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path270,sizeof(path270cmd)/sizeof(VGubyte),path270cmd,path270coord);
    path271=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path271,sizeof(path271cmd)/sizeof(VGubyte),path271cmd,path271coord);
    path272=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path272,sizeof(path272cmd)/sizeof(VGubyte),path272cmd,path272coord);
    path273=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path273,sizeof(path273cmd)/sizeof(VGubyte),path273cmd,path273coord);
    path274=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path274,sizeof(path274cmd)/sizeof(VGubyte),path274cmd,path274coord);
    path275=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path275,sizeof(path275cmd)/sizeof(VGubyte),path275cmd,path275coord);
    path276=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path276,sizeof(path276cmd)/sizeof(VGubyte),path276cmd,path276coord);
    path277=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(path277,sizeof(path277cmd)/sizeof(VGubyte),path277cmd,path277coord);

    if ( path263 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path264 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path265 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path266 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path267 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path268 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path269 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path270 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path271 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path272 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path273 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path274 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path275 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path276 == VG_INVALID_HANDLE )
        return CT_ERROR;
    if ( path277 == VG_INVALID_HANDLE )
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

  matrix[0]=   6.400000e+000f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
  matrix[3]=   0.000000e+000f; matrix[4]=   6.400000e+000f; matrix[5]=   0.000000e+000f;
  switch (subtest)
  {
  case 0:
    matrix[6]=   5.000000e+001f; matrix[7]=   0.000000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 1:
    matrix[6]=   1.000000e+001f; matrix[7]=   0.000000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 2:
    matrix[6]=   5.000000e+001f; matrix[7]=   6.200000e+001f; matrix[8]=   1.000000e+000f;
    break;
  case 3:
    matrix[6]=   1.000000e+001f; matrix[7]=   6.200000e+001f; matrix[8]=   1.000000e+000f;
    break;
  }
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
  vgLoadMatrix(matrix);
  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,14.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path263,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,13.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path264,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,12.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path265,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,11.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path266,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,10.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path267,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,9.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path268,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,8.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path269,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,7.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path270,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,6.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path271,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,5.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path272,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,4.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path273,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path274,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x00FFFFFF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,2.0000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path275,VG_STROKE_PATH);

  vgSetColor(strokepaint,0x0000FFFF);
vgSetPaint(strokepaint, VG_STROKE_PATH);
vgSetf(VG_STROKE_LINE_WIDTH,1.0000f);
vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
vgDrawPath(path276,VG_STROKE_PATH);

  vgSetColor(strokepaint,0xFFFF00FF);
  vgSetPaint(strokepaint, VG_STROKE_PATH);
  vgSetf(VG_STROKE_LINE_WIDTH,0.2000f);
  vgSetf(VG_STROKE_MITER_LIMIT,6.0000f);
  vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT  );
  vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_BEVEL);
  vgDrawPath(path277,VG_STROKE_PATH);

    vgDestroyPath(path263);
    vgDestroyPath(path264);
    vgDestroyPath(path265);
    vgDestroyPath(path266);
    vgDestroyPath(path267);
    vgDestroyPath(path268);
    vgDestroyPath(path269);
    vgDestroyPath(path270);
    vgDestroyPath(path271);
    vgDestroyPath(path272);
    vgDestroyPath(path273);
    vgDestroyPath(path274);
    vgDestroyPath(path275);
    vgDestroyPath(path276);
    vgDestroyPath(path277);
    
    vgDestroyPaint(fillpaint);
    vgDestroyPaint(strokepaint);

    if (vgGetError() == VG_NO_ERROR) {
        return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile);    
    }
    else {
        return CT_ERROR;
    }
}

