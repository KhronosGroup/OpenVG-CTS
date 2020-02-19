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

#include "main.h"

extern CT_Result checkGetError( void );
extern CT_Result checkFlush( void );
extern CT_Result checkFinish( void );

/* Set/Get Parameter */
extern CT_Result checkSetf( void );
extern CT_Result checkSeti( void );
extern CT_Result checkSetfv( void );
extern CT_Result checkSetiv( void );
extern CT_Result checkGetVectorSize( void );
extern CT_Result checkGetf( void );
extern CT_Result checkGeti( void );
extern CT_Result checkGetfv( void );
extern CT_Result checkGetiv( void );
extern CT_Result checkSetParameterf( void );
extern CT_Result checkSetParameteri( void );
extern CT_Result checkSetParameterfv( void );
extern CT_Result checkSetParameteriv( void );
extern CT_Result checkGetParameterVectorSize( void );
extern CT_Result checkGetParameterf( void );
extern CT_Result checkGetParameteri( void );
extern CT_Result checkGetParameterfv( void );
extern CT_Result checkGetParameteriv( void );

/* Matrix Manipulation */
extern CT_Result checkLoadIdentity( void );
extern CT_Result checkLoadMatrix( void );
extern CT_Result checkGetMatrix( void );
extern CT_Result checkMultMatrix( void );
extern CT_Result checkTranslate( void );
extern CT_Result checkScale( void );
extern CT_Result checkShear( void );
extern CT_Result checkRotate( void );

/* Masking */
extern CT_Result checkMask( void );
extern CT_Result checkRenderToMask( void );
extern CT_Result checkCreateMaskLayer( void );
extern CT_Result checkDestroyMaskLayer( void );
extern CT_Result checkFillMaskLayer( void );
extern CT_Result checkCopyMask( void );

/* Clearing */
extern CT_Result checkClear( void );

extern CT_Result checkCreatePath( void );
extern CT_Result checkClearPath( void );
extern CT_Result checkDestroyPath( void );
extern CT_Result checkGetPathCapabilities( void );
extern CT_Result checkRemovePathCapabilities( void );
extern CT_Result checkAppendPath( void );
extern CT_Result checkAppendPathData( void );
extern CT_Result checkModifyPathCoords( void );
extern CT_Result checkTransformPath( void );
extern CT_Result checkInterpolatePath( void );
extern CT_Result checkPathLength( void );
extern CT_Result checkPointAlongPath( void );
extern CT_Result checkPathBounds( void );
extern CT_Result checkPathTransformedBounds( void );
extern CT_Result checkDrawPath( void );

/* Paint */
extern CT_Result checkCreatePaint( void );
extern CT_Result checkDestroyPaint( void );
extern CT_Result checkSetPaint( void );
extern CT_Result checkGetPaint( void );
extern CT_Result checkSetColor( void );
extern CT_Result checkGetColor( void );
extern CT_Result checkPaintPattern( void );

/* Images */
extern CT_Result checkCreateImage( void );
extern CT_Result checkDestroyImage( void );
extern CT_Result checkClearImage( void );
extern CT_Result checkImageSubData( void );
extern CT_Result checkGetImageSubData( void );
extern CT_Result checkChildImage( void );
extern CT_Result checkGetParent( void );
extern CT_Result checkCopyImage( void );
extern CT_Result checkDrawImage( void );
extern CT_Result checkSetPixels( void );
extern CT_Result checkWritePixels( void );
extern CT_Result checkGetPixels( void );
extern CT_Result checkReadPixels( void );
extern CT_Result checkCopyPixels( void );

/* Text */
extern CT_Result checkCreateFont( void );
extern CT_Result checkDestroyFont( void );
extern CT_Result checkSetGlyphToPath( void );
extern CT_Result checkSetGlyphToImage( void );
extern CT_Result checkClearGlyph( void );
extern CT_Result checkDrawGlyph( void );
extern CT_Result checkDrawGlyphs( void );

/* Image Filters */
extern CT_Result checkColorMatrix( void );
extern CT_Result checkConvolve( void );
extern CT_Result checkSeparableConvolve( void );
extern CT_Result checkGaussianBlur( void );
extern CT_Result checkLookup( void );
extern CT_Result checkLookupSingle( void );

/* Hardware Queries */
extern CT_Result checkHardwareQuery( void );

/* Renderer and Extension Information */
extern CT_Result checkGetString( void );



static const CT_FuncRec funcVgList[] = {
    { "vgGetError",                        0,     checkGetError       },
    { "vgFlush",                           1,     checkFlush          },
    { "vgFinish",                          2,     checkFinish         },

    /* Set/Get Parameter */
    { "vgSetf",                            3,     checkSetf           },
    { "vgSeti",                            4,     checkSeti           },
    { "vgSetfv",                           5,     checkSetfv          },
    { "vgSetiv",                           6,     checkSetiv          },
    { "vgGetVectorSize",                   7,     checkGetVectorSize  },
    { "vgGetf",                            8,     checkGetf           },
    { "vgGeti",                            9,     checkGeti           },
    { "vgGetfv",                          10,     checkGetfv          },
    { "vgGetiv",                          11,     checkGetiv          },
    { "vgSetParameterf",                  12,     checkSetParameterf  },
    { "vgSetParameteri",                  13,     checkSetParameteri  },
    { "vgSetParameterfv",                 14,     checkSetParameterfv },
    { "vgSetParameteriv",                 15,     checkSetParameteriv },
    { "vgGetParameterVectorSize",         16,     checkGetParameterVectorSize },
    { "vgGetParameterf",                  17,     checkGetParameterf  },
    { "vgGetParameteri",                  18,     checkGetParameteri  },
    { "vgGetParameterfv",                 19,     checkGetParameterfv },
    { "vgGetParameteriv",                 20,     checkGetParameteriv },

    /* Matrix Manipulation */
    { "vgLoadIdentity",                      21,     checkLoadIdentity   },
    { "vgLoadMatrix",                        22,     checkLoadMatrix     },
    { "vgGetMatrix",                         23,     checkGetMatrix      },
    { "vgMultMatrix",                        24,     checkMultMatrix     },
    { "vgTranslate",                         25,     checkTranslate      },
    { "vgScale",                             26,     checkScale          },
    { "vgShear",                             27,     checkShear          },
    { "vgRotate",                            28,     checkRotate         },
    
    /* Masking */
    { "vgMask",                                29,     checkMask           },
    { "vgRenderToMask",                        30,     checkRenderToMask   },
    { "vgCreateMaskLayer",                     31,     checkCreateMaskLayer    },
    { "vgDestroyMaskLayer",                    32,     checkDestroyMaskLayer   },
    { "vgFillMaskLayer",                       33,     checkFillMaskLayer  },
    { "vgCopyMask",                            34,     checkCopyMask       },

    /* Clearing */
    { "vgClear",                               35,     checkClear          },

    /* Paths */
    { "vgCreatePath",                          36,     checkCreatePath     },
    { "vgClearPath",                           37,     checkClearPath      },
    { "vgDestroyPath",                         38,     checkDestroyPath    },
    { "vgGetPathCapabilities",                 39,     checkGetPathCapabilities    },
    { "vgRemovePathCapabilities",              40,     checkRemovePathCapabilities },
    { "vgAppendPath",                          41,     checkAppendPath     },
    { "vgAppendPathData",                      42,     checkAppendPathData },
    { "vgModifyPathCoords",                    43,     checkModifyPathCoords       },
    { "vgTransformPath",                       44,     checkTransformPath  },
    { "vgInterpolatePath",                     45,     checkInterpolatePath        },
    { "vgPathLength",                          46,     checkPathLength     },
    { "vgPointAlongPath",                      47,     checkPointAlongPath         },
    { "vgPathBounds",                          48,     checkPathBounds     },
    { "vgPathTransformedBounds",               49,     checkPathTransformedBounds  },
    { "vgDrawPath",                            50,     checkDrawPath       },

    /* Paint */
    { "vgCreatePaint",                        51,     checkCreatePaint    },
    { "vgDestroyPaint",                       52,     checkDestroyPaint   },
    { "vgSetPaint",                           53,     checkSetPaint       },
    { "vgGetPaint",                           54,     checkGetPaint       },
    { "vgSetColor",                           55,     checkSetColor       },
    { "vgGetColor",                           56,     checkGetColor       },
    { "vgPaintPattern",                       57,     checkPaintPattern   },

    /* Images */
    { "vgCreateImage",                        58,     checkCreateImage    },
    { "vgDestroyImage",                       59,     checkDestroyImage   },
    { "vgClearImage",                         60,     checkClearImage     },
    { "vgImageSubData",                       61,     checkImageSubData   },
    { "vgGetImageSubData",                    62,     checkGetImageSubData        },
    { "vgChildImage",                         63,     checkChildImage     },
    { "vgGetParent",                          64,     checkGetParent      },
    { "vgCopyImage",                          65,     checkCopyImage      },
    { "vgDrawImage",                          66,     checkDrawImage      },
    { "vgSetPixels",                          67,     checkSetPixels      },
    { "vgWritePixels",                        68,     checkWritePixels    },
    { "vgGetPixels",                          69,     checkGetPixels      },
    { "vgReadPixels",                         70,     checkReadPixels     },
    { "vgCopyPixels",                         71,     checkCopyPixels     },

	/* Text */
    { "vgCreateFont",                         72,     checkCreateFont      },
    { "vgDestroyFont",                        73,     checkDestroyFont     },
    { "vgSetGlyphToPath",                     74,     checkSetGlyphToPath    },
    { "vgSetGlyphToImage",                    75,     checkSetGlyphToImage   },
    { "vgClearGlyph",                         76,     checkClearGlyph      },
    { "vgDrawGlyph",                          77,     checkDrawGlyph       },
    { "vgDrawGlyphs",                         78,     checkDrawGlyphs      },

    /* Image Filters */
    { "vgColorMatrix",                       79,     checkColorMatrix    },
    { "vgConvolve",                          80,     checkConvolve       },
    { "vgSeparableConvolve",                 81,     checkSeparableConvolve      },
    { "vgGaussianBlur",                      82,     checkGaussianBlur   },
    { "vgLookup",                            83,     checkLookup         },
    { "vgLookupSingle",                      84,     checkLookupSingle   },

    /* Hardware Queries */
    { "vgHardwareQuery",                       85,     checkHardwareQuery  },

    /* Renderer and Extension Information */
    { "vgGetString",                           86,     checkGetString      },

    { "End of List" }    
};
