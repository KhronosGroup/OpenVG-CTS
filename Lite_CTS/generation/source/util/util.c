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
#include "util.h"

void Output(CT_AppRec *pMe, VGint level, const VGbyte *format, ...)
{
    VA_LIST args;

    VA_START(args, format);
    if (pMe->verboseLevel >= level) {
        VPRINTF(format, args);
        FFLUSH(stdout);
    }
    VA_END(args);
}

void GetAnswerDir(CT_AppRec *pMe, VGbyte *str)
{
    static const VGbyte surface[4][15] = { "sRGB_NONPRE","lRGB_NONPRE","sRGB_PRE", "lRGB_PRE" };

    SPRINTF (str, "%s/%d", ANSWER_DEFAULT_DIR, pMe->info.configID);

    MKDIR(str);

    if ( pMe->info.alphaMult == 0 )
        SPRINTF (str, "%s/%s", str, surface[pMe->info.cSpace]);   
    else
        SPRINTF (str, "%s/%s", str, surface[pMe->info.cSpace + 2]);    
    MKDIR(str);
}

void GetAnswerFilename(CT_AppRec *pMe, VGbyte *str, VGint subtest )
{
    VGbyte subname[6] = { 0, };

    GetAnswerDir(pMe, str);
    STRCAT(str, "/" );
    STRCAT(str, pMe->curDriver->code);

    if ( subtest >= 0 ) {
        SPRINTF(subname,  "_%04d",  subtest);
        STRCAT(str, subname);            
    }

    STRCAT(str, "_Ans"); 
}

CT_Result StateReset(CT_AppRec *pMe)
{
    VGfloat fillColor[4] = { ITOF(0), ITOF(0), ITOF(0), ITOF(0) };
    VGfloat colorTransform[8] = { ITOF(1), ITOF(1), ITOF(1), ITOF(1), ITOF(0), ITOF(0), ITOF(0), ITOF(0) };
    VGfloat glyphOrigin[2] = { ITOF(0), ITOF(0) };

    if ( vgGetError() != VG_NO_ERROR )
        return CT_ERROR;

    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE ) ;
    vgLoadIdentity() ;
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE ) ;
    vgLoadIdentity() ;
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER ) ;
    vgLoadIdentity() ;
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER ) ;
    vgLoadIdentity() ;
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE ) ;
    vgLoadIdentity() ;
    
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
    vgSeti( VG_FILL_RULE, VG_EVEN_ODD );
    vgSeti( VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_FASTER );
    vgSeti( VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER );
    vgSeti( VG_BLEND_MODE, VG_BLEND_SRC_OVER );
    vgSeti( VG_IMAGE_MODE, VG_DRAW_IMAGE_NORMAL );
    vgSetiv( VG_SCISSOR_RECTS, 0, NULL );
    vgSeti( VG_COLOR_TRANSFORM, VG_FALSE );
    vgSetfv( VG_COLOR_TRANSFORM_VALUES, 8, colorTransform );
    vgSetf( VG_STROKE_LINE_WIDTH, ITOF(1) );
    vgSeti( VG_STROKE_CAP_STYLE, VG_CAP_BUTT );
    vgSeti( VG_STROKE_JOIN_STYLE, VG_JOIN_MITER );
    vgSetf( VG_STROKE_MITER_LIMIT, ITOF(4) );
    vgSetfv( VG_STROKE_DASH_PATTERN, 0, NULL );
    vgSetf( VG_STROKE_DASH_PHASE, ITOF(0) );
    vgSetf( VG_STROKE_DASH_PHASE_RESET, VG_FALSE );    
    vgSetfv( VG_TILE_FILL_COLOR, 4, fillColor );
    vgSetfv( VG_CLEAR_COLOR, 4, fillColor );
    vgSetfv( VG_GLYPH_ORIGIN, 2, glyphOrigin );
    vgSeti( VG_MASKING, VG_FALSE );
    vgSeti( VG_SCISSORING, VG_FALSE );
    vgSeti( VG_PIXEL_LAYOUT, VG_PIXEL_LAYOUT_UNKNOWN );
#if 0    
    vgSeti( VG_SCREEN_LAYOUT, VG_PIXEL_LAYOUT_UNKNOWN ); /* default value is undefined */
#endif    
    vgSeti( VG_FILTER_FORMAT_LINEAR, VG_FALSE );
    vgSeti( VG_FILTER_FORMAT_PREMULTIPLIED, VG_FALSE );
    vgSeti( VG_FILTER_CHANNEL_MASK, (VG_RED|VG_GREEN|VG_BLUE|VG_ALPHA) );

    vgSetPaint(VG_INVALID_HANDLE, VG_FILL_PATH);
    vgSetPaint(VG_INVALID_HANDLE, VG_STROKE_PATH);

    if ( vgGetError() == VG_NO_ERROR )
        return CT_NO_ERROR;
    else
        return CT_ERROR;
}

CT_Result StateCheck(CT_AppRec *pMe)
{
    VGint    i;
    VGfloat  color[4];
    VGfloat  colorTransform[8];
    VGfloat  glyphOrigin[2];
    VGfloat  matrix[9];
    CT_Result result = CT_NO_ERROR;

    if ( vgGetError() != VG_NO_ERROR )
        return CT_ERROR;

    for ( i = VG_MATRIX_GLYPH_USER_TO_SURFACE; i >= VG_MATRIX_PATH_USER_TO_SURFACE; i-- ) {   
        vgSeti( VG_MATRIX_MODE, i );
        vgGetMatrix( matrix );

        if ( matrix[0] != ITOF(1) || matrix[1] != ITOF(0) || matrix[2] != ITOF(0) || 
             matrix[3] != ITOF(0) || matrix[4] != ITOF(1) || matrix[5] != ITOF(0) || 
             matrix[6] != ITOF(0) || matrix[7] != ITOF(0) || matrix[8] != ITOF(1) ) {           
            Output(pMe, 2, "    Error : All Matrix must be initialized to the Identity matrix.\n");
            result = CT_ERROR;
            break;
        }
    }
    
    if ( vgGeti(VG_MATRIX_MODE) != VG_MATRIX_PATH_USER_TO_SURFACE ) {
        Output(pMe, 2, "    Error : VG_MATRIX_MODE must be initialized to VG_MATRIX_PATH_USER_TO_SURFACE.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_FILL_RULE) != VG_EVEN_ODD ) {
        Output(pMe, 2, "    Error : VG_FILL_RULE must be initialized to VG_EVEN_ODD.\n");
        result = CT_ERROR;
    }
    
    if ( vgGeti(VG_IMAGE_QUALITY) != VG_IMAGE_QUALITY_FASTER ) {
        Output(pMe, 2, "    Error : VG_IMAGE_QUALITY must be initialized to VG_IMAGE_QUALITY_FASTER.\n");
        result = CT_ERROR;
    }
    
    if ( vgGeti(VG_RENDERING_QUALITY) != VG_RENDERING_QUALITY_BETTER ) {
        Output(pMe, 2, "    Error : VG_RENDERING_QUALITY must be initialized to VG_RENDERING_QUALITY_BETTER.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_BLEND_MODE) != VG_BLEND_SRC_OVER ) {
        Output(pMe, 2, "    Error : VG_BLEND_MODE must be initialized to VG_BLEND_SRC_OVER.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_IMAGE_MODE) != VG_DRAW_IMAGE_NORMAL ) {
        Output(pMe, 2, "    Error : VG_IMAGE_MODE must be initialized to VG_DRAW_IMAGE_NORMAL.\n");
        result = CT_ERROR;
    }

    if ( vgGetVectorSize(VG_SCISSOR_RECTS) != 0 ) {
        Output(pMe, 2, "    Error : VG_SCISSOR_RECTS must be initialized to NULL.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_COLOR_TRANSFORM) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_COLOR_TRANSFORM must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    vgGetfv( VG_COLOR_TRANSFORM_VALUES, 8, colorTransform );
    if ( colorTransform[0] != ITOF(1) || colorTransform[1] != ITOF(1) ||
         colorTransform[2] != ITOF(1) || colorTransform[3] != ITOF(1) ||
         colorTransform[4] != ITOF(0) || colorTransform[5] != ITOF(0) ||
         colorTransform[6] != ITOF(0) || colorTransform[7] != ITOF(0) ) {
        Output(pMe, 2, "    Error : VG_COLOR_TRANSFORM_VALUES must be initialized to (1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f).\n");
        result = CT_ERROR;
    }
    
    if ( vgGetf(VG_STROKE_LINE_WIDTH) != ITOF(1) ) {
        Output(pMe, 2, "    Error : VG_STROKE_LINE_WIDTH must be initialized to 1.0f.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_STROKE_CAP_STYLE) != VG_CAP_BUTT ) {
        Output(pMe, 2, "    Error : VG_STROKE_CAP_STYLE must be initialized to VG_CAP_BUTT.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_STROKE_JOIN_STYLE) != VG_JOIN_MITER ) {
        Output(pMe, 2, "    Error : VG_STROKE_JOIN_STYLE must be initialized to VG_JOIN_MITER.\n");
        result = CT_ERROR;
    }

    if ( vgGetf(VG_STROKE_MITER_LIMIT) != ITOF(4) ) {
        Output(pMe, 2, "    Error : VG_STROKE_MITER_LIMIT must be initialized to 4.0f.\n");
        result = CT_ERROR;
    }

    if ( vgGetVectorSize(VG_STROKE_DASH_PATTERN) != 0 ) {
        Output(pMe, 2, "    Error : VG_STROKE_DASH_PATTERN must be initialized to NULL.\n");
        result = CT_ERROR;
    }

    if ( vgGetf(VG_STROKE_DASH_PHASE) != ITOF(0) ) {
        Output(pMe, 2, "    Error : VG_STROKE_DASH_PHASE must be initialized to 0.0f.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_STROKE_DASH_PHASE_RESET) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_STROKE_DASH_PHASE_RESET must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    vgGetfv( VG_TILE_FILL_COLOR, 4, color );
    if ( color[0] != ITOF(0) || color[1] != ITOF(0) || color[2] != ITOF(0) || color[3] != ITOF(0) ) {
        Output(pMe, 2, "    Error : VG_TILE_FILL_COLOR must be initialized to (0.0f, 0.0f, 0.0f, 0.0f).\n");
        result = CT_ERROR;
    }

    vgGetfv( VG_CLEAR_COLOR, 4, color );
    if ( color[0] != ITOF(0) || color[1] != ITOF(0) || color[2] != ITOF(0) || color[3] != ITOF(0) ) {
        Output(pMe, 2, "    Error : VG_CLEAR_COLOR must be initialized to (0.0f, 0.0f, 0.0f, 0.0f).\n");
        result = CT_ERROR;
    }

    vgGetfv( VG_GLYPH_ORIGIN, 2, glyphOrigin );
    if ( glyphOrigin[0] != ITOF(0) || glyphOrigin[1] != ITOF(0) ) {
        Output(pMe, 2, "    Error : VG_GLYPH_ORIGIN must be initialized to (0.0f, 0.0f).\n");
        result = CT_ERROR;
    }
    
    if ( vgGeti(VG_MASKING) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_MASKING must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_SCISSORING) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_SCISSORING must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_PIXEL_LAYOUT) != VG_PIXEL_LAYOUT_UNKNOWN ) {
        Output(pMe, 2, "    Error : VG_PIXEL_LAYOUT must be initialized to VG_PIXEL_LAYOUT_UNKNOWN.\n");
        result = CT_ERROR;
    }
#if 0    
    if ( vgGeti(VG_SCREEN_LAYOUT) != VG_PIXEL_LAYOUT_UNKNOWN ) {
        Output(pMe, 2, "    Error : VG_SCREEN_LAYOUT must be initialized to VG_PIXEL_LAYOUT_UNKNOWN.\n");
        result = CT_ERROR;
    }    
#endif
    if ( vgGeti(VG_FILTER_FORMAT_LINEAR) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_FILTER_FORMAT_LINEAR must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_FILTER_FORMAT_PREMULTIPLIED) != VG_FALSE ) {
        Output(pMe, 2, "    Error : VG_FILTER_FORMAT_PREMULTIPLIED must be initialized to VG_FALSE.\n");
        result = CT_ERROR;
    }

    if ( vgGeti(VG_FILTER_CHANNEL_MASK) != (VG_RED|VG_GREEN|VG_BLUE|VG_ALPHA) ) {
        Output(pMe, 2, "    Error : VG_FILTER_CHANNEL_MASK must be initialized to (VG_RED|VG_GREEN|VG_BLUE|VG_ALPHA).\n");
        result = CT_ERROR;
    }

    if ( vgGetError() != VG_NO_ERROR )
        result = CT_ERROR;

    return result;    
}

void MakeExtension( VGbyte *extension, CT_FileType fileType )
{
    if ( fileType == FILE_DAT_TYPE )
        STRCPY( extension, ".dat" );
    else if ( fileType == FILE_TGA_TYPE )
        STRCPY( extension, ".tga" );

    return;
}

CT_Result ConformFile(const CT_File *file)
{
    CT_Result  result = CT_NO_ERROR;    

    FILEHANDLE datFile = NULL;
    FILEHANDLE tgaFile = NULL;    

    VGbyte     datName[CT_MAX_FILE_NAME] = {0,};
    VGbyte     tgaName[CT_MAX_FILE_NAME] = {0,};

    if ( file->type == FILE_INVALID_TYPE )
        return CT_ERROR;

    SPRINTF(datName, "%s.dat", file->filename );
    SPRINTF(tgaName, "%s.tga", file->filename );

    datFile = FOPEN(datName, "rt");
    tgaFile = FOPEN(tgaName, "rb");

    if ( file->type == FILE_DAT_TYPE && !datFile )  
        result = CT_ERROR;
    else if ( file->type == FILE_TGA_TYPE && !tgaFile )
        result = CT_ERROR;

    if ( datFile )
        FCLOSE(datFile);
    if ( tgaFile )
        FCLOSE(tgaFile);    

    return result;
}
