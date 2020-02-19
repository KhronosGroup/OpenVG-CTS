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

CT_Result H10101_ImageOperation_by_HUONE (CT_File *AnsFile)               
{
    VGImage image;
    
    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};/* black color */
    VGfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f};/* white color */
    VGint   format;
    VGint   i;

    VGint   sRGBX_8888[WINDSIZEX],      sRGBX_8888_T[WINDSIZEX];
    VGint   sRGBA_8888[WINDSIZEX],      sRGBA_8888_T[WINDSIZEX];
    VGint   sRGBA_8888_PRE[WINDSIZEX],  sRGBA_8888_PRE_T[WINDSIZEX];
    VGshort sRGB_565[WINDSIZEX],        sRGB_565_T[WINDSIZEX];
    VGshort sRGBA_5551[WINDSIZEX],      sRGBA_5551_T[WINDSIZEX];
    VGshort sRGBA_4444[WINDSIZEX],      sRGBA_4444_T[WINDSIZEX];
    VGubyte sL_8[WINDSIZEX],            sL_8_T[WINDSIZEX];
    VGint   lRGBX_8888[WINDSIZEX],      lRGBX_8888_T[WINDSIZEX];
    VGint   lRGBA_8888[WINDSIZEX],      lRGBA_8888_T[WINDSIZEX];
    VGint   lRGBA_8888_PRE[WINDSIZEX],  lRGBA_8888_PRE_T[WINDSIZEX];
    VGubyte lL_8[WINDSIZEX],            lL_8_T[WINDSIZEX];
    VGubyte A_8[WINDSIZEX],             A_8_T[WINDSIZEX];
    VGubyte BW_1[WINDSIZEX],            BW_1_T[WINDSIZEX];
    VGubyte A_1[WINDSIZEX],             A_1_T[WINDSIZEX];
    VGubyte A_4[WINDSIZEX],             A_4_T[WINDSIZEX];

    for (i=0; i<64; i++) {
        sRGBX_8888[i]       = (VGint)0xFF000080;    
        sRGBA_8888[i]       = (VGint)0xFF000080;
        sRGBA_8888_PRE[i]   = (VGint)0x80000080;
        sRGB_565[i]         = (VGshort)0xF800;
        sRGBA_5551[i]       = (VGshort)0xF801;
        sRGBA_4444[i]       = (VGshort)0xF008;
        sL_8[i]             = (VGubyte)0x80;
        lRGBX_8888[i]       = (VGint)0xFF000080;    
        lRGBA_8888[i]       = (VGint)0xFF000080;
        lRGBA_8888_PRE[i]   = (VGint)0x80000080;
        lL_8[i]             = (VGubyte)0x80;
        A_8[i]              = (VGubyte)0x80;
        BW_1[i]             = (VGubyte)0xAA;
        A_1[i]              = (VGubyte)0xAA;
        A_4[i]              = (VGubyte)0x88;
    }
    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    
    for (format = VG_sRGBX_8888; format<=VG_A_4; format++) {
        image  = vgCreateImage( format, WINDSIZEX, 1, VG_IMAGE_QUALITY_NONANTIALIASED );
        if ( image == VG_INVALID_HANDLE )
            return CT_ERROR;
        switch(format) {
            case VG_sRGBX_8888:
                vgImageSubData(image, sRGBX_8888, 4*WINDSIZEX, format, 32, 0, 32, 1);
                vgGetImageSubData(image, sRGBX_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGBX_8888_T, 4*WINDSIZEX, format, 32, 0, 32, 1);
                break;
            case VG_sRGBA_8888:
                vgImageSubData(image, sRGBA_8888, 4*WINDSIZEX, format, 32, 0, 32, 1);
                vgGetImageSubData(image, sRGBA_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGBA_8888_T, 4*WINDSIZEX, format, 32, 0, 32, 1);
                break;
            case VG_sRGBA_8888_PRE:
                vgImageSubData(image, sRGBA_8888_PRE, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, sRGBA_8888_PRE_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGBA_8888_PRE_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_sRGB_565:
                vgImageSubData(image, sRGB_565, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, sRGB_565_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGB_565_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_sRGBA_5551:
                vgImageSubData(image, sRGBA_5551, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, sRGBA_5551_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGBA_5551_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_sRGBA_4444:
                vgImageSubData(image, sRGBA_4444, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, sRGBA_4444_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sRGBA_4444_T, 2*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_sL_8:
                vgImageSubData(image, sL_8, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, sL_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, sL_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_lRGBX_8888:
                vgImageSubData(image, lRGBX_8888, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, lRGBX_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, lRGBX_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_lRGBA_8888:
                vgImageSubData(image, lRGBA_8888, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, lRGBA_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, lRGBA_8888_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_lRGBA_8888_PRE:
                vgImageSubData(image, lRGBA_8888_PRE, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, lRGBA_8888_PRE_T, 4*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, lRGBA_8888_PRE_T, 4*WINDSIZEX, format, 32, 0,  32, 1);                
                break;
            case VG_lL_8:
                vgImageSubData(image, lL_8, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, lL_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, lL_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_A_8:
                vgImageSubData(image, A_8, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, A_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, A_8_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_BW_1:
                vgImageSubData(image, BW_1, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, BW_1_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, BW_1_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_A_1:
                vgImageSubData(image, A_1, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, A_1_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, A_1_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
            case VG_A_4:
                vgImageSubData(image, A_4, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgGetImageSubData(image, A_4_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                vgImageSubData(image, A_4_T, 1*WINDSIZEX, format, 32, 0,  32, 1);
                break;
        }
        vgSetfv(VG_CLEAR_COLOR, 4, whiteColor);
        vgClearImage(image, 48, 0,  16, 1);
        vgDrawImage(image);
        vgDestroyImage(image);
        vgTranslate(0.0f, 1.0f);
    }

    if ( vgGetError() == VG_NO_ERROR)
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    else
        return CT_ERROR;
}


