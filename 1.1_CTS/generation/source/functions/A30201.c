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

static void MakeValuesFromEnum(VGint startEnum, VGint endEnum, VGfloat* fValues, VGint* iValues)
{
    VGint i;

    for (i=startEnum; i<=endEnum; i++)
    {
        fValues[i-startEnum]=(VGfloat)i;
        iValues[i-startEnum]=i;        
    }
}

static CT_Result EnumTypeForImageTest(VGParamType type, VGint startEnum, VGint endEnum)
{
    VGint i;
    VGfloat *setFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint* setIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGfloat* getFloatValue = (VGfloat*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));
    VGint* getIntValue = (VGint*)MALLOC((endEnum-startEnum+1)*sizeof(VGfloat));

    VGImage image = VG_INVALID_HANDLE;
    
    MakeValuesFromEnum(startEnum, endEnum, setFloatValue, setIntValue);

    for (i=0; i<endEnum-startEnum+1; i++)
    {
        switch(type)
        {
            case VG_IMAGE_FORMAT:
                image  = vgCreateImage( setIntValue[i], 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED);
                break;
        }
        
        if ( image == VG_INVALID_HANDLE )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        /* vgGetParameterf, vgGetParameterfv check. */
        getFloatValue[i] = vgGetParameterf(image, type);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyImage(image);
            return CT_ERROR;
        }

        vgGetParameterfv(image, type, 1, &getFloatValue[i]);
        if ( getFloatValue[i] != setFloatValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyImage(image);
            return CT_ERROR;
        }
        if ( image != VG_INVALID_HANDLE )
            vgDestroyImage(image);

        switch(type)
        {
            case VG_IMAGE_FORMAT:
                image  = vgCreateImage( setIntValue[i], 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED);
                break;
        }
        
        if ( image == VG_INVALID_HANDLE )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            return CT_ERROR;
        }
        
        /* vgGetParameteri, vgGetParameteriv check. */
        getIntValue[i] = vgGetParameteri(image, type);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyImage(image);
            return CT_ERROR;
        }

        vgGetParameteriv(image, type, 1, &getIntValue[i]);
        if ( getIntValue[i] != setIntValue[i] )
        {
            FREE(setFloatValue);
            FREE(setIntValue);
            FREE(getFloatValue);
            FREE(getIntValue);
            vgDestroyImage(image);
            return CT_ERROR;
        }

        if ( image != VG_INVALID_HANDLE )
            vgDestroyImage(image);
        
    }

    FREE(setFloatValue);
    FREE(setIntValue);
    FREE(getFloatValue);
    FREE(getIntValue);

    return CT_NO_ERROR;
    
}

CT_Result ValuesTypeForImageTest(VGParamType type)
{
    VGint count;
    VGfloat setFloatValue;
    VGint setIntValue;
    VGfloat* getFloatValue;
    VGint* getIntValue;

    VGImage image  = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED);
    if ( image == VG_INVALID_HANDLE )
        return CT_ERROR;
    
    count = vgGetParameterVectorSize(image, type);
    getFloatValue = (VGfloat*)MALLOC(count*sizeof(VGfloat));
    getIntValue = (VGint*)MALLOC(count*sizeof(VGint));
    
    /* vgGetParameteri, vgGetParameterf, vgGetParameteriv, vgGetParameterfv check. */
    switch(type)
    {
        case VG_IMAGE_WIDTH:
            setFloatValue = 64.0f;
            setIntValue = 64;
            break;
        case VG_IMAGE_HEIGHT:
            setFloatValue = 64.0f;
            setIntValue = 64;
            break;
    }

    getFloatValue[0] = vgGetParameterf(image, type);
    getIntValue[0] = vgGetParameteri(image, type);

    if ( getFloatValue[0] != setFloatValue || 
         getIntValue[0] != setIntValue )
    {
        FREE(getFloatValue);
        FREE(getIntValue);
        vgDestroyImage(image);
        return CT_ERROR;
    }
    
    vgGetParameterfv(image, type, count, &getFloatValue[0]);
    vgGetParameteriv(image, type, count, &getIntValue[0]);

    if ( getFloatValue[0] != setFloatValue || 
            getIntValue[0] != setIntValue )
    {
        FREE(getFloatValue);
        FREE(getIntValue);
        vgDestroyImage(image);
        return CT_ERROR;
    }     
    
    FREE(getFloatValue);
    FREE(getIntValue);
    vgDestroyImage(image);
    return CT_NO_ERROR;
    
}

CT_Result A30201_ParameterObject_by_HUONE(CT_File *AnsFile)
{
    VGfloat error = 0.0f;
    
    /* vgSetParameteri/vgGetParameteri, vgSetParameterf/vgGetParameterf, vgSetParameteriv/vgGetParameteriv, vgSetParameterfv/vgGetParameterfv check. */    
    if (EnumTypeForImageTest(VG_IMAGE_FORMAT, VG_sRGBX_8888, VG_A_4 ) == CT_ERROR)
        error ++;

    if (ValuesTypeForImageTest(VG_IMAGE_WIDTH) == CT_ERROR)
        error ++;

    if (ValuesTypeForImageTest(VG_IMAGE_HEIGHT) == CT_ERROR)
        error ++;
    
    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

