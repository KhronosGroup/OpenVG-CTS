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

/*-----------------------------------------------------------------------------*/
/*                Test the vgDrawGlyph() functionality                         */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyph()
{
    VGFont             font = VG_INVALID_HANDLE;
    VGuint             glyphIndex = 1;
	VGPaintMode        fs = VG_FILL_PATH;
	VGfloat            newOrigin[2];
    VGint              numGlyphs = 1;
    VGPath             vg_path = VG_INVALID_HANDLE;
    VGboolean          isHinted = VG_TRUE;
    VGfloat            scale = 32.0;
    VGfloat            glyph_origin[2] = {0.0, 0.0};
    VGfloat            escapement_h[2] = {5.0, 5.0};
    VGfloat            escapement_u[2] = {0.25, 0.25};
    VGfloat            m[9];

    font = vgCreateFont(numGlyphs);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement_h);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
	vgLoadIdentity();
	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDrawGlyph(font, glyphIndex, fs, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgGetfv(VG_GLYPH_ORIGIN, 2, newOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	if ((newOrigin[0] != escapement_h[0]) || (newOrigin[1] != escapement_h[1]))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	isHinted = VG_FALSE;
    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement_u);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgScale(scale, scale);
    vgDrawGlyph(font, glyphIndex, fs, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgGetfv(VG_GLYPH_ORIGIN, 2, newOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	if ((newOrigin[0] != escapement_u[0]) || (newOrigin[1] != escapement_u[1]))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgTranslate(escapement_u[0], escapement_u[1]);
	vgGetMatrix(m);

    if (((scale*newOrigin[0]) != m[6]) || ((scale*newOrigin[1]) != m[7]))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);
    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the vgDrawGlyphs() functionality                        */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyphs()
{
    VGFont             font = VG_INVALID_HANDLE;
    VGuint             glyphIndices[2] = {0, 1};
	VGPaintMode        fs = VG_FILL_PATH;
	VGfloat            newOrigin[2];
    VGint              numGlyphs = 2;
    VGPath             vg_path = VG_INVALID_HANDLE;
    VGboolean          isHinted = VG_TRUE;
    VGfloat            scale = 32.0;
    VGfloat            glyph_origin[2] = {0.0, 0.0};
    VGfloat            escapement_h[2] = {5.0, 5.0};
    VGfloat            escapement_u[2] = {0.25, 0.25};
    VGfloat            m[9];

    font = vgCreateFont(numGlyphs);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vgSetGlyphToPath (font, 0, vg_path, isHinted, glyph_origin, escapement_h);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 1, vg_path, isHinted, glyph_origin, escapement_h);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
	vgLoadIdentity();
	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgGetfv(VG_GLYPH_ORIGIN, 2, newOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	if ((newOrigin[0] != (2 * escapement_h[0])) || (newOrigin[1] != (2 * escapement_h[1])))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	isHinted = VG_FALSE;
    vgSetGlyphToPath (font, 0, vg_path, isHinted, glyph_origin, escapement_u);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 1, vg_path, isHinted, glyph_origin, escapement_u);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgScale(scale, scale);
    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgGetfv(VG_GLYPH_ORIGIN, 2, newOrigin);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgTranslate((2*escapement_u[0]), (2*escapement_u[1]));
	vgGetMatrix(m);

    if (((scale*newOrigin[0]) != m[6]) || ((scale*newOrigin[1]) != m[7]))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);

    return CT_NO_ERROR;
}

CT_Result L10302_DrawGlyphTest_by_MTI(CT_File *AnsFile)
{
    VGfloat error = 0.0f;

    if (check_vgDrawGlyph() == CT_ERROR)
        error ++;

    if (check_vgDrawGlyphs() == CT_ERROR)
        error ++;

	if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
