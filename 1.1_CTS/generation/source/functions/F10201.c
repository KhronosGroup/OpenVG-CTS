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

void MakeMaskImage(VGImage image, VGImageFormat format)
{
    VGint   iData[4];
    VGshort sData[4];
    VGbyte  bData[4];
    
    switch(format) {
        case VG_sRGBX_8888:
        case VG_lRGBX_8888:        
            iData[0] = (VGint)0xFF000000;
            iData[1] = (VGint)0x00000000;
            iData[2] = (VGint)0x00000000;
            iData[3] = (VGint)0xFF000000;
            vgImageSubData(image, iData, 8, format, 0, 0, 2, 2);
            break;

        case VG_sRGBA_8888:
        case VG_lRGBA_8888:     
        case VG_sRGBA_8888_PRE:
        case VG_lRGBA_8888_PRE:   
            iData[0] = (VGint)0x000000FF;
            iData[1] = (VGint)0x00000000;
            iData[2] = (VGint)0x00000000;
            iData[3] = (VGint)0x000000FF;
            vgImageSubData(image, iData, 8, format, 0, 0, 2, 2);
            break;

        case VG_sRGB_565:
            sData[0] = (VGshort)0xF800;
            sData[1] = (VGshort)0x0000;
            sData[2] = (VGshort)0x0000;
            sData[3] = (VGshort)0xF800;
            vgImageSubData(image, sData, 4, format, 0, 0, 2, 2);
            break;

        case VG_sRGBA_5551:
            sData[0] = (VGshort)0x0001;
            sData[1] = (VGshort)0x0000;
            sData[2] = (VGshort)0x0000;
            sData[3] = (VGshort)0x0001;
            vgImageSubData(image, sData, 4, format, 0, 0, 2, 2);
            break;

        case VG_sRGBA_4444:
            sData[0] = (VGshort)0x000F;
            sData[1] = (VGshort)0x0000;
            sData[2] = (VGshort)0x0000;
            sData[3] = (VGshort)0x000F;
            vgImageSubData(image, sData, 4, format, 0, 0, 2, 2);
            break;

        case VG_sL_8:
        case VG_lL_8:     
        case VG_A_8:
            bData[0] = (VGbyte)0xFF;
            bData[1] = (VGbyte)0x00;
            bData[2] = (VGbyte)0x00;
            bData[3] = (VGbyte)0xFF;
            vgImageSubData(image, bData, 2, format, 0, 0, 2, 2);
            break;

        case VG_BW_1:
        case VG_A_1:
            bData[0] = (VGbyte)0x01;
            bData[1] = (VGbyte)0x02;
            vgImageSubData(image, bData, 1, format, 0, 0, 2, 2);
            break;

        case VG_A_4:
            bData[0] = (VGbyte)0x0f;
            bData[1] = (VGbyte)0xf0;
            vgImageSubData(image, bData, 1, format, 0, 0, 2, 2);
            break;
    }
}

CT_Result F10201_MaskingOperation_by_HUONE (CT_File *AnsFile)               
{
    VGPath    path;
    VGPaint   paint;
    VGImage   mask;
    VGfloat   blackColor[] = {0.0f, 0.0f, 0.0f, 0.0f};

    VGubyte commands[5] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[]    = {0.0f, 0.0f, (VGfloat)WINDSIZEX, 0.0f, (VGfloat)WINDSIZEX, (VGfloat)WINDSIZEY, 0.0f, (VGfloat)WINDSIZEY};
    
    VGint     i, format;
    
    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE ) {
        return CT_ERROR;
    }
    vgAppendPathData( path, 5, commands, coords);

    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    vgSetPaint(paint, VG_FILL_PATH);
    vgSetColor(paint, 0x00FF00FF);

    vgSetfv( VG_CLEAR_COLOR, 4, blackColor );
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);

    vgSeti( VG_MASKING, VG_TRUE );    
    
    vgMask( VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, WINDSIZEX, WINDSIZEY );

    for( format = VG_sRGBX_8888, i=0; format <= VG_A_4; format++, i++ ) {
        mask = vgCreateImage( format, 2, 2, VG_IMAGE_QUALITY_NONANTIALIASED );
        if ( mask == VG_INVALID_HANDLE ) {
            return CT_ERROR;
            
        }
        MakeMaskImage( mask, format );
        
        vgMask( VG_INVALID_HANDLE, VG_FILL_MASK,  0,  2*i, 8, 2 );
        vgMask( mask, VG_SET_MASK              ,  0,  2*i, 2, 2 );
        vgMask( mask, VG_UNION_MASK            ,  2,  2*i, 2, 2 );
        vgMask( mask, VG_INTERSECT_MASK        ,  4,  2*i, 2, 2 );
        vgMask( mask, VG_SUBTRACT_MASK         ,  6,  2*i, 2, 2 );
        vgMask( mask, VG_SET_MASK              ,  8,  2*i, 2, 2 );
        vgMask( mask, VG_UNION_MASK            , 10,  2*i, 2, 2 );
        vgMask( mask, VG_INTERSECT_MASK        , 12,  2*i, 2, 2 );
        vgMask( mask, VG_SUBTRACT_MASK         , 14,  2*i, 2, 2 );
        
        vgDrawPath( path, VG_FILL_PATH );

        vgDestroyImage( mask );
    }

    vgDestroyPath(path);
    vgDestroyPaint(paint);

    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}
