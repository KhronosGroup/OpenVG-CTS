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


typedef enum {
  CTS_UNKNOWN						= -1,
  CTS_TOP_RIGHT						= (1 << 0), /* RI */
  CTS_BOTTOM_RIGHT					= (1 << 1), 
  CTS_TOP_LEFT						= (1 << 2),	
  CTS_BOTTOM_LEFT					= (1 << 3)	
} CTSTieBreak;

static CTSTieBreak s_tieBreak = CTS_UNKNOWN;


static void DrawSquare_by_STM()
{
	VGPath    path;
	VGPaint   paint;
	VGfloat   blackColor[] = {0.0f, 0.0f, 0.0f, 0.0f};  //same as default

	/* draw a square */
	static const VGubyte commands[5] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS,VG_LINE_TO_ABS,VG_LINE_TO_ABS, VG_CLOSE_PATH};
	static const VGfloat coords[]    = {0.5f, 0.5f, 0.5f, 2.5f, 2.5f, 2.5f, 2.5f, 0.5f};

	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	if ( path == VG_INVALID_HANDLE ) {
		return;
	}
	vgAppendPathData(path, 5, commands, coords);

	paint = vgCreatePaint();
	if ( paint == VG_INVALID_HANDLE ) {
		vgDestroyPath(path);
		return;
	}

	vgSetfv(VG_CLEAR_COLOR, 4, blackColor);
	vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
	vgLoadIdentity();
	vgSetColor(paint, 0xFFFFFFFF);
	vgSetPaint(paint, VG_FILL_PATH);
	vgDrawPath(path, VG_FILL_PATH);

	vgDestroyPath(path);
	vgDestroyPaint(paint);

	/* restore default states */
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER);
	vgSetPaint(VG_INVALID_HANDLE, VG_FILL_PATH);
}

/* draw one square, and read back the corner pixels (top-left, bottom-left, up-right, bottom-right)
   to detect the tie break rule used by the OpenVG implementation */

static CTSTieBreak DetectTieBreakRule_by_STM()
{
	VGImageFormat dataFormat;
	CTSTieBreak rule = CTS_TOP_RIGHT;
	int count = 0;
	VGubyte color;

	DrawSquare_by_STM();   /* clear (BLACK), draw 2x2 rect (WHITE) */

	/* read back format determination */
	/* read BLACK pixel by VG_sL_8, alpha-only surface return 0xFF and others return 0. */
	vgReadPixels(&color, 0, VG_sL_8, WINDSIZEX - 1, WINDSIZEY - 1, 1, 1);
	dataFormat = (color != 0)? VG_A_8 : VG_sL_8;

	/* check which of the 4 pixels at the 4 corners is lit */

	/* check the bottom left pixel */
	vgReadPixels(&color, 0, dataFormat, 0, 0, 1, 1); 
	if (color != 0) {
		rule = CTS_TOP_RIGHT;
		count++;
	}

	/* check top left pixel */
	vgReadPixels(&color, 0, dataFormat, 0, 2, 1, 1); 
	if (color != 0) {
		rule = CTS_BOTTOM_RIGHT;
		count++;
	}

	/* check the top right pixel */
	vgReadPixels(&color, 0, dataFormat, 2, 2, 1, 1); 
	if (color != 0) {
		rule = CTS_BOTTOM_LEFT;
		count++;
	}

	/* check bottom right pixel */
	vgReadPixels(&color, 0, dataFormat, 2, 0, 1, 1); 
	if (color != 0) {
		rule = CTS_TOP_LEFT;
		count++;
	}

	if (count != 1)	{
		PRINTF("Don't know the tie-break rule used by the OpenVG implementation. Using default rule!\n");
		rule = CTS_TOP_RIGHT;
	}

	return rule;
}


void LoadTieBreakRuleMatrix_by_STM(VGint bForceRecal)
{
	static const VGfloat topRight[9]	= {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	static const VGfloat bottomRight[9]	= {1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f, WINDSIZEY, 1.0f};
	static const VGfloat topLeft[9]		= {-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, WINDSIZEX, 0.0f, 1.0f};
	static const VGfloat bottomLeft[9]	= {-1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, WINDSIZEX, WINDSIZEY, 1.0f};
	
	static const VGfloat* s_tieBreakMatrix = NULL;

	if ((s_tieBreakMatrix == NULL) || (bForceRecal == VG_TRUE))
	{
		/* detect the tie break rule used by the OpenVG implementation */
		s_tieBreak = DetectTieBreakRule_by_STM();

		/* set the default matrix according to the tie break rule */
		switch (s_tieBreak)
		{
		case CTS_TOP_RIGHT: /* RI */
			s_tieBreakMatrix = topRight;
			break;

		case CTS_BOTTOM_RIGHT: 
			s_tieBreakMatrix = bottomRight;
			break;

		case CTS_TOP_LEFT:
			s_tieBreakMatrix = topLeft;
			break;

		case CTS_BOTTOM_LEFT:
			s_tieBreakMatrix = bottomLeft;
			break;

		default:
			s_tieBreakMatrix = topRight;
			break;
		}
	}

	vgLoadMatrix(s_tieBreakMatrix);
}


/* do flip the frame buffer  */

void   FlipBuffer_by_STM(VGint width, VGint height)
{
	VGubyte* buf     = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));
	VGubyte* flipBuf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));

	VGImageFormat dataFormat = VG_sRGBA_8888;  /* always this format */

	if (!buf)
		return;

	if (!flipBuf) {
		FREE(buf);
		return;
	}
	
	switch (s_tieBreak)
	{
	case CTS_TOP_RIGHT:
		/* nothing to do */
		break;

	case CTS_BOTTOM_RIGHT:
	{
		VGint    lineOffset  = width * 4;
		VGubyte* tempBuf     = buf;
		VGubyte* tempFlipBuf = flipBuf + lineOffset * (height - 1);
		VGint    j;

		vgReadPixels(buf, width * 4, dataFormat, 0, 0, width, height);

		for (j = 0; j < height; j++)
		{
			memcpy(tempFlipBuf, tempBuf, lineOffset);
			tempBuf += lineOffset;
			tempFlipBuf -= lineOffset;
		}

		vgWritePixels(flipBuf, width * 4, dataFormat, 0, 0, width, height);
		break;
	}

	case CTS_TOP_LEFT:
	{
		VGint    lineOffset  = width * 4;
		VGubyte* tempBuf     = buf;
		VGubyte* tempFlipBuf = flipBuf;
		VGint xOffset, xFlipOffset, i, j;

		vgReadPixels(buf, width*4, dataFormat, 0, 0, width, height);

		for (i = 0; i < width; i++)
		{
			xFlipOffset = (width-i-1)*4;
			xOffset = i*4;
			
			tempFlipBuf += xFlipOffset;
			tempBuf += xOffset;

			for (j = 0; j < height; j++)
			{
				memcpy(tempFlipBuf, tempBuf, 4);
				tempFlipBuf += lineOffset;
				tempBuf += lineOffset;
			}

			tempBuf = buf;
			tempFlipBuf = flipBuf;
		}
	
		vgWritePixels(flipBuf, width*4, dataFormat, 0, 0, width, height);
		break;
	}

	case CTS_BOTTOM_LEFT:
	{
		VGint    lineOffset  = width * 4;
		VGubyte* tempBuf     = buf;
		VGubyte* tempFlipBuf = flipBuf;
		VGint  xOffset, xFlipOffset, i, j;

		vgReadPixels(buf, width*4, dataFormat, 0, 0, width, height);

		for (i = 0; i < width; i++)
		{
			xFlipOffset = (width-i-1)*4;
			xOffset = i*4;
			
			tempFlipBuf += xFlipOffset;
			tempBuf += xOffset;

			tempFlipBuf += lineOffset*(height-1);

			for (j = 0; j < height; j++)
			{
				memcpy(tempFlipBuf, tempBuf, 4);
				tempFlipBuf -= lineOffset;
				tempBuf += lineOffset;
			}

			tempBuf = buf;
			tempFlipBuf = flipBuf;
		}
	
		vgWritePixels(flipBuf, width*4, dataFormat, 0, 0, width, height);
		break;
	}

	default:
		/* others one */
		break;
	}

	FREE(buf);
	FREE(flipBuf);
}
