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
 * G70109_PathError_by_NVIDIA
 *
 * Tests the error conditions of the path API functions. The test
 * performs a number of API calls with both valid and invalid input,
 * and checks that the results and error codes are as expected. The
 * resulting DAT file contains a single value for each test case,
 * telling how many failures were detected.
 */

#include "../main.h"
#include "../util/util.h"

typedef union
{
    VGfloat f;
    VGuint u;
} CTFloatInt;

CT_Result G70109_PathError_by_NVIDIA(CT_File *AnsFile)
{
    VGfloat results[12];
    VGPath  vgPath;
    int     i;

    /* Clear the results. */

    for (i = 0; i < (int)(sizeof(results) / sizeof(results[0])); i++)
        results[i] = 0.0f;

    /* Create the temporary path. */

    vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_S_8, 2.0f, -1.0f, 0, 0, 0xabc);

    /* 0. Init
     * Check that the initialization succeeded. */

    results[0] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[0] += (vgPath == VG_INVALID_HANDLE) ? 1.0f : 0.0f;

    /* 1. vgGetParameter()
     * Check that path queries return the correct values. */
    {
        VGint   type  = vgGetParameteri(vgPath, VG_PATH_DATATYPE);
        VGfloat scale = vgGetParameterf(vgPath, VG_PATH_SCALE);
        VGfloat bias  = vgGetParameterf(vgPath, VG_PATH_BIAS);

        results[1] += (type != VG_PATH_DATATYPE_S_8) ? 1.0f : 0.0f;
        results[1] += (scale != 2.0f) ? 1.0f : 0.0f;
        results[1] += (bias != -1.0f) ? 1.0f : 0.0f;
        results[1] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* 2. vgGetPathCapabilities()
     * Check that the call returns correct capabilities. */

    results[2] += (vgGetPathCapabilities(vgPath) != 0xabc) ? 1.0f : 0.0f;
    results[2] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

    /* 3. vgCreatePath()
     * Check that zero scale produces VG_ILLEGAL_ARGUMENT_ERROR. */
    {
        VGPath vgTmpPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            VG_PATH_DATATYPE_F, 0.0f, 0.0f, 0, 0, 0);

        results[3] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;
        results[3] += (vgTmpPath != VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    }

    /* 4. vgCreatePath()
     * Check that negative scale does not produce an error. */
    {

       
        VGPath vgTmpPath;
        vgTmpPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            VG_PATH_DATATYPE_F, -1.0f, 0.0f, 0, 0, 0);
        vgDestroyPath(vgTmpPath);

        results[4] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        results[4] += (vgTmpPath == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    }


    /* 5. vgCreatePath()
     * Check that negative capacity hints do not produce an error. */
    {
        VGPath vgTmpPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            VG_PATH_DATATYPE_F, 1.0f, 0.0f, -123, -456, 0);
        vgDestroyPath(vgTmpPath);

        results[5] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        results[5] += (vgTmpPath == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
    }

    /* 6. vgCreatePath()
     * Check that unsupported capability bits are ignored. */
    {
        VGPath vgTmpPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
            VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, 0xdeadbeef);
        VGbitfield caps = vgGetPathCapabilities(vgTmpPath);
        vgDestroyPath(vgTmpPath);

        results[6] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
        results[6] += (vgTmpPath == VG_INVALID_HANDLE) ? 1.0f : 0.0f;
        results[6] += (caps != 0xeef) ? 1.0f : 0.0f;
    }

    /* 7. vgClearPath()
     * Check that unsupported capability bits are ignored. */

    vgClearPath(vgPath, 0xdeadbfef);
    results[7] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[7] += (vgGetPathCapabilities(vgPath) != 0xfef) ? 1.0f : 0.0f;

    /* 8. vgRemovePathCapabilities()
     * Check that unsupported capability bits are ignored. */

    vgRemovePathCapabilities(vgPath, 0xcafeb015);
    results[8] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    results[8] += (vgGetPathCapabilities(vgPath) != 0xfea) ? 1.0f : 0.0f;

    /* 9. vgAppendPathData()
     * Check that the call does not produce an error. */
    {
        static const VGubyte pathCmd[] = { VG_MOVE_TO_ABS };
        static const VGbyte pathVal[] = { 0, 0 };

        vgAppendPathData(vgPath, sizeof(pathCmd), pathCmd, pathVal);
        results[9] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* 10. vgPointAlongPath()
     * Check that null x/y/tanX/tanY do not produce an error. */
    {
        VGfloat tmp;

        vgPointAlongPath(vgPath, 0, 1, 0.0f, NULL, &tmp, &tmp, &tmp);
        results[10] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgPointAlongPath(vgPath, 0, 1, 0.0f, &tmp, NULL, &tmp, &tmp);
        results[10] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgPointAlongPath(vgPath, 0, 1, 0.0f, &tmp, &tmp, NULL, &tmp);
        results[10] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;

        vgPointAlongPath(vgPath, 0, 1, 0.0f, &tmp, &tmp, &tmp, NULL);
        results[10] += (vgGetError() != VG_NO_ERROR) ? 1.0f : 0.0f;
    }

    /* 11. vgDrawPath()
     * Check that paintModes=0 produces VG_ILLEGAL_ARGUMENT_ERROR. */

    vgDrawPath(vgPath, 0);
    results[11] += (vgGetError() != VG_ILLEGAL_ARGUMENT_ERROR) ? 1.0f : 0.0f;

    /* Clean up and save the results. */

    if (vgPath != VG_INVALID_HANDLE)
        vgDestroyPath(vgPath);

    return SaveValueFile(sizeof(results) / sizeof(results[0]), results, AnsFile);
}

