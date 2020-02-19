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
#include "tests.h"

static long testList[CT_MAX_DRIVER];

static CT_DriverRec  driver[CT_MAX_DRIVER];
static CT_DriverRec *curDriver;

static CT_Result pass1 = CT_NO_ERROR;
static CT_Result pass2 = CT_NO_ERROR;

static int GetDriveSize( void )
{
    return ( sizeof(func) / sizeof(CT_RatingFuncRec) );
}

static int FindTestIndex(char *code)
{
    long i, count;
    char temp[7]= { 0, };

    count = GetDriveSize();

    sscanf (code, "%6c", temp);

    for (i = 0; i < count; i++) {
        if (strcmp(driver[i].testCode, temp) == 0) {
            return i;
        }
    }
    return -1;
}

CT_Result DriverSetup(void)
{
    long i, count;

    count = GetDriveSize();    

    for (i = 0; i < count; i++) {
        testList[i] = i;
    }

    testList[i] = CT_NULL;
    
    return CT_NO_ERROR;
}

CT_Result DriverSetupName(char *code)
{
    long index;

    index = FindTestIndex(code);

    if (!TestFileName[0] && code)
        strcat(TestFileName, code);

    if (index == -1) {
        return CT_ERROR;
    } 
    else {
        testList[0] = index;
        testList[1] = CT_NULL;
        
        return CT_NO_ERROR;
    }
}

CT_Result DriverSetupFile(char *fileName)
{
    FILE* file;
    char       buf[82];
    char       code[7] = { 0, };
    int         min, max;
    long       i, index;

    file = fopen(fileName, "rt");
    
    if (file != NULL) {
        i = 0;
        index = 0;
        while ( !feof(file) ) {
            fscanf(file, "%[^\n]", buf);
            
            if (buf[0] != '#') {
                sscanf (buf, "%6c %d %d", code, &min, &max);
                strcpy (driver[index].testCode, code);
                driver[index].minValue = min;
                driver[index].maxValue = max; 


                testList[i++] = index++;
            }
            fscanf(file, "%[\n]", buf);
        }
        testList[i] = CT_NULL;
        fclose(file);
        
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

CT_Result DriverSetupInit(void)
{
    FILE* file;
    char       buf[82];
    char       code[7] = { 0, };
    int         min, max;
    long       i, index;

    /* Temporary file open for driver init */
    file = fopen("./ratingtables/888800.dat", "rt");
    
    if (file != NULL) {
        i = 0;
        index = 0;
        while ( !feof(file) ) {
            fscanf(file, "%[^\n]", buf);
            
            if (buf[0] != '#') {
                sscanf (buf, "%6c %d %d", code, &min, &max);
                strcpy (driver[index].testCode, code);
                driver[index].minValue = min;
                driver[index].maxValue = max; 


                testList[i++] = index++;
            }
            fscanf(file, "%[\n]", buf);
        }
        testList[i] = CT_NULL;
        fclose(file);
        
        return CT_NO_ERROR;
    }
    else {
        return CT_ERROR;
    }
}

static void DriverExec()
{
    CT_File     AnsFile, RefFile;
    CT_FileType fileType;
    CT_Result   result;
    
    char    TestName[CT_MAX_FILE_NAME];
    char    AnsFileName[CT_MAX_FILE_NAME];
    char    RefFileName[CT_MAX_FILE_NAME];
    char    surface[4][15] = { "sRGB_NONPRE","lRGB_NONPRE","sRGB_PRE", "lRGB_PRE" };
    
    int     score;
    long    i=0, index=0;
    int     count;
    unsigned int subtest;

    count = GetDriveSize();

    summaryInfo.subIndex = 0;
    for ( index = 0; testList[index] != CT_NULL; index++ ) {
        curDriver = &driver[testList[index]];

        for (i = 0; i < count; i++) {
            if (strncmp(func[i].code, curDriver->testCode, 6*sizeof(char)) == 0)
                break;
        }
        if ( i == count ) {
            pass2 = CT_ERROR;
            Output(0, "[%s] is not exist in RatingTable.dat.\n", curDriver->testCode );
            summaryInfo.fail[summaryInfo.index][channelInfo.cSpace][summaryInfo.subIndex] = curDriver->testCode[0];
            summaryInfo.subIndex++;
            summaryInfo.failed[summaryInfo.index][channelInfo.cSpace]++;
            return;
        }

        /* Bugzilla Bug 3757 - F20102 relies on VG_RENDERING_QUALITY_BETTER
           and specific coverage algorithm */
        if ( strcmp(curDriver->testCode, "F20102") == 0 )
            goto TestSkip;

        /* Bugzilla Bug 3505 - H30206 require dithering for vgCopyImage */
        if ( strcmp(curDriver->testCode, "H30206") == 0 )
            goto TestSkip;

        /* Bugzilla Bug 3538 - Tie breaking detection for MSAA configs */
        if ( channelInfo.sampleBuffers != 0 ) {
            if ( strcmp(curDriver->testCode, "B10101") == 0 ||
                 strcmp(curDriver->testCode, "G30107") == 0 ||
                 strcmp(curDriver->testCode, "H10402") == 0 ) {
                Output(1, "        %s Test is Skipped in MSAA config.\n", curDriver->testCode);         
                goto TestSkip;
            }
        }
        
        /* Bugzilla Bug 5675 - B10109 invalid in MSAA 5551 and 565 configs */
        if ( channelInfo.sampleBuffers != 0 ) {
            if ( strcmp(curDriver->testCode, "B10109") == 0 ) {
                Output(1, "        %s Test is Skipped in MSAA config.\n", curDriver->testCode);
                goto TestSkip;
            }
        }

        /* for Final RC Build - disable test case B10108 in all MSAA configs */
        if ( channelInfo.sampleBuffers != 0 ) {
            if ( strcmp(curDriver->testCode, "B10108") == 0 ) {
                Output(1, "        %s Test is Skipped in MSAA config.\n", curDriver->testCode);    
                goto TestSkip;
            }
        }

        if ( curDriver->testCode[0] == 'N' ) { /* if multisampling test */
            if ( channelInfo.sampleBuffers == 0 ) { /* not support MSAA */
                Output(0, "        The config does not support MSAA Test.\n");
                Output(1, "    [%c] Group Test skipped.\n", curDriver->testCode[0] );
                continue;
            }
        }

        /* For each subtest (if test does not have any subtests do this once)  */
        subtest = 0;
        do {
            memset(TestName, 0, 100);
            memset(AnsFileName, 0, 100);
            memset(RefFileName, 0, 100);

            sprintf(TestName, "%s", curDriver->testCode);

            strcat(AnsFileName, ANSWER_DEFAULT_DIR);
            sprintf(AnsFileName, "%s/%d/%s/%s", AnsFileName, channelInfo.id, surface[channelInfo.cSpace], curDriver->testCode);
    
            strcat(RefFileName, REFERENCE_DEFAULT_DIR);
            sprintf (RefFileName, "%s/%d%d%d%d%d%d/%s/%s", RefFileName, channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth, channelInfo.sampleBuffers, surface[channelInfo.cSpace], curDriver->testCode);

            if ( func[i].nsubtests > 0 ) {
                sprintf(AnsFileName, "%s_%04d", AnsFileName, subtest);
                sprintf(RefFileName, "%s_%04d", RefFileName, subtest);
                sprintf(TestName, "%s_%04d", TestName, subtest);
            }
            if ( curDriver->testCode[0] == CT_MASK_TEST_CODE ) {
                switch( channelInfo.maskSize ) {
                    case 0 :
                        sprintf(RefFileName, "%s_0", RefFileName, channelInfo.maskSize);
                        break;
                        
                    case 1 :
                    case 2 :
                    case 4 :
                    case 8 :
                        break;
                        
                    default:
                        break;
                }
            }

            sprintf(AnsFileName, "%s_Ans", AnsFileName);
            sprintf(RefFileName, "%s_Ref", RefFileName);

            result = OpenFiles(&AnsFile, &RefFile, AnsFileName, RefFileName, &fileType);

            if ( fileType == FILE_INVALID_TYPE ) {
                Output(2, "        %s Test failed.[No valid reference file found]\n", TestName );
                pass1 = CT_ERROR;
                pass2 = CT_ERROR;
            }
            else if ( result == CT_ERROR ) {
                Output(2, "        %s Test failed.[No valid answer file found]\n", TestName );
                pass1 = CT_ERROR;
                pass2 = CT_ERROR;
            }
            else {
                char extension[10] = {0, };
                
                MakeExtension(extension, fileType);
        
                score = func[i].func(AnsFile, RefFile);
            
                if (score < curDriver->minValue || score > curDriver->maxValue) { 
                    Output(2, "        %s Test failed.[format:%s score:%d min:%d max:%d]\n", TestName, extension, score, curDriver->minValue, curDriver->maxValue); 
                    pass1 = CT_ERROR;
                    pass2 = CT_ERROR;
                } 
                else { 
                    Output(2, "        %s Test passed.[format:%s score:%d min:%d max:%d]\n", TestName, extension, score, curDriver->minValue, curDriver->maxValue); 
                }
            }

            CloseFiles(AnsFile, RefFile);
            subtest++;
        } while ( subtest < func[i].nsubtests );
        
TestSkip:
        if ( testList[index+1] == CT_NULL || &func[i+1] == NULL || func[i].code[0] != func[i+1].code[0] ) {
            if (pass1 == CT_ERROR) {
                Output(1, "    [%c] Group Test failed.\n", curDriver->testCode[0] );
                pass1 = CT_NO_ERROR;
                summaryInfo.fail[summaryInfo.index][channelInfo.cSpace][summaryInfo.subIndex] = curDriver->testCode[0];
                summaryInfo.subIndex++;
                summaryInfo.failed[summaryInfo.index][channelInfo.cSpace]++;
            } 
            else {
                Output(1, "    [%c] Group Test passed.\n", curDriver->testCode[0] );
            }
        }
    }
}

CT_Result Driver(void)
{
    CT_Result result;
    
    Output(1, "Score Report\n" );

    DriverExec();

    result = pass2;
    pass2 = CT_NO_ERROR;
    
    return result;
}

