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

CT_Result J30201_FilterLookupTable_by_HUONE (CT_File *AnsFile)               
{
    VGImage parent,child1,child2;
    VGfloat clearColor[] = {0.0f, 0.0f, 0.0f, 1.0f};/* black color */
    VGubyte *data;
    VGuint  LUT[256];
   
    VGint i;

    data = (VGubyte *)MALLOC(sizeof(VGubyte)*WINDSIZEX*WINDSIZEY);
    if(!data)
        return CT_ERROR;
    
    for (i=0;i<WINDSIZEX*WINDSIZEY;i++) {
        data[i] = 0x00;
    }
    
    for (i=0; i<256; i++) {
        if ( i == 0 )
            LUT[0] = 0x80000080;            
        else
            LUT[i] = 0xFFFFFFFF;
    }

    parent = vgCreateImage( VG_A_8, 64, 64, VG_IMAGE_QUALITY_NONANTIALIASED );
    if ( parent == VG_INVALID_HANDLE )
        return CT_ERROR;

    vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
    vgClear(0, 0, WINDSIZEX, WINDSIZEY);
    
    vgImageSubData(parent, data, WINDSIZEX, VG_A_8, 0, 0, WINDSIZEX, WINDSIZEY);
    child1 = vgChildImage(parent, 0, 0, 32, 64);
    child2 = vgChildImage(parent, 32, 0, 32, 64);
        
    vgLookupSingle(child2, child1, LUT, VG_GREEN, VG_FALSE, VG_TRUE);

    if (vgGetError() == VG_NO_ERROR) {
        DISPLAY_IMAGE(parent);

        vgDestroyImage(parent);
        vgDestroyImage(child1);
        vgDestroyImage(child2);

        FREE(data);
        return CT_NO_ERROR;
    }
    else {
        vgDestroyImage(parent);
        vgDestroyImage(child1);
        vgDestroyImage(child2);

        FREE(data);
        return CT_ERROR;
    }
}



