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

#define CT_ENUM(name, value)    { #name, name, value }

typedef struct _CT_EnumCheckRec {
    VGbyte *name;
    VGint value;
    VGint true_;
} CT_EnumCheckRec;

const CT_EnumCheckRec vgEnumList[] = {
    /* Errors */
    CT_ENUM(VG_NO_ERROR                         , 0x0000),
    CT_ENUM(VG_BAD_HANDLE_ERROR                 , 0x1000),
    CT_ENUM(VG_ILLEGAL_ARGUMENT_ERROR           , 0x1001),
    CT_ENUM(VG_OUT_OF_MEMORY_ERROR              , 0x1002),
    CT_ENUM(VG_PATH_CAPABILITY_ERROR            , 0x1003),
    CT_ENUM(VG_UNSUPPORTED_IMAGE_FORMAT_ERROR   , 0x1004),
    CT_ENUM(VG_UNSUPPORTED_PATH_FORMAT_ERROR    , 0x1005),
    CT_ENUM(VG_IMAGE_IN_USE_ERROR               , 0x1006),
    CT_ENUM(VG_NO_CONTEXT_ERROR                 , 0x1007),

    /* Mode settings */
    CT_ENUM(VG_MATRIX_MODE                      , 0x1100),
    CT_ENUM(VG_FILL_RULE                        , 0x1101),
    CT_ENUM(VG_IMAGE_QUALITY                    , 0x1102),
    CT_ENUM(VG_RENDERING_QUALITY                , 0x1103),
    CT_ENUM(VG_BLEND_MODE                       , 0x1104),
    CT_ENUM(VG_IMAGE_MODE                       , 0x1105),

    /* Scissoring rectangles */
    CT_ENUM(VG_SCISSOR_RECTS                    , 0x1106),

    /* Color Transformation */
    CT_ENUM(VG_COLOR_TRANSFORM                 ,0x1170),
    CT_ENUM(VG_COLOR_TRANSFORM_VALUES    ,0x1171),
    
    /* Stroke parameters */
    CT_ENUM(VG_STROKE_LINE_WIDTH                , 0x1110),
    CT_ENUM(VG_STROKE_CAP_STYLE                 , 0x1111),
    CT_ENUM(VG_STROKE_JOIN_STYLE                , 0x1112),
    CT_ENUM(VG_STROKE_MITER_LIMIT               , 0x1113),
    CT_ENUM(VG_STROKE_DASH_PATTERN              , 0x1114),
    CT_ENUM(VG_STROKE_DASH_PHASE                , 0x1115),
    CT_ENUM(VG_STROKE_DASH_PHASE_RESET          , 0x1116),
    
    /* Edge fill color for VG_TILE_FILL tiling mode */
    CT_ENUM(VG_TILE_FILL_COLOR                  , 0x1120),

    /* Color for vgClear */
    CT_ENUM(VG_CLEAR_COLOR                      , 0x1121),\

	/*glyph origin*/
	CT_ENUM(VG_GLYPH_ORIGIN						, 0x1122),
    
	/* Enable/disable alpha masking and scissoring */
    CT_ENUM(VG_MASKING                          , 0x1130),
    CT_ENUM(VG_SCISSORING                       , 0x1131),

    /* Pixel layout information */
    CT_ENUM(VG_PIXEL_LAYOUT                     , 0x1140),
    CT_ENUM(VG_SCREEN_LAYOUT                    , 0x1141),

    /* Source format selection for image filters */
    CT_ENUM(VG_FILTER_FORMAT_LINEAR             , 0x1150),
    CT_ENUM(VG_FILTER_FORMAT_PREMULTIPLIED      , 0x1151),

    /* Destination write enable mask for image filters */
    CT_ENUM(VG_FILTER_CHANNEL_MASK              , 0x1152),

    /* Implementation limits (read-only) */
	CT_ENUM(VG_MAX_SCISSOR_RECTS				, 0x1160),
    CT_ENUM(VG_MAX_DASH_COUNT                   , 0x1161),
    CT_ENUM(VG_MAX_KERNEL_SIZE                  , 0x1162),
    CT_ENUM(VG_MAX_SEPARABLE_KERNEL_SIZE        , 0x1163),
    CT_ENUM(VG_MAX_COLOR_RAMP_STOPS             , 0x1164),
    CT_ENUM(VG_MAX_IMAGE_WIDTH                  , 0x1165),
    CT_ENUM(VG_MAX_IMAGE_HEIGHT                 , 0x1166),
    CT_ENUM(VG_MAX_IMAGE_PIXELS                 , 0x1167),
    CT_ENUM(VG_MAX_IMAGE_BYTES                  , 0x1168),
    CT_ENUM(VG_MAX_FLOAT                        , 0x1169),
    CT_ENUM(VG_MAX_GAUSSIAN_STD_DEVIATION       , 0x116A),

    /* VGRenderingQuality */
    CT_ENUM(VG_RENDERING_QUALITY_NONANTIALIASED , 0x1200),
    CT_ENUM(VG_RENDERING_QUALITY_FASTER         , 0x1201),
    CT_ENUM(VG_RENDERING_QUALITY_BETTER         , 0x1202),

    /* VGPixelLayout */
    CT_ENUM(VG_PIXEL_LAYOUT_UNKNOWN             , 0x1300),
    CT_ENUM(VG_PIXEL_LAYOUT_RGB_VERTICAL        , 0x1301),
    CT_ENUM(VG_PIXEL_LAYOUT_BGR_VERTICAL        , 0x1302),
    CT_ENUM(VG_PIXEL_LAYOUT_RGB_HORIZONTAL      , 0x1303),
    CT_ENUM(VG_PIXEL_LAYOUT_BGR_HORIZONTAL      , 0x1304),

    /* VGMatrixMode */
    CT_ENUM(VG_MATRIX_PATH_USER_TO_SURFACE      , 0x1400),
    CT_ENUM(VG_MATRIX_IMAGE_USER_TO_SURFACE     , 0x1401),
    CT_ENUM(VG_MATRIX_FILL_PAINT_TO_USER        , 0x1402),
    CT_ENUM(VG_MATRIX_STROKE_PAINT_TO_USER      , 0x1403),
    CT_ENUM(VG_MATRIX_GLYPH_USER_TO_SURFACE    , 0x1404),

    /* VGMaskOperation */
    CT_ENUM(VG_CLEAR_MASK                       , 0x1500),
    CT_ENUM(VG_FILL_MASK                        , 0x1501),
    CT_ENUM(VG_SET_MASK                         , 0x1502),
    CT_ENUM(VG_UNION_MASK                       , 0x1503),
    CT_ENUM(VG_INTERSECT_MASK                   , 0x1504),
    CT_ENUM(VG_SUBTRACT_MASK                    , 0x1505),

    /* PathDatatype */
    CT_ENUM(VG_PATH_DATATYPE_S_8                ,  0),
    CT_ENUM(VG_PATH_DATATYPE_S_16               ,  1),
    CT_ENUM(VG_PATH_DATATYPE_S_32               ,  2),
    CT_ENUM(VG_PATH_DATATYPE_F                  ,  3),

    /* PathAbsRel */
    CT_ENUM(VG_ABSOLUTE                         ,  0),
    CT_ENUM(VG_RELATIVE                         ,  1),

    /* VGPathSegment */
    CT_ENUM(VG_CLOSE_PATH                       , ( 0 << 1)),
    CT_ENUM(VG_MOVE_TO                          , ( 1 << 1)),
    CT_ENUM(VG_LINE_TO                          , ( 2 << 1)),
    CT_ENUM(VG_HLINE_TO                         , ( 3 << 1)),
    CT_ENUM(VG_VLINE_TO                         , ( 4 << 1)),
    CT_ENUM(VG_QUAD_TO                          , ( 5 << 1)),
    CT_ENUM(VG_CUBIC_TO                         , ( 6 << 1)),
    CT_ENUM(VG_SQUAD_TO                         , ( 7 << 1)),
    CT_ENUM(VG_SCUBIC_TO                        , ( 8 << 1)),
    CT_ENUM(VG_SCCWARC_TO                       , ( 9 << 1)),
    CT_ENUM(VG_SCWARC_TO                        , (10 << 1)),
    CT_ENUM(VG_LCCWARC_TO                       , (11 << 1)),
    CT_ENUM(VG_LCWARC_TO                        , (12 << 1)),

    /* VGPathCommand */
    CT_ENUM(VG_MOVE_TO_ABS                      , (VG_MOVE_TO    | VG_ABSOLUTE)),
    CT_ENUM(VG_MOVE_TO_REL                      , (VG_MOVE_TO    | VG_RELATIVE)),
    CT_ENUM(VG_LINE_TO_ABS                      , (VG_LINE_TO    | VG_ABSOLUTE)),
    CT_ENUM(VG_LINE_TO_REL                      , (VG_LINE_TO    | VG_RELATIVE)),
    CT_ENUM(VG_HLINE_TO_ABS                     , (VG_HLINE_TO   | VG_ABSOLUTE)),
    CT_ENUM(VG_HLINE_TO_REL                     , (VG_HLINE_TO   | VG_RELATIVE)),
    CT_ENUM(VG_VLINE_TO_ABS                     , (VG_VLINE_TO   | VG_ABSOLUTE)),
    CT_ENUM(VG_VLINE_TO_REL                     , (VG_VLINE_TO   | VG_RELATIVE)),
    CT_ENUM(VG_QUAD_TO_ABS                      , (VG_QUAD_TO    | VG_ABSOLUTE)),
    CT_ENUM(VG_QUAD_TO_REL                      , (VG_QUAD_TO    | VG_RELATIVE)),
    CT_ENUM(VG_CUBIC_TO_ABS                     , (VG_CUBIC_TO   | VG_ABSOLUTE)),
    CT_ENUM(VG_CUBIC_TO_REL                     , (VG_CUBIC_TO   | VG_RELATIVE)),
    CT_ENUM(VG_SQUAD_TO_ABS                     , (VG_SQUAD_TO   | VG_ABSOLUTE)),
    CT_ENUM(VG_SQUAD_TO_REL                     , (VG_SQUAD_TO   | VG_RELATIVE)),
    CT_ENUM(VG_SCUBIC_TO_ABS                    , (VG_SCUBIC_TO  | VG_ABSOLUTE)),
    CT_ENUM(VG_SCUBIC_TO_REL                    , (VG_SCUBIC_TO  | VG_RELATIVE)),
    CT_ENUM(VG_SCCWARC_TO_ABS                   , (VG_SCCWARC_TO | VG_ABSOLUTE)),
    CT_ENUM(VG_SCCWARC_TO_REL                   , (VG_SCCWARC_TO | VG_RELATIVE)),
    CT_ENUM(VG_SCWARC_TO_ABS                    , (VG_SCWARC_TO  | VG_ABSOLUTE)),
    CT_ENUM(VG_SCWARC_TO_REL                    , (VG_SCWARC_TO  | VG_RELATIVE)),
    CT_ENUM(VG_LCCWARC_TO_ABS                   , (VG_LCCWARC_TO | VG_ABSOLUTE)),
    CT_ENUM(VG_LCCWARC_TO_REL                   , (VG_LCCWARC_TO | VG_RELATIVE)),
    CT_ENUM(VG_LCWARC_TO_ABS                    , (VG_LCWARC_TO  | VG_ABSOLUTE)),
    CT_ENUM(VG_LCWARC_TO_REL                    , (VG_LCWARC_TO  | VG_RELATIVE)),

    /* PathCapabilities */
    CT_ENUM(VG_PATH_CAPABILITY_APPEND_FROM              , (1 <<  0)),
    CT_ENUM(VG_PATH_CAPABILITY_APPEND_TO                , (1 <<  1)),
    CT_ENUM(VG_PATH_CAPABILITY_MODIFY                   , (1 <<  2)),
    CT_ENUM(VG_PATH_CAPABILITY_TRANSFORM_FROM           , (1 <<  3)),
    CT_ENUM(VG_PATH_CAPABILITY_TRANSFORM_TO             , (1 <<  4)),
    CT_ENUM(VG_PATH_CAPABILITY_INTERPOLATE_FROM         , (1 <<  5)),
    CT_ENUM(VG_PATH_CAPABILITY_INTERPOLATE_TO           , (1 <<  6)),
    CT_ENUM(VG_PATH_CAPABILITY_PATH_LENGTH              , (1 <<  7)),
    CT_ENUM(VG_PATH_CAPABILITY_POINT_ALONG_PATH         , (1 <<  8)),
    CT_ENUM(VG_PATH_CAPABILITY_TANGENT_ALONG_PATH       , (1 <<  9)),
    CT_ENUM(VG_PATH_CAPABILITY_PATH_BOUNDS              , (1 << 10)),
    CT_ENUM(VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS  , (1 << 11)),
    CT_ENUM(VG_PATH_CAPABILITY_ALL                      , (1 << 12) - 1),

    /* VGPathParamType */
    CT_ENUM(VG_PATH_FORMAT                      , 0x1600),
    CT_ENUM(VG_PATH_DATATYPE                    , 0x1601),
    CT_ENUM(VG_PATH_SCALE                       , 0x1602),
    CT_ENUM(VG_PATH_BIAS                        , 0x1603),
    CT_ENUM(VG_PATH_NUM_SEGMENTS                , 0x1604),
    CT_ENUM(VG_PATH_NUM_COORDS                  , 0x1605),

    /* VGCapStyle */
    CT_ENUM(VG_CAP_BUTT                         , 0x1700),
    CT_ENUM(VG_CAP_ROUND                        , 0x1701),
    CT_ENUM(VG_CAP_SQUARE                       , 0x1702),

    /* VGJoinStyle */
    CT_ENUM(VG_JOIN_MITER                       , 0x1800),
    CT_ENUM(VG_JOIN_ROUND                       , 0x1801),
    CT_ENUM(VG_JOIN_BEVEL                       , 0x1802),

    /* VGFillRule */
    CT_ENUM(VG_EVEN_ODD                         , 0x1900),
    CT_ENUM(VG_NON_ZERO                         , 0x1901),

    /* PaintMode */
    CT_ENUM(VG_STROKE_PATH                      , ( 1 << 0)),
    CT_ENUM(VG_FILL_PATH                        , ( 1 << 1)),

    /* VGPaintParamType */
    CT_ENUM(VG_PAINT_TYPE                       , 0x1A00),
    CT_ENUM(VG_PAINT_COLOR                      , 0x1A01),
    CT_ENUM(VG_PAINT_COLOR_RAMP_SPREAD_MODE     , 0x1A02),
    CT_ENUM(VG_PAINT_COLOR_RAMP_PREMULTIPLIED   , 0x1A07),    
    CT_ENUM(VG_PAINT_COLOR_RAMP_STOPS           , 0x1A03),
    CT_ENUM(VG_PAINT_LINEAR_GRADIENT            , 0x1A04),
    CT_ENUM(VG_PAINT_RADIAL_GRADIENT            , 0x1A05),
    CT_ENUM(VG_PAINT_PATTERN_TILING_MODE        , 0x1A06),

    /* VGPaintType */
    CT_ENUM(VG_PAINT_TYPE_COLOR                 , 0x1B00),
    CT_ENUM(VG_PAINT_TYPE_LINEAR_GRADIENT       , 0x1B01),
    CT_ENUM(VG_PAINT_TYPE_RADIAL_GRADIENT       , 0x1B02),
    CT_ENUM(VG_PAINT_TYPE_PATTERN               , 0x1B03),

    /* VGColorRampSpreadMode */
    CT_ENUM(VG_COLOR_RAMP_SPREAD_PAD            , 0x1C00),
    CT_ENUM(VG_COLOR_RAMP_SPREAD_REPEAT         , 0x1C01),
    CT_ENUM(VG_COLOR_RAMP_SPREAD_REFLECT        , 0x1C02),

    /* VGTilingMode */
    CT_ENUM(VG_TILE_FILL                        , 0x1D00),
    CT_ENUM(VG_TILE_PAD                         , 0x1D01),
    CT_ENUM(VG_TILE_REPEAT                      , 0x1D02),
    CT_ENUM(VG_TILE_REFLECT                     , 0x1D03),

    /* RGB{A,X} channel ordering */
    CT_ENUM(VG_sRGBX_8888                       ,  0),
    CT_ENUM(VG_sRGBA_8888                       ,  1),
    CT_ENUM(VG_sRGBA_8888_PRE                   ,  2),
    CT_ENUM(VG_sRGB_565                         ,  3),
    CT_ENUM(VG_sRGBA_5551                       ,  4),
    CT_ENUM(VG_sRGBA_4444                       ,  5),
    CT_ENUM(VG_sL_8                             ,  6),
    CT_ENUM(VG_lRGBX_8888                       ,  7),
    CT_ENUM(VG_lRGBA_8888                       ,  8),
    CT_ENUM(VG_lRGBA_8888_PRE                   ,  9),
    CT_ENUM(VG_lL_8                             , 10),
    CT_ENUM(VG_A_8                              , 11),
    CT_ENUM(VG_BW_1                             , 12),
    CT_ENUM(VG_A_1                             ,13),
    CT_ENUM(VG_A_4                             ,14),

    /* {A,X}RGB channel ordering */
    CT_ENUM(VG_sXRGB_8888                       , 0 | (1 << 6)),
    CT_ENUM(VG_sARGB_8888                       , 1 | (1 << 6)),
    CT_ENUM(VG_sARGB_8888_PRE                   , 2 | (1 << 6)),
    CT_ENUM(VG_sARGB_1555                       , 4 | (1 << 6)),
    CT_ENUM(VG_sARGB_4444                       , 5 | (1 << 6)),
    CT_ENUM(VG_lXRGB_8888                       , 7 | (1 << 6)),
    CT_ENUM(VG_lARGB_8888                       , 8 | (1 << 6)),
    CT_ENUM(VG_lARGB_8888_PRE                   , 9 | (1 << 6)),

    /* BGR{A,X} channel ordering */
    CT_ENUM(VG_sBGRX_8888                       , 0 | (1 << 7)),
    CT_ENUM(VG_sBGRA_8888                       , 1 | (1 << 7)),
    CT_ENUM(VG_sBGRA_8888_PRE                   , 2 | (1 << 7)),
    CT_ENUM(VG_sBGR_565                         , 3 | (1 << 7)),
    CT_ENUM(VG_sBGRA_5551                       , 4 | (1 << 7)),
    CT_ENUM(VG_sBGRA_4444                       , 5 | (1 << 7)),
    CT_ENUM(VG_lBGRX_8888                       , 7 | (1 << 7)),
    CT_ENUM(VG_lBGRA_8888                       , 8 | (1 << 7)),
    CT_ENUM(VG_lBGRA_8888_PRE                   , 9 | (1 << 7)),

    /* {A,X}BGR channel ordering */
    CT_ENUM(VG_sXBGR_8888                       , 0 | (1 << 6) | (1 << 7)), 
    CT_ENUM(VG_sABGR_8888                       , 1 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_sABGR_8888_PRE                   , 2 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_sABGR_1555                       , 4 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_sABGR_4444                       , 5 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_lXBGR_8888                       , 7 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_lABGR_8888                       , 8 | (1 << 6) | (1 << 7)),
    CT_ENUM(VG_lABGR_8888_PRE                   , 9 | (1 << 6) | (1 << 7)),

    /* ImageQuality */
    CT_ENUM(VG_IMAGE_QUALITY_NONANTIALIASED     , (1 << 0)),
    CT_ENUM(VG_IMAGE_QUALITY_FASTER             , (1 << 1)),
    CT_ENUM(VG_IMAGE_QUALITY_BETTER             , (1 << 2)),

    /* VGImageParamType */
    CT_ENUM(VG_IMAGE_FORMAT                     , 0x1E00),
    CT_ENUM(VG_IMAGE_WIDTH                      , 0x1E01),
    CT_ENUM(VG_IMAGE_HEIGHT                     , 0x1E02),

    /* VGImageMode */
    CT_ENUM(VG_DRAW_IMAGE_NORMAL                , 0x1F00),
    CT_ENUM(VG_DRAW_IMAGE_MULTIPLY              , 0x1F01),

    /* ImageChannel */
    CT_ENUM(VG_RED                              , (1 << 3)),
    CT_ENUM(VG_GREEN                            , (1 << 2)),
    CT_ENUM(VG_BLUE                             , (1 << 1)),
    CT_ENUM(VG_ALPHA                            , (1 << 0)),

    /* VGBlendMode */
    CT_ENUM(VG_BLEND_SRC                        , 0x2000),
    CT_ENUM(VG_BLEND_SRC_OVER                   , 0x2001),
    CT_ENUM(VG_BLEND_DST_OVER                   , 0x2002),
    CT_ENUM(VG_BLEND_SRC_IN                     , 0x2003),
    CT_ENUM(VG_BLEND_DST_IN                     , 0x2004),
    CT_ENUM(VG_BLEND_MULTIPLY                   , 0x2005),
    CT_ENUM(VG_BLEND_SCREEN                     , 0x2006),
    CT_ENUM(VG_BLEND_ADDITIVE                   , 0x2009),

    /* VGHardwareQueryType */
    CT_ENUM(VG_IMAGE_FORMAT_QUERY               , 0x2100),
    CT_ENUM(VG_PATH_DATATYPE_QUERY              , 0x2101),

    /* VGHardwareQueryResult */
    CT_ENUM(VG_HARDWARE_ACCELERATED             , 0x2200),
    CT_ENUM(VG_HARDWARE_UNACCELERATED           , 0x2201),

    /* VGStringID */
    CT_ENUM(VG_VENDOR                           , 0x2300),
    CT_ENUM(VG_RENDERER                         , 0x2301),
    CT_ENUM(VG_VERSION                          , 0x2302),
    CT_ENUM(VG_EXTENSIONS                       , 0x2303),

    /*VGFontParamType*/
    CT_ENUM(VG_FONT_NUM_GLYPHS             , 0x2F00)
};

VGint GetVgEnumSize( void )
{
    return ( sizeof(vgEnumList) / sizeof(CT_EnumCheckRec) );
}

CT_Result A10101_ParameterCoverage_by_HUONE(CT_File *AnsFile)
{
    VGint   i, count;
    VGfloat error = 0.0f;

    count = GetVgEnumSize();
    for ( i = 0; i < count; i++ )  {
        if ( vgEnumList[i].value != vgEnumList[i].true_ ) {
            error++;
        }
    }

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
