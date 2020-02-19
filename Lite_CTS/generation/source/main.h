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

#include "app.h"
#include "adopter/native/native.h"
#include "adopter/platform/platform.h"

#if !defined(ANSWER_DEFAULT_DIR) 
    #error ANSWER_DEFAULT_DIR is not defined (-DANSWER_DEFAULT_DIR="PathName")
#endif
#if !defined(INFO_DEFAULT_DIR) 
    #error INFO_DEFAULT_DIR is not defined (-DINFO_DEFAULT_DIR="PathName")
#endif
#if !defined(TEST_OPTION_VGU) 
    #error TEST_OPTION_VGU is not defined (-DTEST_OPTION_VGU=1 or 0)
#endif

#define CT_UNSPECIFIED          -99
#define CT_MAX_FILE_NAME        200

#define CT_RELEASE_TITLE        "OpenVG Lite Conformance Test"
#define CT_RELEASE_NAME         "OnDevice"
#define CT_RELEASE_VERSION      "1.1 Lite"
#define CT_RELEASE_DATE         "Not released"
#define CT_NULL                 101001

#define CT_MAX_SCISSOR_RECT     1
#define CT_MAX_DASH_COUNT       16
#define CT_MAX_COLOR_RAMP_STOPS 32

typedef struct _CT_FuncRec {
    char      name[30];
    long      number;
    CT_Result (*func)(void);          
} CT_FuncRec;

typedef enum {
    FILE_INVALID_TYPE = 0,
    FILE_DAT_TYPE     = 1,
    FILE_TGA_TYPE     = 2
} CT_FileType;

typedef struct _CT_File {
    CT_FileType type;
    VGbyte      filename[CT_MAX_FILE_NAME];
    CT_AppRec  *pMe;
} CT_File;

#ifdef __cplusplus 
extern "C" { 
#endif

/* main.c */
//extern void Output(VGint level, const VGbyte *format, ...);
//extern TK_ConfigInfoRec *GetConfigInfo( void );

/* driver.c */
extern CT_Result Driver(CT_AppRec *pMe);
extern CT_Result DriverSetup(CT_AppRec *pMe);
extern CT_Result DriverSetupName(CT_AppRec *pMe, VGbyte *code);
extern CT_Result DriverSetupFile(CT_AppRec *pMe, VGbyte *fileName);
extern CT_Result DriverSaveTestList(CT_AppRec *pMe, FILEHANDLE file);

#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* __MAIN_H__ */
