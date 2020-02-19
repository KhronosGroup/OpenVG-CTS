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

/*-----------------------------------------------------------------------------*/
/*                   Test the functionality of Glyph API                       */
/*-----------------------------------------------------------------------------*/
CT_Result makeTestVGFont(VGFont *testFont)
{
    VGFont             font = VG_INVALID_HANDLE;
    VGPath             vg_path = VG_INVALID_HANDLE;

    font = vgCreateFont(6);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph71_numSegments, glyph71_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph71_numSegments, glyph71_Segments, glyph71_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 71, vg_path, VG_FALSE, glyph_origin, glyph71_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph79_numSegments, glyph79_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph79_numSegments, glyph79_Segments, glyph79_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 79, vg_path, VG_FALSE, glyph_origin, glyph79_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph86_numSegments, glyph86_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph86_numSegments, glyph86_Segments, glyph86_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 86, vg_path, VG_FALSE, glyph_origin, glyph86_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph71_numSegments, glyph71_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph101_numSegments, glyph101_Segments, glyph101_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 101, vg_path, VG_FALSE, glyph_origin, glyph101_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph110_numSegments, glyph110_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph110_numSegments, glyph110_Segments, glyph110_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 110, vg_path, VG_FALSE, glyph_origin, glyph110_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath (vg_path);

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0/2048.0, 0.0f,
                           glyph112_numSegments, glyph112_numCoordPairs, 
						   (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgAppendPathData(vg_path, glyph112_numSegments, glyph112_Segments, glyph112_Data);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 112, vg_path, VG_FALSE, glyph_origin, glyph112_escapement);
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

CT_Result L10401_GlyphRendering_by_MTI(CT_File *AnsFile)
{
    VGFont               font = VG_INVALID_HANDLE;
    VGPaint              fill;
	int                  i;
	VGint                numGlyphs;
    VGuint               glyphIndices[6] = {79, 112, 101, 110, 86, 71};
	VGfloat              endLine1[2];
	VGfloat              endLine2[2];
	VGfloat              endLine3[2];
	VGfloat              sx = 16.0;
	VGfloat              sy = 16.0;
	VGfloat              textOrigin[2] = {0.2f, 0.75f};
    static const VGfloat black[4]  = {0, 0, 0, 1};
    static const VGfloat white[4]  = {1, 1, 1, 1};
	static const VGfloat green[4]  = {0, 1, 0, 1};

    vgSetfv(VG_CLEAR_COLOR, 4, white);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

    vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_FASTER);
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

    fill = vgCreatePaint();
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, black);
    vgSetPaint(fill, VG_FILL_PATH);

	if (makeTestVGFont(&font))
	{
		vgDestroyPaint(fill);
        return CT_ERROR;
	}

	if (font == VG_INVALID_HANDLE)
	{
		vgDestroyPaint(fill);
        return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 6)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
	vgLoadIdentity();
	vgScale(sx, sy);
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* draw unadjusted string of glyphs */
	for (i=0; i<6; i++)
	{
		vgDrawGlyph(font, glyphIndices[i], VG_FILL_PATH, VG_FALSE);
	    if (vgGetError() != VG_NO_ERROR)
		{
			vgDestroyPaint(fill);
			vgDestroyFont(font);
	        return CT_ERROR;
		}
	}

	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine1);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* set the new text origin - go back to the beginning of the line and up 1 line */
	textOrigin[1] += 1.0;
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* draw string of glyphs with kerning */
    vgDrawGlyphs(font, 6, glyphIndices, glyphKerningX, glyphKerningY, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine2);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* set the new text origin - go back to the beginning of the line and up 1 line */
	textOrigin[1] += 1.0;
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* draw unadjusted string of glyphs */
    vgDrawGlyphs(font, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine3);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    if (endLine1[0] != endLine3[0])
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* this test checks for correctness of the GLYPH_ORIGIN calculations when 
	** adjustments array pointers are not NULL. Because the floating point 
	** values can be calculated with different precision, I am assuming that at 
	** least four decimal digits (i.e. using 16-bit mantissa) will be correct */
	i = (int)((endLine3[0] - endLine2[0] - 0.08345f) * 10000.0);
	if (i)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* clear glyph 'n' in the font and draw glyphs, should produce an error */
    vgClearGlyph(font, 110);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgDrawGlyphs(font, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* replace glyph 'n' with <space> (empty) glyph having the same metrics */
    vgSetGlyphToPath (font, 110, VG_INVALID_HANDLE, VG_FALSE, glyph_origin, glyph110_escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* translate the matrix */
	vgTranslate((0.2f-endLine3[0]), 0.0f); /* back to the beginning of the line */
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, green);
    vgSetPaint(fill, VG_FILL_PATH);

	/* draw unadjusted string of glyphs, now in GREEN */
	/* should overwrite the black 3rd line, excluding 'n' */
    vgDrawGlyphs(font, 6, glyphIndices, (void*)0, (void*)0, VG_FILL_PATH, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine1);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* assuming worst case precision of 16-bit mantissa */
	i = (int)((2*endLine3[0] - endLine1[0] - 0.19995f) * 10000.0);
	if (i)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPaint(fill);
    vgDestroyFont(font);
    if (vgGetError() == VG_NO_ERROR) {
        return SaveImageFile(0, 0, WINDSIZEX, WINDSIZEY, AnsFile);
    }
    else {
        return CT_ERROR;
    }
}
