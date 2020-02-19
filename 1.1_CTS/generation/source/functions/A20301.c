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

CT_Result A20301_ParameterContext_by_HUONE(CT_File *AnsFile)
{
    VGint   iValue;
    VGfloat fValue;
    VGfloat error = 0.0f;
    
    /* 
        - VG_SCREEN_LAYOUT
    
        VG_MAX_XXX_XXXX parameter check
        - VG_MAX_SCISSOR_RECTS >= 32
        - VG_MAX_DASH_COUNT >= 16
        - VG_MAX_KERNEL_SIZE >= 7
        - VG_MAX_SEPARABLE_KERNEL_SIZE >= 15
        - VG_MAX_COLOR_RAMP_STOPS >= 32
        - VG_MAX_IMAGE_WIDTH >= 256
        - VG_MAX_IMAGE_HEIGHT >= 256
        - VG_MAX_IMAGE_PIXELS >= 65536
        - VG_MAX_IMAGE_BYTES >= 65536
        - VG_MAX_FLOAT >= 10^10
     */

    vgGetiv(VG_SCREEN_LAYOUT, 1, &iValue);
    if (vgGeti(VG_SCREEN_LAYOUT) < VG_PIXEL_LAYOUT_UNKNOWN || 
        vgGeti(VG_SCREEN_LAYOUT) > VG_PIXEL_LAYOUT_BGR_HORIZONTAL || 
        iValue < VG_PIXEL_LAYOUT_UNKNOWN || iValue > VG_PIXEL_LAYOUT_BGR_HORIZONTAL)
        error++;     

    vgGetiv(VG_MAX_SCISSOR_RECTS, 1, &iValue);
    if (vgGeti(VG_MAX_SCISSOR_RECTS) < 32 || iValue < 32)
        error++;

    vgGetiv(VG_MAX_DASH_COUNT, 1, &iValue);
    if (vgGeti(VG_MAX_DASH_COUNT) < 16 || iValue < 16)
        error++;

    vgGetiv(VG_MAX_KERNEL_SIZE, 1, &iValue);
    if (vgGeti(VG_MAX_KERNEL_SIZE) < 7 || iValue < 7)
        error++;

    vgGetiv(VG_MAX_SEPARABLE_KERNEL_SIZE, 1, &iValue);
    if (vgGeti(VG_MAX_SEPARABLE_KERNEL_SIZE) < 15 || iValue < 15)
        error++;

    vgGetiv(VG_MAX_COLOR_RAMP_STOPS, 1, &iValue);
    if (vgGeti(VG_MAX_COLOR_RAMP_STOPS) < 32 || iValue < 32)
        error++;

    vgGetiv(VG_MAX_IMAGE_WIDTH, 1, &iValue);
    if (vgGeti(VG_MAX_IMAGE_WIDTH) < 256 || iValue < 256)
        error++;

    vgGetiv(VG_MAX_IMAGE_HEIGHT, 1, &iValue);
    if (vgGeti(VG_MAX_IMAGE_HEIGHT) < 256 || iValue < 256)        
        error++;

    vgGetiv(VG_MAX_IMAGE_PIXELS, 1, &iValue);
    if (vgGeti(VG_MAX_IMAGE_PIXELS) < 65536 || iValue < 65536)
        error++;

    vgGetiv(VG_MAX_IMAGE_BYTES, 1, &iValue);
    if (vgGeti(VG_MAX_IMAGE_BYTES) < 65536 || iValue < 65536)
        error++;

    vgGetfv(VG_MAX_FLOAT, 1, &fValue);
    if (vgGetf(VG_MAX_FLOAT) < (VGfloat)1e+10 || fValue < (VGfloat)1e+10)        
        error++;

    vgGetiv(VG_MAX_GAUSSIAN_STD_DEVIATION, 1, &iValue);
    if (vgGeti(VG_MAX_GAUSSIAN_STD_DEVIATION) < 16 || iValue < 16)
        error++;        

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

