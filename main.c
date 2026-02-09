#include <stdio.h>
#include <stdlib.h>
#include <wayland-client.h>
#include <EGL/egl.h>

int main() {
    // 1. Connect to the Wayland Display
    struct wl_display *wl_disp = wl_display_connect(NULL);
    if (!wl_disp) {
        fprintf(stderr, "Failed to connect to Wayland display\n");
        return 1;
    }
    printf("Successfully connected to Wayland display.\n");

    // 2. Get the EGL Display
    EGLDisplay egl_disp = eglGetDisplay((EGLNativeDisplayType)wl_disp);
    if (egl_disp == EGL_NO_DISPLAY) {
        fprintf(stderr, "Failed to get EGL display\n");
        return 1;
    }

    // 3. Initialize EGL - THIS IS WHERE THE SYMBOL LOOKUP ERROR HAPPENS
    // Mesa will try to load wl_display_create_queue_with_name from libwayland-client
    printf("Attempting eglInitialize...\n");
    EGLint major, minor;
    if (!eglInitialize(egl_disp, &major, &minor)) {
        fprintf(stderr, "eglInitialize failed\n");
        return 1;
    }

    printf("EGL initialized successfully: version %d.%d\n", major, minor);

    eglTerminate(egl_disp);
    wl_display_disconnect(wl_disp);
    return 0;
}