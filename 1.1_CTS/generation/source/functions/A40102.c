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
 * A40102_GetterConsistency_by_NVIDIA
 *
 * Tests the consistency of the values returned by
 * vgGetXxx() and vgGetParameterXxx(). The test loops
 * over all the per-context and per-object parameter
 * types and checks that all the getter variants
 * return values that match the actual value of the
 * particular parameter.
 *
 * If a parameter is read-only, the test uses a getter
 * of the correct type to determine the actual value.
 * If a parameter is writable, the test tries to set it
 * to various tricky float and intger values, and
 * checks the consistency separately for each value.
 *
 * The consistency checks are based on the following
 * passages of chapter 5.2 in the specification:
 *
 * "When setting a value of integral type using a
 *  floating-point vgSet variant (ending with f or fv),
 *  or retrieving a floating-point value using an integer
 *  vgGet function (ending with i or iv), the value is
 *  converted to an integer using a mathematical floor
 *  operation."
 *
 * "Certain parameter values are read-only. Calling
 *  vgSet or vgSetParameter on these values has no effect."
 *
 * "The original value passed to vgSet (except as
 *  specifically noted, and provided that the call to
 *  vgSet completed without errors) is returned by vgGet,
 *  even if the implementation makes use of a truncated
 *  or quantized value internally."
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

/* The type of a single VGHandle object.
 * CT_OBJ_CONTEXT is a special value signifying the
 * current rendering context. */

typedef enum
{
    CT_OBJ_CONTEXT = 0,
    CT_OBJ_PATH,
    CT_OBJ_PAINT,
    CT_OBJ_IMAGE,
    CT_OBJ_MASK,
    CT_OBJ_FONT,

    CT_OBJ_MAX
} CTObjectClass;

/* The type of a single API parameter. */

typedef enum
{
    CT_PARAM_ENUM = 0,
    CT_PARAM_SCALAR,
    CT_PARAM_VECTOR,

    CT_PARAM_MAX
} CTParamClass;

/* Wrapper for a VGHandle object, specifying the
 * object type alongside the handle. */

typedef struct
{
    CTObjectClass   objClass;
    VGHandle        handle;
} CTObject;

/* Specification of a single API parameter. */

typedef struct
{
    const char*     name;           /* Name string. */
    CTParamClass    paramClass;     /* Type of the parameter. */
    CTObjectClass   objClass;       /* Type of the associated object. */
    VGint           token;          /* API token associated with the parameter. */
    VGboolean       isReadOnly;     /* True if the parameter is read-only. */
    VGboolean       isInteger;      /* True if the values are stored internally as integers,
                                     * false if they are represented as floats. */
    int             itemSize;       /* Number of values on a single item. */
    int             minItems;       /* Minimum number of items. */
    int             maxItems;       /* Maximum number of items.
                                     * Negative to query the value using vgGeti(-maxItems). */
    VGint           enumValue;      /* CT_PARAM_ENUM: A single valid enum value. */
} CTParamSpec;

/* Union data type that allows values to be
 * easily reinterpreted as floats or integers. */

typedef union
{
    VGfloat         f;
    VGuint          u;
    VGint           i;
} CTFloatInt;

/* Determines whether the given 32 bit integer can be
 * converted to a float without loss of precision. */

static VGboolean isIntExactAsFloat(VGint value)
{
    /* Negative -> flip the sign. */

    if (value < 0)
    {
        value = -value;

        /* -2^31 -> powers of two are exact. */

        if (value < 0)
            return VG_TRUE;
    }

    /* Shift the value right until it occupies
     * at most 24 bits. */

    while (value > 0x00ffffff)
    {
        if ((value & 1) != 0)
            return VG_FALSE;
        value >>= 1;
    }
    return VG_TRUE;
}

/* Returns false if the given float bits represent
 * a non-finite value (+-Inf, +-qNan, +-sNaN). */

static VGboolean isFloatFinite(VGuint bits)
{
    return ((~bits & 0x7f800000) != 0);
}

/* Calculates the mathematical floor of the given
 * float bits and converts the result to a signed
 * integer. Overflows are handled by clamping the
 * resulting integer to the minimum or maximum
 * representable value. */

static VGint floatToIntFloor(VGuint bits)
{
    int sign = (bits >> 31) ? -1 : 1;
    int exp  = ((bits >> 23) & 255) - 127;
    int mant = bits & 0x007fffff;
    int sh   = 23 - exp;

    /* abs(value) >= 2^31 -> clamp. */

    if (exp >= 31)
        return (VGint)((sign < 0) ? 0x80000000u : 0x7fffffffu);

    /* abs(value) < 1 -> return -1 or 0. */

    if (exp < 0)
        return (sign < 0 && (exp > -127 || mant != 0)) ? -1 : 0;

    /* abs(value) >= 2^23 -> shift left. */

    mant |= 0x00800000;
    if (sh <= 0)
        return sign * (mant << -sh);

    /* Negative -> add a rounding term. */

    if (sign < 0)
        mant += (1 << sh) - 1;

    /* Shift right to obtain the result. */

    return sign * (mant >> sh);
}

/* Wrapper for vgSetf() and vgSetParameterf(). */

static void setf(CTObject obj, VGint token, VGfloat value)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgSetf(token, value);
    else
        vgSetParameterf(obj.handle, token, value);
}

/* Wrapper for vgSeti() and vgSetParameteri(). */

static void seti(CTObject obj, VGint token, VGint value)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgSeti(token, value);
    else
        vgSetParameteri(obj.handle, token, value);
}

/* Wrapper for vgSetfv() and vgSetParameterfv(). */

static void setfv(CTObject obj, VGint token, VGint count, const VGfloat* values)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgSetfv(token, count, values);
    else
        vgSetParameterfv(obj.handle, token, count, values);
}

/* Wrapper for vgSetiv() and vgSetParameteriv(). */

static void setiv(CTObject obj, VGint token, VGint count, const VGint* values)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgSetiv(token, count, values);
    else
        vgSetParameteriv(obj.handle, token, count, values);
}

/* Wrapper for vgGetf() and vgGetParameterf(). */

static VGfloat getf(CTObject obj, VGint token)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        return vgGetf(token);
    else
        return vgGetParameterf(obj.handle, token);
}

/* Wrapper for vgGeti() and vgGetParameteri(). */

static VGint geti(CTObject obj, VGint token)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        return vgGeti(token);
    else
        return vgGetParameteri(obj.handle, token);
}

/* Wrapper for vgGetfv() and vgGetParameterfv(). */

static void getfv(CTObject obj, VGint token, VGint count, VGfloat* values)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgGetfv(token, count, values);
    else
        vgGetParameterfv(obj.handle, token, count, values);
}

/* Wrapper for vgGetiv() and vgGetParameteriv(). */

static void getiv(CTObject obj, VGint token, VGint count, VGint* values)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        vgGetiv(token, count, values);
    else
        vgGetParameteriv(obj.handle, token, count, values);
}

/* Wrapper for vgGetVectorSize() and vgGetParameterVectorSize(). */

static VGint getVectorSize(CTObject obj, VGint token)
{
    if (obj.objClass == CT_OBJ_CONTEXT)
        return vgGetVectorSize(token);
    else
        return vgGetParameterVectorSize(obj.handle, token);
}

/* Checks that the getters return consistent values for
 * the given parameter. */

static int checkParamValue(
    CTParamSpec spec,
    CTObject    obj,
    CTFloatInt* buffer,             /* Values that the parameter has been set to. */
    VGint       count,              /* Expected number of values. */
    VGboolean   specifiedAsInteger) /* True if seti()/setiv() was used, false if setf()/setfv() was used. */
{
    VGboolean   isScalar    = (spec.paramClass == CT_PARAM_ENUM || spec.paramClass == CT_PARAM_SCALAR);
    CTFloatInt* ints        = buffer + count;   /* Buffer for the result of getiv(). */
    CTFloatInt* floats      = ints + count;     /* Buffer for the result of getfv(). */
    int         result      = 0;                /* Number of failures detected. */
    CTFloatInt  ref;
    int         i;

    /* Check that getVectorSize() returns the expected count. */

    i = getVectorSize(obj, spec.token);
    if (i != count)
    {
        CT_INFO(("%s: getVectorSize()=%d, expected %d\n", spec.name, i, count));
        result++;
        if (count > i)
            count = i;
    }

    /* Empty list -> skip the rest of the checks. */

    if (count == 0)
        return result;

    /* Clear the result buffers. */

    for (i = 0; i < count; i++)
    {
        ints[i].i = 0;
        floats[i].f = 0.0f;
    }

    /* Invoke the vector getters. */

    getfv(obj, spec.token, count, &floats[0].f);
    getiv(obj, spec.token, count, &ints[0].i);

    /* Scalar parameter -> check that the scalar getters return consistent values. */

    if (isScalar)
    {
        ref.f = getf(obj, spec.token);
        if (floats[0].u != ref.u)
        {
            CT_INFO(("%s: getfv()=%08x, getf()=%08x\n", spec.name, floats[0].u, ref.u));
            result++;
        }

        ref.i = geti(obj, spec.token);
        if (ints[0].u != ref.u)
        {
            CT_INFO(("%s: getiv()=%08x, geti()=%08x\n", spec.name, ints[0].u, ref.u));
            result++;
        }
    }

    /* Loop over the results and check that they match the expected values. */

    for (i = 0; i < count; i++)
        if (specifiedAsInteger)
        {
            /* setiv() - getfv() */

            ref.f = (VGfloat)buffer[i].i;
            if (floats[i].u != ref.u && isIntExactAsFloat(buffer[i].i))
            {
                CT_INFO(("%s: setiv(%08x), getfv()=%08x, expected %08x\n", spec.name, buffer[i].u, floats[i].u, ref.u));
                result++;
            }

            /* setiv() - getiv() */

            if (ints[i].u != buffer[i].u && (isIntExactAsFloat(buffer[i].i) || spec.isInteger))
            {
                CT_INFO(("%s: setiv(%08x), getiv()=%08x, expected %08x\n", spec.name, buffer[i].u, ints[i].u, buffer[i].u));
                result++;
            }
        }
        else
        {
            /* setfv() - getfv() */

            ref.u = buffer[i].u;
            if (spec.isInteger)
                ref.f = (VGfloat)floatToIntFloor(ref.u);

            if (floats[i].u != ref.u && buffer[i].u == ref.u)
            {
                CT_INFO(("%s: setfv(%08x), getfv()=%08x, expected %08x\n", spec.name, buffer[i].u, floats[i].u, ref.u));
                result++;
            }

            /* setfv() - getiv() */

            ref.i = floatToIntFloor(buffer[i].u);
            if (ints[i].u != ref.u && isFloatFinite(buffer[i].u))
            {
                CT_INFO(("%s: setfv(%08x), getiv()=%08x, expected %08x\n", spec.name, buffer[i].u, ints[i].u, ref.u));
                result++;
            }
        }

    return result;
}

CT_Result A40102_GetterConsistency_by_NVIDIA(CT_File *AnsFile)
{
    static const CTParamSpec paramSpecs[] =
    {
#define ENUM(OBJ, NAME, ISREADONLY, VALUE) \
        { #NAME, CT_PARAM_ENUM, CT_OBJ_ ## OBJ, VG_ ## NAME, (VGboolean)ISREADONLY, VG_TRUE, 1, 1, 1, VALUE }
#define SCALAR(OBJ, NAME, ISREADONLY, ISINTEGER) \
        { #NAME, CT_PARAM_SCALAR, CT_OBJ_ ## OBJ, VG_ ## NAME, (VGboolean)ISREADONLY, (VGboolean)ISINTEGER, 1, 1, 1, 0 }
#define VECTOR(OBJ, NAME, ISREADONLY, ISINTEGER, ISIZE, MINI, MAXI) \
        { #NAME, CT_PARAM_VECTOR, CT_OBJ_ ## OBJ, VG_ ## NAME, (VGboolean)ISREADONLY, (VGboolean)ISINTEGER, ISIZE, MINI, MAXI, 0 }

        ENUM    (CONTEXT,   MATRIX_MODE,                    0, VG_MATRIX_PATH_USER_TO_SURFACE),
        ENUM    (CONTEXT,   FILL_RULE,                      0, VG_EVEN_ODD),
        ENUM    (CONTEXT,   IMAGE_QUALITY,                  0, VG_IMAGE_QUALITY_BETTER),
        ENUM    (CONTEXT,   RENDERING_QUALITY,              0, VG_RENDERING_QUALITY_BETTER),
        ENUM    (CONTEXT,   BLEND_MODE,                     0, VG_BLEND_SRC),
        ENUM    (CONTEXT,   IMAGE_MODE,                     0, VG_DRAW_IMAGE_NORMAL),
        VECTOR  (CONTEXT,   SCISSOR_RECTS,                  0, 1, 4, 0, -VG_MAX_SCISSOR_RECTS),
        ENUM    (CONTEXT,   COLOR_TRANSFORM,                0, VG_TRUE),
        VECTOR  (CONTEXT,   COLOR_TRANSFORM_VALUES,         0, 0, 8, 1, 1),
        SCALAR  (CONTEXT,   STROKE_LINE_WIDTH,              0, 0),
        ENUM    (CONTEXT,   STROKE_CAP_STYLE,               0, VG_CAP_BUTT),
        ENUM    (CONTEXT,   STROKE_JOIN_STYLE,              0, VG_JOIN_MITER),
        SCALAR  (CONTEXT,   STROKE_MITER_LIMIT,             0, 0),
        VECTOR  (CONTEXT,   STROKE_DASH_PATTERN,            0, 0, 1, 0, -VG_MAX_DASH_COUNT),
        SCALAR  (CONTEXT,   STROKE_DASH_PHASE,              0, 0),
        ENUM    (CONTEXT,   STROKE_DASH_PHASE_RESET,        0, VG_TRUE),
        VECTOR  (CONTEXT,   TILE_FILL_COLOR,                0, 0, 4, 1, 1),
        VECTOR  (CONTEXT,   CLEAR_COLOR,                    0, 0, 4, 1, 1),
        VECTOR  (CONTEXT,   GLYPH_ORIGIN,                   0, 0, 2, 1, 1),
        ENUM    (CONTEXT,   MASKING,                        0, VG_TRUE),
        ENUM    (CONTEXT,   SCISSORING,                     0, VG_TRUE),
        ENUM    (CONTEXT,   PIXEL_LAYOUT,                   0, VG_PIXEL_LAYOUT_UNKNOWN),
        ENUM    (CONTEXT,   SCREEN_LAYOUT,                  1, VG_PIXEL_LAYOUT_UNKNOWN),
        ENUM    (CONTEXT,   FILTER_FORMAT_LINEAR,           0, VG_TRUE),
        ENUM    (CONTEXT,   FILTER_FORMAT_PREMULTIPLIED,    0, VG_TRUE),
        ENUM    (CONTEXT,   FILTER_CHANNEL_MASK,            0, VG_RED | VG_GREEN),

        SCALAR  (CONTEXT,   MAX_SCISSOR_RECTS,              1, 1),
        SCALAR  (CONTEXT,   MAX_DASH_COUNT,                 1, 1),
        SCALAR  (CONTEXT,   MAX_KERNEL_SIZE,                1, 1),
        SCALAR  (CONTEXT,   MAX_SEPARABLE_KERNEL_SIZE,      1, 1),
        SCALAR  (CONTEXT,   MAX_COLOR_RAMP_STOPS,           1, 1),
        SCALAR  (CONTEXT,   MAX_IMAGE_WIDTH,                1, 1),
        SCALAR  (CONTEXT,   MAX_IMAGE_HEIGHT,               1, 1),
        SCALAR  (CONTEXT,   MAX_IMAGE_PIXELS,               1, 1),
        SCALAR  (CONTEXT,   MAX_IMAGE_BYTES,                1, 1),
        SCALAR  (CONTEXT,   MAX_FLOAT,                      1, 0),
        SCALAR  (CONTEXT,   MAX_GAUSSIAN_STD_DEVIATION,     1, 0),

        ENUM    (PATH,      PATH_FORMAT,                    1, VG_PATH_FORMAT_STANDARD),
        ENUM    (PATH,      PATH_DATATYPE,                  1, VG_PATH_DATATYPE_F),
        SCALAR  (PATH,      PATH_SCALE,                     1, 0),
        SCALAR  (PATH,      PATH_BIAS,                      1, 0),
        SCALAR  (PATH,      PATH_NUM_SEGMENTS,              1, 1),
        SCALAR  (PATH,      PATH_NUM_COORDS,                1, 1),

        ENUM    (PAINT,     PAINT_TYPE,                     0, VG_PAINT_TYPE_COLOR),
        VECTOR  (PAINT,     PAINT_COLOR,                    0, 0, 4, 1, 1),
        ENUM    (PAINT,     PAINT_COLOR_RAMP_SPREAD_MODE,   0, VG_COLOR_RAMP_SPREAD_PAD),
        ENUM    (PAINT,     PAINT_COLOR_RAMP_PREMULTIPLIED, 0, VG_TRUE),
        VECTOR  (PAINT,     PAINT_COLOR_RAMP_STOPS,         0, 0, 5, 0, -VG_MAX_COLOR_RAMP_STOPS),
        VECTOR  (PAINT,     PAINT_LINEAR_GRADIENT,          0, 0, 4, 1, 1),
        VECTOR  (PAINT,     PAINT_RADIAL_GRADIENT,          0, 0, 5, 1, 1),
        ENUM    (PAINT,     PAINT_PATTERN_TILING_MODE,      0, VG_TILE_FILL),

        ENUM    (IMAGE,     IMAGE_FORMAT,                   1, VG_A_8),
        SCALAR  (IMAGE,     IMAGE_WIDTH,                    1, 1),
        SCALAR  (IMAGE,     IMAGE_HEIGHT,                   1, 1),
 
        SCALAR  (FONT,      FONT_NUM_GLYPHS,                1, 1)

#undef ENUM
#undef SCALAR
#undef VECTOR
    };

    static const VGuint trickyValues[] =
    {
        0x7fffffffu, 0x80000000u, 			    /* Integer: around min/max. */
        0xffffffffu, 0x00000000u,               /* Integer: around zero. */
        0x00ffffffu, 0x01000000u, 0x01000001u,  /* Integer: around 2^24. */
        0xfeffffffu, 0xff000000u, 0xff000001u,  /* Integer: around -2^24. */
        0x3f7fffffu, 0x3f800000u, 0x3f800001u,  /* Float: around 1.0f. */
        0xbf7fffffu, 0xbf800000u, 0xbf800001u,  /* Float: around -1.0f. */
        0x7f7ffffdu, 0x7f7ffffeu, 0x7f7fffffu,  /* Float: around largest positive. */
        0xff7ffffdu, 0xff7ffffeu, 0xff7fffffu,  /* Float: around largest negative. */
        0x4effffffu, 0x4f000000u, 0x4f000001u,  /* Float: around 2^31. */
        0xceffffffu, 0xcf000000u, 0xcf000001u,  /* Float: around -2^31. */
        0x4f7fffffu, 0x4f800000u, 0x4f800001u,  /* Float: around 2^32. */
        0xcf7fffffu, 0xcf800000u, 0xcf800001u,  /* Float: around -2^32. */
        0x7f800000u, 0xff800000u,               /* Float: +-Inf. */
        0x7fc00000u, 0x7fc00001u,               /* Float: +qNaN. */
        0xffc00000u, 0xffc00001u,               /* Float: -qNaN. */
        0xdeadbeefu, 0xdeadc0deu, 0xcafebabeu,  /* Magic numbers. */
        0x9e3779b9u, 0xaaaaaaaau, 0xccccccccu   /* Magic numbers. */
    };

    int         bufferSize = 256;
    int         numParams = sizeof(paramSpecs) / sizeof(paramSpecs[0]);
    int         numTricky = sizeof(trickyValues) / sizeof(trickyValues[0]);
    VGfloat     results[sizeof(paramSpecs) / sizeof(paramSpecs[0])];
    CTObject    objs[CT_OBJ_MAX];
    CTFloatInt* buffer;
    int         i, j, k;

    /* Allocate the temporary buffer. */

    buffer = (CTFloatInt*)MALLOC(3 * bufferSize * sizeof(CTFloatInt));
    if (!buffer)
        return CT_ERROR;

    /* Create the object structs. */

    for (i = 0; i < CT_OBJ_MAX; i++)
    {
        objs[i].objClass = (CTObjectClass)i;
        objs[i].handle = VG_INVALID_HANDLE;
    }

    /* Create the objects. */

    objs[CT_OBJ_PATH].handle  = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, 0);
    objs[CT_OBJ_PAINT].handle = vgCreatePaint();
    objs[CT_OBJ_IMAGE].handle = vgCreateImage(VG_A_8, 1, 1, VG_IMAGE_QUALITY_NONANTIALIASED);
    objs[CT_OBJ_MASK].handle  = vgCreateMaskLayer(1, 1);
    objs[CT_OBJ_FONT].handle  = vgCreateFont(1);

    /* Loop over the API parameters. */

    for (i = 0; i < numParams; i++)
    {
        const CTParamSpec spec = paramSpecs[i];
        CTObject obj = objs[spec.objClass];
        int result = 0;

        /* The object was created successfully -> run the tests. */

        if (obj.handle != VG_INVALID_HANDLE || obj.objClass == CT_OBJ_CONTEXT)
        {
            /* Read-only parameter. */

            if (spec.isReadOnly)
            {
                VGint count = getVectorSize(obj, spec.token);
                if (count > bufferSize)
                    result++;
                else
                {
                    /* Read the actual value. */

                    if (spec.isInteger)
                        getiv(obj, spec.token, count, &buffer[0].i);
                    else
                        getfv(obj, spec.token, count, &buffer[0].f);

                    /* Check consistency. */

                    result += checkParamValue(spec, obj, buffer, count, spec.isInteger);

                    /* Try to set to a bogus value.
                     * The call should get ignored by the implementation,
                     * and should not produce an error. */

                    seti(obj, spec.token, (VGint)0xdeadbeefu);
                    setf(obj, spec.token, (VGfloat)0xdeadbeefu);

                    /* Check consistency again. */

                    result += checkParamValue(spec, obj, buffer, count, spec.isInteger);
                }
            }

            /* Enum parameter. */

            else if (spec.paramClass == CT_PARAM_ENUM)
            {
                VGint intValue = spec.enumValue;
                VGfloat floatValue = (VGfloat)intValue + 0.999f;

                /* Set to spec.enumValue using each setter variant. */

                buffer[0].i = intValue;
                seti(obj, spec.token, buffer[0].i);
                result += checkParamValue(spec, obj, buffer, 1, VG_TRUE);

                buffer[0].f = floatValue;
                setf(obj, spec.token, buffer[0].f);
                result += checkParamValue(spec, obj, buffer, 1, VG_FALSE);

                buffer[0].i = intValue;
                setiv(obj, spec.token, 1, &buffer[0].i);
                result += checkParamValue(spec, obj, buffer, 1, VG_TRUE);

                buffer[0].f = floatValue;
                setfv(obj, spec.token, 1, &buffer[0].f);
                result += checkParamValue(spec, obj, buffer, 1, VG_FALSE);
            }

            /* Writable vector parameter. */

            else
            {
                VGint count;
                VGint minCount = spec.minItems * spec.itemSize;
                VGint maxCount = spec.maxItems;
                if (maxCount < 0)
                    maxCount = vgGeti((VGParamType)-maxCount);
                maxCount *= spec.itemSize;
                if (maxCount > bufferSize)
                    maxCount = bufferSize;

                /* Loop over different counts and values. */

                for (count = minCount; count <= maxCount; count += spec.itemSize)
                    for (j = 0; j < numTricky; j++)
                    {
                        /* Lookup the values from the table. */

                        for (k = 0; k < count; k++)
                            buffer[k].u = trickyValues[(j + k) % numTricky];

                        /* Scalar parameter -> Set using seti() and setf(). */

                        if (spec.paramClass == CT_PARAM_SCALAR)
                        {
                            seti(obj, spec.token, buffer[0].i);
                            result += checkParamValue(spec, obj, buffer, 1, VG_TRUE);
                            setf(obj, spec.token, buffer[0].f);
                            result += checkParamValue(spec, obj, buffer, 1, VG_FALSE);
                        }

                        /* Set using setiv() and setfv(). */

                        setiv(obj, spec.token, count, &buffer[0].i);
                        result += checkParamValue(spec, obj, buffer, count, VG_TRUE);
                        setfv(obj, spec.token, count, &buffer[0].f);
                        result += checkParamValue(spec, obj, buffer, count, VG_FALSE);
                    }
            }
        }

        /* Check for VG errors and store the result. */

        if (vgGetError() != VG_NO_ERROR)
        {
            CT_INFO(("%s: caught a VGError\n", spec.name));
            result++;
        }
        results[i] = (VGfloat)result;
    }

    /* Destroy the objects. */

    if (objs[CT_OBJ_PATH].handle != VG_INVALID_HANDLE)
        vgDestroyPath(objs[CT_OBJ_PATH].handle);
    if (objs[CT_OBJ_PAINT].handle != VG_INVALID_HANDLE)
        vgDestroyPaint(objs[CT_OBJ_PAINT].handle);
    if (objs[CT_OBJ_IMAGE].handle != VG_INVALID_HANDLE)
        vgDestroyImage(objs[CT_OBJ_IMAGE].handle);
    if (objs[CT_OBJ_MASK].handle != VG_INVALID_HANDLE)
        vgDestroyMaskLayer(objs[CT_OBJ_MASK].handle);
    if (objs[CT_OBJ_FONT].handle != VG_INVALID_HANDLE)
        vgDestroyFont(objs[CT_OBJ_FONT].handle);

    /* Clean up and save the results. */

    FREE(buffer);
    return SaveValueFile(numParams, results, AnsFile);
}

