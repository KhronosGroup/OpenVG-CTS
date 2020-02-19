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

/*
 * K20201_ColorTransform_by_NVIDIA
 *
 * Tests the error conditions and consistency of setting/getting
 * VG_COLOR_TRANSFORM and VG_COLOR_TRANSFORM_VALUES. The resulting
 * DAT file contains a single value for each test case, telling
 * how many failures were detected.
 */

#include "../main.h"
#include "../util/util.h"

CT_Result K20201_ColorTransform_by_NVIDIA(CT_File *AnsFile)
{
    VGint       intValues[9];
    VGfloat     floatValues[9];
    VGfloat     results[6];
    int         i;

    /* Clear the results. */

    for (i = 0; i < (int)(sizeof(results) / sizeof(results[0])); i++)
        results[i] = 0.0f;

    /* 0. Failing vgSetiv() and vgSetfv() on VG_COLOR_TRANSFORM. */

    intValues[0] = VG_TRUE;
    floatValues[0] = (VGfloat)VG_TRUE;

    vgSetiv(VG_COLOR_TRANSFORM, 0, intValues);
    results[0] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM, 0, floatValues);
    results[0] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSetiv(VG_COLOR_TRANSFORM, 2, intValues);
    results[0] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM, 2, floatValues);
    results[0] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 1. Failing vgSeti() and vgSetf() on VG_COLOR_TRANSFORM_VALUES. */

    vgSeti(VG_COLOR_TRANSFORM_VALUES, 0);
    results[1] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSetf(VG_COLOR_TRANSFORM_VALUES, 0.0f);
    results[1] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 2. Failing vgSetiv() and vgSetfv() on VG_COLOR_TRANSFORM_VALUES. */

    vgSetiv(VG_COLOR_TRANSFORM_VALUES, 0, intValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 0, floatValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSetiv(VG_COLOR_TRANSFORM_VALUES, 7, intValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 7, floatValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSetiv(VG_COLOR_TRANSFORM_VALUES, 9, intValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 9, floatValues);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    vgSetiv(VG_COLOR_TRANSFORM_VALUES, 8, (const VGint*)0x03);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
    vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, (const VGfloat*)0x03);
    results[2] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* 3. Default values. */
    {
        static const VGint intDefValues[] =
        { 1, 1, 1, 1, 0, 0, 0, 0 };
        static const VGfloat floatDefValues[] =
        { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };

        results[3] += (vgGeti(VG_COLOR_TRANSFORM) != VG_FALSE) ? 1.0f : 0.0f;
        results[3] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        results[3] += (vgGetf(VG_COLOR_TRANSFORM) != (VGfloat)VG_FALSE) ? 1.0f : 0.0f;
        results[3] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        results[3] += (vgGetVectorSize(VG_COLOR_TRANSFORM_VALUES) != 8) ? 1.0f : 0.0f;
        results[3] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgGetiv(VG_COLOR_TRANSFORM_VALUES, 8, intValues);
        results[3] += (memcmp(intValues, intDefValues, sizeof(intDefValues)) != 0) ? 1.0f : 0.0f;
        results[3] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgGetfv(VG_COLOR_TRANSFORM_VALUES, 8, floatValues);
        results[3] += (memcmp(floatValues, floatDefValues, sizeof(floatDefValues)) != 0) ? 1.0f : 0.0f;
        results[3] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* 4. Succeeding vgSetiv() and vgSetfv() on VG_COLOR_TRANSFORM. */

    intValues[0] = VG_TRUE;
    vgSetiv(VG_COLOR_TRANSFORM, 1, intValues);
    results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[4] += (vgGeti(VG_COLOR_TRANSFORM) != VG_TRUE) ? 1.0f : 0.0f;
    results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

    floatValues[0] = (VGfloat)VG_FALSE;
    vgSetfv(VG_COLOR_TRANSFORM, 1, floatValues);
    results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[4] += (vgGeti(VG_COLOR_TRANSFORM) != VG_FALSE) ? 1.0f : 0.0f;
    results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

    /* 5. Setter/getter consistency on VG_COLOR_TRANSFORM_VALUES. */
    {
        static const VGint intNastyValues[] =
        { (VGint)0x80000000, -0x7fff0000, 0x7fff0000, -2, -1, 0, 1, 2 };
        static const VGfloat floatNastyValues[] =
        { 1.0e10f, -1.0e20f, 1.0e30f, -1.0e38f, -1.0e10f, 1.0e20f, -1.0e30f, 1.0e38f };

        vgSetiv(VG_COLOR_TRANSFORM_VALUES, 8, intNastyValues);
        results[5] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        vgGetiv(VG_COLOR_TRANSFORM_VALUES, 8, intValues);
        results[5] += (memcmp(intValues, intNastyValues, sizeof(intNastyValues)) != 0) ? 1.0f : 0.0f;
        results[5] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, floatNastyValues);
        results[5] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        vgGetfv(VG_COLOR_TRANSFORM_VALUES, 8, floatValues);
        results[5] += (memcmp(floatValues, floatNastyValues, sizeof(floatNastyValues)) != 0) ? 1.0f : 0.0f;
        results[5] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* Save the results. */

    return SaveValueFile(sizeof(results) / sizeof(results[0]), results, AnsFile);
}

