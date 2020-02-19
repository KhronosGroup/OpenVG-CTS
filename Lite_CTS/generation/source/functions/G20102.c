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

CT_Result G20102_PathOperation_by_HUONE (CT_File *AnsFile)               
{
    VGint   i;
    VGPath  path;
    VGfloat answer[30*4];
    VGint   dataType;
    VGPathCapabilities capTable[15] = {VG_PATH_CAPABILITY_APPEND_FROM-1,
                                       VG_PATH_CAPABILITY_APPEND_FROM,
                                       VG_PATH_CAPABILITY_APPEND_TO,
                                       VG_PATH_CAPABILITY_MODIFY,
                                       VG_PATH_CAPABILITY_TRANSFORM_FROM,
                                       VG_PATH_CAPABILITY_TRANSFORM_TO,
                                       VG_PATH_CAPABILITY_INTERPOLATE_FROM,
                                       VG_PATH_CAPABILITY_INTERPOLATE_TO ,
                                       VG_PATH_CAPABILITY_PATH_LENGTH,
                                       VG_PATH_CAPABILITY_POINT_ALONG_PATH,
                                       VG_PATH_CAPABILITY_TANGENT_ALONG_PATH,
                                       VG_PATH_CAPABILITY_PATH_BOUNDS,
                                       VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS,
                                       VG_PATH_CAPABILITY_ALL,
                                       VG_PATH_CAPABILITY_ALL+1};

    for ( dataType = VG_PATH_DATATYPE_S_8; dataType <= VG_PATH_DATATYPE_F; dataType++ ) {
        path = vgCreatePath(VG_PATH_FORMAT_STANDARD, dataType, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        if ( path == VG_INVALID_HANDLE )
            return CT_ERROR;
            
        for (i=0; i<15; i++) {
            vgRemovePathCapabilities(path, capTable[i]);
            answer[dataType*30+i] = (VGfloat)vgGetPathCapabilities(path);
        }
        vgDestroyPath(path);

        path = vgCreatePath(VG_PATH_FORMAT_STANDARD, dataType, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        if ( path == VG_INVALID_HANDLE )
            return CT_ERROR;
            
        for (i=0; i<15; i++) {
            vgClearPath(path, capTable[i]);
            answer[dataType*30+15+i] = (VGfloat)vgGetPathCapabilities(path);
        }
        vgDestroyPath(path);
    }

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (120, answer, AnsFile);
    else
        return CT_ERROR;
}


