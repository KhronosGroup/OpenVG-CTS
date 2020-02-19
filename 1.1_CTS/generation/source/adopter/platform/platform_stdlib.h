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

#ifndef PLATFORM_STDLIB_H
#define PLATFORM_STDLIB_H

#ifdef __cplusplus 
extern "C" { 
#endif

/*
** To be adapted to target platform.
*/

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <direct.h>
#endif

#ifndef ANSWER_DEFAULT_DIR
#define ANSWER_DEFAULT_DIR               "../../../../data/answer"
#endif
#ifndef INFO_DEFAULT_DIR
#define INFO_DEFAULT_DIR                 "../../../../data/info"
#endif
#define TEST_OPTION_VGU                  1

/* stdarg */
#define VA_ARG(arg, type)                va_arg((arg), type)
#define VA_END(arg)                      va_end((arg))
#define VA_LIST                          va_list
#define VA_START(arg, format)            va_start((arg), (format))

/* stdio */
typedef FILE                            *FILEHANDLE;
#define FCLOSE                           fclose
#define FEOF                             feof
#define FFLUSH                           fflush
#define FOPEN                            fopen
#define FPUTS                            fputs
#define PUTS                             puts
#define PRINTF                           printf
#define FPRINTF                          fprintf
#define SPRINTF                          sprintf
#define VPRINTF                          vprintf
#define VSPRINTF                         vsprintf
#define FSCANF                           fscanf
#define SSCANF                           sscanf
#define FWRITE                           fwrite
#ifdef WIN32
#define MKDIR                            mkdir
#else
#define MKDIR(x)                         mkdir(x, 0777)
#endif
#define RMDIR                            rmdir
/* stdlib */
#define EXIT                             exit
#define FREE                             free
#define MALLOC                           malloc
#define MEMCPY                           memcpy
#define MEMSET                           memset

/* string */
#define STRCMP                           strcmp
#define STRCPY                           strcpy
#define STRLEN                           strlen
#define STRSTR                           strstr
#define STRCAT                           strcat
#define ITOA                             itoa
#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* PLATFORM_STDLIB_H */
