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

#ifndef PLATFORM_MATH_H
#define PLATFORM_MATH_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include <stdlib.h>
#include <math.h>

#ifdef  M_PI
#define PI          ((float)M_PI)
#else
#define PI          ((float)3.14159265358979323846)
#endif

#ifdef  M_LN2
#define LN2         ((float)M_LN2)
#else
#define LN2         ((float)0.69314718)
#endif

#define MIN(x, y)   (((x) < (y)) ? (x) : (y))
#define MAX(x, y)   (((x) < (y)) ? (y) : (x))

#define XTOF(x)     (LDEXP((float)(x), -16))

/* stdlib */
#define ITOF(i)     ((float)(VGint)(i))
#define FTOI(x)     ((int) (x))
#define ATOF(s)     ((float) atof((s)))
#define ATOI(s)     (atoi((s)))

/* math */
#define ABS(x)      ((float) fabs((x)))
#define ADD(x, y)   ((x) + (y))
#define COS(x)      ((float) cos((x)))
#define COSD(x)     (COS((PI/180.0f)*(x)))
#define DIV(x, y)   ((x) / (y))
#define EXP(x)      ((float) exp((x)))
#define FLOOR(x)    ((float) floor((x)))
#define LDEXP(x, y) ((float) ldexp((x), (y)))
#define LOG(x)      ((float) log((x)))
#define LOG2(x)     ((float) (log((x))/LN2))
#define MUL(x, y)   ((x) * (y))
#define POW(x, y)   ((float) pow((x), (y)))
#define SIN(x)      ((float) sin((x)))
#define SIND(x)     (SIN((PI/180.0f)*(x)))
#define SUB(x, y)   ((x) - (y))
#define SQRT(x)     ((float) sqrt((x)))
#define RAND()      (rand())
#define SRAND(x)    (srand(x))

#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* PLATFORM_MATH */
