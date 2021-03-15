#include <stdio.h>
#include <string.h>
#include <wayland-client-protocol.h>

#include "ObigoProxy.h"
#include "SubSurfaceManager.h"

extern const struct wl_interface ivi_application_interface;

struct wl_display *display = nullptr;
struct wl_compositor *compositor = nullptr;
struct ivi_application *iviapplication = nullptr;
struct wl_shm *shm = nullptr;

static void global_registry_handler(void *data,
                                    struct wl_registry *registry,
                                    uint32_t id,
                                    const char *interface,
                                    uint32_t version) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = static_cast<wl_compositor*>(wl_registry_bind(registry, id, &wl_compositor_interface, 1));
    } else if (strcmp(interface, "ivi_application") == 0) {
        iviapplication = static_cast<ivi_application*>(wl_registry_bind(registry, id, &ivi_application_interface, 1));
    } else if (strcmp(interface, "wl_shm") == 0) {
        shm = static_cast<wl_shm*>(wl_registry_bind(registry, id, &wl_shm_interface, 1));
    }
}

static void global_registry_remover(void *data, struct wl_registry *registry, uint32_t id) {
}

const struct wl_registry_listener listener = {
    global_registry_handler,
    global_registry_remover
};

SubSurfaceManager::SubSurfaceManager() {}

SubSurfaceManager::~SubSurfaceManager() {}

void SubSurfaceManager::Initiailze() {
    display = wl_display_connect(nullptr);
    struct wl_registry *wl_registry = wl_display_get_registry(display);

    wl_registry_add_listener(wl_registry, &listener, nullptr);

    wl_display_dispatch(display);
    wl_display_roundtrip(display);
}

void SubSurfaceManager::CreateSubSurface(int32_t surfaceid) {
    SubSurface* pSubSurface = new SubSurface();
    pSubSurface->CreateSurface(surfaceid);

    m_subSurfaces.push_back(pSubSurface);
}
