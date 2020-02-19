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

extern int    A10101_ParameterCoverage_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A10102_ParameterCoverage_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A20101_ParameterContext_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A20201_ParameterContext_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A20301_ParameterContext_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A30101_ParameterObject_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A30201_ParameterObject_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A30301_ParameterObject_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    A40101_ErrorOrdering_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    A40102_GetterConsistency_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    B10101_RenderingQualityPath_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    B10102_RenderingQualityPath_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    B10103_RenderingQualityPath_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    B10104_RenderingQualityPath_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    B10105_RenderingQualityPath_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    B10106_RenderingQualityPath_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    B10108_RenderingQualityPath_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    B10109_RenderingQualityPath_by_ATI(CT_File AnsFile, CT_File RefFile);

extern int    C10101_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10201_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10202_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10203_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10301_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10401_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10402_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10403_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10501_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10601_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10701_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10801_MatrixOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    C10802_MatrixOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    C20101_MatrixMode_by_HUONE(CT_File AnsFile, CT_File RefFile);

extern int    D10101_ClearingOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    D10201_ClearingOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    D10301_ClearingOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);

extern int    E10101_ScissoringOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    E10102_ScissoringOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    E10103_ScissoringOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    E10104_ScissoringOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    E10201_ScissoringOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    E10301_ScissoringOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    E10302_ScissoringOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);

extern int    F10101_MaskingOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    F10201_MaskingOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    F10202_MaskingOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    F10203_MaskingOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    F10204_MaskingOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    F20101_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20102_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20103_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20104_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20105_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20106_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    F20107_Masking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    G10101_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10102_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10103_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10201_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10202_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10203_PathSegment_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G10204_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10205_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10206_PathSegment_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G10301_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10302_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10303_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G10304_PathSegment_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20101_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20102_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20201_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20301_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20302_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20303_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20304_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20401_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20402_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20501_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20502_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20503_PathOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G20601_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20602_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20603_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20604_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20605_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20606_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20607_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20608_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20609_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20610_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20701_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20702_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20703_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20704_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20801_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20802_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20803_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20804_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20901_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20902_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20903_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G20904_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G21001_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G21002_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G21003_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G21004_PathOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G30101_PathStroking_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G30102_PathStroking_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G30103_PathStroking_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G30104_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30106_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30107_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30108_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30110_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30111_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30112_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30114_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30115_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30116_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30117_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30118_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30119_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30120_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30122_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30123_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30124_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30125_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30126_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30127_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30128_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30201_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30203_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30204_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30205_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30206_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30207_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30208_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30209_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30210_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30211_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30212_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30213_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30214_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30215_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30216_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30217_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30218_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30219_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30220_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30221_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30222_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30223_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30224_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30225_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30226_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30228_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30229_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30230_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30231_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30232_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30233_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30234_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30235_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30236_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30237_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30238_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30239_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30240_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30241_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30242_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30243_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30244_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30245_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30246_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30247_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30248_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30249_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30250_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30251_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30252_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30253_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30254_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30255_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30256_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30257_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30258_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30259_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30260_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30261_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30262_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30263_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30264_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30265_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30266_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30267_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30268_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30269_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30270_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30271_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30272_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30273_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30274_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30275_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30276_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30277_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30278_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30279_PathStroking_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G30301_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30302_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30303_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30304_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30305_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30306_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30307_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30308_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G30309_PathStroking_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G40101_PathDashing_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G40102_PathDashing_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G40103_PathDashing_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50101_PathFilling_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G50102_PathFilling_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G50103_PathFilling_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G50104_PathFilling_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G50105_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50106_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50107_PathFilling_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    G50108_PathFilling_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    G50109_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50110_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50111_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50112_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G50113_PathFilling_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    G60101_JoinStyles_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70101_Arcs_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70102_Stroking_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70103_Clipping_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70104_PointAlongPath_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70105_PathBounds_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70106_PathOps_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70107_PathTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70108_Dashing_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    G70109_PathError_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    H10101_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10201_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10202_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10203_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10301_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10302_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10316_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10317_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10318_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10319_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10320_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10321_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10322_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10323_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10324_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10325_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10326_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10327_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10328_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10329_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10330_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10331_ImageConversion_by_ATI(CT_File AnsFile, CT_File RefFile);
extern int    H10401_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10402_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10403_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10501_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10601_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10701_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10702_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H10801_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10901_ImageOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    H10902_ImageOperation_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H20101_ImageQuality_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    H30101_ImageMode_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30201_ImageError_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30202_ImageBlit_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30203_ImageClamping_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30204_ImageChildren_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30205_ImageChildren_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    H30206_ImageDithering_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    I10101_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I10102_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I10103_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I10104_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I10201_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I10202_PaintOperation_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I20101_PaintFlatColor_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I30101_PaintGradient_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I30102_PaintGradient_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I30103_PaintGradient_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I30104_PaintGradient_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    I30201_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30202_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30203_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30204_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30205_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30206_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30207_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30208_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30209_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30301_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30302_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30303_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30304_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30305_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30306_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30307_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30308_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I30309_PaintGradient_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40101_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40102_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40103_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40104_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40105_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    I40106_PaintPatternImage_by_HYBRID(CT_File AnsFile, CT_File RefFile);

extern int    J10101_FilterColorMatrix_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    J20101_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20102_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20103_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20104_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20201_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20202_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20203_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20204_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20301_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20302_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20303_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20304_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20305_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20306_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20307_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20308_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20309_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20310_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20311_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J20312_FilterConvolve_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    J30101_FilterLookupTable_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    J30201_FilterLookupTable_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    J40101_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40102_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40103_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40104_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40105_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40106_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40107_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40108_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40109_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    J40110_ImageFilter_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    K10101_BlendingNormal_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    K10102_BlendingNormal_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    K10201_BlendingMultiply_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    K10301_BlendingStencil_by_HYBRID(CT_File AnsFile, CT_File RefFile);
extern int    K20101_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20102_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20103_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20104_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20105_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20106_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20201_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20202_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20203_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20204_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20205_ColorTransform_by_NVIDIA(CT_File AnsFile, CT_File RefFile);
extern int    K20301_ColorTransform_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    K20401_Blending_by_NVIDIA(CT_File AnsFile, CT_File RefFile);

extern int    L10101_VGFontHandling_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10102_VGFontHandling_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10201_GlyphHandling_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10301_DrawGlyphTest_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10302_DrawGlyphTest_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10401_GlyphRendering_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10402_GlyphRendering_by_MTI(CT_File AnsFile, CT_File RefFile);
extern int    L10403_GlyphRendering_by_MTI(CT_File AnsFile, CT_File RefFile);

#if (TEST_OPTION_VGU != 0)
extern int    M10101_ParameterCoverage_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M10102_ParameterCoverage_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20101_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20201_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20202_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20301_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20401_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20501_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20601_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20602_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M20603_VguHLPrim_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M30101_VguImageWarping_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M30201_VguImageWarping_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    M30301_VguImageWarping_by_HUONE(CT_File AnsFile, CT_File RefFile);
#endif

extern int    N10101_MSAA_by_HUONE(CT_File AnsFile, CT_File RefFile);
extern int    N10201_MSAA_MASK_by_HUONE(CT_File AnsFile, CT_File RefFile);

/* rating code | rating func */
static const CT_RatingFuncRec func[] = {
    { "A10101",  A10101_ParameterCoverage_by_HUONE, 0 },
    { "A10102",  A10102_ParameterCoverage_by_HUONE, 0 },
    { "A20101",  A20101_ParameterContext_by_HUONE, 0 },
    { "A20201",  A20201_ParameterContext_by_HUONE, 0 },
    { "A20301",  A20301_ParameterContext_by_HUONE, 0 },
    { "A30101",  A30101_ParameterObject_by_HUONE, 0 },
    { "A30201",  A30201_ParameterObject_by_HUONE, 0 },
    { "A30301",  A30301_ParameterObject_by_HUONE, 0 },
    { "A40101",  A40101_ErrorOrdering_by_NVIDIA, 0 },
    { "A40102",  A40102_GetterConsistency_by_NVIDIA, 0 },
    
    { "B10101",  B10101_RenderingQualityPath_by_HYBRID, 0 },
    { "B10102",  B10102_RenderingQualityPath_by_HYBRID, 0 },
    { "B10103",  B10103_RenderingQualityPath_by_HYBRID, 0 },
    { "B10104",  B10104_RenderingQualityPath_by_HYBRID, 0 },
    { "B10105",  B10105_RenderingQualityPath_by_ATI, 0 },
    { "B10106",  B10106_RenderingQualityPath_by_ATI, 2 },
    { "B10108",  B10108_RenderingQualityPath_by_ATI, 0 },
    { "B10109",  B10109_RenderingQualityPath_by_ATI, 8 },
    
    { "C10101",  C10101_MatrixOperation_by_HUONE, 0 },
    { "C10201",  C10201_MatrixOperation_by_HUONE, 0 },
    { "C10202",  C10202_MatrixOperation_by_HUONE, 0 },
    { "C10203",  C10203_MatrixOperation_by_HUONE, 0 },
    { "C10301",  C10301_MatrixOperation_by_HUONE, 0 },
    { "C10401",  C10401_MatrixOperation_by_HUONE, 0 },
    { "C10402",  C10402_MatrixOperation_by_HUONE, 0 },
    { "C10403",  C10403_MatrixOperation_by_HUONE, 0 },    
    { "C10501",  C10501_MatrixOperation_by_HUONE, 0 },
    { "C10601",  C10601_MatrixOperation_by_HUONE, 0 },
    { "C10701",  C10701_MatrixOperation_by_HUONE, 0 },
    { "C10801",  C10801_MatrixOperation_by_HUONE, 0 },
    { "C10802",  C10802_MatrixOperation_by_HYBRID, 0 },
    { "C20101",  C20101_MatrixMode_by_HUONE, 0 },
    
    { "D10101",  D10101_ClearingOperation_by_HUONE, 0 },
    { "D10201",  D10201_ClearingOperation_by_HUONE, 0 },
    { "D10301",  D10301_ClearingOperation_by_HUONE, 0 },
    
    { "E10101",  E10101_ScissoringOperation_by_HUONE, 0 },
    { "E10102",  E10102_ScissoringOperation_by_HUONE, 0 },
    { "E10103",  E10103_ScissoringOperation_by_HUONE, 0 },
    { "E10104",  E10104_ScissoringOperation_by_HYBRID, 0 },
    { "E10201",  E10201_ScissoringOperation_by_HUONE, 0 },
    { "E10301",  E10301_ScissoringOperation_by_HUONE, 0 },
    { "E10302",  E10302_ScissoringOperation_by_HYBRID, 0 },
    
    { "F10101",  F10101_MaskingOperation_by_HUONE, 0 },
    { "F10201",  F10201_MaskingOperation_by_HUONE, 0 },
    { "F10202",  F10202_MaskingOperation_by_HYBRID, 0 },
    { "F10203",  F10203_MaskingOperation_by_HYBRID, 0 },
    { "F10204",  F10204_MaskingOperation_by_HYBRID, 0 },
    { "F20101",  F20101_Masking_by_NVIDIA, 0 },
    { "F20102",  F20102_Masking_by_NVIDIA, 6 },
    { "F20103",  F20103_Masking_by_NVIDIA, 0 },
    { "F20104",  F20104_Masking_by_NVIDIA, 18 },
    { "F20105",  F20105_Masking_by_NVIDIA, 0 },
    { "F20106",  F20106_Masking_by_NVIDIA, 0 },
    { "F20107",  F20107_Masking_by_NVIDIA, 24 },
    
    { "G10101",  G10101_PathSegment_by_HUONE, 0 },
    { "G10102",  G10102_PathSegment_by_HUONE, 0 },
    { "G10103",  G10103_PathSegment_by_HUONE, 0 },
    { "G10201",  G10201_PathSegment_by_HUONE, 0 },
    { "G10202",  G10202_PathSegment_by_HUONE, 0 },
    { "G10203",  G10203_PathSegment_by_HYBRID, 0 },
    { "G10204",  G10204_PathSegment_by_HUONE, 0 },
    { "G10205",  G10205_PathSegment_by_HUONE, 0 },
    { "G10206",  G10206_PathSegment_by_HYBRID, 0 },
    { "G10301",  G10301_PathSegment_by_HUONE, 0 },
    { "G10302",  G10302_PathSegment_by_HUONE, 0 },
    { "G10303",  G10303_PathSegment_by_HUONE, 0 },
    { "G10304",  G10304_PathSegment_by_HUONE, 0 },
    { "G20101",  G20101_PathOperation_by_HUONE, 0 },
    { "G20102",  G20102_PathOperation_by_HUONE, 0 },
    { "G20201",  G20201_PathOperation_by_HUONE, 0 },
    { "G20301",  G20301_PathOperation_by_HUONE, 0 },
    { "G20302",  G20302_PathOperation_by_HUONE, 0 },
    { "G20303",  G20303_PathOperation_by_HUONE, 0 },
    { "G20304",  G20304_PathOperation_by_HUONE, 0 },
    { "G20401",  G20401_PathOperation_by_HUONE, 0 },
    { "G20402",  G20402_PathOperation_by_HUONE, 0 },
    { "G20501",  G20501_PathOperation_by_HUONE, 0 },
    { "G20502",  G20502_PathOperation_by_HUONE, 0 },
    { "G20503",  G20503_PathOperation_by_HYBRID, 4 },
    { "G20601",  G20601_PathOperation_by_HUONE, 0 },
    { "G20602",  G20602_PathOperation_by_HUONE, 0 },
    { "G20603",  G20603_PathOperation_by_HUONE, 0 },
    { "G20604",  G20604_PathOperation_by_HUONE, 0 },
    { "G20605",  G20605_PathOperation_by_HUONE, 0 },
    { "G20606",  G20606_PathOperation_by_HUONE, 0 },
    { "G20607",  G20607_PathOperation_by_HUONE, 0 },
    { "G20608",  G20608_PathOperation_by_HUONE, 0 },
    { "G20609",  G20609_PathOperation_by_HUONE, 0 },
    { "G20610",  G20610_PathOperation_by_HUONE, 0 },
    { "G20701",  G20701_PathOperation_by_HUONE, 0 },
    { "G20702",  G20702_PathOperation_by_HUONE, 0 },
    { "G20703",  G20703_PathOperation_by_HUONE, 0 },
    { "G20704",  G20704_PathOperation_by_HUONE, 0 },
    { "G20801",  G20801_PathOperation_by_HUONE, 0 },
    { "G20802",  G20802_PathOperation_by_HUONE, 0 },
    { "G20803",  G20803_PathOperation_by_HUONE, 0 },
    { "G20804",  G20804_PathOperation_by_HUONE, 0 },
    { "G20901",  G20901_PathOperation_by_HUONE, 0 },
    { "G20902",  G20902_PathOperation_by_HUONE, 0 },
    { "G20903",  G20903_PathOperation_by_HUONE, 0 },
    { "G20904",  G20904_PathOperation_by_HUONE, 0 },
    { "G21001",  G21001_PathOperation_by_HUONE, 3 },
    { "G21002",  G21002_PathOperation_by_HUONE, 0 },
    { "G21003",  G21003_PathOperation_by_HUONE, 0 },
    { "G21004",  G21004_PathOperation_by_HUONE, 0 },
    { "G30101",  G30101_PathStroking_by_HUONE, 0 },
    { "G30102",  G30102_PathStroking_by_HUONE, 0 },
    { "G30103",  G30103_PathStroking_by_HUONE, 0 },
    { "G30104",  G30104_PathStroking_by_HYBRID, 0 },
    { "G30106",  G30106_PathStroking_by_HYBRID, 0 },
    { "G30107",  G30107_PathStroking_by_ATI, 0 },
    { "G30108",  G30108_PathStroking_by_ATI, 0 },
    { "G30110",  G30110_PathStroking_by_ATI, 0 },
    { "G30111",  G30111_PathStroking_by_ATI, 0 },
    { "G30112",  G30112_PathStroking_by_ATI, 0 },
    { "G30114",  G30114_PathStroking_by_ATI, 0 },
    { "G30115",  G30115_PathStroking_by_ATI, 0 },
    { "G30116",  G30116_PathStroking_by_ATI, 0 },
    { "G30117",  G30117_PathStroking_by_ATI, 0 },
    { "G30118",  G30118_PathStroking_by_ATI, 0 },
    { "G30119",  G30119_PathStroking_by_ATI, 0 },
    { "G30120",  G30120_PathStroking_by_ATI, 0 },
    { "G30122",  G30122_PathStroking_by_HYBRID, 0 },
    { "G30123",  G30123_PathStroking_by_HYBRID, 0 },
    { "G30124",  G30124_PathStroking_by_HYBRID, 0 },
    { "G30125",  G30125_PathStroking_by_HYBRID, 0 },
    { "G30126",  G30126_PathStroking_by_HYBRID, 0 },
    { "G30127",  G30127_PathStroking_by_HYBRID, 0 },
    { "G30128",  G30128_PathStroking_by_HYBRID, 0 },
    { "G30201",  G30201_PathStroking_by_HYBRID, 0 },
    { "G30203",  G30203_PathStroking_by_HYBRID, 0 },
    { "G30204",  G30204_PathStroking_by_HYBRID, 0 },
    { "G30205",  G30205_PathStroking_by_HYBRID, 0 },
    { "G30206",  G30206_PathStroking_by_HYBRID, 0 },
    { "G30207",  G30207_PathStroking_by_HYBRID, 0 },
    { "G30208",  G30208_PathStroking_by_ATI, 0 },
    { "G30209",  G30209_PathStroking_by_ATI, 0 },
    { "G30210",  G30210_PathStroking_by_ATI, 0 },
    { "G30211",  G30211_PathStroking_by_ATI, 0 },
    { "G30212",  G30212_PathStroking_by_ATI, 0 },
    { "G30213",  G30213_PathStroking_by_ATI, 0 },
    { "G30214",  G30214_PathStroking_by_ATI, 0 },
    { "G30215",  G30215_PathStroking_by_ATI, 0 },
    { "G30216",  G30216_PathStroking_by_ATI, 0 },
    { "G30217",  G30217_PathStroking_by_ATI, 0 },
    { "G30218",  G30218_PathStroking_by_ATI, 0 },
    { "G30219",  G30219_PathStroking_by_ATI, 0 },
    { "G30220",  G30220_PathStroking_by_ATI, 0 },
    { "G30221",  G30221_PathStroking_by_ATI, 0 },
    { "G30222",  G30222_PathStroking_by_ATI, 0 },
    { "G30223",  G30223_PathStroking_by_ATI, 0 },
    { "G30224",  G30224_PathStroking_by_ATI, 0 },
    { "G30225",  G30225_PathStroking_by_ATI, 0 },
    { "G30226",  G30226_PathStroking_by_ATI, 0 },
    { "G30228",  G30228_PathStroking_by_ATI, 30 },
    { "G30229",  G30229_PathStroking_by_ATI, 0 },
    { "G30230",  G30230_PathStroking_by_ATI, 0 },
    { "G30231",  G30231_PathStroking_by_ATI, 0 },
    { "G30232",  G30232_PathStroking_by_ATI, 0 },
    { "G30233",  G30233_PathStroking_by_ATI, 0 },
    { "G30234",  G30234_PathStroking_by_ATI, 0 },
    { "G30235",  G30235_PathStroking_by_ATI, 0 },
    { "G30236",  G30236_PathStroking_by_ATI, 4 },
    { "G30237",  G30237_PathStroking_by_ATI, 0 },
    { "G30238",  G30238_PathStroking_by_ATI, 0 },
    { "G30239",  G30239_PathStroking_by_ATI, 0 },
    { "G30240",  G30240_PathStroking_by_ATI, 0 },
    { "G30241",  G30241_PathStroking_by_ATI, 0 },
    { "G30242",  G30242_PathStroking_by_ATI, 0 },
    { "G30243",  G30243_PathStroking_by_ATI, 0 },
    { "G30244",  G30244_PathStroking_by_ATI, 0 },
    { "G30245",  G30245_PathStroking_by_ATI, 0 },
    { "G30246",  G30246_PathStroking_by_ATI, 0 },
    { "G30247",  G30247_PathStroking_by_ATI, 0 },
    { "G30248",  G30248_PathStroking_by_ATI, 0 },
    { "G30249",  G30249_PathStroking_by_ATI, 0 },
    { "G30250",  G30250_PathStroking_by_ATI, 0 },
    { "G30251",  G30251_PathStroking_by_ATI, 4 },
    { "G30252",  G30252_PathStroking_by_ATI, 4 },
    { "G30253",  G30253_PathStroking_by_ATI, 4 },
    { "G30254",  G30254_PathStroking_by_ATI, 0 },
    { "G30255",  G30255_PathStroking_by_ATI, 0 },
    { "G30256",  G30256_PathStroking_by_ATI, 0 },
    { "G30257",  G30257_PathStroking_by_ATI, 0 },
    { "G30258",  G30258_PathStroking_by_ATI, 0 },
    { "G30259",  G30259_PathStroking_by_ATI, 0 },
    { "G30260",  G30260_PathStroking_by_ATI, 0 },
    { "G30261",  G30261_PathStroking_by_ATI, 4 },
    { "G30262",  G30262_PathStroking_by_ATI, 0 },
    { "G30263",  G30263_PathStroking_by_ATI, 0 },
    { "G30264",  G30264_PathStroking_by_ATI, 0 },
    { "G30265",  G30265_PathStroking_by_ATI, 0 },
    { "G30266",  G30266_PathStroking_by_ATI, 0 },
    { "G30267",  G30267_PathStroking_by_ATI, 0 },
    { "G30268",  G30268_PathStroking_by_ATI, 0 },
    { "G30269",  G30269_PathStroking_by_ATI, 0 },
    { "G30270",  G30270_PathStroking_by_ATI, 0 },
    { "G30271",  G30271_PathStroking_by_ATI, 0 },
    { "G30272",  G30272_PathStroking_by_ATI, 0 },
    { "G30273",  G30273_PathStroking_by_ATI, 0 },
    { "G30274",  G30274_PathStroking_by_ATI, 0 },
    { "G30275",  G30275_PathStroking_by_ATI, 0 },
    { "G30276",  G30276_PathStroking_by_HYBRID, 0 },
    { "G30277",  G30277_PathStroking_by_HYBRID, 0 },
    { "G30278",  G30278_PathStroking_by_HYBRID, 0 },
    { "G30279",  G30279_PathStroking_by_HYBRID, 0 },
    { "G30301",  G30301_PathStroking_by_ATI, 0 },
    { "G30302",  G30302_PathStroking_by_ATI, 0 },
    { "G30303",  G30303_PathStroking_by_ATI, 0 },
    { "G30304",  G30304_PathStroking_by_ATI, 0 },
    { "G30305",  G30305_PathStroking_by_ATI, 0 },
    { "G30306",  G30306_PathStroking_by_ATI, 0 },
    { "G30307",  G30307_PathStroking_by_ATI, 0 },
    { "G30308",  G30308_PathStroking_by_ATI, 0 },
    { "G30309",  G30309_PathStroking_by_ATI, 0 },
    { "G40101",  G40101_PathDashing_by_HUONE, 0 },
    { "G40102",  G40102_PathDashing_by_HYBRID, 0 },
    { "G40103",  G40103_PathDashing_by_HYBRID, 0 },
    { "G50101",  G50101_PathFilling_by_HUONE, 0 },
    { "G50102",  G50102_PathFilling_by_HUONE, 0 },
    { "G50103",  G50103_PathFilling_by_HUONE, 0 },
    { "G50104",  G50104_PathFilling_by_HUONE, 0 },
    { "G50105",  G50105_PathFilling_by_HYBRID, 0 },
    { "G50106",  G50106_PathFilling_by_HYBRID, 0 },
    { "G50107",  G50107_PathFilling_by_HUONE, 0 },
    { "G50108",  G50108_PathFilling_by_ATI, 0 },
    { "G50109",  G50109_PathFilling_by_HYBRID, 0 },
    { "G50110",  G50110_PathFilling_by_HYBRID, 0 },
    { "G50111",  G50111_PathFilling_by_HYBRID, 0 },
    { "G50112",  G50112_PathFilling_by_HYBRID, 0 },
    { "G50113",  G50113_PathFilling_by_HYBRID, 0 },
    { "G60101",  G60101_JoinStyles_by_NVIDIA, 121 },
    { "G70101",  G70101_Arcs_by_NVIDIA, 12 },
    { "G70102",  G70102_Stroking_by_NVIDIA, 18 },
    { "G70103",  G70103_Clipping_by_NVIDIA, 9 },
    { "G70104",  G70104_PointAlongPath_by_NVIDIA, 6 },
    { "G70105",  G70105_PathBounds_by_NVIDIA, 4 },
    { "G70106",  G70106_PathOps_by_NVIDIA, 4 },
    { "G70107",  G70107_PathTransform_by_NVIDIA, 0 },
    { "G70108",  G70108_Dashing_by_NVIDIA, 4 },
    { "G70109",  G70109_PathError_by_NVIDIA, 0 },
    
    { "H10101",  H10101_ImageOperation_by_HUONE, 0 },
    { "H10201",  H10201_ImageOperation_by_HUONE, 0 },
    { "H10202",  H10202_ImageOperation_by_HUONE, 0 },
    { "H10203",  H10203_ImageOperation_by_HYBRID, 0 },
    { "H10301",  H10301_ImageOperation_by_HUONE, 0 },
    { "H10302",  H10302_ImageOperation_by_HYBRID, 0 },
    { "H10316",  H10316_ImageOperation_by_HYBRID, 3 },
    { "H10317",  H10317_ImageOperation_by_HYBRID, 0 },
    { "H10318",  H10318_ImageOperation_by_HYBRID, 0 },
    { "H10319",  H10319_ImageOperation_by_HYBRID, 0 },
    { "H10320",  H10320_ImageOperation_by_HYBRID, 0 },
    { "H10321",  H10321_ImageOperation_by_HYBRID, 0 },
    { "H10322",  H10322_ImageOperation_by_HYBRID, 0 },
    { "H10323",  H10323_ImageOperation_by_HYBRID, 0 },
    { "H10324",  H10324_ImageOperation_by_HYBRID, 0 },
    { "H10325",  H10325_ImageOperation_by_HYBRID, 0 },
    { "H10326",  H10326_ImageOperation_by_HYBRID, 0 },
    { "H10327",  H10327_ImageOperation_by_HYBRID, 0 },
    { "H10328",  H10328_ImageOperation_by_HYBRID, 0 },
    { "H10329",  H10329_ImageOperation_by_HYBRID, 0 },
    { "H10330",  H10330_ImageOperation_by_HYBRID, 0 },
    { "H10331",  H10331_ImageConversion_by_ATI, 39 },
    { "H10401",  H10401_ImageOperation_by_HUONE, 0 },
    { "H10402",  H10402_ImageOperation_by_HYBRID, 0 },
    { "H10403",  H10403_ImageOperation_by_HYBRID, 0 },
    { "H10501",  H10501_ImageOperation_by_HUONE, 0 },
    { "H10601",  H10601_ImageOperation_by_HUONE, 0 },
    { "H10701",  H10701_ImageOperation_by_HUONE, 0 },
    { "H10702",  H10702_ImageOperation_by_HYBRID, 0 },
    { "H10801",  H10801_ImageOperation_by_HUONE, 0 },
    { "H10901",  H10901_ImageOperation_by_HUONE, 0 },
    { "H10902",  H10902_ImageOperation_by_HYBRID, 0 },
    { "H20101",  H20101_ImageQuality_by_HYBRID, 0 },
    { "H30101",  H30101_ImageMode_by_NVIDIA, 18 },
    { "H30201",  H30201_ImageError_by_NVIDIA, 0 },
    { "H30202",  H30202_ImageBlit_by_NVIDIA, 21 },
    { "H30203",  H30203_ImageClamping_by_NVIDIA, 8 },
    { "H30204",  H30204_ImageChildren_by_NVIDIA, 0 },
    { "H30205",  H30205_ImageChildren_by_NVIDIA, 0 },
#if 0  /* for CTS1.1 RC9 */
    { "H30206",  H30206_ImageDithering_by_NVIDIA, 6 },
#endif

    { "I10101",  I10101_PaintOperation_by_HUONE, 0 },
    { "I10102",  I10102_PaintOperation_by_HUONE, 0 },
    { "I10103",  I10103_PaintOperation_by_HUONE, 0 },
    { "I10104",  I10104_PaintOperation_by_HUONE, 0 },
    { "I10201",  I10201_PaintOperation_by_HUONE, 0 },
    { "I10202",  I10202_PaintOperation_by_HUONE, 0 },
    { "I20101",  I20101_PaintFlatColor_by_HUONE, 0 },
    { "I30101",  I30101_PaintGradient_by_HUONE, 0 },
    { "I30102",  I30102_PaintGradient_by_HUONE, 0 },
    { "I30103",  I30103_PaintGradient_by_HUONE, 0 },
    { "I30104",  I30104_PaintGradient_by_HUONE, 0 },
    { "I30201",  I30201_PaintGradient_by_HYBRID, 0 },
    { "I30202",  I30202_PaintGradient_by_HYBRID, 0 },
    { "I30203",  I30203_PaintGradient_by_HYBRID, 0 },
    { "I30204",  I30204_PaintGradient_by_HYBRID, 0 },
    { "I30205",  I30205_PaintGradient_by_HYBRID, 0 },
    { "I30206",  I30206_PaintGradient_by_HYBRID, 0 },
    { "I30207",  I30207_PaintGradient_by_HYBRID, 0 },
    { "I30208",  I30208_PaintGradient_by_HYBRID, 0 },
    { "I30209",  I30209_PaintGradient_by_HYBRID, 0 },
    { "I30301",  I30301_PaintGradient_by_HYBRID, 0 },
    { "I30302",  I30302_PaintGradient_by_HYBRID, 0 },
    { "I30303",  I30303_PaintGradient_by_HYBRID, 0 },
    { "I30304",  I30304_PaintGradient_by_HYBRID, 0 },
    { "I30305",  I30305_PaintGradient_by_HYBRID, 0 },
    { "I30306",  I30306_PaintGradient_by_HYBRID, 0 },
    { "I30307",  I30307_PaintGradient_by_HYBRID, 0 },
    { "I30308",  I30308_PaintGradient_by_HYBRID, 0 },
    { "I30309",  I30309_PaintGradient_by_HYBRID, 0 },
    { "I40101",  I40101_PaintPatternImage_by_HYBRID, 0 },
    { "I40102",  I40102_PaintPatternImage_by_HYBRID, 0 },
    { "I40103",  I40103_PaintPatternImage_by_HYBRID, 0 },
    { "I40104",  I40104_PaintPatternImage_by_HYBRID, 0 },
    { "I40105",  I40105_PaintPatternImage_by_HYBRID, 0 },
    { "I40106",  I40106_PaintPatternImage_by_HYBRID, 0 },
    
    { "J10101",  J10101_FilterColorMatrix_by_HUONE, 0 },
    { "J20101",  J20101_FilterConvolve_by_HYBRID, 6 },
    { "J20102",  J20102_FilterConvolve_by_HYBRID, 4 },
    { "J20103",  J20103_FilterConvolve_by_HYBRID, 12 },
    { "J20104",  J20104_FilterConvolve_by_HYBRID, 4 },
    { "J20201",  J20201_FilterConvolve_by_HYBRID, 6 },
    { "J20202",  J20202_FilterConvolve_by_HYBRID, 4 },
    { "J20203",  J20203_FilterConvolve_by_HYBRID, 12 },
    { "J20204",  J20204_FilterConvolve_by_HYBRID, 4 },
    { "J20301",  J20301_FilterConvolve_by_HYBRID, 0 },
    { "J20302",  J20302_FilterConvolve_by_HYBRID, 0 },
    { "J20303",  J20303_FilterConvolve_by_HYBRID, 0 },
    { "J20304",  J20304_FilterConvolve_by_HYBRID, 0 },
    { "J20305",  J20305_FilterConvolve_by_HYBRID, 0 },
    { "J20306",  J20306_FilterConvolve_by_HYBRID, 0 },
    { "J20307",  J20307_FilterConvolve_by_HYBRID, 0 },
    { "J20308",  J20308_FilterConvolve_by_HYBRID, 0 },
    { "J20309",  J20309_FilterConvolve_by_HYBRID, 0 },
    { "J20310",  J20310_FilterConvolve_by_HYBRID, 0 },
    { "J20311",  J20311_FilterConvolve_by_HYBRID, 0 },
    { "J20312",  J20312_FilterConvolve_by_HYBRID, 0 },
    { "J30101",  J30101_FilterLookupTable_by_HUONE, 0 },
    { "J30201",  J30201_FilterLookupTable_by_HUONE, 0 },
    { "J40101",  J40101_ImageFilter_by_NVIDIA, 0 },
    { "J40102",  J40102_ImageFilter_by_NVIDIA, 4 },
    { "J40103",  J40103_ImageFilter_by_NVIDIA, 4 },
    { "J40104",  J40104_ImageFilter_by_NVIDIA, 4 },
    { "J40105",  J40105_ImageFilter_by_NVIDIA, 0 },
    { "J40106",  J40106_ImageFilter_by_NVIDIA, 4 },
    { "J40107",  J40107_ImageFilter_by_NVIDIA, 0 },
    { "J40108",  J40108_ImageFilter_by_NVIDIA, 15 },
    { "J40109",  J40109_ImageFilter_by_NVIDIA, 15 },
    { "J40110",  J40110_ImageFilter_by_NVIDIA, 0 },

    { "K10101",  K10101_BlendingNormal_by_HYBRID, 10 },
    { "K10102",  K10102_BlendingNormal_by_HYBRID, 10 },
    { "K10201",  K10201_BlendingMultiply_by_HYBRID, 10 },
    { "K10301",  K10301_BlendingStencil_by_HYBRID, 10 },
    { "K20101",  K20101_ColorTransform_by_NVIDIA, 0 },
    { "K20102",  K20102_ColorTransform_by_NVIDIA, 3 },
    { "K20103",  K20103_ColorTransform_by_NVIDIA, 0 },
    { "K20104",  K20104_ColorTransform_by_NVIDIA, 3 },
    { "K20105",  K20105_ColorTransform_by_NVIDIA, 0 },
    { "K20106",  K20106_ColorTransform_by_NVIDIA, 0 },
    { "K20201",  K20201_ColorTransform_by_NVIDIA, 0 },
    { "K20202",  K20202_ColorTransform_by_NVIDIA, 0 },
    { "K20203",  K20203_ColorTransform_by_NVIDIA, 24 },
    { "K20204",  K20204_ColorTransform_by_NVIDIA, 0 },
    { "K20205",  K20205_ColorTransform_by_NVIDIA, 0 },
    { "K20301",  K20301_ColorTransform_by_HUONE, 0 },
    { "K20401",  K20401_Blending_by_NVIDIA, 10 },

    { "L10101",  L10101_VGFontHandling_by_MTI, 0 },
    { "L10102",  L10102_VGFontHandling_by_MTI, 0 },
    { "L10201",  L10201_GlyphHandling_by_MTI, 0 },
    { "L10301",  L10301_DrawGlyphTest_by_MTI, 0 },
    { "L10302",  L10302_DrawGlyphTest_by_MTI, 0 },
    { "L10401",  L10401_GlyphRendering_by_MTI, 0 },
    { "L10402",  L10402_GlyphRendering_by_MTI, 0 },
    { "L10403",  L10403_GlyphRendering_by_MTI, 0 },

#if (TEST_OPTION_VGU != 0)
    { "M10101",  M10101_ParameterCoverage_by_HUONE, 0 },
    { "M10102",  M10102_ParameterCoverage_by_HUONE, 0 },
    { "M20101",  M20101_VguHLPrim_by_HUONE, 0 },
    { "M20201",  M20201_VguHLPrim_by_HUONE, 0 },
    { "M20202",  M20202_VguHLPrim_by_HUONE, 0 },
    { "M20301",  M20301_VguHLPrim_by_HUONE, 0 },
    { "M20401",  M20401_VguHLPrim_by_HUONE, 0 },
    { "M20501",  M20501_VguHLPrim_by_HUONE, 0 },
    { "M20601",  M20601_VguHLPrim_by_HUONE, 0 },
    { "M20602",  M20602_VguHLPrim_by_HUONE, 0 },
    { "M20603",  M20603_VguHLPrim_by_HUONE, 0 },
    { "M30101",  M30101_VguImageWarping_by_HUONE, 0 },
    { "M30201",  M30201_VguImageWarping_by_HUONE, 0 },
    { "M30301",  M30301_VguImageWarping_by_HUONE, 0 },
#endif

    { "N10101",  N10101_MSAA_by_HUONE, 6 },
    { "N10201",  N10201_MSAA_MASK_by_HUONE, 6 },
};

