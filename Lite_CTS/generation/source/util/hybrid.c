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

#include "../main.h"
#include "util.h"

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Appends data into a path
 * \param   path            The path to append data to
 * \param   numSegments     The number of path segments
 * \param   segments        The segments
 * \param   numCoordinates  Number of coordinates
 * \param   coordinates     The coordinates
 *//*-------------------------------------------------------------------*/

static void append(VGPath path, int numSegments, const VGubyte* segments, int numCoordinates, const VGfloat* coordinates)
{
    VGPathDatatype datatype = (VGPathDatatype)vgGetParameteri(path, VG_PATH_DATATYPE);
    VGfloat        scale    = vgGetParameterf(path, VG_PATH_SCALE);
    VGfloat        bias     = vgGetParameterf(path, VG_PATH_BIAS);

    switch(datatype)
    {
    case VG_PATH_DATATYPE_S_8:
    {
        signed char data[26];
        int i;
        for(i=0;i<numCoordinates;i++)
            data[i] = (signed char)FLOOR((((coordinates[i] - bias) / scale) + 0.5f));
        vgAppendPathData(path, numSegments, segments, data);
        break;
    }

    case VG_PATH_DATATYPE_S_16:
    {
        short data[26];
        int i;
        for(i=0;i<numCoordinates;i++)
            data[i] = (short)FLOOR((((coordinates[i] - bias) / scale) + 0.5f));
        vgAppendPathData(path, numSegments, segments, data);
        break;
    }

    case VG_PATH_DATATYPE_S_32:
    {
        int data[26];
        int i;
        for(i=0;i<numCoordinates;i++)
            data[i] = (int)FLOOR((((coordinates[i] - bias) / scale) + 0.5f));
        vgAppendPathData(path, numSegments, segments, data);
        break;
    }

    default:
    {
        float data[26];
        int i;
        for(i=0;i<numCoordinates;i++)
            data[i] = (float)((coordinates[i] - bias) / scale);
        vgAppendPathData(path, numSegments, segments, data);
        break;
    }
    }
}

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Writes one TGA raw packet
 * \param   r       red channel
 * \param   g       green channel
 * \param   b       blue channel
 * \param   a       alpha channel
 *//*-------------------------------------------------------------------*/

static void writeRawPacket(
    FILEHANDLE fp,
    unsigned int color
)
{
    unsigned char r = (unsigned char)((color >> 24) & 0xff);
    unsigned char g = (unsigned char)((color >> 16) & 0xff);
    unsigned char b = (unsigned char)((color >> 8) & 0xff);
    unsigned char a = (unsigned char)(color & 0xff);

    FWRITE(&b, sizeof(unsigned char), 1, fp);
    FWRITE(&g, sizeof(unsigned char), 1, fp);
    FWRITE(&r, sizeof(unsigned char), 1, fp);
    FWRITE(&a, sizeof(unsigned char), 1, fp);
}

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Writes one TGA RLE packet
 * \param   count   The number of pixels packed in the packet
 * \param   r       red channel
 * \param   g       green channel
 * \param   b       blue channel
 * \param   a       alpha channel
 *//*-------------------------------------------------------------------*/

static void writeRLEPacket(
    FILEHANDLE fp,
    unsigned int count,
    unsigned int color
)
{
    unsigned char r = (unsigned char)((color >> 24) & 0xff);
    unsigned char g = (unsigned char)((color >> 16) & 0xff);
    unsigned char b = (unsigned char)((color >> 8) & 0xff);
    unsigned char a = (unsigned char)(color & 0xff);
    unsigned char c;

    count -= 1;
    count |= 0x80;
    c = (unsigned char)count;
    FWRITE(&c, sizeof(unsigned char), 1, fp);
    FWRITE(&b, sizeof(unsigned char), 1, fp);
    FWRITE(&g, sizeof(unsigned char), 1, fp);
    FWRITE(&r, sizeof(unsigned char), 1, fp);
    FWRITE(&a, sizeof(unsigned char), 1, fp);
}
/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   creates a mask that passes thru only the color channel depths
 *          of the dst surface
 * \param   pMe         ptr to the current CT_AppRec struct
 *//*-------------------------------------------------------------------*/

unsigned int getRelavantBitMask(CT_AppRec *pMe)
{
    int rShift = 8 - pMe->info.rDepth;
    int gShift = 8 - pMe->info.gDepth;
    int bShift = 8 - pMe->info.bDepth;
    int aShift = 8 - ((pMe->info.aDepth) ? pMe->info.aDepth : 8);
    int lDepth = pMe->info.lDepth;
    unsigned int mask = 0x0;
  
    if (lDepth)
    {
        /* set rgb depth to be the same as ldepth */
        rShift = gShift = bShift = 8 - lDepth;
    }
   
    /* Mask is in RGBA order */
    mask = (0xFF >> rShift << (24 + rShift)) |
           (0xFF >> gShift << (16 + gShift)) |
           (0xFF >> bShift << (8  + bShift)) |
           (0xFF >> aShift << aShift);
    return mask;
}

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Saves the frame buffer or a given image in .tga format into
 *          the given file
 * \param   filename    File name
 * \param   buffer      the buffer to be saved
 * \param   width       Dimension
 * \param   height      Dimension
 *//*-------------------------------------------------------------------*/

static CT_Result saveBuffer(
    const char* filename,
    CT_AppRec *pMe,
    VGubyte* buffer,
    int width,
    int height,
    unsigned int imageDepths)
{
    static const unsigned char head1[] =
        { 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    const unsigned char bitdepth = 32;
    const unsigned char descriptor = 8;
    
    FILEHANDLE fp = FOPEN(filename, "wb");
    
    unsigned int* endPtr;
    unsigned int* dataPtr;
    
    unsigned char widthMSB = (unsigned char)(((unsigned int)width >> 8) & 255);
    unsigned char widthLSB = (unsigned char)((unsigned int)width & 255);
    unsigned char heightMSB = (unsigned char)(((unsigned int)height >> 8) & 255);
    unsigned char heightLSB = (unsigned char)((unsigned int)height & 255);
    
    unsigned int pixelMask = 0xFFFFFFFF;
    int idSize =((imageDepths)? sizeof(unsigned int) : 0);
         
    if (fp == NULL) {
        return CT_ERROR;
    }

    if (pMe){
        pixelMask = getRelavantBitMask(pMe);
    }

    FWRITE(&idSize, sizeof(unsigned char), 1, fp);
    FWRITE(head1, sizeof(unsigned char), sizeof(head1), fp);
    FWRITE(&widthLSB, sizeof(unsigned char), 1, fp);
    FWRITE(&widthMSB, sizeof(unsigned char), 1, fp);
    FWRITE(&heightLSB, sizeof(unsigned char), 1, fp);
    FWRITE(&heightMSB, sizeof(unsigned char), 1, fp);
    FWRITE(&bitdepth, sizeof(unsigned char), 1, fp);
    FWRITE(&descriptor, sizeof(unsigned char), 1, fp);
    if (imageDepths)
    {   // store original image bit depths as image id in tga file
        FWRITE(&imageDepths, sizeof(unsigned int), 1, fp);
    }

    dataPtr = (unsigned int*)buffer;
    endPtr = dataPtr + width*height;

    while (dataPtr < endPtr)
    {
        /* Last pixel is always written as a raw packet */
        if(dataPtr == endPtr-1)
        {
            unsigned char zero = 0;
            FWRITE(&zero, sizeof(unsigned char), 1, fp);
            writeRawPacket(fp, *dataPtr & pixelMask);
            break;
        }

        /* We'll write a raw pixel if two consecutive pixels are different */
        if (*dataPtr != *(dataPtr+1))
        {
            /* Raw packet */
            int count, i;
            unsigned int* raw = dataPtr;
            unsigned int thisColor = *raw++;

            /* Find out the length of the raw packet */
            for(count = 0;raw < endPtr && count < 128;raw++,count++)
            {
                unsigned int nextColor = *raw;
                if(thisColor == nextColor)
                    break;
                thisColor = nextColor;
            }

            /* Print the header of the raw packet */
            {
                unsigned char countMinusOne = (unsigned char)(count-1);
                FWRITE(&countMinusOne, sizeof(unsigned char), 1, fp);
            }

            /* Print out the raw packet */
            for (i=0;i<count;i++)
                writeRawPacket(fp, *dataPtr++ & pixelMask );
        }
        else
        {
            /* RLE packet */
            int count;
            unsigned int thisColor = *dataPtr++;
            
            for(count = 1;count < 128 && dataPtr < endPtr;dataPtr++,count++)
            {
                if(*dataPtr != thisColor)
                break;
            }

            writeRLEPacket(fp, count, thisColor & pixelMask);
        }
    }

    FCLOSE(fp);
    return CT_NO_ERROR;
}

/*-------------------------------------------------------------------*//*!
 * \brief   Converts the config info descriptor into image format
 * \param   info    The config info descriptor
 * \return  the format
 *//*-------------------------------------------------------------------*/

 static VGImageFormat dataFormatFromFileInfo(TK_ConfigInfoRec* info)
{
    int isPremultiplied = info->alphaMult;
    int isLinear        = info->cSpace;

    if ( isLinear )
        if (isPremultiplied)
            return VG_lRGBA_8888_PRE;
        else
            return VG_lRGBA_8888;
    else
        if (isPremultiplied)
            return VG_sRGBA_8888_PRE;
        else
            return VG_sRGBA_8888;
}

/*-------------------------------------------------------------------*//*!
 * \brief   Chooses an appropriate write format
 *
 * Maps the source image format into a appropriate 8888 format.
 * Possible output values are VG_lRGBA_8888_PRE, VG_lRGBA_8888,
 * VG_sRGBA_8888_PRE and VG_sRGBA_8888
 *
 * \param   format  The source format
 * \return  The desired write image format
 *//*-------------------------------------------------------------------*/

static VGImageFormat mapWriteFormat(VGImageFormat format)
{
    /* Mask the channel ordering bits away */
    format = format & 0x3f;

    switch (format)
    {
    case VG_sRGBA_8888_PRE:
        return VG_sRGBA_8888_PRE;

    case VG_lRGBA_8888_PRE:
        return VG_lRGBA_8888_PRE;

    case VG_sRGBX_8888:
    case VG_sRGBA_8888:
    case VG_sRGB_565:
    case VG_sRGBA_5551:
    case VG_sRGBA_4444:
    case VG_sL_8:
        return VG_sRGBA_8888;

    default:
        return VG_lRGBA_8888;
    }
}

/*-------------------------------------------------------------------*//*!
 * \brief   Saves a image file in .tga format
 * \param   width   The dimensions of the image
 * \param   height  The dimensions of the image
 * \return  
 *//*-------------------------------------------------------------------*/

CT_Result SaveFrameBufToTGAFile_by_HYBRID(VGint width, VGint height, CT_File *AnsFile)
{
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };
    VGubyte* buf = NULL;

    CT_Result result;
    VGImageFormat dataFormat = dataFormatFromFileInfo(&AnsFile->pMe->info);

    buf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));
    if ( !buf )
        return CT_ERROR;

    AnsFile->type = FILE_TGA_TYPE;
    SPRINTF(name, "%s.tga", AnsFile->filename );

    vgReadPixels(buf, width*4, dataFormat, 0, 0, width, height);

    result = saveBuffer(name, AnsFile->pMe, buf, width, height, 0x0);
    FREE(buf);

    return result;
}

unsigned int getImageDepths(VGImageFormat imageFormat)
{
    static const unsigned int ARGBdepths[] =
    {
        0x00080808, /* 0  VG_sRGBX_8888 */
        0x08080808, /* 1  VG_sRGBA_8888 */
        0x08080808, /* 2  VG_sRGBA_8888_PRE */
        0x00050605, /* 3  VG_sRGB_565 */
        0x01050505, /* 4  VG_sRGBA_5551 */
        0x04040404, /* 5  VG_sRGBA_4444 */
        0x00080808, /* 6  VG_sL_8 */
        0x00080808, /* 7  VG_lRGBX_8888 */
        0x08080808, /* 8  VG_lRGBA_8888 */
        0x08080808, /* 9  VG_lRGBA_8888_PRE */
        0x00080808, /* 10 VG_lL_8 */
        0x08000000, /* 11 VG_A_8 */
        0x00010101, /* 12 VG_BW_1 */
        0x01000000, /* 13 VG_A_1 */
        0x04000000  /* 14 VG_A_4 */
    };
    return ARGBdepths[imageFormat];
}

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Saves the contents of the given image as a .tga file
 * \param   width   
 * \param   height  
 * \param   image   
 * \return  
 *//*-------------------------------------------------------------------*/

CT_Result SaveImageToTGAFile_by_HYBRID(VGImage image, CT_File *AnsFile)
{
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };
    VGint width = vgGetParameteri(image, VG_IMAGE_WIDTH);
    VGint height = vgGetParameteri(image, VG_IMAGE_HEIGHT);
    VGubyte* buf = NULL;
    VGImageFormat readImageFormat = (VGImageFormat)vgGetParameteri(image, VG_IMAGE_FORMAT) & 0x3F;
    VGImageFormat writeImageFormat = mapWriteFormat(readImageFormat);

    CT_Result result;

    buf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));
    if ( !buf )
        return CT_ERROR;

    AnsFile->type = FILE_TGA_TYPE;
    SPRINTF(name, "%s.tga", AnsFile->filename );  
        
    vgGetImageSubData(image, buf, width*4, writeImageFormat, 0, 0, width, height);

    result = saveBuffer(name, 0, buf, width, height, getImageDepths(readImageFormat));
    FREE(buf);
    return result;
}

/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Saves the contents of the given image as a .tga file
 * \param   subtest - the currect subtest number
 * \param   width   
 * \param   height  
 * \param   image   
 * \return  
 *//*-------------------------------------------------------------------*/

CT_Result SaveSubtestImageToTGAFile_by_HYBRID(VGuint subtest, VGImage image, CT_File *AnsFile)
{
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };
    VGint width = vgGetParameteri(image, VG_IMAGE_WIDTH);
    VGint height = vgGetParameteri(image, VG_IMAGE_HEIGHT);
    VGubyte* buf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));

    VGImageFormat readImageFormat = (VGImageFormat)vgGetParameteri(image, VG_IMAGE_FORMAT) & 0x3F;
    VGImageFormat writeImageFormat = mapWriteFormat(readImageFormat);

    CT_Result result;

    AnsFile->type = FILE_TGA_TYPE;
    SPRINTF(name, "%s.tga", AnsFile->filename );

    vgGetImageSubData(image, buf, width*4, writeImageFormat, 0, 0, width, height);

    result = saveBuffer(name, 0, buf, width, height, getImageDepths(readImageFormat));
    FREE(buf);
    return result;
}

/*-------------------------------------------------------------------*//*!
 * \brief   Saves a image file for a subtest in .tga format
 * \param   width   The dimensions of the image
 * \param   height  The dimensions of the image
 * \return  
 *//*-------------------------------------------------------------------*/

CT_Result SaveSubtestFrameBufToTGAFile_by_HYBRID(VGuint subtest, VGint width, VGint height, CT_File *AnsFile)
{
    VGbyte name[CT_MAX_FILE_NAME] = { 0, };
    VGubyte* buf = NULL;

    CT_Result result;

    VGImageFormat dataFormat = dataFormatFromFileInfo(&AnsFile->pMe->info);

    buf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));
    if ( !buf )
        return CT_ERROR;

    AnsFile->type = FILE_TGA_TYPE;
    SPRINTF(name, "%s.tga", AnsFile->filename );

    vgReadPixels(buf, width*4, dataFormat, 0, 0, width, height);

    result = saveBuffer(name, AnsFile->pMe, buf, width, height, 0x0);
    FREE(buf);
    return result;
}

/*-------------------------------------------------------------------*//*!
 * \brief   Draws a rectangle as defined by VGU
 * \param   path    The rect is appended into this path
 * \param   x       The dimensions of the rect
 * \param   y       The dimensions of the rect
 * \param   width   The dimensions of the rect
 * \param   height  The dimensions of the rect
 * \note    Since VGU is not mandated we provide the functionality here.
 *//*-------------------------------------------------------------------*/

void DrawRect_by_HYBRID(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
    static const VGubyte segments[5] = {(VGubyte)VG_MOVE_TO  | VG_ABSOLUTE,
                                        (VGubyte)VG_HLINE_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_VLINE_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_HLINE_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_CLOSE_PATH};
    VGfloat data[5];

    if (width <= 0.f || height <= 0.f)
        return;

    data[0] = x;
    data[1] = y;
    data[2] = x + width;
    data[3] = y + height;
    data[4] = x;

    append(path, 5, segments, 5, data);
}

/*-------------------------------------------------------------------*//*!
 * \brief   Draws an ellipse as defined by VGU
 * \param   path    The rect is appended into this path
 * \param   cx      center point x coordinate
 * \param   cy      center point y coordinate
 * \param   width   width of the ellipse
 * \param   height  height of the ellipse
 *//*-------------------------------------------------------------------*/

void DrawEllipse_by_HYBRID(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height)
{
   static const VGubyte segments[4] = {(VGubyte)VG_MOVE_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_SCCWARC_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_SCCWARC_TO | VG_ABSOLUTE,
                                        (VGubyte)VG_CLOSE_PATH};
    VGfloat data[12];
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    if (width <= 0.f || height <= 0.f)
        return;

    data[0] = cx + hw; 
    data[1] = cy; 
    data[2] = hw; 
    data[3] = hh; 
    data[4] = 0; 
    data[5] = cx - hw; 
    data[6] = cy; 
    data[7] = hw; 
    data[8] = hh; 
    data[9] = 0; 
    data[10] = data[0]; 
    data[11] = cy;

    append(path, 4, segments, 12, data);
}

CT_Result saveFramebufToTGA_by_HUONE(const char* filename, CT_AppRec *pMe, int width, int height)
{
    VGubyte* buf = NULL;
    CT_Result result;

    VGImageFormat dataFormat = dataFormatFromFileInfo(&pMe->info);

    buf = (VGubyte*)MALLOC(width*height*4*sizeof(VGubyte));
    if ( !buf )
        return CT_ERROR;

    vgReadPixels(buf, width*4, dataFormat, 0, 0, width, height);

    result = saveBuffer(filename, pMe, buf, width, height, 0x0);

    FREE(buf);
    return result;
}

