#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include "SubSurface.h"
#include "EGLClient.h"

extern struct wl_display *display;
extern struct wl_compositor *compositor;
extern struct ivi_application *iviapplication;
extern struct wl_shm *shm;

const int WIDTH = 250;
const int HEIGHT = 250;

SubSurface::SubSurface() :
  m_wlsurface(nullptr),
  m_ivisurface(nullptr),
  m_eglCleint(nullptr),
  m_surfaceId(0),
  m_wasShown(false) {
    m_wlsurface = nullptr;
    m_ivisurface = nullptr;
    m_eglCleint = nullptr;
}

SubSurface::~SubSurface() {
    if (m_eglCleint) {
        delete m_eglCleint;
    }
}

void SubSurface::CreateSurface(int32_t surfaceid) {
    m_eglCleint = new EGLClient(WIDTH, HEIGHT);
    m_eglCleint->initialize();
    m_wlsurface =  m_eglCleint->get_wayland_surface();
    m_ivisurface = ivi_application_surface_create(iviapplication, surfaceid, m_wlsurface);
    m_surfaceId = surfaceid;
    wl_display_flush(display);
}

void SubSurface::Draw() {
    m_eglCleint->redraw(0);
    wl_display_flush(display);
}

void SubSurface::DestroyIviSurface() {
   ivi_surface_destroy(m_ivisurface);
    // m_eglCleint->destroy_ivi_surface();
    // wl_display_flush(display);
}

void SubSurface::DestroyWlSurface() {
    m_eglCleint->destroy_wl_surface();
    wl_display_flush(display);
}

void SubSurface::DestroyWlEglSurface() {
    m_eglCleint->destroy_wl_egl_surface();
    wl_display_flush(display);
}

void SubSurface::DestroyEglSurface() {
    m_eglCleint->destroy_egl_surface();
    wl_display_flush(display);
}


