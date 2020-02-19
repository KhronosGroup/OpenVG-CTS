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

extern CT_Result makeTestVGFont(VGFont *);

/*-----------------------------------------------------------------------------*/
/*                   Test the functionality of Glyph API                       */
/*-----------------------------------------------------------------------------*/

CT_Result L10403_GlyphRendering_by_MTI(CT_File *AnsFile)
{
    VGFont               font = VG_INVALID_HANDLE;
    VGPaint              fill;
	int                  i;
	VGint                numGlyphs;
    VGuint               glyphIndices[6] = {79, 112, 101, 110, 86, 71};
	VGfloat              endLine[2];
	VGfloat              sx = 16.0;
	VGfloat              sy = 16.0;
	VGfloat              shx = 0.25f;
	VGfloat              shy = 0.0f;
	VGfloat              textOrigin[2] = {0.8f, 0.0f};
    static const VGfloat black[4]  = {0, 0, 0, 1};
    static const VGfloat white[4]  = {1, 1, 1, 1};
    static const VGfloat red[4]  = {1, 0, 0, 1};

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
	/* rotate and shear the matrix */
	vgLoadIdentity();
	vgScale(sx, sy);
	vgRotate(45.0);
	vgShear(shx, shy);

	/* set the new text origin */
	textOrigin[0] = 0.8f;
	textOrigin[1] = 0.0f;
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

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* check whether the glyph origin calculations are correct - it should be
	** the sum of all glyph escapements plus the initial text origin. Round to
	** four decimal digits assuming worst-case precision of 16-bit mantissa */
	i = (int)((endLine[0] - 3.610407f - 0.79995f + endLine[1]) * 10000.0);
	if (i)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* rotate, shear and translate */
	vgLoadIdentity();
	vgScale(sx, sy);
	vgTranslate(0.0f, 4.0f);
	vgRotate(-45.0);
	vgShear(-shx, shy);
    vgSetParameterfv(fill, VG_PAINT_COLOR, 4, red);
    vgSetPaint(fill, VG_FILL_PATH);
	/* set the new text origin */
	vgSetfv(VG_GLYPH_ORIGIN, 2, textOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* draw unadjusted string of glyphs with RED color */
	/* since fill = 0 it should not paint any RED pixels */
    vgDrawGlyphs(font, 6, glyphIndices, (void*)0, (void*)0, 0, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

 	vgGetfv(VG_GLYPH_ORIGIN, 2, endLine);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPaint(fill);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* check whether the glyph origin calculations are correct - it should be
	** the sum of all glyph escapements plus the initial text origin. Round to
	** four decimal digits assuming worst-case precision of 16-bit mantissa */
	i = (int)((endLine[0] - 3.610407f - 0.79995f + endLine[1]) * 10000.0);
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
