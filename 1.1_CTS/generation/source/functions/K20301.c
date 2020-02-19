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

CT_Result K20301_ColorTransform_by_HUONE(CT_File *AnsFile)
{
    VGPath path;
    VGPaint paint;
    VGubyte commands[5] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[8] = {0.0f,0.0f, 4.0f,0.0f, 4.0f,16.0f, 0.0f,16.0f};

    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */                       
    VGfloat fillColor[4][4] = {{1.0f, 0.0f, 0.0f, 1.0f},/* red color */
                              {0.0f, 1.0f, 0.0f, 1.0f},/* green color */
                              {0.0f, 0.0f, 1.0f, 1.0f},/* blue color */
                              {0.0f, 0.0f, 0.0f, 1.0f}};/* black color */   

    VGfloat scale[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    VGfloat bias[4] = { 0.25f, 0.5f, 0.75f, 1.0f };

    VGint i, j;

    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0,  VG_PATH_CAPABILITY_ALL);
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    
    vgAppendPathData(path, 5, commands, coords);

    vgSetfv( VG_CLEAR_COLOR, 4, clearColor );
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );

    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE )
        return CT_ERROR;
    
    for ( j = 0; j < 4; j++ ) {
        for ( i = 0; i < 16; i++ ) {
            if ( i >=0 && i < 4 )
                vgSetParameterfv( paint, VG_PAINT_COLOR, 4, fillColor[0]);
            else if ( i > 3 && i < 8 )
                vgSetParameterfv( paint, VG_PAINT_COLOR, 4, fillColor[1]);
            else if ( i > 7 && i < 12 )
                vgSetParameterfv( paint, VG_PAINT_COLOR, 4, fillColor[2]);
            else
                vgSetParameterfv( paint, VG_PAINT_COLOR, 4, fillColor[3]);

            vgSetPaint( paint, VG_FILL_PATH );

            vgLoadIdentity();
            vgTranslate( (VGfloat)i*4, (VGfloat)j*16 );

            /* for each channel : change scale, bias */
            switch(j) {
                case 0:
                {
                    VGfloat values[8] = {42.0f, 1.0f, 1.0f, 1.0f, 42.0f, 0.0f, 0.0f, 0.0f};
                    values[0] = scale[i%4];
                    values[4] = bias[i%4];

                    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values );
                    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
                }
                    break;
                case 1:
                {
                    VGfloat values[8] = {1.0f, 42.0f, 1.0f, 1.0f, 0.0f, 42.0f, 0.0f, 0.0f};
                    values[1] = scale[i%4];
                    values[5] = bias[i%4];

                    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
                    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
                }
                    break;
                case 2:
                {
                    VGfloat values[8] = {1.0f, 1.0f, 42.0f, 1.0f, 0.0f, 0.0f, 42.0f, 0.0f};
                    values[2] = scale[i%4];
                    values[6] = bias[i%4];

                    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
                    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
                }
                    break;
                case 3:
                {
                    VGfloat values[8] = {1.0f, 1.0f, 1.0f, 42.0f, 0.0f, 0.0f, 0.0f, 42.0f};
                    values[3] = scale[i%4];
                    values[7] = bias[i%4];

                    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
                    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
                }
                    break;
            }
            
            vgDrawPath(path, VG_FILL_PATH);
        }
    }

    vgDestroyPath(path);
    vgDestroyPaint(paint);

    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}

