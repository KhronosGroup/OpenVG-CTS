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

CT_Result A30101_ParameterObject_by_HUONE(CT_File *AnsFile)
{
    VGfloat   error = 0.0f;
    VGPath  path;
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH,
                          VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[]   = { 0.0f,  0.0f, 64.0f,  0.0f, 64.0f, 64.0f,  0.0f, 64.0f,
                          16.0f, 16.0f, 48.0f, 16.0f, 48.0f, 48.0f, 16.0f, 48.0f,};                          

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );

    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    if ( vgGetParameteri( path, VG_PATH_FORMAT ) != VG_PATH_FORMAT_STANDARD )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_DATATYPE ) != VG_PATH_DATATYPE_F )
        error ++;

    if ( vgGetParameterf( path, VG_PATH_SCALE ) != 1.0f )
        error ++;

    if ( vgGetParameterf( path, VG_PATH_BIAS ) != 0.0f )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_NUM_SEGMENTS ) != 0 )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_NUM_COORDS ) != 0 )
        error ++;

    vgAppendPathData( path, 10,  commands, coords );

    if ( vgGetParameteri( path, VG_PATH_FORMAT ) != VG_PATH_FORMAT_STANDARD )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_DATATYPE ) != VG_PATH_DATATYPE_F )
        error ++;

    if ( vgGetParameterf( path, VG_PATH_SCALE ) != 1.0f )
        error ++;

    if ( vgGetParameterf( path, VG_PATH_BIAS ) != 0.0f )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_NUM_SEGMENTS ) != 10 )
        error ++;

    if ( vgGetParameteri( path, VG_PATH_NUM_COORDS ) != 16 )
        error ++;

    vgDestroyPath( path );

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

