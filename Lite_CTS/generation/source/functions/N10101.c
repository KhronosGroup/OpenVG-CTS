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

CT_Result N10101_MSAA_by_HUONE(CT_File *AnsFile, VGuint subtest)
{
    VGPath path1, path2;
    VGPaint paint;
    VGfloat errorSum = 0.0f;

    VGubyte cmds1[] = { VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords1[] = { 32.0f,8.0f, 56.0f,32.0f, 32.0f,56.0f, 8.0f,32.0f };

    VGubyte cmds2[] = { VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH,
                       VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords2[] = { 0.0f,0.0f, 64.0f,0.0f, 64.0f,64.0f, 0.0f,64.0f,
                         32.0f,8.0f, 56.0f,32.0f, 32.0f,56.0f, 8.0f,32.0f };

    VGubyte cmds3[] = { VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS, VG_SCWARC_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords3[] = { 32.0f,8.0f, 24.0f,24.0f,180.0f,32.0f,56.0f, 24.0f,24.0f,180.0f,32.0f,8.0f };

    VGubyte cmds4[] = { VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH,
                       VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS, VG_SCWARC_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords4[] = { 0.0f,0.0f, 64.0f,0.0f, 64.0f,64.0f, 0.0f,64.0f,
                         32.0f,8.0f, 24.0f,24.0f,180.0f,32.0f,56.0f, 24.0f,24.0f,180.0f,32.0f,8.0 };

    VGubyte cmds5[] = { VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords5[] = { 8.0f,32.0f, 24.0f,24.0f,180.0f,56.0f,32.0f, 32.0f,8.0f };

    VGubyte cmds6[] = { VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH,
                       VG_MOVE_TO_ABS, VG_SCWARC_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH };
    VGfloat coords6[] = { 0.0f,0.0f, 64.0f,0.0f, 64.0f,64.0f, 0.0f,64.0f,
                         8.0f,32.0f, 24.0f,24.0f,180.0f,56.0f,32.0f, 32.0f,8.0f };

    VGfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    VGfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    path1 = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path1 == VG_INVALID_HANDLE )
        return CT_ERROR;  
    path2 = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path2 == VG_INVALID_HANDLE ) {
        vgDestroyPath( path1 );
        return CT_ERROR;
    }

    switch ( subtest % 3 )
    {
        /* Lozenge */
        case 0:
            vgAppendPathData( path1, 4, cmds1, coords1 );
            vgAppendPathData( path2, 10, cmds2, coords2 );
            break;
        /* Circle */
        case 1:
            vgAppendPathData( path1, 4, cmds3, coords3 );
            vgAppendPathData( path2, 9, cmds4, coords4 );
            break;
        /* Arc + Triangle */
        case 2:
            vgAppendPathData( path1, 4, cmds5, coords5 );
            vgAppendPathData( path2, 9, cmds6, coords6 );
            break;
    }

    switch ( subtest )
    {
        case 0:
        case 1:
        case 2:
            /* Render Quality Setting, Non-AA */
            vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
            break;
        case 3:
        case 4:
        case 5:
            /* Render Quality Setting, BETTER */
            vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
            break;
    }

    /* 1. Clear Screen with blue color */
    vgSetfv(VG_CLEAR_COLOR, 4, blue);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath( path1 );
        vgDestroyPath( path2 );  
        return CT_ERROR;
    }
    vgSetParameterfv( paint, VG_PAINT_COLOR, 4, red );
    vgSetPaint( paint, VG_FILL_PATH );

    {
        /* 2. First Path Rendering */
        vgLoadIdentity();
        vgDrawPath( path1, VG_FILL_PATH );
    }

    {
        /* 3. Second Path Rendering */
        vgLoadIdentity();
        vgDrawPath( path2, VG_FILL_PATH );
    }

    {
        VGubyte *buf = NULL;
        VGint i;
        
        buf = (VGubyte *)MALLOC(WINDSIZEX * WINDSIZEY * 4 * sizeof(VGubyte));
        if ( !buf ) {
            vgDestroyPath( path1 );
            vgDestroyPath( path2 );
            vgDestroyPaint( paint );
            return CT_ERROR;
        }

        vgReadPixels(buf, WINDSIZEX*4, VG_sRGBA_8888, 0, 0, WINDSIZEX, WINDSIZEY);

        /* Blue channel must be zero. */
        for ( i = 0; i < WINDSIZEX * WINDSIZEY; i++ ) {  
            if ( buf[i*4+1] != 0x00 )
                errorSum++;
        }

        FREE(buf);
    }
    
    /* Release Handles */
    vgDestroyPath( path1 );
    vgDestroyPath( path2 );
    vgDestroyPaint( paint );
    
    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile(1, &errorSum, AnsFile);
    else
        return CT_ERROR;
}

