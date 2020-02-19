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

CT_Result G30228_PathStroking_by_ATI (CT_File *AnsFile, VGuint subtest)
{
    VGPaint fillpaint;
    VGPaint strokepaint;

    VGPath testpath;
 
 VGubyte  path98cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path98coord[]={ /* 8 coordinates */
     0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.100000e+000f,   0.000000e+000f,  2.900000e+000f,
     0.000000e+000f,  3.000000e+000f};

 VGubyte  path99cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path99coord[]={ /* 8 coordinates */
     0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.000000e+000f,
     0.000000e+000f,  3.000000e+000f};

 VGubyte  path100cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path100coord[]={ /* 8 coordinates */
     0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.200000e+000f,
     0.000000e+000f,  3.000000e+000f};

 VGubyte  path101cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_CUBIC_TO_ABS   };
 VGfloat path101coord[]={ /* 8 coordinates */
     0.000000e+000f,  3.200000e+000f,   0.000000e+000f,  3.300000e+000f,   0.000000e+000f,  3.400000e+000f,
     0.000000e+000f,  3.500000e+000f};

 VGubyte  path102cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path102coord[]={ /* 4 coordinates */
     0.000000e+000f,  3.000000e+000f,   0.000000e+000f,  3.000000e+000f};

 VGubyte  path103cmd[]={ /* 2 segments */
   VG_MOVE_TO_ABS    , VG_LINE_TO_ABS    };
 VGfloat path103coord[]={ /* 4 coordinates */
     0.000000e+000f,   2.000000e+000f,   0.000000e+000f, 3.000000e+000f};


     VGfloat matrix[9];
     VGfloat defaultColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/*clear color */                       

     testpath=vgCreatePath(VG_PATH_FORMAT_STANDARD,VG_PATH_DATATYPE_F, 1.0000f,0.0000f, 0,0, (unsigned int)VG_PATH_CAPABILITY_APPEND_TO);
     
    if (subtest > 17)
    {
        path98coord[2] = path99coord[2] = path100coord[2] = path101coord[2]= 0.6f;
        path98coord[4] = path99coord[4] = path100coord[4] = path101coord[4]= 1.2f;
        path98coord[6] = path99coord[6] = path100coord[6] = path101coord[6]= 1.8f;
    }        

     switch (subtest / 3)
     {
     case 0:
         vgAppendPathData(testpath,sizeof(path98cmd)/sizeof(VGubyte),path98cmd,path98coord);
         break;
     case 1:
         vgAppendPathData(testpath,sizeof(path99cmd)/sizeof(VGubyte),path99cmd,path99coord);
         break;
     case 2:
         vgAppendPathData(testpath,sizeof(path100cmd)/sizeof(VGubyte),path100cmd,path100coord);
         break;
     case 3:
         vgAppendPathData(testpath,sizeof(path101cmd)/sizeof(VGubyte),path101cmd,path101coord);
         break;
     case 4:
         vgAppendPathData(testpath,sizeof(path102cmd)/sizeof(VGubyte),path102cmd,path102coord);
         break;
     case 5:
         vgAppendPathData(testpath,sizeof(path103cmd)/sizeof(VGubyte),path103cmd,path103coord);
         break;
     case 6:
         vgAppendPathData(testpath,sizeof(path98cmd)/sizeof(VGubyte),path98cmd,path98coord);
         break;
     case 7:
         vgAppendPathData(testpath,sizeof(path99cmd)/sizeof(VGubyte),path99cmd,path99coord);
         break;
     case 8:
         vgAppendPathData(testpath,sizeof(path100cmd)/sizeof(VGubyte),path100cmd,path100coord);
         break;
     case 9:
         vgAppendPathData(testpath,sizeof(path101cmd)/sizeof(VGubyte),path101cmd,path101coord);
         break;
     }
     if ( testpath == VG_INVALID_HANDLE )
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

     matrix[0]=   1.000000e+001f; matrix[1]=   0.000000e+000f; matrix[2]=   0.000000e+000f;
     matrix[3]=   0.000000e+000f; matrix[4]=   1.000000e+001f; matrix[5]=   0.000000e+000f;
     matrix[6]=   2.010000e+001f; matrix[7]=   3.200000e+000f; matrix[8]=   0.000000e+000f;

     vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
     vgLoadMatrix(matrix);
     vgSetColor(strokepaint,0x0000FFFF);
     vgSetPaint(strokepaint, VG_STROKE_PATH);
     vgSetf(VG_STROKE_LINE_WIDTH,3.0000f);
     vgSetf(VG_STROKE_MITER_LIMIT,4.0000f);
     vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_MITER);
     switch (subtest % 3)
     {
     case 0:
         vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_BUTT );
         break;
     case 1:
         vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_SQUARE );
         break;
     case 2:
         vgSeti(VG_STROKE_CAP_STYLE,VG_CAP_ROUND );
         break;
     }

     vgDrawPath(testpath,VG_STROKE_PATH);
     vgDestroyPath(testpath);

     vgDestroyPaint(fillpaint);
     vgDestroyPaint(strokepaint);

     if (vgGetError() == VG_NO_ERROR) {
         return SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile); 
     }
     else {
         return CT_ERROR;
     }
}

