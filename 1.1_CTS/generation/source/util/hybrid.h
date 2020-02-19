#ifndef __HYBRID_H__
#define __HYBRID_H__

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

/* Use this to output images with the correct function */
#define DISPLAY_TEST_BUFFER()  SaveFrameBufToTGAFile_by_HYBRID(WINDSIZEX, WINDSIZEY, AnsFile)
#define DISPLAY_SUBTEST_BUFFER(subtest) SaveSubtestFrameBufToTGAFile_by_HYBRID(subtest, WINDSIZEX, WINDSIZEY, AnsFile)
#define DISPLAY_IMAGE(image)   SaveImageToTGAFile_by_HYBRID(image, AnsFile)
#define SAVE_SUBTEST_IMAGE(subtest, image)   SaveSubtestImageToTGAFile_by_HYBRID(subtest, image, AnsFile)

#ifdef __cplusplus 
extern "C" { 
#endif

extern CT_Result   SaveFrameBufToTGAFile_by_HYBRID(VGint width, VGint height, CT_File *AnsFile);
extern CT_Result   SaveImageToTGAFile_by_HYBRID(VGImage image, CT_File *AnsFile);
extern CT_Result   SaveSubtestImageToTGAFile_by_HYBRID(VGuint subtest, VGImage image, CT_File *AnsFile);
extern CT_Result   SaveSubtestFrameBufToTGAFile_by_HYBRID(VGuint subtest, VGint width, VGint height, CT_File *AnsFile);
extern void        DrawRect_by_HYBRID(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height);
extern void        DrawEllipse_by_HYBRID(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height);

extern CT_Result   saveFramebufToTGA_by_HUONE(const char* filename, CT_AppRec *pMe, int width, int height);
#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif

