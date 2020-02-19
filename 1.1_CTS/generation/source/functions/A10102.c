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
#include "../static/vgapi.h"

#define CT_ERROR_ASSERT( x )         { if ( vgGetError() != (x) ) { result = CT_ERROR; } }
#define CT_IFNOT_ASSERT( c, x )      { if ( (c) != (x) )            result = CT_ERROR; }
#define CT_IF_ASSERT( c, x )         { if ( (c) == (x) )            result = CT_ERROR; }

CT_Result checkGetError( void )
{
    VGErrorCode code;

    if ( vgGetError() != VG_NO_ERROR ) 
        return CT_ERROR;

    /* Set Error Code - 1st test case */
    vgLoadMatrix((const VGfloat *)NULL);
    code = vgGetError();

    if ( code <= VG_NO_ERROR || code > VG_IMAGE_IN_USE_ERROR )
        return CT_ERROR;

    if ( vgGetError() != VG_NO_ERROR ) 
        return CT_ERROR;

    /* Set Error Code - 2nd test case */
    vgDrawImage( VG_INVALID_HANDLE );
    code = vgGetError();

    if ( code <= VG_NO_ERROR || code > VG_IMAGE_IN_USE_ERROR ) 
        return CT_ERROR;

    if ( vgGetError() != VG_NO_ERROR ) 
        return CT_ERROR;

    return CT_NO_ERROR;    
}

CT_Result checkFlush( void )
{
    /* nothing */
    return CT_NO_ERROR;
}

CT_Result checkFinish( void )
{
    /* nothing */
    return CT_NO_ERROR;
}

CT_Result checkMask( void )
{
    VGImage image;
    CT_Result result = CT_NO_ERROR;

    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    vgMask( VG_INVALID_HANDLE, VG_SET_MASK, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    vgMask( VG_INVALID_HANDLE, VG_UNION_MASK, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    vgMask( VG_INVALID_HANDLE, VG_INTERSECT_MASK, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    vgMask( VG_INVALID_HANDLE, VG_SUBTRACT_MASK, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if operation is not a valid value from the VGMaskOperation enumeration */
    vgMask( image, VG_CLEAR_MASK - 1, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgMask( image, VG_SUBTRACT_MASK + 1, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if width or height is less than or equal to 0 */
    vgMask( VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0,   0,  64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgMask( VG_INVALID_HANDLE, VG_FILL_MASK,  0, 0, -64,  64 );    
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgMask( VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0,  64,   0 );    
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgMask( VG_INVALID_HANDLE, VG_FILL_MASK,  0, 0,  64, -64 );    
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgDestroyImage(image);

    return result;
}

CT_Result checkRenderToMask( void )
{
    VGPath path = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle */
    vgRenderToMask( VG_INVALID_HANDLE, VG_STROKE_PATH|VG_FILL_PATH, VG_SET_MASK );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgRenderToMask( VG_INVALID_HANDLE, VG_STROKE_PATH|VG_FILL_PATH, VG_UNION_MASK );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgRenderToMask( VG_INVALID_HANDLE, VG_STROKE_PATH|VG_FILL_PATH, VG_INTERSECT_MASK );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgRenderToMask( VG_INVALID_HANDLE, VG_STROKE_PATH|VG_FILL_PATH, VG_SUBTRACT_MASK );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);        
        
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paintModes is not a valid bitwise OR of values from the VGPaintMode enumeration */
    vgRenderToMask( path, ~(VG_STROKE_PATH|VG_FILL_PATH), VG_SET_MASK );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if operation is not a valid value from the VGMaskOperation enumeration */
    vgRenderToMask( path, VG_STROKE_PATH|VG_FILL_PATH, VG_CLEAR_MASK - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgRenderToMask( path, VG_STROKE_PATH|VG_FILL_PATH, VG_SUBTRACT_MASK + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    vgDestroyPath(path);

    return result;
}

CT_Result checkCreateMaskLayer( void )
{
    VGMaskLayer maskLayer = VG_INVALID_HANDLE;
    VGint width, height, pixels;
    CT_Result result = CT_NO_ERROR;

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height are less than or equal to 0 */
    maskLayer = vgCreateMaskLayer( 0, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    maskLayer = vgCreateMaskLayer( 64, 0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    maskLayer = vgCreateMaskLayer( -1, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    maskLayer = vgCreateMaskLayer( 64, -1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    width = vgGeti(VG_MAX_IMAGE_WIDTH);
    height = vgGeti(VG_MAX_IMAGE_HEIGHT);
    pixels = vgGeti(VG_MAX_IMAGE_PIXELS);
    
    /* if width is greater than VG_MAX_IMAGE_WIDTH */
    maskLayer = vgCreateMaskLayer( width + 1, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    /* if height is greater than VG_MAX_IMAGE_HEIGHT */
    maskLayer = vgCreateMaskLayer( height + 1, 64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(maskLayer, VG_INVALID_HANDLE);

    /* if width*height is greater than VG_MAX_IMAGE_PIXELS */
    if ( width * height > pixels )
        result = CT_ERROR;
    
    return result;
}

CT_Result checkDestroyMaskLayer( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if maskLayer is not a valid mask handle */
    vgDestroyMaskLayer(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;    
}

CT_Result checkFillMaskLayer( void )
{
    VGMaskLayer maskLayer = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    maskLayer = vgCreateMaskLayer( 64, 64 );
    if (maskLayer == VG_INVALID_HANDLE) {
        if (vgGetError() != VG_NO_ERROR)
            return CT_ERROR;
        return CT_NO_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if maskLayer is not a valid mask layer handle, or is not shared with the current context */
    vgFillMaskLayer(VG_INVALID_HANDLE, 0, 0, 64, 64, 1.0f);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if value is less than 0 or greater than 1 */
    vgFillMaskLayer(maskLayer, 0, 0, 64, 64, -1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgFillMaskLayer(maskLayer, 0, 0, 64, 64, 1.0f + 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if width or height is less than or equal to 0 */
    vgFillMaskLayer(maskLayer, 0, 0, 0, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgFillMaskLayer(maskLayer, 0, 0, 64, 0, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgFillMaskLayer(maskLayer, 0, 0, -1, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgFillMaskLayer(maskLayer, 0, 0, 64, -1, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if x or y is less than 0 */
    vgFillMaskLayer(maskLayer, -1, 0, 64, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgFillMaskLayer(maskLayer, 0, -1, 64, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if x + width is greater than the width of the mask */
    vgFillMaskLayer(maskLayer, 1, 0, 64, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if y + height is greater than the height of the mask */
    vgFillMaskLayer(maskLayer, 0, 1, 64, 64, 1.0f);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyMaskLayer(maskLayer);
    
    return result;
    
}

CT_Result checkCopyMask( void )
{
    VGMaskLayer maskLayer = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    maskLayer = vgCreateMaskLayer( 64, 64 );
    if (maskLayer == VG_INVALID_HANDLE) {
        if (vgGetError() != VG_NO_ERROR)
            return CT_ERROR;
        return CT_NO_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if maskLayer is not a valid mask layer handle */
    vgCopyMask(VG_INVALID_HANDLE, 0, 0, 0, 0, 64, 64);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height are less than or equal to 0 */
    vgCopyMask(maskLayer, 0, 0, 0, 0, -1, 64);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyMask(maskLayer, 0, 0, 0, 0, 64, -1);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyMaskLayer(maskLayer);
    
    return result;
}

CT_Result checkClear( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgClear( 0, 0,   0,  64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgClear( 0, 0, -64,  64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgClear( 0, 0,  64,   0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);    
    vgClear( 0, 0,  64, -64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);    

    return result;
}

CT_Result checkHardwareQuery( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if key is not one of the values from the VGHardwareQueryType enumeration. */
    vgHardwareQuery( VG_IMAGE_FORMAT_QUERY - 1, VG_sRGBX_8888 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgHardwareQuery( VG_PATH_DATATYPE_QUERY + 1, VG_PATH_DATATYPE_S_8 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if setting is not one of the values from the enumeration associated with key. */
    vgHardwareQuery( VG_IMAGE_FORMAT_QUERY, -1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgHardwareQuery( VG_PATH_DATATYPE_QUERY, -1);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkGetString( void )
{
    const VGubyte *result;

    result = vgGetString( VG_VENDOR - 1 );
    if ( result != NULL )
        return CT_ERROR; 

    result = vgGetString( VG_EXTENSIONS + 1 );
    if ( result != NULL )
        return CT_ERROR; 
    
    return CT_NO_ERROR;
}

CT_Result checkSetf( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetf( VG_MATRIX_MODE - 1, 1.0f );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_FILTER_CHANNEL_MASK + 1, 1.0f );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgSetf or vgSeti */
    vgSetf( VG_SCISSOR_RECTS, 1.0f );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_STROKE_DASH_PATTERN, 1.0f ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_TILE_FILL_COLOR, 1.0f );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_CLEAR_COLOR, 1.0f );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if value is not a legal enumerated value for the given parameter in vgSetf or vgSeti. */ 
    vgSetf( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetf( VG_FILL_RULE, VG_EVEN_ODD - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_FILL_RULE, VG_NON_ZERO + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgSetf( VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetf( VG_BLEND_MODE, VG_BLEND_SRC - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_BLEND_MODE, VG_BLEND_ADDITIVE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetf( VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgSetf( VG_STROKE_CAP_STYLE, VG_CAP_BUTT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_STROKE_CAP_STYLE, VG_CAP_SQUARE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetf( VG_STROKE_JOIN_STYLE, VG_JOIN_MITER - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_STROKE_JOIN_STYLE, VG_JOIN_BEVEL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetf( VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_UNKNOWN - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetf( VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_BGR_HORIZONTAL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkSeti( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSeti( VG_MATRIX_MODE - 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_FILTER_CHANNEL_MASK + 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgSeti or vgSeti */
    vgSeti( VG_SCISSOR_RECTS, 1 );      
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_STROKE_DASH_PATTERN, 1 ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_TILE_FILL_COLOR, 1 );        
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_CLEAR_COLOR, 1 );            
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if value is not a legal enumerated value for the given parameter in vgSeti or vgSeti. */ 
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSeti( VG_FILL_RULE, VG_EVEN_ODD - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_FILL_RULE, VG_NON_ZERO + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgSeti( VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSeti( VG_BLEND_MODE, VG_BLEND_SRC - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_BLEND_MODE, VG_BLEND_ADDITIVE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSeti( VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgSeti( VG_STROKE_CAP_STYLE, VG_CAP_BUTT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_STROKE_CAP_STYLE, VG_CAP_SQUARE + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSeti( VG_STROKE_JOIN_STYLE, VG_JOIN_MITER - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_STROKE_JOIN_STYLE, VG_JOIN_BEVEL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSeti( VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_UNKNOWN - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeti( VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_BGR_HORIZONTAL + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkSetfv( void )
{
    VGfloat floatValue          = 1.0f;
    VGfloat booleanValue        = VG_FALSE;
    VGfloat bitfiledValue       = 0xF;
    VGfloat matrixMode          = VG_MATRIX_PATH_USER_TO_SURFACE;
    VGfloat fillRule            = VG_EVEN_ODD;
    VGfloat imageQuality        = VG_IMAGE_QUALITY_FASTER;
    VGfloat renderingQuality    = VG_RENDERING_QUALITY_FASTER;
    VGfloat blendMode           = VG_BLEND_SRC_OVER;
    VGfloat imageMode           = VG_DRAW_IMAGE_NORMAL;
    VGfloat capStyle            = VG_CAP_BUTT;
    VGfloat joinStyle           = VG_JOIN_MITER;
    VGfloat pixelLayout         = VG_PIXEL_LAYOUT_UNKNOWN;
    VGfloat floatArray[4]       = { 0.5f, 0.5, 1.0f, 1.0f };

    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetfv( VG_MATRIX_MODE - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_FILTER_CHANNEL_MASK + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a scalar parameter in vgSetfv or vgSetiv and count is not equal to 1. */
    vgSetfv( VG_MATRIX_MODE, 0, &matrixMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_FILL_RULE, 0, &fillRule );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_IMAGE_QUALITY, 0, &imageQuality );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_RENDERING_QUALITY, 0, &renderingQuality );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_BLEND_MODE, 0, &blendMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_IMAGE_MODE, 0, &imageMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_LINE_WIDTH, 0, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_CAP_STYLE, 0, &capStyle );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_JOIN_STYLE, 0, &joinStyle );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_MITER_LIMIT, 0, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_DASH_PHASE, 0, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_DASH_PHASE_RESET, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);        
    vgSetfv( VG_MASKING, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_SCISSORING, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_PIXEL_LAYOUT, 0, &pixelLayout );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_FILTER_FORMAT_LINEAR, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_FILTER_FORMAT_PREMULTIPLIED, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_FILTER_CHANNEL_MASK, 0, &bitfiledValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is NULL in vgSetfv or vgSetiv and count is greater than 0. */
    vgSetfv( VG_SCISSOR_RECTS, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_DASH_PATTERN, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_TILE_FILL_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_CLEAR_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is not properly aligned in vgSetfv or vgSetiv */
    /* (VGfloat *)0x03 is reference address. */
    vgSetfv( VG_SCISSOR_RECTS, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_DASH_PATTERN, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_TILE_FILL_COLOR, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_CLEAR_COLOR, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    /* if count is less than 0 in vgSetfv or vgSetiv */
    vgSetfv( VG_SCISSOR_RECTS, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_STROKE_DASH_PATTERN, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_TILE_FILL_COLOR, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_CLEAR_COLOR, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if count is not a valid value for the given parameter */
    vgSetfv( VG_SCISSOR_RECTS, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
#if 0        
    vgSetfv( VG_STROKE_DASH_PATTERN, 1, floatArray ); /* If the dash pattern has an odd number of elements, the final element is ignored. */
      CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
#endif      
    vgSetfv( VG_TILE_FILL_COLOR, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetfv( VG_CLEAR_COLOR, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkSetiv( void )
{
    VGint intValue            = 1;
    VGint booleanValue        = VG_FALSE;
    VGint bitfiledValue       = 0xF;
    VGint matrixMode          = VG_MATRIX_PATH_USER_TO_SURFACE;
    VGint fillRule            = VG_EVEN_ODD;
    VGint imageQuality        = VG_IMAGE_QUALITY_FASTER;
    VGint renderingQuality    = VG_RENDERING_QUALITY_FASTER;
    VGint blendMode           = VG_BLEND_SRC_OVER;
    VGint imageMode           = VG_DRAW_IMAGE_NORMAL;
    VGint capStyle            = VG_CAP_BUTT;
    VGint joinStyle           = VG_JOIN_MITER;
    VGint pixelLayout         = VG_PIXEL_LAYOUT_UNKNOWN;
    VGint intArray[4]         = { 0, 1, 2, 3 };

    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetiv( VG_MATRIX_MODE - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_FILTER_CHANNEL_MASK + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a scalar parameter in vgSetiv or vgSetiv and count is not equal to 1. */
    vgSetiv( VG_MATRIX_MODE, 0, &matrixMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_FILL_RULE, 0, &fillRule );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_IMAGE_QUALITY, 0, &imageQuality );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_RENDERING_QUALITY, 0, &renderingQuality );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_BLEND_MODE, 0, &blendMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_IMAGE_MODE, 0, &imageMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_LINE_WIDTH, 0, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_CAP_STYLE, 0, &capStyle );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_JOIN_STYLE, 0, &joinStyle );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_MITER_LIMIT, 0, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_DASH_PHASE, 0, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_DASH_PHASE_RESET, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);        
    vgSetiv( VG_MASKING, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_SCISSORING, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_PIXEL_LAYOUT, 0, &pixelLayout );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);    
    vgSetiv( VG_FILTER_FORMAT_LINEAR, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_FILTER_FORMAT_PREMULTIPLIED, 0, &booleanValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_FILTER_CHANNEL_MASK, 0, &bitfiledValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is NULL in vgSetiv or vgSetiv and count is greater than 0. */
    vgSetiv( VG_SCISSOR_RECTS, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_DASH_PATTERN, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_TILE_FILL_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_CLEAR_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is not properly aligned in vgSetfv or vgSetiv */
    /* (VGint *)0x03 is reference address. */
    vgSetiv( VG_SCISSOR_RECTS, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_DASH_PATTERN, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_TILE_FILL_COLOR, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_CLEAR_COLOR, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if count is less than 0 in vgSetiv or vgSetiv */
    vgSetiv( VG_SCISSOR_RECTS, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_STROKE_DASH_PATTERN, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_TILE_FILL_COLOR, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_CLEAR_COLOR, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if count is not a valid value for the given parameter */
    vgSetiv( VG_SCISSOR_RECTS, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
#if 0        
    vgSetiv( VG_STROKE_DASH_PATTERN, 1, intArray ); /* If the dash pattern has an odd number of elements, the final element is ignored. */
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
#endif
    vgSetiv( VG_TILE_FILL_COLOR, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetiv( VG_CLEAR_COLOR, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkGetf( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetf( VG_MATRIX_MODE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetf( VG_MAX_GAUSSIAN_STD_DEVIATION + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetf or vgGeti. */
    vgGetf( VG_SCISSOR_RECTS );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetf( VG_STROKE_DASH_PATTERN ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetf( VG_TILE_FILL_COLOR );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetf( VG_CLEAR_COLOR );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkGeti( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGeti( VG_MATRIX_MODE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGeti( VG_MAX_GAUSSIAN_STD_DEVIATION + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetf or vgGeti. */
    vgGeti( VG_SCISSOR_RECTS );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGeti( VG_STROKE_DASH_PATTERN ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGeti( VG_TILE_FILL_COLOR );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGeti( VG_CLEAR_COLOR );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkGetfv( void )
{
    VGint   i, size;
    VGfloat floatValue;
    VGfloat floatArray[100];
    CT_Result result = CT_NO_ERROR;

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetfv( VG_MATRIX_MODE - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetfv( VG_MAX_GAUSSIAN_STD_DEVIATION + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    for ( i = VG_MATRIX_MODE; i <= VG_MAX_GAUSSIAN_STD_DEVIATION; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetfv( i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetfv( i, 0, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetfv( i, -1, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetVectorSize(i);
        vgGetfv( i, size+1, floatArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }

    /* if values is not properly aligned in vgGetfv or vgGetiv */
    /* (VGfloat *)0x03 is reference address. */
    vgGetfv( VG_SCISSOR_RECTS, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetfv( VG_STROKE_DASH_PATTERN, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetfv( VG_TILE_FILL_COLOR, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetfv( VG_CLEAR_COLOR, 4, (VGfloat *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    return result;
}


CT_Result checkGetiv( void )
{
    VGint   i, size;
    VGint   intValue;
    VGint   intArray[100];
    CT_Result result = CT_NO_ERROR;

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetiv( VG_MATRIX_MODE - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetiv( VG_MAX_GAUSSIAN_STD_DEVIATION + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    for ( i = VG_MATRIX_MODE; i <= VG_MAX_GAUSSIAN_STD_DEVIATION; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetiv( i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetiv( i, 0, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetiv( i, -1, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetVectorSize(i);
        vgGetiv( i, size+1, intArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }
    /* if values is not properly aligned in vgGetfv or vgGetiv */
    /* (VGint *)0x03 is reference address. */
    vgGetiv( VG_SCISSOR_RECTS, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetiv( VG_STROKE_DASH_PATTERN, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetiv( VG_TILE_FILL_COLOR, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetiv( VG_CLEAR_COLOR, 4, (VGint *)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    return result;    
}

CT_Result checkGetVectorSize( void )
{
    VGint i;
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetVectorSize( VG_MATRIX_MODE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetVectorSize( VG_MAX_GAUSSIAN_STD_DEVIATION + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* for scalar values, 1 is returned */
    for ( i = VG_MATRIX_MODE; i <= VG_MAX_GAUSSIAN_STD_DEVIATION; i++ ) {
        switch( i ) {
            case VG_MATRIX_MODE:
            case VG_FILL_RULE:
            case VG_IMAGE_QUALITY:
            case VG_RENDERING_QUALITY:
            case VG_BLEND_MODE:
            case VG_IMAGE_MODE:
            case VG_STROKE_LINE_WIDTH:
            case VG_STROKE_CAP_STYLE:
            case VG_STROKE_JOIN_STYLE:
            case VG_STROKE_MITER_LIMIT:
            case VG_STROKE_DASH_PHASE:
            case VG_STROKE_DASH_PHASE_RESET:            
            case VG_MAX_SCISSOR_RECTS:
            case VG_MAX_DASH_COUNT:
            case VG_MAX_KERNEL_SIZE:
            case VG_MAX_SEPARABLE_KERNEL_SIZE:
            case VG_MAX_COLOR_RAMP_STOPS:
            case VG_MAX_IMAGE_WIDTH:
            case VG_MAX_IMAGE_HEIGHT:
            case VG_MAX_IMAGE_PIXELS:
            case VG_MAX_IMAGE_BYTES:
            case VG_MAX_FLOAT:
            case VG_MAX_GAUSSIAN_STD_DEVIATION:
            case VG_MASKING:
            case VG_SCISSORING:
            case VG_PIXEL_LAYOUT:
            case VG_SCREEN_LAYOUT:            
            case VG_FILTER_FORMAT_LINEAR:
            case VG_FILTER_FORMAT_PREMULTIPLIED:
            case VG_FILTER_CHANNEL_MASK:
                CT_IFNOT_ASSERT(vgGetVectorSize(i), 1);
                break;

            case VG_TILE_FILL_COLOR :
            case VG_CLEAR_COLOR :
                CT_IFNOT_ASSERT(vgGetVectorSize(i), 4);
                break;     

            case VG_SCISSOR_RECTS :
            case VG_STROKE_DASH_PATTERN :
                if ( vgGetVectorSize(i) < 0 )
                    return CT_ERROR;
                break;
        }
    }

    return result;
}

CT_Result checkSetParameterf( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;

    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgSetParameterf( VG_INVALID_HANDLE, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetParameterf( paint, VG_PAINT_TYPE - 1, 1.0f );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1.0f );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetParameterf or vgGetParameteri */
    vgSetParameterf( paint, VG_PAINT_COLOR, 1.0f );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_COLOR_RAMP_STOPS, 1.0f ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_LINEAR_GRADIENT, 1.0f );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_RADIAL_GRADIENT, 1.0f );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if value is not a legal enumerated value for the given parameter in vgGetParameterf or vgGetParameteri. */ 
    vgSetParameterf( paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetParameterf( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetParameterf( paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_FILL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterf( paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkSetParameteri( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;

    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgSetParameteri( VG_INVALID_HANDLE, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetParameteri( paint, VG_PAINT_TYPE - 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetParameterf or vgGetParameteri */
    vgSetParameteri( paint, VG_PAINT_COLOR, 1 );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_COLOR_RAMP_STOPS, 1 ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_LINEAR_GRADIENT, 1 );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_RADIAL_GRADIENT, 1 );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if value is not a legal enumerated value for the given parameter in vgGetParameterf or vgGetParameteri. */ 
    vgSetParameteri( paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetParameteri( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgSetParameteri( paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_FILL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteri( paint, VG_PAINT_PATTERN_TILING_MODE, VG_TILE_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkSetParameterfv( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    
    VGfloat floatValue      = 1.0f;    
    VGfloat pathFormat      = VG_PATH_FORMAT_STANDARD;
    VGfloat imageFormat     = VG_sRGBA_8888;
    VGfloat paintType       = VG_PAINT_TYPE_COLOR;
    VGfloat spreadMode      = VG_COLOR_RAMP_SPREAD_PAD;
    VGfloat premultiplied   = VG_FALSE;
    VGfloat tilingMode      = VG_TILE_FILL;
    VGfloat floatArray[5]   = { 0.5f, 0.5, 1.0f, 1.0f, 1.0f };

    CT_Result result = CT_NO_ERROR;
    
    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgSetParameterfv( VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &paintType );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetParameterfv( paint, VG_PAINT_TYPE - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a scalar parameter in vgSetParameterfv or vgSetParameteriv and count is not equal to 1. */
    vgSetParameterfv( paint, VG_PAINT_TYPE, 0, &paintType );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, 0, &spreadMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED, 0, &premultiplied );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);        
    vgSetParameterfv( paint, VG_PAINT_PATTERN_TILING_MODE, 0, &tilingMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is NULL in vgSetParameterfv or vgSetParameteriv and count is greater than 0. */
    vgSetParameterfv( paint, VG_PAINT_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_LINEAR_GRADIENT, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_RADIAL_GRADIENT, 5, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is not properly aligned in vgSetParameterfv or vgSetParameteriv */
    vgSetParameterfv( paint, VG_PAINT_COLOR, 4, (VGfloat*)0x03 ); /* (VGfloat *)0x03 is reference address. */
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_LINEAR_GRADIENT, 4, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_RADIAL_GRADIENT, 5, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    /* if count is less than 0 in vgSetParameterfv or vgSetParameteriv */
    vgSetParameterfv( paint, VG_PAINT_COLOR, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_STOPS, -5, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_LINEAR_GRADIENT, -4, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_RADIAL_GRADIENT, -5, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if count is not a valid value for the given parameter */
    vgSetParameterfv( paint, VG_PAINT_COLOR, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_COLOR_RAMP_STOPS, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_LINEAR_GRADIENT, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameterfv( paint, VG_PAINT_RADIAL_GRADIENT, 1, floatArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkSetParameteriv( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    
    VGint   intValue        = 1;    
    VGint   pathFormat      = VG_PATH_FORMAT_STANDARD;
    VGint   imageFormat     = VG_sRGBA_8888;
    VGint   paintType       = VG_PAINT_TYPE_COLOR;
    VGint   spreadMode      = VG_COLOR_RAMP_SPREAD_PAD;
    VGint   premultiplied   = VG_FALSE;
    VGint   tilingMode      = VG_TILE_FILL;
    VGint   intArray[5]     = { 0, 1, 2, 3, 4 };

    CT_Result result = CT_NO_ERROR;
    
    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgSetParameteriv( VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &paintType );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgSetParameteriv( paint, VG_PAINT_TYPE - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a scalar parameter in vgSetParameterfv or vgSetParameteriv and count is not equal to 1. */
    vgSetParameteriv( paint, VG_PAINT_TYPE, 0, &paintType );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, 0, &spreadMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED, 0, &premultiplied );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_PATTERN_TILING_MODE, 0, &tilingMode );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is NULL in vgSetParameterfv or vgSetParameteriv and count is greater than 0. */
    vgSetParameteriv( paint, VG_PAINT_COLOR, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_LINEAR_GRADIENT, 4, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_RADIAL_GRADIENT, 5, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if values is not properly aligned in vgSetParameterfv or vgSetParameteriv */
    vgSetParameteriv( paint, VG_PAINT_COLOR, 4, (VGint*)0x03 ); /*(VGint *)0x03 is reference address.*/
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_LINEAR_GRADIENT, 4, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_RADIAL_GRADIENT, 5, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if count is less than 0 in vgSetParameterfv or vgSetParameteriv */
    vgSetParameteriv( paint, VG_PAINT_COLOR, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_STOPS, -5, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_LINEAR_GRADIENT, -4, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_RADIAL_GRADIENT, -5, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if count is not a valid value for the given parameter */
    vgSetParameteriv( paint, VG_PAINT_COLOR, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_COLOR_RAMP_STOPS, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_LINEAR_GRADIENT, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetParameteriv( paint, VG_PAINT_RADIAL_GRADIENT, 1, intArray );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkGetParameterf( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;
    
    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }
    
    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgGetParameterf( VG_INVALID_HANDLE, VG_PATH_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterf( VG_INVALID_HANDLE, VG_IMAGE_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterf( VG_INVALID_HANDLE, VG_PAINT_TYPE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetParameterf( path, VG_PATH_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( path, VG_PATH_NUM_COORDS + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgGetParameterf( image, VG_IMAGE_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( image, VG_IMAGE_HEIGHT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgGetParameterf( paint, VG_PAINT_TYPE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetParameterf or vgGetParameteri. */
    vgGetParameterf( paint, VG_PAINT_COLOR );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( paint, VG_PAINT_COLOR_RAMP_STOPS ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( paint, VG_PAINT_LINEAR_GRADIENT );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterf( paint, VG_PAINT_RADIAL_GRADIENT );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}


CT_Result checkGetParameteri( void )
{
    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;

    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgGetParameteri( VG_INVALID_HANDLE, VG_PATH_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameteri( VG_INVALID_HANDLE, VG_IMAGE_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameteri( VG_INVALID_HANDLE, VG_PAINT_TYPE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetParameteri( path, VG_PATH_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( path, VG_PATH_NUM_COORDS + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgGetParameteri( image, VG_IMAGE_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( image, VG_IMAGE_HEIGHT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgGetParameteri( paint, VG_PAINT_TYPE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if paramType refers to a vector parameter in vgGetParameterf or vgGetParameteri. */
    vgGetParameteri( paint, VG_PAINT_COLOR );       
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( paint, VG_PAINT_COLOR_RAMP_STOPS ); 
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( paint, VG_PAINT_LINEAR_GRADIENT );     
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteri( paint, VG_PAINT_RADIAL_GRADIENT );         
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkGetParameterfv( void )
{
    VGint   i, size;
    VGfloat floatValue;
    VGfloat floatArray[100];

    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;
    
    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }
    
    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgGetParameterfv( VG_INVALID_HANDLE, VG_PATH_FORMAT, 1, &floatValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterfv( VG_INVALID_HANDLE, VG_IMAGE_FORMAT, 1, &floatValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterfv( VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &floatValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetParameterfv( path, VG_PATH_FORMAT - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( path, VG_PATH_NUM_COORDS + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgGetParameterfv( image, VG_IMAGE_FORMAT - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( image, VG_IMAGE_HEIGHT + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgGetParameterfv( paint, VG_PAINT_TYPE - 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1, &floatValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    for ( i = VG_PATH_FORMAT; i <= VG_PATH_NUM_COORDS; i++ ) {
        /* if values is NULL in vgGetParameterfv or vgGetParameteriv */
        vgGetParameterfv( path, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetParameterfv or vgGetParameteriv */
        vgGetParameterfv( path, i, 0, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameterfv( path, i, -1, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetParameterfv or vgGetParameteriv. */
        size = vgGetParameterVectorSize(path, i);
        vgGetParameterfv( path, i, size+1, floatArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }

    for ( i = VG_IMAGE_FORMAT; i <= VG_IMAGE_HEIGHT; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetParameterfv( image, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetParameterfv( image, i, 0, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameterfv( image, i, -1, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetParameterVectorSize(image, i);
        vgGetParameterfv( image, i, size+1, floatArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }

    for ( i = VG_PAINT_TYPE; i <= VG_PAINT_COLOR_RAMP_PREMULTIPLIED; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetParameterfv( paint, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetParameterfv( paint, i, 0, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameterfv( paint, i, -1, &floatValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetParameterVectorSize(paint, i);
        vgGetParameterfv( paint, i, size+1, floatArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }    

    /* if values is not properly aligned in vgGetParameterfv or vgGetParameteriv */
    /*(VGfloat *)0x03 is reference address/*/
    vgGetParameterfv( paint, VG_PAINT_COLOR, 4, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( paint, VG_PAINT_LINEAR_GRADIENT, 4, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterfv( paint, VG_PAINT_RADIAL_GRADIENT, 5, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);    

    return result;
}

CT_Result checkGetParameteriv( void )
{
    VGint   i, size;
    VGint   intValue;
    VGint   intArray[100];

    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;

    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgGetParameteriv( VG_INVALID_HANDLE, VG_PATH_FORMAT, 1, &intValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameteriv( VG_INVALID_HANDLE, VG_IMAGE_FORMAT, 1, &intValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameteriv( VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &intValue );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetParameteriv( path, VG_PATH_FORMAT - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( path, VG_PATH_NUM_COORDS + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgGetParameteriv( image, VG_IMAGE_FORMAT - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( image, VG_IMAGE_HEIGHT + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgGetParameteriv( paint, VG_PAINT_TYPE - 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1, 1, &intValue );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    for ( i = VG_PATH_FORMAT; i <= VG_PATH_NUM_COORDS; i++ ) {
        /* if values is NULL in vgGetParameterfv or vgGetParameteriv */
        vgGetParameteriv( path, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetParameterfv or vgGetParameteriv */
        vgGetParameteriv( path, i, 0, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameteriv( path, i, -1, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetParameterfv or vgGetParameteriv. */
        size = vgGetParameterVectorSize(path, i);
        vgGetParameteriv( path, i, size+1, intArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }

    for ( i = VG_IMAGE_FORMAT; i <= VG_IMAGE_HEIGHT; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetParameteriv( image, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetParameteriv( image, i, 0, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameteriv( image, i, -1, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetParameterVectorSize(image, i);
        vgGetParameteriv( image, i, size+1, intArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }

    for ( i = VG_PAINT_TYPE; i <= VG_PAINT_COLOR_RAMP_PREMULTIPLIED; i++ ) {
        /* if values is NULL in vgGetfv or vgGetiv */
        vgGetParameteriv( paint, i, 1, NULL );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is less than or equal to 0 in vgGetfv or vgGetiv */
        vgGetParameteriv( paint, i, 0, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        vgGetParameteriv( paint, i, -1, &intValue );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

        /* if count is greater than the value returned by vgGetVectorSize for the given parameter in vgGetfv or vgGetiv. */
        size = vgGetParameterVectorSize(paint, i);
        vgGetParameteriv( paint, i, size+1, intArray );
            CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    }    
    
    /* if values is not properly aligned in vgGetParameterfv or vgGetParameteriv */
    /*(VGint *)0x03 is reference address.*/
    vgGetParameteriv( paint, VG_PAINT_COLOR, 4, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( paint, VG_PAINT_COLOR_RAMP_STOPS, 5, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( paint, VG_PAINT_LINEAR_GRADIENT, 4, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameteriv( paint, VG_PAINT_RADIAL_GRADIENT, 5, (VGint*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);    

    return result;
}

CT_Result checkGetParameterVectorSize( void )
{
    VGint   i;
    VGPath  path;
    VGImage image;
    VGPaint paint;
    CT_Result result = CT_NO_ERROR;

    path  = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;
    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
    if ( image == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        return CT_ERROR;
    }
    paint = vgCreatePaint();
    if ( paint == VG_INVALID_HANDLE ) {
        vgDestroyPath(path);
        vgDestroyImage(image);
        return CT_ERROR;
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if object is not a valid handle, or is not shared with the current context */
    vgGetParameterVectorSize( VG_INVALID_HANDLE, VG_PATH_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterVectorSize( VG_INVALID_HANDLE, VG_IMAGE_FORMAT );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGetParameterVectorSize( VG_INVALID_HANDLE, VG_PAINT_TYPE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paramType is not a valid value from the VGParamType enumeration */
    vgGetParameterVectorSize( path, VG_PATH_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterVectorSize( path, VG_PATH_NUM_COORDS + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    vgGetParameterVectorSize( image, VG_IMAGE_FORMAT - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterVectorSize( image, VG_IMAGE_HEIGHT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgGetParameterVectorSize( paint, VG_PAINT_TYPE - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetParameterVectorSize( paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* for scalar values, 1 is returned */
    for ( i = VG_PATH_FORMAT; i <= VG_PATH_NUM_COORDS; i++ ) {
        if ( vgGetParameterVectorSize(path, i) != 1 )
            return CT_ERROR;    
    }

    for ( i = VG_IMAGE_FORMAT; i <= VG_IMAGE_HEIGHT; i++ ) {
        if ( vgGetParameterVectorSize(image, i) != 1 )
            return CT_ERROR;    
    }

    for ( i = VG_PAINT_TYPE; i <= VG_PAINT_COLOR_RAMP_PREMULTIPLIED; i++ ) {
        switch( i ) {
            case VG_PAINT_TYPE :
            case VG_PAINT_COLOR_RAMP_SPREAD_MODE :
            case VG_PAINT_COLOR_RAMP_PREMULTIPLIED :
            case VG_PAINT_PATTERN_TILING_MODE :
                if ( vgGetParameterVectorSize(paint, i) != 1 )
                    return CT_ERROR;
                break;    
                    
            default :
                if ( vgGetParameterVectorSize(paint, i) < 0 )
                    return CT_ERROR;
                break;    
        }            
    }

    vgDestroyPath(path);
    vgDestroyImage(image);
    vgDestroyPaint(paint);

    return result;
}

CT_Result checkLoadIdentity( void )
{
    return CT_NO_ERROR;
}

CT_Result checkLoadMatrix( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* if m is NULL */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgLoadMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgLoadMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgLoadMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgLoadMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    /* if m is not properly aligned */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgLoadMatrix( (VGfloat*)0x03 );/*(VGint *)0x03 is reference address.*/
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgLoadMatrix( (VGfloat*)0x03 );/*(VGint *)0x03 is reference address.*/
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgLoadMatrix( (VGfloat*)0x03 );/*(VGint *)0x03 is reference address.*/
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgLoadMatrix( (VGfloat*)0x03 );/*(VGint *)0x03 is reference address.*/
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    return result;
}

CT_Result checkGetMatrix( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* if m is NULL */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgGetMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgGetMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgGetMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgGetMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    /* if m is not properly aligned */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgGetMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgGetMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgGetMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgGetMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    return result;
}

CT_Result checkMultMatrix( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* if m is NULL */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgMultMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgMultMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgMultMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgMultMatrix( NULL );
    CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    /* if m is not properly aligned */
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgMultMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE );
    vgMultMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgMultMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgMultMatrix( (VGfloat*)0x03 );
        CT_ERROR_ASSERT( VG_ILLEGAL_ARGUMENT_ERROR );

    return result;
}

CT_Result checkTranslate( void )
{
    return CT_NO_ERROR;
}

CT_Result checkScale( void )
{
    return CT_NO_ERROR;
}

CT_Result checkShear( void )
{
    return CT_NO_ERROR;
}

CT_Result checkRotate( void )
{
    return CT_NO_ERROR;
}


CT_Result checkCreatePath( void )
{
    VGPath path = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;
    
    /* VG_UNSUPPORTED_PATH_FORMAT_ERROR */
    /* if pathFormat is not a supported format */
    path = vgCreatePath(-1, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_ERROR_ASSERT(VG_UNSUPPORTED_PATH_FORMAT_ERROR);
        CT_IFNOT_ASSERT(path, VG_INVALID_HANDLE);

    /* VG_ILLEGAL_ARGUMENT_ERROR */    
    /* if datatype is not a valid value from the VGPathDatatype enumeration */
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, -1, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(path, VG_INVALID_HANDLE);

    /* if scale if equal to 0 */
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 0.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(path, VG_INVALID_HANDLE);
        
    return result;
}

CT_Result checkClearPath( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle, or is not shared width the current context */
    vgClearPath(VG_INVALID_HANDLE, VG_PATH_CAPABILITY_ALL);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;
}

CT_Result checkDestroyPath( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle, or is not shared width the current context */
    vgDestroyPath(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;
}

CT_Result checkGetPathCapabilities( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */    
    vgGetPathCapabilities(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;
}

CT_Result checkRemovePathCapabilities( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle, or is not shared width the current context */    
    vgRemovePathCapabilities(VG_INVALID_HANDLE, VG_PATH_CAPABILITY_ALL);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;
}

CT_Result checkAppendPath( void )
{
    VGPath dstPath, srcPath;
    CT_Result result = CT_NO_ERROR;
    
    srcPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(srcPath, VG_INVALID_HANDLE);

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);    
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle, or is not shared width the current context */            
    vgAppendPath(VG_INVALID_HANDLE, srcPath);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgAppendPath((VGPath)dstPath, VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_APPEND_FROM is not enabled for srcPath */
    vgClearPath(srcPath, ~VG_PATH_CAPABILITY_APPEND_FROM);
    vgClearPath(dstPath, VG_PATH_CAPABILITY_ALL);
    vgAppendPath(dstPath, srcPath);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    /* if VG_PATH_CAPABILITY_APPEND_TO is not enabled for dstPath */
    vgClearPath(srcPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPath(dstPath, srcPath);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    vgDestroyPath(srcPath);
    
    return result;
}

CT_Result checkAppendPathData( void )
{
    VGPath dstPath;
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[] = {0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 64.0f};
    VGubyte illegalcommands1[] = {VG_MOVE_TO_ABS, VG_LCWARC_TO_REL, VG_CLOSE_PATH-1};
    VGfloat illegalcoords1[] = {0.0f, 0.0f, 10.0f, 10.0f, 0.0f, 0.0f, 10.0f};
    VGubyte illegalcommands2[] = {VG_MOVE_TO_ABS, VG_LCWARC_TO_REL+1, VG_CLOSE_PATH};
    VGfloat illegalcoords2[] = {0.0f, 0.0f, 10.0f, 10.0f, 0.0f, 0.0f, 10.0f};
    VGint format;
    CT_Result result = CT_NO_ERROR;
    
    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if path is not a valid path handle, or is not shared width the current context */    
    vgAppendPathData(VG_INVALID_HANDLE, 4, commands, coords);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if pathSegments is NULL */
    vgAppendPathData(dstPath, 4, NULL, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if pathData is NULL */        
    vgAppendPathData(dstPath, 4, commands, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if numSegments is less than or equal to 0 */
    vgAppendPathData(dstPath, -4, commands, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgAppendPathData(dstPath, 0, commands, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if pathSegments contains an illegal command */
    vgAppendPathData(dstPath, 3, illegalcommands1, illegalcoords1);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgAppendPathData(dstPath, 3, illegalcommands2, illegalcoords2);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_APPEND_FROM is not enabled for srcPath */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_APPEND_TO);
    vgAppendPathData(dstPath, 4, commands, coords);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);

    /* if pathData is not properly aligned */
    for (format=VG_PATH_DATATYPE_S_8; format<=VG_PATH_DATATYPE_F; format++)
    {
        dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, format, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

        switch(format)
        {
            case VG_PATH_DATATYPE_S_8:
                break;
            case VG_PATH_DATATYPE_S_16:
                vgAppendPathData(dstPath, 4, commands, (VGshort*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
            case VG_PATH_DATATYPE_S_32:
                vgAppendPathData(dstPath, 4, commands, (VGint*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
            case VG_PATH_DATATYPE_F:
                vgAppendPathData(dstPath, 4, commands, (VGfloat*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
        }  
        vgDestroyPath(dstPath);
    }
      
    return result;
}

CT_Result checkModifyPathCoords( void )
{
    VGPath dstPath;
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[] = {0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 64.0f};
    VGint format;
    CT_Result result = CT_NO_ERROR;
    
    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    vgAppendPathData(dstPath, 4, commands, coords);    

    /* VG_BAD_HANDLE_ERROR */
    /* if dstPath is not a valid path handle, or is not shared width the current context */        
    vgModifyPathCoords(VG_INVALID_HANDLE, 0, 4, coords);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if pathData is NULL */
    vgModifyPathCoords(dstPath, 0, 4, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if startIndex is less than 0 */
    vgModifyPathCoords(dstPath, -1, 4, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* numSegments is less than or equal to 0 */
    vgModifyPathCoords(dstPath, 0, 0, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgModifyPathCoords(dstPath, 0, -4, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if startIndex + numSegments is greater than the number of segment in the path */
    vgModifyPathCoords(dstPath, 1, 4, coords);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_MODIFY is not enabled for dstPath */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_MODIFY);
    
    vgAppendPathData(dstPath, 4, commands, coords);    
    vgModifyPathCoords(dstPath, 0, 4, coords);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);
        
    vgDestroyPath(dstPath);

    /* if pathData is not properly aligned */
    /*(VGfloat)0x03 is reference address. */
    for (format=VG_PATH_DATATYPE_S_8; format<=VG_PATH_DATATYPE_F; format++)
    {
        dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, format, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
            CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

        switch(format)
        {
            case VG_PATH_DATATYPE_S_8:
                break;
            case VG_PATH_DATATYPE_S_16:
                vgModifyPathCoords(dstPath, 0, 4, (VGshort*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
            case VG_PATH_DATATYPE_S_32:
                vgModifyPathCoords(dstPath, 0, 4, (VGint*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
            case VG_PATH_DATATYPE_F:
                vgModifyPathCoords(dstPath, 0, 4, (VGfloat*)0x03);
                    CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
                break;
        }  
        vgDestroyPath(dstPath);
    }
        
    return result;
}

CT_Result checkTransformPath( void )
{
    VGPath dstPath, srcPath;
    CT_Result result = CT_NO_ERROR;

    srcPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(srcPath, VG_INVALID_HANDLE);

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if dstPath or srcPath is not a valid path handle, or is not shared width the current context */        
    vgTransformPath(VG_INVALID_HANDLE, srcPath);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgTransformPath(dstPath, VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_TRANSFORM_FROM is not enabled for srcPath */
    vgClearPath(dstPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath(srcPath, ~VG_PATH_CAPABILITY_TRANSFORM_FROM);
    vgTransformPath(dstPath, srcPath);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    /* if VG_PATH_CAPABILITY_TRANSFORM_TO is not enabled for dstPath */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_TRANSFORM_TO);
    vgClearPath(srcPath, VG_PATH_CAPABILITY_ALL);
    vgTransformPath(dstPath, srcPath);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    vgDestroyPath(srcPath);
        
    return result;
}

CT_Result checkInterpolatePath( void )
{
    VGPath dstPath, startPath, endPath;
    CT_Result result = CT_NO_ERROR;

    startPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(startPath, VG_INVALID_HANDLE);

    endPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL); 
        CT_IF_ASSERT(endPath, VG_INVALID_HANDLE);

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL); 
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */   
    /* if dstPath, startPath or endPath is not a valid path handle, or is not shared width the current context */            
    vgInterpolatePath(VG_INVALID_HANDLE, startPath, endPath, 0.5f);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    vgInterpolatePath(dstPath, VG_INVALID_HANDLE, endPath, 0.5f);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    vgInterpolatePath(dstPath, startPath, VG_INVALID_HANDLE, 0.5f);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_INTERPOLATE_TO is not enabled for dstPath */
    vgClearPath( dstPath, ~VG_PATH_CAPABILITY_INTERPOLATE_TO);
    vgClearPath( startPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath( endPath, VG_PATH_CAPABILITY_ALL);
    vgInterpolatePath(dstPath, startPath, endPath, 0.5f);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    /* if VG_PATH_CAPABILITY_INTERPOLATE_FROM is not enabled for startPath */
    vgClearPath( dstPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath( startPath, ~VG_PATH_CAPABILITY_INTERPOLATE_FROM);
    vgClearPath( endPath, VG_PATH_CAPABILITY_ALL);
    vgInterpolatePath(dstPath, startPath, endPath, 0.5f);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    /* if VG_PATH_CAPABILITY_INTERPOLATE_FROM is not enabled for endPath */        
    vgClearPath( dstPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath( startPath, VG_PATH_CAPABILITY_ALL);
    vgClearPath( endPath, ~VG_PATH_CAPABILITY_INTERPOLATE_FROM);
    vgInterpolatePath(dstPath, startPath, endPath, 0.5f);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    vgDestroyPath(startPath);
    vgDestroyPath(endPath);
    
    return result;
}

CT_Result checkPathLength( void )
{
    VGPath dstPath;
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[] = {0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 64.0f};
    CT_Result result = CT_NO_ERROR;

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);
    vgAppendPathData(dstPath, 4, commands, coords);

    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */            
    vgPathLength(VG_INVALID_HANDLE, 0, 4);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if startSegment is less than 0 */
    vgPathLength(dstPath, -1, 4);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if startSegment is than the index of the final path segment */
    vgPathLength(dstPath, 4, 4);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if numSegments is less than or equal to 0 */
    vgPathLength(dstPath, 0,  0);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathLength(dstPath, 0, -4);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    /* if (startSegment + numSegments - 1) is less than 0 or greater than the index of the final path segment */
    vgPathLength(dstPath, 0, 5);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_PATH_LENGTH is not enabled for path */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_PATH_LENGTH);
    vgPathLength(dstPath, 0, 4);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);
        
    vgDestroyPath(dstPath);

    return result;
}

CT_Result checkPointAlongPath( void )
{
    VGPath dstPath;
    VGfloat x, y, tanX, tanY;
    VGubyte commands[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS, VG_LINE_TO_ABS, VG_CLOSE_PATH};
    VGfloat coords[] = {0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 64.0f};
    CT_Result result = CT_NO_ERROR;

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);
    vgAppendPathData(dstPath, 4, commands, coords);

    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */    
    vgPointAlongPath(VG_INVALID_HANDLE, 0, 4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if startSegment is less than 0 */
    vgPointAlongPath(dstPath, -1, 4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if startSegment is greater than the index of the final path segment */
    vgPointAlongPath(dstPath, 4, 4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if numSegments is less than or equal to 0 */
    vgPointAlongPath(dstPath, 0, -4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPointAlongPath(dstPath, 0, 0, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if (startSegment + numSegments - 1) is less than 0 or greater than the index 0f the final path segment */
    vgPointAlongPath(dstPath, 0, 5, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if x, y, tangentX or tangentY is not properly aligned */
    /* (VGfloat*)0x03 is reference address. */
    vgPointAlongPath(dstPath, 0, 4, 64.0f, (VGfloat*)0x03, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPointAlongPath(dstPath, 0, 4, 64.0f, &x, (VGfloat*)0x03, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPointAlongPath(dstPath, 0, 4, 64.0f, &x, &y, (VGfloat*)0x03, &tanY);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPointAlongPath(dstPath, 0, 4, 64.0f, &x, &y, &tanX, (VGfloat*)0x03);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_POINT_ALONG_PATH is not enabled for path */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_POINT_ALONG_PATH);
    vgAppendPathData(dstPath, 4, commands, coords);
    vgPointAlongPath(dstPath, 0, 4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    /* if VG_PATH_CAPABILITY_TANGENT_ALONG_PATH capability is not enabled for path */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_TANGENT_ALONG_PATH);
    vgAppendPathData(dstPath, 4, commands, coords);
    vgPointAlongPath(dstPath, 0, 4, 64.0f, &x, &y, &tanX, &tanY);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    
    return result;
}

CT_Result checkPathBounds( void )
{   
    VGPath dstPath;
    VGfloat minX, minY, width, height;
    CT_Result result = CT_NO_ERROR;

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */    
    vgPathBounds(VG_INVALID_HANDLE, &minX, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if minX, minY, width or height is NULL */    
    vgPathBounds(dstPath, NULL, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, NULL, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, &minY, NULL, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, &minY, &width, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if minX, minY, width, or height is not properly aligned */
    /* (VGfloat*)0x03 is reference address. */
    vgPathBounds(dstPath, (VGfloat*)0x03, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, (VGfloat*)0x03, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, &minY, (VGfloat*)0x03, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathBounds(dstPath, &minX, &minY, &width, (VGfloat*)0x03);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_PATH_BOUNDS is not enabled for path */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_PATH_BOUNDS);
    vgPathBounds(dstPath, &minX, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    
    return result;
}

CT_Result checkPathTransformedBounds( void )
{
    VGPath dstPath;
    VGfloat minX, minY, width, height;
    CT_Result result = CT_NO_ERROR;

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */        
    vgPathTransformedBounds(VG_INVALID_HANDLE, &minX, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if minX, minY, width or height is NULL */    
    vgPathTransformedBounds(dstPath, NULL, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, NULL, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, &minY, NULL, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, &minY, &width, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    /* if minX, minY, width, or height is not properly aligned */
    /* (VGfloat*)0x03 is reference address. */
    vgPathTransformedBounds(dstPath, (VGfloat*)0x03, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, (VGfloat*)0x03, &width, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, &minY, (VGfloat*)0x03, &height);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgPathTransformedBounds(dstPath, &minX, &minY, &width, (VGfloat*)0x03);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    
    /* VG_PATH_CAPABILITY_ERROR */
    /* if VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS is not enabled for path */
    vgClearPath(dstPath, ~VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS);
    vgPathTransformedBounds(dstPath, &minX, &minY, &width, &height);
        CT_ERROR_ASSERT(VG_PATH_CAPABILITY_ERROR);

    vgDestroyPath(dstPath);
    
    return result;
}

CT_Result checkDrawPath( void )
{
    VGPath dstPath;
    CT_Result result = CT_NO_ERROR;

    dstPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(dstPath, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */   
    /* if path is not a valid path handle, or is not shared width the current context */            
    vgDrawPath(VG_INVALID_HANDLE, VG_FILL_PATH);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paintModes is not a valid bitwise OR of values from the VGPaintMode enumeration */    
    vgDrawPath(dstPath, ~(VG_STROKE_PATH|VG_FILL_PATH));
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyPath(dstPath);
    
    return result;
}

CT_Result checkCreatePaint( void )
{
    /* nothing */
    return CT_NO_ERROR;
}

CT_Result checkDestroyPaint( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if paint is not a valid paint handle, or is not shared with the current context */
    vgDestroyPaint(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    return result;
}

CT_Result checkSetPaint( void )
{
    VGPaint paint;
    VGImage image;
    CT_Result result = CT_NO_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    /* if paint is neither a valid paint handle nor equal to VG_INVALID_HANDLE, or is not shared with the current context */
    image = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_BETTER);
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);
    vgSetPaint(image, VG_FILL_PATH|VG_STROKE_PATH);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgDestroyImage(image);

    /* if paint is neither a valid paint handle nor equal to VG_INVALID_HANDLE, or is not shared with the current context */
    vgSetPaint(VG_INVALID_HANDLE, VG_FILL_PATH|VG_STROKE_PATH);
        CT_ERROR_ASSERT(VG_NO_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paintModes is not a valid bitwise OR of values from the VGPaintMode enumeration */
    paint = vgCreatePaint();
        CT_IF_ASSERT(paint, VG_INVALID_HANDLE);
    vgSetPaint(paint, ~(VG_STROKE_PATH|VG_FILL_PATH) );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgDestroyPaint(paint);
    
    return result;
}

CT_Result checkGetPaint( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if paintMode is not a valid value from the VGPaintMode enumeration */
    vgGetPaint(VG_STROKE_PATH-1);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetPaint(VG_FILL_PATH+1);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    return result;
}

CT_Result checkSetColor( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if paint is not a valid paint handle, or is not shared with the current context */
    vgSetColor(VG_INVALID_HANDLE, 0);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
        
    return result;
}

CT_Result checkGetColor( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if paint is not a valid paint handle, or is not shared with the current context */
    vgGetColor(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    return result;
}

CT_Result checkPaintPattern( void )
{
    VGPaint paint;
    VGImage pattern;
    VGPath path;
    CT_Result result = CT_NO_ERROR;

    paint = vgCreatePaint();
        CT_IF_ASSERT(paint, VG_INVALID_HANDLE);
        
    /* VG_BAD_HANDLE_ERROR */
    /* if paint is not a valid paint handle, or is not shared with the current context */
    pattern = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_BETTER);
        CT_IF_ASSERT(pattern, VG_INVALID_HANDLE);
    vgPaintPattern(VG_INVALID_HANDLE, pattern);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgDestroyImage(pattern);

    /* if pattern is neither a valid image handle nor equal to VG_INVALID_HANDLE, or is not shared with the current context */
    path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
        CT_IF_ASSERT(path, VG_INVALID_HANDLE);
    vgPaintPattern(paint, path);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgDestroyPath(path);

    /* if pattern is neither a valid image handle nor equal to VG_INVALID_HANDLE, or is not shared with the current context */    
    vgPaintPattern(paint, VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_NO_ERROR);

    vgDestroyPaint(paint);
    
    return result;
}

CT_Result checkCreateImage( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_UNSUPPORTED_IMAGE_FORMAT_ERROR */
    /* if format is not a valid value from the VGImageFormat enumeration */
    vgCreateImage( -1, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);

   /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height are less than or equal to 0 */
    vgCreateImage( VG_sRGBA_8888,   0,  64, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCreateImage( VG_sRGBA_8888, -64,  64, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCreateImage( VG_sRGBA_8888,  64,   0, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCreateImage( VG_sRGBA_8888,  64, -64, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if width is greater than VG_MAX_IMAGE_WIDTH */
    vgCreateImage( VG_sRGBA_8888, vgGeti(VG_MAX_IMAGE_WIDTH)+1, 64, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if height is greater than VG_MAX_IMAGE_HEIGHT */
    vgCreateImage( VG_sRGBA_8888, 64, vgGeti(VG_MAX_IMAGE_HEIGHT)+1, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* width*height is greater than VG_MAX_IMAGE_PIXELS */
    vgCreateImage( VG_sRGBA_8888, 1, vgGeti(VG_MAX_IMAGE_PIXELS)+1, VG_IMAGE_QUALITY_BETTER );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if width*height*(pixel size of format) is greater than VG_MAX_IMAGE_BYTES */
    if ( vgGeti(VG_MAX_IMAGE_PIXELS) * 4 > vgGeti(VG_MAX_IMAGE_BYTES) )
        return CT_ERROR;
    
    /* if allowedQuality is not a bitwise OR of values from the VGImageQuality enumeration */
    vgCreateImage( VG_sRGBA_8888, 64, 64, ~(VG_IMAGE_QUALITY_NONANTIALIASED | VG_IMAGE_QUALITY_FASTER | VG_IMAGE_QUALITY_BETTER) );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkDestroyImage( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgDestroyImage( VG_INVALID_HANDLE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    return result;
}

CT_Result checkClearImage( void )
{
    VGImage image;
    CT_Result result = CT_NO_ERROR;

    image = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgClearImage( VG_INVALID_HANDLE, 0, 0, 64, 64 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgClearImage( image, 0, 0,   0,  64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgClearImage( image, 0, 0, -64,  64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgClearImage( image, 0, 0,  64,   0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgClearImage( image, 0, 0,  64, -64 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( image );

    return result;
}

CT_Result checkImageSubData( void )
{
    VGImage image;
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

    image = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgImageSubData( VG_INVALID_HANDLE, data, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_UNSUPPORTED_IMAGE_FORMAT_ERROR */
    /* if dataFormat is not a valid value from the VGImageFormat enumeration */
    vgImageSubData( image, data, 8, -1, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgImageSubData( image, data, 8, VG_sRGBA_8888, 0, 0, 0, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, data, 8, VG_sRGBA_8888, 0, 0, 2, 0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is NULL */
    vgImageSubData( image, NULL, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if data is not properly aligned */
    /* (VGfloat*)0x03 is reference address. */
    vgImageSubData( image, (VGint*)0x03, 8, VG_sRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGint*)0x03, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGint*)0x03, 8, VG_sRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGshort*)0x03, 8, VG_sRGB_565, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGshort*)0x03, 8, VG_sRGBA_5551, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGshort*)0x03, 8, VG_sRGBA_4444, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgImageSubData( image, (VGint*)0x03, 8, VG_lRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    vgDestroyImage(image);

    return result;
}

CT_Result checkGetImageSubData( void )
{
    VGImage image;
    VGuint  subData[4];
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

    image = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);
    vgImageSubData( image, data, 8, VG_sRGBA_8888, 0, 0, 2, 2 );

    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgGetImageSubData( VG_INVALID_HANDLE, subData, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_UNSUPPORTED_IMAGE_FORMAT_ERROR */
    /* if dataFormat is not a valid value from the VGImageFormat enumeration */
    vgGetImageSubData( image, subData, 8, -1, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgGetImageSubData( image, subData, 8, VG_sRGBA_8888, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, subData, 8, VG_sRGBA_8888, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, subData, 8, VG_sRGBA_8888, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, subData, 8, VG_sRGBA_8888, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is NULL */
    vgGetImageSubData( image, NULL, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is not properly aligned */
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_sRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_sRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGshort*)0x03, 8, VG_sRGB_565, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGshort*)0x03, 8, VG_sRGBA_5551, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGshort*)0x03, 8, VG_sRGBA_4444, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetImageSubData( image, (VGint*)0x03, 8, VG_lRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    vgDestroyImage( image );

    return result;
}

CT_Result checkChildImage( void )
{
    VGImage image;
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

    image = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);
    vgImageSubData( image, data, 8, VG_sRGBA_8888, 0, 0, 2, 2 );

    /* VG_BAD_HANDLE_ERROR */
    /* if parent is not a valid image handle, or is not shared with the current context */
    vgChildImage( VG_INVALID_HANDLE, 0, 0, 1, 1 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if x is less than 0 or greater than or equal to the parent width */
    vgChildImage( image, -1, 0, 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgChildImage( image,  2, 0, 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if y is less than 0 or greater than or equal to the parent height */
    vgChildImage( image, 0, -1, 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgChildImage( image, 0,  2, 1, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if width or height is less than or equal to 0 */
    vgChildImage( image, 0, 0,  0,  1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgChildImage( image, 0, 0, -1,  1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgChildImage( image, 0, 0,  1,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgChildImage( image, 0, 0,  1, -1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if x + width is greater than the parent width */
    vgChildImage( image, 1, 0, 2, 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if y + height is greater than the parent height */
    vgChildImage( image, 0, 1, 1, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( image );

    return result;
}

CT_Result checkGetParent( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgGetParent( VG_INVALID_HANDLE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    return result;
}

CT_Result checkCopyImage( void )
{
    VGImage dstImage, srcImage;
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

    srcImage = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(srcImage, VG_INVALID_HANDLE);
    dstImage = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dstImage, VG_INVALID_HANDLE);

    vgImageSubData( srcImage, data, 8, VG_sRGBA_8888, 0, 0, 2, 2 );

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgCopyImage( VG_INVALID_HANDLE, 0, 0, srcImage, 0, 0, 2, 2, VG_FALSE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgCopyImage( dstImage, 0, 0, VG_INVALID_HANDLE, 0, 0, 2, 2, VG_FALSE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgCopyImage( dstImage, 0, 0, srcImage, 0, 0,  0,  2, VG_FALSE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyImage( dstImage, 0, 0, srcImage, 0, 0, -2,  2, VG_FALSE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyImage( dstImage, 0, 0, srcImage, 0, 0,  2,  0, VG_FALSE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyImage( dstImage, 0, 0, srcImage, 0, 0,  2, -2, VG_FALSE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( srcImage );
    vgDestroyImage( dstImage );

    return result;
}

CT_Result checkDrawImage( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /* if image is not a valid image handle, or is not shared with the current context */
    vgDrawImage( VG_INVALID_HANDLE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    return result;
}

CT_Result checkSetPixels( void )
{
    VGImage image;
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

    image = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(image, VG_INVALID_HANDLE);
    vgImageSubData( image, data, 8, VG_sRGBA_8888, 0, 0, 2, 2 );

    /* VG_BAD_HANDLE_ERROR */
    /* if src is not a valid image handle, or is not shared with the current context */
    vgSetPixels( 0, 0, VG_INVALID_HANDLE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgSetPixels( 0, 0, image, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetPixels( 0, 0, image, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetPixels( 0, 0, image, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetPixels( 0, 0, image, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( image );

    return result;
}

CT_Result checkWritePixels( void )
{
    CT_Result result = CT_NO_ERROR;
    VGuint data[]    = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    
    /* VG_UNSUPPORTED_IMAGE_FORMAT_ERROR */
    /* if dataFormat is not a valid value from the VGImageFormat enumeration */
    vgWritePixels( data, 8, -1, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgWritePixels( data, 0, VG_sRGBA_8888, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( data, 0, VG_sRGBA_8888, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( data, 0, VG_sRGBA_8888, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( data, 0, VG_sRGBA_8888, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is NULL */
    vgWritePixels( NULL, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is not properly aligned */
    vgWritePixels( (VGint*)0x03, 8, VG_sRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGint*)0x03, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGint*)0x03, 8, VG_sRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGshort*)0x03, 8, VG_sRGB_565, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGshort*)0x03, 8, VG_sRGBA_5551, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGshort*)0x03, 8, VG_sRGBA_4444, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgWritePixels( (VGint*)0x03, 8, VG_lRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkGetPixels( void )
{
    VGImage dstImage;
    CT_Result result = CT_NO_ERROR;

    dstImage = vgCreateImage( VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dstImage, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if dst is not a valid image handle, or is not shared with the current context */
    vgGetPixels( VG_INVALID_HANDLE, 0, 0, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgGetPixels( dstImage, 0, 0, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetPixels( dstImage, 0, 0, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetPixels( dstImage, 0, 0, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGetPixels( dstImage, 0, 0, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( dstImage );

    return result;
}

CT_Result checkReadPixels( void )
{
    VGuint temp[4];
    CT_Result result = CT_NO_ERROR;

    /* VG_UNSUPPORTED_IMAGE_FORMAT_ERROR */
    /* if dataFormat is not a valid value from the VGImageFormat enumeration */
    vgReadPixels( temp, 8, -1, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgReadPixels( temp, 8, VG_sRGBA_8888, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( temp, 8, VG_sRGBA_8888, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( temp, 8, VG_sRGBA_8888, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( temp, 8, VG_sRGBA_8888, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is NULL */
    vgReadPixels( NULL, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if data is not properly aligned */
    vgReadPixels( (VGint*)0x03, 8, VG_sRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGint*)0x03, 8, VG_sRGBA_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGint*)0x03, 8, VG_sRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGshort*)0x03, 8, VG_sRGB_565, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGshort*)0x03, 8, VG_sRGBA_5551, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGshort*)0x03, 8, VG_sRGBA_4444, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGint*)0x03, 8, VG_lRGBX_8888, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgReadPixels( (VGint*)0x03, 8, VG_lRGBA_8888_PRE, 0, 0, 2, 2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    return result;
}

CT_Result checkCopyPixels( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if width or height is less than or equal to 0 */
    vgCopyPixels( 1, 1, 0, 0,  0,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyPixels( 1, 1, 0, 0, -2,  2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyPixels( 1, 1, 0, 0,  2,  0 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgCopyPixels( 1, 1, 0, 0,  2, -2 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    return result;
}

CT_Result checkCreateFont( void )
{
    VGFont font = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if glyphCapacityHint is negative */
    font = vgCreateFont( -1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        CT_IFNOT_ASSERT(font, VG_INVALID_HANDLE);

    if ( font != VG_INVALID_HANDLE )
        vgDestroyFont(font);
    
    return result;
}

CT_Result checkDestroyFont( void )
{
    CT_Result result = CT_NO_ERROR;
    
    /* VG_BAD_HANDLE_ERROR */
    /*  if font is not a valid font handle, or is not shared with the current context */
    vgDestroyFont(VG_INVALID_HANDLE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    return result;
}

CT_Result checkSetGlyphToPath( void )
{
    VGPath path = VG_INVALID_HANDLE;
    VGFont font = VG_INVALID_HANDLE;
    VGfloat glyphOrigin[2] = { 0.0f, 0.0f };
    VGfloat escapement[2] = { 0.0f, 0.0f };
    CT_Result result = CT_NO_ERROR;

    font = vgCreateFont( 1 );
    if ( font == VG_INVALID_HANDLE )
        return CT_ERROR;
    
    path = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
    if ( path == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    /*  if font is not a valid font handle, or is not shared with the current context */
    vgSetGlyphToPath(VG_INVALID_HANDLE, 1, path, VG_TRUE, glyphOrigin, escapement);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* if path is not a valid path handle or VG_INVALID_HANDLE, or is not shared with the current context */
    vgSetGlyphToPath(font, 1, font, VG_TRUE, glyphOrigin, escapement);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if the pointer to glyphOrigin or escapement is NULL or is not properly aligned */
    vgSetGlyphToPath(font, 1, path, VG_TRUE, NULL, escapement);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetGlyphToPath(font, 1, path, VG_TRUE, glyphOrigin, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyFont(font);
    vgDestroyPath(path);
    
    return result;
}

CT_Result checkSetGlyphToImage( void )
{
    VGImage image = VG_INVALID_HANDLE;
    VGFont font = VG_INVALID_HANDLE;
    VGfloat glyphOrigin[2] = { 0.0f, 0.0f };
    VGfloat escapement[2] = { 0.0f, 0.0f };
    CT_Result result = CT_NO_ERROR;

    font = vgCreateFont( 1 );
    if ( font == VG_INVALID_HANDLE )
        return CT_ERROR;

    image = vgCreateImage(VG_sRGBA_8888, 2, 2, VG_IMAGE_QUALITY_NONANTIALIASED);
    if ( image == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    /*  if font is not a valid font handle, or is not shared with the current context */
    vgSetGlyphToImage(VG_INVALID_HANDLE, 1, image, glyphOrigin, escapement);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* if image is not a valid image handle or VG_INVALID_HANDLE, or is not shared with the current context */
    vgSetGlyphToImage(font, 1, font, glyphOrigin, escapement);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if the pointer to glyphOrigin or escapement is NULL or is not properly aligned */
    vgSetGlyphToImage(font, 1, image, NULL, escapement);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSetGlyphToImage(font, 1, image, glyphOrigin, NULL);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyFont(font);
    vgDestroyImage(image);
    
    return result;
}

CT_Result checkClearGlyph( void )
{
    VGFont font = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    font = vgCreateFont( 1 );
    if ( font == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    /* if font is not a valid font handle, or is not shared with the current context */
    vgClearGlyph(VG_INVALID_HANDLE, 1);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if glyphIndex is not defined for the font */
    vgClearGlyph(font, 0);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyFont(font);
    
    return result;
}

CT_Result checkDrawGlyph( void )
{
    VGFont font = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    font = vgCreateFont( 1 );
    if ( font == VG_INVALID_HANDLE )
        return CT_ERROR;

    /* VG_BAD_HANDLE_ERROR */
    /* if font is not a valid font handle, or is not shared with the current context */
    vgDrawGlyph(VG_INVALID_HANDLE, 1, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if glyphIndex has not been defined for a given font object */
    vgDrawGlyph(font, 0, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
        
    /* if paintModes is not a valid bitwise OR of values from the VGPaintMode enumeration, or 0 */
    vgDrawGlyph(font, 1, ~(VG_STROKE_PATH|VG_FILL_PATH), VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyFont(font);
    
    return result; 
}

CT_Result checkDrawGlyphs( void )
{
    VGPath path[2];
    VGFont font = VG_INVALID_HANDLE;
    CT_Result result = CT_NO_ERROR;

    VGint i;
    VGfloat glyphOrigin[2] = { 0.0f, 0.0f };
    VGfloat escapement[2] = { 10.0f, 0.0f };

    VGuint glyphIndices[2] = { 1, 2 };
    VGfloat adjustments_x = 0.0f;
    VGfloat adjustments_y = 0.0f;
    
    font = vgCreateFont( 1 );
    if ( font == VG_INVALID_HANDLE )
        return CT_ERROR;

    for ( i = 0; i < 2; i++ ) {
        path[i] = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL );
        if ( path == VG_INVALID_HANDLE )
            return CT_ERROR;

        vgSetGlyphToPath(font, i + 1, path[i], VG_FALSE, glyphOrigin, escapement);
    }

    /* VG_BAD_HANDLE_ERROR */
    /* if font is not a valid font handle, or is not shared with the current context */
    vgDrawGlyphs(VG_INVALID_HANDLE, 2, glyphIndices, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if glyphCount is zero or a negative value */
    vgDrawGlyphs(font, 0, glyphIndices, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);    
    vgDrawGlyphs(font, -1, glyphIndices, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);  
        
    /* if the pointer to the glyphIndices array is NULL or is not properly aligned */
    vgDrawGlyphs(font, 2, NULL, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);  
    vgDrawGlyphs(font, 2, (VGuint*)0x03, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);          

    /* if a pointer to either of the adjustments_x or adjustments_y arrays are non-NULL and are not properly aligned */
    vgDrawGlyphs(font, 2, glyphIndices, (VGfloat*)0x03, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);   
    vgDrawGlyphs(font, 2, glyphIndices, &adjustments_x, (VGfloat*)0x03, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);   
        
    /* if any of the glyphIndices has not been defined in a given font object */
    glyphIndices[0] = 3;
    glyphIndices[1] = 4;
    vgDrawGlyphs(font, 2, glyphIndices, &adjustments_x, &adjustments_y, VG_STROKE_PATH|VG_FILL_PATH, VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);   
            
    /* if paintModes is not a valid bitwise OR of values from the VGPaintMode enumeration, or 0 */
    glyphIndices[0] = 1;
    glyphIndices[1] = 2;    
    vgDrawGlyphs(font, 2, glyphIndices, &adjustments_x, &adjustments_y, ~(VG_STROKE_PATH|VG_FILL_PATH), VG_FALSE);
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);   
        
    for ( i = 0; i < 2; i++ ) {
        vgDestroyPath(path[i]);
    }
    vgDestroyFont(font);
    
    return result; 
}

CT_Result checkColorMatrix( void )
{
    VGImage dst, src, child;
    VGfloat matrix[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    CT_Result result = CT_NO_ERROR;
    
    src = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(child, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgColorMatrix( VG_INVALID_HANDLE, src, matrix );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgColorMatrix( dst, VG_INVALID_HANDLE, matrix );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgColorMatrix( src, src, matrix );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgColorMatrix( src, child, matrix );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if matrix is NULL */
    vgColorMatrix( dst, src, NULL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if matrix is not properly aligned */
    vgColorMatrix( dst, src, (VGfloat*)0x03 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );
    
    return result;
}

CT_Result checkConvolve( void )
{
    VGImage dst, src, child;
    const VGshort kernel[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    CT_Result result = CT_NO_ERROR;

    src = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);    

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgConvolve( VG_INVALID_HANDLE, src, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgConvolve( dst, VG_INVALID_HANDLE, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgConvolve( src, src, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( src, child, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelWidth or kernelHeight is less than or equal to 0 */
    vgConvolve( dst, src,  0,  3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( dst, src, -3,  3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( dst, src,  3,  0, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( dst, src,  3, -3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelWidth or kernelHeight is greater than VG_MAX_KERNEL_SIZE */
    vgConvolve( dst, src, vgGeti(VG_MAX_KERNEL_SIZE)+1, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( dst, src, 3, vgGeti(VG_MAX_KERNEL_SIZE)+1, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernel is NULL */
    vgConvolve( dst, src, 3, 3, 0, 0, NULL, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernel is not properly aligned */
    vgConvolve( dst, src, 3, 3, 0, 0, (VGshort*)0x03, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    
    /* if tilingMode is not one of the values from the VGTilingMode enumeration */
    vgConvolve( dst, src, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_FILL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgConvolve( dst, src, 3, 3, 0, 0, kernel, 1.0f, 0.0f, VG_TILE_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );

    return result;
}

CT_Result checkSeparableConvolve( void )
{
    VGImage dst, src, child;
    const VGshort kernelX[] = { 0, 0, 0 };
    const VGshort kernelY[] = { 0, 0, 0 };

    CT_Result result = CT_NO_ERROR;

    src = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(child, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgSeparableConvolve( VG_INVALID_HANDLE, src, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgSeparableConvolve( dst, VG_INVALID_HANDLE, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgSeparableConvolve( src, src, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( src, child, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelWidth or kernelHeight is less than or equal to 0 */
    vgSeparableConvolve( dst, src,  0,  3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src, -3,  3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src,  3,  0, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src,  3, -3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelWidth or kernelHeight is greater than VG_MAX_KERNEL_SIZE */
    vgSeparableConvolve( dst, src, vgGeti(VG_MAX_SEPARABLE_KERNEL_SIZE)+1, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src, 3, vgGeti(VG_MAX_SEPARABLE_KERNEL_SIZE)+1, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelX or kernelY is NULL */
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, NULL, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, kernelX, NULL, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if kernelX or kernelY is not properly aligned */
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, (VGshort*)0x03, kernelY, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, kernelX, (VGshort*)0x03, 1.0f, 0.0f, VG_TILE_PAD );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if tilingMode is not one of the values from the VGTilingMode enumeration */
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_FILL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgSeparableConvolve( dst, src, 3, 3, 0, 0, kernelX, kernelY, 1.0f, 0.0f, VG_TILE_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );

    return result;
}

CT_Result checkGaussianBlur( void )
{
    VGImage dst, src, child;
    CT_Result result = CT_NO_ERROR;

    src = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_lRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(child, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgGaussianBlur( VG_INVALID_HANDLE, src, 1.0f, 1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgGaussianBlur( dst, VG_INVALID_HANDLE, 1.0f, 1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgGaussianBlur( src, src, 1.0f, 1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGaussianBlur( src, child, 1.0f, 1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if stdDeviationX or stdDeviationY is less than or equal to 0 */
    vgGaussianBlur( dst, src,  0.0f,  1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGaussianBlur( dst, src, -1.0f,  1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGaussianBlur( dst, src,  1.0f,  0.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGaussianBlur( dst, src,  1.0f, -1.0f, VG_TILE_FILL );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if tilingMode is not one of the values from the VGTilingMode enumeration */
    vgGaussianBlur( dst, src, 1.0f, 1.0f, VG_TILE_FILL - 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgGaussianBlur( dst, src, 1.0f, 1.0f, VG_TILE_REFLECT + 1 );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );

    return result;
}

CT_Result checkLookup( void )
{
    VGImage dst, src, child;
    const VGubyte redLUT[256] = { 0, };
    const VGubyte greenLUT[256] = { 0, };
    const VGubyte blueLUT[256] = { 0, };
    const VGubyte alphaLUT[256] = { 0, };
    
    CT_Result result = CT_NO_ERROR;

    src = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(child, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgLookup( VG_INVALID_HANDLE, src, redLUT, greenLUT, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgLookup( dst, VG_INVALID_HANDLE, redLUT, greenLUT, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);

    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgLookup( src, src, redLUT, greenLUT, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookup( src, child, redLUT, greenLUT, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if any pointer parameter is NULL */
    vgLookup( dst, src, NULL, greenLUT, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookup( dst, src, redLUT, NULL, blueLUT, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookup( dst, src, redLUT, greenLUT, NULL, alphaLUT, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookup( dst, src, redLUT, greenLUT, blueLUT, NULL, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );

    return result;
}

CT_Result checkLookupSingle( void )
{
    VGImage dst, src, child;
    const VGuint lookupTable[256] = { 0x000000,  };
    CT_Result result = CT_NO_ERROR;

    src = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(src, VG_INVALID_HANDLE);
    dst = vgCreateImage( VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_BETTER );
        CT_IF_ASSERT(dst, VG_INVALID_HANDLE);
    child = vgChildImage(src, 0, 0, 32, 32);
        CT_IF_ASSERT(child, VG_INVALID_HANDLE);

    /* VG_BAD_HANDLE_ERROR */
    /* if either dst or src is not a valid image handle, or is not shared with the current context */
    vgLookupSingle( VG_INVALID_HANDLE, src, lookupTable, VG_RED, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    vgLookupSingle( dst, VG_INVALID_HANDLE, lookupTable, VG_RED, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_BAD_HANDLE_ERROR);
    
    /* VG_ILLEGAL_ARGUMENT_ERROR */
    /* if src and dst overlap */
    vgLookupSingle( src, src, lookupTable, VG_RED , VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookupSingle( src, child, lookupTable, VG_RED , VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if src is in an RGB pixel format and sourceChannel is not one of VG_RED, VG_GREEN, VG_BLUE or VG_ALPHA from the VGImageChannel */
    vgLookupSingle( dst, src, lookupTable, VG_ALPHA-1, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);
    vgLookupSingle( dst, src, lookupTable, VG_RED+1, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if lookupTable is NULL */
    vgLookupSingle( dst, src, NULL, VG_RED, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    /* if lookupTable is not properly aligned */
    vgLookupSingle( dst, src, (VGuint*)0x03, VG_RED, VG_TRUE, VG_TRUE );
        CT_ERROR_ASSERT(VG_ILLEGAL_ARGUMENT_ERROR);

    vgDestroyImage( child );
    vgDestroyImage( src );
    vgDestroyImage( dst );

    return result;
}

CT_Result A10102_ParameterCoverage_by_HUONE(CT_File *AnsFile)
{
    VGint i;
    VGfloat error = 0.0f;

    /* OpenVG API Error Check */
    for ( i = 0; STRCMP( funcVgList[i].name, "End of List" ) != 0; i++ ) {
        if ( vgGetError() != VG_NO_ERROR )
            return CT_ERROR; 
        if (funcVgList[i].func() == CT_ERROR) {
            error++;
        }
    }

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
