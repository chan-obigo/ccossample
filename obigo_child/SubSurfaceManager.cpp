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

SubSurfaceManager::SubSurfaceManager() :
  m_currentSurfaceIndex(m_startSurfaceIndex),
  m_activeSurface(nullptr),
  m_createdSurface(nullptr) {

}

SubSurfaceManager::~SubSurfaceManager() {
    for (auto surface : m_subSurfaces) {
        delete surface.second;
    }
}

void SubSurfaceManager::Initiailze() {
    display = wl_display_connect(nullptr);
    struct wl_registry *wl_registry = wl_display_get_registry(display);

    wl_registry_add_listener(wl_registry, &listener, nullptr);

    wl_display_dispatch(display);
    wl_display_roundtrip(display);
}

void SubSurfaceManager::Draw() {
    std::map<int, SubSurface*>::iterator it;
    for (it=m_subSurfaces.begin(); it!=m_subSurfaces.end(); ++it) {
        SubSurface* surface = it->second;
        if (surface && surface->Shown()) {
            surface->Draw();
        }
    }
}

SubSurface*  SubSurfaceManager::GetLatestCreatedSurface() {
    if (nullptr == m_activeSurface) {
        m_activeSurface = m_createdSurface;
    }
    return m_activeSurface;
}

void SubSurfaceManager::CreateSurface(int index) {
    int emptySurfaceId = GetEmptySurfaceId();
    fprintf(stdout, "[ObigoChild]::%s::%d::%d is created\n", __func__, __LINE__, emptySurfaceId); fflush(stdout);
    m_createdSurface = new SubSurface();
    m_createdSurface->CreateSurface(emptySurfaceId, index);

    m_subSurfaces[emptySurfaceId] = m_createdSurface;
    v1::commonapi::examples::ObigoProxy::getInstance()->CreatedApplication(emptySurfaceId);
}

void SubSurfaceManager::DestroySurface(int surface_id) {
    std::map<int, SubSurface*>::iterator it;
    for (it=m_subSurfaces.begin(); it!=m_subSurfaces.end(); ++it) {
        if (it->first == surface_id) {
            delete it->second;
            m_subSurfaces.erase(it);
            fprintf(stdout, "[ObigoChild]::%s::%d::%d is removed from list\n", __func__, __LINE__, surface_id); fflush(stdout);
            break;
        }
    }
    v1::commonapi::examples::ObigoProxy::getInstance()->DestroyedApplication(surface_id);
}

void SubSurfaceManager::ShowSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->setShown(true);
    v1::commonapi::examples::ObigoProxy::getInstance()->ShownApplication(surface_id);
}

void SubSurfaceManager::HideSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->setShown(false);
    v1::commonapi::examples::ObigoProxy::getInstance()->HiddenApplication(surface_id);
}

void SubSurfaceManager::DestroyIviSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->DestroyIviSurface();
    v1::commonapi::examples::ObigoProxy::getInstance()->DestroyedIviSurface(surface_id);
}

void SubSurfaceManager::DestroyWlSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->DestroyWlSurface();
    v1::commonapi::examples::ObigoProxy::getInstance()->DestroyedWlSurface(surface_id);
}

void SubSurfaceManager::DestroyWlEglSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->DestroyWlEglSurface();
    v1::commonapi::examples::ObigoProxy::getInstance()->DestroyedWlEglSurface(surface_id);
}

void SubSurfaceManager::DestroyEglSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->DestroyEglSurface();
    v1::commonapi::examples::ObigoProxy::getInstance()->DestroyedEglSurface(surface_id);
}

void SubSurfaceManager::MakeCurrentSurface(int surface_id) {
    SubSurface* surface = m_subSurfaces[surface_id];
    surface->MakeCurrentSurface();
    v1::commonapi::examples::ObigoProxy::getInstance()->MadeCurrentSurface(surface_id);
}
