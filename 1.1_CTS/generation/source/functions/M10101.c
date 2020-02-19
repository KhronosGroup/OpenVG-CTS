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

#if (TEST_OPTION_VGU != 0)

#define CT_ENUM(name, value)    { #name, name, value }

typedef struct _CT_EnumCheckRec {
    VGbyte *name;
    VGint value;
    VGint true_;
} CT_EnumCheckRec;

const CT_EnumCheckRec vguEnumList[] = {
    /* Errors */
    CT_ENUM(VGU_NO_ERROR                         , 0x0000),
    CT_ENUM(VGU_BAD_HANDLE_ERROR                 , 0xF000),
    CT_ENUM(VGU_ILLEGAL_ARGUMENT_ERROR           , 0xF001),
    CT_ENUM(VGU_OUT_OF_MEMORY_ERROR              , 0xF002),
    CT_ENUM(VGU_PATH_CAPABILITY_ERROR            , 0xF003),
    CT_ENUM(VGU_BAD_WARP_ERROR                   , 0xF004),

    /* ArcType */
    CT_ENUM(VGU_ARC_OPEN                         , 0xF100),
    CT_ENUM(VGU_ARC_CHORD                        , 0xF101),
    CT_ENUM(VGU_ARC_PIE                          , 0xF102),
};

VGint GetVguEnumSize( void )
{
    return ( sizeof(vguEnumList) / sizeof(CT_EnumCheckRec) );
}

CT_Result M10101_ParameterCoverage_by_HUONE(CT_File *AnsFile)
{
    VGint i, count;
    VGfloat error = 0.0f;

    count = GetVguEnumSize();
    for ( i = 0; i < count; i++ )  {
        if ( vguEnumList[i].value != vguEnumList[i].true_ ) {
            error++;
        }
    }

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

#endif
