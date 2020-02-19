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

#include <ctype.h>

#include "../main.h"
#include "util.h"
 

void Dump_Value_by_HUONE (float** AnsValues, float** RefValues, int* count, FILE* AnsFile, FILE* RefFile)
{
    long i;
    ValueFileHeader_by_HUONE AnsHeader, RefHeader;
    
    Read_ValueHeader_by_HUONE (AnsFile, &AnsHeader);
    Read_ValueHeader_by_HUONE (RefFile, &RefHeader);

    if (Compare_ValueHeader_by_HUONE (AnsHeader, RefHeader) <0 ){
        (*count) = -1;
        return;
    }

    (*AnsValues) = (float*) malloc (AnsHeader.count*sizeof(float));
    (*RefValues) = (float*) malloc (RefHeader.count*sizeof(float));
    
    for (i=0; i<RefHeader.count; i++) {
        fscanf (AnsFile, "%f ", (*AnsValues)+i);
        fscanf (RefFile, "%f ", (*RefValues)+i);
    }

    (*count) = RefHeader.count;
}

void Release_Value_by_HUONE (float* AnsValues, float* RefValues)
{
    if (AnsValues) {
        free (AnsValues);
    }
    if (RefValues) {
        free (RefValues);
    }
}

void Read_ValueHeader_by_HUONE  (FILE* file, ValueFileHeader_by_HUONE* valueHeader)
{
    fscanf (file, "%d", &valueHeader->errorcode);
    fscanf (file, "%d", &valueHeader->count);
}

int Compare_ValueHeader_by_HUONE (ValueFileHeader_by_HUONE ansHeader, ValueFileHeader_by_HUONE refHeader) 
{
    int error = 0;
    if (ansHeader.errorcode != refHeader.errorcode) {
        error--;
    }
    if (ansHeader.count != refHeader.count) {
        error--;
    }

    return error;
}


/*===========================================================================*/
/* Main Comparison Interface Function                                        */
/*---------------------------------------------------------------------------*/
float ValueDiff_by_HUONE(FILE *AnsFile, FILE *RefFile)
{
    float  errorSum = 0.0f;
    float* AnsValues = NULL;
    float* RefValues = NULL;
    int    i, count;

    Dump_Value_by_HUONE (&AnsValues, &RefValues, &count, AnsFile, RefFile);
    if ( count < 0 ) {
        Release_Value_by_HUONE(AnsValues, RefValues);
        return CT_INVALID_SCORE;
    }

    for (i = 0; i < count; i++) {
        if (AnsValues[i] != RefValues[i]) {
            errorSum++; 
        }
    }
    Release_Value_by_HUONE(AnsValues, RefValues);    

    return errorSum;
}

float ValueDiff_with_epsilon_by_HUONE(FILE *AnsFile, FILE *RefFile, const float e)
{
    float  errorSum  = 0.0f;
    float* AnsValues = NULL;
    float* RefValues = NULL;
    int    i, count;

    Dump_Value_by_HUONE (&AnsValues, &RefValues, &count, AnsFile, RefFile);
    if ( count < 0 ) {
        Release_Value_by_HUONE(AnsValues, RefValues);
        return CT_INVALID_SCORE;
    }

    for ( i = 0; i < count; i++ ) {
        if ((float)fabs(AnsValues[i] - RefValues[i]) > e) {
            errorSum++;
        }
    }
    Release_Value_by_HUONE(AnsValues, RefValues);    

    return errorSum;
}

int IsBoundingBoxSmaller_by_ATI(FILE *AnsFile, FILE *RefFile)
{
    int errorSum = 0;
    float* AnsValues = NULL;
    float* RefValues = NULL;
    int count;

    Dump_Value_by_HUONE (&AnsValues, &RefValues, &count, AnsFile, RefFile);
    if ( count != 4 ){
        Release_Value_by_HUONE(AnsValues, RefValues);
        return CT_INVALID_SCORE;
    }

    if (AnsValues[0] >= (RefValues[0] + 0.5f))
        errorSum ++;
    if (AnsValues[1] >= (RefValues[1] + 0.5f))
        errorSum ++;
    if ((AnsValues[0] + AnsValues[2] + 0.5f) <= (RefValues[0] + RefValues[2]))
        errorSum ++;
    if ((AnsValues[1] + AnsValues[3] + 0.5f) <= (RefValues[1] + RefValues[3]))
        errorSum ++;
        
    Release_Value_by_HUONE(AnsValues, RefValues);

    return errorSum ++;
}


