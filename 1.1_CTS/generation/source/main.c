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
#include "util/util.h"
#include "util/st.h"

/* EGL Config Function */
/*
TK_ConfigInfoRec *GetConfigInfo( void )
{
    return &info;
}
*/

static CT_Result EGLConfigInfo(CT_AppRec *pMe)
{
    FILEHANDLE file;
    VGbyte     name[CT_MAX_FILE_NAME] = {0,};
    
    STRCAT(name, INFO_DEFAULT_DIR);
    MKDIR(name);
    
    STRCAT(name, "/config.inf");
    
    file = FOPEN (name, "wt");
    
    if (file == NULL) {
        Output(pMe, 0, "config.inf can't be created.\n");
        return CT_ERROR;
    }

    tkGetConfigs( pMe, file );
    
    Output(pMe, 0, "    Total EGL Config  = %d\n", pMe->list.count );
    Output(pMe, 0, "    Conformant Config = %d\n\n", pMe->list.conformantCount );

    FCLOSE(file);

    return CT_NO_ERROR;
}

static void AppSetup(CT_AppRec *pMe)
{
    if ( !pMe )
        return;

    STRCPY( pMe->title,   CT_RELEASE_TITLE );
    STRCPY( pMe->name,    CT_RELEASE_NAME );
    STRCPY( pMe->version, CT_RELEASE_VERSION );
    STRCPY( pMe->date,    CT_RELEASE_DATE );
    pMe->verboseLevel   = 1;
    pMe->configID       = CT_UNSPECIFIED;

    pMe->native_window  = 0;
    pMe->native_display = 0;

    pMe->egl_display = EGL_NO_DISPLAY;
    pMe->egl_surface = EGL_NO_SURFACE;
    pMe->egl_context = EGL_NO_CONTEXT;    

    Output(pMe, 0, "\n" );
    Output(pMe, 0, "%s\n", pMe->title );
    Output(pMe, 0, "version %s (%s)\n\n", pMe->version, pMe->date );
}

static CT_Result ArguSetup(CT_AppRec *pMe, VGint argc, VGbyte **argv)
{
    FILEHANDLE file;
    VGint i;
    
    for (i = 1; i < argc; i++) {
        if (STRCMP(argv[i], "-1") == 0) {  /* run single test. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(pMe, 0, "-1 (No test name).\n\n");
                return CT_ERROR;
            } 
            else {
                if (DriverSetupName(pMe, argv[++i]) == CT_ERROR) {
                    Output(pMe, 0, "-1 (Bad test name).\n\n");
                    return CT_ERROR;
                }
            }
        } 
        else if (STRCMP(argv[i], "-c") == 0) {  /* config. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(pMe, 0, "-c (No config ID).\n\n");
                return CT_ERROR;
            } 
            else {
                pMe->configID = ATOI(argv[++i]);
            }
        } 
        else if (STRCMP(argv[i], "-f") == 0) {  /* use test set. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(pMe, 0, "-f (No file name).\n\n");
                return CT_ERROR;
            } else {
                if (DriverSetupFile(pMe, argv[++i]) == CT_ERROR) {
                    Output(pMe, 0, "-f (Bad file).\n\n");
                    return CT_ERROR;
                }
            }
        } 
        else if (STRCMP(argv[i], "-g") == 0) {  /* generate test set. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(pMe, 0, "-g (No file name).\n\n");
            } 
            else {
                file = FOPEN(argv[++i], "wt");
                
                if (file != NULL) {
                    DriverSaveTestList(pMe, file);

                    FCLOSE(file);
                    Output(pMe, 0, "Test file [%s] created.\n\n", argv[i]);
                } else {
                    Output(pMe, 0, "-g (Bad file name).\n\n");
                }
            }
            return CT_ERROR;
        } 
        else if (STRCMP(argv[i], "-h") == 0) {  /* help. */
            Output(pMe, 0, "Options:\n");
            Output(pMe, 0, "\t-1 <test>\tSingle test using \"test\" id.\n");
            Output(pMe, 0, "\t-c <id>\t\tUse config id.\n");
            Output(pMe, 0, "\t-f <file>\tUse test set in \"file\".\n");
            Output(pMe, 0, "\t-g <file>\tGenerate test set in \"file\".\n");
            Output(pMe, 0, "\t-h\t\tPrint this help screen.\n");
            Output(pMe, 0, "\t-v [0-2]\tVerbose level.\n");
            Output(pMe, 0, "\n");
            return CT_ERROR;
        } 
        else if (STRCMP(argv[i], "-v") == 0) {  /* verbose. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(pMe, 0, "-v (No verbose level).\n\n");
                return CT_ERROR;
            } 
            else {
                pMe->verboseLevel = ATOI(argv[++i]);
                if (pMe->verboseLevel < 0 || pMe->verboseLevel > 2) {
                    Output(pMe, 0, "-v (Bad verbose level).\n\n");
                    return CT_ERROR;
                }
            }
        } 
        else {
            Output(pMe, 0, "%s (Bad option).\n\n", argv[i]);
            return CT_ERROR;
        }
    }
    
    return CT_NO_ERROR;
}

static void StateSetup(CT_AppRec *pMe)
{
    Output(pMe, 1, "Generation Report\n");

    if ( StateCheck(pMe) == CT_ERROR ) {
        Output(pMe, 0, "    Default Parameter values for a Context are wrong.\n");
        Output(pMe, 0, "%s failed.\n", pMe->name);

        EXIT(EXIT_FAILURE);
    }
    
    if ( StateReset(pMe) == CT_ERROR || StateCheck(pMe) == CT_ERROR ) {
        Output(pMe, 0, "    Default CONTEXT parameter setting test failed.\n");
        Output(pMe, 0, "    Cannot continue until this test passes.\n\n");
        Output(pMe, 0, "%s failed.\n",  pMe->name);

        EXIT(EXIT_FAILURE);
    }
}

static void Exec(CT_AppRec *pMe, int index)
{
    static const VGbyte surface[2][2][15] = { { "sRGB_NONPRE","lRGB_NONPRE" },
                                              { "sRGB_PRE", "lRGB_PRE" } };
    int i, numalphaformats;
    int j, numcolorspaces;
    
    /* The type indicates the following:
           0x0001  - The config is non-conformant with respect to OpenVG.
           0x0002  - The config does not support OpenVG.
           0x0004  - The config does not support rendering to a pbuffer or window surface.
           0x0008  - The config configuration is not testable
           0x0010  - The config does not support the COLORSPACE_LINEAR attribute
           0x0020  - The config does not support the ALPHA_FORMAT_PRE attribute
       
       Bottom byte of 0 means the config should be tested.
    */
    switch( 0x0F & pMe->list.type[index] ) {
        case 0x00:
            numcolorspaces = ( 0x10 & pMe->list.type[index] ) ? 1 : 2;
            numalphaformats = ( 0x20 & pMe->list.type[index] ) ? 1 : 2;
            for ( i = 0; i < numalphaformats; i++ ) {
                for ( j = 0; j < numcolorspaces; j++ ) {
                    pMe->info.cSpace = j;
                    pMe->info.alphaMult = i;
                    if (tkCreateContext(pMe, pMe->list.IDs[index])) {
                        Output(pMe, 0, "Config : #%d, %s, RGB(%d%d%d), A(%d), L(%d), M(%d)\n", pMe->list.IDs[index], surface[i][j], pMe->info.rDepth, pMe->info.gDepth, pMe->info.bDepth, pMe->info.aDepth, pMe->info.lDepth, pMe->info.maskSize );
                        StateSetup(pMe);                        
                        LOAD_TIE_BREAK_RULE_MATRIX_FORCE_RECAL();
                        
                        if ( Driver(pMe) == CT_NO_ERROR ) {
                            #if (TEST_OPTION_VGU != 0)
                                Output(pMe, 0, "%s Result Generation Succeeded.[included VGU tests]\n\n", pMe->name );
                            #else
                                Output(pMe, 0, "%s Result Generation Succeeded.[excluded VGU tests]\n\n", pMe->name );
                            #endif
                        } 
                        else {
                            #if (TEST_OPTION_VGU != 0)
                                Output(pMe, 0, "%s Result Generation Failed.[included VGU tests]\n\n", pMe->name );
                            #else
                                Output(pMe, 0, "%s Result Generation Failed.[excluded VGU tests]\n\n", pMe->name );
                            #endif        
                        } 
                        tkDestroyContext(pMe);
                    }
                }
            }
            break;
        
        case 0x01:
            Output(pMe, 0, "Config : #%d, is identified as EGL_NON_CONFORMANT_CONFIG\n\n", pMe->list.IDs[index]);
            break;

        case 0x02:
            Output(pMe, 0, "Config : #%d, does not support OpenVG\n\n", pMe->list.IDs[index]);
            break;

        case 0x04:
            Output(pMe, 0, "Config : #%d, does not support rendering to a pbuffer or windows surface\n\n", pMe->list.IDs[index]);
            break;            

        case 0x08:            
            Output(pMe, 0, "Config : #%d, is unsupportable RGBA depth or unsupportable surface type\n\n", pMe->list.IDs[index] );
            break;
    }
}

int main(int argc, char **argv)
{
    CT_AppRec  *pMe;
    VGint i;

    pMe = (CT_AppRec *)MALLOC( sizeof(CT_AppRec) );    
    if ( !pMe )
        goto fail;
        
    MEMSET(pMe, 0, sizeof(CT_AppRec));

    /* App Setup */
    AppSetup(pMe);

    /* Driver Setup */
    if (CT_NO_ERROR != DriverSetup(pMe))
        goto fail;

    /* Setup Report */
    if (ArguSetup(pMe, argc, (VGbyte **)argv) == CT_ERROR) {
        goto fail;
    }
    else {
        if ( tkNewWindow( pMe, 0, 0, WINDSIZEX, WINDSIZEY) ) { 
            if ( tkCreateContext( pMe, 0 ) ) {
                Output(pMe, 0, "[Implementation Report]\n");
                Output(pMe, 0, "    Vender    = %s\n", vgGetString(VG_VENDOR) );
                Output(pMe, 0, "    Renderer  = %s\n", vgGetString(VG_RENDERER) );    
                Output(pMe, 0, "    Version   = %s\n", vgGetString(VG_VERSION) );    
                Output(pMe, 0, "    Extension = %s\n\n", vgGetString(VG_EXTENSIONS) );    
                tkDestroyContext(pMe);
            }
            tkCloseWindow(pMe);
        }
        Output(pMe, 0, "[Setup Report]\n");
        Output(pMe, 0, "    Verbose level = %d.\n", pMe->verboseLevel);
        if ( pMe->configID != CT_UNSPECIFIED )
            Output(pMe, 0, "    EGL Config ID = %d\n", pMe->configID );
#if (TEST_OPTION_VGU != 0)
        Output(pMe, 0, "    VGU Test = Yes\n");
#else
        Output(pMe, 0, "    VGU Test = No\n");
#endif
    }

    /* Create Window */
    if ( tkNewWindow( pMe, 0, 0, WINDSIZEX, WINDSIZEY) == 0 ) {
        goto fail;
    }

    /* EGL Report */
    Output(pMe, 0, "\n[EGL Report]\n");
    if (CT_NO_ERROR != EGLConfigInfo(pMe))
        goto fail;

    if (pMe->configID == CT_UNSPECIFIED) {
        for ( i = 0; i < pMe->list.count; i++) {
            Exec(pMe, i);
        }
    }
    else {
        for ( i = 0; i < pMe->list.count; i++ ) {
            if (pMe->list.IDs[i] == pMe->configID) {
                Exec(pMe, i);
                break;
            }
        }
        if ( i == pMe->list.count )
            Output(pMe, 0, "Config ID not found.\n\n");
    }

    tkCloseWindow(pMe);
    FREE( pMe );
    return EXIT_SUCCESS;

fail:
    if ( pMe )
        FREE( pMe );
        
    EXIT(EXIT_FAILURE);
}
