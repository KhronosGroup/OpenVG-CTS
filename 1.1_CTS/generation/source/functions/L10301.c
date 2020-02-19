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
/*                Test the error handling of vgDrawGlyph()                     */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyph_BadHandle()
{
    VGFont       font = VG_INVALID_HANDLE;
    VGuint       glyphIndex = 0;
	VGPaintMode  fs = VG_FILL_PATH;

    vgDrawGlyph(font, glyphIndex, fs, VG_FALSE);

    if (vgGetError() != VG_BAD_HANDLE_ERROR)
        return CT_ERROR;

    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the error handling of vgDrawGlyph()                     */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyph_IllegalArgument()
{
    VGFont             font = VG_INVALID_HANDLE;
    VGuint             glyphIndex = 1;
	VGPaintMode        fs = VG_FILL_PATH;
    VGint              numGlyphs = 1;
    VGPath             vg_path;
    VGboolean          isHinted = VG_FALSE;
    VGfloat            glyph_origin[2] = {0.0, 0.0};
    VGfloat            escapement[2] = {0.0, 0.0};

    font = vgCreateFont(numGlyphs);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

	/* glyphIndex is undefined */
    vgDrawGlyph(font, glyphIndex, fs, VG_FALSE);

    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           0, 0, (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	fs = 4; /* call with invalid fs data */
    vgDrawGlyph(font, glyphIndex, fs, VG_FALSE);

    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath(vg_path);
	vgDestroyFont(font);
    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the error handling of vgDrawGlyphs()                    */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyphs_BadHandle()
{
    VGFont       font = VG_INVALID_HANDLE;
    VGuint       glyphIndices[2] = {0, 1};
	VGPaintMode  fs = VG_FILL_PATH;

    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);

    if (vgGetError() != VG_BAD_HANDLE_ERROR)
        return CT_ERROR;

    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the error handling of vgDrawGlyphs()                    */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgDrawGlyphs_IllegalArgument()
{
    VGFont             font = VG_INVALID_HANDLE;
    VGuint             glyphIndices[2] = {0, 1};
	VGPaintMode        fs = VG_FILL_PATH;
    VGint              numGlyphs = 2;
    VGPath             vg_path;
    VGboolean          isHinted = VG_TRUE;
    VGfloat            glyph_origin[2] = {0.0, 0.0};
    VGfloat            escapement[2] = {5.0, 0.0};

    font = vgCreateFont(numGlyphs);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

	/* none of glyphIndices are defined */
    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           0, 0, (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, 0, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* only one of glyphIndices is defined */
    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* define an empty glyph (no path object specified) */
    vgSetGlyphToPath (font, 1, (VGHandle)0, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	fs = 4; /* call with invalid fs data */
    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, fs, VG_FALSE);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* call with fs = 0 (no rendering) */
    vgDrawGlyphs(font, 2, glyphIndices, (void*)0, (void*)0, 0, VG_FALSE);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyPath(vg_path);
	vgDestroyFont(font);
    return CT_NO_ERROR;
}

CT_Result L10301_DrawGlyphTest_by_MTI(CT_File *AnsFile)
{
    VGfloat error = 0.0f;
   
    if (check_vgDrawGlyph_BadHandle() == CT_ERROR)
        error ++;

    if (check_vgDrawGlyph_IllegalArgument() == CT_ERROR)
        error ++;

    if (check_vgDrawGlyphs_BadHandle() == CT_ERROR)
        error ++;
    
    if (check_vgDrawGlyphs_IllegalArgument() == CT_ERROR)
        error ++;
    
    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
