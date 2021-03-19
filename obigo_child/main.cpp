#include <stdio.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern struct wl_display *display;

typedef enum SignalType {
    FROM_SIGNAL_CREATE_APPLICATION,
    FROM_SIGNAL_DESTROY_APPLICATION,
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

void HandleSignal(SignalType type) {
    switch (type) {
        case FROM_SIGNAL_CREATE_APPLICATION :
            subSurfaceManager.CreateSubSurface();
            fprintf(stdout, "[ObigoChild] CreateSubSurface\n"); fflush(stdout);
            break;
        case FROM_SIGNAL_DESTROY_APPLICATION :
            subSurfaceManager.DestroySubSurface(actving_surface);
            fprintf(stdout, "[ObigoChild] DestroySubSurface\n"); fflush(stdout);
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
