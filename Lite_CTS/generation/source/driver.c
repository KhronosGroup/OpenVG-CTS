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

#include "main.h"
#include "util/util.h"
#include "static/tests.h"

static VGint GetDriveSize( void )
{
    return ( sizeof(driver) / sizeof(CT_DriverRec) );
}

static VGint FindTestIndex(VGbyte *code)
{
    VGint i, count;

    count = GetDriveSize();

    for (i = 0; i < count; i++) {
        if (STRCMP(driver[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

CT_Result DriverSaveTestList(CT_AppRec *pMe, FILEHANDLE file)
{
    VGint i, count;

    FPRINTF(file, "#Test Lists\n");

    count = GetDriveSize();
    for (i = 0; i < count; i++) {
        FPRINTF(file, "%s\n", driver[i].code);
    }

    return CT_NO_ERROR;
}

CT_Result DriverSetup(CT_AppRec *pMe)
{
    VGint i, count;
    
    count = GetDriveSize();    

    for (i = 0; i < count; i++) {
        pMe->testList[i] = i;
    }

    pMe->testList[i] = CT_NULL;
    
    return CT_NO_ERROR;
}

CT_Result DriverSetupName(CT_AppRec *pMe, VGbyte *code)
{
    VGint index;

    index = FindTestIndex(code);
    
    if (index == -1) {
        return CT_ERROR;
    } 
    else {
        pMe->testList[0] = index;
        pMe->testList[1] = CT_NULL;
        
        return CT_NO_ERROR;
    }
}

CT_Result DriverSetupFile(CT_AppRec *pMe, VGbyte *fileName)
{
    FILEHANDLE file;
    VGbyte     buf[82];
    VGint      index, i;

    file = FOPEN(fileName, "rt");
    
    if (file != NULL) {
        i = 0;
        
        while ( !FEOF(file) ) {
            FSCANF(file, "%[^\r\n]", buf);
            
            if (buf[0] != '#') {
                index = FindTestIndex(buf);

                if (index == -1) {
                    Output(pMe, 1, "Cannot find test '%s'.\n", buf);
                    FCLOSE(file);
                    return CT_ERROR;
                } 
                else {
                    pMe->testList[i++] = index;
                }
            }
            FSCANF(file, "%[\r]", buf);
            FSCANF(file, "%[\n]", buf );
        }
        pMe->testList[i] = CT_NULL;
        FCLOSE(file);
        
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

static CT_Result DriverExec(CT_AppRec *pMe, CT_Result (*Func)(), VGuint subtest)
{
    CT_DriverRec *curDriver;
    CT_Result     result = CT_NO_ERROR;
    VGbyte        dir[CT_MAX_FILE_NAME] = {0,};
    VGbyte        extension[10] = {0, };
    CT_File       AnsFile;

    curDriver = pMe->curDriver;
    AnsFile.pMe = pMe;
    AnsFile.type = FILE_INVALID_TYPE;
    if (curDriver->nsubtests > 0) {
        GetAnswerFilename(pMe, AnsFile.filename, subtest);
    }
    else {
        GetAnswerFilename(pMe, AnsFile.filename, -1);
    }
    result = (*Func)(&AnsFile, subtest);

    if ( result == CT_NO_ERROR ) {
        if ( curDriver->nsubtests > 0 ) {
            Output(pMe, 2, "        %s_%04d_Ans", curDriver->code, subtest );
        }
        else {
            Output(pMe, 2, "        %s_Ans", curDriver->code );
        }

        MakeExtension(extension, AnsFile.type);
        if ( curDriver->nsubtests == 0 )
            Output(pMe, 2, "....." );

        if (ConformFile(&AnsFile) == CT_ERROR) {
            Output(pMe, 2, "%s .......... Failed\n", extension);     
            result = CT_ERROR;
        }
        else {
            Output(pMe, 2, "%s .......... Done\n", extension); 
        }
    }
    else {
        Output(pMe, 2, "        %s_%04d may encounter error .......... Failed\n", curDriver->code, subtest );
    }

    return result;
}

CT_Result Driver(CT_AppRec *pMe)
{
    CT_DriverRec *curDriver;
    CT_Result     result = CT_NO_ERROR;
    CT_Result     pass1 = CT_NO_ERROR;
    CT_Result     pass2 = CT_NO_ERROR;
    VGint         index;
    VGint         count;
    VGuint        subtest;

    count = GetDriveSize();
    MKDIR( ANSWER_DEFAULT_DIR );
    
    for (index = 0; pMe->testList[index] != CT_NULL; index++) {
        pMe->curDriver = (CT_DriverRec *)(&driver[pMe->testList[index]]);
        curDriver = pMe->curDriver;

        if ( curDriver->func == NULL )
            continue;

        /* Bugzilla Bug 3757 - F20102 relies on VG_RENDERING_QUALITY_BETTER
           and specific coverage algorithm */
        if ( STRCMP(curDriver->code, "F20102") == 0 )
            goto TestSkip;

        /* Bugzilla Bug 3505 - H30206 require dithering for vgCopyImage */
        if ( STRCMP(curDriver->code, "H30206") == 0 )
            goto TestSkip;
        
        /* Bugzilla Bug 3538 - Tie breaking detection for MSAA configs */
        if ( pMe->info.sampleBuffers != 0 ) {
            if ( STRCMP(curDriver->code, "B10101") == 0 ||
                 STRCMP(curDriver->code, "G30107") == 0 ||
                 STRCMP(curDriver->code, "H10402") == 0 ) {
                Output(pMe, 1, "        %s Test is Skipped in MSAA config.\n", curDriver->code);    
                goto TestSkip;
            }
        }
        
        /* Bugzilla Bug 5675 - B10109 invalid in MSAA 5551 and 565 configs */
        if ( pMe->info.sampleBuffers != 0 ) {
            if ( STRCMP(curDriver->code, "B10109") == 0 ) {
                Output(pMe, 1, "        %s Test is Skipped in MSAA config.\n", curDriver->code);
                goto TestSkip;
            }
        }

        /* for Final RC Build - disable test case B10108 in all MSAA configs */
        if ( pMe->info.sampleBuffers != 0 ) {
            if ( STRCMP(curDriver->code, "B10108") == 0 ) {
                Output(pMe, 1, "        %s Test is Skipped in MSAA config.\n", curDriver->code);    
                goto TestSkip;
            }
        }

        if ( curDriver->code[0] == 'N' ) { /* if multisampling test */
            if ( pMe->info.sampleBuffers == 0 ) { /* not support MSAA */
                Output(pMe, 0, "        The config does not support MSAA Test.\n");
                Output(pMe, 1, "    [%c] Group Test skipped.\n", curDriver->code[0] );
                continue;
            }
        }

        if ( curDriver->nsubtests > 0 )
        {
            for ( subtest = 0; subtest < curDriver->nsubtests; subtest++ )
            {
                if ( vgGetError() != VG_NO_ERROR )
                    return CT_ERROR;

                result = DriverExec(pMe, curDriver->func, subtest);

                if ( result == CT_ERROR ) { 
                    pass1 = CT_ERROR;
                    pass2 = CT_ERROR;
                }
                
                if ( StateReset(pMe) == CT_ERROR || StateCheck(pMe) == CT_ERROR ) {
                    Output(pMe, 0, "Context Parameter values not restored to default condition.\n");
                    Output(pMe, 0, "Cannot continue until default state test passes.\n\n");

                    EXIT(EXIT_FAILURE);
                }
            }
        }
        else
        {
            if ( vgGetError() != VG_NO_ERROR )
                return CT_ERROR;

            result = DriverExec(pMe, curDriver->func, 0);

            if ( result == CT_ERROR ) { 
                pass1 = CT_ERROR;
                pass2 = CT_ERROR;
            }
            
            if ( StateReset(pMe) == CT_ERROR || StateCheck(pMe) == CT_ERROR ) {
                Output(pMe, 0, "Context Parameter values not restored to default condition.\n");
                Output(pMe, 0, "Cannot continue until default state test passes.\n\n");

                EXIT(EXIT_FAILURE);
            }            
        }
        
TestSkip:
        if ( pMe->testList[index+1] == CT_NULL || curDriver->code[0] != driver[pMe->testList[index+1]].code[0] ) {    /* Group Test done */
            if (pass1 == CT_ERROR) {
                Output(pMe, 1, "    [%c] Group Test Result Generation Failed.\n", curDriver->code[0] );
                pass1 = CT_NO_ERROR;
            }
            else {
                    Output(pMe, 1, "    [%c] Group Test Result Generation Succeeded.\n", curDriver->code[0] );
            }
        }
    }

    return pass2;
}

