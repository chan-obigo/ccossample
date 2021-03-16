#include <stdio.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern struct wl_display *display;

int main(int argc, char *argv[]) {
    SubSurfaceManager subSurfaceManager;

    fprintf(stdout, "[ObigoChild] started\n"); fflush(stdout);
    subSurfaceManager.Initiailze();

    subSurfaceManager.CreateSubSurface(27777);
    subSurfaceManager.CreateSubSurface(27778);
    subSurfaceManager.CreateSubSurface(27779);
    subSurfaceManager.CreateSubSurface(27780);

    // v1::commonapi::examples::ObigoProxy::getInstance()->Connect();

    fprintf(stdout, "[ObigoChild] waiting\n"); fflush(stdout);
    int ret = 0;
    while (1) {
        ret = wl_display_dispatch(display);
        ret = wl_display_dispatch_pending(display);
        sleep(1);
    }

    return 0;
}
