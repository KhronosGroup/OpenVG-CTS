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

static void MakeValuesFromRandomFloat(VGfloat start, VGfloat end, VGint count, VGfloat* Values)
{
    VGint i;

    if ( start == 0.0f && end == 1.0f )
    {
        for (i=0; i<count; i++)
        {
            Values[i]=(VGfloat)(RAND()%256)/255.0f;
        }
    }
    else
    {
        for (i=0; i<count; i++)
        {
            Values[i]=(VGfloat)(RAND()%(VGint)(end-start+1))+start;
        }
    }
}

static void MakeValuesFromEnum(VGint startEnum, VGint endEnum, VGfloat* fValues, VGint* iValues)
{
    VGint i;

    for (i=startEnum; i<=endEnum; i++)
    {
        fValues[i-startEnum]=(VGfloat)i;
        iValues[i-startEnum]=i;        
    }
}

static void MakeValuesFromRandomInt(VGint start, VGint end, VGint count, VGint* Values)
{
    VGint i;

    for (i=0; i<count; i++)
    {
        Values[i]=(VGint)(RAND()%(end-start+1))+start;
    }
}

static CT_Result EnumTypeTest(VGParamType type, VGint startEnum, VGint endEnum)
{
    VGint    i;
    VGfloat  preFloatValue;
    VGint    preIntValue;
    VGfloat *setFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint   *setIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGfloat *getFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint   *getIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));

    MakeValuesFromEnum(startEnum, endEnum, setFloatValue, setIntValue);

    for ( i=0; i<endEnum-startEnum+1; i++)
    {
        /* vgSeti/vgGeti, vgSetf/vgGetf, vgSetiv/vgGetiv, vgSetfv/vgGetfv check. */
        vgSetf(type, setFloatValue[i]);
        getFloatValue[i] = vgGetf(type);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        vgSeti(type, setIntValue[i]);
        getIntValue[i] = vgGeti(type);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        vgSetfv( type, 1, &setFloatValue[i]);
        vgGetfv(type, 1, &getFloatValue[i]);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        vgSetiv( type, 1, &setIntValue[i]);
        vgGetiv(type, 1, &getIntValue[i]);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }

        /* If the count parameter of each vgSetiv/vgSetfv or vgGetiv/vgGetfv function is 0, the pointer argument is not dereferenced. */
        preFloatValue = setFloatValue[i];
        vgSetfv( type, 0, &setFloatValue[i]);
        if ( (preFloatValue != setFloatValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        preFloatValue = getFloatValue[i];
        vgGetfv(type, 0, &getFloatValue[i]);
        if ( (preFloatValue != getFloatValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        preIntValue = setIntValue[i];
        vgSetiv( type, 0, &setIntValue[i]);
        if ( (preIntValue != setIntValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }

        preIntValue = getIntValue[i];
        vgGetiv(type, 0, &getIntValue[i]);
        if ( (preIntValue != getIntValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
    }
    
    FREE(setFloatValue);
    FREE(setIntValue);
    FREE(getFloatValue);
    FREE(getIntValue);
    return CT_NO_ERROR;
    
}

static CT_Result ValuesTypeTest(VGParamType type, VGint start, VGint end, VGint count)
{
    VGint i;
    VGfloat* preFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    VGint* preIntValue = (VGint*)MALLOC(count*sizeof(VGint));
    VGfloat* setFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    VGint* setIntValue = (VGint*)MALLOC(count*sizeof(VGint));
    VGfloat* getFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    VGint* getIntValue = (VGint*)MALLOC(count*sizeof(VGint));

    MakeValuesFromRandomFloat((VGfloat)start, (VGfloat)end, count, setFloatValue);
    MakeValuesFromRandomInt(start, end, count, setIntValue);

    /* vgSeti/vgGeti, vgSetf/vgGetf, vgSetiv/vgGetiv, vgSetfv/vgGetfv check. */
    vgSetfv( type, count, &setFloatValue[0]);
    vgGetfv(type, count, &getFloatValue[0]);
    vgSetiv( type, count, &setIntValue[0]);
    vgGetiv(type, count, &getIntValue[0]);

    for (i=0; i<count; i++)
    {
        if ( getFloatValue[i] != setFloatValue[i] || 
                getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            FREE(preFloatValue);
            FREE(preIntValue);
            return CT_ERROR;
        }     
    }
    
    /* If the count parameter of each vgSetiv/vgSetfv or vgGetiv/vgGetfv function is 0, the pointer argument is not dereferenced. */
    MEMCPY(preFloatValue, setFloatValue, count*sizeof(VGfloat));
    vgSetfv( type, 0, &setFloatValue[0]);
    for (i=0; i<count; i++)
    {
        if ( preFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            FREE(preFloatValue);
            FREE(preIntValue);
            return CT_ERROR;
        }     
    }
    MEMCPY(preFloatValue, getFloatValue, count*sizeof(VGfloat));
    vgGetfv( type, 0, &getFloatValue[0]);
    for (i=0; i<count; i++)
    {
        if ( preFloatValue[i] != getFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            FREE(preFloatValue);
            FREE(preIntValue);
            return CT_ERROR;
        }     
    }
    MEMCPY(preIntValue, setIntValue, count*sizeof(VGint));
    vgSetiv( type, 0, &setIntValue[0]);
    for (i=0; i<count; i++)
    {
        if ( preIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            FREE(preFloatValue);
            FREE(preIntValue);
            return CT_ERROR;
        }     
    }
    MEMCPY(preIntValue, getIntValue, count*sizeof(VGint));
    vgGetiv( type, 0, &getIntValue[0]);
    for (i=0; i<count; i++)
    {
        if ( preIntValue[i] != getIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            FREE(preFloatValue);
            FREE(preIntValue);
            return CT_ERROR;
        }     
    }
    FREE(setFloatValue);
    FREE(setIntValue);
    FREE(getFloatValue);
    FREE(getIntValue);
    FREE(preFloatValue);
    FREE(preIntValue);
    return CT_NO_ERROR;
    
}

CT_Result A20101_ParameterContext_by_HUONE(CT_File *AnsFile)
{
    VGfloat error = 0.0f;

    /* vgSeti/vgGeti, vgSetf/vgGetf, vgSetiv/vgGetiv, vgSetfv/vgGetfv check. */
    if ( EnumTypeTest(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE, VG_MATRIX_GLYPH_USER_TO_SURFACE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_FILL_RULE, VG_EVEN_ODD, VG_NON_ZERO) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED, VG_IMAGE_QUALITY_NONANTIALIASED) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_FASTER, VG_IMAGE_QUALITY_FASTER) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_BETTER, VG_IMAGE_QUALITY_BETTER) == CT_ERROR )
        error++;

 
    if ( EnumTypeTest(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED, VG_RENDERING_QUALITY_BETTER) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_BLEND_MODE, VG_BLEND_SRC, VG_BLEND_ADDITIVE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL, VG_DRAW_IMAGE_STENCIL) == CT_ERROR )
        error++;

    if ( vgGeti(VG_MAX_SCISSOR_RECTS) < CT_MAX_SCISSOR_RECT || ValuesTypeTest(VG_SCISSOR_RECTS, 0, 64, CT_MAX_SCISSOR_RECT*4) == CT_ERROR ) /* at least 32 scissor rectangels */
        error++;

    if ( ValuesTypeTest(VG_STROKE_LINE_WIDTH, 0, 64, vgGetVectorSize(VG_STROKE_LINE_WIDTH)) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_STROKE_CAP_STYLE, VG_CAP_BUTT, VG_CAP_SQUARE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER, VG_JOIN_BEVEL) == CT_ERROR )
        error++;

    if ( ValuesTypeTest(VG_STROKE_MITER_LIMIT, 0, 64, vgGetVectorSize(VG_STROKE_MITER_LIMIT)) == CT_ERROR )
        error++;

    if ( vgGeti(VG_MAX_DASH_COUNT) < CT_MAX_DASH_COUNT || ValuesTypeTest(VG_STROKE_DASH_PATTERN, 0, 64, CT_MAX_DASH_COUNT) == CT_ERROR ) /* at least 16 dash count */
        error++;

    if ( ValuesTypeTest(VG_STROKE_DASH_PHASE, 0, 64, vgGetVectorSize(VG_STROKE_DASH_PHASE)) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_STROKE_DASH_PHASE_RESET, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;

    if ( ValuesTypeTest(VG_TILE_FILL_COLOR, 0, 1, vgGetVectorSize(VG_TILE_FILL_COLOR)) == CT_ERROR )
        error++;

    if ( ValuesTypeTest(VG_CLEAR_COLOR, 0, 1, vgGetVectorSize(VG_CLEAR_COLOR)) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_MASKING, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_SCISSORING, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_UNKNOWN, VG_PIXEL_LAYOUT_BGR_HORIZONTAL) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_FILTER_FORMAT_LINEAR, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_FILTER_FORMAT_PREMULTIPLIED, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_FILTER_CHANNEL_MASK, VG_ALPHA, VG_RED ) == CT_ERROR )
        error++;

    if ( EnumTypeTest(VG_COLOR_TRANSFORM, VG_FALSE, VG_TRUE) == CT_ERROR )
        error++;
        
    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

