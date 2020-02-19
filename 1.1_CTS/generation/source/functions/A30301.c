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

static void MakeValuesFromRandomInt(VGint start, VGint end, VGint count, VGint* Values)
{
    VGint i;

    for (i=0; i<count; i++)
    {
        Values[i]=(VGint)(RAND()%(end-start+1))+start;
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

static CT_Result ValuesTypeForPaintTest(VGParamType type, VGint start, VGint end, VGint count)
{
    VGint i;
    VGfloat* preFloatValue;
    VGint* preIntValue;
    VGfloat* setFloatValue;
    VGint* setIntValue;
    VGfloat* getFloatValue;
    VGint* getIntValue;
    VGPaint paint = vgCreatePaint();

    if ( paint == VG_INVALID_HANDLE )
    {
        return CT_ERROR;
    }
    preFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    preIntValue = (VGint*)MALLOC(count*sizeof(VGint));
    setFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    setIntValue = (VGint*)MALLOC(count*sizeof(VGint));
    getFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    getIntValue = (VGint*)MALLOC(count*sizeof(VGint));

    MakeValuesFromRandomFloat((VGfloat)start, (VGfloat)end, count, setFloatValue);
    MakeValuesFromRandomInt(start, end, count, setIntValue);

    /* vgSetParameteri/vgGetParameteri, vgSetParameterf/vgGetParameterf, vgSetParameteriv/vgGetParameteriv, vgSetParameterfv/vgGetParameterfv check. */
    vgSetParameterfv(paint, type, count, &setFloatValue[0]);
    vgGetParameterfv(paint, type, count, &getFloatValue[0]);
    vgSetParameteriv(paint, type, count, &setIntValue[0]);
    vgGetParameteriv(paint, type, count, &getIntValue[0]);

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
            vgDestroyPaint(paint);
            return CT_ERROR;
        }     
    }
    
    /* If the count parameter of each vgSetParameteriv/vgSetParameterfv or vgGetParameteriv/vgGetParameterfv function is 0, the pointer argument is not dereferenced. */
    MEMCPY(preFloatValue, setFloatValue, count*sizeof(VGfloat));
    vgSetParameterfv(paint, type, 0, &setFloatValue[0]);
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
            vgDestroyPaint(paint);
            return CT_ERROR;
        }     
    }
    MEMCPY(preFloatValue, getFloatValue, count*sizeof(VGfloat));
    vgGetParameterfv(paint, type, 0, &getFloatValue[0]);
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
            vgDestroyPaint(paint);
            return CT_ERROR;
        }     
    }
    MEMCPY(preIntValue, setIntValue, count*sizeof(VGint));
    vgSetParameteriv(paint, type, 0, &setIntValue[0]);
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
            vgDestroyPaint(paint);
            return CT_ERROR;
        }     
    }
    MEMCPY(preIntValue, getIntValue, count*sizeof(VGint));
    vgGetParameteriv(paint, type, 0, &getIntValue[0]);
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
            vgDestroyPaint(paint);
            return CT_ERROR;
        }     
    }
    FREE(setFloatValue);
    FREE(setIntValue);
    FREE(getFloatValue);
    FREE(getIntValue);
    FREE(preFloatValue);
    FREE(preIntValue);
    vgDestroyPaint(paint);
    return CT_NO_ERROR;
    
}

static CT_Result EnumTypeForPaintTest(VGParamType type, VGint startEnum, VGint endEnum)
{
    VGint i;
    VGfloat preFloatValue;
    VGint preIntValue;
    VGfloat *setFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint* setIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGfloat* getFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint* getIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));

    VGPath paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE )
    {
        FREE(setFloatValue);
        FREE(setIntValue);
        FREE(getFloatValue);
        FREE(getIntValue);
        return CT_ERROR;
    }
    
    MakeValuesFromEnum(startEnum, endEnum, setFloatValue, setIntValue);

    for (i=0; i<endEnum-startEnum+1; i++)
    {
        /* vgGetParameterf, vgGetParameterfv check. */
        vgSetParameterf(paint, type, setFloatValue[i]);
        getFloatValue[i] = vgGetParameterf(paint, type);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }
        vgSetParameterfv(paint, type, 1, &setFloatValue[i]);
        vgGetParameterfv(paint, type, 1, &getFloatValue[i]);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }

        /* vgGetParameteri, vgGetParameteriv check. */
        vgSetParameteri(paint, type, setIntValue[i]);
        getIntValue[i] = vgGetParameteri(paint, type);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }
        vgSetParameteriv(paint, type, 1, &setIntValue[i]);
        vgGetParameteriv(paint, type, 1, &getIntValue[i]);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }

        /* If the count parameter of each vgSetparameteriv/vgSetparameterfv or vgGetparameteriv/vgGetparameterfv function is 0, the pointer argument is not dereferenced. */
        preFloatValue = setFloatValue[i];
        vgSetParameterfv(paint, type, 0, &setFloatValue[i]);
        if ( (preFloatValue != setFloatValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }
        
        preFloatValue = getFloatValue[i];
        vgGetParameterfv(paint,type, 0, &getFloatValue[i]);
        if ( (preFloatValue != getFloatValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }
        
        preIntValue = setIntValue[i];
        vgSetParameteriv(paint, type, 0, &setIntValue[i]);
        if ( (preIntValue != setIntValue[i])  || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }

        preIntValue = getIntValue[i];
        vgGetParameteriv(paint,type, 0, &getIntValue[i]);
        if ( (preIntValue != getIntValue[i]) || (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyPaint(paint);
            return CT_ERROR;
        }
    }

    FREE(setFloatValue);
    FREE(setIntValue);
    FREE(getFloatValue);
    FREE(getIntValue);
    vgDestroyPaint(paint);
    return CT_NO_ERROR;
    
}

CT_Result A30301_ParameterObject_by_HUONE(CT_File *AnsFile)
{
    VGfloat error = 0.0f;
    
    if (EnumTypeForPaintTest(VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR, VG_PAINT_TYPE_PATTERN ) == CT_ERROR)
        error ++;

    if (ValuesTypeForPaintTest(VG_PAINT_COLOR, 0, 1, 4) == CT_ERROR)
        error ++;

    if (EnumTypeForPaintTest(VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD, VG_COLOR_RAMP_SPREAD_REFLECT ) == CT_ERROR)
        error ++;

    if (EnumTypeForPaintTest(VG_PAINT_COLOR_RAMP_PREMULTIPLIED, VG_FALSE, VG_TRUE ) == CT_ERROR)
        error ++;        

    if ( vgGeti(VG_MAX_COLOR_RAMP_STOPS) < CT_MAX_COLOR_RAMP_STOPS || ValuesTypeForPaintTest(VG_PAINT_COLOR_RAMP_STOPS, 0, 1, CT_MAX_COLOR_RAMP_STOPS*5) == CT_ERROR) /* at least 32 color ramp stops */
        error ++;

    if (ValuesTypeForPaintTest(VG_PAINT_LINEAR_GRADIENT, 0, 1, 4) == CT_ERROR)
        error ++;

    if (ValuesTypeForPaintTest(VG_PAINT_RADIAL_GRADIENT, 0, 1, 5) == CT_ERROR)
        error ++;

    if (EnumTypeForPaintTest(VG_PAINT_PATTERN_TILING_MODE, VG_TILE_FILL, VG_TILE_REFLECT ) == CT_ERROR)
        error ++;

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
