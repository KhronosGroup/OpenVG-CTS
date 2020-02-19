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
 * A40101_ErrorOrdering_by_NVIDIA
 *
 * Tests that the error conditions listed in the
 * specification are accounted for by the implementation,
 * and that existing error codes are never overridden
 * by a new error, as stated in spec chapter 4.1:
 *
 * "vgGetError returns the oldest error code provided
 *  by an API call on the current context since the
 *  previous call to vgGetError on that context (or
 *  since the creation of the context)."
 *
 * The test is performed in two passes. The first pass
 * loops through the error conditions, and checks that
 * vgGetError() returns the correct error code after
 * each erroneous API call.
 *
 * The second pass loops through the same error
 * conditions, but makes two erroneous API calls instead
 * of one. The first call is selected so that the two
 * calls produce different error codes. After making both
 * calls, the test calls vgGetError() and checks that the
 * returned error code matches the first call.
 *
 * The result file contains a single number for each
 * error condition, telling total number of failures
 * that were detected.
 */

#include "../main.h"
#include "../util/util.h"

/* Set to 1 to enable detailed printouts of the failures. */
#define CT_ENABLE_INFO 0

#if (CT_ENABLE_INFO != 0)
#   define CT_INFO(X) PRINTF X
#else
#   define CT_INFO(X)
#endif

static VGboolean call_vgSetXxx(VGErrorCode errorCode, int errorCase)
{
    VGint invalidInt = 0xdeadbeef;
    VGfloat invalidFloat = (VGfloat)invalidInt;

    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetf(invalidInt, invalidFloat); break;
        case 1:  vgSeti(invalidInt, invalidInt); break;
        case 2:  vgSetfv(invalidInt, 1, &invalidFloat); break;
        case 3:  vgSetiv(invalidInt, 1, &invalidInt); break;
        case 4:  vgSetf(VG_CLEAR_COLOR, invalidFloat); break;
        case 5:  vgSeti(VG_CLEAR_COLOR, invalidInt); break;
        case 6:  vgSetfv(VG_BLEND_MODE, 2, &invalidFloat); break;
        case 7:  vgSetiv(VG_BLEND_MODE, 2, &invalidInt); break;
        case 8:  vgSetf(VG_BLEND_MODE, invalidFloat); break;
        case 9:  vgSeti(VG_BLEND_MODE, invalidInt); break;
        case 10: vgSetfv(VG_BLEND_MODE, 1, &invalidFloat); break;
        case 11: vgSetiv(VG_BLEND_MODE, 1, &invalidInt); break;
        case 12: vgSetfv(VG_BLEND_MODE, 1, NULL); break;
        case 13: vgSetiv(VG_BLEND_MODE, 1, NULL); break;
        case 14: vgSetfv(VG_BLEND_MODE, -1, &invalidFloat); break;
        case 15: vgSetiv(VG_BLEND_MODE, -1, &invalidInt); break;
        case 16: vgSetfv(VG_CLEAR_COLOR, 2, &invalidFloat); break;
        case 17: vgSetiv(VG_CLEAR_COLOR, 2, &invalidInt); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgGetXxx(VGErrorCode errorCode, int errorCase)
{
    VGint invalidInt = 0xdeadbeef;
    VGfloat invalidFloat = (VGfloat)invalidInt;

    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgGetf(invalidInt); break;
        case 1:  vgGeti(invalidInt); break;
        case 2:  vgGetVectorSize(invalidInt); break;
        case 3:  vgGetfv(invalidInt, 1, &invalidFloat); break;
        case 4:  vgGetiv(invalidInt, 1, &invalidInt); break;
        case 5:  vgGetf(VG_CLEAR_COLOR); break;
        case 6:  vgGeti(VG_CLEAR_COLOR); break;
        case 7:  vgGetfv(VG_BLEND_MODE, 2, &invalidFloat); break;
        case 8:  vgGetiv(VG_BLEND_MODE, 2, &invalidInt); break;
        case 9:  vgGetfv(VG_BLEND_MODE, 1, NULL); break;
        case 10: vgGetiv(VG_BLEND_MODE, 1, NULL); break;
        case 11: vgGetfv(VG_BLEND_MODE, 0, &invalidFloat); break;
        case 12: vgGetiv(VG_BLEND_MODE, 0, &invalidInt); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgSetParameterXxx(VGErrorCode errorCode, int errorCase)
{
    VGint validInt = VG_PAINT_TYPE_COLOR;
    VGfloat validFloat = (VGfloat)validInt;
    VGint invalidInt = 0xdeadbeef;
    VGfloat invalidFloat = (VGfloat)invalidInt;
    VGPaint vgPaint = vgCreatePaint();

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetParameterf(VG_INVALID_HANDLE, VG_PAINT_TYPE, validFloat); break;
        case 1:  vgSetParameteri(VG_INVALID_HANDLE, VG_PAINT_TYPE, validInt); break;
        case 2:  vgSetParameterfv(VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &validFloat); break;
        case 3:  vgSetParameteriv(VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &validInt); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetParameterf(vgPaint, invalidInt, invalidFloat); break;
        case 1:  vgSetParameteri(vgPaint, invalidInt, invalidInt); break;
        case 2:  vgSetParameterfv(vgPaint, invalidInt, 1, &invalidFloat); break;
        case 3:  vgSetParameteriv(vgPaint, invalidInt, 1, &invalidInt); break;
        case 4:  vgSetParameterf(vgPaint, VG_PAINT_COLOR, invalidFloat); break;
        case 5:  vgSetParameteri(vgPaint, VG_PAINT_COLOR, invalidInt); break;
        case 6:  vgSetParameterfv(vgPaint, VG_PAINT_TYPE, 2, &invalidFloat); break;
        case 7:  vgSetParameteriv(vgPaint, VG_PAINT_TYPE, 2, &invalidInt); break;
        case 8:  vgSetParameterf(vgPaint, VG_PAINT_TYPE, invalidFloat); break;
        case 9:  vgSetParameteri(vgPaint, VG_PAINT_TYPE, invalidInt); break;
        case 10: vgSetParameterfv(vgPaint, VG_PAINT_TYPE, 1, &invalidFloat); break;
        case 11: vgSetParameteriv(vgPaint, VG_PAINT_TYPE, 1, &invalidInt); break;
        case 12: vgSetParameterfv(vgPaint, VG_PAINT_TYPE, 1, NULL); break;
        case 13: vgSetParameteriv(vgPaint, VG_PAINT_TYPE, 1, NULL); break;
        case 14: vgSetParameterfv(vgPaint, VG_PAINT_TYPE, -1, &invalidFloat); break;
        case 15: vgSetParameteriv(vgPaint, VG_PAINT_TYPE, -1, &invalidInt); break;
        case 16: vgSetParameterfv(vgPaint, VG_PAINT_COLOR, 2, &invalidFloat); break;
        case 17: vgSetParameteriv(vgPaint, VG_PAINT_COLOR, 2, &invalidInt); break;
        }
        break;
    }

    vgDestroyPaint(vgPaint);
    return VG_TRUE;
}

static VGboolean call_vgGetParameterXxx(VGErrorCode errorCode, int errorCase)
{
    VGint invalidInt = 0xdeadbeef;
    VGfloat invalidFloat = (VGfloat)invalidInt;
    VGPaint vgPaint = vgCreatePaint();

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgGetParameterf(VG_INVALID_HANDLE, VG_PAINT_TYPE); break;
        case 1:  vgGetParameteri(VG_INVALID_HANDLE, VG_PAINT_TYPE); break;
        case 2:  vgGetParameterfv(VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &invalidFloat); break;
        case 3:  vgGetParameteriv(VG_INVALID_HANDLE, VG_PAINT_TYPE, 1, &invalidInt); break;
        case 4:  vgGetParameterVectorSize(VG_INVALID_HANDLE, VG_PAINT_TYPE); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgGetParameterf(vgPaint, invalidInt); break;
        case 1:  vgGetParameteri(vgPaint, invalidInt); break;
        case 2:  vgGetParameterVectorSize(vgPaint, invalidInt); break;
        case 3:  vgGetParameterfv(vgPaint, invalidInt, 1, &invalidFloat); break;
        case 4:  vgGetParameteriv(vgPaint, invalidInt, 1, &invalidInt); break;
        case 5:  vgGetParameterf(vgPaint, VG_PAINT_COLOR); break;
        case 6:  vgGetParameteri(vgPaint, VG_PAINT_COLOR); break;
        case 7:  vgGetParameterfv(vgPaint, VG_PAINT_TYPE, 2, &invalidFloat); break;
        case 8:  vgGetParameteriv(vgPaint, VG_PAINT_TYPE, 2, &invalidInt); break;
        case 9:  vgGetParameterfv(vgPaint, VG_PAINT_TYPE, 1, NULL); break;
        case 10: vgGetParameteriv(vgPaint, VG_PAINT_TYPE, 1, NULL); break;
        case 11: vgGetParameterfv(vgPaint, VG_PAINT_TYPE, 0, &invalidFloat); break;
        case 12: vgGetParameteriv(vgPaint, VG_PAINT_TYPE, 0, &invalidInt); break;
        }
        break;
    }

    vgDestroyPaint(vgPaint);
    return VG_TRUE;
}

static VGboolean call_vgXxxMatrix(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgLoadMatrix(NULL); break;
        case 1:  vgGetMatrix(NULL); break;
        case 2:  vgMultMatrix(NULL); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgMask(VGErrorCode errorCode, int errorCase)
{
    VGImage vgImage = vgCreateImage(VG_A_8, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        vgMask(VG_INVALID_HANDLE, VG_SET_MASK, 0, 0, 1, 1);
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgMask(vgImage, (VGMaskOperation)0xdeadbeef, 0, 0, 1, 1); break;
        case 1:  vgMask(vgImage, VG_SET_MASK, 0, 0, 0, 0); break;
        }
        break;
    }

    vgDestroyImage(vgImage);
    return VG_TRUE;
}

static VGboolean call_vgRenderToMask(VGErrorCode errorCode, int errorCase)
{
    VGPath vgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, 0);

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        vgRenderToMask(VG_INVALID_HANDLE, VG_FILL_PATH, VG_SET_MASK);
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgRenderToMask(vgPath, 0, VG_SET_MASK); break;
        case 1:  vgRenderToMask(vgPath, VG_FILL_PATH, (VGMaskOperation)0xdeadbeef); break;
        }
        break;
    }

    vgDestroyPath(vgPath);
    return VG_TRUE;
}

static VGboolean call_vgCreateMaskLayer(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgCreateMaskLayer(0, 0); break;
        case 1:  vgCreateMaskLayer(vgGeti(VG_MAX_IMAGE_WIDTH) + 1, 1); break;
        case 2:  vgCreateMaskLayer(1, vgGeti(VG_MAX_IMAGE_HEIGHT) + 1); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgDestroyXxx(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgDestroyMaskLayer(VG_INVALID_HANDLE); break;
        case 1:  vgDestroyPath(VG_INVALID_HANDLE); break;
        case 2:  vgDestroyPaint(VG_INVALID_HANDLE); break;
        case 3:  vgDestroyImage(VG_INVALID_HANDLE); break;
        case 4:  vgDestroyFont(VG_INVALID_HANDLE); break;
        }
    }

    return VG_TRUE;
}

static VGboolean call_vgXxxMaskXxx(VGErrorCode errorCode, int errorCase)
{
    VGMaskLayer vgMaskLayer = vgCreateMaskLayer(1, 1);
    if (vgMaskLayer == VG_INVALID_HANDLE)
        return VG_FALSE;

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgFillMaskLayer(VG_INVALID_HANDLE, 0, 0, 1, 1, 1.0f); break;
        case 1:  vgCopyMask(VG_INVALID_HANDLE, 0, 0, 0, 0, 1, 1); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgFillMaskLayer(vgMaskLayer, 0, 0, 1, 1, 2.0f); break;
        case 1:  vgFillMaskLayer(vgMaskLayer, 0, 0, 0, 0, 1.0f); break;
        case 2:  vgFillMaskLayer(vgMaskLayer, -1, -1, 1, 1, 1.0f); break;
        case 3:  vgFillMaskLayer(vgMaskLayer, 1, 1, 1, 1, 1.0f); break;
        case 4:  vgCopyMask(vgMaskLayer, 0, 0, 0, 0, 0, 0); break;
        }
        break;
    }

    vgDestroyMaskLayer(vgMaskLayer);
    return VG_TRUE;
}

static VGboolean call_vgClear(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0: vgClear(0, 0, 0, 1); break;
        case 1: vgClear(0, 0, 1, 0); break;
        case 2: vgClear(0, 0, -1, 1); break;
        case 3: vgClear(0, 0, 1, -1); break;
        case 4: vgClear(0, 0, -1, -1); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgCreatePath(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_UNSUPPORTED_PATH_FORMAT_ERROR:
        vgCreatePath(0xdeadbeef, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, 0);
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgCreatePath(VG_PATH_FORMAT_STANDARD, (VGPathDatatype)0xdeadbeef, 1.0f, 0.0f, 0, 0, 0); break;
        case 1:  vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 0.0f, 0.0f, 0, 0, 0); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgXxxPathXxx(VGErrorCode errorCode, int errorCase)
{
    VGPath vgPathA = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
    VGPath vgPathB = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_APPEND_TO);
    VGPath vgPathC = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, 0);
    VGubyte validSegment = VG_HLINE_TO_REL;
    VGubyte invalidSegment = (VGubyte)0xff;
    VGfloat validData = 0.0f;

    vgAppendPathData(vgPathA, 1, &validSegment, &validData);
    vgAppendPathData(vgPathB, 1, &validSegment, &validData);

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgClearPath(VG_INVALID_HANDLE, 0); break;
        case 1:  vgGetPathCapabilities(VG_INVALID_HANDLE); break;
        case 2:  vgRemovePathCapabilities(VG_INVALID_HANDLE, 0); break;
        case 3:  vgAppendPath(vgPathA, VG_INVALID_HANDLE); break;
        case 4:  vgAppendPath(VG_INVALID_HANDLE, vgPathA); break;
        case 5:  vgAppendPathData(VG_INVALID_HANDLE, 1, &validSegment, &validData); break;
        case 6:  vgModifyPathCoords(VG_INVALID_HANDLE, 0, 1, &validData); break;
        case 7:  vgTransformPath(vgPathA, VG_INVALID_HANDLE); break;
        case 8:  vgTransformPath(VG_INVALID_HANDLE, vgPathA); break;
        case 9:  vgInterpolatePath(vgPathA, vgPathA, VG_INVALID_HANDLE, 0.0f); break;
        case 10: vgInterpolatePath(vgPathA, VG_INVALID_HANDLE, vgPathA, 0.0f); break;
        case 11: vgInterpolatePath(VG_INVALID_HANDLE, vgPathA, vgPathA, 0.0f); break;
        case 12: vgPathLength(VG_INVALID_HANDLE, 0, 1); break;
        case 13: vgPointAlongPath(VG_INVALID_HANDLE, 0, 1, 0.0f, &validData, &validData, &validData, &validData); break;
        case 14: vgPathBounds(VG_INVALID_HANDLE, &validData, &validData, &validData, &validData); break;
        case 15: vgPathTransformedBounds(VG_INVALID_HANDLE, &validData, &validData, &validData, &validData); break;
        case 16: vgDrawPath(VG_INVALID_HANDLE, VG_FILL_PATH); break;
        }
        break;

    case VG_PATH_CAPABILITY_ERROR:
        switch (errorCase)
        {
        case 0:  vgAppendPath(vgPathA, vgPathC); break;
        case 1:  vgAppendPath(vgPathC, vgPathA); break;
        case 2:  vgAppendPathData(vgPathC, 1, &validSegment, &validData); break;
        case 3:  vgModifyPathCoords(vgPathB, 0, 1, &validData); break;
        case 4:  vgTransformPath(vgPathA, vgPathC); break;
        case 5:  vgTransformPath(vgPathC, vgPathA); break;
        case 6:  vgInterpolatePath(vgPathA, vgPathA, vgPathC, 0.0f); break;
        case 7:  vgInterpolatePath(vgPathA, vgPathC, vgPathA, 0.0f); break;
        case 8:  vgInterpolatePath(vgPathC, vgPathA, vgPathA, 0.0f); break;
        case 9:  vgPathLength(vgPathC, 0, 1); break;
        case 10: vgPointAlongPath(vgPathC, 0, 1, 0.0f, &validData, &validData, NULL, NULL); break;
        case 11: vgPointAlongPath(vgPathC, 0, 1, 0.0f, NULL, NULL, &validData, &validData); break;
        case 12: vgPathBounds(vgPathC, &validData, &validData, &validData, &validData); break;
        case 13: vgPathTransformedBounds(vgPathC, &validData, &validData, &validData, &validData); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgAppendPathData(vgPathA, 1, NULL, &validData); break;
        case 1:  vgAppendPathData(vgPathA, 1, &validSegment, NULL); break;
        case 2:  vgAppendPathData(vgPathA, 0, &validSegment, &validData); break;
        case 3:  vgAppendPathData(vgPathA, 1, &invalidSegment, &validData); break;
        case 4:  vgModifyPathCoords(vgPathA, 0, 1, NULL); break;
        case 5:  vgModifyPathCoords(vgPathA, -1, 1, &validData); break;
        case 6:  vgModifyPathCoords(vgPathA, 0, 0, &validData); break;
        case 7:  vgModifyPathCoords(vgPathA, 1, 1, &validData); break;
        case 8:  vgPathLength(vgPathA, -1, 1); break;
        case 9:  vgPathLength(vgPathA, 0, 0); break;
        case 10: vgPathLength(vgPathA, 1, 1); break;
        case 11: vgPointAlongPath(vgPathA, -1, 1, 0.0f, &validData, &validData, &validData, &validData); break;
        case 12: vgPointAlongPath(vgPathA, 0, 0, 0.0f, &validData, &validData, &validData, &validData); break;
        case 13: vgPointAlongPath(vgPathA, 1, 1, 0.0f, &validData, &validData, &validData, &validData); break;
        case 14: vgPathBounds(vgPathA, NULL, &validData, &validData, &validData); break;
        case 15: vgPathBounds(vgPathA, &validData, NULL, &validData, &validData); break;
        case 16: vgPathBounds(vgPathA, &validData, &validData, NULL, &validData); break;
        case 17: vgPathBounds(vgPathA, &validData, &validData, &validData, NULL); break;
        case 18: vgPathTransformedBounds(vgPathA, NULL, &validData, &validData, &validData); break;
        case 19: vgPathTransformedBounds(vgPathA, &validData, NULL, &validData, &validData); break;
        case 20: vgPathTransformedBounds(vgPathA, &validData, &validData, NULL, &validData); break;
        case 21: vgPathTransformedBounds(vgPathA, &validData, &validData, &validData, NULL); break;
        case 22: vgDrawPath(vgPathA, 0); break;
        }
        break;
    }

    vgDestroyPath(vgPathA);
    vgDestroyPath(vgPathB);
    vgDestroyPath(vgPathC);
    return VG_TRUE;
}

static VGboolean call_vgXxxPaintXxx(VGErrorCode errorCode, int errorCase)
{
    VGPaint vgPaint = vgCreatePaint();

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetColor(VG_INVALID_HANDLE, 0); break;
        case 1:  vgGetColor(VG_INVALID_HANDLE); break;
        case 2:  vgPaintPattern(VG_INVALID_HANDLE, VG_INVALID_HANDLE); break;
        case 3:  vgPaintPattern(vgPaint, (VGImage)0xdeadbeef); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetPaint(vgPaint, 0); break;
        case 1:  vgGetPaint(0); break;
        case 2:  vgGetPaint(VG_FILL_PATH | VG_STROKE_PATH); break;
        }
        break;
    }

    vgDestroyPaint(vgPaint);
    return VG_TRUE;
}

static VGboolean call_vgCreateImage(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_UNSUPPORTED_IMAGE_FORMAT_ERROR:
        vgCreateImage((VGImageFormat)0xdeadbeef, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgCreateImage(VG_A_8, 0, 0, VG_IMAGE_QUALITY_NONANTIALIASED); break;
        case 1:  vgCreateImage(VG_A_8, vgGeti(VG_MAX_IMAGE_WIDTH) + 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED); break;
        case 2:  vgCreateImage(VG_A_8, 1, vgGeti(VG_MAX_IMAGE_HEIGHT) + 1, VG_IMAGE_QUALITY_NONANTIALIASED); break;
        case 3:  vgCreateImage(VG_A_8, 1, 1, 0); break;
        }
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgXxxImageXxx(VGErrorCode errorCode, int errorCase)
{
    VGImage vgImage = vgCreateImage(VG_A_8, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    VGubyte data = (VGubyte)0xff;

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgClearImage(VG_INVALID_HANDLE, 0, 0, 1, 1); break;
        case 1:  vgImageSubData(VG_INVALID_HANDLE, &data, 0, VG_A_8, 0, 0, 1, 1); break;
        case 2:  vgGetImageSubData(VG_INVALID_HANDLE, &data, 0, VG_A_8, 0, 0, 1, 1); break;
        case 3:  vgChildImage(VG_INVALID_HANDLE, 0, 0, 1, 1); break;
        case 4:  vgGetParent(VG_INVALID_HANDLE); break;
        case 5:  vgCopyImage(vgImage, 0, 0, VG_INVALID_HANDLE, 0, 0, 1, 1, VG_FALSE); break;
        case 6:  vgCopyImage(VG_INVALID_HANDLE, 0, 0, vgImage, 0, 0, 1, 1, VG_FALSE); break;
        case 7:  vgDrawImage(VG_INVALID_HANDLE); break;
        case 8:  vgSetPixels(0, 0, VG_INVALID_HANDLE, 0, 0, 1, 1); break;
        case 9:  vgGetPixels(VG_INVALID_HANDLE, 0, 0, 0, 0, 1, 1); break;
        }
        break;

    case VG_UNSUPPORTED_IMAGE_FORMAT_ERROR:
        switch (errorCase)
        {
        case 0:  vgImageSubData(vgImage, &data, 0, (VGImageFormat)0xdeadbeef, 0, 0, 1, 1); break;
        case 1:  vgGetImageSubData(vgImage, &data, 0, (VGImageFormat)0xdeadbeef, 0, 0, 1, 1); break;
        case 2:  vgWritePixels(&data, 0, (VGImageFormat)0xdeadbeef, 0, 0, 1, 1); break;
        case 3:  vgReadPixels(&data, 0, (VGImageFormat)0xdeadbeef, 0, 0, 1, 1); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgClearImage(vgImage, 0, 0, 0, 0); break;
        case 1:  vgImageSubData(vgImage, &data, 0, VG_A_8, 0, 0, 0, 0); break;
        case 2:  vgImageSubData(vgImage, NULL, 0, VG_A_8, 0, 0, 1, 1); break;
        case 3:  vgGetImageSubData(vgImage, &data, 0, VG_A_8, 0, 0, 0, 0); break;
        case 4:  vgGetImageSubData(vgImage, NULL, 0, VG_A_8, 0, 0, 1, 1); break;
        case 5:  vgChildImage(vgImage, -1, -1, 1, 1); break;
        case 6:  vgChildImage(vgImage, 0, 0, 0, 0); break;
        case 7:  vgChildImage(vgImage, 1, 1, 1, 1); break;
        case 8:  vgCopyImage(vgImage, 0, 0, vgImage, 0, 0, 0, 0, VG_FALSE); break;
        case 9:  vgSetPixels(0, 0, vgImage, 0, 0, 0, 0); break;
        case 10: vgWritePixels(&data, 0, VG_A_8, 0, 0, 0, 0); break;
        case 11: vgWritePixels(NULL, 0, VG_A_8, 0, 0, 1, 1); break;
        case 12: vgGetPixels(vgImage, 0, 0, 0, 0, 0, 0); break;
        case 13: vgReadPixels(&data, 0, VG_A_8, 0, 0, 0, 0); break;
        case 14: vgReadPixels(NULL, 0, VG_A_8, 0, 0, 1, 1); break;
        case 15: vgCopyPixels(0, 0, 0, 0, 0, 0); break;
        }
        break;
    }

    vgDestroyImage(vgImage);
    return VG_TRUE;
}

static VGboolean call_vgCreateFont(VGErrorCode errorCode, int errorCase)
{
    (void)errorCase;

    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        vgCreateFont(-1);
        break;
    }

    return VG_TRUE;
}

static VGboolean call_vgXxxFontXxx(VGErrorCode errorCode, int errorCase)
{
    VGfloat vec2[] = { 0.0f, 0.0f };
    VGFont vgFont = vgCreateFont(0);
    VGuint validGlyph = 0;
    VGuint invalidGlyph = 1;

    vgSetGlyphToPath(vgFont, validGlyph, VG_INVALID_HANDLE, VG_FALSE, vec2, vec2);

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetGlyphToPath(VG_INVALID_HANDLE, validGlyph, VG_INVALID_HANDLE, VG_FALSE, vec2, vec2); break;
        case 1:  vgSetGlyphToPath(vgFont, validGlyph, (VGPath)0xdeadbeef, VG_FALSE, vec2, vec2); break;
        case 2:  vgSetGlyphToImage(VG_INVALID_HANDLE, validGlyph, VG_INVALID_HANDLE, vec2, vec2); break;
        case 3:  vgSetGlyphToImage(vgFont, validGlyph, (VGImage)0xdeadbeef, vec2, vec2); break;
        case 4:  vgClearGlyph(VG_INVALID_HANDLE, validGlyph); break;
        case 5:  vgDrawGlyph(VG_INVALID_HANDLE, validGlyph, VG_FILL_PATH, VG_FALSE); break;
        case 6:  vgDrawGlyphs(VG_INVALID_HANDLE, 1, &validGlyph, NULL, NULL, VG_FILL_PATH, VG_FALSE); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgSetGlyphToPath(vgFont, validGlyph, VG_INVALID_HANDLE, VG_FALSE, NULL, vec2); break;
        case 1:  vgSetGlyphToPath(vgFont, validGlyph, VG_INVALID_HANDLE, VG_FALSE, vec2, NULL); break;
        case 2:  vgSetGlyphToImage(vgFont, validGlyph, VG_INVALID_HANDLE, NULL, vec2); break;
        case 3:  vgSetGlyphToImage(vgFont, validGlyph, VG_INVALID_HANDLE, vec2, NULL); break;
        case 4:  vgClearGlyph(vgFont, invalidGlyph); break;
        case 5:  vgDrawGlyph(vgFont, invalidGlyph, VG_FILL_PATH, VG_FALSE); break;
        case 6:  vgDrawGlyph(vgFont, validGlyph, 1 << 2, VG_FALSE); break;
        case 7:  vgDrawGlyphs(vgFont, 0, &validGlyph, NULL, NULL, VG_FILL_PATH, VG_FALSE); break;
        case 8:  vgDrawGlyphs(vgFont, 1, NULL, NULL, NULL, VG_FILL_PATH, VG_FALSE); break;
        case 9:  vgDrawGlyphs(vgFont, 1, &invalidGlyph, NULL, NULL, VG_FILL_PATH, VG_FALSE); break;
        case 10: vgDrawGlyphs(vgFont, 1, &validGlyph, NULL, NULL, 1 << 2, VG_FALSE); break;
        }
        break;
    }

    vgDestroyFont(vgFont);
    return VG_TRUE;
}

static VGboolean call_vgXxxFilterXxx(VGErrorCode errorCode, int errorCase)
{
    static const VGfloat matrix[] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };

    VGImage vgImageA;
    VGImage vgImageB;
    VGshort kernel = 1;
    VGuint* lookupInt;
    VGubyte* lookupByte;

    lookupInt = MALLOC(256 * sizeof(VGuint));
    if (!lookupInt)
        return VG_FALSE;

    MEMSET(lookupInt, 0, 256 * sizeof(VGuint));
    lookupByte = (VGubyte*)lookupInt;

    vgImageA = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    vgImageB = vgCreateImage(VG_sRGBA_8888, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);

    switch (errorCode)
    {
    case VG_BAD_HANDLE_ERROR:
        switch (errorCase)
        {
        case 0:  vgColorMatrix(VG_INVALID_HANDLE, vgImageB, matrix); break;
        case 1:  vgColorMatrix(vgImageA, VG_INVALID_HANDLE, matrix); break;
        case 2:  vgConvolve(VG_INVALID_HANDLE, vgImageB, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 3:  vgConvolve(vgImageA, VG_INVALID_HANDLE, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 4:  vgSeparableConvolve(VG_INVALID_HANDLE, vgImageB, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 5:  vgSeparableConvolve(vgImageA, VG_INVALID_HANDLE, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 6:  vgGaussianBlur(VG_INVALID_HANDLE, vgImageB, 1.0f, 1.0f, VG_TILE_FILL); break;
        case 7:  vgGaussianBlur(vgImageA, VG_INVALID_HANDLE, 1.0f, 1.0f, VG_TILE_FILL); break;
        case 8:  vgLookup(VG_INVALID_HANDLE, vgImageB, lookupByte, lookupByte, lookupByte, lookupByte, VG_FALSE, VG_FALSE); break;
        case 9:  vgLookup(vgImageA, VG_INVALID_HANDLE, lookupByte, lookupByte, lookupByte, lookupByte, VG_FALSE, VG_FALSE); break;
        case 10: vgLookupSingle(VG_INVALID_HANDLE, vgImageB, lookupInt, VG_RED, VG_FALSE, VG_FALSE); break;
        case 11: vgLookupSingle(vgImageA, VG_INVALID_HANDLE, lookupInt, VG_RED, VG_FALSE, VG_FALSE); break;
        }
        break;

    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgColorMatrix(vgImageA, vgImageA, matrix); break;
        case 1:  vgColorMatrix(vgImageA, vgImageB, NULL); break;
        case 2:  vgConvolve(vgImageA, vgImageA, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 3:  vgConvolve(vgImageA, vgImageB, 0, 0, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 4:  vgConvolve(vgImageA, vgImageB, vgGeti(VG_MAX_KERNEL_SIZE) + 1, 1, 0, 0, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 5:  vgConvolve(vgImageA, vgImageB, 1, 1, 0, 0, NULL, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 6:  vgConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, 1.0f, 0.0f, (VGTilingMode)0xdeadbeef); break;
        case 7:  vgSeparableConvolve(vgImageA, vgImageA, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 8:  vgSeparableConvolve(vgImageA, vgImageB, 0, 0, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 9:  vgSeparableConvolve(vgImageA, vgImageB, vgGeti(VG_MAX_SEPARABLE_KERNEL_SIZE) + 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 10: vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, NULL, &kernel, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 11: vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, NULL, 1.0f, 0.0f, VG_TILE_FILL); break;
        case 12: vgSeparableConvolve(vgImageA, vgImageB, 1, 1, 0, 0, &kernel, &kernel, 1.0f, 0.0f, (VGTilingMode)0xdeadbeef); break;
        case 13: vgGaussianBlur(vgImageA, vgImageA, 1.0f, 1.0f, VG_TILE_FILL); break;
        case 14: vgGaussianBlur(vgImageA, vgImageB, 0.0f, 0.0f, VG_TILE_FILL); break;
        case 15: vgGaussianBlur(vgImageA, vgImageB, 1.0f, 1.0f, (VGTilingMode)0xdeadbeef); break;
        case 16: vgLookup(vgImageA, vgImageA, lookupByte, lookupByte, lookupByte, lookupByte, VG_FALSE, VG_FALSE); break;
        case 17: vgLookup(vgImageA, vgImageB, NULL, lookupByte, lookupByte, lookupByte, VG_FALSE, VG_FALSE); break;
        case 18: vgLookup(vgImageA, vgImageB, lookupByte, NULL, lookupByte, lookupByte, VG_FALSE, VG_FALSE); break;
        case 19: vgLookup(vgImageA, vgImageB, lookupByte, lookupByte, NULL, lookupByte, VG_FALSE, VG_FALSE); break;
        case 20: vgLookup(vgImageA, vgImageB, lookupByte, lookupByte, lookupByte, NULL, VG_FALSE, VG_FALSE); break;
        case 21: vgLookupSingle(vgImageA, vgImageA, lookupInt, VG_RED, VG_FALSE, VG_FALSE); break;
        case 22: vgLookupSingle(vgImageA, vgImageB, lookupInt, 0, VG_FALSE, VG_FALSE); break;
        case 23: vgLookupSingle(vgImageA, vgImageB, NULL, VG_RED, VG_FALSE, VG_FALSE); break;
        }
        break;
    }

    FREE(lookupInt);
    vgDestroyImage(vgImageA);
    vgDestroyImage(vgImageB);
    return VG_TRUE;
}

static VGboolean call_vgHardwareQuery(VGErrorCode errorCode, int errorCase)
{
    switch (errorCode)
    {
    case VG_ILLEGAL_ARGUMENT_ERROR:
        switch (errorCase)
        {
        case 0:  vgHardwareQuery((VGHardwareQueryType)0xdeadbeef, VG_A_8); break;
        case 1:  vgHardwareQuery(VG_PATH_DATATYPE_QUERY, VG_A_8); break;
        }
        break;
    }

    return VG_TRUE;
}

CT_Result A40101_ErrorOrdering_by_NVIDIA(CT_File *AnsFile)
{
    static const struct
    {
        const char* funcName;
        const char* errorName;
        VGboolean   (*func)(VGErrorCode errorCode, int errorCase);
        VGErrorCode errorCode;
        int         numCases;
    } items[] =
    {
#define ITEM(FUNC, CODE, CASE) { #FUNC, #CODE, call_ ## FUNC, VG_ ## CODE ## _ERROR, CASE }
        ITEM(vgSetXxx,              ILLEGAL_ARGUMENT,           18),
        ITEM(vgGetXxx,              ILLEGAL_ARGUMENT,           13),
        ITEM(vgSetParameterXxx,     BAD_HANDLE,                 4),
        ITEM(vgSetParameterXxx,     ILLEGAL_ARGUMENT,           18),
        ITEM(vgGetParameterXxx,     BAD_HANDLE,                 5),
        ITEM(vgGetParameterXxx,     ILLEGAL_ARGUMENT,           13),
        ITEM(vgXxxMatrix,           ILLEGAL_ARGUMENT,           3),
        ITEM(vgMask,                BAD_HANDLE,                 1),
        ITEM(vgMask,                ILLEGAL_ARGUMENT,           2),
        ITEM(vgRenderToMask,        BAD_HANDLE,                 1),
        ITEM(vgRenderToMask,        ILLEGAL_ARGUMENT,           2),
        ITEM(vgCreateMaskLayer,     ILLEGAL_ARGUMENT,           3),
        ITEM(vgDestroyXxx,          BAD_HANDLE,                 5),
        ITEM(vgXxxMaskXxx,          BAD_HANDLE,                 2),
        ITEM(vgXxxMaskXxx,          ILLEGAL_ARGUMENT,           5),
        ITEM(vgClear,               ILLEGAL_ARGUMENT,           5),
        ITEM(vgCreatePath,          UNSUPPORTED_PATH_FORMAT,    1),
        ITEM(vgCreatePath,          ILLEGAL_ARGUMENT,           2),
        ITEM(vgXxxPathXxx,          BAD_HANDLE,                 17),
        ITEM(vgXxxPathXxx,          PATH_CAPABILITY,            14),
        ITEM(vgXxxPathXxx,          ILLEGAL_ARGUMENT,           23),
        ITEM(vgXxxPaintXxx,         BAD_HANDLE,                 4),
        ITEM(vgXxxPaintXxx,         ILLEGAL_ARGUMENT,           3),
        ITEM(vgCreateImage,         UNSUPPORTED_IMAGE_FORMAT,   1),
        ITEM(vgCreateImage,         ILLEGAL_ARGUMENT,           4),
        ITEM(vgXxxImageXxx,         BAD_HANDLE,                 10),
        ITEM(vgXxxImageXxx,         UNSUPPORTED_IMAGE_FORMAT,   4),
        ITEM(vgXxxImageXxx,         ILLEGAL_ARGUMENT,           16),
        ITEM(vgCreateFont,          ILLEGAL_ARGUMENT,           1),
        ITEM(vgXxxFontXxx,          BAD_HANDLE,                 7),
        ITEM(vgXxxFontXxx,          ILLEGAL_ARGUMENT,           11),
        ITEM(vgXxxFilterXxx,        BAD_HANDLE,                 12),
        ITEM(vgXxxFilterXxx,        ILLEGAL_ARGUMENT,           24),
        ITEM(vgHardwareQuery,       ILLEGAL_ARGUMENT,           2)
#undef ITEM
    };

    int         numItems = sizeof(items) / sizeof(items[0]);
    VGfloat     results[sizeof(items) / sizeof(items[0])];
    int         initItem;
    int         initCase;
    int         i, j;

    /* Clear the results. */

    for (i = 0; i < numItems; i++)
        results[i] = 0.0f;

    /* Check that the API calls produce the errors as expected. */

    for (i = 0; i < numItems; i++)
        for (j = 0; j < items[i].numCases; j++)
        {
            /* No error before the call. */

            if (vgGetError() != VG_NO_ERROR)
                results[i] += 1.0f;

            /* Invoke the call and check the error. */

            if (items[i].func(items[i].errorCode, j) &&
                vgGetError() != items[i].errorCode)
            {
                CT_INFO(("%-12s%-24s%-28s%d\n", "No error", items[i].funcName, items[i].errorName, j));
                results[i] += 1.0f;
            }

            /* No more errors after calling vgGetError(). */

            if (vgGetError() != VG_NO_ERROR)
                results[i] += 1.0f;
        }

    /* Check that no function overrides the current error. */

    initItem = 0;
    initCase = -1;

    for (i = 0; i < numItems; i++)
        for (j = 0; j < items[i].numCases; j++)
        {
            VGboolean wrapped = VG_FALSE;

            /* No error before the call. */

            if (vgGetError() != VG_NO_ERROR)
                results[i] += 1.0f;

            /* Select and execute a call that produces an error
             * othen than items[i].errorCode. */

            for (;;)
            {
                initCase++;
                if (initCase >= items[initItem].numCases)
                {
                    initItem++;
                    initCase = 0;
                    if (initItem >= numItems)
                    {
                        initItem = 0;
                        if (wrapped)
                            return CT_ERROR;
                        wrapped = VG_TRUE;
                    }
                }

                if (items[initItem].errorCode != items[i].errorCode &&
                    items[initItem].func(items[initItem].errorCode, initCase) &&
                    vgGetError() == items[initItem].errorCode &&
                    items[initItem].func(items[initItem].errorCode, initCase))
                {
                    break;
                }
            }

            /* Invoke the call. */

            items[i].func(items[i].errorCode, j);

            /* Check that the previous error was not overridden. */

            if (vgGetError() != items[initItem].errorCode)
            {
                CT_INFO(("%-12s%-24s%-28s%d\n", "Override", items[i].funcName, items[i].errorName, j));
                results[i] += 1.0f;
            }

            /* No more errors after calling vgGetError(). */

            if (vgGetError() != VG_NO_ERROR)
                results[i] += 1.0f;
        }

    /* Save the results. */

    return SaveValueFile(numItems, results, AnsFile);
}

