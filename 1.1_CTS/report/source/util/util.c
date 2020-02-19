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

#include <stdarg.h>

#include "../main.h"
#include "util.h"

void Output(int level, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    if (app.verboseLevel >= level) {
        vprintf(format, args);
        fflush(stdout);
    }
    va_end(args);
}

void MakeExtension(char *extension, CT_FileType fileType)
{
    if ( fileType == FILE_DAT_TYPE )
        strcpy( extension, "DAT" );
    else if ( fileType == FILE_TGA_TYPE )
        strcpy( extension, "TGA" );

    return;
}

CT_Result OpenFiles(CT_File *AnsFile, CT_File *RefFile, char *AnsFileName, char *RefFileName, CT_FileType *fileType) 
{
    CT_Result result = CT_NO_ERROR;

    char datAnsName[CT_MAX_FILE_NAME] = {0,};
    char tgaAnsName[CT_MAX_FILE_NAME] = {0,};

    char datRefName[CT_MAX_FILE_NAME] = {0,};
    char tgaRefName[CT_MAX_FILE_NAME] = {0,};    

    (*fileType) = FILE_INVALID_TYPE;

    AnsFile->dat = NULL;
    AnsFile->tga = NULL;

    RefFile->dat = NULL;
    RefFile->tga = NULL;

    sprintf(datAnsName, "%s.dat", AnsFileName);
    sprintf(datRefName, "%s.dat", RefFileName);
    sprintf(tgaAnsName, "%s.tga", AnsFileName);
    sprintf(tgaRefName, "%s.tga", RefFileName);

    AnsFile->dat = fopen (datAnsName, "rt");
    RefFile->dat = fopen (datRefName, "rt");
    AnsFile->tga = fopen (tgaAnsName, "rb");
    RefFile->tga = fopen (tgaRefName, "rb");

    if ( RefFile->dat ) {
        (*fileType) = FILE_DAT_TYPE;
        if ( AnsFile->dat == NULL )
            result = CT_ERROR;
    }     
    else if ( RefFile->tga ) {
        (*fileType) = FILE_TGA_TYPE;
        if ( AnsFile->tga == NULL )
            result = CT_ERROR;
    }        

    return result;
}

void CloseFiles (CT_File AnsFile, CT_File RefFile)
{
    if (AnsFile.dat)
        fclose(AnsFile.dat);
     if (AnsFile.tga)
        fclose(AnsFile.tga);
        
    if (RefFile.dat)
        fclose(RefFile.dat);
    if (RefFile.tga)
        fclose(RefFile.tga);        
}
