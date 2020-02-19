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
#include "../static/hybrid/mobile_man.h"

#ifdef WIN32
#pragma optimize ("", off)
#endif

CT_Result H10203_ImageOperation_by_HYBRID(CT_File *AnsFile)
{
    VGImage mobile_man;
    VGImage mobileParent;
    VGImage child1;
    VGImage parent1;
    VGImage child2;
    VGImage parent2;
    VGImage parent3;
	VGint	scUpperLeft[4]	= {0, 32, 32, 32};
	VGint	scUpperRight[4] = {32, 32, 32, 32};
	VGint	scLowerLeft[4]	= {0, 0, 32, 32};
	VGint	scLowerRight[4] = {32, 0, 32, 32};
    VGfloat bgCol[4]		= {0.906f, 0.914f, 0.761f, 1.0f};

	/* Test that changes made to child, parent or sibling of an image are 
	   visible. Also effects on grandparent are tested. vgGetParent() is
	   verified to give correct output in these cases. */

	/* Background clear */
    vgSetfv(VG_CLEAR_COLOR, 4, bgCol);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);

	/* Set scissoring on for the test */
	vgSeti(VG_SCISSORING, VG_TRUE);

	/* Setup matrix mode */
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	/* Disable antialiasing */
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_NONANTIALIASED);
	vgSeti(VG_IMAGE_QUALITY, VG_IMAGE_QUALITY_NONANTIALIASED);

	/* Create the parent image */
    mobile_man = vgCreateImage(VG_sRGBA_8888, 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED|VG_IMAGE_QUALITY_FASTER|VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(mobile_man, mobile_man_data, 256, VG_sRGBA_8888, 0, 0, 64, 64);

	/* Try to get the parent of an image which has no parent */
    mobileParent = vgGetParent(mobile_man);

	/* If the parent is not available is should return a handle to the same image */
    if ( (mobileParent) != (mobile_man) )
    {
		return CT_ERROR;
    }

	/* Create two child images and check the result by drawing them over the original image.*/
    child1	= vgChildImage(mobile_man, 0, 0, 18, 18);
    parent1 = vgGetParent(child1);

	/* The parent of child1 should be mobile_man */
    if ( (parent1) != (mobile_man) )
    {
		return CT_ERROR;
    }

    child2 = vgChildImage(mobile_man, 16, 16, 16, 16);
    parent2 = vgGetParent(child2);

	/* Again the parent should be mobile_man */
    if ( (parent2) != (mobile_man) )
    {
		return CT_ERROR;
    }

	/*---------------------------------------------------------------------
	 * Lower left corner
	 *-------------------------------------------------------------------*/

	vgLoadIdentity();
	vgSetiv(VG_SCISSOR_RECTS, 4, scLowerLeft);

	/* Draw the child and the parent images and check that the pixels align correctly */
	vgDrawImage(mobile_man);
    vgDrawImage(child1);
    vgTranslate(16, 16);
    vgDrawImage(child2);

	/* Reset scissors and child images */
	vgSetiv(VG_SCISSOR_RECTS, 0, NULL);
	vgDestroyImage(child1);
	vgDestroyImage(child2);

	/*---------------------------------------------------------------------
	 * Lower right corner
	 *-------------------------------------------------------------------*/

	vgLoadIdentity();
	vgSetiv(VG_SCISSOR_RECTS, 4, scLowerRight);

	/* Test that modifying the parent has effect on both children */
    child1	= vgChildImage(mobile_man, 32, 0, 32, 20);
    child2  = vgChildImage(mobile_man, 38, 16, 26, 16);

    vgClearImage(mobile_man, 40, 8, 16, 20);
	vgTranslate(32, 0);
    vgDrawImage(child1);
	vgLoadIdentity();
	vgTranslate(38, 16);
    vgDrawImage(child2);

	/* Reset scissors and child images */
	vgSetiv(VG_SCISSOR_RECTS, 0, NULL);
	vgDestroyImage(child1);
	vgDestroyImage(child2);

	/*---------------------------------------------------------------------
	 * Upper left corner
	 *-------------------------------------------------------------------*/

	vgLoadIdentity();
	vgSetiv(VG_SCISSOR_RECTS, 4, scUpperLeft);

	/* Test that modifying a child is reflected in the parent and the child */
	child1 = vgChildImage(mobile_man, 0, 32, 20, 20);
	child2 = vgChildImage(mobile_man, 12, 42, 16, 16);
    
    vgClearImage(child1, 8, 6, 100, 100);
    vgDrawImage(mobile_man);

	vgTranslate(12, 42);
	vgDrawImage(child2);

	/* Reset the scissors and destroy old child images */
	vgSetiv(VG_SCISSOR_RECTS, 0, NULL);
	vgDestroyImage(child1);
	vgDestroyImage(child2);

	/*---------------------------------------------------------------------
	 * Upper right corner
	 *-------------------------------------------------------------------*/

	vgLoadIdentity();
	vgSetiv(VG_SCISSOR_RECTS, 4, scUpperRight);    

	/* Create a child image from the child1 */
	child1 = vgChildImage(mobile_man, 32, 32, 20, 20);
	child2 = vgChildImage(child1, 0, 0, 16, 16);
    parent3 = vgGetParent(child2);

    if (parent3 != child1)
    {
		return CT_ERROR;
    }

    vgClearImage(child2, 0, 0, 10, 10);
    vgDrawImage(mobile_man);
    vgDrawImage(child1);

    vgDestroyImage(mobile_man);
    vgDestroyImage(child1);
    vgDestroyImage(child2);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_TEST_BUFFER();    
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

