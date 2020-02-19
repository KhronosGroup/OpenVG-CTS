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


#ifndef __PATHDATA_H__
#define __PATHDATA_H__

static const VGint frame_numSegments  = 5;
static const VGint frame_numCoordPairs  = 5;

static const VGubyte frameSegments[5] = 
{
	0x02, 0x04, 0x04, 0x04, 0x04
};

static const VGfloat frameData[10] = 
{
	0.5, 0.5, 63.5, 0.5, 63.5, 63.5, 0.5, 63.5, 0.5, 0.5
};

/*-----------------------------------------------------------------------------*/
/*               Defining unhinted glyph path and metrics data                 */
/*-----------------------------------------------------------------------------*/
static VGfloat glyph_origin[2] = {0.0, 0.0};

static const VGint glyph71_numSegments  = 29;
static const VGint glyph79_numSegments  = 18;
static const VGint glyph86_numSegments  = 20;
static const VGint glyph101_numSegments = 19;
static const VGint glyph110_numSegments = 32;
static const VGint glyph112_numSegments = 31;

static const VGint glyph71_numCoordPairs  = 49;
static const VGint glyph79_numCoordPairs  = 34;
static const VGint glyph86_numCoordPairs  = 28;
static const VGint glyph101_numCoordPairs = 33;
static const VGint glyph110_numCoordPairs = 48;
static const VGint glyph112_numCoordPairs = 49;

static VGfloat glyph71_escapement[2]  = {0.722179f, 0.0};
static VGfloat glyph79_escapement[2]  = {0.722179f, 0.0};
static VGfloat glyph86_escapement[2]  = {0.722179f, 0.0};
static VGfloat glyph101_escapement[2] = {0.443854f, 0.0};
static VGfloat glyph110_escapement[2] = {0.500008f, 0.0};
static VGfloat glyph112_escapement[2] = {0.500008f, 0.0};

static VGfloat glyphKerningX[6] = {0.0, 0.0, 0.0, -0.0542f, -0.0293f, 0.0f};
static VGfloat glyphKerningY[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0f};

static const VGubyte glyph71_Segments[29] = 
{
	0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	0x0a, 0x0a, 0x04, 0x04, 0x04, 0x0a,
	0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	0x04, 0x0a, 0x0a, 0x0a, 0x04, 0x04,
	0x04, 0x0a, 0x0a, 0x04, 0x0a
};

static const VGfloat glyph71_Data[98] = 
{
	756.0, -31.0, 451.0, -31.0, 263.5, 167.5, 76.0, 366.0, 
	76.0, 678.0, 76.0, 979.0, 280.5, 1182.5, 485.0, 1386.0, 
	791.0, 1386.0, 901.0, 1386.0, 1066.0, 1350.0, 1148.0, 
	1331.0, 1176.0, 1331.0, 1218.0, 1331.0, 1229.0, 1386.0, 
	1274.0, 1386.0, 1274.0, 975.0, 1233.0, 975.0, 1139.0, 
	1313.0, 799.0, 1313.0, 579.0, 1313.0, 439.0, 1147.0, 
	299.0, 981.0, 299.0, 680.0, 299.0, 484.0, 366.0, 341.5, 
	433.0, 199.0, 553.5, 123.0, 674.0, 47.0, 811.0, 47.0, 
	976.0, 47.0, 1106.0, 127.0, 1106.0, 369.0, 1106.0, 469.0, 
	1097.0, 508.5, 1088.0, 548.0, 1049.0, 565.0, 1010.0, 
	582.0, 913.0, 582.0, 913.0, 629.0, 1452.0, 629.0, 1452.0, 
	582.0, 1361.0, 582.0, 1329.5, 551.0, 1298.0, 520.0, 
	1298.0, 401.0, 1298.0, 92.0, 1062.0, -31.0, 756.0, -31.0
};

static const VGubyte glyph79_Segments[18] = 
{
	0x02, 0x0a, 0x0a, 0x0a, 0x0a, 
	0x0a, 0x0a, 0x0a, 0x0a, 0x02, 
	0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 
	0x0a, 0x0a, 0x0a 
};

static const VGfloat glyph79_Data[68] = 
{
	739.0, 1386.0, 1035.0, 1386.0, 1219.0, 1188.0, 1403.0, 990.0, 
	1403.0, 678.0, 1403.0, 367.0, 1220.5, 168.0, 1038.0, -31.0, 
	739.0, -31.0, 444.0, -31.0, 260.0, 167.0, 76.0, 365.0, 76.0, 
	678.0, 76.0, 990.0, 260.0, 1188.0, 444.0, 1386.0, 739.0, 
	1386.0, 739.0, 45.0, 953.0, 45.0, 1066.5, 216.5, 1180.0, 
	388.0, 1180.0, 678.0, 1180.0, 968.0, 1066.5, 1140.5, 953.0, 
	1313.0, 739.0, 1313.0, 526.0, 1313.0, 412.5, 1140.5, 299.0, 
	968.0, 299.0, 678.0, 299.0, 388.0, 412.5, 216.5, 526.0, 45.0, 
	739.0, 45.0
};

static const VGubyte glyph86_Segments[20] = 
{
	0x02, 0x0a, 0x0a, 0x04, 0x04, 
	0x04, 0x0a, 0x0a, 0x04, 0x04, 
	0x04, 0x0a, 0x0a, 0x04, 0x04, 
	0x0a, 0x0a, 0x04, 0x04, 0x04
};

static const VGfloat glyph86_Data[56] = 
{
	1456.0, 1309.0, 1373.0, 1309.0, 1337.0, 1268.5, 1301.0, 1228.0, 
	1243.0, 1090.0, 780.0, -31.0, 743.0, -31.0, 246.0, 1104.0, 192.0, 
	1227.0, 151.5, 1268.0, 111.0, 1309.0, 20.0, 1309.0, 20.0, 1356.0, 
	575.0, 1356.0, 575.0, 1309.0, 424.0, 1309.0, 424.0, 1212.0, 
	424.0, 1169.0, 481.0, 1038.0, 815.0, 276.0, 1126.0, 1030.0, 
	1182.0, 1161.0, 1182.0, 1219.0, 1182.0, 1309.0, 1038.0, 1309.0, 
	1038.0, 1356.0, 1456.0, 1356.0, 1456.0, 1309.0
};

static const VGubyte glyph101_Segments[19] = 
{
	0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 
	0x0a, 0x0a, 0x04, 0x0a, 0x0a, 0x0a, 
	0x04, 0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x04
};

static const VGfloat glyph101_Data[66] = 
{
	858.0, 227.0, 712.0, -31.0, 473.0, -31.0, 302.0, -31.0, 187.0, 
	109.5, 72.0, 250.0, 72.0, 461.0, 72.0, 682.0, 187.0, 823.5, 302.0, 
	965.0, 479.0, 965.0, 641.0, 965.0, 745.5, 843.5, 850.0, 722.0, 
	850.0, 530.0, 231.0, 530.0, 231.0, 344.0, 312.0, 226.5, 393.0, 
	109.0, 537.0, 109.0, 708.0, 109.0, 823.0, 264.0, 858.0, 227.0, 
	651.0, 602.0, 651.0, 735.0, 601.5, 814.0, 552.0, 893.0, 467.0, 
	893.0, 376.0, 893.0, 313.5, 814.5, 251.0, 736.0, 236.0, 602.0, 
	651.0, 602.0
};

static const VGubyte glyph110_Segments[32] = 
{
	0x02, 0x04, 0x04, 0x0a, 0x0a, 0x04, 0x0a, 0x0a, 
	0x0a, 0x04, 0x0a, 0x0a, 0x04, 0x04, 0x04, 0x0a, 
	0x0a, 0x04, 0x0a, 0x0a, 0x04, 0x04, 0x04, 0x04, 
	0x04, 0x0a, 0x0a, 0x0a, 0x04, 0x0a, 0x0a, 0x04
};

static const VGfloat glyph110_Data[96] = 
{
	997.0, 0.0, 586.0, 0.0, 586.0, 47.0, 674.0, 47.0, 694.5, 75.0, 
	715.0, 103.0, 715.0, 201.0, 715.0, 606.0, 715.0, 732.0, 671.0, 
	788.0, 627.0, 844.0, 532.0, 844.0, 437.0, 844.0, 334.0, 760.0, 
	334.0, 201.0, 334.0, 99.0, 357.0, 73.0, 380.0, 47.0, 453.0, 47.0, 
	453.0, 0.0, 41.0, 0.0, 41.0, 47.0, 129.0, 47.0, 149.5, 75.0, 
	170.0, 103.0, 170.0, 201.0, 170.0, 723.0, 170.0, 782.0, 152.0, 
	803.5, 134.0, 825.0, 82.0, 825.0, 25.0, 825.0, 25.0, 868.0, 297.0, 
	965.0, 334.0, 965.0, 334.0, 825.0, 482.0, 965.0, 623.0, 965.0, 
	752.0, 965.0, 815.5, 882.5, 879.0, 800.0, 879.0, 655.0, 879.0, 
	201.0, 879.0, 99.0, 902.0, 73.0, 925.0, 47.0, 997.0, 47.0, 997.0, 0.0
};

static const VGubyte glyph112_Segments[31] = 
{
	0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 
	0x0a, 0x04, 0x0a, 0x0a, 0x04, 0x04, 
	0x04, 0x0a, 0x0a, 0x04, 0x0a, 0x0a, 
	0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 
	0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x04
};

static const VGfloat glyph112_Data[98] = 
{
	315.0, 825.0, 466.0, 965.0, 602.0, 965.0, 763.0, 965.0, 857.5, 
	829.0, 952.0, 693.0, 952.0, 504.0, 952.0, 290.0, 823.0, 130.5, 
	694.0, -29.0, 510.0, -29.0, 419.0, -29.0, 315.0, 0.0, 315.0, 
	-238.0, 315.0, -345.0, 339.5, -368.0, 364.0, -391.0, 475.0, 
	-391.0, 475.0, -438.0, 23.0, -438.0, 23.0, -391.0, 111.0, -391.0, 
	131.5, -363.0, 152.0, -335.0, 152.0, -238.0, 152.0, 723.0, 152.0, 
	783.0, 133.5, 804.0, 115.0, 825.0, 63.0, 825.0, 6.0, 825.0, 6.0, 
	868.0, 281.0, 965.0, 315.0, 965.0, 315.0, 825.0, 315.0, 104.0, 
	406.0, 43.0, 512.0, 43.0, 639.0, 43.0, 709.5, 151.5, 780.0, 260.0, 
	780.0, 446.0, 780.0, 618.0, 709.0, 731.0, 638.0, 844.0, 512.0, 
	844.0, 422.0, 844.0, 315.0, 760.0, 315.0, 104.0
};


/*-----------------------------------------------------------------------------*/
/*                Defining hinted glyph path and metrics data                  */
/*-----------------------------------------------------------------------------*/

static VGfloat hintedGlyph71_escapement[2]  = {11.0f, 0.0};
static VGfloat hintedGlyph79_escapement[2]  = {12.0f, 0.0};
static VGfloat hintedGlyph86_escapement[2]  = {12.0f, 0.0};
static VGfloat hintedGlyph101_escapement[2] = {7.0f, 0.0};
static VGfloat hintedGlyph110_escapement[2] = {7.0f, 0.0};
static VGfloat hintedGlyph112_escapement[2] = {7.0f, 0.0};

static const VGfloat hintedGlyph71_Data[98] = 
{
	6.015625f, 0.0f, 3.515625f, 0.0f, 2.257813f, 1.539063f, 1.0f,
	3.078125f, 1.0f, 5.5f, 1.0f, 7.843750f, 2.421875f, 9.421875f,
	3.84375f, 11.0f, 5.96875f, 11.0f, 6.71875f, 11.0f, 7.875f,
	10.84375f, 8.4375f, 10.0f, 8.625f, 10.0f, 8.921875f, 10.0f,
	9.0f, 11.0f, 10.0f, 11.0f, 10.0f, 8.0f, 9.0f, 8.0f, 8.296875f,
	10.0f, 5.75f, 10.0f, 4.09375f, 10.0f, 3.046875f, 8.820313f, 2.0f,
	7.640625f, 2.0f, 5.5f, 2.0f, 4.109375f, 2.578125f, 3.09375f,
	3.15625f, 2.078125f, 3.953125f, 1.539063f, 4.75f, 1.0f, 6.4375f,
	1.0f, 7.875f, 1.0f, 9.0f, 1.453125f, 9.0f, 2.8125f, 9.0f, 3.359375f,
	8.90625f, 3.585938f, 8.8125f, 3.8125f, 8.40625f, 3.90625f, 8.0f,
	4.0f, 7.0f, 4.0f, 7.0f, 5.0f, 11.0f, 5.0f, 11.0f, 4.0f, 10.40625f,
	4.0f, 10.203125f, 3.796875f, 10.0f, 3.59375f, 10.0f, 2.8125f,
	10.0f, 0.796875f, 8.265625f, 0.0f, 6.015625f, 0.0
};

static const VGfloat hintedGlyph79_Data[68] = 
{
	6.0f, 11.0f, 8.234375f, 11.0f, 9.617188f, 9.460938f, 11.0f, 7.921875f,
	11.0f, 5.5f, 11.0f, 3.093750f, 9.625f, 1.546875f, 8.25f, 0.0f, 6.0f, 0.0f,
	3.765625f, 0.0f, 2.382813f, 1.539063f, 1.0f, 3.078125f, 1.0f, 5.5f, 1.0f,
	7.921875f, 2.382813f, 9.460938f, 3.765625f, 11.0f, 6.0f, 11.0f, 6.0f, 1.0f,
	7.9375f, 1.0f, 8.96875f, 2.21875f, 10.0f, 3.4375f, 10.0f, 5.5f, 10.0f,
	7.546875f, 8.96875f, 8.773438f, 7.9375f, 10.0f, 6.0f, 10.0f, 4.0625f, 10.0f,
	3.03125f, 8.773438f, 2.0f, 7.546875f, 2.0f, 5.5f, 2.0f, 3.4375f, 3.03125f,
	2.21875f, 4.0625f, 1.0f, 6.0f, 1.0f
};

static const VGfloat hintedGlyph86_Data[56] = 
{
	12.0f, 10.0f, 11.546875f, 10.0f, 11.351563f, 9.695313f, 11.15625f,
	9.390625f, 10.84375f, 8.359375f, 6.421875f, 0.0f, 5.421875f, 0.0f,
	1.21875f, 8.46875f, 0.921875f, 9.390625f, 0.703125f, 9.695313f,
	0.484375f, 10.0f, 0.0f, 10.0f, 0.0f, 11.0f, 3.0f, 11.0f, 3.0f, 10.0f,
	1.96875f, 10.0f, 1.96875f, 9.265625f, 1.96875f, 8.9375f, 2.421875f,
	7.953125f, 6.0f, 0.96875f, 9.578125f, 7.953125f, 10.015625f, 8.921875f,
	10.015625f, 9.34375f, 10.015625f, 10.00f, 9.0f, 10.0f, 9.0f, 11.0f,
	12.0f, 11.0f, 12.0f, 10.0f
};

static const VGfloat hintedGlyph101_Data[66] = 
{
	6.0f, 1.75f, 5.125f, 0.0f, 3.671875f, 0.0f, 3.140625f, 0.0f, 2.195313f,
	0.984375f, 1.25f, 1.96875f, 1.25f, 3.453125f, 1.25f, 5.015625f, 2.140625f,
	6.007813f, 3.03125f, 7.0f, 3.734375f, 7.0f, 4.71875f, 7.0f, 5.359375f,
	6.070313f, 6.0f, 5.140625f, 6.0f, 3.0f, 2.0f, 3.0f, 2.0f, 2.109375f,
	2.515625f, 1.554688f, 3.03125f, 1.0f, 3.953125f, 1.0f, 5.046875f, 1.0f,
	5.78125f, 2.0f, 6.0f, 1.75f, 5.0f, 4.0f, 5.0f, 4.921875f, 4.640625f,
	5.460938f, 4.28125f, 6.0f, 3.671875f, 6.0f, 3.015625f, 6.0f, 2.5625f,
	5.460938f, 2.109375f, 4.921875f, 2.0f, 4.0f, 5.0f, 4.0f
};

static const VGfloat hintedGlyph110_Data[96] = 
{
	7.0f, 0.0f, 4.0f, 0.0f, 4.0f, 1.0f, 4.6875f, 1.0f, 4.843750f, 1.171875f,
	5.0f, 1.34375f, 5.0f, 1.96875f, 5.0f, 4.5f, 5.0f, 5.296875f, 4.656250f,
	5.648438f, 4.3125f, 6.0f, 3.5625f, 6.0f, 2.8125f, 6.0f, 2.0f, 5.0f, 2.0f,
	1.859375f, 2.0f, 1.296875f, 2.195313f, 1.148438f, 2.390625f, 1.0f, 3.0f,
	1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.6875f, 1.0f, 0.84375f, 1.179688f,
	1.0f, 1.359375f, 1.0f, 1.984375f, 1.0f, 5.34375f, 1.0f, 5.71875f, 0.875f,
	5.859375f, 0.75f, 6.0f, 0.390625f, 6.0f, 0.0f, 6.0f, 0.0f, 7.0f, 1.765625f,
	7.0f, 2.0f, 7.0f, 2.0f, 6.0f, 3.09375f, 7.0f, 4.125f, 7.0f, 4.46875f, 7.0f,
	4.9375f, 6.460938f, 5.40625f, 5.921875f, 6.0f, 4.96875f, 6.0f, 2.0f, 6.0f,
	1.34375f, 6.195313f, 1.171875f, 6.390625f, 1.0f, 7.0f, 1.0f, 7.0f, 0.0f
};

static const VGfloat hintedGlyph112_Data[98] = 
{
	2.0f, 6.0f, 3.1875f, 7.0f, 4.25f, 7.0f, 5.140625f, 7.0f, 6.070313f, 5.914063f,
	7.0f, 4.828125f, 7.0f, 3.75f, 7.0f, 2.25f, 5.984375f, 1.125f, 4.96875f, 0.0f,
	3.53125f, 0.0f, 2.8125f, 0.0f, 2.0f, 0.21875f, 2.0f, -1.15625f, 2.0f, -1.75f,
	2.15625f, -1.875f, 2.3125f, -2.0f, 3.0f, -2.0f, 3.0f, -3.0f, 0.0f, -3.0f, 0.0f,
	-2.0f, 0.6875f, -2.0f, 0.84375f, -1.8125f, 1.0f, -1.625f, 1.0f, -1.0f, 1.0f,
	5.328125f, 1.0f, 5.71875f, 0.875f, 5.859375f, 0.75f, 6.0f, 0.390625f, 6.0f,
	0.0f, 6.0f, 0.0f, 7.0f, 1.78125f, 7.0f, 2.0f, 7.0f, 2.0f, 6.0f, 2.0f, 1.34375f,
	2.78125f, 1.0f, 3.6875f, 1.0f, 4.78125f, 1.0f, 5.390625f, 1.679688f, 6.0f,
	2.359375f, 6.0f, 3.515625f, 6.0f, 4.59375f, 5.390625f, 5.296875f, 4.78125f,
	6.0f, 3.6875f, 6.0f, 2.921875f, 6.0f, 2.0f, 5.0f, 2.0f, 1.34375f
};

#endif /* __PATHDATA_H__ */
