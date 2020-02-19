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

#ifndef __MAIN_H__
#define __MAIN_H__

#if !defined(ANSWER_DEFAULT_DIR) 
    #error ANSWER_DEFAULT_DIR is not defined (-DANSWER_DEFAULT_DIR="PathName")
#endif
#if !defined(INFO_DEFAULT_DIR) 
    #error INFO_DEFAULT_DIR is not defined (-DINFO_DEFAULT_DIR="PathName")
#endif
#if !defined(REFERENCE_DEFAULT_DIR) 
    #error REFERENCE_DEFAULT_DIR is not defined (-DREFERENCE_DEFAULT_DIR="PathName")
#endif
#if !defined(TEST_OPTION_VGU) 
    #error TEST_OPTION_VGU is not defined (-DTEST_OPTION_VGU=1 or 0)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WINDSIZEX               64
#define WINDSIZEY               64
#define CT_UNSPECIFIED          -99
#define CT_INVALID_SCORE        9999

#define CT_MAX_GROUP            20
#define CT_MAX_DRIVER           500
#define CT_MAX_CONFIG           100
#define CT_MAX_FILE_NAME        200

#define CT_RELEASE_TITLE        "OpenVG Conformance Test"
#define CT_RELEASE_NAME         "OnDevice"
#define CT_RELEASE_VERSION      "1.1 RC12"
#define CT_RELEASE_DATE         "13th December 2010"
#define CT_NULL                 101001

#define CT_MASK_TEST_CODE       'F'
#define CT_VGU_TEST_CODE        'M'

typedef enum {
    CT_NO_ERROR      = 0,
    CT_ERROR         = 1
} CT_Result;

typedef struct _CT_AppRec {
    char         title[80];
    char         name[80];
    char         version[40];
    char         date[40];
    long         verboseLevel;   
    long         configID;
} CT_AppRec;

typedef struct _CT_DriverRec {
    char         testCode[10];
    int          minValue;
    int          maxValue;
} CT_DriverRec;

typedef struct _CT_RatingFuncRec {
    const char    code[10];
    int          (*func)();
    unsigned int  nsubtests;
} CT_RatingFuncRec;

typedef struct _CT_ChannelRec {
    int id;
    int conformant;
    int rDepth;
    int gDepth;
    int bDepth;
    int aDepth;
    int lDepth;
    int maskSize;
    int cSpace;
    int sampleBuffers;
    int samples;
} CT_ChannelRec;

typedef struct _CT_ConfigRec {
    int num;
    CT_ChannelRec channel[CT_MAX_CONFIG];
} CT_ConfigRec;

typedef struct _CT_SummaryRec {
    int  index;
    int  subIndex;
    int  single;
    int  failed[CT_MAX_CONFIG][4];
    char fail[CT_MAX_CONFIG][4][CT_MAX_GROUP];
}CT_SummaryRec;

typedef struct _CT_FileRec {
    FILE *dat;
    FILE *tga;
} CT_File;

typedef enum {
    FILE_INVALID_TYPE = 0,
    FILE_DAT_TYPE     = 1,
    FILE_TGA_TYPE     = 2
} CT_FileType;

/* main.c */
extern CT_AppRec         app;
extern CT_ConfigRec      configRec;
extern CT_ChannelRec     channelInfo;
extern CT_SummaryRec     summaryInfo;
extern char              TestFileName[CT_MAX_FILE_NAME];

/* driver.c */
extern CT_Result Driver(void);
extern CT_Result DriverSetup(void);
extern CT_Result DriverSetupName(char *);
extern CT_Result DriverSetupFile(char *);
extern CT_Result DriverSetupInit(void);

#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* __MAIN_H__ */
