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
#include "../static/monotype/pathdata.h"
#include "../static/monotype/bitmapdata.h"

extern CT_Result makeFramePath(VGPath *);

/*-----------------------------------------------------------------------------*/
/*                   Test the functionality of Glyph API                       */
/*-----------------------------------------------------------------------------*/
static CT_Result makeHintedVGFont(VGFont *testFont)
{
    VGFont             font = VG_INVALID_HANDLE;
    VGPath             vg_path = VG_INVALID_HANDLE;
    VGfloat            glyph_origin[2] = {0.0, 0.0};

    font = vgCreateFont(6);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph71_numSegments, glyph71_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph71_numSegments, glyph71_Segments, hintedGlyph71_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 71, vg_path, VG_TRUE, glyph_origin, hintedGlyph71_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph79_numSegments, glyph79_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph79_numSegments, glyph79_Segments, hintedGlyph79_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 79, vg_path, VG_TRUE, glyph_origin, hintedGlyph79_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph86_numSegments, glyph86_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph86_numSegments, glyph86_Segments, hintedGlyph86_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 86, vg_path, VG_TRUE, glyph_origin, hintedGlyph86_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph71_numSegments, glyph71_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph101_numSegments, glyph101_Segments, hintedGlyph101_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 101, vg_path, VG_TRUE, glyph_origin, hintedGlyph101_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph110_numSegments, glyph110_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph110_numSegments, glyph110_Segments, hintedGlyph110_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 110, vg_path, VG_TRUE, glyph_origin, hintedGlyph110_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph112_numSegments, glyph112_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph112_numSegments, glyph112_Segments, hintedGlyph112_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 112, vg_path, VG_TRUE, glyph_origin, hintedGlyph112_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

	*(testFont) = font; /* return font handle */
    return CT_NO_ERROR;
}

static CT_Result makeBitmapVGFont(VGFont *testFont)
{
    VGFont             font = VG_INVALID_HANDLE;
    VGImage            vg_image = VG_INVALID_HANDLE;

    font = vgCreateFont(6);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph71_width, bitmapGlyph71_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph71_Data, bitmapGlyph71_stride, VG_A_8, 
				   0, 0, bitmapGlyph71_width, bitmapGlyph71_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 71, vg_image, bitmapGlyph71_origin, bitmapGlyph71_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph79_width, bitmapGlyph79_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph79_Data, bitmapGlyph79_stride, VG_A_8, 
				   0, 0, bitmapGlyph79_width, bitmapGlyph79_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 79, vg_image, bitmapGlyph79_origin, bitmapGlyph79_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph86_width, bitmapGlyph86_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph86_Data, bitmapGlyph86_stride, VG_A_8, 
				   0, 0, bitmapGlyph86_width, bitmapGlyph86_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 86, vg_image, bitmapGlyph86_origin, bitmapGlyph86_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph101_width, bitmapGlyph101_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph101_Data, bitmapGlyph101_stride, VG_A_8, 
				   0, 0, bitmapGlyph101_width, bitmapGlyph101_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 101, vg_image, bitmapGlyph101_origin, bitmapGlyph101_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph110_width, bitmapGlyph110_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph110_Data, bitmapGlyph110_stride, VG_A_8, 
				   0, 0, bitmapGlyph110_width, bitmapGlyph110_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 110, vg_image, bitmapGlyph110_origin, bitmapGlyph110_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph112_width, bitmapGlyph112_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph112_Data, bitmapGlyph112_stride, VG_A_8, 
				   0, 0, bitmapGlyph112_width, bitmapGlyph112_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 112, vg_image, bitmapGlyph112_origin, bitmapGlyph112_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

	*(testFont) = font; /* return font handle */
    return CT_NO_ERROR;
}

static CT_Result makeMixedVGFont(VGFont *testFont)
{
    VGFont             font = VG_INVALID_HANDLE;
    VGPath             vg_path = VG_INVALID_HANDLE;
    VGImage            vg_image = VG_INVALID_HANDLE;
    VGfloat            glyph_origin[2] = {0.0, 0.0};

    font = vgCreateFont(6);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph71_numSegments, glyph71_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph71_numSegments, glyph71_Segments, hintedGlyph71_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 71, vg_path, VG_TRUE, glyph_origin, hintedGlyph71_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph79_numSegments, glyph79_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph79_numSegments, glyph79_Segments, hintedGlyph79_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 79, vg_path, VG_TRUE, glyph_origin, hintedGlyph79_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           glyph86_numSegments, glyph86_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph86_numSegments, glyph86_Segments, hintedGlyph86_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 86, vg_path, VG_TRUE, glyph_origin, hintedGlyph86_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph101_width, bitmapGlyph101_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph101_Data, bitmapGlyph101_stride, VG_A_8, 
				   0, 0, bitmapGlyph101_width, bitmapGlyph101_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 101, vg_image, bitmapGlyph101_origin, bitmapGlyph101_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph110_width, bitmapGlyph110_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph110_Data, bitmapGlyph110_stride, VG_A_8, 
				   0, 0, bitmapGlyph110_width, bitmapGlyph110_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 110, vg_image, bitmapGlyph110_origin, bitmapGlyph110_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

    vg_image = vgCreateImage(VG_A_8, bitmapGlyph112_width, bitmapGlyph112_height,
                             VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgImageSubData(vg_image, bitmapGlyph112_Data, bitmapGlyph112_stride, VG_A_8, 
				   0, 0, bitmapGlyph112_width, bitmapGlyph112_height);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, 112, vg_image, bitmapGlyph112_origin, bitmapGlyph112_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);

	*(testFont) = font; /* return font handle */
    return CT_NO_ERROR;
}

CT_Result L10402_GlyphRendering_by_MTI(CT_File *AnsFile)
{
    VGFont               hintedFont = VG_INVALID_HANDLE;
    VGFont               bitmapFont = VG_INVALID_HANDLE;
    VGFont               mixedFont = VG_INVALID_HANDLE;
    VGPaint              fill;
	int                  i;
	VGint                numGlyphs;
    VGuint               glyphIndices[6] = {79, 112, 101, 110, 86, 71};
	VGfloat              endLine1[2];
	VGfloat              endLine2[2];
	VGfloat              endLine3[2];
	VGfloat              textOrigin[2] = {3.0f, 11.0f};
    static const VGfloat black[4]  = {0, 0, 0, 1};
    static const VGfloat white[4]  = {1, 1, 1, 1};

    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_FASTER);
	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
	vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_STENCIL);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, black);
    vgSetPaint(fill, VG_FILL_PATH);

	if (makeHintedVGFont(&hintedFont))
	{
		vgDestroyPaint(fill);
		return CT_ERROR;
	}
	if (hintedFont == VG_INVALID_HANDLE)
	{
		vgDestroyPaint(fill);
		return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(hintedFont, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 6)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
        return CT_ERROR;
	}

	if (makeBitmapVGFont(&bitmapFont))
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		return CT_ERROR;
	}
	if (bitmapFont == VG_INVALID_HANDLE)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(bitmapFont, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 6)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
        return CT_ERROR;
	}

	if (makeMixedVGFont(&mixedFont))
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		return CT_ERROR;
	}
	if (mixedFont == VG_INVALID_HANDLE)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(mixedFont, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 6)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
        return CT_ERROR;
	}

	vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
	vgLoadIdentity();
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* draw unadjusted string of glyphs */
    vgDrawGlyphs(hintedFont, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine1);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* set the new text origin - go back to the beginning of the line and up 1 line */
	textOrigin[1] += 16.0;
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* draw unadjusted string of glyphs */
    vgDrawGlyphs(bitmapFont, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine2);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* set the new text origin - go back to the beginning of the line and up 1 line */
	textOrigin[1] += 16.0;
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* draw unadjusted string of glyphs */
    vgDrawGlyphs(mixedFont, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine3);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
		return CT_ERROR;
	}

	/* cumulative test for errors in calculating glyph origin */
	textOrigin[0] = endLine1[0] + endLine2[0] + endLine3[0];
	textOrigin[1] = endLine1[1] + endLine2[1] + endLine3[1];
	i = (int)(textOrigin[0] + textOrigin[1] - 257.95);
	if (i)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(hintedFont);
		vgDestroyFont(bitmapFont);
		vgDestroyFont(mixedFont);
        return CT_ERROR;
	}

    vgDestroyPaint(fill);
    vgDestroyFont(hintedFont);
	vgDestroyFont(bitmapFont);
	vgDestroyFont(mixedFont);
    if (vgGetError() == VG_NO_ERROR) {
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    }
    else {
        return CT_ERROR;
    }
}