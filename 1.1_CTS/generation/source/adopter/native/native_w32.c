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

#include <windows.h>
#include <stdio.h>

#include "native.h"

static LRESULT tkWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT  Paint;
    LPMINMAXINFO lpmmi;

    switch (message) {
        case WM_PAINT:
            BeginPaint( hWnd, &Paint );
            EndPaint( hWnd, &Paint );
            return 0;

        case WM_GETMINMAXINFO:
            lpmmi = (LPMINMAXINFO)lParam;
            lpmmi->ptMinTrackSize.x = 1;
            lpmmi->ptMinTrackSize.y = 1;
            return 0;

        case WM_DESTROY:
            PostQuitMessage(TRUE);
            return (DefWindowProc( hWnd, message, wParam, lParam));
    }
    
    return (DefWindowProc( hWnd, message, wParam, lParam));
}

int tkNewWindow(CT_AppRec *pMe, int x, int y, int width, int height )
{
    EGLint   majorVersion, minorVersion;
    
    WNDCLASS wndclass;
    RECT     WinRect;
    HANDLE   hInstance;

    hInstance = GetModuleHandle(NULL);
    wndclass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc    = (WNDPROC)tkWndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = hInstance;
    wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName   = NULL;
    wndclass.lpszClassName  = pMe->title;

    RegisterClass(&wndclass);

    WinRect.left   = (x == CW_USEDEFAULT) ? 0 : x;
    WinRect.top    = (y == CW_USEDEFAULT) ? 0 : y;
    WinRect.right  = WinRect.left + width;
    WinRect.bottom = WinRect.top + height;

    AdjustWindowRect(&WinRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

    pMe->native_window = CreateWindowEx(  WS_EX_TOPMOST,
                                          wndclass.lpszClassName,
                                          pMe->title,
                                          WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                                          (x == CW_USEDEFAULT ? CW_USEDEFAULT : WinRect.left),
                                          (y == CW_USEDEFAULT ? CW_USEDEFAULT : WinRect.top),
                                          WinRect.right  - WinRect.left,
                                          WinRect.bottom - WinRect.top,
                                          NULL,
                                          NULL,
                                          hInstance,
                                          NULL );
    
    if ( !pMe->native_window ) {
        FPRINTF(stderr, "%s", "Can't create windows.\n");
        return 0;
    }        

    pMe->native_display = GetDC(pMe->native_window);
    pMe->egl_display    = eglGetDisplay(pMe->native_display);

    if (!eglInitialize(pMe->egl_display, &majorVersion, &minorVersion)) {
        FPRINTF(stderr, "%s", "eglInitialize failed.\n");
        ReleaseDC(pMe->native_window, pMe->native_display);
        DestroyWindow(pMe->native_window);
        return 0;
    }

    eglBindAPI(EGL_OPENVG_API);
    return 1;
}

void tkCloseWindow(CT_AppRec *pMe)
{
    eglMakeCurrent(pMe->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(pMe->egl_display);
    ReleaseDC(pMe->native_window, pMe->native_display);
    DestroyWindow(pMe->native_window);
}

int tkCreateContext(CT_AppRec *pMe, int configID )
{
    EGLConfig  egl_config;
    EGLint     count;
    EGLint     config_list[3];
    EGLint     attrib_list[9];
    EGLint     surfaceType;
    
    config_list[0] = EGL_CONFIG_ID;
    config_list[1] = configID;
    config_list[2] = EGL_NONE;

    attrib_list[0] = EGL_ALPHA_FORMAT;
    attrib_list[1] = (pMe->info.alphaMult == 0) ? EGL_ALPHA_FORMAT_NONPRE : EGL_ALPHA_FORMAT_PRE ;
    attrib_list[2] = EGL_COLORSPACE;
    attrib_list[3] = (pMe->info.cSpace == 0) ? EGL_COLORSPACE_sRGB : EGL_COLORSPACE_LINEAR;
    attrib_list[4] = EGL_NONE;

    pMe->egl_surface = EGL_NO_SURFACE;
    pMe->egl_context = EGL_NO_CONTEXT;

    /* Make window large enough to hold a client area as large as wind */
    if (!eglChooseConfig(pMe->egl_display, config_list, &egl_config, 1, &count)) {
        return 0;
    }

    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_SURFACE_TYPE, &surfaceType );

    /* Create Surface */
    if ( pMe->egl_surface == EGL_NO_SURFACE && surfaceType & EGL_WINDOW_BIT ) {    
        pMe->egl_surface = eglCreateWindowSurface(pMe->egl_display, egl_config, pMe->native_window, attrib_list);
    }
    if ( pMe->egl_surface == EGL_NO_SURFACE && surfaceType & EGL_PBUFFER_BIT ) {
        attrib_list[4] = EGL_WIDTH;     attrib_list[5] = WINDSIZEX;
        attrib_list[6] = EGL_HEIGHT;    attrib_list[7] = WINDSIZEY;        
        attrib_list[8] = EGL_NONE;        
        pMe->egl_surface = eglCreatePbufferSurface(pMe->egl_display, egl_config, attrib_list);
    }
    if (pMe->egl_surface == EGL_NO_SURFACE) {
        FPRINTF(stderr, "%s", "Can't create EGL window.\n");
        return 0;
    }

    /* Create Context */
    pMe->egl_context = eglCreateContext(pMe->egl_display, egl_config, EGL_NO_CONTEXT, NULL);
    if (pMe->egl_context == EGL_NO_CONTEXT) {
        FPRINTF(stderr, "%s", "Can't create a context.\n");
        return 0;
    }

    if (!eglMakeCurrent(pMe->egl_display, pMe->egl_surface, pMe->egl_surface, pMe->egl_context)) {
        FPRINTF(stderr, "%s", "Can't make context current.\n");
        return 0;
    }

    pMe->info.configID = configID;
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_RED_SIZE, &pMe->info.rDepth);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_GREEN_SIZE, &pMe->info.gDepth);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_BLUE_SIZE, &pMe->info.bDepth);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_ALPHA_SIZE, &pMe->info.aDepth);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_LUMINANCE_SIZE, &pMe->info.lDepth);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_ALPHA_MASK_SIZE, &pMe->info.maskSize);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_SAMPLE_BUFFERS, &pMe->info.sampleBuffers);
    eglGetConfigAttrib(pMe->egl_display, egl_config, EGL_SAMPLES, &pMe->info.samples);                

    return 1;
}

void tkDestroyContext(CT_AppRec *pMe)
{
    eglMakeCurrent(pMe->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
    eglDestroyContext(pMe->egl_display, pMe->egl_context);
    eglDestroySurface(pMe->egl_display, pMe->egl_surface);
}

void tkSwapBuffers(CT_AppRec *pMe)
{
    eglSwapBuffers(pMe->egl_display, pMe->egl_surface);
}

int tkTestableConfig( int r, int g, int b, int a, int l )
{
    static const int config[MAX_TESTABLE_EGL_CONFIG][5] = {
        { 8, 8, 8, 8, 0 },
        { 8, 8, 8, 0, 0 },
        { 5, 5, 5, 1, 0 },
        { 5, 6, 5, 0, 0 },
        { 4, 4, 4, 4, 0 },
        { 0, 0, 0, 8, 0 },
        { 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 1 }
    };
    int i;

    for ( i = 0; i < MAX_TESTABLE_EGL_CONFIG; i++ ) {
        if ( r == config[i][0] && g == config[i][1] && b == config[i][2] && a == config[i][3] && l == config[i][4] )
            return 1;
    }
    
    return 0;
}

EGLBoolean tkQueryExtension(EGLDisplay dpy, char *extName)
{
    unsigned int n;
    char *p = (char *) eglQueryString( dpy, EGL_EXTENSIONS );
    char *end = p + strlen(p);
    while ( p < end )
    {
        n = (unsigned int) strcspn(p, " ");
        if ((strlen(extName)==n) && (strncmp(extName,p,n)==0)) {
            return EGL_TRUE;
        }
        p += (n + 1);
    }
    return EGL_FALSE;
}

void tkGetConfigs(CT_AppRec *pMe, FILEHANDLE file)
{
    EGLBoolean extended;
    EGLint     num_config;
    EGLConfig *configs;
    EGLint     configId, conformant, apiType, surfaceType;
    EGLint     red, green, blue, alpha, lumin, mask, renderableType, sampleBuffers, samples;
    EGLint     i;

    pMe->list.count              = 0;
    pMe->list.conformantCount    = 0;

#if !defined( EGL_VERSION_1_3 )
    /* Query config attributes extension. */
    extended = tkQueryExtension( pMe->egl_display, "EGL_KHR_config_attribs" );
#else
    extended = EGL_TRUE;
#endif

    eglGetConfigs(pMe->egl_display, NULL, 0, &num_config);
    configs = (EGLConfig *)MALLOC(num_config * sizeof(EGLConfig));
    eglGetConfigs(pMe->egl_display, configs, num_config, &num_config);

    FPRINTF(file, "%d\n", num_config);

    for (i = 0; i < num_config; i++) {
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_CONFIG_ID, &configId);
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_RENDERABLE_TYPE, &apiType); 
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_SURFACE_TYPE, &surfaceType);
        
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_RED_SIZE, &red);        
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_GREEN_SIZE, &green);        
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_BLUE_SIZE, &blue);        
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_ALPHA_SIZE, &alpha);        
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_LUMINANCE_SIZE, &lumin);
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_ALPHA_MASK_SIZE, &mask);                

        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_SAMPLE_BUFFERS, &sampleBuffers);
        eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_SAMPLES, &samples);                

        /* Update renderableType to indicate if:
           0x0001  - The config is non-conformant with respect to OpenVG.
           0x0002  - The config does not support OpenVG.
           0x0004  - The config does not support rendering to a pbuffer or window surface.
           0x0008  - The config configuration is not testable
           0x0010  - The config does not support the COLORSPACE_LINEAR attribute
           0x0020  - The config does not support the ALPHA_FORMAT_PRE attribute

           Note that if the EGL_KHR_config_attribs extension is NOT supported, the
           implementation MUST support the COLORSPACE_LINEAR and ALPHA_FORMAT_PRE attribs.
        */
        if ( extended )
        {
#if defined( EGL_VERSION_1_3 ) || defined(EGL_CONFORMANT_KHR)
            eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_CONFORMANT_KHR, &conformant);                
            renderableType = (!(conformant & EGL_OPENVG_BIT))                     ? 0x01 :
                             (!(apiType & EGL_OPENVG_BIT))                        ? 0x02 :
                             (!(surfaceType & (EGL_WINDOW_BIT|EGL_PBUFFER_BIT)) ) ? 0x04 :
                             (!tkTestableConfig(red, green, blue, alpha, lumin) ) ? 0x08 : 0x00;
            renderableType |= (!(surfaceType & EGL_VG_COLORSPACE_LINEAR_BIT))     ? 0x10 : 0x00;
            renderableType |= (!(surfaceType & EGL_VG_ALPHA_FORMAT_PRE_BIT))      ? 0x20 : 0x00;
#else
            eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_CONFIG_CAVEAT, &conformant);
            renderableType = (conformant == EGL_NON_CONFORMANT_CONFIG)            ? 0x01 :
                             (!(apiType & EGL_OPENVG_BIT))                        ? 0x02 :
                             (!(surfaceType & (EGL_WINDOW_BIT|EGL_PBUFFER_BIT)) ) ? 0x04 :
                             (!tkTestableConfig(red, green, blue, alpha, lumin) ) ? 0x08 : 0x00;
#endif
        }
        else
        {
            eglGetConfigAttrib(pMe->egl_display, configs[i], EGL_CONFIG_CAVEAT, &conformant);
            renderableType = (conformant == EGL_NON_CONFORMANT_CONFIG)            ? 0x01 :
                             (!(apiType & EGL_OPENVG_BIT))                        ? 0x02 :
                             (!(surfaceType & (EGL_WINDOW_BIT|EGL_PBUFFER_BIT)) ) ? 0x04 :
                             (!tkTestableConfig(red, green, blue, alpha, lumin) ) ? 0x08 : 0x00;
        }

        pMe->list.IDs[pMe->list.count] = configId;
        pMe->list.type[pMe->list.count] = renderableType;
            
        /* Bottom byte of 0 means the config is conformant. */
        if ( (0x0F & pMe->list.type[pMe->list.count]) == 0 )
            pMe->list.conformantCount ++;

        FPRINTF(file, "%d %d %d %d %d %d %d %d %d %d\n", configId, renderableType, red, green, blue, alpha, lumin, mask, sampleBuffers, samples);

        pMe->list.count++;
    }

    FREE(configs);
}

