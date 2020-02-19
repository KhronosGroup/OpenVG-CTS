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

#ifndef __APP_H__
#define __APP_H__

#include <EGL/egl.h>
#include <VG/openvg.h>
#include <VG/vgu.h>

#define TK_MAX_CONFIG       100
#define CT_MAX_DRIVER       500

#define WINDSIZEX           64
#define WINDSIZEY           64

typedef enum {
    CT_NO_ERROR      = 0,
    CT_ERROR         = 1
} CT_Result;

/* Toolkit Configs Structure */
typedef struct _TK_ConfigsRec {
    long count;
    long conformantCount;
    long IDs[TK_MAX_CONFIG];
    long type[TK_MAX_CONFIG];
} TK_ConfigsRec;

typedef struct _TK_ConfigInfoRec {
    EGLint   configID;
    EGLint   rDepth;
    EGLint   gDepth;
    EGLint   bDepth;
    EGLint   aDepth;
    EGLint   lDepth;
    EGLint   maskSize;
    EGLint   cSpace;
    EGLint   alphaMult;
    EGLint   sampleBuffers;
    EGLint   samples;
} TK_ConfigInfoRec;

typedef struct _CT_DriverRec {
    VGbyte      code[10];
    CT_Result   (*func)();
    VGuint      nsubtests;
} CT_DriverRec;

typedef struct _CT_AppRec {
    char              title[80];
    char              name[80];
    char              version[40];
    char              date[40];
    VGint             verboseLevel;
    VGint             configID;

    TK_ConfigsRec     list;
    TK_ConfigInfoRec  info;

    NativeWindowType  native_window;
    NativeDisplayType native_display;

    EGLDisplay        egl_display;
    EGLSurface        egl_surface;
    EGLContext        egl_context;    

    VGint             testList[CT_MAX_DRIVER];   
    CT_DriverRec     *curDriver;
} CT_AppRec;

#ifdef __cplusplus 
extern "C" { 
#endif

#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* __APP_H__ */
