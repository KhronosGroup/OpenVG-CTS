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
#include "../static/vguapi.h"

#if (TEST_OPTION_VGU != 0)

#define CT_ERRORIF_ASSERT( c, x )    { if ( (c) != (x) )          { result = CT_ERROR; } }

CT_Result checkLine( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguLine( VG_INVALID_HANDLE, 0, 0, 10, 10 );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguLine( path, 0, 0, 10, 10 );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);
    
    return result;
}

CT_Result checkPolygon( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;
    VGfloat      points[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguPolygon( VG_INVALID_HANDLE, points, 4, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_ILLEGAL_ARGUMENT_ERROR */   
    /* if points is NULL */
    code = vguPolygon( path, NULL, 4, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* if points is not properly aligned */
    code = vguPolygon( path, (VGfloat*)0x03, 4, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    
    /* if points is less than or equal to 0 */
    code = vguPolygon( path, points, 0, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguPolygon( path, points, -1, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguPolygon( path, points, 4, VG_TRUE );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);

    return result;
}

CT_Result checkRect( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;    
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguRect( VG_INVALID_HANDLE, 0, 0, 10.0f, 10.0f );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_ILLEGAL_ARGUMENT_ERROR */    
    /* if width or height are less than or equal to 0 */
    code = vguRect( path, 0, 0,   0.0f, 10.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRect( path, 0, 0, -10.0f, 10.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRect( path, 0, 0, 10.0f,   0.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRect( path, 0, 0, 10.0f, -10.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguRect( path, 0, 0, 10.0f, 10.0f );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);

    return result;
}

CT_Result checkRoundRect( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;    
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguRoundRect( VG_INVALID_HANDLE, 0, 0, 10.0f, 10.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_ILLEGAL_ARGUMENT_ERROR */    
    /* if width or height are less than or equal to 0 */
    code = vguRoundRect( path, 0, 0,   0.0f, 10.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRoundRect( path, 0, 0, -10.0f, 10.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRoundRect( path, 0, 0, 10.0f,   0.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguRoundRect( path, 0, 0, 10.0f, -10.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguRoundRect( path, 0, 0, 10.0f, 10.0f, 1.0f, 1.0f );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);

    return result;
}

CT_Result checkEllipse( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;    
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguEllipse( VG_INVALID_HANDLE, 0, 0, 10.0f, 20.0f );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_ILLEGAL_ARGUMENT_ERROR */    
    /* if width or height are less than or equal to 0 */
    code = vguEllipse( path, 0, 0,   0.0f,  20.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguEllipse( path, 0, 0, -10.0f,  20.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguEllipse( path, 0, 0,  10.0f,   0.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguEllipse( path, 0, 0,  10.0f, -20.0f );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguEllipse( path, 0, 0, 10.0f, 20.0f );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);

    return result;
}

CT_Result checkArc( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGPath       path;    
    VGUErrorCode code;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VGU_BAD_HANDLE_ERROR */
    /* if path is not a valid handle, or is not shared width the current context */
    code = vguArc( VG_INVALID_HANDLE, 0, 0, 10.0f, 20.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_BAD_HANDLE_ERROR);

    /* VGU_ILLEGAL_ARGUMENT_ERROR */    
    /* if width or height are less than or equal to 0 */
    code = vguArc( path, 0, 0,   0.0f,  20.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguArc( path, 0, 0, -10.0f,  20.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguArc( path, 0, 0,  10.0f,   0.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguArc( path, 0, 0,  10.0f, -20.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* if arcType is not one of the values from the VGUArcType enumeration */
    code = vguArc( path, 0, 0, 10.0f, 20.0f, -10.0f, 90.0f, VGU_ARC_OPEN - 1 );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    code = vguArc( path, 0, 0, 10.0f, 20.0f, -10.0f, 90.0f, VGU_ARC_PIE + 1 );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);    

    /* VGU_PATH_CAPABLITITY_APPEND_TO */
    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for path */
    vgClearPath( path, ~VG_PATH_CAPABILITY_APPEND_TO );
    code = vguArc( path, 0, 0, 10.0f, 20.0f, -10.0f, 90.0f, VGU_ARC_PIE );
        CT_ERRORIF_ASSERT(code, VGU_PATH_CAPABILITY_ERROR);

    vgDestroyPath(path);

    return result;
}

CT_Result checkComputeWarpQuadToSquare( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGfloat      matrix[9];
    VGUErrorCode code;

    /* VGU_ILLEGAL_ARGUMENT_ERROR */
    /* if matrix is NULL */
    code = vguComputeWarpQuadToSquare( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    /* if matrix is not properly aligned */
    code = vguComputeWarpQuadToSquare( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, (VGfloat*)0x03 );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    
    /* VGU_BAD_WARP_ERROR */
    /* if no non-degenerate transform satisfies the constraints */
    code = vguComputeWarpQuadToSquare( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, matrix );
        CT_ERRORIF_ASSERT(code, VGU_BAD_WARP_ERROR);

    return result;
}

CT_Result checkComputeWarpSquareToQuad( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGfloat      matrix[9];
    VGUErrorCode code;

    /* VGU_ILLEGAL_ARGUMENT_ERROR */
    /* if matrix is NULL */
    code = vguComputeWarpSquareToQuad( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* if matrix is not properly aligned */
    code = vguComputeWarpSquareToQuad( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, (VGfloat*)0x03 );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    
    /* VGU_BAD_WARP_ERROR */
    /* if no non-degenerate transform satisfies the constraints */
    code = vguComputeWarpSquareToQuad( 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, matrix );
        CT_ERRORIF_ASSERT(code, VGU_BAD_WARP_ERROR);

    return result;
}

CT_Result checkComputeWarpQuadToQuad( void )
{
    CT_Result    result = CT_NO_ERROR;
    VGfloat      matrix[9];
    VGUErrorCode code;

    /* VGU_ILLEGAL_ARGUMENT_ERROR */
    /* if matrix is NULL */
    code = vguComputeWarpQuadToQuad( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);

    /* if matrix is not properly aligned */
    code = vguComputeWarpQuadToQuad( 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, (VGfloat*)0x03 );
        CT_ERRORIF_ASSERT(code, VGU_ILLEGAL_ARGUMENT_ERROR);
    
    /* VGU_BAD_WARP_ERROR */
    /* if no non-degenerate transform satisfies the constraints */
    code = vguComputeWarpQuadToQuad( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, matrix );
        CT_ERRORIF_ASSERT(code, VGU_BAD_WARP_ERROR);

    return result;
}

CT_Result M10102_ParameterCoverage_by_HUONE(CT_File *AnsFile)
{
    VGint i;
    VGfloat error = 0.0f;

    /* VGU API Error Check */
    for ( i = 0; STRCMP( funcVguList[i].name, "End of List" ) != 0; i++ ) {
        if ( vgGetError() != VG_NO_ERROR )
            return CT_ERROR;
        if (funcVguList[i].func() == CT_ERROR) {
            error++;
        }
    }

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}

#endif
