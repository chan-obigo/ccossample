#include <stdio.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern struct wl_display *display;

int main(int argc, char *argv[]) {
    fprintf(stdout, "[ObigoChild] started\n"); fflush(stdout);


    SubSurfaceManager subSurfaceManager;
    subSurfaceManager.Initiailze();
    subSurfaceManager.CreateSubSurface(1);
    subSurfaceManager.CreateSubSurface(2);

    v1::commonapi::examples::ObigoProxy::getInstance()->Connect();
    v1::commonapi::examples::ObigoProxy::getInstance()->CreateHSubSurface(1);
    v1::commonapi::examples::ObigoProxy::getInstance()->CreateHSubSurface(2);

    fprintf(stdout, "[ObigoChild] waiting\n"); fflush(stdout);
    int ret = 0;
    while (1) {
        ret = wl_display_dispatch(display);
        ret = wl_display_dispatch_pending(display);
        subSurfaceManager.Draw();
    }

    return 0;
}
