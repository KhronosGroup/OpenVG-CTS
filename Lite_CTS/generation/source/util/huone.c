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

CT_Result SaveValueFile (VGint count, VGfloat* values, CT_File *AnsFile)
{
    VGint i;
    FILEHANDLE file;
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };
    CT_ValueFileHeader header;
    VGfloat* data;
    
    AnsFile->type = FILE_DAT_TYPE;
    SPRINTF(name, "%s.dat", AnsFile->filename );    

    /* header */
    header.errorcode = vgGetError();
    header.count = count;

    /* data */
    data = values;
    
    file = FOPEN(name, "wt");

    if (file == NULL) {
        return CT_ERROR;
    }

    FPRINTF (file, "%d\n", header.errorcode);
    FPRINTF (file, "%d\n", header.count);
    for (i=0; i<header.count; i++) {
        FPRINTF (file, "%f ", data[i]);
    }

    FCLOSE(file);
    return CT_NO_ERROR;
}

CT_Result SaveImageFile(VGint x, VGint y, VGint width, VGint height, CT_File *AnsFile)
{
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };

    AnsFile->type = FILE_TGA_TYPE;
    SPRINTF(name, "%s.tga", AnsFile->filename );    

    return saveFramebufToTGA_by_HUONE(name, AnsFile->pMe, width, height);
}

