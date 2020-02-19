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

CT_AppRec     app;
CT_ConfigRec  configRec = {0, {0,}};
CT_SummaryRec summaryInfo = {0, 0, 0, {0,}, {0,}};

CT_ChannelRec channelInfo;
char          TestFileName[CT_MAX_FILE_NAME];

static AppSetup(void)
{
    strcpy( app.title,   CT_RELEASE_TITLE );
    strcpy( app.name,    CT_RELEASE_NAME );
    strcpy( app.version, CT_RELEASE_VERSION );
    strcpy( app.date,    CT_RELEASE_DATE );

    app.verboseLevel = 1;
    app.configID     = CT_UNSPECIFIED;

    Output(0, "\n" );
    Output(0, "%s\n", app.title );
    Output(0, "version %s (%s)\n\n", app.version, app.date );
}

static CT_Result ArguSetup(int argc, char **argv)
{
    long i;

    if (DriverSetupInit() == CT_ERROR) {
        Output(0, "Driver setup failed.\n\n");
        return CT_ERROR;
    }
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-1") == 0) {  /* run single test. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(0, "-1 (No test name).\n\n");
                return CT_ERROR;
            } 
            else {
                if (DriverSetupName(argv[++i]) == CT_ERROR) {
                    Output(0, "-1 (Bad test name).\n\n");
                    return CT_ERROR;
                }
            }
        } 
        else if (strcmp(argv[i], "-c") == 0) {  /* config. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(0, "-c (No config ID).\n\n");
                return CT_ERROR;
            } 
            else {
                app.configID = atoi(argv[++i]);
            }
        } 
        else if (strcmp(argv[i], "-h") == 0) {  /* help. */
            Output(0, "Options:\n");
            Output(0, "\t-1 <test>\tSingle test using \"test\" id.\n");
            Output(0, "\t-c <id>\t\tUse config id.\n");
            Output(0, "\t-h\t\tPrint this help screen.\n");
            Output(0, "\t-v [0-2]\tVerbose level.\n");
            Output(0, "\n");
            return CT_ERROR;
        } 
        else if (strcmp(argv[i], "-v") == 0) {  /* verbose. */
            if (i+1 >= argc || argv[i+1][0] == '-') {
                Output(0, "-v (No verbose level).\n\n");
                return CT_ERROR;
            } 
            else {
                app.verboseLevel = atoi(argv[++i]);
                if (app.verboseLevel < 0 || app.verboseLevel > 2) {
                    Output(0, "-v (Bad verbose level).\n\n");
                    return CT_ERROR;
                }
            }
        } 
        else {
            Output(0, "%s (Bad option).\n\n", argv[i]);
            return CT_ERROR;
        }
    }
    
    return CT_NO_ERROR;
}

CT_Result LoadConfigFile ()
{
    int            i;
    char           name[CT_MAX_FILE_NAME] = {0,};
    FILE          *configfile;
    CT_ChannelRec  channel;

    strcat (name, INFO_DEFAULT_DIR);
    strcat (name, "/config.inf");
    configfile = fopen (name, "rt");
    if (configfile == NULL) {
        Output(0, "config.inf can't be read.\n");
        return CT_ERROR;
    }

    fscanf (configfile, "%d\n", &configRec.num);
    
    for (i=0; i<configRec.num; i++) {
        fscanf (configfile, "%d %d %d %d %d %d %d %d %d %d\n", &channel.id, &channel.conformant, &channel.rDepth, &channel.gDepth, &channel.bDepth, &channel.aDepth, &channel.lDepth, &channel.maskSize, &channel.sampleBuffers, &channel.samples);
        configRec.channel[i] = channel;
    }

    fclose (configfile);
    return CT_NO_ERROR;
}

static long Exec()
{
    static const char surface[4][15] = { "sRGB_NONPRE","lRGB_NONPRE", "sRGB_PRE", "lRGB_PRE" };
    int i, numalphaformats;
    int j, numcolorspaces;
    char RatingTableName[CT_MAX_FILE_NAME];

    /* The type indicates the following:
           0x0001  - The config is non-conformant with respect to OpenVG.
           0x0002  - The config does not support OpenVG.
           0x0004  - The config does not support rendering to a pbuffer or window surface.
           0x0008  - The config configuration is not testable
           0x0010  - The config does not support the COLORSPACE_LINEAR attribute
           0x0020  - The config does not support the ALPHA_FORMAT_PRE attribute

       Bottom byte of 0 means the config should be reported.
    */
    
    memset(RatingTableName, 0, 100);
    sprintf (RatingTableName, "%s/%d%d%d%d%d%d.dat", "./ratingtables", channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth, channelInfo.sampleBuffers );

    if ( ( 0x0F & channelInfo.conformant ) == 0x00 ) {
        if (DriverSetupFile (RatingTableName) == CT_ERROR) {
            Output(0, "Loading RatingTable file failed.\n\n");
            return CT_ERROR;
        }

        if (TestFileName[0]) {
            if (DriverSetupName(TestFileName) == CT_ERROR) {
                return CT_ERROR;
            }
        }
    }

    switch( 0x0F & channelInfo.conformant ) {
        case 0x00:
            numcolorspaces = ( 0x10 & channelInfo.conformant ) ? 1 : 2;
            numalphaformats = ( 0x20 & channelInfo.conformant ) ? 1 : 2;
            for ( i = 0; i < numalphaformats; i++ ) {
                for ( j = 0; j < numcolorspaces; j++ ) {
                    channelInfo.cSpace = 2*i+j;
                    Output(0, "Config : #%d, %s, RGB(%d%d%d), A(%d), L(%d), M(%d)\n", channelInfo.id, surface[channelInfo.cSpace], channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth, channelInfo.maskSize);
                    if (Driver() == CT_NO_ERROR) {
                        #if (TEST_OPTION_VGU != 0)
                            Output(0, "%s passed.[included VGU tests]\n\n", app.name );
                        #else
                            Output(0, "%s passed.[excluded VGU tests]\n\n", app.name );
                        #endif    
                    } 
                    else {
                        #if (TEST_OPTION_VGU != 0)
                            Output(0, "%s failed.[included VGU tests]\n\n", app.name );
                        #else
                            Output(0, "%s failed.[excluded VGU tests]\n\n", app.name );
                        #endif    
                    }
                }
            }
            break;

        case 0x01:
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d)\n", channelInfo.id, channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth);
            Output(0, "Config is identified as EGL_NON_CONFORMANT_CONFIG\n");
            Output(0, "%s test is skipped.\n\n", app.name );                    
            break;

        case 0x02:
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d)\n", channelInfo.id, channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth);
            Output(0, "Config does not support OpenVG\n");
            Output(0, "%s test is skipped.\n\n", app.name );                    
            break;

        case 0x04:
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d)\n", channelInfo.id, channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth);
            Output(0, "Config does not support rendering to a pbuffer or windows surface\n");
            Output(0, "%s test is skipped.\n\n", app.name );                    
            break;            

        case 0x08:            
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d)\n", channelInfo.id, channelInfo.rDepth, channelInfo.gDepth, channelInfo.bDepth, channelInfo.aDepth, channelInfo.lDepth);
            Output(0, "Config is unsupportable RGBA depth or unsupportable surface type\n");
            Output(0, "%s test is skipped.\n\n", app.name );        
            break;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i, j, k, m, n;
    int numalphaformats;
    int numcolorspaces;

    /* App Setup */
    AppSetup();

    /* Driver Setup */
    DriverSetup();

    /* Setup Report */    
    if (ArguSetup(argc, argv) == CT_ERROR) {
        exit(1);
        return 1;
    }
    else {
        Output(0, "[Setup Report]\n");
        Output(0, "    Verbose level = %d.\n", app.verboseLevel);
        if (app.configID != CT_UNSPECIFIED)
            Output(0, "    EGL Config ID = %d\n", app.configID );
#if (TEST_OPTION_VGU != 0)
        Output(0, "    VGU Test = Yes\n");
#else
        Output(0, "    VGU Test = No\n");
#endif            
    }

    Output(0, "\n");
    if (LoadConfigFile() == CT_ERROR) {
        exit(1);
        return 1;
    }
    if (app.configID == CT_UNSPECIFIED) {
        summaryInfo.single = 0;
        for (i=0; i<configRec.num; i++) {
            channelInfo = configRec.channel[i];

            summaryInfo.index = i;
            Exec();
        }
    }
    else {
        int i;
        for ( i = 0; i < configRec.num; i++ ) {
            if ( app.configID == configRec.channel[i].id ) {
                break;
            }
        }
        if ( i == configRec.num )
            Output(0, "ConfigID : #%d can't find.\n", app.configID);
        else {
            channelInfo = configRec.channel[i];
            
            summaryInfo.index = i;
            summaryInfo.single = 1;
            
            Exec();
        }
    }
    /* Summarize */
    Output(0, "***************** SUMMARY OF 'report' RESULTS *****************\n");

    for (i = 0; i < configRec.num; i++) {
        CT_ChannelRec channel = configRec.channel[i];
        char surface[4][15] = { "sRGB_NONPRE","lRGB_NONPRE","sRGB_PRE", "lRGB_PRE" };
        
        if ( (0x0F & channel.conformant) == 0) {
            numcolorspaces = ( 0x10 & channel.conformant ) ? 1 : 2;
            numalphaformats = ( 0x20 & channel.conformant ) ? 1 : 2;
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d), conformant\n", channel.id, channel.rDepth, channel.gDepth, channel.bDepth, channel.aDepth, channel.lDepth);
            for ( j = 0; j < 2; j++ ) {
                for ( k = 0; k < 2; k++ ) {
                    m = 2*j+k;
                    if ( j < numalphaformats && k < numcolorspaces )
                    {
                        if (summaryInfo.failed[i][m]) {
                            for ( n = 0; n < summaryInfo.failed[i][m]; n++ ) {
                                if (n == 0) {
                                    Output(0, "Result(%s) : [%c] Group failed\n", surface[m], summaryInfo.fail[i][m][n]);    
                                }
                                else {
                                    Output(0, "               [%c] Group failed\n", summaryInfo.fail[i][m][n]);    
                                }
                            }
                        }
                        else {
                            Output(0, "Result(%s) : All Group passed\n", surface[m]);
                        }
                    }
                    else
                    {
                        Output(0, "Result(%s) : All Group skipped (%s unsupported)\n", surface[m], surface[m]);
                    }
                }
            }
        }
        else {
            Output(0, "Config : #%d, RGB(%d%d%d), A(%d), L(%d), non-Conformant\n", channel.id, channel.rDepth, channel.gDepth, channel.bDepth, channel.aDepth, channel.lDepth);
            Output(0, "Result : All Group skipped\n");
        }

        if (i != configRec.num-1) {
            Output(0, "---------------------------------------------------------------\n");
        }
        else {
            Output(0, "***************************************************************\n");            
        }          
    }
    return 0;
}
