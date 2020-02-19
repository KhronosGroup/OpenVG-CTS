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

static const int pukki_16x16_width = 16;
static const int pukki_16x16_height = 16;
static const int pukki_16x16_stride = 64;

static const VGuint pukki_16x16_data[256] =
{
	0xffffff00, 0xffffff00, 0xf4f4f400, 0xf8f8f800,
	0xdfdfdf00, 0xbabcbc43, 0xafb0b09d, 0xb4b4b48f,
	0xd2d2d238, 0xdedede01, 0xcfcfcf04, 0xe9e9e900,
	0xffffff00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xf7f7f700, 0xf9f9f900,
	0xaaa8a890, 0x7b6f6fff, 0xdfdcdcff, 0xd2d3d3ff,
	0x8c8c8cfa, 0xb7b7b7ce, 0xc5c5c5d6, 0xa5a5a5ba,
	0xdbdbdb2b, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xffffff00, 0xb0b2b155,
	0x756b6be8, 0x6b5656ff, 0x928888ff, 0x898c8cff,
	0x858a8aff, 0xaeb2b2ff, 0xd2d3d3ff, 0xd6d6d69e,
	0xe4e3e31e, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xd9dada33, 0x656c6cff,
	0x654848ff, 0x7d1617ff, 0x751719ff, 0x6e2324ff,
	0x652f30ff, 0x523b3bff, 0x4e4949fb, 0x908e8ea4,
	0xe5e5e500, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xc3c5c550, 0x6b6b6bff,
	0xa07373ff, 0xa40000ff, 0xa60001ff, 0x9b0000ff,
	0x880000ff, 0x680000ff, 0x360000ff, 0x321d1dff,
	0xcecfcf41, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xae5f60a6, 0xa71212ff,
	0xbb0c10ff, 0xb80206ff, 0xc80307ff, 0xc20307ff,
	0xb50307ff, 0x9e0306ff, 0x720000ff, 0x3b1919ff,
	0xa4adadbd, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xa84548c1, 0xaf0000ff,
	0xaf0104ff, 0xb60307ff, 0xd30308ff, 0xcd0105ff,
	0xc30004ff, 0xa90205ff, 0x760102ff, 0x751616ff,
	0xc29c9c80, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xd096976f, 0xb20000ff,
	0xb30104ff, 0xb20306ff, 0xd70001ff, 0xba060aff,
	0x9a1417ff, 0x8d0507ff, 0x730102ff, 0x950305fd,
	0xd8bebf33, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xfaf5f50c, 0xcf5154b5,
	0xc50000ff, 0xb60000ff, 0x9d2f31ff, 0x827979ff,
	0x6b7777ff, 0x423030ff, 0x750000ff, 0xb14b4eb9,
	0xf8ffff00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xffffff00, 0xf5e6e602,
	0xe8a7a84a, 0xad4849e9, 0xb2bbbbff, 0xbfc6c6ff,
	0xa1a7a7ff, 0x616464ff, 0x8f2728df, 0xedd3d42d,
	0xfcfefe00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xffffff00, 0xf2dcdd00,
	0xfcf5f600, 0xe5eae954, 0xb78d85fb, 0x967a73ff,
	0x985a53ff, 0x8f7f7dde, 0xe5d4d519, 0xffffff00,
	0xfefdfd00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xfefefe00, 0xf7eded00,
	0xfaf3f400, 0xffffff00, 0xc3aaa6bc, 0x976f6eff,
	0x9f7e7de9, 0xe4d5d33f, 0xffffff00, 0xfefdfd00,
	0xfefefe00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xfbfbfb00, 0xfcfdfd00,
	0xfcfcfc00, 0xfeffff00, 0xe9d2d334, 0x760b0cfc,
	0x8d787893, 0xffffff00, 0xfdfdfd00, 0xfdfcfc00,
	0xfdfcfc00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xffffff00, 0xba898a7b,
	0x8b7171a4, 0xfbfbfb0d, 0xfffefe00, 0xfefefe00,
	0xfefefe00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xefefef00, 0xefefef00,
	0xefefef00, 0xefefef00, 0xf0f0f000, 0xeaeded49,
	0xc5c4c5ff, 0xd1d1d17f, 0xffffff00, 0xfbfbfb00,
	0xfbfbfb00, 0xffffff00, 0xffffff00, 0xffffff00,
	0xffffff00, 0xffffff00, 0xf4f4f400, 0xf4f4f400,
	0xf4f4f400, 0xf4f4f400, 0xf4f4f400, 0xf4f4f41e,
	0xf9fafa8f, 0xf3f3f330, 0xffffff00, 0xfefefe00,
	0xfefefe00, 0xffffff00, 0xffffff00, 0xffffff00
};
