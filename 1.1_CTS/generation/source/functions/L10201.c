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
/*              Test the error handling of vgSetGlyphToPath()                  */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgSetGlyphToPath_BadHandle()
{
    VGint     numGlyphs = 10;
    VGFont    font = VG_INVALID_HANDLE;
    VGPath    vg_path = VG_INVALID_HANDLE;
    VGuint    glyphIndex = 0;
    VGboolean isHinted = VG_FALSE;
    VGfloat   glyph_origin[2] = {0.0, 0.0};
    VGfloat   escapement[2] = {1.0, 0.0};

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           0, 0, (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
        return CT_ERROR;

	/* invalid font handle */
    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_BAD_HANDLE_ERROR)
	{
		vgDestroyPath(vg_path);
        return CT_ERROR;
	}

    font = vgCreateFont(numGlyphs);
    if ((vgGetError() != VG_NO_ERROR) || (font == VG_INVALID_HANDLE))
	{
		vgDestroyPath(vg_path);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgDestroyPath(vg_path);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_BAD_HANDLE_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vg_path = VG_INVALID_HANDLE;
    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);

    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*              Test the error handling of vgSetGlyphToPath()                  */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgSetGlyphToPath_InvalidArgument()
{
    VGint     numGlyphs = 10;
    VGFont    font = VG_INVALID_HANDLE;
    VGPath    vg_path = VG_INVALID_HANDLE;
    VGuint    glyphIndex = 0;
    VGboolean isHinted = VG_FALSE;
    VGfloat   glyph_origin[2] = {0.0, 0.0};
    VGfloat   escapement[2] = {1.0, 0.0};
	char*     ptr;

    vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0, 0.0f,
                           0, 0, (unsigned int)VG_PATH_CAPABILITY_ALL);

    if ((vgGetError() != VG_NO_ERROR) || (vg_path == VG_INVALID_HANDLE))
        return CT_ERROR;

    font = vgCreateFont(numGlyphs);
    if ((vgGetError() != VG_NO_ERROR) || (font == VG_INVALID_HANDLE))
	{
		vgDestroyPath(vg_path);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, (void*)0, escapement);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, (void*)0);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	ptr = ((char*)glyph_origin)+1;
    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, (void*)ptr, escapement);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyPath(vg_path);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	ptr = ((char*)escapement)+1;
    vgSetGlyphToPath (font, glyphIndex, vg_path, isHinted, glyph_origin, (void*)ptr);
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
/*              Test the error handling of vgSetGlyphToImage()                 */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgSetGlyphToImage_BadHandle()
{
    VGint     numGlyphs = 10;
    VGFont    font = VG_INVALID_HANDLE;
	VGImage   vg_image = VG_INVALID_HANDLE;
    VGuint    glyphIndex = 0;
    VGfloat   glyph_origin[2] = {0.0, 0.0};
    VGfloat   escapement[2] = {4.0, 0.0};

    vg_image = vgCreateImage(VG_A_8, 4, 4, VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
        return CT_ERROR;

	/* invalid font handle */
    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, escapement);
    if (vgGetError() != VG_BAD_HANDLE_ERROR)
	{
		vgDestroyImage(vg_image);
        return CT_ERROR;
	}

    font = vgCreateFont(numGlyphs);
    if ((vgGetError() != VG_NO_ERROR) || (font == VG_INVALID_HANDLE))
	{
		vgDestroyImage(vg_image);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgDestroyImage(vg_image);
    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, escapement);
    if (vgGetError() != VG_BAD_HANDLE_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vg_image = VG_INVALID_HANDLE;
    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);
    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*              Test the error handling of vgSetGlyphToImage()                 */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgSetGlyphToImage_InvalidArgument()
{
    VGint     numGlyphs = 10;
    VGFont    font = VG_INVALID_HANDLE;
	VGImage   vg_image = VG_INVALID_HANDLE;
    VGuint    glyphIndex = 0;
    VGfloat   glyph_origin[2] = {0.0, 0.0};
    VGfloat   escapement[2] = {4.0, 0.0};
	char*     ptr;

    vg_image = vgCreateImage(VG_A_8, 4, 4, VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
        return CT_ERROR;

    font = vgCreateFont(numGlyphs);
    if ((vgGetError() != VG_NO_ERROR) || (font == VG_INVALID_HANDLE))
	{
		vgDestroyImage(vg_image);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, glyphIndex, vg_image, (void*)0, escapement);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, (void*)0);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	ptr = ((char*)glyph_origin)+1;
    vgSetGlyphToImage (font, glyphIndex, vg_image, (void*)ptr, escapement);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	ptr = ((char*)escapement)+1;
    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, (void*)ptr);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyImage(vg_image);
	vgDestroyFont(font);

    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the error handling of vgClearGlyph()                    */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgClearGlyph_ErrorHandling()
{
    VGFont  font = VG_INVALID_HANDLE;
    VGuint  glyphIndex = 1;
    VGint   numGlyphs = 1;

    vgClearGlyph(font, glyphIndex);

    if (vgGetError() != VG_BAD_HANDLE_ERROR)
        return CT_ERROR;

    font = vgCreateFont(numGlyphs);

    if ((vgGetError() != VG_NO_ERROR) || (font == VG_INVALID_HANDLE))
        return CT_ERROR;

	/* no glyphs defined */
    vgClearGlyph(font, glyphIndex);

    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);
    return CT_NO_ERROR;
}

/*-----------------------------------------------------------------------------*/
/*                Test the functionality of vgClearGlyph()                     */
/*-----------------------------------------------------------------------------*/
static CT_Result check_vgClearGlyph()
{
    VGint     numGlyphs = 2;
    VGFont    font;
    VGuint    glyphIndex = 1;
    VGPath    vg_path;
	VGImage   vg_image;
    VGboolean isHinted = VG_FALSE;
    VGfloat   glyph_origin[2] = {0.0, 0.0};
    VGfloat   escapement[2] = {4.0, 0.0};

    font = vgCreateFont(numGlyphs);

    if (vgGetError() != VG_NO_ERROR)
        return CT_ERROR;

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
	vgDestroyPath(vg_path);

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 1)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vg_image = vgCreateImage(VG_A_8, 4, 4, VG_IMAGE_QUALITY_NONANTIALIASED);

    if ((vgGetError() != VG_NO_ERROR) || (vg_image == VG_INVALID_HANDLE))
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    glyphIndex++;
    vgSetGlyphToImage (font, glyphIndex, vg_image, glyph_origin, escapement);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyImage(vg_image);
		vgDestroyFont(font);
        return CT_ERROR;
	}
	vgDestroyImage(vg_image);

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 2)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    glyphIndex++;
	/* attempt to clear non-existing glyph */
    vgClearGlyph(font, glyphIndex);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 2)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    glyphIndex--;
    vgClearGlyph(font, glyphIndex);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 1)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	/* clearing the same glyph again */
    vgClearGlyph(font, glyphIndex);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 1)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    glyphIndex--;
    vgClearGlyph(font, glyphIndex);
    if (vgGetError() != VG_NO_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	numGlyphs = vgGetParameteri(font, VG_FONT_NUM_GLYPHS);
	if (numGlyphs != 0)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

    vgClearGlyph(font, glyphIndex);
    if (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR)
	{
		vgDestroyFont(font);
        return CT_ERROR;
	}

	vgDestroyFont(font);
    return CT_NO_ERROR;
}

CT_Result L10201_GlyphHandling_by_MTI(CT_File *AnsFile)
{
    VGfloat error = 0.0f;
   
    if (check_vgSetGlyphToPath_BadHandle() == CT_ERROR)
        error ++;

    if (check_vgSetGlyphToPath_InvalidArgument() == CT_ERROR)
        error ++;

    if (check_vgSetGlyphToImage_BadHandle() == CT_ERROR)
        error ++;

    if (check_vgSetGlyphToImage_InvalidArgument() == CT_ERROR)
        error ++;

    if (check_vgClearGlyph_ErrorHandling() == CT_ERROR)
        error ++;

    if (check_vgClearGlyph() == CT_ERROR)
        error ++;

    if ( vgGetError() == VG_NO_ERROR )
        return SaveValueFile (1, &error, AnsFile);
    else
        return CT_ERROR;
}
