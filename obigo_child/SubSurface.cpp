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

const int WIDTH = 1000;
const int HEIGHT = 600;

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

    DestroyIviSurface();
    DestroyWlSurface();
    DestroyWlEglSurface();
    DestroyEglSurface();

    if (m_eglCleint) {
        delete m_eglCleint;
    }
}

void SubSurface::CreateSurface(int32_t surfaceid, int index) {
    m_eglCleint = new EGLClient(WIDTH, HEIGHT, index);
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
    if (!m_ivisurface) {
        return;
    }
    ivi_surface_destroy(m_ivisurface);
    m_ivisurface = nullptr;
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, m_surfaceId); fflush(stdout);
    // m_eglCleint->destroy_ivi_surface();
    // wl_display_flush(display);
}

void SubSurface::DestroyWlSurface() {
    m_eglCleint->destroy_wl_surface();
    wl_display_flush(display);
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, m_surfaceId); fflush(stdout);
}

void SubSurface::DestroyWlEglSurface() {
    m_eglCleint->destroy_wl_egl_surface();
    wl_display_flush(display);
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, m_surfaceId); fflush(stdout);
}

void SubSurface::DestroyEglSurface() {
    m_eglCleint->destroy_egl_surface();
    wl_display_flush(display);
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, m_surfaceId); fflush(stdout);
}

void SubSurface::MakeCurrentSurface() {
    m_eglCleint->make_current();
    wl_display_flush(display);
    fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, m_surfaceId); fflush(stdout);
}



