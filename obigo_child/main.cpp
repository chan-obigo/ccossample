#include <stdio.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern struct wl_display *display;

typedef enum SignalType {
    FROM_SIGNAL_CREATE_APPLICATION,
    FROM_SIGNAL_DESTROY_APPLICATION,
    FROM_SIGNAL_SHOW_APPLICATION,
    FROM_SIGNAL_HIDE_APPLICATION,
    FROM_SIGNAL_DESTROY_IVI_SURFACE,
    FROM_SIGNAL_DESTROY_WL_SURFACE,
    FROM_SIGNAL_DESTROY_WL_EGL_SURFACE,
    FROM_SIGNAL_DESTROY_EGL_SURFACE,
    FROM_SIGNAL_NONE,
};

int actving_surface = 0;
SignalType actving_signal = FROM_SIGNAL_NONE;
SubSurfaceManager subSurfaceManager;

void CreateApplication(const int32_t& index) {
    fprintf(stdout, "[ObigoChild]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    actving_surface = 0;
    actving_signal = FROM_SIGNAL_CREATE_APPLICATION;
}

void DestroyApplication(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_DESTROY_APPLICATION;
}

void ShowApplication(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_SHOW_APPLICATION;
}

void HideApplication(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_HIDE_APPLICATION;
}

void DestroyIviSurface(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_DESTROY_IVI_SURFACE;
}

void DestroyWlSurface(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_DESTROY_WL_SURFACE;
}

void DestroyWlEglSurface(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_DESTROY_WL_EGL_SURFACE;
}

void DestroyEglSurface(const int32_t& surface_id) {
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    actving_surface = surface_id;
    actving_signal = FROM_SIGNAL_DESTROY_EGL_SURFACE;
}

void HandleSignal(SignalType type) {
    switch (type) {
        case FROM_SIGNAL_CREATE_APPLICATION :
            subSurfaceManager.CreateSurface();
            break;
        case FROM_SIGNAL_DESTROY_APPLICATION :
            subSurfaceManager.DestroySurface(actving_surface);
            break;
        case FROM_SIGNAL_SHOW_APPLICATION :
            subSurfaceManager.ShowSurface(actving_surface);
            break;
        case FROM_SIGNAL_HIDE_APPLICATION :
            subSurfaceManager.HideSurface(actving_surface);
            break;
        case FROM_SIGNAL_DESTROY_IVI_SURFACE :
            subSurfaceManager.DestroyIviSurface(actving_surface);
            break;
        case FROM_SIGNAL_DESTROY_WL_SURFACE :
            subSurfaceManager.DestroyWlSurface(actving_surface);
            break;
        case FROM_SIGNAL_DESTROY_WL_EGL_SURFACE :
            subSurfaceManager.DestroyWlEglSurface(actving_surface);
            break;
        case FROM_SIGNAL_DESTROY_EGL_SURFACE :
            subSurfaceManager.DestroyEglSurface(actving_surface);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    fprintf(stdout, "[ObigoChild] started\n"); fflush(stdout);

    subSurfaceManager.Initiailze();
    fprintf(stdout, "[ObigoChild] Initiailze\n"); fflush(stdout);

    v1::commonapi::examples::ObigoProxy::getInstance()->Connect();

    fprintf(stdout, "[ObigoChild] waiting\n"); fflush(stdout);
    while (1) {
        //wl_display_dispatch(display);
        wl_display_dispatch_pending(display);
        if (actving_signal != FROM_SIGNAL_NONE) {
            HandleSignal(actving_signal);
            actving_signal = FROM_SIGNAL_NONE;
        }
        subSurfaceManager.Draw();
        usleep(1000*100);
    }

    return 0;
}
