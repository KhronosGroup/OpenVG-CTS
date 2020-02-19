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

static CT_Result ReadOnlyTypeTest( VGParamType type )
{
    CT_Result error = CT_NO_ERROR;

    if ( type == VG_MAX_FLOAT ) {
        VGfloat setValue;
        VGfloat getPreValue, getCurValue;
        
        getPreValue = vgGetf( type );
        setValue = getPreValue + 1.0f;
        vgSetf( type, setValue );

        getCurValue = vgGetf( type );

        if ( getPreValue != getCurValue )
            error = CT_ERROR;

        vgGetfv(type, 1, &getPreValue);
        setValue = getPreValue + 1;
        vgSetfv(type, 1, &setValue);
        vgGetfv(type, 1, &getCurValue);
        
        if ( getPreValue != getCurValue )
           error = CT_ERROR;
    }
    else {
        VGint setValue;
        VGint getPreValue, getCurValue;
        
        getPreValue = vgGeti(type);
        setValue = getPreValue + 1;
        vgSeti(type, setValue);
        getCurValue = vgGeti(type);
        
        if ( getPreValue != getCurValue )
            error = CT_ERROR;

        vgGetiv(type, 1, &getPreValue);
        setValue = getPreValue + 1;
        vgSetiv(type, 1, &setValue);
        vgGetiv(type, 1, &getCurValue);
        
        if ( getPreValue != getCurValue )
           error = CT_ERROR;
    }
    if ( vgGetError() != VG_NO_ERROR )
        return CT_ERROR;

    return error;
}

CT_Result A20201_ParameterContext_by_HUONE(CT_File *AnsFile)
{
    VGfloat error = 0.0f;

    if ( ReadOnlyTypeTest(VG_SCREEN_LAYOUT) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_SCISSOR_RECTS) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_DASH_COUNT) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_KERNEL_SIZE) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_SEPARABLE_KERNEL_SIZE) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_COLOR_RAMP_STOPS) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_IMAGE_WIDTH) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_IMAGE_HEIGHT) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_IMAGE_PIXELS) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_IMAGE_BYTES) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_FLOAT) == CT_ERROR )
        error++;

    if ( ReadOnlyTypeTest(VG_MAX_GAUSSIAN_STD_DEVIATION) == CT_ERROR )
        error++;

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

