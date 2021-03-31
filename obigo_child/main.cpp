#include <stdio.h>
#include <unistd.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern struct wl_display *display;
bool g_is_destroy = false;
int g_surface_id = 0;

int main(int argc, char *argv[]) {
    fprintf(stdout, "[ObigoChild] started\n"); fflush(stdout);

    if (argc != 2) {
        fprintf(stdout, "[ObigoChild] invalied argument. example : obigo_child [surface id]\n"); fflush(stdout);        
        return 0;
    }

    g_surface_id = atoi(argv[1]);

    SubSurfaceManager subSurfaceManager;
    subSurfaceManager.Initiailze();
    subSurfaceManager.CreateSubSurface(g_surface_id);

    v1::commonapi::examples::ObigoProxy::getInstance()->Connect();
    v1::commonapi::examples::ObigoProxy::getInstance()->CreateHSubSurface(g_surface_id);

    fprintf(stdout, "[ObigoChild] waiting\n"); fflush(stdout);
    int ret = 0;
    while (1) {
        ret = wl_display_dispatch(display);
        ret = wl_display_dispatch_pending(display);
        subSurfaceManager.Draw();

        if (g_is_destroy) {
            subSurfaceManager.destroy();
            break;
        }
    }

    return 0;
}
